#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

typedef struct {
    int sensor_id;
    int raw_value;
    float voltage;
} sensor_data_t;

static QueueHandle_t s_sensor_queue = NULL;

void task_producer(void *pv) {
    sensor_data_t data;
    int count = 0;
    while (1) {
        data.sensor_id = 1;
        data.raw_value = 2048 + (count % 100);
        data.voltage = (data.raw_value / 4095.0f) * 3.3f;
        xQueueSend(s_sensor_queue, &data, portMAX_DELAY);
        count++;
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void task_consumer(void *pv) {
    sensor_data_t rx;
    while (1) {
        if (xQueueReceive(s_sensor_queue, &rx, portMAX_DELAY)) {
            printf("[Consumer] Sensor #%d -> Raw=%d, Voltage=%.2fV\n", rx.sensor_id, rx.raw_value, rx.voltage);
        }
    }
}

void app_main(void) {
    s_sensor_queue = xQueueCreate(10, sizeof(sensor_data_t));
    xTaskCreate(task_producer, "prod", 2048, NULL, 5, NULL);
    xTaskCreate(task_consumer, "cons", 2048, NULL, 5, NULL);
}
