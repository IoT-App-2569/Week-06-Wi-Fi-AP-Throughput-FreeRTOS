// =============================================================
//  Lab 6-5: Assignment Project — Smart RF Proximity Attendance System
//  ESP32 SoftAP + FreeRTOS Task + Real RSSI Scanning + HTTP Web Server
// =============================================================

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"

static const char *TAG = "SMART_ATTENDANCE";

#define AP_SSID          "CLASSROOM_ATTENDANCE_AP_0085"
#define AP_PASS          "12345678"
#define RSSI_THRESHOLD   -60  // dBm threshold for valid proximity check

typedef struct {
    char mac_str[18];
    uint8_t raw_mac[6];
    int8_t rssi;
    bool checked_in;
    uint32_t timestamp_sec;
} student_record_t;

static student_record_t s_records[10];
static int s_student_count = 0;
static SemaphoreHandle_t s_records_mutex = NULL;

// =============================================================
//  Helper: Find or Add Student Record by MAC
// =============================================================
static int find_or_add_student(const uint8_t mac[6]) {
    char mac_buf[18];
    snprintf(mac_buf, sizeof(mac_buf), "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    for (int i = 0; i < s_student_count; i++) {
        if (memcmp(s_records[i].raw_mac, mac, 6) == 0) {
            return i;
        }
    }

    if (s_student_count < 10) {
        int idx = s_student_count;
        memcpy(s_records[idx].raw_mac, mac, 6);
        strncpy(s_records[idx].mac_str, mac_buf, 18);
        s_records[idx].rssi = -70;
        s_records[idx].checked_in = false;
        s_records[idx].timestamp_sec = 0;
        s_student_count++;
        return idx;
    }
    return -1;
}

// =============================================================
//  HTTP GET / Handler: Dashboard
// =============================================================
static esp_err_t http_attendance_html_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "[HTTP]: GET / requested");

    char *resp = malloc(4096);
    if (!resp) {
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    int len = snprintf(resp, 4096,
        "<!DOCTYPE html><html lang='th'>"
        "<head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<title>Smart Classroom Check-in</title>"
        "<style>"
        "  body{font-family:'Segoe UI',sans-serif;background:#0f172a;color:#e2e8f0;margin:0;padding:20px;display:flex;justify-content:center;}"
        "  .card{background:#1e293b;border:1px solid #334155;border-radius:16px;padding:24px;width:100%%;max-width:520px;box-shadow:0 10px 25px rgba(0,0,0,0.5);}"
        "  h2{color:#38bdf8;text-align:center;margin-bottom:8px;}"
        "  p.status{text-align:center;color:#94a3b8;font-size:0.9rem;margin-bottom:20px;}"
        "  table{width:100%%;border-collapse:collapse;margin-top:15px;}"
        "  th,td{border-bottom:1px solid #334155;padding:12px;text-align:center;font-size:0.85rem;}"
        "  th{background:#0f172a;color:#38bdf8;text-transform:uppercase;letter-spacing:0.05em;}"
        "  .btn{display:block;width:100%%;background:#2563eb;color:white;padding:14px;border:none;border-radius:10px;font-size:1rem;font-weight:bold;cursor:pointer;margin-top:20px;transition:0.2s;}"
        "  .btn:hover{background:#1d4ed8;}"
        "  .badge-near{color:#4ade80;font-weight:bold;}"
        "  .badge-far{color:#f87171;font-weight:bold;}"
        "  .checked{color:#38bdf8;font-weight:bold;}"
        "</style></head><body>"
        "<div class='card'>"
        "<h2>📋 Smart Classroom Attendance</h2>"
        "<p class='status'>RF Proximity System (Threshold: <b>%d dBm</b>)</p>"
        "<form action='/checkin' method='POST'>"
        "  <button class='btn'>⚡ Confirm Attendance (1-Click)</button>"
        "</form>"
        "<h3 style='margin-top:24px;font-size:1.1rem;color:#cbd5e1;'>Connected Devices (%d)</h3>"
        "<table><tr><th>Device MAC</th><th>RSSI</th><th>Proximity</th><th>Check-in</th></tr>",
        RSSI_THRESHOLD, s_student_count);

    xSemaphoreTake(s_records_mutex, portMAX_DELAY);
    for (int i = 0; i < s_student_count; i++) {
        char prox_str[64];
        if (s_records[i].rssi >= RSSI_THRESHOLD) {
            snprintf(prox_str, sizeof(prox_str), "<span class='badge-near'>NEAR (Valid)</span>");
        } else {
            snprintf(prox_str, sizeof(prox_str), "<span class='badge-far'>FAR (Invalid)</span>");
        }

        char check_str[64];
        if (s_records[i].checked_in) {
            snprintf(check_str, sizeof(check_str), "<span class='checked'>PASSED ✅</span>");
        } else {
            snprintf(check_str, sizeof(check_str), "<span style='color:#64748b;'>PENDING</span>");
        }

        len += snprintf(resp + len, 4096 - len,
            "<tr><td>%s</td><td>%d dBm</td><td>%s</td><td>%s</td></tr>",
            s_records[i].mac_str, s_records[i].rssi, prox_str, check_str);
    }
    xSemaphoreGive(s_records_mutex);

    len += snprintf(resp + len, 4096 - len, "</table></div></body></html>");

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    free(resp);
    return ESP_OK;
}

// =============================================================
//  HTTP POST /checkin Handler: Confirm Attendance
// =============================================================
static esp_err_t http_checkin_post_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "[HTTP]: POST /checkin received");

    // โค้ดสร้างผลลัพธ์การเช็กชื่อ
    char html_resp[1024];
    bool success = false;
    int client_rssi = -99;
    char client_mac[18] = "Unknown";

    xSemaphoreTake(s_records_mutex, portMAX_DELAY);
    if (s_student_count > 0) {
        // อัปเดตสถานะของเครื่องแรกสุด/เครื่องล่าสุดที่ส่ง request
        s_records[0].checked_in = true;
        s_records[0].timestamp_sec = xTaskGetTickCount() * portTICK_PERIOD_MS / 1000;
        client_rssi = s_records[0].rssi;
        strncpy(client_mac, s_records[0].mac_str, sizeof(client_mac));
        success = (client_rssi >= RSSI_THRESHOLD);
    }
    xSemaphoreGive(s_records_mutex);

    if (success) {
        snprintf(html_resp, sizeof(html_resp),
            "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
            "<meta name='viewport' content='width=device-width, initial-scale=1'>"
            "<style>body{font-family:Arial;background:#0f172a;color:white;text-align:center;padding:40px;}</style>"
            "</head><body>"
            "<h1 style='color:#4ade80;'>✅ CHECK-IN PASSED!</h1>"
            "<p>MAC Address: <b>%s</b></p>"
            "<p>Measured RSSI: <b>%d dBm</b> (Valid Proximity)</p>"
            "<br><a href='/' style='color:#38bdf8;'>Back to Dashboard</a>"
            "</body></html>", client_mac, client_rssi);
    } else {
        snprintf(html_resp, sizeof(html_resp),
            "<!DOCTYPE html><html><head><meta charset='UTF-8'>"
            "<meta name='viewport' content='width=device-width, initial-scale=1'>"
            "<style>body{font-family:Arial;background:#0f172a;color:white;text-align:center;padding:40px;}</style>"
            "</head><body>"
            "<h1 style='color:#f87171;'>❌ CHECK-IN REJECTED!</h1>"
            "<p>MAC Address: <b>%s</b></p>"
            "<p>Measured RSSI: <b>%d dBm</b> (Too Far / Invalid Distance)</p>"
            "<br><a href='/' style='color:#38bdf8;'>Try Again</a>"
            "</body></html>", client_mac, client_rssi);
    }

    httpd_resp_set_type(req, "text/html");
    httpd_resp_send(req, html_resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// =============================================================
//  HTTP 404 Captive Portal Redirect Handler
// =============================================================
static esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err) {
    httpd_resp_set_status(req, "302 Found");
    httpd_resp_set_hdr(req, "Location", "http://192.168.4.1/");
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

// =============================================================
//  Start Web Server
// =============================================================
static void start_web_server(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t uri_get = {
            .uri      = "/",
            .method   = HTTP_GET,
            .handler  = http_attendance_html_handler,
            .user_ctx = NULL
        };
        httpd_uri_t uri_post = {
            .uri      = "/checkin",
            .method   = HTTP_POST,
            .handler  = http_checkin_post_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &uri_get);
        httpd_register_uri_handler(server, &uri_post);
        httpd_register_err_handler(server, HTTPD_404_NOT_FOUND, http_404_error_handler);
        ESP_LOGI(TAG, "[SERVER]: Attendance Web Server Started at http://192.168.4.1");
    }
}

// =============================================================
//  FreeRTOS Task: Periodic STA RSSI Scanner
// =============================================================
static void vProximityScannerTask(void *pvParameters) {
    wifi_sta_list_t sta_list;

    while (1) {
        if (esp_wifi_ap_get_sta_list(&sta_list) == ESP_OK) {
            xSemaphoreTake(s_records_mutex, portMAX_DELAY);
            for (int i = 0; i < sta_list.num; i++) {
                int idx = find_or_add_student(sta_list.sta[i].mac);
                if (idx >= 0) {
                    s_records[idx].rssi = sta_list.sta[i].rssi;
                    ESP_LOGI(TAG, "[PROXIMITY SCAN]: STA[%d] MAC=%s RSSI=%d dBm",
                             i, s_records[idx].mac_str, s_records[idx].rssi);
                }
            }
            xSemaphoreGive(s_records_mutex);
        }
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

// =============================================================
//  Wi-Fi Event Handler
// =============================================================
static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        xSemaphoreTake(s_records_mutex, portMAX_DELAY);
        int idx = find_or_add_student(event->mac);
        if (idx >= 0) {
            ESP_LOGI(TAG, "🎉 [PROXIMITY DETECTED]: Device %s connected to Attendance AP!", s_records[idx].mac_str);
        }
        xSemaphoreGive(s_records_mutex);
    }
}

// =============================================================
//  app_main
// =============================================================
void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    s_records_mutex = xSemaphoreCreateMutex();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .ssid_len = strlen(AP_SSID),
            .password = AP_PASS,
            .max_connection = 5,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    if (strlen(AP_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    start_web_server();

    // สร้าง FreeRTOS Task คอยสแกนค่า RSSI ของอุปกรณ์ที่ต่ออยู่อย่างต่อเนื่อง
    xTaskCreate(vProximityScannerTask, "ProximityTask", 4096, NULL, 5, NULL);

    ESP_LOGI(TAG, "=======================================================");
    ESP_LOGI(TAG, " Smart Classroom Proximity Attendance System Ready!");
    ESP_LOGI(TAG, " Connect Wi-Fi: %s (Pass: %s)", AP_SSID, AP_PASS);
    ESP_LOGI(TAG, " Open Browser  : http://192.168.4.1");
    ESP_LOGI(TAG, "=======================================================");
}