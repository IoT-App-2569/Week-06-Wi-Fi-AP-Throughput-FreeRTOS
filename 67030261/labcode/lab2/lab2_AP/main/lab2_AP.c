#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "lwip/sockets.h"

static const char *TAG = "LAB_SOFTAP";

#define AP_SSID           "MY_ESP32_AP"
#define AP_PASS           "12345678"
#define AP_CHANNEL        1
#define AP_MAX_CONNECTION 4
#define SERVER_PORT       8080
#define RECV_BUF_LEN      1024

// แก้ค่านี้ก่อนคอมไพล์ในแต่ละรอบทดลอง (ใบงาน 6.2 ข้อ 3-7):
// 80 = 20dBm, 60 = 15dBm, 40 = 10dBm, 20 = 5dBm, 8 = 2dBm
#define AP_TX_POWER       8

static int s_session_count = 0;

static void wifi_event_handler(void *arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t *event = event_data;

        ESP_LOGI(TAG, "=======================================================");
        ESP_LOGI(TAG, "[FORENSIC EVENT]: Client Connected to ESP32 SoftAP!");
        ESP_LOGI(TAG, "  -> Client MAC Address : %02X:%02X:%02X:%02X:%02X:%02X",
                 event->mac[0], event->mac[1], event->mac[2],
                 event->mac[3], event->mac[4], event->mac[5]);
        ESP_LOGI(TAG, "  -> Assigned AID       : %d", event->aid);
        ESP_LOGI(TAG, "=======================================================");
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t *event = event_data;

        ESP_LOGW(TAG, "[FORENSIC EVENT]: Client Disconnected, AID=%d", event->aid);
    }
}

static void wifi_init_softap(void)
{
    ESP_LOGI(TAG, "[FORENSIC]: Call esp_netif_init()");
    ESP_ERROR_CHECK(esp_netif_init());

    ESP_LOGI(TAG, "[FORENSIC]: Call esp_event_loop_create_default()");
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_LOGI(TAG, "[FORENSIC]: Call esp_netif_create_default_wifi_ap()");
    esp_netif_t *ap_netif = esp_netif_create_default_wifi_ap();
    ESP_ERROR_CHECK(ap_netif == NULL ? ESP_FAIL : ESP_OK);
    ESP_LOGI(TAG, "[FORENSIC]: SoftAP Interface created at %p (Default IP: 192.168.4.1)",
             ap_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_init(&cfg)");
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_LOGI(TAG, "[FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)");
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                         ESP_EVENT_ANY_ID,
                                                         &wifi_event_handler,
                                                         NULL,
                                                         NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .ssid_len = strlen(AP_SSID),
            .password = AP_PASS,
            .channel = AP_CHANNEL,
            .max_connection = AP_MAX_CONNECTION,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

    ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)");
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));

    ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_start()");
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "[FORENSIC]: Call esp_wifi_set_max_tx_power(%d)", AP_TX_POWER);
    ESP_ERROR_CHECK(esp_wifi_set_max_tx_power(AP_TX_POWER));

    ESP_LOGI(TAG, "==================================================================");
    ESP_LOGI(TAG, "  ESP32 SoftAP Running! SSID: \"%s\", Channel: %d", AP_SSID, AP_CHANNEL);
    ESP_LOGI(TAG, "==================================================================");
}

static void handle_client_session(int client_socket, struct sockaddr_in *client_addr)
{
    s_session_count++;

    char client_ip[INET_ADDRSTRLEN];
    inet_ntoa_r(client_addr->sin_addr, client_ip, sizeof(client_ip));

    ESP_LOGI(TAG, "=======================================================");
    ESP_LOGI(TAG, "[TCP SERVER SESSION %d]: Client connected from %s:%d",
             s_session_count, client_ip, ntohs(client_addr->sin_port));

    char rx_buffer[RECV_BUF_LEN];
    int total_received = 0;
    int received;

    while ((received = recv(client_socket, rx_buffer, sizeof(rx_buffer), 0)) > 0) {
        total_received += received;
    }

    ESP_LOGI(TAG, "[TCP SERVER SESSION %d]: Transfer complete", s_session_count);
    ESP_LOGI(TAG, "  -> Total Received : %d Bytes", total_received);
    ESP_LOGI(TAG, "=======================================================");

    shutdown(client_socket, SHUT_RDWR);
    close(client_socket);
}

static void tcp_server_task(void *arg)
{
    int listen_socket = (int)(intptr_t)arg;

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        int client_socket = accept(listen_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0) {
            ESP_LOGE(TAG, "accept() failed, errno=%d", errno);
            continue;
        }

        handle_client_session(client_socket, &client_addr);
    }
}

static void start_tcp_server(void)
{
    int listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (listen_socket < 0) {
        ESP_LOGE(TAG, "Unable to create socket, errno=%d", errno);
        return;
    }

    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = htonl(INADDR_ANY),
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
    };

    if (bind(listen_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
        ESP_LOGE(TAG, "bind() failed, errno=%d", errno);
        close(listen_socket);
        return;
    }

    if (listen(listen_socket, 1) != 0) {
        ESP_LOGE(TAG, "listen() failed, errno=%d", errno);
        close(listen_socket);
        return;
    }

    ESP_LOGI(TAG, "[TCP SERVER]: Listening on 192.168.4.1:%d", SERVER_PORT);

    xTaskCreate(tcp_server_task, "tcp_server_task", 4096, (void *)(intptr_t)listen_socket, 5, NULL);
}

void app_main(void)
{
    ESP_LOGI(TAG, "[FORENSIC]: Call nvs_flash_init()");
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    wifi_init_softap();
    start_tcp_server();
}
