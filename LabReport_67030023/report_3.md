### report6.3

คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
        ความปลอดภัยของ Queue: มีระบบจัดการล็อกข้อมูลในตัวและใช้การสำเนาข้อมูล (Copy-by-Value) ป้องกันปัญหา Race Condition และ Data Corruption ได้อย่างเด็ดขาด ต่างจากตัวแปร Global ที่เข้าถึงพร้อมกันได้

2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
        ประโยชน์ของ Stack High Water Mark: ใช้ตรวจสอบพื้นที่ Stack ที่เหลือต่ำที่สุด ช่วยป้องกันข้อผิดพลาดประเภท Stack Overflow และช่วยให้ปรับขนาด RAM ของแต่ละ Task ได้อย่างเหมาะสม

3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
        ผลกระทบเมื่อความเร็วไม่เท่ากัน: Queue จะเต็มอย่างรวดเร็ว หากตั้งค่า Timeout เป็น 0 ข้อมูลใหม่จะถูกทิ้ง (Data Drop) แต่หากตั้งเวลารอ Task ผู้ส่งจะถูกบล็อกรอ ทำให้ระบบหน่วงช้าลงตามความเร็วของเครือข่าย



I (31) boot: ESP-IDF v5.1.2-dirty 2nd stage bootloader
I (31) boot: compile time Oct 25 2026 17:08:36
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
I (96) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=096d8h ( 38616) map
I (119) esp_image: segment 1: paddr=00019700 vaddr=3ffb0000 size=020f0h (  8432) load
I (122) esp_image: segment 2: paddr=0001b7f8 vaddr=40080000 size=04820h ( 18464) load
I (132) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=13ad4h ( 80596) map
I (162) esp_image: segment 4: paddr=00033afc vaddr=40084820 size=07968h ( 31080) load
I (181) boot: Loaded app from partition at offset 0x10000
I (182) boot: Disabling RNG early entropy source...
I (193) cpu_start: Multicore app
I (193) cpu_start: Pro cpu up.
I (193) cpu_start: Starting app cpu, entry point is 0x40081100
--- 0x40081100: call_start_cpu1 at /Users/kittikarnkaewnual/esp/esp-idf/components/esp_system/port/cpu_start.c:157
I (0) cpu_start: App cpu up.
I (211) cpu_start: Pro cpu start user code
I (211) cpu_start: cpu freq: 160000000 Hz
I (211) cpu_start: Application information:
I (216) cpu_start: Project name:     freertos_sensor_queue
I (222) cpu_start: App version:      029da6d
I (227) cpu_start: Compile time:     Oct 25 2026 17:08:29
I (233) cpu_start: ELF file SHA256:  a237a25ff824714e...
I (239) cpu_start: ESP-IDF:          v5.1.2-dirty
I (245) cpu_start: Min chip rev:     v0.0
I (249) cpu_start: Max chip rev:     v3.99 
I (254) cpu_start: Chip rev:         v3.1
I (259) heap_init: Initializing. RAM available for dynamic allocation:
I (266) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (272) heap_init: At 3FFB2970 len 0002D690 (181 KiB): DRAM
I (278) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (285) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (291) heap_init: At 4008C188 len 00013E78 (79 KiB): IRAM
I (299) spi_flash: detected chip: generic
I (302) spi_flash: flash io: dio
W (306) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (320) app_start: Starting scheduler on CPU0
I (324) app_start: Starting scheduler on CPU1
I (324) main_task: Started on CPU0
I (334) main_task: Calling app_main()
I (334) LAB_FREERTOS_QUEUE: ==================================================================
I (344) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (354) LAB_FREERTOS_QUEUE: ==================================================================
I (364) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 0
I (364) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.1 C, Hum: 59.8 %, Lux: 206
I (374) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (384) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (394) LAB_FREERTOS_QUEUE: =======================================================
I (404) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (404) LAB_FREERTOS_QUEUE:   -> Timestamp   : 40 ms
I (414) LAB_FREERTOS_QUEUE:   -> Temperature : 29.10 degC
I (424) LAB_FREERTOS_QUEUE:   -> Humidity    : 59.80 %
I (424) LAB_FREERTOS_QUEUE:   -> Light Lux   : 206 lux
I (434) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (444) LAB_FREERTOS_QUEUE: =======================================================
I (454) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (454) main_task: Returned from app_main()
I (1884) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.0 C, Hum: 53.4 %, Lux: 371
I (1884) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (1884) LAB_FREERTOS_QUEUE: =======================================================
I (1894) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (1904) LAB_FREERTOS_QUEUE:   -> Timestamp   : 1560 ms
I (1904) LAB_FREERTOS_QUEUE:   -> Temperature : 29.00 degC
I (1914) LAB_FREERTOS_QUEUE:   -> Humidity    : 53.40 %
I (1924) LAB_FREERTOS_QUEUE:   -> Light Lux   : 371 lux
I (1924) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (1934) LAB_FREERTOS_QUEUE: =======================================================
I (1944) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (3384) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.8 C, Hum: 60.2 %, Lux: 669
I (3384) LAB_FREERTOS_QUEUE: =======================================================
I (3384) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (3384) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (3404) LAB_FREERTOS_QUEUE:   -> Timestamp   : 3060 ms
I (3404) LAB_FREERTOS_QUEUE:   -> Temperature : 34.80 degC
I (3414) LAB_FREERTOS_QUEUE:   -> Humidity    : 60.20 %
I (3424) LAB_FREERTOS_QUEUE:   -> Light Lux   : 669 lux
I (3424) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (3434) LAB_FREERTOS_QUEUE: =======================================================
I (3444) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (4894) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.8 C, Hum: 58.4 %, Lux: 625
I (4894) LAB_FREERTOS_QUEUE: =======================================================
I (4894) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (4894) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (4914) LAB_FREERTOS_QUEUE:   -> Timestamp   : 4570 ms
I (4914) LAB_FREERTOS_QUEUE:   -> Temperature : 29.80 degC
I (4924) LAB_FREERTOS_QUEUE:   -> Humidity    : 58.40 %
I (4934) LAB_FREERTOS_QUEUE:   -> Light Lux   : 625 lux
I (4934) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (4944) LAB_FREERTOS_QUEUE: =======================================================
I (4954) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (6404) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.2 C, Hum: 54.1 %, Lux: 227
I (6404) LAB_FREERTOS_QUEUE: =======================================================
I (6404) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (6404) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (6424) LAB_FREERTOS_QUEUE:   -> Timestamp   : 6080 ms
I (6424) LAB_FREERTOS_QUEUE:   -> Temperature : 34.20 degC
I (6434) LAB_FREERTOS_QUEUE:   -> Humidity    : 54.10 %
I (6444) LAB_FREERTOS_QUEUE:   -> Light Lux   : 227 lux
I (6444) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (6454) LAB_FREERTOS_QUEUE: =======================================================
I (6464) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (7914) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.5 C, Hum: 66.6 %, Lux: 571
I (7914) LAB_FREERTOS_QUEUE: =======================================================
I (7914) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (7914) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (7934) LAB_FREERTOS_QUEUE:   -> Timestamp   : 7590 ms
I (7934) LAB_FREERTOS_QUEUE:   -> Temperature : 28.50 degC
I (7944) LAB_FREERTOS_QUEUE:   -> Humidity    : 66.60 %
I (7954) LAB_FREERTOS_QUEUE:   -> Light Lux   : 571 lux
I (7954) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (7964) LAB_FREERTOS_QUEUE: =======================================================
I (7974) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (9424) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.0 C, Hum: 51.3 %, Lux: 506
I (9424) LAB_FREERTOS_QUEUE: =======================================================
I (9424) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (9424) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (9444) LAB_FREERTOS_QUEUE:   -> Timestamp   : 9100 ms
I (9444) LAB_FREERTOS_QUEUE:   -> Temperature : 34.00 degC
I (9454) LAB_FREERTOS_QUEUE:   -> Humidity    : 51.30 %
I (9464) LAB_FREERTOS_QUEUE:   -> Light Lux   : 506 lux
I (9464) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (9474) LAB_FREERTOS_QUEUE: =======================================================
I (9484) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (10934) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 32.8 C, Hum: 67.5 %, Lux: 644
I (10934) LAB_FREERTOS_QUEUE: =======================================================
I (10934) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (10934) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (10954) LAB_FREERTOS_QUEUE:   -> Timestamp   : 10610 ms
I (10954) LAB_FREERTOS_QUEUE:   -> Temperature : 32.80 degC
I (10964) LAB_FREERTOS_QUEUE:   -> Humidity    : 67.50 %
I (10974) LAB_FREERTOS_QUEUE:   -> Light Lux   : 644 lux
I (10974) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (10984) LAB_FREERTOS_QUEUE: =======================================================
I (10994) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (12444) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.9 C, Hum: 68.4 %, Lux: 699
I (12444) LAB_FREERTOS_QUEUE: =======================================================
I (12444) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (12444) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (12464) LAB_FREERTOS_QUEUE:   -> Timestamp   : 12120 ms
I (12464) LAB_FREERTOS_QUEUE:   -> Temperature : 28.90 degC
I (12474) LAB_FREERTOS_QUEUE:   -> Humidity    : 68.40 %
I (12484) LAB_FREERTOS_QUEUE:   -> Light Lux   : 699 lux
I (12484) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (12494) LAB_FREERTOS_QUEUE: =======================================================
I (12504) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (13954) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 32.7 C, Hum: 57.6 %, Lux: 233
I (13954) LAB_FREERTOS_QUEUE: =======================================================
I (13954) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (13954) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (13974) LAB_FREERTOS_QUEUE:   -> Timestamp   : 13630 ms
I (13974) LAB_FREERTOS_QUEUE:   -> Temperature : 32.70 degC
I (13984) LAB_FREERTOS_QUEUE:   -> Humidity    : 57.60 %
I (13994) LAB_FREERTOS_QUEUE:   -> Light Lux   : 233 lux
I (13994) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (14004) LAB_FREERTOS_QUEUE: =======================================================
I (14014) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (15464) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.1 C, Hum: 63.6 %, Lux: 229
I (15464) LAB_FREERTOS_QUEUE: =======================================================
I (15464) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (15464) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (15484) LAB_FREERTOS_QUEUE:   -> Timestamp   : 15140 ms
I (15484) LAB_FREERTOS_QUEUE:   -> Temperature : 29.10 degC
I (15494) LAB_FREERTOS_QUEUE:   -> Humidity    : 63.60 %
I (15504) LAB_FREERTOS_QUEUE:   -> Light Lux   : 229 lux
I (15504) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (15514) LAB_FREERTOS_QUEUE: =======================================================
I (15524) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (16974) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 33.9 C, Hum: 52.6 %, Lux: 358
I (16974) LAB_FREERTOS_QUEUE: =======================================================
I (16974) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (16974) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (16994) LAB_FREERTOS_QUEUE:   -> Timestamp   : 16650 ms
I (16994) LAB_FREERTOS_QUEUE:   -> Temperature : 33.90 degC
I (17004) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.60 %
I (17014) LAB_FREERTOS_QUEUE:   -> Light Lux   : 358 lux
I (17014) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (17024) LAB_FREERTOS_QUEUE: =======================================================
I (17034) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (18484) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.4 C, Hum: 62.2 %, Lux: 687
I (18484) LAB_FREERTOS_QUEUE: =======================================================
I (18484) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (18484) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (18504) LAB_FREERTOS_QUEUE:   -> Timestamp   : 18160 ms
I (18504) LAB_FREERTOS_QUEUE:   -> Temperature : 28.40 degC
I (18514) LAB_FREERTOS_QUEUE:   -> Humidity    : 62.20 %
I (18524) LAB_FREERTOS_QUEUE:   -> Light Lux   : 687 lux
I (18524) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (18534) LAB_FREERTOS_QUEUE: =======================================================
I (18544) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (19994) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.9 C, Hum: 67.7 %, Lux: 321
I (19994) LAB_FREERTOS_QUEUE: =======================================================
I (19994) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (19994) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (20014) LAB_FREERTOS_QUEUE:   -> Timestamp   : 19670 ms
I (20014) LAB_FREERTOS_QUEUE:   -> Temperature : 26.90 degC
I (20024) LAB_FREERTOS_QUEUE:   -> Humidity    : 67.70 %
I (20034) LAB_FREERTOS_QUEUE:   -> Light Lux   : 321 lux
I (20034) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (20044) LAB_FREERTOS_QUEUE: =======================================================
I (20054) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (21504) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.3 C, Hum: 64.0 %, Lux: 423
I (21504) LAB_FREERTOS_QUEUE: =======================================================
I (21504) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (21504) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (21524) LAB_FREERTOS_QUEUE:   -> Timestamp   : 21180 ms
I (21524) LAB_FREERTOS_QUEUE:   -> Temperature : 28.30 degC
I (21534) LAB_FREERTOS_QUEUE:   -> Humidity    : 64.00 %
I (21544) LAB_FREERTOS_QUEUE:   -> Light Lux   : 423 lux
I (21544) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (21554) LAB_FREERTOS_QUEUE: =======================================================
I (21564) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (23014) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.4 C, Hum: 65.4 %, Lux: 302
I (23014) LAB_FREERTOS_QUEUE: =======================================================
I (23014) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (23014) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (23034) LAB_FREERTOS_QUEUE:   -> Timestamp   : 22690 ms
I (23034) LAB_FREERTOS_QUEUE:   -> Temperature : 34.40 degC
I (23044) LAB_FREERTOS_QUEUE:   -> Humidity    : 65.40 %
I (23054) LAB_FREERTOS_QUEUE:   -> Light Lux   : 302 lux
I (23054) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (23064) LAB_FREERTOS_QUEUE: =======================================================
I (23074) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (24524) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 25.7 C, Hum: 52.1 %, Lux: 595
I (24524) LAB_FREERTOS_QUEUE: =======================================================
I (24524) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (24524) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (24544) LAB_FREERTOS_QUEUE:   -> Timestamp   : 24200 ms
I (24544) LAB_FREERTOS_QUEUE:   -> Temperature : 25.70 degC
I (24554) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.10 %
I (24564) LAB_FREERTOS_QUEUE:   -> Light Lux   : 595 lux
I (24564) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (24574) LAB_FREERTOS_QUEUE: =======================================================
I (24584) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (26034) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.1 C, Hum: 56.9 %, Lux: 515
I (26034) LAB_FREERTOS_QUEUE: =======================================================
I (26034) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (26034) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (26054) LAB_FREERTOS_QUEUE:   -> Timestamp   : 25710 ms
I (26054) LAB_FREERTOS_QUEUE:   -> Temperature : 26.10 degC
I (26064) LAB_FREERTOS_QUEUE:   -> Humidity    : 56.90 %
I (26074) LAB_FREERTOS_QUEUE:   -> Light Lux   : 515 lux
I (26074) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (26084) LAB_FREERTOS_QUEUE: =======================================================
I (26094) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (27544) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 31.6 C, Hum: 55.7 %, Lux: 253
I (27544) LAB_FREERTOS_QUEUE: =======================================================
I (27544) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (27544) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (27564) LAB_FREERTOS_QUEUE:   -> Timestamp   : 27220 ms
I (27564) LAB_FREERTOS_QUEUE:   -> Temperature : 31.60 degC
I (27574) LAB_FREERTOS_QUEUE:   -> Humidity    : 55.70 %
I (27584) LAB_FREERTOS_QUEUE:   -> Light Lux   : 253 lux
I (27584) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (27594) LAB_FREERTOS_QUEUE: =======================================================
I (27604) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
I (29054) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 27.3 C, Hum: 64.5 %, Lux: 663
I (29054) LAB_FREERTOS_QUEUE: =======================================================
I (29054) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1284 words (1284 bytes)
I (29054) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (29074) LAB_FREERTOS_QUEUE:   -> Timestamp   : 28730 ms
I (29074) LAB_FREERTOS_QUEUE:   -> Temperature : 27.30 degC
I (29084) LAB_FREERTOS_QUEUE:   -> Humidity    : 64.50 %
I (29094) LAB_FREERTOS_QUEUE:   -> Light Lux   : 663 lux
I (29094) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (29104) LAB_FREERTOS_QUEUE: =======================================================
I (29114) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2320 words (2320 bytes)
