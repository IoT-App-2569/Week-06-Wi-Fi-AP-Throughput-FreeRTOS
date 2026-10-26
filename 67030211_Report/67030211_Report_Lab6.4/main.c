#include <stdio.h>
#include "esp_http_server.h"
void app_main(void) {
    httpd_handle_t s = NULL;
    httpd_config_t c = HTTPD_DEFAULT_CONFIG();
    httpd_start(&s, &c);
    printf("HTTP Dashboard server running on port 80\n");
}
