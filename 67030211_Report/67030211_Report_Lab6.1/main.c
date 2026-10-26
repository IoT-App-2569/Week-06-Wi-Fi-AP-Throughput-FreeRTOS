#include <stdio.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

static void wifi_event_handler(void* arg, esp_event_base_t base, int32_t id, void* data) {
    if (id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* e = (wifi_event_ap_staconnected_t*) data;
        printf("[SoftAP] Station joined: MAC=%02x:%02x:%02x:%02x:%02x:%02x AID=%d\n",
               e->mac[0], e->mac[1], e->mac[2], e->mac[3], e->mac[4], e->mac[5], e->aid);
    }
}

void app_main(void) {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);
    wifi_config_t conf = {
        .ap = { .ssid = "ESP32_IoT_Gateway", .password = "securepass123", .max_connection = 4, .authmode = WIFI_AUTH_WPA2_PSK }
    };
    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &conf);
    esp_wifi_start();
    printf("SoftAP Started: SSID=ESP32_IoT_Gateway IP=192.168.4.1\n");
}
