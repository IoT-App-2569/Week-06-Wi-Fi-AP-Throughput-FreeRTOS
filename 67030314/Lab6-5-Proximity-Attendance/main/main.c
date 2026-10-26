#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "lwip/sockets.h"

static const char *TAG = "SMART_ATTENDANCE";

#define AP_SSID          "CLASSROOM_ATTENDANCE_AP"
#define AP_PASS          "12345678"
#define RSSI_THRESHOLD   -55  // dBm threshold for proximity check (within lab-desk radius)
#define MAX_STUDENTS     5

typedef struct {
    uint8_t mac[6];
    char mac_str[18];
    int8_t rssi;
    bool online;
    bool checked_in;
    uint32_t timestamp_sec;
} student_record_t;

static student_record_t s_records[MAX_STUDENTS];
static int s_student_count = 0;
static SemaphoreHandle_t s_records_lock;   // shared by Wi-Fi event task and httpd task
static esp_netif_t *s_ap_netif;

// Find a record by MAC, or add a new one (call with s_records_lock held)
static student_record_t *find_or_add_record(const uint8_t mac[6]) {
    for (int i = 0; i < s_student_count; i++) {
        if (memcmp(s_records[i].mac, mac, 6) == 0) {
            return &s_records[i];
        }
    }
    if (s_student_count >= MAX_STUDENTS) {
        return NULL;
    }
    student_record_t *rec = &s_records[s_student_count++];
    memset(rec, 0, sizeof(*rec));
    memcpy(rec->mac, mac, 6);
    snprintf(rec->mac_str, sizeof(rec->mac_str), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return rec;
}

// Update RSSI of every connected station from the Wi-Fi driver (real measurement)
static void refresh_rssi(void) {
    wifi_sta_list_t sta_list;
    if (esp_wifi_ap_get_sta_list(&sta_list) != ESP_OK) {
        return;
    }
    xSemaphoreTake(s_records_lock, portMAX_DELAY);
    for (int i = 0; i < s_student_count; i++) {
        s_records[i].online = false;
    }
    for (int i = 0; i < sta_list.num; i++) {
        student_record_t *rec = find_or_add_record(sta_list.sta[i].mac);
        if (rec) {
            rec->rssi = sta_list.sta[i].rssi;
            rec->online = true;
        }
    }
    xSemaphoreGive(s_records_lock);
}

// Identify which phone sent the request: socket peer IP -> DHCP lease -> MAC
static bool mac_from_request(httpd_req_t *req, uint8_t mac_out[6]) {
    struct sockaddr_storage addr;
    socklen_t addr_len = sizeof(addr);
    if (getpeername(httpd_req_to_sockfd(req), (struct sockaddr *)&addr, &addr_len) != 0) {
        return false;
    }
    uint32_t peer_ip;
    if (addr.ss_family == AF_INET) {
        peer_ip = ((struct sockaddr_in *)&addr)->sin_addr.s_addr;
    } else {
        // IPv4-mapped IPv6 address (::ffff:192.168.4.x)
        peer_ip = ((struct sockaddr_in6 *)&addr)->sin6_addr.un.u32_addr[3];
    }

    wifi_sta_list_t sta_list;
    if (esp_wifi_ap_get_sta_list(&sta_list) != ESP_OK || sta_list.num == 0) {
        return false;
    }
    esp_netif_pair_mac_ip_t pairs[ESP_WIFI_MAX_CONN_NUM];
    for (int i = 0; i < sta_list.num; i++) {
        memcpy(pairs[i].mac, sta_list.sta[i].mac, 6);
    }
    if (esp_netif_dhcps_get_clients_by_mac(s_ap_netif, sta_list.num, pairs) != ESP_OK) {
        return false;
    }
    for (int i = 0; i < sta_list.num; i++) {
        if (pairs[i].ip.addr == peer_ip) {
            memcpy(mac_out, pairs[i].mac, 6);
            return true;
        }
    }
    return false;
}

// HTTP GET Handler for Attendance Web Dashboard (sent in chunks: no fixed-size buffer limit)
static esp_err_t http_attendance_html_handler(httpd_req_t *req) {
    refresh_rssi();
    httpd_resp_set_type(req, "text/html");
    httpd_resp_sendstr_chunk(req,
        "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<meta http-equiv='refresh' content='3'>"
        "<style>body{font-family:Arial;text-align:center;background:#f4f4f9;padding:20px;}"
        ".card{background:white;padding:20px;border-radius:10px;box-shadow:0 2px 5px rgba(0,0,0,0.2);}"
        "table{width:100%;border-collapse:collapse;margin-top:15px;}"
        "th,td{border:1px solid #ddd;padding:8px;text-align:center;}"
        "th{background:#4CAF50;color:white;}"
        ".btn{background:#2196F3;color:white;padding:10px 20px;border:none;border-radius:5px;cursor:pointer;}"
        "</style></head><body>"
        "<div class='card'><h2>Smart Classroom Proximity Check-in</h2>"
        "<p>Connect Status: <b>PROXIMITY ACTIVE</b> (threshold " );

    char line[256];
    snprintf(line, sizeof(line), "%d dBm)</p>", RSSI_THRESHOLD);
    httpd_resp_sendstr_chunk(req, line);
    httpd_resp_sendstr_chunk(req,
        "<form action='/checkin' method='POST'><button class='btn'>Confirm Attendance (1-Click)</button></form>"
        "<h3>Active Connected Devices</h3>"
        "<table><tr><th>Device MAC</th><th>RSSI (dBm)</th><th>Proximity Status</th><th>Check-in</th></tr>");

    xSemaphoreTake(s_records_lock, portMAX_DELAY);
    for (int i = 0; i < s_student_count; i++) {
        const student_record_t *rec = &s_records[i];
        char status_str[64];
        char checkin_str[48];
        if (!rec->online) {
            snprintf(status_str, sizeof(status_str), "<font color='gray'>OFFLINE</font>");
        } else if (rec->rssi >= RSSI_THRESHOLD) {
            snprintf(status_str, sizeof(status_str), "<font color='green'><b>NEAR (Valid)</b></font>");
        } else {
            snprintf(status_str, sizeof(status_str), "<font color='red'>FAR (Invalid)</font>");
        }
        if (rec->checked_in) {
            snprintf(checkin_str, sizeof(checkin_str), "Passed @ %lus", (unsigned long)rec->timestamp_sec);
        } else {
            snprintf(checkin_str, sizeof(checkin_str), "-");
        }
        snprintf(line, sizeof(line), "<tr><td>%s</td><td>%d dBm</td><td>%s</td><td>%s</td></tr>",
                 rec->mac_str, rec->rssi, status_str, checkin_str);
        httpd_resp_sendstr_chunk(req, line);
    }
    xSemaphoreGive(s_records_lock);

    httpd_resp_sendstr_chunk(req, "</table></div></body></html>");
    httpd_resp_sendstr_chunk(req, NULL);   // end of chunked response
    return ESP_OK;
}

// HTTP POST Handler: check in only when the requesting phone is near enough
static esp_err_t http_checkin_handler(httpd_req_t *req) {
    char body[64];
    int remaining = req->content_len;
    while (remaining > 0) {   // discard the (empty) form body
        int r = httpd_req_recv(req, body, remaining < (int)sizeof(body) ? remaining : (int)sizeof(body));
        if (r <= 0) {
            break;
        }
        remaining -= r;
    }

    refresh_rssi();
    uint8_t mac[6];
    char msg[256];
    if (!mac_from_request(req, mac)) {
        snprintf(msg, sizeof(msg), "<h2>Device not found</h2>");
    } else {
        xSemaphoreTake(s_records_lock, portMAX_DELAY);
        student_record_t *rec = find_or_add_record(mac);
        if (rec == NULL) {
            snprintf(msg, sizeof(msg), "<h2>Classroom is full</h2>");
        } else if (rec->rssi >= RSSI_THRESHOLD) {
            rec->checked_in = true;
            rec->timestamp_sec = (uint32_t)(esp_timer_get_time() / 1000000);
            ESP_LOGI(TAG, "[CHECK-IN PASSED]: %s RSSI=%d dBm", rec->mac_str, rec->rssi);
            snprintf(msg, sizeof(msg), "<h2 style='color:green'>PASSED</h2><p>%s<br>RSSI %d dBm</p>",
                     rec->mac_str, rec->rssi);
        } else {
            ESP_LOGW(TAG, "[CHECK-IN REJECTED]: %s RSSI=%d dBm < %d dBm", rec->mac_str, rec->rssi, RSSI_THRESHOLD);
            snprintf(msg, sizeof(msg), "<h2 style='color:red'>REJECTED</h2><p>%s<br>RSSI %d dBm (need &ge; %d dBm)</p>",
                     rec->mac_str, rec->rssi, RSSI_THRESHOLD);
        }
        xSemaphoreGive(s_records_lock);
    }

    httpd_resp_set_type(req, "text/html");
    httpd_resp_sendstr_chunk(req, "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'></head>"
                                  "<body style='font-family:Arial;text-align:center;padding:20px;'>");
    httpd_resp_sendstr_chunk(req, msg);
    httpd_resp_sendstr_chunk(req, "<p><a href='/'>Back to dashboard</a></p></body></html>");
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

static void start_web_server(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t uri_get = {
            .uri      = "/",
            .method   = HTTP_GET,
            .handler  = http_attendance_html_handler,
            .user_ctx = NULL
        };
        httpd_uri_t uri_checkin = {
            .uri      = "/checkin",
            .method   = HTTP_POST,
            .handler  = http_checkin_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_checkin);
        ESP_LOGI(TAG, "Attendance Web Server Started at http://192.168.4.1");
    }
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        xSemaphoreTake(s_records_lock, portMAX_DELAY);
        student_record_t *rec = find_or_add_record(event->mac);
        if (rec) {
            rec->online = true;
        }
        xSemaphoreGive(s_records_lock);
        ESP_LOGI(TAG, "[PROXIMITY DETECTED]: New student device connected! (AID=%d)", event->aid);
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        xSemaphoreTake(s_records_lock, portMAX_DELAY);
        student_record_t *rec = find_or_add_record(event->mac);
        if (rec) {
            rec->online = false;
        }
        xSemaphoreGive(s_records_lock);
        ESP_LOGI(TAG, "[PROXIMITY LOST]: Student device disconnected (AID=%d)", event->aid);
    }
}

void app_main(void) {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    s_ap_netif = esp_netif_create_default_wifi_ap();
    s_records_lock = xSemaphoreCreateMutex();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .ssid_len = strlen(AP_SSID),
            .password = AP_PASS,
            .max_connection = MAX_STUDENTS,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();

    start_web_server();
}
