# ใบงานที่ 6.4: IoT Sensor Dashboard — แสดงผลค่าเซนเซอร์แบบ Real-Time ผ่าน Web Browser บนมือถือ

```
--- 0x40080400: _invalid_pc_placeholder at C:/Users/09677/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug 10 2026 20:25:59
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (34) boot.esp32: SPI Speed      : 40MHz
I (38) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (45) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (52) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (65) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (78) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1cc08h (117768) map
I (129) esp_image: segment 1: paddr=0002cc30 vaddr=3ffb0000 size=033e8h ( 13288) load
I (134) esp_image: segment 2: paddr=00030020 vaddr=400d0020 size=8ecdch (584924) map
I (334) esp_image: segment 3: paddr=000bed04 vaddr=3ffb33e8 size=00b04h (  2820) load
I (335) esp_image: segment 4: paddr=000bf810 vaddr=40080000 size=17fc4h ( 98244) load
I (376) esp_image: segment 5: paddr=000d77dc vaddr=50000000 size=00020h (    32) load
I (388) boot: Loaded app from partition at offset 0x10000
I (388) boot: Disabling RNG early entropy source...
I (399) cpu_start: Multicore app
I (407) cpu_start: Pro cpu start user code
I (407) cpu_start: cpu freq: 160000000 Hz
I (407) app_init: Application information:
I (407) app_init: Project name:     iot_sensor_dashboard
I (412) app_init: App version:      029da6d-dirty
I (417) app_init: Compile time:     Aug 10 2026 20:24:47
I (422) app_init: ELF file SHA256:  88652b8af...
I (426) app_init: ESP-IDF:          v5.5.1-dirty
I (430) efuse_init: Min chip rev:     v0.0
I (434) efuse_init: Max chip rev:     v3.99 
I (438) efuse_init: Chip rev:         v3.1
I (442) heap_init: Initializing. RAM available for dynamic allocation:
I (448) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (453) heap_init: At 3FFB7FE8 len 00028018 (160 KiB): DRAM
I (459) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (464) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (470) heap_init: At 40097FC4 len 0000803C (32 KiB): IRAM
W (476) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (488) spi_flash: detected chip: generic
I (491) spi_flash: flash io: dio
W (494) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (508) main_task: Started on CPU0
I (518) main_task: Calling app_main()
I (518) MAIN: [FORENSIC]: Call nvs_flash_init()
I (558) MAIN: =======================================================
I (558) MAIN:   Lab 6-4: IoT Sensor Dashboard
I (558) MAIN:   SoftAP + FreeRTOS Queue + HTTP Server
I (558) MAIN: =======================================================
I (568) MAIN: [FORENSIC]: Call xSemaphoreCreateMutex()
I (568) MAIN: [FORENSIC]: Mutex created at 0x3ffbb7cc
I (578) MAIN: [FORENSIC]: Call xQueueCreate(10, sizeof(sensor_data_t))
I (578) MAIN: [FORENSIC]: Queue created at 0x3ffbb824
I (588) SOFTAP: [FORENSIC]: Call esp_netif_init()
I (598) SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (598) SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (608) SOFTAP: [FORENSIC]: SoftAP netif created at 0x3ffbdac4 (IP: 192.168.4.1)
I (608) SOFTAP: [FORENSIC]: Call esp_wifi_init()
I (628) wifi:wifi driver task: 3ffc0204, prio:23, stack:6656, core=0
I (648) wifi:wifi firmware version: 14da9b7
I (648) wifi:wifi certification version: v7.0
I (648) wifi:config NVS flash: enabled
I (648) wifi:config nano formatting: disabled
I (648) wifi:Init data frame dynamic rx buffer num: 32
I (658) wifi:Init static rx mgmt buffer num: 5
I (658) wifi:Init management short buffer num: 32
I (658) wifi:Init dynamic tx buffer num: 32
I (668) wifi:Init static rx buffer size: 1600
I (668) wifi:Init static rx buffer num: 10
I (678) wifi:Init dynamic rx buffer num: 32
I (678) wifi_init: rx ba win: 6
I (678) wifi_init: accept mbox: 6
I (688) wifi_init: tcpip mbox: 32
I (688) wifi_init: udp mbox: 6
I (688) wifi_init: tcp mbox: 6
I (688) wifi_init: tcp tx win: 5760
I (698) wifi_init: tcp rx win: 5760
I (698) wifi_init: tcp mss: 1440
I (698) wifi_init: WiFi IRAM OP enabled
I (708) wifi_init: WiFi RX IRAM OP enabled
I (708) SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (718) SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (718) SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP)
I (998) SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (998) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (1078) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (1108) wifi:mode : softAP (88:57:21:ad:64:99)
I (1108) wifi:Total power save buffer number: 16
I (1108) wifi:Init max length of beacon: 752/752
I (1108) wifi:Init max length of beacon: 752/752
I (1118) SOFTAP: =======================================================
I (1118) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1128) SOFTAP:   SoftAP Running! SSID: "MY_ESP32_SENSOR_AP", Channel: 1
I (1138) SOFTAP:   -> Connect your phone to: MY_ESP32_SENSOR_AP
I (1138) SOFTAP:   -> Then open browser:      http://192.168.4.1
I (1148) SOFTAP: =======================================================
I (1148) HTTP_SERVER: [FORENSIC]: Call httpd_start()
I (1158) HTTP_SERVER: =======================================================
I (1158) HTTP_SERVER: [HTTP SERVER]: Started successfully
I (1168) HTTP_SERVER:   -> Dashboard : http://192.168.4.1/
I (1178) HTTP_SERVER:   -> JSON API  : http://192.168.4.1/api/data
I (1178) HTTP_SERVER: =======================================================
I (1188) MAIN: [FORENSIC]: Call xTaskCreate(vSensorTask)  Stack=3072
I (1188) SENSOR_TASK: [FORENSIC]: Sensor Collector Task started on Core 0
I (1198) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 26.5 C, Hum: 51.3 %, Lux: 256
I (1208) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (1218) MAIN: [FORENSIC]: Call xTaskCreate(vNetworkTask) Stack=4096
I (1218) NETWORK_TASK: [FORENSIC]: Network Task started on Core 0
I (1228) NETWORK_TASK: =======================================================
I (1228) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (1238) NETWORK_TASK:   -> Timestamp   : 690 ms
I (1238) NETWORK_TASK:   -> Temperature : 26.50 degC
I (1248) NETWORK_TASK:   -> Humidity    : 51.30 %
I (1248) NETWORK_TASK:   -> Light Lux   : 256 lux
I (1258) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (1258) NETWORK_TASK: =======================================================
I (1268) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (1278) MAIN: =======================================================
I (1278) MAIN:   System Ready! Open browser at http://192.168.4.1
I (1288) MAIN: =======================================================
I (1298) main_task: Returned from app_main()
I (2718) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 34.4 C, Hum: 50.9 %, Lux: 546
I (2718) NETWORK_TASK: =======================================================
I (2718) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (2718) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (2728) NETWORK_TASK:   -> Timestamp   : 2210 ms
I (2738) NETWORK_TASK:   -> Temperature : 34.40 degC
I (2738) NETWORK_TASK:   -> Humidity    : 50.90 %
I (2748) NETWORK_TASK:   -> Light Lux   : 546 lux
I (2748) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (2758) NETWORK_TASK: =======================================================
I (2758) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (4228) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 27.3 C, Hum: 58.3 %, Lux: 453
I (4228) NETWORK_TASK: =======================================================
I (4228) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (4228) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (4238) NETWORK_TASK:   -> Timestamp   : 3720 ms
I (4248) NETWORK_TASK:   -> Temperature : 27.30 degC
I (4248) NETWORK_TASK:   -> Humidity    : 58.30 %
I (4258) NETWORK_TASK:   -> Light Lux   : 453 lux
I (4258) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (4268) NETWORK_TASK: =======================================================
I (4268) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (5738) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 25.6 C, Hum: 65.8 %, Lux: 559
I (5738) NETWORK_TASK: =======================================================
I (5738) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (5738) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (5748) NETWORK_TASK:   -> Timestamp   : 5230 ms
I (5758) NETWORK_TASK:   -> Temperature : 25.60 degC
I (5758) NETWORK_TASK:   -> Humidity    : 65.80 %
I (5768) NETWORK_TASK:   -> Light Lux   : 559 lux
I (5768) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (5778) NETWORK_TASK: =======================================================
I (5778) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (7248) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 28.5 C, Hum: 62.7 %, Lux: 614
I (7248) NETWORK_TASK: =======================================================
I (7248) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (7248) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (7258) NETWORK_TASK:   -> Timestamp   : 6740 ms
I (7268) NETWORK_TASK:   -> Temperature : 28.50 degC
I (7268) NETWORK_TASK:   -> Humidity    : 62.70 %
I (7278) NETWORK_TASK:   -> Light Lux   : 614 lux
I (7278) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (7288) NETWORK_TASK: =======================================================
I (7288) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (8758) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 31.2 C, Hum: 59.2 %, Lux: 529
I (8758) NETWORK_TASK: =======================================================
I (8758) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (8758) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (8768) NETWORK_TASK:   -> Timestamp   : 8250 ms
I (8778) NETWORK_TASK:   -> Temperature : 31.20 degC
I (8778) NETWORK_TASK:   -> Humidity    : 59.20 %
I (8788) NETWORK_TASK:   -> Light Lux   : 529 lux
I (8788) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (8798) NETWORK_TASK: =======================================================
I (8798) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (10268) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 33.9 C, Hum: 60.1 %, Lux: 631
I (10268) NETWORK_TASK: =======================================================
I (10268) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (10268) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (10278) NETWORK_TASK:   -> Timestamp   : 9760 ms
I (10288) NETWORK_TASK:   -> Temperature : 33.90 degC
I (10288) NETWORK_TASK:   -> Humidity    : 60.10 %
I (10298) NETWORK_TASK:   -> Light Lux   : 631 lux
I (10298) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (10308) NETWORK_TASK: =======================================================
I (10308) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (11778) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 32.9 C, Hum: 59.7 %, Lux: 255
I (11778) NETWORK_TASK: =======================================================
I (11778) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (11778) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (11788) NETWORK_TASK:   -> Timestamp   : 11270 ms
I (11798) NETWORK_TASK:   -> Temperature : 32.90 degC
I (11798) NETWORK_TASK:   -> Humidity    : 59.70 %
I (11808) NETWORK_TASK:   -> Light Lux   : 255 lux
I (11808) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (11818) NETWORK_TASK: =======================================================
I (11818) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
I (13288) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 31.7 C, Hum: 61.5 %, Lux: 617
I (13288) NETWORK_TASK: =======================================================
I (13288) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1192 words (1192 bytes)
I (13288) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (13298) NETWORK_TASK:   -> Timestamp   : 12780 ms
I (13308) NETWORK_TASK:   -> Temperature : 31.70 degC
I (13308) NETWORK_TASK:   -> Humidity    : 61.50 %
I (13318) NETWORK_TASK:   -> Light Lux   : 617 lux
I (13318) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (13328) NETWORK_TASK: =======================================================
I (13328) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2212 words (2212 bytes)
```



### 7.1 บันทึกข้อมูลจาก Dashboard

| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :------: | :--------------: | :----------: | :-------: | :------------: |
|  **1**   |      28.60       |    55.30     |    367    |    1074020     |
|  **2**   |      34.90       |    50.70     |    257    |    1075530     |
|  **3**   |      25.10       |    60.80     |    494    |    1077040     |

### 7.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response จาก Browser:

![[Pasted image 20260810214647.png]]

---

## 8. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
		- **เหตุผล:** ป้องกันไม่ให้ `vNetworkTask` (ฝั่งเขียน) และ `HTTP Handler` (ฝั่งอ่าน) เข้าถึงตัวแปร `g_latest_data` พร้อมกัน
	    - **ถ้าไม่ใช้:** เกิด **Data Race** ทำให้ข้อมูลแสดงผลขัดแย้ง/ผิดพลาด หรือเกิด **Crash (Guru Meditation Error)** จากการอ่าน-เขียนหน่วยความจำที่ไม่สมบูรณ์พร้อมกัน
2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?
		- - ไม่ใช่ Thread เดียวกัน
        - **รายละเอียด:** `esp_http_server` รันบน FreeRTOS Task แยกเฉพาะของระบบ (ชื่อ `httpd`) ซึ่งทำงานขนานกับ `vNetworkTask` ของเรา
3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
		- **`<meta refresh>`:** โค้ดง่าย ไม่ต้องเขียน JS แต่ **ข้อเสียคือหน้าเว็บกระพริบ** และเปลืองทรัพยากรเพราะต้องโหลด HTML ใหม่ทั้งหน้าทุกรอบ
		- **`fetch()`:** หน้าเว็บลื่นไหล ไม่กระพริบ ประหยัดเน็ตเพราะดึงแค่ JSON แต่ **ข้อเสียคือโค้ดซับซ้อนขึ้น** ต้องเขียน JS ฝั่ง Client เพิ่ม
