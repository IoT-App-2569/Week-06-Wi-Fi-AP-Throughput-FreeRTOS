# ใบงานที่ 6.3: การออกแบบ FreeRTOS Task Architecture & Sensor Data Fusion ผ่าน Queue

## 0. กล่าวนำ (Introduction)
ในแอปพลิเคชัน IoT ระดับอุตสาหกรรม โปรแกรมเมอร์จะไม่เขียนโค้ดอ่านค่าเซนเซอร์และการรับส่งข้อมูล Wi-Fi รวมไว้ในฟังก์ชันเดียวกัน เพราะจะทำให้สแตกระบบเครือข่ายชะงัก (Network Latency & Blocking) 

ในใบงานนี้นักศึกษาจะได้ออกแบบสถาปัตยกรรม **FreeRTOS Multi-Tasking** โดยแยกโปรแกรมออกเป็น **Sensor Collector Task** และ **Network Communication Task** แล้วใช้ **FreeRTOS Queue** เป็นสะพานเชื่อมส่งผ่านโครงสร้างข้อมูล `sensor_data_t` อย่างปลอดภัย (Thread-Safe) พร้อมทั้งใช้คำสั่ง Forensic ตรวจวัดหน่วยความจำสแตก `uxTaskGetStackHighWaterMark()`

---

## 1. วัตถุประสงค์ (Objectives)
1. สามารถสร้างและบริหารจัดการ FreeRTOS Tasks บน ESP-IDF ด้วยฟังก์ชัน `xTaskCreate()` ได้
2. สามารถสร้างและใช้งาน FreeRTOS Queue (`xQueueCreate`, `xQueueSend`, `xQueueReceive`) ในการส่งผ่านข้อมูลได้
3. ป้องกันปัญหาการบล็อกระบบเครือข่าย Wi-Fi โดยการแยกงานอ่านเซนเซอร์ออกจาก Network Loop
4. ประเมินการใช้หน่วยความจำสแตกของแต่ละ Task ในสไตล์ Forensic ด้วย `uxTaskGetStackHighWaterMark()`

---

## 2. อุปกรณ์และซอฟต์แวร์ที่ใช้ในการทดลอง (Equipment & Tools)
1. บอร์ดไมโครคอนโทรลเลอร์ ESP32 จำนวน 1 บอร์ด
2. สายเชื่อมต่อ Micro-USB หรือ USB-C จำนวน 1 เส้น
3. โปรแกรม IDE เช่น VS Code พร้อม ESP-IDF Toolchain

---

## 3. สถาปัตยกรรมระบบ (System Architecture & Sequence)

```mermaid
sequenceDiagram
    autonumber
    participant Sens as Sensor Collector Task
    participant Queue as FreeRTOS Queue (sensor_queue)
    participant Net as Network Task
    participant Mon as Forensic Stack Monitor

    loop ทุกๆ 1 วินาที
        Sens->>Sens: อ่านค่าเซนเซอร์ (Temp, Hum, Motion)
        Sens->>Queue: xQueueSend(&sensor_data, 100ms)
    end

    loop เมื่อมีข้อมูลใน Queue
        Queue->>Net: xQueueReceive(&received_data, portMAX_DELAY)
        Net->>Net: ประมวลผลแพ็กเกจ Wi-Fi / ส่งออก TCP JSON
    end

    Mon->>Sens: uxTaskGetStackHighWaterMark()
    Mon->>Net: uxTaskGetStackHighWaterMark()
```

---

## 4. ขั้นตอนการทดลอง (Experimental Procedures)

1. นำซอร์สโค้ดในข้อ 5 ไปวางในไฟล์ `main/main.c` ทำการ Build และ Flash ลงบอร์ด ESP32
2. สังเกต Forensic Log ใน Serial Monitor:
   - ตรวจดูข้อมูลที่ถูกส่งจาก `vSensorTask` เข้าสู่ Queue และถูกรับโดย `vNetworkTask`
   - ตรวจดูค่า **Stack High Water Mark** (ขนาดสแตกคงเหลือ) ของแต่ละ Task
3. ทดลองปรับขนาดสแตกของ `vSensorTask` ใน `xTaskCreate()` จาก `4096` ลดลงเหลือ `1024` สังเกตค่า High Water Mark และวิเคราะห์จุดเสี่ยง Stack Overflow

---

## 5. ซอร์สโค้ดการทดลอง (Complete ESP-IDF Source Code - `main.c`)

```c
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_random.h"

static const char *TAG = "LAB_FREERTOS_QUEUE";

// Sensor Data Structure
typedef struct {
    float temperature;
    float humidity;
    uint32_t light_lux;
    uint32_t timestamp_ms;
} sensor_data_t;

// Queue Handle
static QueueHandle_t xSensorQueue = NULL;

// ------------------------------------------------------------------
// Task 1: Sensor Collector Task (Simulates Reading Hardware Sensors)
// ------------------------------------------------------------------
void vSensorTask(void *pvParameters) {
    sensor_data_t data;
    ESP_LOGI(TAG, "[TASK CREATED]: Sensor Collector Task Started on Core %d", xPortGetCoreID());

    while (1) {
        // 1. Simulate reading sensors
        data.temperature = 25.0f + (esp_random() % 100) / 10.0f;
        data.humidity = 50.0f + (esp_random() % 200) / 10.0f;
        data.light_lux = 200 + (esp_random() % 500);
        data.timestamp_ms = xTaskGetTickCount() * portTICK_PERIOD_MS;

        ESP_LOGI(TAG, "[SENSOR TASK]: Pushing Data -> Temp: %.1f C, Hum: %.1f %%, Lux: %ld",
                 data.temperature, data.humidity, data.light_lux);

        // 2. Send data structure to FreeRTOS Queue
        if (xQueueSend(xSensorQueue, &data, pdMS_TO_TICKS(100)) != pdPASS) {
            ESP_LOGW(TAG, "[QUEUE WARNING]: Queue Full! Failed to push sensor data.");
        }

        // 3. Stack High Water Mark Check
        UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
        ESP_LOGI("FORENSIC_STACK", "  -> SensorTask Stack Remaining: %u words (%u bytes)",
                 hwm, hwm * sizeof(StackType_t));

        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

// ------------------------------------------------------------------
// Task 2: Network Task (Consumes Data from Queue for Wi-Fi Transmission)
// ------------------------------------------------------------------
void vNetworkTask(void *pvParameters) {
    sensor_data_t rx_data;
    ESP_LOGI(TAG, "[TASK CREATED]: Network Task Started on Core %d", xPortGetCoreID());

    while (1) {
        // Wait indefinitely for data from Queue
        if (xQueueReceive(xSensorQueue, &rx_data, portMAX_DELAY) == pdTRUE) {
            ESP_LOGI(TAG, "=======================================================");
            ESP_LOGI(TAG, "[NETWORK TASK]: Data Received from Queue!");
            ESP_LOGI(TAG, "  -> Timestamp   : %ld ms", rx_data.timestamp_ms);
            ESP_LOGI(TAG, "  -> Temperature : %.2f degC", rx_data.temperature);
            ESP_LOGI(TAG, "  -> Humidity    : %.2f %%", rx_data.humidity);
            ESP_LOGI(TAG, "  -> Light Lux   : %ld lux", rx_data.light_lux);
            ESP_LOGI(TAG, "[NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...");
            ESP_LOGI(TAG, "=======================================================");
        }

        UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
        ESP_LOGI("FORENSIC_STACK", "  -> NetworkTask Stack Remaining: %u words (%u bytes)",
                 hwm, hwm * sizeof(StackType_t));
    }
}

void app_main(void) {
    ESP_LOGI(TAG, "==================================================================");
    ESP_LOGI(TAG, "  Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion");
    ESP_LOGI(TAG, "==================================================================");

    // Create FreeRTOS Queue for 10 items of sensor_data_t
    xSensorQueue = xQueueCreate(10, sizeof(sensor_data_t));
    if (xSensorQueue == NULL) {
        ESP_LOGE(TAG, "Failed to create FreeRTOS Queue!");
        return;
    }

    // Create Tasks
    xTaskCreate(vSensorTask, "SensorCollectorTask", 3072, NULL, 5, NULL);
    xTaskCreate(vNetworkTask, "NetworkCommTask", 4096, NULL, 4, NULL);
}
```

---

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :--- | :---: | :---: | :---: |
| **`SensorCollectorTask`** | 3072 |2020 | ปลอดภัย เหลือ 34.24% |
| **`NetworkCommTask`** | 4096 |3072 | ปลอดภัย เหลือ 25%|

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
```
Queue มีกลไก mutual exclusion ในตัวอยู่แล้ว ทำให้การอ่าน เขียนข้อมูลระหว่าง 2 Task เกิดขึ้นแบบอะตอมิก ไม่มีทาง race condition หรือข้อมูลถูกเขียนทับกลางคัน ต่างจาก Global Variable ที่ถ้า Task หนึ่งกำลังเขียนอยู่แล้วอีก Task แย่ง context switch เข้ามาอ่านพร้อมกัน จะได้ข้อมูลครึ่งเก่าครึ่งใหม่ นอกจาก Queue ยังมี buffer รองรับให้ Task ที่ผลิตข้อมูลเร็วกว่าไม่ต้องรอ Task ที่บริโภคช้ากว่าทันที
```
2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
```
ใช้เป็นตัวชี้วัดว่า Task นั้นเคยใช้ Stack ไปมากที่สุดกี่ byte ตลอดการทำงาน ถ้าค่าที่เหลือ ใกล้ 0 หรือติดลบ = สัญญาณเตือนล่วงหน้าของ Stack Overflow ซึ่งเป็นสาเหตุคลาสสิกของอาการค้างหรือ รีเซ็ตแบบสุ่มใน RTOS ที่ debug ยากมากถ้าไม่มีค่านี้ จึงใช้ปรับขนาด Stack ให้พอดี ไม่มากเกินจนเปลือง RAM ไม่น้อยเกินจนเต็ม
```
3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
```
Queue จะเริ่มเต็ม เพราะ Sensor Task สร้างข้อมูลเร็วกว่า Network Task ใช้มากเมื่อ Queue เต็ม พฤติกรรมขึ้นกับการเรียกใช้ xQueueSend()
ถ้าตั้ง timeout ไว้  Sensor Task จะ block รอจนกว่าจะมีที่ว่าง ทำให้ Sensor Task ทำงานช้าลงตาม Network Task ไปด้วย ถ้าไม่รอ ข้อมูลที่ส่งไม่ทันจะสูญหาย ไม่ถูกเก็บ

วิธีเเก้คือเพิ่มขนาด Queue ให้รองรับ burst ได้ระดับหนึ่ง ใช้ overwrite ค่าล่าสุด ถ้าสนใจแค่ค่าปัจจุบัน ไม่สนใจค่าเก่าหรือปรับให้ Network Task ทำงานเร็วขึ้น ลดความถี่การส่งของ Sensor Task ลงให้สมดุลกัน
```

### Log 
```
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15848
load:0x40080400,len:3920
--- 0x40080400: _invalid_pc_placeholder at /Users/ittikorntongsima/My-Library/esp-idf/components/xtensa/xtensa_vectors.S:2259
entry 0x40080644
--- 0x40080644: call_start_cpu0 at /Users/ittikorntongsima/My-Library/esp-idf/components/bootloader/subproject/main/bootloader_start.c:27
I (27) boot: ESP-IDF v6.1-dev-3480-g44c77cbf46 2nd stage bootloader
I (27) boot: compile time Aug 23 2026 22:47:51
I (28) boot: Multicore bootloader
I (30) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (40) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (57) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (80) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=08b58h ( 35672) map
I (101) esp_image: segment 1: paddr=00018b80 vaddr=3ffb0000 size=02a7ch ( 10876) load
I (105) esp_image: segment 2: paddr=0001b604 vaddr=40080000 size=04a14h ( 18964) load
I (113) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=0c770h ( 51056) map
I (131) esp_image: segment 4: paddr=0002c798 vaddr=40084a14 size=062a4h ( 25252) load
I (142) esp_image: segment 5: paddr=00032a44 vaddr=50000000 size=00028h (    40) load
I (148) boot: Loaded app from partition at offset 0x10000
I (148) boot: Disabling RNG early entropy source...
I (160) cpu_start: Multicore app
I (168) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (169) cpu_start: Pro cpu start user code
I (169) cpu_start: cpu freq: 160000000 Hz
I (170) app_init: Application information:
I (174) app_init: Project name:     lab3
I (178) app_init: App version:      1
I (181) app_init: Compile time:     Aug 23 2026 22:47:43
I (186) app_init: ELF file SHA256:  a91c577e7...
I (191) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
I (196) efuse_init: Min chip rev:     v0.0
I (200) efuse_init: Max chip rev:     v3.99
I (204) efuse_init: Chip rev:         v3.1
I (208) heap_init: Initializing. RAM available for dynamic allocation:
I (214) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (219) heap_init: At 3FFB3430 len 0002CBD0 (178 KiB): DRAM
I (224) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (230) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (235) heap_init: At 4008ACB8 len 00015348 (84 KiB): IRAM
I (242) spi_flash: detected chip: generic
I (244) spi_flash: flash io: dio
W (247) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (261) main_task: Started on CPU0
I (271) main_task: Calling app_main()
I (271) LAB_FREERTOS_QUEUE: ==================================================================
I (271) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (281) LAB_FREERTOS_QUEUE: ==================================================================
I (281) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 0
I (291) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.2 C, Hum: 61.6 %, Lux: 546
I (301) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (311) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (311) LAB_FREERTOS_QUEUE: =======================================================
I (321) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (331) LAB_FREERTOS_QUEUE:   -> Timestamp   : 30 ms
I (331) LAB_FREERTOS_QUEUE:   -> Temperature : 29.20 degC
I (341) LAB_FREERTOS_QUEUE:   -> Humidity    : 61.60 %
I (341) LAB_FREERTOS_QUEUE:   -> Light Lux   : 546 lux
I (351) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (361) LAB_FREERTOS_QUEUE: =======================================================
I (361) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)
I (371) main_task: Returned from app_main()
I (1811) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 30.5 C, Hum: 52.7 %, Lux: 347
I (1811) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (1811) LAB_FREERTOS_QUEUE: =======================================================
I (1821) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (1821) LAB_FREERTOS_QUEUE:   -> Timestamp   : 1550 ms
I (1831) LAB_FREERTOS_QUEUE:   -> Temperature : 30.50 degC
I (1831) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.70 %
I (1841) LAB_FREERTOS_QUEUE:   -> Light Lux   : 347 lux
I (1841) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (1851) LAB_FREERTOS_QUEUE: =======================================================
I (1861) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)
I (3311) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.2 C, Hum: 61.7 %, Lux: 419
I (3311) LAB_FREERTOS_QUEUE: =======================================================
I (3311) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (3311) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (3321) LAB_FREERTOS_QUEUE:   -> Timestamp   : 3050 ms
I (3331) LAB_FREERTOS_QUEUE:   -> Temperature : 26.20 degC
I (3331) LAB_FREERTOS_QUEUE:   -> Humidity    : 61.70 %
I (3341) LAB_FREERTOS_QUEUE:   -> Light Lux   : 419 lux
I (3341) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (3351) LAB_FREERTOS_QUEUE: =======================================================
I (3361) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)
I (4821) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.1 C, Hum: 64.2 %, Lux: 531
I (4821) LAB_FREERTOS_QUEUE: =======================================================
I (4821) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (4821) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (4831) LAB_FREERTOS_QUEUE:   -> Timestamp   : 4560 ms
I (4841) LAB_FREERTOS_QUEUE:   -> Temperature : 28.10 degC
I (4841) LAB_FREERTOS_QUEUE:   -> Humidity    : 64.20 %
I (4851) LAB_FREERTOS_QUEUE:   -> Light Lux   : 531 lux
I (4851) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (4861) LAB_FREERTOS_QUEUE: =======================================================
I (4871) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)

Done
ittikorntongsima@Sloth lab3 %
```
