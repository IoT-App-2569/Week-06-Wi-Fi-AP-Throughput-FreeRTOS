#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"

static const char *TAG = "SMART_ATTENDANCE";

#define AP_SSID           "CLASSROOM_ATTENDANCE_AP"
#define AP_PASS           "12345678"
#define RSSI_NEAR         -55   // dBm: อยู่ในรัศมีโต๊ะปฏิบัติการ (ตรงตาม sequence diagram)
#define RSSI_FAR          -70   // dBm: อยู่นอกห้องเรียน
#define MAX_STUDENTS      5

typedef struct {
    char mac_str[18];
    int8_t rssi;
    bool checked_in;
    uint32_t timestamp_sec;
} student_record_t;

static student_record_t s_records[MAX_STUDENTS];
static int s_student_count = 0;

// ------------------------------------------------------------------
// อัพเดต RSSI จริงของทุกอุปกรณ์ที่เชื่อมต่ออยู่ (เรียกก่อน render หน้าเว็บทุกครั้ง)
// ------------------------------------------------------------------
static void refresh_rssi_from_sta_list(void) {
    wifi_sta_list_t sta_list;
    if (esp_wifi_ap_get_sta_list(&sta_list) != ESP_OK) {
        return;
    }

    for (int i = 0; i < sta_list.num; i++) {
        char mac_str[18];
        snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X",
                 sta_list.sta[i].mac[0], sta_list.sta[i].mac[1], sta_list.sta[i].mac[2],
                 sta_list.sta[i].mac[3], sta_list.sta[i].mac[4], sta_list.sta[i].mac[5]);

        // หา record ที่ตรงกับ MAC นี้ แล้วอัพเดต RSSI จริง
        for (int j = 0; j < s_student_count; j++) {
            if (strcmp(s_records[j].mac_str, mac_str) == 0) {
                s_records[j].rssi = sta_list.sta[i].rssi;
                break;
            }
        }
    }
}

// ------------------------------------------------------------------
// GET / -> แสดงหน้า Dashboard + ตารายชื่อ
// ------------------------------------------------------------------
static esp_err_t http_attendance_html_handler(httpd_req_t *req) {
    refresh_rssi_from_sta_list();

    char resp[2048];
    int len = snprintf(resp, sizeof(resp),
        "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<style>body{font-family:Arial;text-align:center;background:#f4f4f9;padding:20px;}"
        ".card{background:white;padding:20px;border-radius:10px;box-shadow:0 2px 5px rgba(0,0,0,0.2);}"
        "table{width:100%%;border-collapse:collapse;margin-top:15px;}"
        "th,td{border:1px solid #ddd;padding:8px;text-align:center;}"
        "th{background:#4CAF50;color:white;}"
        ".btn{background:#2196F3;color:white;padding:10px 20px;border:none;border-radius:5px;cursor:pointer;font-size:16px;}"
        "</style></head><body>"
        "<div class='card'><h2>Smart Classroom Proximity Check-in</h2>"
        "<p>Connect Status: <b>PROXIMITY ACTIVE</b></p>"
        "<form action='/checkin' method='POST'><button class='btn'>Confirm Attendance (1-Click)</button></form>"
        "<h3>Active Connected Devices</h3>"
        "<table><tr><th>Device MAC</th><th>RSSI (dBm)</th><th>Proximity Status</th><th>Check-in</th></tr>");

    for (int i = 0; i < s_student_count; i++) {
        char status_str[64];
        if (s_records[i].rssi >= RSSI_NEAR) {
            snprintf(status_str, sizeof(status_str), "<font color='green'><b>NEAR (Valid)</b></font>");
        } else if (s_records[i].rssi <= RSSI_FAR) {
            snprintf(status_str, sizeof(status_str), "<font color='red'>FAR (Out of Room)</font>");
        } else {
            snprintf(status_str, sizeof(status_str), "<font color='orange'>BORDERLINE</font>");
        }
        len += snprintf(resp + len, sizeof(resp) - len,
            "<tr><td>%s</td><td>%d dBm</td><td>%s</td><td>%s</td></tr>",
            s_records[i].mac_str, s_records[i].rssi, status_str,
            s_records[i].checked_in ? "PASSED" : "-");
    }

    len += snprintf(resp + len, sizeof(resp) - len, "</table></div></body></html>");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// ------------------------------------------------------------------
// POST /checkin -> ยืนยันลงชื่อ โดยเช็ค RSSI ล่าสุดของผู้ขอ (ระบุจาก source IP->MAC ผ่าน ARP ไม่ตรงตัวง่ายบน ESP-IDF
// ในระดับ lab นี้ ใช้แนวทางง่าย: เช็ค record ล่าสุดที่เชื่อมต่อ (index ล่าสุด) หรือทุกคนที่ผ่านเกณฑ์
// ------------------------------------------------------------------
static esp_err_t http_checkin_handler(httpd_req_t *req) {
    refresh_rssi_from_sta_list();

    char resp[512];
    bool any_passed = false;

    for (int i = 0; i < s_student_count; i++) {
        if (s_records[i].rssi >= RSSI_NEAR) {
            s_records[i].checked_in = true;
            s_records[i].timestamp_sec = xTaskGetTickCount() * portTICK_PERIOD_MS / 1000;
            any_passed = true;
            ESP_LOGI(TAG, "[CHECK-IN PASSED]: %s RSSI=%d dBm", s_records[i].mac_str, s_records[i].rssi);
        } else {
            ESP_LOGW(TAG, "[CHECK-IN REJECTED]: %s RSSI=%d dBm (too far)", s_records[i].mac_str, s_records[i].rssi);
        }
    }

    if (any_passed) {
        snprintf(resp, sizeof(resp),
            "<html><body style='font-family:Arial;text-align:center;padding:40px;'>"
            "<h2 style='color:green;'>Check-in Successful!</h2>"
            "<p>Distance: Near (within table radius)</p>"
            "<a href='/'>Back</a></body></html>");
    } else {
        snprintf(resp, sizeof(resp),
            "<html><body style='font-family:Arial;text-align:center;padding:40px;'>"
            "<h2 style='color:red;'>Signal too weak!</h2>"
            "<p>You are not within the classroom radius. Move closer and try again.</p>"
            "<a href='/'>Back</a></body></html>");
    }

    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static void start_web_server(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t uri_get = {
            .uri = "/", .method = HTTP_GET, .handler = http_attendance_html_handler, .user_ctx = NULL
        };
        httpd_uri_t uri_checkin = {
            .uri = "/checkin", .method = HTTP_POST, .handler = http_checkin_handler, .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_checkin);
        ESP_LOGI(TAG, "Attendance Web Server Started at http://192.168.4.1");
    } else {
        ESP_LOGE(TAG, "Failed to start HTTP server!");
    }
}

// ------------------------------------------------------------------
// Wi-Fi Event: ตรวจจับอุปกรณ์ใหม่เชื่อมต่อเข้ามา (Proximity Detected)
// ------------------------------------------------------------------
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        if (s_student_count < MAX_STUDENTS) {
            snprintf(s_records[s_student_count].mac_str, 18, "%02X:%02X:%02X:%02X:%02X:%02X",
                     event->mac[0], event->mac[1], event->mac[2],
                     event->mac[3], event->mac[4], event->mac[5]);
            s_records[s_student_count].rssi = -100; // ค่าเริ่มต้นก่อนอ่าน RSSI จริงครั้งแรก
            s_records[s_student_count].checked_in = false;
            s_records[s_student_count].timestamp_sec = 0;
            s_student_count++;
            ESP_LOGI(TAG, "[PROXIMITY DETECTED]: New device connected! MAC: %02X:%02X:%02X:%02X:%02X:%02X",
                     event->mac[0], event->mac[1], event->mac[2],
                     event->mac[3], event->mac[4], event->mac[5]);
        } else {
            ESP_LOGW(TAG, "[FULL]: Max student capacity reached, cannot register new device.");
        }
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGW(TAG, "[DISCONNECTED]: MAC: %02X:%02X:%02X:%02X:%02X:%02X",
                 event->mac[0], event->mac[1], event->mac[2],
                 event->mac[3], event->mac[4], event->mac[5]);
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "==========================================================");
    ESP_LOGI(TAG, "  Lab 6-5: Smart RF Proximity & Sensor Fusion Attendance");
    ESP_LOGI(TAG, "==========================================================");

    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_ap();

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

    ESP_LOGI(TAG, "SoftAP Running! SSID: %s  Password: %s", AP_SSID, AP_PASS);
    ESP_LOGI(TAG, "RSSI Threshold -> Near: >= %d dBm, Far: <= %d dBm", RSSI_NEAR, RSSI_FAR);

    start_web_server();
}