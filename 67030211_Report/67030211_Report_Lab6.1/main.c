#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"

void app_main(void) {
    nvs_flash_init(); esp_netif_init(); esp_event_loop_create_default();
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    wifi_config_t conf = { .ap = { .ssid = "ESP32_IoT_Gateway", .password = "securepass123", .max_connection = 4 } };
    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &conf);
    esp_wifi_start();
    printf("SoftAP Started: SSID=ESP32_IoT_Gateway IP=192.168.4.1\n");
}
