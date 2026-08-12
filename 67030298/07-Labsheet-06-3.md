## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :--- | :---: | :---: | :---: |
| **`SensorCollectorTask`** | 3072 | 2028 | ปลอดภัย |
| **`NetworkCommTask`** | 4096 | 3080 | ปลอดภัย |

```text
I (27) boot: ESP-IDF v6.0.2-dirty 2nd stage bootloader
I (27) boot: compile time Aug 12 2026 00:05:02
I (28) boot: Multicore bootloader
I (29) boot: chip revision: v3.1
I (32) boot.esp32: SPI Speed      : 40MHz
I (36) boot.esp32: SPI Mode       : DIO
I (39) boot.esp32: SPI Flash Size : 2MB
I (43) boot: Enabling RNG early entropy source...
I (47) boot: Partition Table:
I (50) boot: ## Label            Usage          Type ST Offset   Length
I (56) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (63) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (69) boot:  2 factory          factory app      00 00 00010000 00100000
I (76) boot: End of partition table
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=08938h ( 35128) map
I (99) esp_image: segment 1: paddr=00018960 vaddr=3ffb0000 size=029fch ( 10748) load
I (104) esp_image: segment 2: paddr=0001b364 vaddr=40080000 size=04cb4h ( 19636) load
I (112) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=0c3b0h ( 50096) map
I (130) esp_image: segment 4: paddr=0002c3d8 vaddr=40084cb4 size=05fe4h ( 24548) load
I (140) esp_image: segment 5: paddr=000323c4 vaddr=50000000 size=00028h (    40) load
I (146) boot: Loaded app from partition at offset 0x10000
I (146) boot: Disabling RNG early entropy source...
I (159) cpu_start: Multicore app
I (167) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (167) cpu_start: Pro cpu start user code
I (167) cpu_start: cpu freq: 160000000 Hz
I (169) app_init: Application information:
I (173) app_init: Project name:     main
I (176) app_init: App version:      6d9eb91
I (180) app_init: Compile time:     Aug 12 2026 08:53:46
I (185) app_init: ELF file SHA256:  edc99b324...
I (190) app_init: ESP-IDF:          v6.0.2-dirty
I (258) main_task: Started on CPU0
I (258) main_task: Calling app_main()
I (258) LAB_FREERTOS_QUEUE: ==================================================================
I (268) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (278) LAB_FREERTOS_QUEUE: ==================================================================
I (288) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 0
I (288) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 25.0 C, Hum: 52.8 %, Lux: 401
I (298) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2028 words (2028 bytes)
I (308) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (308) LAB_FREERTOS_QUEUE: =======================================================
I (318) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (328) LAB_FREERTOS_QUEUE:   -> Timestamp   : 30 ms
I (328) LAB_FREERTOS_QUEUE:   -> Temperature : 25.00 degC
I (338) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.80 %
I (338) LAB_FREERTOS_QUEUE:   -> Light Lux   : 401 lux
I (348) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (358) LAB_FREERTOS_QUEUE: =======================================================
I (358) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3080 words (3080 bytes)
I (368) main_task: Returned from app_main()
I (1808) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.6 C, Hum: 54.9 %, Lux: 682
I (1808) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2028 words (2028 bytes)
I (1808) LAB_FREERTOS_QUEUE: =======================================================
I (1818) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (1818) LAB_FREERTOS_QUEUE:   -> Timestamp   : 1550 ms
I (1828) LAB_FREERTOS_QUEUE:   -> Temperature : 29.60 degC
I (1828) LAB_FREERTOS_QUEUE:   -> Humidity    : 54.90 %
I (1838) LAB_FREERTOS_QUEUE:   -> Light Lux   : 682 lux
I (1838) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (1848) LAB_FREERTOS_QUEUE: =======================================================
I (1858) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3080 words (3080 bytes)
```

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
> เพราะ Queue มีกลไกจัดการ Lock อัตโนมัติ ช่วยป้องกันข้อมูลพัง (Data Corruption) เมื่อเกิดการเข้าถึงข้อมูลจากหลาย Task พร้อมๆ กัน
2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
> ใช้ดู "พื้นที่สแตกที่เหลือน้อยที่สุด" ทำให้รู้ว่าใช้สแตกไปเท่าไหร่ ช่วยป้องกันบั๊ก Stack Overflow และใช้ RAM ได้คุ้มค่าขึ้น
3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
> Queue จะเต็ม ทำให้รับข้อมูลใหม่ไม่ได้ ระบบรับมือโดย `xQueueSend` จะแจ้ง Error กลับมา ทำให้โปรแกรมตัดสินใจทิ้งข้อมูลนั้นได้โดยไม่บล็อกการทำงาน