# ใบงานที่ 6.3: การออกแบบ FreeRTOS Task Architecture & Sensor Data Fusion ผ่าน Queue

```
rst:0x1 (POWERON_RESET),boot:0x12 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0030,len:6380
ho 0 tail 12 room 4
load:0x40078000,len:15916
load:0x40080400,len:3860
--- 0x40080400: _invalid_pc_placeholder at C:/Users/09677/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug 10 2026 09:42:12
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=09e38h ( 40504) map
I (102) esp_image: segment 1: paddr=00019e60 vaddr=3ffb0000 size=023d8h (  9176) load
I (106) esp_image: segment 2: paddr=0001c240 vaddr=40080000 size=03dd8h ( 15832) load
I (112) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=13850h ( 79952) map
I (141) esp_image: segment 4: paddr=00033878 vaddr=40083dd8 size=0934ch ( 37708) load
I (156) esp_image: segment 5: paddr=0003cbcc vaddr=50000000 size=00020h (    32) load
I (163) boot: Loaded app from partition at offset 0x10000
I (163) boot: Disabling RNG early entropy source...
I (174) cpu_start: Multicore app
I (183) cpu_start: Pro cpu start user code
I (183) cpu_start: cpu freq: 160000000 Hz
I (183) app_init: Application information:
I (183) app_init: Project name:     freertos_sensor_queue
I (188) app_init: App version:      029da6d-dirty
I (192) app_init: Compile time:     Aug 10 2026 09:40:42
I (197) app_init: ELF file SHA256:  69b818337...
I (202) app_init: ESP-IDF:          v5.5.1-dirty
I (206) efuse_init: Min chip rev:     v0.0
I (210) efuse_init: Max chip rev:     v3.99 
I (214) efuse_init: Chip rev:         v3.1
I (218) heap_init: Initializing. RAM available for dynamic allocation:
I (224) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (229) heap_init: At 3FFB2CA8 len 0002D358 (180 KiB): DRAM
I (234) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (240) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (245) heap_init: At 4008D124 len 00012EDC (75 KiB): IRAM
W (252) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (264) spi_flash: detected chip: generic
I (267) spi_flash: flash io: dio
W (270) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (283) main_task: Started on CPU0
I (293) main_task: Calling app_main()
I (293) LAB_FREERTOS_QUEUE: ==================================================================
I (293) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (303) LAB_FREERTOS_QUEUE: ==================================================================
I (313) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 0
I (313) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.1 C, Hum: 52.0 %, Lux: 459
I (323) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (333) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (333) LAB_FREERTOS_QUEUE: =======================================================
I (343) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (353) LAB_FREERTOS_QUEUE:   -> Timestamp   : 30 ms
I (353) LAB_FREERTOS_QUEUE:   -> Temperature : 28.10 degC
I (363) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.00 %
I (363) LAB_FREERTOS_QUEUE:   -> Light Lux   : 459 lux
I (373) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (383) LAB_FREERTOS_QUEUE: =======================================================
I (383) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (393) main_task: Returned from app_main()
I (1833) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.8 C, Hum: 69.3 %, Lux: 326
I (1833) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (1833) LAB_FREERTOS_QUEUE: =======================================================
I (1843) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (1843) LAB_FREERTOS_QUEUE:   -> Timestamp   : 1550 ms
I (1853) LAB_FREERTOS_QUEUE:   -> Temperature : 34.80 degC
I (1853) LAB_FREERTOS_QUEUE:   -> Humidity    : 69.30 %
I (1863) LAB_FREERTOS_QUEUE:   -> Light Lux   : 326 lux
I (1863) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (1873) LAB_FREERTOS_QUEUE: =======================================================
I (1883) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (3333) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 32.1 C, Hum: 63.9 %, Lux: 434
I (3333) LAB_FREERTOS_QUEUE: =======================================================
I (3333) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (3333) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (3343) LAB_FREERTOS_QUEUE:   -> Timestamp   : 3050 ms
I (3353) LAB_FREERTOS_QUEUE:   -> Temperature : 32.10 degC
I (3353) LAB_FREERTOS_QUEUE:   -> Humidity    : 63.90 %
I (3363) LAB_FREERTOS_QUEUE:   -> Light Lux   : 434 lux
I (3363) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (3373) LAB_FREERTOS_QUEUE: =======================================================
I (3383) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (4843) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.1 C, Hum: 50.1 %, Lux: 264
I (4843) LAB_FREERTOS_QUEUE: =======================================================
I (4843) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (4843) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (4853) LAB_FREERTOS_QUEUE:   -> Timestamp   : 4560 ms
I (4863) LAB_FREERTOS_QUEUE:   -> Temperature : 29.10 degC
I (4863) LAB_FREERTOS_QUEUE:   -> Humidity    : 50.10 %
I (4873) LAB_FREERTOS_QUEUE:   -> Light Lux   : 264 lux
I (4873) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (4883) LAB_FREERTOS_QUEUE: =======================================================
I (4893) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (6353) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.3 C, Hum: 68.2 %, Lux: 398
I (6353) LAB_FREERTOS_QUEUE: =======================================================
I (6353) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (6353) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (6363) LAB_FREERTOS_QUEUE:   -> Timestamp   : 6070 ms
I (6373) LAB_FREERTOS_QUEUE:   -> Temperature : 26.30 degC
I (6373) LAB_FREERTOS_QUEUE:   -> Humidity    : 68.20 %
I (6383) LAB_FREERTOS_QUEUE:   -> Light Lux   : 398 lux
I (6383) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (6393) LAB_FREERTOS_QUEUE: =======================================================
I (6403) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (7863) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.8 C, Hum: 55.1 %, Lux: 266
I (7863) LAB_FREERTOS_QUEUE: =======================================================
I (7863) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (7863) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (7873) LAB_FREERTOS_QUEUE:   -> Timestamp   : 7580 ms
I (7883) LAB_FREERTOS_QUEUE:   -> Temperature : 26.80 degC
I (7883) LAB_FREERTOS_QUEUE:   -> Humidity    : 55.10 %
I (7893) LAB_FREERTOS_QUEUE:   -> Light Lux   : 266 lux
I (7893) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (7903) LAB_FREERTOS_QUEUE: =======================================================
I (7913) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (9373) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 32.0 C, Hum: 59.1 %, Lux: 622
I (9373) LAB_FREERTOS_QUEUE: =======================================================
I (9373) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (9373) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (9383) LAB_FREERTOS_QUEUE:   -> Timestamp   : 9090 ms
I (9393) LAB_FREERTOS_QUEUE:   -> Temperature : 32.00 degC
I (9393) LAB_FREERTOS_QUEUE:   -> Humidity    : 59.10 %
I (9403) LAB_FREERTOS_QUEUE:   -> Light Lux   : 622 lux
I (9403) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (9413) LAB_FREERTOS_QUEUE: =======================================================
I (9423) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (10883) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.3 C, Hum: 52.7 %, Lux: 635
I (10883) LAB_FREERTOS_QUEUE: =======================================================
I (10883) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (10883) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (10893) LAB_FREERTOS_QUEUE:   -> Timestamp   : 10600 ms
I (10903) LAB_FREERTOS_QUEUE:   -> Temperature : 29.30 degC
I (10903) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.70 %
I (10913) LAB_FREERTOS_QUEUE:   -> Light Lux   : 635 lux
I (10913) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
```
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task        | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) |          สถานะความปลอดภัยสแตก          |
| :------------------------ | :-----------------------------------------: | :--------------------------------------------: | :------------------------------------: |
| **`SensorCollectorTask`** |                    3072                     |               1196 Words / Bytes               | **ปลอดภัย (Safe)** — เหลือสแตก 1.19 KB |
| **`NetworkCommTask`**     |                    4096                     |               2248 Words / Bytes               | **ปลอดภัย (Safe)** — เหลือสแตก 2.24 KB |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
		Ans
			- **ป้องกันสภาวะแย่งชิงข้อมูล :** การใช้ตัวแปรแบบ Global โดยไม่มีกลไกป้องกัน อาจถูก Task หนึ่งเขียนทับในขณะที่อีก Task กำลังอ่านข้อมูล ทำให้ข้อมูลขัดข้อง 
			- **มีกลไก Critical Section และ Mutex ในตัว:** FreeRTOS Queue ใช้การคัดลอกข้อมูลแบบ Pass-by-Value และถูกควบคุมด้วย Mutex/Interrupt Lock ระดับเคอร์เนล ทำให้อ่านและเขียนข้อมูลได้อย่างสมบูรณ์ในจังหวะเดียว 
2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
		Ans
			- **ป้องกันและตรวจจับ Stack Overflow:** ช่วยวิเคราะห์ว่า Task ใดใช้งานสแตกใกล้เต็มขีดจำกัด 
			- **ปรับแต่งการใช้หน่วยความจำ RAM (Memory Optimization):** ช่วยตรวจสอบการจองสแตกเกินความจำเป็น (
			- **ระบุพฤติกรรมผิดปกติของฟังก์ชัน:** หากค่า High Water Mark ลดลงกะทันหัน สามารถสืบทราบได้ว่ามีฟังก์ชันใดสร้าง Local Variable ขนาดใหญ่เกินไป 
3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
		Ans
			- **เกิดอะไรขึ้น:** Queue จะเต็ม ข้อมูลใหม่จะถูกทิ้ง (Data Loss) หรือ Task ฝั่งเซนเซอร์จะถูกบล็อกจนค้าง
			- **วิธีแก้:** ใช้ `xQueueOverwrite` เอาเฉพาะค่าล่าสุด, รวมข้อมูล (Data Aggregation) ก่อนส่ง หรือขยายขนาด Queue
