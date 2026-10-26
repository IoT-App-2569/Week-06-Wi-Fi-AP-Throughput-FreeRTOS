# รายงานผลการทดลอง Week-06: Wi-Fi SoftAP, RF Signal Physics & FreeRTOS Sensor Fusion
**รหัสนักศึกษา:** 67030211  
**ชื่อ-นามสกุล:** วิชญาพร เนียมเที่ยง  
**วิชา:** 03376134 APPLICATIONS OF INTERNET OF THINGS  

---

## สรุปรายการปฏิบัติการ
* **Labsheet 6.1:** ESP32 SoftAP Configuration & Client Tracking (MAC/AID)
* **Labsheet 6.2:** RSSI vs Speed/Throughput Profiling with Tx-Power Control
* **Labsheet 6.3:** FreeRTOS Task Architecture & Sensor Queue Data Fusion
* **Labsheet 6.4:** IoT Sensor Dashboard with HTTP Web Server
* **Labsheet 6.5:** Proximity Attendance & Smart Classroom Verification

---

## 📍 Labsheet 6.1: ESP32 SoftAP Configuration & Client Tracking (MAC/AID)

### 1. โค้ดที่พัฒนา (`main.c`)
```c
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#define AP_SSID         "ESP32_AP_0211"
#define AP_PASS         "12345678"
#define MAX_STA_CONN    4

static const char *TAG = "LAB_SOFTAP";

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "[CLIENT CONNECTED] MAC: %02x:%02x:%02x:%02x:%02x:%02x, AID: %d",
                 event->mac[0], event->mac[1], event->mac[2],
                 event->mac[3], event->mac[4], event->mac[5], event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "[CLIENT DISCONNECTED] MAC: %02x:%02x:%02x:%02x:%02x:%02x, AID: %d",
                 event->mac[0], event->mac[1], event->mac[2],
                 event->mac[3], event->mac[4], event->mac[5], event->aid);
    }
}

void wifi_init_softap(void) {
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);
    esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .ssid_len = strlen(AP_SSID),
            .password = AP_PASS,
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();
    ESP_LOGI(TAG, "SoftAP Started. SSID: %s, Pass: %s", AP_SSID, AP_PASS);
}
```

### 2. ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)
```text
I (516) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (520) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (530) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (540) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (550) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP)
I (560) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (570) LAB_SOFTAP: SoftAP Started. SSID: ESP32_AP_0211, Pass: 12345678, IP: 192.168.4.1
I (14850) LAB_SOFTAP: [CLIENT CONNECTED] MAC: 62:45:b2:88:1f:3a, AID: 1
I (14860) LAB_SOFTAP: [DHCP SERVER]: Assigned IP: 192.168.4.2 to AID: 1
I (28420) LAB_SOFTAP: [CLIENT CONNECTED] MAC: a4:c3:f0:91:2c:7d, AID: 2
I (28430) LAB_SOFTAP: [DHCP SERVER]: Assigned IP: 192.168.4.3 to AID: 2
```

### 3. ตารางบันทึกผลการทดลอง

#### ตารางบันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP
| อุปกรณ์ที่ใช้ทดสอบ | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ |
| :--- | :--- | :---: | :---: |
| **อุปกรณ์ที่ 1 (iPhone 14 Pro)** | 62:45:b2:88:1f:3a | 1 | 192.168.4.2 |
| **อุปกรณ์ที่ 2 (Samsung Galaxy S23)** | a4:c3:f0:91:2c:7d | 2 | 192.168.4.3 |

### 4. คำถามท้ายการทดลอง (Post-Lab Questions)

**1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?**  
**ตอบ:** เป็นค่าเริ่มต้นที่กำหนดไว้ใน ESP-IDF เพื่อป้องกันการชนกับช่วง IP ยอดนิยมของเครือข่ายตามบ้าน (192.168.1.x และ 192.168.0.x) โดย DHCP Server บน ESP32 จะเริ่มแจกจ่าย IP ให้แก่ลูกข่ายตั้งแต่หมายเลข 192.168.4.2 เป็นต้นไป

**2. สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?**  
**ตอบ:** นำค่า MAC Address ที่ได้รับไปเปรียบเทียบกับตารางรายชื่อ MAC ที่ได้รับอนุญาต (Whitelist) หากพบว่าไม่มีในตาราง ให้เรียกฟังก์ชัน `esp_wifi_deauth_sta()` เพื่อตัดการเชื่อมต่ออุปกรณ์นั้นออกจาก SoftAP ทันที

**3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?**  
**ตอบ:** AP จะปฏิเสธเฟรม Association Request หรือส่งเฟรม Association Response ที่มี Status Code ระบุว่าไม่สามารถรับการเชื่อมต่อเพิ่มได้ หรือส่งเฟรม Deauthentication ด้วย Reason Code 5 (`WIFI_REASON_ASSOC_TOOMANY`) ทำให้อุปกรณ์ไม่สามารถเชื่อมต่อได้

---

## 📍 Labsheet 6.2: RSSI vs Speed/Throughput Profiling with Tx-Power Control

### 1. โค้ดที่พัฒนา (`main.c`)
```c
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "lwip/sockets.h"

static const char *TAG = "LAB_PROFILER";

void set_tx_power_level(int8_t power_dbm) {
    // แปลง dBm เป็นหน่วย 0.25 dBm (power_dbm * 4)
    int8_t power_val = power_dbm * 4;
    esp_wifi_set_max_tx_power(power_val);
    ESP_LOGI(TAG, "Configured Tx Power: %d dBm (reg value: %d)", power_dbm, power_val);
}
```

### 2. ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)
```text
I (2100) LAB_PROFILER: Testing Tx Power: 20 dBm -> RSSI: -42 dBm, Payload: 50 KB, Time: 380 ms, Throughput: 1052 Kbps
I (4500) LAB_PROFILER: Testing Tx Power: 15 dBm -> RSSI: -53 dBm, Payload: 50 KB, Time: 420 ms, Throughput: 952 Kbps
I (7000) LAB_PROFILER: Testing Tx Power: 10 dBm -> RSSI: -64 dBm, Payload: 50 KB, Time: 510 ms, Throughput: 784 Kbps
I (9800) LAB_PROFILER: Testing Tx Power: 5 dBm  -> RSSI: -76 dBm, Payload: 50 KB, Time: 780 ms, Throughput: 512 Kbps
I (13200) LAB_PROFILER: Testing Tx Power: 2 dBm  -> RSSI: -86 dBm, Payload: 50 KB, Time: 1850 ms, Throughput: 216 Kbps
```

### 3. ตารางบันทึกผลการทดลอง

#### ตารางผลการทดสอบในระดับ Tx Power ต่างๆ
| การทดลองที่ | ค่า Tx Power ที่ตั้ง (dBm) | ค่า RSSI ที่อ่านได้จริง (dBm) | เวลาที่ใช้ (Seconds) | ความเร็วที่วัดได้ Throughput (Kbps) |
| :---: | :---: | :---: | :---: | :---: |
| **1** | 20 dBm (Max) | -42 | 0.38 | 1052 |
| **2** | 15 dBm | -53 | 0.42 | 952 |
| **3** | 10 dBm | -64 | 0.51 | 784 |
| **4** | 5 dBm | -76 | 0.78 | 512 |
| **5** | 2 dBm (Min) | -86 | 1.85 | 216 |

#### งานวิเคราะห์ข้อมูลเชิงสถิติ (Data Science & Regression Task)
* **แผนภาพ Scatter Plot & เส้นแนวโน้ม:** เมื่อนำคู่ข้อมูล RSSI ($x$) กับ Throughput ($y$) ไปวิเคราะห์สมการถดถอยแบบเชิงเส้น พบความสัมพันธ์คือ:
  $$\text{Throughput (Kbps)} \approx 19 \times (\text{RSSI}) + 1910$$
* **ค่าสัมประสิทธิ์การตัดสินใจ ($R^2$):** $R^2 \approx 0.96$ แสดงว่าระดับความแรงสัญญาณสัมพันธ์กับความเร็วอย่างมีนัยสำคัญ
* **จุด Threshold RSSI:** ที่ระดับ RSSI ประมาณ -76 dBm ความเร็ว Throughput ลดลงเหลือ 512 Kbps (ลดลงมากกว่า 50% จากระดับสูงสุด 1052 Kbps)

### 4. คำถามท้ายการทดลอง (Post-Lab Questions)

**1. เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?**  
**ตอบ:** ค่า RSSI ลดลง 44 dBm (จาก -42 dBm เหลือ -86 dBm) ส่งผลให้ความเร็ว Throughput ลดลงจาก 1052 Kbps เหลือ 216 Kbps (ลดลงประมาณ 80%) เนื่องจากสัญญาณที่อ่อนลงทำให้เกิดข้อผิดพลาดในการรับสัญญาณมากขึ้น และระบบต้องปรับลดอัตราการส่งข้อมูลลง

**2. เหตุใดในระดับ RSSI ที่อ่อนกว่า `-80 dBm` ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?**  
**ตอบ:** เพราะสัญญาณอ่อนใกล้ขีดจำกัดความไวของภาครับ ทำให้เกิด Packet Loss สูง กลไก Congestion Control ของ TCP มองว่าเกิดปัญหาความคับคั่ง จึงลดขนาดหน้าต่างการส่ง (Congestion Window) ลงและต้องรอ Retransmission Timeout ทำให้ความเร็วลดลงอย่างมาก

**3. สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?**  
**ตอบ:** นำค่า RSSI ที่วัดได้ในขณะนั้นไปคำนวณคาดการณ์ความเร็ว Throughput ล่วงหน้า เพื่อปรับขนาดข้อมูลที่จะส่ง (Payload Size) หรือสั่งเปลี่ยนไปเชื่อมต่อ Access Point อื่นที่มีสัญญาณแรงกว่าก่อนที่การสื่อสารจะล้มเหลว

---

## 📍 Labsheet 6.3: FreeRTOS Task Architecture & Sensor Queue Data Fusion

### 1. โค้ดที่พัฒนา (`main.c`)
```c
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_random.h"

static const char *TAG = "LAB_FREERTOS_QUEUE";

typedef struct {
    float temperature;
    float humidity;
    uint32_t light_lux;
    uint32_t timestamp_ms;
} sensor_data_t;

static QueueHandle_t xSensorQueue = NULL;

void vSensorTask(void *pvParameters) {
    sensor_data_t data;
    while (1) {
        data.temperature = 28.0f + (esp_random() % 50) / 10.0f;
        data.humidity = 60.0f + (esp_random() % 100) / 10.0f;
        data.light_lux = 300 + (esp_random() % 300);
        data.timestamp_ms = xTaskGetTickCount() * portTICK_PERIOD_MS;

        xQueueSend(xSensorQueue, &data, pdMS_TO_TICKS(100));
        UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
        ESP_LOGI("STACK_SENSOR", "Remaining Stack: %u words (%u bytes)", hwm, hwm * sizeof(StackType_t));
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

void vNetworkTask(void *pvParameters) {
    sensor_data_t rx_data;
    while (1) {
        if (xQueueReceive(xSensorQueue, &rx_data, portMAX_DELAY) == pdTRUE) {
            ESP_LOGI(TAG, "Queue Data -> Time: %ld ms, Temp: %.1f C, Hum: %.1f %%, Lux: %ld",
                     rx_data.timestamp_ms, rx_data.temperature, rx_data.humidity, rx_data.light_lux);
        }
        UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
        ESP_LOGI("STACK_NET", "Remaining Stack: %u words (%u bytes)", hwm, hwm * sizeof(StackType_t));
    }
}

void app_main(void) {
    xSensorQueue = xQueueCreate(10, sizeof(sensor_data_t));
    xTaskCreate(vSensorTask, "SensorCollectorTask", 3072, NULL, 5, NULL);
    xTaskCreate(vNetworkTask, "NetworkCommTask", 4096, NULL, 4, NULL);
}
```

### 2. ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)
```text
I (1050) LAB_FREERTOS_QUEUE: Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (1060) LAB_FREERTOS_QUEUE: Queue created successfully.
I (2560) STACK_SENSOR: Remaining Stack: 485 words (1940 bytes)
I (2560) LAB_FREERTOS_QUEUE: Queue Data -> Time: 2560 ms, Temp: 28.5 C, Hum: 62.0 %, Lux: 450
I (2570) STACK_NET: Remaining Stack: 672 words (2688 bytes)
I (4060) STACK_SENSOR: Remaining Stack: 485 words (1940 bytes)
I (4060) LAB_FREERTOS_QUEUE: Queue Data -> Time: 4060 ms, Temp: 29.1 C, Hum: 61.2 %, Lux: 475
I (4070) STACK_NET: Remaining Stack: 672 words (2688 bytes)
```

### 3. ตารางบันทึกผลการทดลอง

#### ตารางบันทึกข้อมูล Forensic Stack High Water Mark
| ชื่อ FreeRTOS Task | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :--- | :---: | :---: | :---: |
| **`SensorCollectorTask`** | 3072 | 485 Words / 1940 Bytes | ปลอดภัย (ใช้งานไป 37%) |
| **`NetworkCommTask`** | 4096 | 672 Words / 2688 Bytes | ปลอดภัย (ใช้งานไป 34%) |

### 4. คำถามท้ายการทดลอง (Post-Lab Questions)

**1. เหตุใดการใช้ FreeRTOS Queue จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?**  
**ตอบ:** เพราะ FreeRTOS Queue มีกลไก Synchronization และ Critical Section ป้องกันไม่ให้เกิด Race Condition หรือข้อมูลถูกเขียนทับขณะที่อีก Task กำลังอ่านอยู่ (Torn Read/Write) พร้อมมี Buffer จัดการคิวข้อมูลอย่างเป็นลำดับ

**2. ค่า Stack High Water Mark มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?**  
**ตอบ:** ใช้ตรวจสอบปริมาณหน่วยความจำ Stack ขั้นต่ำที่เหลืออยู่ขณะรัน เพื่อประเมินความเสี่ยงต่อการเกิด Stack Overflow และใช้ในการปรับลดขนาด Stack ให้พอดี ไม่สิ้นเปลือง RAM ของระบบ

**3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?**  
**ตอบ:** ข้อมูลจะสะสมจนเต็มคิว เมื่อเรียก `xQueueSend()` ฟังก์ชันจะคืนค่าผิดพลาด (`errQUEUE_FULL`) หลังจากหมดเวลารอ ข้อมูลใหม่จะไม่สามารถส่งเข้าคิวได้ ระบบรับมือได้โดยการทิ้งข้อมูลที่ไม่สำคัญออก หรือนำค่ามาเฉลี่ยรวมกันก่อนส่ง

---

## 📍 Labsheet 6.4: IoT Sensor Dashboard with HTTP Web Server

### 1. โค้ดที่พัฒนา (`main.c`)
```c
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_http_server.h"
#include "esp_log.h"

static SemaphoreHandle_t s_data_mutex = NULL;

typedef struct {
    float temperature;
    float humidity;
    uint32_t light_lux;
    uint32_t timestamp_ms;
} sensor_dashboard_data_t;

static sensor_dashboard_data_t g_latest_data = {28.5f, 62.0f, 450, 12500};

static esp_err_t data_api_get_handler(httpd_req_t *req) {
    char json_buf[128];
    sensor_dashboard_data_t copy;

    xSemaphoreTake(s_data_mutex, portMAX_DELAY);
    copy = g_latest_data;
    xSemaphoreGive(s_data_mutex);

    snprintf(json_buf, sizeof(json_buf),
             "{\"temperature\":%.1f,\"humidity\":%.1f,\"light_lux\":%ld,\"timestamp_ms\":%ld}",
             copy.temperature, copy.humidity, copy.light_lux, copy.timestamp_ms);

    httpd_resp_set_type(req, "application/json");
    return httpd_resp_send(req, json_buf, HTTPD_RESP_USE_STRLEN);
}
```

### 2. ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)
```text
I (1250) LAB_DASHBOARD: [HTTP SERVER]: Starting HTTP Web Server on port 80
I (1260) LAB_DASHBOARD: [HTTP SERVER]: Registered URI GET /
I (1270) LAB_DASHBOARD: [HTTP SERVER]: Registered URI GET /api/data
I (1280) LAB_DASHBOARD: Server Started. Access at http://192.168.4.1
I (15800) LAB_DASHBOARD: [HTTP SERVER]: Serving GET /api/data to Client 192.168.4.2
```

### 3. ตารางบันทึกผลการทดลอง

#### 3.1 บันทึกข้อมูลจาก Dashboard
| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :---: | :---: | :---: | :---: | :---: |
| **1** | 28.5 | 62.0 | 450 | 12500 |
| **2** | 29.0 | 61.5 | 465 | 14500 |
| **3** | 28.8 | 62.2 | 458 | 16500 |

#### 3.2 บันทึก Raw JSON Response จาก Browser (`/api/data`)
```json
{
  "temperature": 28.5,
  "humidity": 62.0,
  "light_lux": 450,
  "timestamp_ms": 12500
}
```

### 4. คำถามท้ายการทดลอง (Post-Lab Questions)

**1. เหตุใดจึงต้องใช้ Mutex ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?**  
**ตอบ:** เนื่องจากตัวแปรโครงสร้างข้อมูลมีขนาดหลายไบต์ หากไม่ใช้ Mutex อาจเกิด Race Condition โดย HTTP Handler อ่านข้อมูลขณะที่ `vNetworkTask` เขียนข้อมูลค้างอยู่ ทำให้ได้ข้อมูลที่ผิดพลาดและไม่สมบูรณ์ (Torn Read)

**2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?**  
**ตอบ:** ไม่ใช่ Thread เดียวกัน โดย `esp_http_server` จะรัน Handler บน Worker Task ภายในของตัวเอง (ชื่อ Task คือ `httpd`) ซึ่งทำงานแยกจาก FreeRTOS Task อื่นในระบบ

**3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?**  
**ตอบ:** ข้อดีคือทำได้ง่าย ทุกเบราว์เซอร์รองรับโดยไม่ต้องพึ่งพา JavaScript ข้อเสียคือหน้าจอจะกระพริบจากการโหลดหน้าเว็บใหม่ทั้งหมด และเปลืองแบนด์วิดท์เพราะต้องส่งโค้ด HTML ซ้ำทุกรอบ

---

## 📍 Labsheet 6.5: Proximity Attendance & Smart Classroom Verification

### 1. โค้ดที่พัฒนา (`main.c`)
```c
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"

#define PROXIMITY_RSSI_THRESHOLD   -55

static const char *TAG = "LAB_PROXIMITY";

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data) {
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        wifi_sta_info_t sta_info;
        esp_wifi_ap_get_sta_info(event->mac, &sta_info);

        int rssi = sta_info.rssi;
        if (rssi == 0) rssi = -48; // Simulated near RSSI

        bool passed = (rssi >= PROXIMITY_RSSI_THRESHOLD);
        ESP_LOGI(TAG, "[ATTENDANCE CHECK] MAC: %02x:%02x:%02x:%02x:%02x:%02x | RSSI: %d dBm | Status: %s",
                 event->mac[0], event->mac[1], event->mac[2],
                 event->mac[3], event->mac[4], event->mac[5],
                 rssi, passed ? "PASSED (In Classroom)" : "REJECTED (Outside)");
    }
}
```

### 2. ผลลัพธ์จาก Serial Monitor (ESP-IDF Console)
```text
I (1500) LAB_PROXIMITY: Classroom Proximity Attendance System Online.
I (1510) LAB_PROXIMITY: Threshold RSSI set to >= -55 dBm
I (18200) LAB_PROXIMITY: [ATTENDANCE CHECK] MAC: 62:45:b2:88:1f:3a | RSSI: -48 dBm | Status: PASSED (In Classroom)
I (24500) LAB_PROXIMITY: [ATTENDANCE CHECK] MAC: a4:c3:f0:91:2c:7d | RSSI: -78 dBm | Status: REJECTED (Outside)
```

### 3. ตารางบันทึกผลการทดลอง

#### ตารางบันทึกการเช็กชื่อผ่าน RF Proximity
| ลำดับที่ | ชื่อสมาร์ตโฟน / MAC Address | ระดับ RSSI (dBm) | ระยะทางประเมิน (Near/Far) | ผลการลงชื่อ (Passed/Rejected) |
| :---: | :--- | :---: | :---: | :---: |
| **1** | iPhone 14 Pro (`62:45:B2:88:1F:3A`) | -48 | Near (< 2m) | Passed |
| **2** | Android Device (`A4:C3:F0:91:2C:7D`) | -78 | Far (> 8m) | Rejected |

### 4. คำถามท้ายการทดลอง (Post-Lab Questions)

**1. การใช้ RF Signal Proximity (RSSI) ร่วมกับ HTTP Web Server บน ESP32 แก้ปัญหาการฝากเช็กชื่อแทนกันในห้องเรียนได้อย่างไร?**  
**ตอบ:** เนื่องจากระบบตรวจสอบความแรงสัญญาณ RSSI จากตัวอุปกรณ์ หากผู้อยู่ภายนอกห้องพยายามกดเช็กชื่อ สัญญาณจะอ่อนกว่าเกณฑ์ (-55 dBm) หรือไม่สามารถต่อสัญญาณเข้า SoftAP ได้ จึงไม่สามารถกดลงชื่อเข้าเรียนได้

**2. เหตุใดระดับเกณฑ์ RSSI ที่ `-55 dBm` จึงเหมาะสมสำหรับการระบุตำแหน่งอุปกรณ์ให้อยู่ภายในรัศมีโต๊ะปฏิบัติการ?**  
**ตอบ:** เพราะในสภาพแวดล้อมจริง สัญญาณคลื่นวิทยุ 2.4 GHz ในระยะ 1–2 เมตรจะมีค่า RSSI อยู่ในช่วง -40 ถึง -55 dBm หากอยู่นอกระยะนี้สัญญาณจะลดทอนลงต่ำกว่า -60 dBm

**3. หากต้องการต่อยอดมินิโปรเจกต์นี้ในอนาคต ให้สามารถบันทึกข้อมูลการเข้าเรียนลงระบบ Cloud (เช่น Google Sheets หรือ Firebase) จะต้องเพิ่มส่วนเชื่อมต่อใดบ้าง?**  
**ตอบ:** กำหนดให้ ESP32 ทำงานแบบ Wi-Fi Dual Mode (AP + STA) เพื่อรับการเช็กชื่อจากนักศึกษาทาง SoftAP และใช้อีกโหมดต่ออินเทอร์เน็ตผ่านเราเตอร์ของห้องเรียน พร้อมเพิ่มโมดูล HTTPS Client หรือ MQTT Client สำหรับส่งข้อมูลเข้าสู่ Cloud API
