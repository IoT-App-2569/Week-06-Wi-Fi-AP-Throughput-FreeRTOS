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
#include "esp_mac.h"
#include "esp_timer.h"

#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"

static const char *TAG = "SMART_ATTENDANCE";

#define AP_SSID "CLASSROOM_ATTENDANCE_AP"
#define AP_PASS "12345678"
#define RSSI_THRESHOLD (-60)
#define MAX_STUDENTS 5

typedef struct {
    char mac_str[18];
    int8_t rssi;
    bool checked_in;
    uint32_t timestamp_sec;
} student_record_t;

static student_record_t s_records[MAX_STUDENTS];
static int s_student_count = 0;

static int find_student_by_mac(const uint8_t mac[6])
{
    char mac_str[18];

    snprintf(mac_str, sizeof(mac_str),
             "%02X:%02X:%02X:%02X:%02X:%02X",
             mac[0], mac[1], mac[2],
             mac[3], mac[4], mac[5]);

    for (int i = 0; i < s_student_count; i++) {
        if (strcmp(s_records[i].mac_str, mac_str) == 0) {
            return i;
        }
    }

    return -1;
}

static esp_err_t http_attendance_html_handler(httpd_req_t *req)
{
    char resp[4096];

    int len = snprintf(
        resp, sizeof(resp),
        "<!DOCTYPE html><html><head>"
        "<meta charset='UTF-8'>"
        "<meta name='viewport' content='width=device-width,initial-scale=1'>"
        "<title>Smart Attendance</title>"
        "<style>"
        "body{font-family:Arial;text-align:center;background:#f4f4f9;padding:20px;color:#222}"
        ".card{background:white;padding:20px;border-radius:10px;max-width:850px;margin:auto}"
        "table{width:100%%;border-collapse:collapse;margin-top:15px}"
        "th,td{border:1px solid #ddd;padding:10px}"
        "th{background:#4CAF50;color:white}"
        ".btn{background:#2196F3;color:white;padding:12px 20px;border:0;border-radius:5px;cursor:pointer}"
        ".near{color:green;font-weight:bold}.far{color:red}"
        "</style></head><body><div class='card'>"
        "<h2>Smart Classroom Proximity Check-in</h2>"
        "<p>Wi-Fi Access Point: <b>PROXIMITY ACTIVE</b></p>"
        "<form action='/checkin' method='POST'>"
        "<button class='btn' type='submit'>Confirm Attendance</button>"
        "</form><h3>Connected Devices</h3>"
        "<p>Connected students: %d</p>"
        "<table><tr><th>Device MAC</th><th>RSSI (dBm)</th>"
        "<th>Proximity Status</th><th>Attendance</th></tr>",
        s_student_count
    );

    if (len < 0 || len >= (int)sizeof(resp)) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                            "Failed to generate dashboard");
        return ESP_FAIL;
    }

    for (int i = 0; i < s_student_count; i++) {
        const char *proximity =
            (s_records[i].rssi >= RSSI_THRESHOLD)
            ? "<span class='near'>NEAR (Valid)</span>"
            : "<span class='far'>FAR (Invalid)</span>";

        const char *attendance =
            s_records[i].checked_in ? "Checked in" : "Not checked in";

        int written = snprintf(
            resp + len, sizeof(resp) - len,
            "<tr><td>%s</td><td>%d</td><td>%s</td><td>%s</td></tr>",
            s_records[i].mac_str,
            (int)s_records[i].rssi,
            proximity,
            attendance
        );

        if (written < 0 || written >= (int)(sizeof(resp) - len)) {
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                                "Dashboard is too large");
            return ESP_FAIL;
        }

        len += written;
    }

    int written = snprintf(resp + len, sizeof(resp) - len,
                           "</table></div></body></html>");

    if (written < 0 || written >= (int)(sizeof(resp) - len)) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR,
                            "Dashboard is too large");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "text/html; charset=UTF-8");
    return httpd_resp_send(req, resp, len + written);
}

static esp_err_t http_checkin_handler(httpd_req_t *req)
{
    int checked_count = 0;

    for (int i = 0; i < s_student_count; i++) {
        if (s_records[i].rssi >= RSSI_THRESHOLD) {
            s_records[i].checked_in = true;
            s_records[i].timestamp_sec =
                (uint32_t)(esp_timer_get_time() / 1000000ULL);
            checked_count++;
        }
    }

    ESP_LOGI(TAG, "Attendance confirmation: %d device(s)", checked_count);

    httpd_resp_set_status(req, "303 See Other");
    httpd_resp_set_hdr(req, "Location", "/");
    return httpd_resp_send(req, NULL, 0);
}

static httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t root_uri = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = http_attendance_html_handler,
            .user_ctx = NULL
        };

        httpd_uri_t checkin_uri = {
            .uri = "/checkin",
            .method = HTTP_POST,
            .handler = http_checkin_handler,
            .user_ctx = NULL
        };

        ESP_ERROR_CHECK(httpd_register_uri_handler(server, &root_uri));
        ESP_ERROR_CHECK(httpd_register_uri_handler(server, &checkin_uri));

        ESP_LOGI(TAG, "HTTP server started");
    } else {
        ESP_LOGE(TAG, "Failed to start HTTP server");
    }

    return server;
}

static void wifi_event_handler(void *arg,
                               esp_event_base_t event_base,
                               int32_t event_id,
                               void *event_data)
{
    if (event_base == WIFI_EVENT &&
        event_id == WIFI_EVENT_AP_STACONNECTED) {

        wifi_event_ap_staconnected_t *event =
            (wifi_event_ap_staconnected_t *)event_data;

        int index = find_student_by_mac(event->mac);

        if (index < 0 && s_student_count < MAX_STUDENTS) {
            index = s_student_count++;
            snprintf(s_records[index].mac_str,
                     sizeof(s_records[index].mac_str),
                     "%02X:%02X:%02X:%02X:%02X:%02X",
                     event->mac[0], event->mac[1], event->mac[2],
                     event->mac[3], event->mac[4], event->mac[5]);

            s_records[index].rssi = -45; /* Placeholder; not actual RSSI */
            s_records[index].checked_in = false;
            s_records[index].timestamp_sec = 0;
        }

        ESP_LOGI(TAG, "Station connected; total records: %d",
                 s_student_count);

    } else if (event_base == WIFI_EVENT &&
               event_id == WIFI_EVENT_AP_STADISCONNECTED) {

        wifi_event_ap_stadisconnected_t *event =
            (wifi_event_ap_stadisconnected_t *)event_data;

        ESP_LOGI(TAG, "Station disconnected: %02X:%02X:%02X:%02X:%02X:%02X",
                 event->mac[0], event->mac[1], event->mac[2],
                 event->mac[3], event->mac[4], event->mac[5]);
    }
}

void app_main(void)
{
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
    if (ap_netif == NULL) {
        ESP_LOGE(TAG, "Failed to create Wi-Fi AP interface");
        return;
    }

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(
        WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));

    wifi_config_t wifi_config = {0};

    snprintf((char *)wifi_config.ap.ssid,
             sizeof(wifi_config.ap.ssid), "%s", AP_SSID);
    snprintf((char *)wifi_config.ap.password,
             sizeof(wifi_config.ap.password), "%s", AP_PASS);

    wifi_config.ap.ssid_len = strlen(AP_SSID);
    wifi_config.ap.channel = 1;
    wifi_config.ap.max_connection = MAX_STUDENTS;
    wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi AP started");
    ESP_LOGI(TAG, "SSID: %s", AP_SSID);
    ESP_LOGI(TAG, "Password: %s", AP_PASS);
    ESP_LOGI(TAG, "Open http://192.168.4.1");

    start_webserver();
}