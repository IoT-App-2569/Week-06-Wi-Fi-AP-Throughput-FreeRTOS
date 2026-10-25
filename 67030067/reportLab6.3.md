Lab6.3
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
I (12444) LAB_FREERTOS_QUEUE: ===============================



#คำถามท้ายการทดลอง 
1. เหตุใดการใช้ FreeRTOS Queue จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
ตอบ เพราะ FreeRTOS Queue มีกลไกจัดการการเข้าถึงข้อมูลอย่างปลอดภัยระหว่าง Task ช่วยป้องกันการอ่านหรือเขียนข้อมูลชนกัน ขณะที่ตัวแปร Global อาจเกิด Race Condition หากหลาย Task เข้าถึงพร้อมกันโดยไม่มีการป้องกัน

2. ค่า Stack High Water Mark มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
ตอบ ใช้ตรวจสอบปริมาณ Stack ที่เหลืออยู่น้อยที่สุดของ Task ช่วยให้ทราบว่า Task ใช้ Stack มากเกินไปหรือไม่ และช่วยป้องกันปัญหา Stack Overflow ซึ่งอาจทำให้ระบบทำงานผิดพลาดหรือหยุดทำงาน

3. หาก vSensorTask ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ vNetworkTask ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
ตอบ Queue จะมีข้อมูลสะสมเพิ่มขึ้นจนเต็ม เนื่องจาก Task เซนเซอร์ส่งข้อมูลเร็วกว่าที่ Task เครือข่ายจะประมวลผลได้ หาก Queue เต็ม การส่งข้อมูลใหม่อาจล้มเหลวหรือรอจนกว่าจะมีพื้นที่ว่าง ระบบสามารถรับมือได้โดยเพิ่มขนาด Queue ลดความถี่ในการส่งข้อมูล หรือใช้วิธีเก็บเฉพาะข้อมูลล่าสุดตามความเหมาะสมของงาน