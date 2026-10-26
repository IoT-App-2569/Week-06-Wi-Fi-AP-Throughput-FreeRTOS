#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

typedef struct { int id; int raw; float v; } sensor_data_t;
static QueueHandle_t s_q = NULL;

void task_prod(void* pv) {
    sensor_data_t d = { .id = 1, .raw = 2048, .v = 1.65f };
    while (1) { xQueueSend(s_q, &d, portMAX_DELAY); vTaskDelay(pdMS_TO_TICKS(500)); }
}
void task_cons(void* pv) {
    sensor_data_t rx;
    while (1) { if (xQueueReceive(s_q, &rx, portMAX_DELAY)) printf("[Queue] Raw: %d, Voltage: %.2fV\n", rx.raw, rx.v); }
}
void app_main(void) {
    s_q = xQueueCreate(10, sizeof(sensor_data_t));
    xTaskCreate(task_prod, "p", 2048, NULL, 5, NULL);
    xTaskCreate(task_cons, "c", 2048, NULL, 5, NULL);
}
