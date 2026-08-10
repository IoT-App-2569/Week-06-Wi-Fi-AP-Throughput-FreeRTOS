#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"

#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"

static const char *TAG = "SMART_ATTENDANCE";

#define AP_SSID        "CLASSROOM_ATTENDANCE_AP_0207"
#define AP_PASS        "12345678"
#define RSSI_THRESHOLD -60
#define MAX_STUDENTS   5

typedef struct {
    char mac_str[18];
    int8_t rssi;
    bool checked_in;
    uint32_t timestamp_sec;
} student_record_t;

static student_record_t s_records[MAX_STUDENTS];
static int s_student_count = 0;


/* =========================================================
 * ค้นหา MAC Address ว่ามีอยู่ในรายการแล้วหรือไม่
 * ========================================================= */
static int find_student_by_mac(const uint8_t *mac)
{
    char mac_str[18];

    snprintf(
        mac_str,
        sizeof(mac_str),
        "%02X:%02X:%02X:%02X:%02X:%02X",
        mac[0], mac[1], mac[2],
        mac[3], mac[4], mac[5]
    );

    for (int i = 0; i < s_student_count; i++) {
        if (strcmp(s_records[i].mac_str, mac_str) == 0) {
            return i;
        }
    }

    return -1;
}


/* =========================================================
 * อ่านข้อมูล Station ที่เชื่อมต่อกับ SoftAP
 * ========================================================= */
static void update_station_rssi(void)
{
    wifi_sta_list_t sta_list;

    memset(&sta_list, 0, sizeof(sta_list));

    esp_err_t err = esp_wifi_ap_get_sta_list(&sta_list);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Cannot get station list: %s",
                 esp_err_to_name(err));
        return;
    }

    for (int i = 0; i < sta_list.num; i++) {

        int index = find_student_by_mac(sta_list.sta[i].mac);

        if (index >= 0) {
            s_records[index].rssi = sta_list.sta[i].rssi;

            ESP_LOGI(
                TAG,
                "Student %s RSSI = %d dBm",
                s_records[index].mac_str,
                s_records[index].rssi
            );
        }
    }
}


/* =========================================================
 * Web Server
 * ========================================================= */
static esp_err_t http_attendance_html_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "text/html");

    httpd_resp_sendstr_chunk(
        req,
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta charset='UTF-8'>"
        "<meta name='viewport' content='width=device-width,initial-scale=1'>"
        "<title>Smart Classroom Attendance</title>"

        "<style>"
        "body{"
        "font-family:Arial;"
        "text-align:center;"
        "background:#f4f4f9;"
        "padding:20px;"
        "}"

        ".card{"
        "background:white;"
        "padding:20px;"
        "border-radius:10px;"
        "box-shadow:0 2px 5px rgba(0,0,0,0.2);"
        "max-width:800px;"
        "margin:auto;"
        "}"

        "table{"
        "width:100%;"
        "border-collapse:collapse;"
        "margin-top:15px;"
        "}"

        "th,td{"
        "border:1px solid #ddd;"
        "padding:8px;"
        "text-align:center;"
        "}"

        "th{"
        "background:#4CAF50;"
        "color:white;"
        "}"

        ".near{color:green;font-weight:bold;}"
        ".far{color:red;font-weight:bold;}"
        "</style>"

        "</head>"
        "<body>"

        "<div class='card'>"

        "<h1>Smart Classroom</h1>"
        "<h2>Proximity Check-in</h2>"

        "<p><b>Connect Status:</b> PROXIMITY ACTIVE</p>"
        "<p><b>Confirm Attendance:</b> 1-Click</p>"

        "<h3>Active Connected Devices</h3>"

        "<table>"
        "<tr>"
        "<th>Device MAC</th>"
        "<th>RSSI</th>"
        "<th>Proximity Status</th>"
        "</tr>"
    );

    update_station_rssi();

    for (int i = 0; i < s_student_count; i++) {

        if (s_records[i].rssi >= RSSI_THRESHOLD) {

            httpd_resp_sendstr_chunk(
                req,
                "<tr>"
                "<td>"
            );

            httpd_resp_sendstr_chunk(
                req,
                s_records[i].mac_str
            );

            httpd_resp_sendstr_chunk(
                req,
                "</td>"
                "<td>"
            );

            char rssi_str[32];

            snprintf(
                rssi_str,
                sizeof(rssi_str),
                "%d dBm",
                s_records[i].rssi
            );

            httpd_resp_sendstr_chunk(req, rssi_str);

            httpd_resp_sendstr_chunk(
                req,
                "</td>"
                "<td class='near'>"
                "NEAR (Valid)"
                "</td>"
                "</tr>"
            );

        } else {

            httpd_resp_sendstr_chunk(
                req,
                "<tr>"
                "<td>"
            );

            httpd_resp_sendstr_chunk(
                req,
                s_records[i].mac_str
            );

            httpd_resp_sendstr_chunk(
                req,
                "</td>"
                "<td>"
            );

            char rssi_str[32];

            snprintf(
                rssi_str,
                sizeof(rssi_str),
                "%d dBm",
                s_records[i].rssi
            );

            httpd_resp_sendstr_chunk(req, rssi_str);

            httpd_resp_sendstr_chunk(
                req,
                "</td>"
                "<td class='far'>"
                "FAR (Invalid)"
                "</td>"
                "</tr>"
            );
        }
    }

    httpd_resp_sendstr_chunk(
        req,
        "</table>"
        "</div>"
        "</body>"
        "</html>"
    );

    httpd_resp_sendstr_chunk(req, NULL);

    return ESP_OK;
}


/* =========================================================
 * Start Web Server
 * ========================================================= */
static void start_web_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    httpd_handle_t server = NULL;

    esp_err_t err = httpd_start(&server, &config);

    if (err == ESP_OK) {

        httpd_uri_t uri_get = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = http_attendance_html_handler,
            .user_ctx = NULL
        };

        httpd_register_uri_handler(server, &uri_get);

        ESP_LOGI(
            TAG,
            "Attendance Web Server Started"
        );

        ESP_LOGI(
            TAG,
            "Open http://192.168.4.1"
        );
    }
}


/* =========================================================
 * WiFi Event Handler
 * ========================================================= */
static void wifi_event_handler(
    void *arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data)
{
    /* =============================================
     * มีอุปกรณ์เชื่อมต่อ
     * ============================================= */
    if (event_base == WIFI_EVENT &&
        event_id == WIFI_EVENT_AP_STACONNECTED) {

        wifi_event_ap_staconnected_t *event =
            (wifi_event_ap_staconnected_t *)event_data;

        if (find_student_by_mac(event->mac) >= 0) {

            ESP_LOGI(
                TAG,
                "Existing student device connected"
            );

            return;
        }

        if (s_student_count < MAX_STUDENTS) {

            snprintf(
                s_records[s_student_count].mac_str,
                sizeof(s_records[s_student_count].mac_str),
                "%02X:%02X:%02X:%02X:%02X:%02X",
                event->mac[0],
                event->mac[1],
                event->mac[2],
                event->mac[3],
                event->mac[4],
                event->mac[5]
            );

            /*
             * ค่าเริ่มต้น
             * RSSI จริงจะถูกอัปเดตโดย update_station_rssi()
             */
            s_records[s_student_count].rssi = -100;

            s_records[s_student_count].checked_in = false;

            s_student_count++;

            ESP_LOGI(
                TAG,
                "[PROXIMITY DETECTED] New student device connected!"
            );
        }
        else {

            ESP_LOGW(
                TAG,
                "Maximum student limit reached!"
            );
        }
    }


    /* =============================================
     * มีอุปกรณ์ Disconnect
     * ============================================= */
    else if (
        event_base == WIFI_EVENT &&
        event_id == WIFI_EVENT_AP_STADISCONNECTED
    ) {

        wifi_event_ap_stadisconnected_t *event =
            (wifi_event_ap_stadisconnected_t *)event_data;

        int index = find_student_by_mac(event->mac);

        if (index >= 0) {

            ESP_LOGI(
                TAG,
                "Student %s disconnected",
                s_records[index].mac_str
            );

            /*
             * ลบรายการโดยเลื่อนข้อมูลตัวถัดไปขึ้นมา
             */
            for (int i = index; i < s_student_count - 1; i++) {

                s_records[i] = s_records[i + 1];
            }

            s_student_count--;
        }
    }
}


/* =========================================================
 * app_main
 * ========================================================= */
void app_main(void)
{
    esp_err_t ret;

    /* Initialize NVS */
    ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {

        ESP_ERROR_CHECK(nvs_flash_erase());

        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);


    /* Initialize TCP/IP */
    ESP_ERROR_CHECK(
        esp_netif_init()
    );


    /* Create Event Loop */
    ESP_ERROR_CHECK(
        esp_event_loop_create_default()
    );


    /* Create WiFi AP */
    esp_netif_create_default_wifi_ap();


    /* Initialize WiFi */
    wifi_init_config_t cfg =
        WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(
        esp_wifi_init(&cfg)
    );


    /* Register WiFi Event Handler */
    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(
            WIFI_EVENT,
            ESP_EVENT_ANY_ID,
            &wifi_event_handler,
            NULL,
            NULL
        )
    );


    /* WiFi AP Configuration */
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .ssid_len = strlen(AP_SSID),
            .password = AP_PASS,
            .max_connection = MAX_STUDENTS,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };


    /* Set AP Mode */
    ESP_ERROR_CHECK(
        esp_wifi_set_mode(WIFI_MODE_AP)
    );


    /* Set AP Configuration */
    ESP_ERROR_CHECK(
        esp_wifi_set_config(
            WIFI_IF_AP,
            &wifi_config
        )
    );


    /* Start WiFi */
    ESP_ERROR_CHECK(
        esp_wifi_start()
    );


    ESP_LOGI(
        TAG,
        "WiFi AP Started"
    );

    ESP_LOGI(
        TAG,
        "SSID: %s",
        AP_SSID
    );

    ESP_LOGI(
        TAG,
        "IP Address: 192.168.4.1"
    );


    /* Start Web Server */
    start_web_server();
}