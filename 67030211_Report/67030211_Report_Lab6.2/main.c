#include <stdio.h>
#include "esp_wifi.h"
void app_main(void) {
    esp_wifi_set_max_tx_power(78); // 19.5 dBm
    printf("Tx Power adjusted. Running RSSI vs Speed profiling...\n");
}
