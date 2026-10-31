### report6.4

คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
        เหตุผลที่ต้องใช้: ตัวแปร g_latest_data เป็นตัวแปรส่วนกลาง (Global Variable) ที่ถูกใช้งานจากสองเธรด/ทาสก์ที่ทำงานแบบ并发 (Concurrent) พร้อมกัน คือ vNetworkTask (ทำหน้าที่อัปเดตข้อมูล) และ HTTP Handler (ทำหน้าที่อ่านข้อมูลส่งให้ไคลเอนต์) การใช้ Mutex (Mutual Exclusion) จะช่วยล็อกการเข้าถึง ทำให้มั่นใจได้ว่าจะมีเพียงกระบวนการเดียวเท่านั้นที่เข้าถึงหรือแก้ไขข้อมูลได้ในแต่ละช่วงเวลา
        หากไม่ใช้จะเกิดอะไรขึ้น: จะเกิดปัญหา Race Condition และ Data Corruption กล่าวคือ หาก HTTP Handler เข้ามาอ่านข้อมูลในจังหวะที่ vNetworkTask กำลังเขียนข้อมูลลงไปพอดี (เช่น ข้อมูลโครงสร้างหลายไบต์) HTTP Handler อาจได้ข้อมูลครึ่งเก่าครึ่งใหม่ที่ไม่สมบูรณ์ ส่งผลให้ค่าที่แสดงผลผิดเพี้ยน, ข้อมูลเสียหาย หรือในกรณีที่รุนแรงอาจทำให้ระบบเกิดอาการ Guru Meditation Error (Crash) ได้

2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?
        ไม่ใช่ Thread เดียวกันครับ esp_http_server จะสร้างและจัดการ FreeRTOS Task ของตัวมันเองขึ้นมาต่างหาก (เรียกว่า HTTP Server Worker Tasks) เพื่อรอรับและประมวลผลคำขอ (HTTP Requests) ที่เข้ามาจากเบราว์เซอร์

3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
        ข้อดี: เขียนโค้ดง่ายมาก ใช้เพียงแท็ก HTML บรรทัดเดียวโดยไม่ต้องเขียนโปรแกรมฝั่ง JavaScript เพิ่มเติม
        ทำงานได้แม้เบราว์เซอร์จะปิดการใช้งาน JavaScript (JS disabled)
        ข้อเสีย:เกิดการรีโหลดหน้าเว็บใหม่ทั้งหมด (Full Page Reload) ทุก ๆ 2 วินาที ทำให้หน้าจอเกิดอาการกระพริบ (Flicker)
        สูญเสียสถานะหน้าเว็บ เช่น ตำแหน่งการเลื่อนหน้าจอ (Scroll Position) หรือฟอร์มที่กำลังกรอก


I (31) boot: ESP-IDF v5.1.2-dirty 2nd stage bootloader
I (31) boot: compile time Oct 25 2026 17:36:59
I (31) boot: Multicore bootloader
I (36) boot: chip revision: v3.1
I (40) boot.esp32: SPI Speed      : 40MHz
I (44) boot.esp32: SPI Mode       : DIO
I (49) boot.esp32: SPI Flash Size : 2MB
I (53) boot: Enabling RNG early entropy source...
I (59) boot: Partition Table:
I (62) boot: ## Label            Usage          Type ST Offset   Length
I (70) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (77) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (85) boot:  2 factory          factory app      00 00 00010000 00100000
I (92) boot: End of partition table
I (96) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=22f9ch (143260) map
I (157) esp_image: segment 1: paddr=00032fc4 vaddr=3ffb0000 size=03a7ch ( 14972) load
I (163) esp_image: segment 2: paddr=00036a48 vaddr=40080000 size=095d0h ( 38352) load
I (179) esp_image: segment 3: paddr=00040020 vaddr=400d0020 size=8a2d0h (565968) map
I (383) esp_image: segment 4: paddr=000ca2f8 vaddr=400895d0 size=0c6a4h ( 50852) load
I (416) boot: Loaded app from partition at offset 0x10000
I (416) boot: Disabling RNG early entropy source...
I (427) cpu_start: Multicore app
I (428) cpu_start: Pro cpu up.
I (428) cpu_start: Starting app cpu, entry point is 0x40081390
--- 0x40081390: call_start_cpu1 at /Users/kittikarnkaewnual/esp/esp-idf/components/esp_system/port/cpu_start.c:157
I (0) cpu_start: App cpu up.
I (446) cpu_start: Pro cpu start user code
I (446) cpu_start: cpu freq: 160000000 Hz
I (446) cpu_start: Application information:
I (450) cpu_start: Project name:     iot_sensor_dashboard
I (457) cpu_start: App version:      029da6d
I (461) cpu_start: Compile time:     Oct 25 2026 17:36:51
I (468) cpu_start: ELF file SHA256:  154f2d9dcb6a1d4a...
I (474) cpu_start: ESP-IDF:          v5.1.2-dirty
I (479) cpu_start: Min chip rev:     v0.0
I (484) cpu_start: Max chip rev:     v3.99 
I (488) cpu_start: Chip rev:         v3.1
I (493) heap_init: Initializing. RAM available for dynamic allocation:
I (501) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (506) heap_init: At 3FFB7B28 len 000284D8 (161 KiB): DRAM
I (513) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (519) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (525) heap_init: At 40095C74 len 0000A38C (40 KiB): IRAM
I (533) spi_flash: detected chip: generic
I (536) spi_flash: flash io: dio
W (540) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (554) app_start: Starting scheduler on CPU0
I (558) app_start: Starting scheduler on CPU1
I (558) main_task: Started on CPU0
I (568) main_task: Calling app_main()
I (568) MAIN: [FORENSIC]: Call nvs_flash_init()
I (608) MAIN: =======================================================
I (618) MAIN:   Lab 6-4: IoT Sensor Dashboard
I (618) MAIN:   SoftAP + FreeRTOS Queue + HTTP Server
I (618) MAIN: =======================================================
I (628) MAIN: [FORENSIC]: Call xSemaphoreCreateMutex()
I (628) MAIN: [FORENSIC]: Mutex created at 0x3ffbb3dc
I (638) MAIN: [FORENSIC]: Call xQueueCreate(10, sizeof(sensor_data_t))
I (648) MAIN: [FORENSIC]: Queue created at 0x3ffbb434
I (648) SOFTAP: [FORENSIC]: Call esp_netif_init()
I (658) SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (668) SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (668) SOFTAP: [FORENSIC]: SoftAP netif created at 0x3ffbd6f8 (IP: 192.168.4.1)
I (678) SOFTAP: [FORENSIC]: Call esp_wifi_init()
I (698) wifi:wifi driver task: 3ffbfd98, prio:23, stack:6656, core=0
I (718) wifi:wifi firmware version: 91b9630
I (718) wifi:wifi certification version: v7.0
I (718) wifi:config NVS flash: enabled
I (718) wifi:config nano formating: disabled
I (728) wifi:Init data frame dynamic rx buffer num: 32
I (728) wifi:Init static rx mgmt buffer num: 5
I (728) wifi:Init management short buffer num: 32
I (738) wifi:Init dynamic tx buffer num: 32
I (738) wifi:Init static rx buffer size: 1600
I (748) wifi:Init static rx buffer num: 10
I (748) wifi:Init dynamic rx buffer num: 32
I (758) wifi_init: rx ba win: 6
I (758) wifi_init: tcpip mbox: 32
I (758) wifi_init: udp mbox: 6
I (768) wifi_init: tcp mbox: 6
I (768) wifi_init: tcp tx win: 5744
I (768) wifi_init: tcp rx win: 5744
I (778) wifi_init: tcp mss: 1440
I (778) wifi_init: WiFi IRAM OP enabled
I (788) wifi_init: WiFi RX IRAM OP enabled
I (788) SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (798) SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (808) SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP)
I (818) SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (818) phy_init: phy_version 4780,16b31a7,Sep 22 2023,20:42:16
I (898) wifi:mode : softAP (84:1f:e8:39:b4:49)
I (908) wifi:Total power save buffer number: 16
I (908) wifi:Init max length of beacon: 752/752
I (908) wifi:Init max length of beacon: 752/752
I (908) SOFTAP: =======================================================
I (908) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (928) SOFTAP:   SoftAP Running! SSID: "MY_ESP32_SENSOR_AP", Channel: 1
I (928) SOFTAP:   -> Connect your phone to: MY_ESP32_SENSOR_AP
I (938) SOFTAP:   -> Then open browser:      http://192.168.4.1
I (948) SOFTAP: =======================================================
I (948) HTTP_SERVER: [FORENSIC]: Call httpd_start()
I (958) HTTP_SERVER: =======================================================
I (968) HTTP_SERVER: [HTTP SERVER]: Started successfully
I (968) HTTP_SERVER:   -> Dashboard : http://192.168.4.1/
I (978) HTTP_SERVER:   -> JSON API  : http://192.168.4.1/api/data
I (988) HTTP_SERVER: =======================================================
I (988) MAIN: [FORENSIC]: Call xTaskCreate(vSensorTask)  Stack=3072
I (998) SENSOR_TASK: [FORENSIC]: Sensor Collector Task started on Core 0
I (1008) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 34.8 C, Hum: 58.9 %, Lux: 664
I (1018) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (1028) MAIN: [FORENSIC]: Call xTaskCreate(vNetworkTask) Stack=4096
I (1028) NETWORK_TASK: [FORENSIC]: Network Task started on Core 0
I (1038) NETWORK_TASK: =======================================================
I (1048) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (1048) NETWORK_TASK:   -> Timestamp   : 450 ms
I (1058) NETWORK_TASK:   -> Temperature : 34.80 degC
I (1058) NETWORK_TASK:   -> Humidity    : 58.90 %
I (1068) NETWORK_TASK:   -> Light Lux   : 664 lux
I (1078) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (1078) NETWORK_TASK: =======================================================
I (1088) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (1098) MAIN: =======================================================
I (1108) MAIN:   System Ready! Open browser at http://192.168.4.1
I (1108) MAIN: =======================================================
I (1118) main_task: Returned from app_main()
I (2528) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 30.8 C, Hum: 65.4 %, Lux: 695
I (2528) NETWORK_TASK: =======================================================
I (2528) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (2528) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (2548) NETWORK_TASK:   -> Timestamp   : 1970 ms
I (2548) NETWORK_TASK:   -> Temperature : 30.80 degC
I (2558) NETWORK_TASK:   -> Humidity    : 65.40 %
I (2558) NETWORK_TASK:   -> Light Lux   : 695 lux
I (2568) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (2568) NETWORK_TASK: =======================================================
I (2578) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (4038) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 26.3 C, Hum: 66.5 %, Lux: 271
I (4038) NETWORK_TASK: =======================================================
I (4038) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (4038) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (4058) NETWORK_TASK:   -> Timestamp   : 3480 ms
I (4058) NETWORK_TASK:   -> Temperature : 26.30 degC
I (4068) NETWORK_TASK:   -> Humidity    : 66.50 %
I (4068) NETWORK_TASK:   -> Light Lux   : 271 lux
I (4078) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (4078) NETWORK_TASK: =======================================================
I (4088) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (5548) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 31.5 C, Hum: 53.3 %, Lux: 267
I (5548) NETWORK_TASK: =======================================================
I (5548) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (5548) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (5568) NETWORK_TASK:   -> Timestamp   : 4990 ms
I (5568) NETWORK_TASK:   -> Temperature : 31.50 degC
I (5578) NETWORK_TASK:   -> Humidity    : 53.30 %
I (5578) NETWORK_TASK:   -> Light Lux   : 267 lux
I (5588) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (5588) NETWORK_TASK: =======================================================
I (5598) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (7058) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 32.5 C, Hum: 62.7 %, Lux: 557
I (7058) NETWORK_TASK: =======================================================
I (7058) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (7058) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (7078) NETWORK_TASK:   -> Timestamp   : 6500 ms
I (7078) NETWORK_TASK:   -> Temperature : 32.50 degC
I (7088) NETWORK_TASK:   -> Humidity    : 62.70 %
I (7088) NETWORK_TASK:   -> Light Lux   : 557 lux
I (7098) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (7108) NETWORK_TASK: =======================================================
I (7108) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (8568) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 33.8 C, Hum: 66.7 %, Lux: 537
I (8568) NETWORK_TASK: =======================================================
I (8568) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (8568) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (8588) NETWORK_TASK:   -> Timestamp   : 8010 ms
I (8588) NETWORK_TASK:   -> Temperature : 33.80 degC
I (8598) NETWORK_TASK:   -> Humidity    : 66.70 %
I (8598) NETWORK_TASK:   -> Light Lux   : 537 lux
I (8608) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (8608) NETWORK_TASK: =======================================================
I (8618) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (10078) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 27.3 C, Hum: 66.2 %, Lux: 266
I (10078) NETWORK_TASK: =======================================================
I (10078) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (10078) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (10098) NETWORK_TASK:   -> Timestamp   : 9520 ms
I (10098) NETWORK_TASK:   -> Temperature : 27.30 degC
I (10108) NETWORK_TASK:   -> Humidity    : 66.20 %
I (10108) NETWORK_TASK:   -> Light Lux   : 266 lux
I (10118) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (10128) NETWORK_TASK: =======================================================
I (10128) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (11588) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 34.0 C, Hum: 61.7 %, Lux: 559
I (11588) NETWORK_TASK: =======================================================
I (11588) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (11588) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (11608) NETWORK_TASK:   -> Timestamp   : 11030 ms
I (11608) NETWORK_TASK:   -> Temperature : 34.00 degC
I (11618) NETWORK_TASK:   -> Humidity    : 61.70 %
I (11618) NETWORK_TASK:   -> Light Lux   : 559 lux
I (11628) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (11638) NETWORK_TASK: =======================================================
I (11638) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (13098) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 30.5 C, Hum: 62.6 %, Lux: 402
I (13098) NETWORK_TASK: =======================================================
I (13098) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (13098) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (13118) NETWORK_TASK:   -> Timestamp   : 12540 ms
I (13118) NETWORK_TASK:   -> Temperature : 30.50 degC
I (13128) NETWORK_TASK:   -> Humidity    : 62.60 %
I (13128) NETWORK_TASK:   -> Light Lux   : 402 lux
I (13138) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (13148) NETWORK_TASK: =======================================================
I (13148) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
I (14608) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 33.3 C, Hum: 63.9 %, Lux: 557
I (14608) NETWORK_TASK: =======================================================
I (14608) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1252 words (1252 bytes)
I (14608) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (14628) NETWORK_TASK:   -> Timestamp   : 14050 ms
I (14628) NETWORK_TASK:   -> Temperature : 33.30 degC
I (14638) NETWORK_TASK:   -> Humidity    : 63.90 %
I (14638) NETWORK_TASK:   -> Light Lux   : 557 lux
I (14648) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (14658) NETWORK_TASK: =======================================================
I (14658) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2288 words (2288 bytes)
