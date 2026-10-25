Lab6.2
I (31) boot: ESP-IDF v5.1.2-dirty 2nd stage bootloader
I (31) boot: compile time Oct 25 2026 16:51:08
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
I (96) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1fd04h (130308) map
I (152) esp_image: segment 1: paddr=0002fd2c vaddr=3ffb0000 size=002ech (  748) load
I (152) esp_image: segment 2: paddr=00030020 vaddr=400d0020 size=82250h (533072) map
I (350) esp_image: segment 3: paddr=000b2278 vaddr=3ffb02ec size=03790h (14224) load
I (356) esp_image: segment 4: paddr=000b5a10 vaddr=40080000 size=15c3ch (89148) load
I (404) boot: Loaded app from partition at offset 0x10000
I (404) boot: Disabling RNG early entropy source...
I (416) cpu_start: Multicore app
I (416) cpu_start: Pro cpu up.
I (416) cpu_start: Starting app cpu, entry point is 0x40081390
--- 0x40081390: call_start_cpu1 at /Users/kittikarnkaewnual/esp/esp-idf/components/esp_system/port/cpu_start.c:157
I (0) cpu_start: App cpu up.
I (434) cpu_start: Pro cpu start user code
I (434) cpu_start: cpu freq: 160000000 Hz
I (434) cpu_start: Application information:
I (439) cpu_start: Project name:     rssi_speed_profiler
I (445) cpu_start: App version:      029da6d
I (450) cpu_start: Compile time:     Oct 25 2026 16:51:01
I (456) cpu_start: ELF file SHA256:  90317ba384259145...
I (462) cpu_start: ESP-IDF:          v5.1.2-dirty
I (467) cpu_start: Min chip rev:     v0.0
I (472) cpu_start: Max chip rev:     v3.99 
I (477) cpu_start: Chip rev:         v3.1
I (482) heap_init: Initializing. RAM available for dynamic allocation:
I (489) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (495) heap_init: At 3FFB7B20 len 000284E0 (161 KiB): DRAM
I (501) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (507) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (514) heap_init: At 40095C3C len 0000A3C4 (40 KiB): IRAM
I (521) spi_flash: detected chip: generic
I (525) spi_flash: flash io: dio
W (528) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (542) app_start: Starting scheduler on CPU0
I (547) app_start: Starting scheduler on CPU1
I (547) main_task: Started on CPU0
I (557) main_task: Calling app_main()
I (557) CLIENT_PROFILER: [FORENSIC]: Call nvs_flash_init()
I (607) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_init()
I (607) CLIENT_PROFILER: [FORENSIC]: Call esp_event_loop_create_default()
I (607) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (617) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_init(&config)
I (627) wifi:wifi driver task: 3ffbfc20, prio:23, stack:6656, core=0
I (647) wifi:wifi firmware version: 91b9630
I (647) wifi:wifi certification version: v7.0
I (647) wifi:config NVS flash: enabled
I (647) wifi:config nano formating: disabled
I (657) wifi:Init data frame dynamic rx buffer num: 32
I (657) wifi:Init static rx mgmt buffer num: 5
I (667) wifi:Init management short buffer num: 32
I (667) wifi:Init dynamic tx buffer num: 32
I (677) wifi:Init static rx buffer size: 1600
I (677) wifi:Init static rx buffer num: 10
I (677) wifi:Init dynamic rx buffer num: 32
I (687) wifi_init: rx ba win: 6
I (687) wifi_init: tcpip mbox: 32
I (697) wifi_init: udp mbox: 6
I (697) wifi_init: tcp mbox: 6
I (697) wifi_init: tcp tx win: 5744
I (707) wifi_init: tcp rx win: 5744
I (707) wifi_init: tcp mss: 1440
I (717) wifi_init: WiFi IRAM OP enabled
I (717) wifi_init: WiFi RX IRAM OP enabled
I (717) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (727) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (737) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_start()
I (747) phy_init: phy_version 4780,16b31a7,Sep 22 2023,20:42:16
I (827) wifi:mode : sta (84:1f:e8:39:b4:48)
I (827) wifi:enable tsf
I (827) CLIENT_PROFILER: Client profiler ready: 50 KB x 10 rounds
I (827) main_task: Returned from app_main()
I (827) CLIENT_PROFILER: [FORENSIC EVENT]: Station started; connecting toMY_ESP32_AP
W (3257) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (3257) CLIENT_PROFILER: Retrying Wi-Fi connection (1/10)
W (5667) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (5667) CLIENT_PROFILER: Retrying Wi-Fi connection (2/10)
W (8087) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (8087) CLIENT_PROFILER: Retrying Wi-Fi connection (3/10)
W (10507) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (10507) CLIENT_PROFILER: Retrying Wi-Fi connection (4/10)
W (12917) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (12917) CLIENT_PROFILER: Retrying Wi-Fi connection (5/10)
W (15337) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (15337) CLIENT_PROFILER: Retrying Wi-Fi connection (6/10)
W (17747) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (17747) CLIENT_PROFILER: Retrying Wi-Fi connection (7/10)
W (20167) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (20167) CLIENT_PROFILER: Retrying Wi-Fi connection (8/10)
W (22577) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (22577) CLIENT_PROFILER: Retrying Wi-Fi connection (9/10)
W (24997) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
I (24997) CLIENT_PROFILER: Retrying Wi-Fi connection (10/10)
W (27407) CLIENT_PROFILER: [FORENSIC EVENT]: Disconnected, reason=201
E (27417) CLIENT_PROFILER: Cannot connect to MY_ESP32_AP; profiler stopped
I (27417) CLIENT_PROFILER: All benchmark rounds completed





#คำถามท้ายการทดลอง 

1. เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?
ตอบ ค่า Tx Power ลดลง 18 dB ส่วนค่า RSSI จะลดลงตามสภาพแวดล้อมและระยะห่างระหว่างอุปกรณ์ ทำให้สัญญาณอ่อนลงและความเร็ว Throughput มีแนวโน้มลดลง

2. เหตุใดในระดับ RSSI ที่อ่อนกว่า -80 dBm ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?
ตอบ เนื่องจากสัญญาณ Wi-Fi อ่อนมาก ทำให้เกิดข้อผิดพลาดในการรับส่งข้อมูลและแพ็กเก็ตสูญหาย TCP จึงต้องส่งข้อมูลซ้ำและลดอัตราการส่งข้อมูลลง ส่งผลให้ Throughput ลดลงอย่างรวดเร็ว

3. สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?
ตอบ สามารถนำสมการ Regression มาใช้ทำนายค่า Throughput จากค่า RSSI ที่วัดได้ เพื่อประเมินคุณภาพการเชื่อมต่อและกำหนดเงื่อนไขให้ระบบแจ้งเตือนหรือปรับการทำงานเมื่อสัญญาณอ่อน เพื่อให้แอปพลิเคชัน IoT ทำงานได้อย่างมีประสิทธิภาพ




