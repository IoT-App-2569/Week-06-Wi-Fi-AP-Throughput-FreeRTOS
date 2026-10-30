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

#define AP_SSID          "CLASSROOM_ATTENDANCE_AP_0181"
#define AP_PASS          "12345678"
#define RSSI_THRESHOLD   -60  // dBm threshold for proximity check
#define MAX_STUDENTS     5

typedef struct {
    char mac_str[18];
    int8_t rssi;
    bool checked_in;
    uint32_t timestamp_sec;
} student_record_t;

static student_record_t s_records[MAX_STUDENTS];
static int s_student_count = 0;

// HTTP GET Handler for Attendance Web Dashboard
static esp_err_t http_attendance_html_handler(httpd_req_t *req) {
    // 1. ส่งส่วน Header และ CSS ตรงๆ ไม่ผ่าน snprintf เพื่อป้องกัน Buffer Truncation Error
    const char* html_header = 
        "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
        "<style>body{font-family:Arial;text-align:center;background:#f4f4f9;padding:20px;}"
        ".card{background:white;padding:20px;border-radius:10px;box-shadow:0 2px 5px rgba(0,0,0,0.2);}"
        "table{width:100%;border-collapse:collapse;margin-top:15px;}"
        "th,td{border:1px solid #ddd;padding:8px;text-align:center;}"
        "th{background:#4CAF50;color:white;}"
        ".btn{background:#2196F3;color:white;padding:10px 20px;border:none;border-radius:5px;cursor:pointer;}"
        "</style></head><body>"
        "<div class='card'><h2>Smart Classroom Proximity Check-in</h2>"
        "<p>Connect Status: <b>PROXIMITY ACTIVE</b></p>"
        "<form action='/checkin' method='POST'><button class='btn'>Confirm Attendance (1-Click)</button></form>"
        "<h3>Active Connected Devices</h3>"
        "<table><tr><th>Device MAC</th><th>RSSI (dBm)</th><th>Proximity Status</th></tr>";
    
    httpd_resp_send_chunk(req, html_header, HTTPD_RESP_USE_STRLEN);

    // 2. ใช้ Buffer ขนาดเล็ก 256 บล็อก สำหรับข้อมูล Dynamic ใน loop
    char chunk[256];
    for (int i = 0; i < s_student_count; i++) {
        const char* status_str = (s_records[i].rssi >= RSSI_THRESHOLD) 
            ? "<font color='green'><b>NEAR (Valid)</b></font>" 
            : "<font color='red'>FAR (Invalid)</font>";

        snprintf(chunk, sizeof(chunk),
            "<tr><td>%s</td><td>%d dBm</td><td>%s</td></tr>",
            s_records[i].mac_str, s_records[i].rssi, status_str);
        httpd_resp_send_chunk(req, chunk, HTTPD_RESP_USE_STRLEN);
    }

    // 3. ส่งส่วนปิด HTML
    const char* html_footer = "</table></div></body></html>";
    httpd_resp_send_chunk(req, html_footer, HTTPD_RESP_USE_STRLEN);

    // สัญญาณบอก HTTP Server ว่าส่งข้อมูลครบแล้ว
    httpd_resp_send_chunk(req, NULL, 0);
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
        httpd_register_uri_handler(server, &uri_get);
        ESP_LOGI(TAG, "Attendance Web Server Started at http://192.168.4.1");
    }
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        
        char mac_str[18];
        snprintf(mac_str, sizeof(mac_str), "%02X:%02X:%02X:%02X:%02X:%02X",
                 event->mac[0], event->mac[1], event->mac[2],
                 event->mac[3], event->mac[4], event->mac[5]);

        // เช็กป้องกันการบันทึก MAC ซ้ำ
        int existing_index = -1;
        for (int i = 0; i < s_student_count; i++) {
            if (strcmp(s_records[i].mac_str, mac_str) == 0) {
                existing_index = i;
                break;
            }
        }

        if (existing_index != -1) {
            s_records[existing_index].rssi = -45; // Simulated RSSI
            ESP_LOGI(TAG, "[PROXIMITY RE-DETECTED]: Device %s reconnected", mac_str);
        } else if (s_student_count < MAX_STUDENTS) {
            strncpy(s_records[s_student_count].mac_str, mac_str, sizeof(s_records[s_student_count].mac_str));
            s_records[s_student_count].rssi = -45; // Simulated RSSI
            s_records[s_student_count].checked_in = true;
            s_student_count++;
            ESP_LOGI(TAG, "[PROXIMITY DETECTED]: New student device connected: %s", mac_str);
        } else {
            ESP_LOGW(TAG, "Student limit reached! Cannot add %s", mac_str);
        }
    }
}

void app_main(void) {
    // Init NVS Flash
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

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
            .max_connection = MAX_STUDENTS,
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
}