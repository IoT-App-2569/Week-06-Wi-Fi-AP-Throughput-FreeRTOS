# ใบงานที่ 6.5: 📋 Assignment Project — ระบบเช็กชื่อและยืนยันตัวตนอัจฉริยะด้วย RF Proximity & Sensor Fusion
```
--- 0x40080400: _invalid_pc_placeholder at C:/Users/09677/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.cI (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug 10 2026 22:07:27
:25
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1b758h (112472) map
I (127) esp_image: segment 1: paddr=0002b780 vaddr=3ffb0000 size=03eech ( 16108) load
I (133) esp_image: segment 2: paddr=0002f674 vaddr=40080000 size=009a4h (  2468) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8e1b4h (582068) map
I (337) esp_image: segment 4: paddr=000be1dc vaddr=400809a4 size=175e8h ( 95720) load
I (375) esp_image: segment 5: paddr=000d57cc vaddr=50000000 size=00020h (    32) load
I (387) boot: Loaded app from partition at offset 0x10000
I (387) boot: Disabling RNG early entropy source...
I (397) cpu_start: Multicore app
I (406) cpu_start: Pro cpu start user code
I (406) cpu_start: cpu freq: 160000000 Hz
I (406) app_init: Application information:
I (406) app_init: Project name:     smart_attendance
I (410) app_init: App version:      4d1cafd
I (414) app_init: Compile time:     Aug 10 2026 22:07:00
I (419) app_init: ELF file SHA256:  7ab878dba...
I (424) app_init: ESP-IDF:          v5.5.1-dirty
I (428) efuse_init: Min chip rev:     v0.0
I (432) efuse_init: Max chip rev:     v3.99 
I (436) efuse_init: Chip rev:         v3.1
I (440) heap_init: Initializing. RAM available for dynamic allocation:
I (446) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (451) heap_init: At 3FFB8048 len 00027FB8 (159 KiB): DRAM
I (456) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (462) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (467) heap_init: At 40097F8C len 00008074 (32 KiB): IRAM
W (474) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (485) spi_flash: detected chip: generic
I (489) spi_flash: flash io: dio
W (492) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (505) main_task: Started on CPU0
I (515) main_task: Calling app_main()
I (575) wifi:wifi driver task: 3ffc0194, prio:23, stack:6656, core=0
I (595) wifi:wifi firmware version: 14da9b7
I (595) wifi:wifi certification version: v7.0
I (595) wifi:config NVS flash: enabled
I (595) wifi:config nano formatting: disabled
I (595) wifi:Init data frame dynamic rx buffer num: 32
I (605) wifi:Init static rx mgmt buffer num: 5
I (605) wifi:Init management short buffer num: 32
I (605) wifi:Init dynamic tx buffer num: 32
I (615) wifi:Init static rx buffer size: 1600
I (615) wifi:Init static rx buffer num: 10
I (625) wifi:Init dynamic rx buffer num: 32
I (625) wifi_init: rx ba win: 6
I (625) wifi_init: accept mbox: 6
I (635) wifi_init: tcpip mbox: 32
I (635) wifi_init: udp mbox: 6
I (635) wifi_init: tcp mbox: 6
I (635) wifi_init: tcp tx win: 5760
I (645) wifi_init: tcp rx win: 5760
I (645) wifi_init: tcp mss: 1440
I (645) wifi_init: WiFi IRAM OP enabled
I (655) wifi_init: WiFi RX IRAM OP enabled
I (665) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (745) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (775) wifi:mode : softAP (88:57:21:ad:64:99)
I (775) wifi:Total power save buffer number: 16
I (775) wifi:Init max length of beacon: 752/752
I (775) wifi:Init max length of beacon: 752/752
I (785) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (795) SMART_ATTENDANCE: Attendance Web Server Started at http://192.168.4.1
I (795) main_task: Returned from app_main()
I (24295) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (24295) wifi:station: 3e:98:c8:94:6d:68 join, AID=1, bgn, 40U
I (24355) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (24505) wifi:<ba-add>idx:2 (ifx:1, 3e:98:c8:94:6d:68), tid:0, ssn:0, winSize:64
I (24555) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
W (41095) httpd_uri: httpd_uri: URI '/favicon.ico' not found
W (41105) httpd_txrx: httpd_resp_send_err: 404 Not Found - Nothing matches the given URI
I (97065) wifi:new:<1,0>, old:<1,1>, ap:<1,0>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (97065) wifi:station: 1e:0a:6d:d7:be:c2 join, AID=2, bgn, 20
I (97085) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (98305) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3
I (100275) wifi:<ba-add>idx:3 (ifx:1, 1e:0a:6d:d7:be:c2), tid:0, ssn:2, winSize:64
I (100285) wifi:<ba-add>idx:4 (ifx:1, 3e:98:c8:94:6d:68), tid:7, ssn:0, winSize:64
W (144655) httpd_uri: httpd_uri: URI '/favicon.ico' not found
W (144665) httpd_txrx: httpd_resp_send_err: 404 Not Found - Nothing matches the given URI
W (146535) httpd_uri: httpd_uri: URI '/checkin' not found
W (146535) httpd_txrx: httpd_resp_send_err: 404 Not Found - Nothing matches the given URI

```

## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

### 5.1 ตารางบันทึกการเช็กชื่อผ่าน RF Proximity

| ลำดับที่ | ชื่อสมาร์ตโฟน / MAC Address | ระดับ RSSI (dBm) | ระยะทางประเมิน (Near/Far) | ผลการลงชื่อ (Passed/Rejected) |
| :------: | :-------------------------- | :--------------: | :-----------------------: | :---------------------------: |
|  **1**   | 3E:98:C8:94:6D:68           |     -45 dBm      |           Near            |            Passed             |
|  **2**   | 1E:0A:6D:D7:BE:C2           |     -45 dBm      |           Near            |            Passed             |
![[S__18595842.jpg]]
---

## 6. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การใช้ **RF Signal Proximity (RSSI)** ร่วมกับ **HTTP Web Server** บน ESP32 แก้ปัญหาการฝากเช็กชื่อแทนกันในห้องเรียนได้อย่างไร?
		บังคับให้สมาร์ตโฟนต้องอยู่ใกล้ ESP32 ในห้องเรียนจริงเท่านั้น สัญญาณ RSSI ถึงจะแรงพอเปิดสิทธิ์ให้กดเช็กชื่อได้
2. เหตุใดระดับเกณฑ์ RSSI ที่ `-55 dBm` จึงเหมาะสมสำหรับการระบุตำแหน่งอุปกรณ์ให้อยู่ภายในรัศมีโต๊ะปฏิบัติการ?
		เป็นระดับความแรงสัญญาณระยะประชิด (ประมาณ 1–2 เมตร) ในรัศมีโต๊ะปฏิบัติการ ถ้าอยู่นอกห้องสัญญาณจะดร็อปลงทันที
3. หากต้องการต่อยอดมินิโปรเจกต์นี้ในอนาคต ให้สามารถบันทึกข้อมูลการเข้าเรียนลงระบบ Cloud (เช่น Google Sheets หรือ Firebase) จะต้องเพิ่มส่วนเชื่อมต่อใดบ้าง?
		- **Wi-Fi AP+STA Mode:** ให้ ESP32 ต่ออินเทอร์เน็ตพร้อมปล่อย AP ได้
		- **`esp_http_client`:** สำหรับส่ง REST API/Webhook ไปยัง Google Sheets หรือ Firebase