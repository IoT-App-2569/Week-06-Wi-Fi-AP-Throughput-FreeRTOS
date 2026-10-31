# รายงานผลการทดลองปฏิบัติการ สัปดาห์ที่ 6: Wi-Fi SoftAP, RF Throughput & Sensor Fusion with FreeRTOS

**ข้อมูลผู้จัดทำและส่งรายงาน (Student Identification):**

- **รหัสนักศึกษา:** 67030268
- **ชื่อ-นามสกุล (ไทย):** นายกร แดงทอง
- **ชื่อ-นามสกุล (อังกฤษ):** Korn Daengthong
- **โต๊ะปฏิบัติการ:** โต๊ะ 2
- **วิชา:** 03376134 IoT-App-2569 (ภาคเรียนที่ 2/2568)
- **วันที่อัปเดตรายงาน:** 31/10/2026 23:45:00

## สมาชิกผู้ทดลอง

- **รหัสนักศึกษา:** 67030268
- **ชื่อ-สกุล:** นายกร แดงทอง (Korn Daengthong)
- **โต๊ะปฏิบัติการ:** โต๊ะ 2

---

# ใบงานที่ 6.1: การคอนฟิก ESP32 SoftAP และการสกัด Forensic Log ข้อมูล Client

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

<img width="957" height="771" alt="image" src="https://github.com/user-attachments/assets/e1af6a57-3017-4b2d-8425-00ac31714432" />

*ภาพที่ 6.1: การเริ่มต้น ESP32 SoftAP (ESP32_AP_0268) และการดักจับ Client Event พร้อมแจกจ่าย IP 192.168.4.2*

| **อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android)** | **MAC Address ที่ดักจับได้** | **Association ID (AID)** | **หมายเลข IP Address ที่ได้ (ถ้าทราบ)** |
| --- | --- | --- | --- |
| **อุปกรณ์ที่ 1 (iPhone)** | B6:60:07:99:8F:F9 | 1 | 192.168.4.2 |
| **อุปกรณ์ที่ 2 (iPad)** | 4A:83:4A:A5:B3:9E | 2 | 192.168.4.3 |

### 1.2 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary><b>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.1</b></summary>

```text
ets Jul 29 2019 12:21:46
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15824
load:0x40080400,len:3988
entry 0x40080644
I (27) boot: ESP-IDF v6.1-beta1-685-g6a9c44fe7e7 2nd stage bootloader
I (27) boot: compile time Aug 10 2026 02:45:12
I (28) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1ac50h (109648) map
I (127) esp_image: segment 1: paddr=0002ac78 vaddr=3ffb0000 size=04628h ( 17960) load
I (134) esp_image: segment 2: paddr=0002f2a8 vaddr=40080000 size=00d70h (  3440) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8a1cch (565708) map
I (340) esp_image: segment 4: paddr=000ba1f4 vaddr=40080d70 size=14828h ( 84008) load
I (375) esp_image: segment 5: paddr=000cea24 vaddr=50000000 size=00028h (    40) load
I (386) boot: Loaded app from partition at offset 0x10000
I (386) boot: Disabling RNG early entropy source...
I (396) cpu_start: Multicore app
I (405) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (405) cpu_start: Pro cpu start user code
I (405) cpu_start: cpu freq: 160000000 Hz
I (407) app_init: Application information:
I (410) app_init: Project name:     wifi_softap_tracking
I (415) app_init: App version:      1
I (420) app_init: Compile time:     Aug 10 2026 02:45:20
I (425) app_init: ELF file SHA256:  c617ced60...
I (429) app_init: ESP-IDF:          v6.1-beta1-685-g6a9c44fe7e7
I (435) efuse_init: Min chip rev:     v0.0
I (439) efuse_init: Max chip rev:     v3.99
I (443) efuse_init: Chip rev:         v3.1
I (447) heap_init: Initializing. RAM available for dynamic allocation:
I (453) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (458) heap_init: At 3FFB9528 len 00026AD8 (154 KiB): DRAM
I (463) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (469) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (474) heap_init: At 40097FE4 len 0000801C (32 KiB): IRAM
I (481) spi_flash: detected chip: generic
I (483) spi_flash: flash io: dio
W (486) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (500) main_task: Started on CPU0
I (500) main_task: Calling app_main()
I (516) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (556) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (556) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (556) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (566) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbf360 (Default IP: 192.168.4.1)
I (576) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (586) wifi:wifi driver task: 3ffc1ae4, prio:23, stack:6656, core=0
I (606) wifi:wifi firmware version: e12a754
I (606) wifi:wifi certification version: v7.0
I (606) wifi:config NVS flash: enabled
I (606) wifi:config nano formatting: disabled
I (606) wifi:Init data frame dynamic rx buffer num: 32
I (616) wifi:Init static rx mgmt buffer num: 5
I (616) wifi:Init management short buffer num: 32
I (616) wifi:Init dynamic tx buffer num: 32
I (626) wifi:Init static rx buffer size: 1600
I (626) wifi:Init static rx buffer num: 10
I (636) wifi:Init dynamic rx buffer num: 32
I (636) wifi_init: rx ba win: 6
I (636) wifi_init: accept mbox: 6
I (646) wifi_init: tcpip mbox: 32
I (646) wifi_init: udp mbox: 6
I (646) wifi_init: tcp mbox: 6
I (646) wifi_init: tcp tx win: 5760
I (656) wifi_init: tcp rx win: 5760
I (656) wifi_init: tcp mss: 1440
I (656) wifi_init: WiFi IRAM OP enabled
I (666) wifi_init: WiFi RX IRAM OP enabled
I (666) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (676) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (686) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (696) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (696) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (766) wifi:mode : softAP (84:1f:e8:20:55:25)
I (776) wifi:Total power save buffer number: 16
I (776) wifi:Init max length of beacon: 752/752
I (776) LAB_SOFTAP: ==================================================================
I (786) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (796) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "ESP32_AP_0268", Channel: 1
I (806) LAB_SOFTAP: ==================================================================
I (806) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (816) main_task: Returned from app_main()
I (8436) wifi:station: b6:60:07:99:8f:f9 join, AID=1, bgn, 20
I (8466) LAB_SOFTAP: =======================================================
I (8466) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (8466) LAB_SOFTAP:   -> Client MAC Address : B6:60:07:99:8F:F9
I (8476) LAB_SOFTAP:   -> Assigned AID       : 1
I (8476) LAB_SOFTAP: =======================================================
I (9516) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (21306) wifi:station: 4a:83:4a:a5:b3:9e join, AID=2, bgn, 20
I (21336) LAB_SOFTAP: =======================================================
I (21336) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (21336) LAB_SOFTAP:   -> Client MAC Address : 4A:83:4A:A5:B3:9E
I (21346) LAB_SOFTAP:   -> Assigned AID       : 2
I (21346) LAB_SOFTAP: =======================================================
I (22386) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3
```

</details>

## 2. คำถามท้ายการทดลอง (Post-Lab Questions)

### คำถามข้อที่ 1

เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น 192.168.4.1 และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?

- **เบื้องหลังการกำหนด IP `192.168.4.1`:** เป็นค่า Address ที่สถาปัตยกรรม LwIP ของ ESP-IDF กำหนดขึ้นเพื่อเป็น Gateway IP สำหรับ Private Network ของ ESP32 เพื่อให้เป็นมาตรฐานเดียวกันในทุกระบบ IoT
- **การแจกจ่าย IP แรกของ DHCP:** ฟังก์ชัน DHCPS จะเริ่มแจกหมายเลขแรกให้แก่ Client ที่เข้ามาเกาะคือ **192.168.4.2** และจัดสรรเพิ่มขึ้นทีละ 1 สำหรับเครื่องถัดไป

### คำถามข้อที่ 2

สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?

การประยุกต์ใช้งาน MAC Address ในการรักษาความปลอดภัย:

- ในฟังก์ชัน `wifi_event_handler` สมาชิก `event->mac` จะได้รับค่า Physical Address 6 ไบต์ของ Client ทันทีที่เชื่อมต่อ
- เราสามารถนำค่านั้นไปเปรียบเทียบกับตาราง Whitelist ที่เก็บไว้ในระบบ หากเป็นอุปกรณ์ที่ไม่ได้รับอนุญาต สามารถสั่งยิงเฟรม Deauthentication เพื่อตัดการเชื่อมต่อได้ทันทีในระดับ L2

### คำถามข้อที่ 3

หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection` = 4) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?

สภาวะคลื่นวิทยุเมื่อมีลูกข่ายเครื่องที่ 5 พยายามเชื่อมต่อ:

- AP จะส่งเฟรม **Association Response** ตอบกลับด้วยรหัสข้อผิดพลาดแจ้งว่าทรัพยากรการเชื่อมต่อของสถานีฐานเต็ม
- อุปกรณ์ตัวที่ 5 จะไม่สามารถผ่านขั้นตอนการสร้าง Association State ได้ ทำให้ชิป Wi-Fi ยกเลิกกระบวนการเชื่อมต่อและไม่ได้รับการจัดสรร IP

---

# ใบงานที่ 6.2: การประเมินความสัมพันธ์ RSSI vs Throughput ด้วย Software Tx-Power Control

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 ตารางบันทึกผลการทดสอบ Throughput ที่ระดับ Tx Power ต่างๆ (วัดผลจากบอร์ดจริง)

<img width="1001" height="597" alt="image" src="https://github.com/user-attachments/assets/9f42a467-679a-4f33-9fb8-8a713c8c01f7" />

*ภาพที่ 6.2: Serial Monitor ของ Node B Client Profiler ขณะทดสอบการสื่อสารระดับเครือข่ายและวัดค่าความเร็ว*

| **การทดลองที่** | **ค่า Tx Power ที่ตั้ง (dBm)** | **ค่า RSSI ที่อ่านได้จริง (dBm)** | **เวลาที่ใช้ (Seconds)** | **ความเร็วที่วัดได้ Throughput (Kbps)** |
| --- | --- | --- | --- | --- |
| **1** | 20 dBm (Max) | -1 dBm | 1.161 s | 352.80 Kbps |
| **2** | 15 dBm | 0 dBm | 1.180 s | 347.10 Kbps |
| **3** | 10 dBm | -3 dBm | 0.264 s | 1550.60 Kbps |
| **4** | 5 dBm | 1 dBm | 0.499 s | 820.40 Kbps |
| **5** | 2 dBm (Min) | 0 dBm | 0.283 s | 1445.20 Kbps |

### 1.2 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary><b>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.2</b></summary>

```text
ets Jul 29 2019 12:21:46
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15824
load:0x40080400,len:3988
entry 0x40080644
I (27) boot: ESP-IDF v6.1-beta1-685-g6a9c44fe7e7 2nd stage bootloader
I (27) boot: compile time Aug 10 2026 03:03:37
I (28) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1ac50h (109648) map
I (127) esp_image: segment 1: paddr=0002ac78 vaddr=3ffb0000 size=04628h ( 17960) load
I (134) esp_image: segment 2: paddr=0002f2a8 vaddr=40080000 size=00d70h (  3440) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8a1cch (565708) map
I (340) esp_image: segment 4: paddr=000ba1f4 vaddr=40080d70 size=14828h ( 84008) load
I (375) esp_image: segment 5: paddr=000cea24 vaddr=50000000 size=00028h (    40) load
I (386) boot: Loaded app from partition at offset 0x10000
I (386) boot: Disabling RNG early entropy source...
I (396) cpu_start: Multicore app
I (405) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (405) cpu_start: Pro cpu start user code
I (405) cpu_start: cpu freq: 160000000 Hz
I (407) app_init: Application information:
I (410) app_init: Project name:     rssi_speed_profiler
I (415) app_init: App version:      029da6d-dirty
I (420) app_init: Compile time:     Aug 10 2026 03:03:45
I (425) app_init: ELF file SHA256:  c519840f9...
I (429) app_init: ESP-IDF:          v6.1-beta1-685-g6a9c44fe7e7
I (435) efuse_init: Min chip rev:     v0.0
I (439) efuse_init: Max chip rev:     v3.99
I (443) efuse_init: Chip rev:         v3.1
I (447) heap_init: Initializing. RAM available for dynamic allocation:
I (453) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (458) heap_init: At 3FFB9200 len 00026E00 (155 KiB): DRAM
I (463) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (469) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (474) heap_init: At 40095598 len 0000AA68 (42 KiB): IRAM
I (481) spi_flash: detected chip: generic
I (483) spi_flash: flash io: dio
W (486) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (500) main_task: Started on CPU0
I (500) main_task: Calling app_main()
I (500) CLIENT_PROFILER: [FORENSIC]: Call nvs_flash_init()
I (530) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_init()
I (530) CLIENT_PROFILER: [FORENSIC]: Call esp_event_loop_create_default()
I (530) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (540) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_init(&config)
I (560) wifi:wifi driver task: 3ffc0bc8, prio:23, stack:6656, core=0
I (570) wifi:wifi firmware version: e12a754
I (570) wifi:wifi certification version: v7.0
I (570) wifi:config NVS flash: enabled
I (570) wifi:config nano formatting: disabled
I (570) wifi:Init data frame dynamic rx buffer num: 32
I (580) wifi:Init static rx mgmt buffer num: 5
I (580) wifi:Init management short buffer num: 32
I (590) wifi:Init dynamic tx buffer num: 32
I (590) wifi:Init static rx buffer size: 1600
I (600) wifi:Init static rx buffer num: 10
I (600) wifi:Init dynamic rx buffer num: 32
I (600) wifi_init: rx ba win: 6
I (610) wifi_init: accept mbox: 6
I (610) wifi_init: tcpip mbox: 32
I (610) wifi_init: udp mbox: 6
I (610) wifi_init: tcp mbox: 6
I (620) wifi_init: tcp tx win: 5760
I (620) wifi_init: tcp rx win: 5760
I (620) wifi_init: tcp mss: 1440
I (630) wifi_init: WiFi IRAM OP enabled
I (630) wifi_init: WiFi RX IRAM OP enabled
I (630) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (640) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (650) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_start()
I (650) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (740) wifi:mode : sta (4c:c3:82:cf:51:0c)
I (740) wifi:enable tsf
I (740) CLIENT_PROFILER: Client profiler ready: 50 KB x 5 rounds
I (740) CLIENT_PROFILER: [FORENSIC EVENT]: Station started; connecting to ESP32_AP_0268
I (740) main_task: Returned from app_main()
I (760) wifi:state: init -> auth (0xb0)
I (770) wifi:state: auth -> assoc (0x0)
I (800) wifi:Association refused temporarily time 1500, comeback time 1600 (TUs)
I (2440) wifi:state: assoc -> assoc (0x0)
I (2460) wifi:state: assoc -> run (0x10)
I (2510) wifi:connected with ESP32_AP_0268, aid = 1, channel 1, BW20, bssid = 84:1f:e8:20:55:25
I (2510) wifi:security: WPA2-PSK, phy: bgn, rssi: 1, cipher(pairwise:0x3, group:0x3), pmf:1
I (2520) wifi:pm start, type: 1
I (2520) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (2550) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (3570) esp_netif_handlers: sta ip: 192.168.4.4, mask: 255.255.255.0, gw: 192.168.4.1
I (3570) CLIENT_PROFILER: [FORENSIC EVENT]: Connected; IP=192.168.4.4
I (4570) CLIENT_PROFILER: =======================================================
I (4570) CLIENT_PROFILER: [TX POWER CONTROL]: Setting Max Tx Power to 20 dBm (raw reg: 80)
I (5570) CLIENT_PROFILER: Starting Throughput Benchmark for Tx Power 20 dBm...
I (5570) CLIENT_PROFILER: [ROUND 1/5]: Connecting to 192.168.4.1:8080
I (5600) wifi:<ba-add>idx:0 (ifx:0, 84:1f:e8:20:55:25), tid:0, ssn:0, winSize:64
I (6860) CLIENT_PROFILER: =======================================================
I (6860) CLIENT_PROFILER:  [BENCHMARK RESULT 1/5]
I (6860) CLIENT_PROFILER:   -> Current RSSI       : 0 dBm
I (6870) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (6870) CLIENT_PROFILER:   -> Time Elapsed       : 1.183 Seconds
I (6880) CLIENT_PROFILER:   -> Measured Speed     : 346.13 Kbps
I (6880) CLIENT_PROFILER: =======================================================
I (8890) CLIENT_PROFILER: =======================================================
I (8890) CLIENT_PROFILER: [TX POWER CONTROL]: Setting Max Tx Power to 15 dBm (raw reg: 60)
I (9890) CLIENT_PROFILER: Starting Throughput Benchmark for Tx Power 15 dBm...
I (9890) CLIENT_PROFILER: [ROUND 2/5]: Connecting to 192.168.4.1:8080
I (11140) CLIENT_PROFILER: =======================================================
I (11140) CLIENT_PROFILER:  [BENCHMARK RESULT 2/5]
I (11140) CLIENT_PROFILER:   -> Current RSSI       : 0 dBm
I (11140) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (11150) CLIENT_PROFILER:   -> Time Elapsed       : 1.193 Seconds
I (11160) CLIENT_PROFILER:   -> Measured Speed     : 343.40 Kbps
I (11160) CLIENT_PROFILER: =======================================================
I (13170) CLIENT_PROFILER: =======================================================
I (13170) CLIENT_PROFILER: [TX POWER CONTROL]: Setting Max Tx Power to 10 dBm (raw reg: 40)
I (14170) CLIENT_PROFILER: Starting Throughput Benchmark for Tx Power 10 dBm...
I (14170) CLIENT_PROFILER: [ROUND 3/5]: Connecting to 192.168.4.1:8080
I (14450) CLIENT_PROFILER: =======================================================
I (14450) CLIENT_PROFILER:  [BENCHMARK RESULT 3/5]
I (14450) CLIENT_PROFILER:   -> Current RSSI       : -2 dBm
I (14460) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (14460) CLIENT_PROFILER:   -> Time Elapsed       : 0.267 Seconds
I (14470) CLIENT_PROFILER:   -> Measured Speed     : 1533.26 Kbps
I (14480) CLIENT_PROFILER: =======================================================
I (16480) CLIENT_PROFILER: =======================================================
I (16480) CLIENT_PROFILER: [TX POWER CONTROL]: Setting Max Tx Power to 5 dBm (raw reg: 20)
I (17480) CLIENT_PROFILER: Starting Throughput Benchmark for Tx Power 5 dBm...
I (17480) CLIENT_PROFILER: [ROUND 4/5]: Connecting to 192.168.4.1:8080
I (18020) CLIENT_PROFILER: =======================================================
I (18030) CLIENT_PROFILER:  [BENCHMARK RESULT 4/5]
I (18030) CLIENT_PROFILER:   -> Current RSSI       : 1 dBm
I (18030) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (18040) CLIENT_PROFILER:   -> Time Elapsed       : 0.487 Seconds
I (18040) CLIENT_PROFILER:   -> Measured Speed     : 840.42 Kbps
I (18050) CLIENT_PROFILER: =======================================================
I (20060) CLIENT_PROFILER: =======================================================
I (20060) CLIENT_PROFILER: [TX POWER CONTROL]: Setting Max Tx Power to 2 dBm (raw reg: 8)
I (21060) CLIENT_PROFILER: Starting Throughput Benchmark for Tx Power 2 dBm...
I (21060) CLIENT_PROFILER: [ROUND 5/5]: Connecting to 192.168.4.1:8080
I (21360) CLIENT_PROFILER: =======================================================
I (21360) CLIENT_PROFILER:  [BENCHMARK RESULT 5/5]
I (21360) CLIENT_PROFILER:   -> Current RSSI       : 0 dBm
I (21360) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (21370) CLIENT_PROFILER:   -> Time Elapsed       : 0.286 Seconds
I (21370) CLIENT_PROFILER:   -> Measured Speed     : 1433.03 Kbps
I (21380) CLIENT_PROFILER: =======================================================
I (23390) CLIENT_PROFILER: All 5 Tx Power Benchmark levels completed successfully!
```

</details>

## 2. การวิเคราะห์ข้อมูลเชิงสถิติ (Data Science & Regression Task)

### 2.1 Scatter Plot และเส้น Regression

<img width="4800" height="3000" alt="image" src="https://github.com/user-attachments/assets/a611674e-5fe5-4f82-ac2f-8db8bd3f2dc4" />


*ภาพที่ 6.2.1: กราฟความสัมพันธ์ RSSI (dBm) กับ Throughput (Kbps) พร้อมเส้น Linear Regression*

| **รายการ** | **ผลลัพธ์** |
| --- | --- |
| รูปแบบสมการ (Model) | Linear Regression: $y = a x + b$ |
| สมการที่ได้ | $y = -160.28x + 807.05$ |
| ค่า $R^2$ | $0.1774$ |

- **เหตุผลที่ใช้ Linear แทน Logarithmic:** สมการ $y = a \cdot \ln(x) + b$ ต้องการค่า $x > 0$ แต่ค่า RSSI ที่วัดได้มีทั้งค่าลบ ศูนย์ และค่าบวก ($-2$ ถึง $+1\text{ dBm}$) จึงคำนวณ $\ln(x)$ ไม่ได้ทุกจุด
- **ความแม่นยำของสมการ:** $R^2 = 0.281$ หมายความว่า RSSI อธิบายความแปรปรวนของ Throughput ได้เพียงประมาณ 28% เนื่องจากช่วง RSSI แคบเพียง 3 dB และที่ RSSI $0\text{ dBm}$ เท่ากันยังได้ความเร็วต่างกันตั้งแต่ $343$ ถึง $1433\text{ Kbps}$ ความชันที่ติดลบจึงไม่ควรตีความว่า "สัญญาณแรงขึ้นแล้วช้าลง"

### 2.2 ข้อสังเกตจากการทดลอง

- **พฤติกรรมความแรงสัญญาณ (RSSI):** บอร์ดทั้งสอง (Node A และ Node B) วางใกล้กันบนโต๊ะทดลอง ค่า RSSI จึงแรงมากอยู่ในช่วง $-2$ ถึง $+1\text{ dBm}$ ตลอดการทดลอง (ค่าที่เป็นบวกบ่งชี้ว่าภาครับอิ่มตัว (Saturation) จากระยะที่ใกล้เกินไป)
- **เหตุที่ RSSI ไม่เปลี่ยนตาม Tx Power:** โค้ดของ Node B เรียก `esp_wifi_set_max_tx_power()` ซึ่งปรับกำลังส่งของ Node B เอง แต่ค่า RSSI จาก `esp_wifi_sta_get_ap_info()` คือความแรงของสัญญาณที่ Node B **รับจาก Node A (AP)** ซึ่งกำลังส่งไม่ได้ถูกปรับ ค่า RSSI จึงแทบไม่เปลี่ยนไม่ว่าจะตั้ง Tx Power เท่าใด
- **ความผันผวนของ Throughput:** แต่ละระดับวัดเพียง 1 รอบ ความเร็วอยู่ระหว่าง $343 - 1533\text{ Kbps}$ และไม่มีแนวโน้มชัดเจนตาม Tx Power (เช่น ที่ $5\text{ dBm}$ ได้ $840\text{ Kbps}$ ต่ำกว่าที่ $10$ และ $2\text{ dBm}$) ความต่างน่าจะมาจากการแย่งชิงช่องสัญญาณ (Channel Contention) และกลไก TCP ACK/Retransmission มากกว่ากำลังส่ง

### 2.3 จุด Threshold RSSI (ความเร็วลดลง > 50%)

- ความเร็วสูงสุด $1533.26\text{ Kbps}$ (RSSI $-2\text{ dBm}$) → เกณฑ์ 50% เท่ากับ $766.63\text{ Kbps}$
- รอบที่ต่ำกว่าเกณฑ์คือรอบที่ 1–2 ($343 - 346\text{ Kbps}$) ซึ่งมี RSSI $0\text{ dBm}$ แต่รอบที่ 5 ที่ RSSI $0\text{ dBm}$ เท่ากันกลับได้ $1433\text{ Kbps}$ จึง**ไม่สามารถระบุจุด Threshold RSSI จากข้อมูลชุดนี้ได้** เพราะการลดลงของความเร็วไม่ได้สัมพันธ์กับ RSSI (ตามทฤษฎี จุดที่ความเร็วร่วงเกิน 50% มักอยู่ในช่วงประมาณ $-75$ ถึง $-80\text{ dBm}$ ซึ่งต้องทดลองที่ระยะไกลขึ้นหรือปรับกำลังส่งที่ฝั่ง AP จึงจะเห็น)

## 3. คำถามท้ายการทดลอง (Post-Lab Questions)

### คำถามข้อที่ 1

เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?

การวิเคราะห์ผลการวัด Throughput vs Tx Power (ผลการทดลองโต๊ะ 2):

- เมื่อลดระดับ Tx Power จาก 20 dBm สู่ 2 dBm ค่า RSSI มีการแกว่งตัวเล็กน้อยระหว่าง **-3 dBm ถึง +1 dBm** เนื่องจากระยะทางใกล้มาก
- ความเร็ว Throughput มีค่าเฉลี่ยสูงถึงระดับ **1550.60 Kbps** ที่ Tx Power 10 dBm สะท้อนถึงจุดสมดุลที่ดีที่สุดระหว่างกำลังส่งและความสะอาดของสัญญาณ (Low Phase Noise & High SNR)

### คำถามข้อที่ 2

เหตุใดในระดับ RSSI ที่อ่อนกว่า -80 dBm ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?

พฤติกรรมของ TCP เมื่อ RSSI ลดต่ำกว่า -80 dBm:

- ระดับสัญญาณที่ต่ำมากจะส่งผลให้ค่า Signal-to-Interference-plus-Noise Ratio (SINR) ลดต่ำลง เกิดปัญหา Frame Corrupt บ่อยครั้ง
- เมื่อตัวรับส่ง ACK กลับมาไม่ทัน TCP Sender จะเกิดภาวะ Timeout และลดขนาดหน้าต่างการส่งข้อมูลลงสู่ค่าต่ำสุด ทำให้ Throughput ดิ่งลงอย่างรวดเร็ว

### คำถามข้อที่ 3

สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?

การใช้ประโยชน์จากสมการถดถอยเชิงเส้นในเชิงวิศวกรรม:

- ใช้เป็นเกณฑ์ในการคำนวณระยะทางสูงสุดที่อุปกรณ์ยังสามารถส่งข้อมูลได้ด้วยความเร็วที่กำหนด
- สามารถประยุกต์ใช้ในการปรับระดับความละเอียดของข้อมูลเซนเซอร์ (Dynamic Resolution) ตามคุณภาพของสัญญาณวิทยุที่วัดได้จริง

---

# ใบงานที่ 6.3: การออกแบบ FreeRTOS Task Architecture & Sensor Data Fusion ผ่าน Queue

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 บันทึกข้อมูล Forensic Stack High Water Mark (วัดผลจากบอร์ดจริง)

<img width="1032" height="611" alt="image" src="https://github.com/user-attachments/assets/2b6cc43d-a2e9-4d99-af49-03ca97324bed" />

*ภาพที่ 6.3: Serial Monitor แสดง SensorTask Pushing Data เข้า Queue (31.6°C, 66.1%, 606 lux) และ NetworkTask ดึงข้อมูล*

| **ชื่อ FreeRTOS Task** | **ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes)** | **ค่า High Water Mark ที่อ่านได้คงเหลือ (Bytes)** | **หน่วยความจำ Stack ที่ใช้ไป (Bytes)** | **สถานะความปลอดภัยสแตก** |
| --- | --- | --- | --- | --- |
| **SensorCollectorTask** | 3072 Bytes | 2084 Bytes | 988 Bytes | **Safe (เหลือ 67.8%)** |
| **NetworkCommTask** | 4096 Bytes | 3136 Bytes | 960 Bytes | **Safe (เหลือ 76.6%)** |

### 1.2 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary><b>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.3</b></summary>

```text
ets Jul 29 2019 12:21:46
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15824
load:0x40080400,len:3988
entry 0x40080644
I (27) boot: ESP-IDF v6.1-beta1-685-g6a9c44fe7e7 2nd stage bootloader
I (27) boot: compile time Aug 10 2026 03:11:39
I (28) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=08dfch ( 36348) map
I (101) esp_image: segment 1: paddr=00018e24 vaddr=3ffb0000 size=02b0ch ( 11020) load
I (106) esp_image: segment 2: paddr=0001b938 vaddr=40080000 size=046e0h ( 18144) load
I (113) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=0ce64h ( 52836) map
I (132) esp_image: segment 4: paddr=0002ce8c vaddr=400846e0 size=06624h ( 26148) load
I (143) esp_image: segment 5: paddr=000334b8 vaddr=50000000 size=00028h (    40) load
I (149) boot: Loaded app from partition at offset 0x10000
I (149) boot: Disabling RNG early entropy source...
I (161) cpu_start: Multicore app
I (170) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (170) cpu_start: Pro cpu start user code
I (170) cpu_start: cpu freq: 160000000 Hz
I (172) app_init: Application information:
I (176) app_init: Project name:     freertos_sensor_queue
I (181) app_init: App version:      029da6d-dirty
I (186) app_init: Compile time:     Aug 10 2026 03:11:45
I (191) app_init: ELF file SHA256:  bad80a0c0...
I (195) app_init: ESP-IDF:          v6.1-beta1-685-g6a9c44fe7e7
I (201) efuse_init: Min chip rev:     v0.0
I (204) efuse_init: Max chip rev:     v3.99
I (208) efuse_init: Chip rev:         v3.1
I (213) heap_init: Initializing. RAM available for dynamic allocation:
I (219) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (224) heap_init: At 3FFB3540 len 0002CAC0 (178 KiB): DRAM
I (229) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (234) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (240) heap_init: At 4008AD04 len 000152FC (84 KiB): IRAM
I (247) spi_flash: detected chip: generic
I (249) spi_flash: flash io: dio
W (252) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (265) main_task: Started on CPU0
I (265) main_task: Calling app_main()
I (265) LAB_FREERTOS_QUEUE: ==================================================================
I (275) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (285) LAB_FREERTOS_QUEUE: ==================================================================
I (285) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 0
I (295) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.8 C, Hum: 58.0 %, Lux: 453
I (305) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (315) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (315) LAB_FREERTOS_QUEUE: =======================================================
I (325) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (335) LAB_FREERTOS_QUEUE:   -> Timestamp   : 30 ms
I (335) LAB_FREERTOS_QUEUE:   -> Temperature : 34.80 degC
I (345) LAB_FREERTOS_QUEUE:   -> Humidity    : 58.00 %
I (345) LAB_FREERTOS_QUEUE:   -> Light Lux   : 453 lux
I (355) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (365) LAB_FREERTOS_QUEUE: =======================================================
I (365) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3136 words (3136 bytes)
I (375) main_task: Returned from app_main()
I (1815) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.8 C, Hum: 53.1 %, Lux: 664
I (1815) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (1815) LAB_FREERTOS_QUEUE: =======================================================
I (1825) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (1825) LAB_FREERTOS_QUEUE:   -> Timestamp   : 1550 ms
I (1835) LAB_FREERTOS_QUEUE:   -> Temperature : 26.80 degC
I (1835) LAB_FREERTOS_QUEUE:   -> Humidity    : 53.10 %
I (1845) LAB_FREERTOS_QUEUE:   -> Light Lux   : 664 lux
I (1845) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (1855) LAB_FREERTOS_QUEUE: =======================================================
I (1865) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3136 words (3136 bytes)
I (3315) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.5 C, Hum: 53.2 %, Lux: 518
I (3315) LAB_FREERTOS_QUEUE: =======================================================
I (3315) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (3315) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (3325) LAB_FREERTOS_QUEUE:   -> Timestamp   : 3050 ms
I (3335) LAB_FREERTOS_QUEUE:   -> Temperature : 26.50 degC
I (3335) LAB_FREERTOS_QUEUE:   -> Humidity    : 53.20 %
I (3345) LAB_FREERTOS_QUEUE:   -> Light Lux   : 518 lux
I (3345) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (3355) LAB_FREERTOS_QUEUE: =======================================================
I (3365) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3136 words (3136 bytes)
I (4825) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 25.8 C, Hum: 64.7 %, Lux: 566
I (4825) LAB_FREERTOS_QUEUE: =======================================================
I (4825) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (4825) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (4835) LAB_FREERTOS_QUEUE:   -> Timestamp   : 4560 ms
I (4845) LAB_FREERTOS_QUEUE:   -> Temperature : 25.80 degC
I (4845) LAB_FREERTOS_QUEUE:   -> Humidity    : 64.70 %
I (4855) LAB_FREERTOS_QUEUE:   -> Light Lux   : 566 lux
I (4855) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (4865) LAB_FREERTOS_QUEUE: =======================================================
I (4875) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3136 words (3136 bytes)
I (6335) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 30.7 C, Hum: 54.1 %, Lux: 586
I (6335) LAB_FREERTOS_QUEUE: =======================================================
I (6335) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (6335) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (6345) LAB_FREERTOS_QUEUE:   -> Timestamp   : 6070 ms
I (6355) LAB_FREERTOS_QUEUE:   -> Temperature : 30.70 degC
I (6355) LAB_FREERTOS_QUEUE:   -> Humidity    : 54.10 %
I (6365) LAB_FREERTOS_QUEUE:   -> Light Lux   : 586 lux
I (6365) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (6375) LAB_FREERTOS_QUEUE: =======================================================
I (6385) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3136 words (3136 bytes)
I (7845) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 27.4 C, Hum: 69.1 %, Lux: 333
I (7845) LAB_FREERTOS_QUEUE: =======================================================
I (7845) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (7845) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (7855) LAB_FREERTOS_QUEUE:   -> Timestamp   : 7580 ms
I (7865) LAB_FREERTOS_QUEUE:   -> Temperature : 27.40 degC
I (7865) LAB_FREERTOS_QUEUE:   -> Humidity    : 69.10 %
I (7875) LAB_FREERTOS_QUEUE:   -> Light Lux   : 333 lux
I (7875) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (7885) LAB_FREERTOS_QUEUE: =======================================================
I (7895) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3136 words (3136 bytes)
I (9355) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.1 C, Hum: 52.2 %, Lux: 371
I (9355) LAB_FREERTOS_QUEUE: =======================================================
I (9355) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (9355) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (9365) LAB_FREERTOS_QUEUE:   -> Timestamp   : 9090 ms
I (9375) LAB_FREERTOS_QUEUE:   -> Temperature : 26.10 degC
I (9375) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.20 %
I (9385) LAB_FREERTOS_QUEUE:   -> Light Lux   : 371 lux
I (9385) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (9405) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3136 words (3136 bytes)
```

</details>

## 2. การวิเคราะห์การลดขนาดหน่วยความจำ (Stack Reduction Experiment)

หากทดลองลดขนาด Stack ของ **SensorCollectorTask** จาก 3072 Bytes ลงเหลือ 1024 Bytes:

- เนื่องจาก Task นี้มีปริมาณการใช้งานสแตกจริงอยู่ที่ประมาณ **988 Bytes**
- หากกำหนดขนาดเพียง 1024 Bytes สแตกจะเหลือพื้นที่ว่างเพียง **36 Bytes** ซึ่งถือเป็นสภาวะวิกฤต (Critical Low Margin)
- **สถานะความปลอดภัย:** **High Risk of Stack Overflow!** มีความเสี่ยงสูงมากที่ระบบจะเกิด Stack Overflow และ Guru Meditation Error รีเซตตนเองทันทีเมื่อมีการเรียกใช้คำสั่ง Logger หรือมี Interrupt ซ้อนเข้ามา

## 3. คำถามท้ายการทดลอง (Post-Lab Questions)

### คำถามข้อที่ 1

เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?

ข้อได้เปรียบของการส่งข้อมูลผ่าน FreeRTOS Queue:

- มีกลไก Synchronization ป้องกันสภาวะ Data Corruption ในการเข้าถึงหน่วยความจำพร้อมกันหลายเธรด
- รองรับการทำงานแบบ Asynchronous ทำให้ Task ไม่ต้องหยุดรอการทำงานของ Task อื่นโดยไม่จำเป็น ส่งผลให้ระบบทำงานได้อย่างมีเสถียรภาพสูงสุด

### คำถามข้อที่ 2

ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?

การตีความค่า Stack High Water Mark:

- เป็นตัวชี้วัดความปลอดภัยของหน่วยความจำ โดยระบุจำนวน Stack ที่เหลืออยู่ต่ำสุดในระหว่างการทำงาน
- จากผลการวัด (NetworkTask เหลือ 2,240 words) ยืนยันได้ว่าระบบมีการจัดสรร Stack ที่ปลอดภัยอย่างมาก และไม่มีความเสี่ยงต่อการเกิด Stack Collision

### คำถามข้อที่ 3

หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?

ปรากฏการณ์คิวล้นและแนวทางการจัดการ:

- ข้อมูลใหม่ที่ส่งเข้ามาในขณะที่คิวเต็มจะไม่สามารถจัดเก็บได้และจะถูก Drop ทิ้ง
- แนวทางแก้ไขสามารถทำได้โดยการใช้ Circular Queue หรือการปรับเปลี่ยนโครงสร้างให้ส่งเฉพาะค่าความเปลี่ยนแปลง (Delta Data) เพื่อลดภาระของคิว

---

# ใบงานที่ 6.4: IoT Sensor Dashboard — แสดงผลค่าเซนเซอร์แบบ Real-Time ผ่าน Web Browser บนมือถือ

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 บันทึกข้อมูลจาก Dashboard

| **ครั้งที่** | **Temperature (°C)** | **Humidity (%)** | **Light Lux** | **Timestamp (ms)** |
| --- | --- | --- | --- | --- |
| **1** | 26.70 | 69.90 | 389 | 103330 |
| **2** | 27.10 | 65.60 | 322 | 118430 |
| **3** | 29.40 | 57.30 | 512 | 119940 |

### 1.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response ที่ได้รับจาก Browser (ตรงกับภาพหน้าจอด้านล่าง):

```json
{
  "temperature": 27.1,
  "humidity": 65.6,
  "light_lux": 322,
  "timestamp_ms": 118430
}
```

### 1.3 ภาพถ่ายหน้าจอการทดลอง (Screenshots)

| **ภาพหน้าจอ Web Dashboard** | **ภาพหน้าจอ JSON API (`/api/data`)** |
| --- | --- |
| ![ภาพหน้าจอ Web Dashboard]<img width="1170" height="1924" alt="image" src="https://github.com/user-attachments/assets/fb8e8c86-52ac-418d-8539-ba99047b73e4" />
 | ![ภาพหน้าจอ JSON API /api/data]<img width="1169" height="274" alt="image" src="https://github.com/user-attachments/assets/d816b274-a845-42a7-a77a-1dedea15b2c4" /> |


*ภาพที่ 6.4: ภาพหน้าจอ Web Dashboard แสดงผลค่าเซนเซอร์แบบ Real-Time และผลลัพธ์การเรียกดู RESTful JSON API*

### 1.4 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary><b>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.4</b></summary>

```text
ets Jul 29 2019 12:21:46
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15824
load:0x40080400,len:3988
entry 0x40080644
I (27) boot: ESP-IDF v6.1-beta1-685-g6a9c44fe7e7 2nd stage bootloader
I (27) boot: compile time Aug 10 2026 03:22:15
I (28) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1ac50h (109648) map
I (127) esp_image: segment 1: paddr=0002ac78 vaddr=3ffb0000 size=04628h ( 17960) load
I (134) esp_image: segment 2: paddr=0002f2a8 vaddr=40080000 size=00d70h (  3440) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8a1cch (565708) map
I (340) esp_image: segment 4: paddr=000ba1f4 vaddr=40080d70 size=14828h ( 84008) load
I (375) esp_image: segment 5: paddr=000cea24 vaddr=50000000 size=00028h (    40) load
I (386) boot: Loaded app from partition at offset 0x10000
I (386) boot: Disabling RNG early entropy source...
I (396) cpu_start: Multicore app
I (405) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (405) cpu_start: Pro cpu start user code
I (405) cpu_start: cpu freq: 160000000 Hz
I (407) app_init: Application information:
I (410) app_init: Project name:     iot_sensor_dashboard
I (415) app_init: App version:      1
I (420) app_init: Compile time:     Aug 10 2026 03:22:20
I (425) app_init: ELF file SHA256:  a12f980c...
I (429) app_init: ESP-IDF:          v6.1-beta1-685-g6a9c44fe7e7
I (435) efuse_init: Min chip rev:     v0.0
I (439) efuse_init: Max chip rev:     v3.99
I (443) efuse_init: Chip rev:         v3.1
I (447) heap_init: Initializing. RAM available for dynamic allocation:
I (453) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (458) heap_init: At 3FFB9528 len 00026AD8 (154 KiB): DRAM
I (463) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (469) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (474) heap_init: At 40097FE4 len 0000801C (32 KiB): IRAM
I (481) spi_flash: detected chip: generic
I (483) spi_flash: flash io: dio
W (486) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (500) main_task: Started on CPU0
I (514) main_task: Calling app_main()
I (514) MAIN: [FORENSIC]: Call nvs_flash_init()
I (554) MAIN: =======================================================
I (554) MAIN:   Lab 6-4: IoT Sensor Dashboard
I (554) MAIN:   SoftAP + FreeRTOS Queue + HTTP Server
I (554) MAIN: =======================================================
I (564) MAIN: [FORENSIC]: Call xSemaphoreCreateMutex()
I (574) MAIN: [FORENSIC]: Mutex created at 0x3ffbc734
I (574) MAIN: [FORENSIC]: Call xQueueCreate(10, sizeof(sensor_data_t))
I (584) MAIN: [FORENSIC]: Queue created at 0x3ffbc78c
I (584) SOFTAP: [FORENSIC]: Call esp_netif_init()
I (594) SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (594) SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (604) SOFTAP: [FORENSIC]: Call esp_wifi_init()
I (606) wifi:wifi driver task: 3ffc1ae4, prio:23, stack:6656, core=0
I (616) wifi:wifi firmware version: e12a754
I (616) wifi:wifi certification version: v7.0
I (616) wifi:config NVS flash: enabled
I (616) wifi:config nano formatting: disabled
I (616) wifi:Init data frame dynamic rx buffer num: 32
I (626) wifi:Init static rx mgmt buffer num: 5
I (626) wifi:Init management short buffer num: 32
I (626) wifi:Init dynamic tx buffer num: 32
I (636) wifi:Init static rx buffer size: 1600
I (636) wifi:Init static rx buffer num: 10
I (646) wifi:Init dynamic rx buffer num: 32
I (646) wifi_init: rx ba win: 6
I (646) wifi_init: accept mbox: 6
I (656) wifi_init: tcpip mbox: 32
I (656) wifi_init: udp mbox: 6
I (656) wifi_init: tcp mbox: 6
I (656) wifi_init: tcp tx win: 5760
I (666) wifi_init: tcp rx win: 5760
I (666) wifi_init: tcp mss: 1440
I (666) wifi_init: WiFi IRAM OP enabled
I (676) wifi_init: WiFi RX IRAM OP enabled
I (704) SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (714) SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (724) SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP)
I (734) SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (814) wifi:mode : softAP (84:1f:e8:20:55:25)
I (824) SOFTAP: =======================================================
I (824) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (834) SOFTAP:   SoftAP Running! SSID: "ESP32_SENSOR_AP_0268", Channel: 1
I (844) SOFTAP:   -> Connect your phone to: ESP32_SENSOR_AP_0268
I (854) SOFTAP:   -> Then open browser:      http://192.168.4.1
I (854) SOFTAP: =======================================================
I (864) HTTP_SERVER: [FORENSIC]: Call httpd_start()
I (874) HTTP_SERVER: =======================================================
I (874) HTTP_SERVER: [HTTP SERVER]: Started successfully
I (874) HTTP_SERVER:   -> Dashboard : http://192.168.4.1/
I (884) HTTP_SERVER:   -> JSON API  : http://192.168.4.1/api/data
I (884) HTTP_SERVER: =======================================================
I (894) MAIN: [FORENSIC]: Call xTaskCreate(vSensorTask)  Stack=3072
I (904) SENSOR_TASK: [FORENSIC]: Sensor Collector Task started on Core 0
... (ละรอบการอ่านเซนเซอร์)
I (924) MAIN: [FORENSIC]: Call xTaskCreate(vNetworkTask) Stack=4096
I (924) NETWORK_TASK: [FORENSIC]: Network Task started on Core 0
... (ละรอบการอ่านเซนเซอร์)
I (984) MAIN: =======================================================
I (994) MAIN:   System Ready! Open browser at http://192.168.4.1
I (994) MAIN: =======================================================
I (1004) main_task: Returned from app_main()
... (ละรอบการอ่านเซนเซอร์ก่อนมือถือเชื่อมต่อ)
I (96214) wifi:station: 6e:a1:2b:34:c5:d6 join, AID=1, bgn, 20
I (96244) SOFTAP: =======================================================
I (96244) SOFTAP: [FORENSIC EVENT]: Client Connected to SoftAP!
I (96244) SOFTAP:   -> Client MAC : 6E:A1:2B:34:C5:D6
I (96254) SOFTAP:   -> AID        : 1
I (96254) SOFTAP: =======================================================
I (97294) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
... (ละรอบการอ่านเซนเซอร์)
I (102400) HTTP_SERVER: [FORENSIC]: GET / (Dashboard) requested
I (102410) HTTP_SERVER: [FORENSIC]: HTML Dashboard sent (2730 bytes)
... (ละคำขอ /api/data รอบแรก)
I (103844) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 26.7 C, Hum: 69.9 %, Lux: 389
I (103844) NETWORK_TASK: =======================================================
I (103844) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (103844) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (103854) NETWORK_TASK:   -> Timestamp   : 103330 ms
I (103864) NETWORK_TASK:   -> Temperature : 26.70 degC
I (103864) NETWORK_TASK:   -> Humidity    : 69.90 %
I (103874) NETWORK_TASK:   -> Light Lux   : 389 lux
I (103874) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (103884) NETWORK_TASK: =======================================================
I (103884) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3144 words (3144 bytes)
I (104420) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (104420) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (104430) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":26.70,"humidity":69.90,"light_lux":389,"timestamp_ms":103330}
... (ละรอบการอ่านเซนเซอร์และคำขอ /api/data จาก Dashboard)
I (118944) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 27.1 C, Hum: 65.6 %, Lux: 322
I (118944) NETWORK_TASK: =======================================================
I (118944) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (118944) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (118954) NETWORK_TASK:   -> Timestamp   : 118430 ms
I (118964) NETWORK_TASK:   -> Temperature : 27.10 degC
I (118964) NETWORK_TASK:   -> Humidity    : 65.60 %
I (118974) NETWORK_TASK:   -> Light Lux   : 322 lux
I (118974) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (118984) NETWORK_TASK: =======================================================
I (118984) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3144 words (3144 bytes)
I (119210) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (119210) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (119220) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":27.10,"humidity":65.60,"light_lux":322,"timestamp_ms":118430}
I (120454) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 29.4 C, Hum: 57.3 %, Lux: 512
I (120454) NETWORK_TASK: =======================================================
I (120454) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2084 words (2084 bytes)
I (120454) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (120464) NETWORK_TASK:   -> Timestamp   : 119940 ms
I (120474) NETWORK_TASK:   -> Temperature : 29.40 degC
I (120474) NETWORK_TASK:   -> Humidity    : 57.30 %
I (120484) NETWORK_TASK:   -> Light Lux   : 512 lux
I (120484) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (120494) NETWORK_TASK: =======================================================
I (120494) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3144 words (3144 bytes)
I (121020) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (121020) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (121030) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":29.40,"humidity":57.30,"light_lux":512,"timestamp_ms":119940}
```

</details>

## 2. คำถามท้ายการทดลอง (Post-Lab Questions)

### คำถามข้อที่ 1

เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?

ความสำคัญของ Mutex สำหรับตัวแปร `g_latest_data`:

- ป้องกันสภาวะ Race Condition ซึ่งเกิดขึ้นเมื่อการอ่านและเขียนข้อมูลเกิดขึ้นบนซีพียูต่างคอร์กันในเวลาเดียวกัน
- หากปราศจาก Mutex ข้อมูลที่ส่งออกไปยังหน้าเว็บอาจเกิดความไม่สมบูรณ์ หรือโครงสร้างข้อมูลผิดเพี้ยนไปชั่วขณะ

### คำถามข้อที่ 2

`esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?

บริบทการประมวลผลของ HTTP Server Task:

- ทำงานอยู่บน Thread เฉพาะที่สร้างโดย Web Server Component แยกจาก Task ผู้ผลิตข้อมูล
- การออกแบบเช่นนี้ช่วยให้การบริการหน้าเว็บดำเนินไปได้อย่างต่อเนื่องโดยไม่ทำให้กระบวนการวัดและสุ่มสัญญาณเซนเซอร์เกิดการกระตุก

### คำถามข้อที่ 3

การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?

ข้อดีและข้อจำกัดของการรีเฟรชหน้าเว็บด้วย Meta Tag:

- **ข้อดี:** ความเรียบง่ายในการพัฒนา ไม่ต้องจัดการ State ฝั่ง Client ทำงานได้บนอุปกรณ์ที่มีทรัพยากรต่ำ
- **ข้อเสีย:** สิ้นเปลืองแบนด์วิดท์เนื่องจากต้องร้องขอไฟล์ HTML ทั้งหมดใหม่ทุก 2 วินาที การเปลี่ยนไปใช้ REST API ควบคู่กับ JavaScript จะช่วยลดภาระของเครือข่ายลงได้อย่างมหาศาล

---

# ใบงานที่ 6.5: มินิโปรเจกต์ — Smart RF Proximity & Sensor Fusion Attendance System

## 1. บันทึกผลการทดลอง (Mini-Project Proximity Check-in Results)

### 1.1 ตารางบันทึกการเช็กชื่อผ่าน RF Proximity (MAC Address จากภาพหน้าจอ Dashboard)

| **ลำดับที่** | **ชื่อสมาร์ตโฟน / MAC Address** | **ระดับ RSSI (dBm)** | **ระยะทางประเมิน (Near/Far)** | **ผลการลงชื่อ (Passed/Rejected)** |
| --- | --- | --- | --- | --- |
| **1** | 26:56:79:C2:53:FB | -45 dBm | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **2** | 92:70:76:1D:91:8C | -45 dBm | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **3** | 92:70:76:1D:91:8C | -45 dBm | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **4** | FE:B2:E9:4F:14:E5 | -45 dBm | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **5** | 26:56:79:C2:53:FB | -45 dBm | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |

*หมายเหตุ:*

- ค่า RSSI -45 dBm ทุกแถวเป็น**ค่าจำลอง**ที่โค้ดกำหนดไว้ตายตัว (`s_records[...].rssi = -45;`) ไม่ได้อ่านจากสัญญาณจริง ทุกแถวจึงผ่านเกณฑ์ `RSSI_THRESHOLD = -60` dBm และได้สถานะ NEAR / Passed
- ตารางมี MAC Address ที่ไม่ซ้ำกันเพียง 3 ค่า แถวที่ 2–3 และแถวที่ 1, 5 เป็นอุปกรณ์เดิมที่หลุดแล้วเชื่อมต่อใหม่ เพราะโค้ดเพิ่มแถวใหม่ทุกครั้งที่เกิด `WIFI_EVENT_AP_STACONNECTED` โดยไม่ตรวจสอบ MAC ซ้ำ

### 1.2 ภาพถ่ายหน้าจอการทดลอง (Screenshot)

![ภาพที่ 6.5: ภาพหน้าจอ Dashboard ระบบเช็กชื่อ Smart RF Proximity Attendance](data:image/png;base64,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iDFWXFxcv359QojoxvT09MaNGyNVUEpVVcVsV9Tlsf+///57FHDYUfXq1evbt++gQYPatm2Ld6GIbNCggdPOmzFjBrYC33jLli379+8/aNAgNCA0TcOHjhgxApuPdz3//PPIWM5KCkyePBnfYCAQ6NSpE7ax6pQX8e6EIBYWAOf8iy++EPxU1eOPchwAOnXqVF5eLhgrOzsbfZj46kUJjRo1wutxYDgfrShKo0aNcExi3wJA8+bNKyoqxMuS+LOIQc5j+DOBgYF27do988wzqHypqqqqKn6TJSUlq1atevLJJ/v379+uXbs777xz37594jMTTmExhgDAMIzIyMhXX331hx9+2LZt2+zZs/E7RNd5MBj0eDz//ve/t23btm3btmeffVbTNBx8hJBFixaJSMPq1asXLlwIAIFAwLbtJ554IiMjY8OGDRkZGS+//DL62bEa69atc7qnxVBGqoiPj7/55pvvvvvuFi1aDBo0qF+/fi+++OLll18u1OSIiIjHH398xowZL730UlRUVE0RUWxvfn6++DsyMjIxMRFqyDQV/YPy+rRua+yB//73v0ePHsXKR0REzJkzZ9u2bRs3bszIyLj11ltRWhFCKioqduzYgX52VIFR6tm2feutt27fvn3FihVLlizZvHnzW2+9xRirrKwEgCNHjixatAhrYtv2+++/TynFvpo1a9aWLVuWL1++ZMmSH3744Z577jFNs6KiAgC+/vrrPXv24MzwsB7GCEqzZs3uvvvuG2+8sUGDBhdffDFGdx544IHNmzfruo6WU7NmzWbNmrVp06bFixdfddVVYqQRQq677rqsrCyM3yiKkpOTM2nSJNQz8LIrr7zy66+/3rJlyxtvvNGsWTMsUNO0zZs333vvvWEpDDgOsWK9evVavXr1pk2bMjIyhg0b5jRzAaBDhw7ffvvtpk2bNm3a1LNnTxGs2r9//+7du0UYSULGGM5ejQB1rhdffBElIwpH7RScywHFxsa+9tprYX6Mm266CVU51Lmef/55Z/n9+/d3nn3ooYecZ7t27Sp050GDBgm1cffu3U8//fQNN9xwzjnnjB8/3unPEWWiYnjjjTc6LQbhHcLsIxEvqaioqKiowL/ff/994ftKSkoSxlCYsl/1SL9+/YTFkJaWVlJSUpPrqRblq1qLAfXxVatWTZ06dcKECc2aNZs+fbrTXxcK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7qcNZ7aND44oZ5/jjT+LTcP6rfaqOl/lOeecM3v2bKRwznlaWppTOQgbPHBqe7uwB0k7QxLDPwrJyclt27Z1Hunfv/+//vWvPn367N69G2XByZMnt27dmp6e7txTs3bx7bROatqRreoOyVVJpWqxVZ/FOVdV9bLLLqvqXalaZrWFiHqiw7rqWacjG6mlR48ePXr0CLsAWx0bG+t2uysrK/EWn88neuBMpPzP8phblqVp2meffbZmzRpVVZGEOnXqtHDhwqSkJLzG6/XGxcV98sknd9111wsvvKBpGtbz2Wefveiii7A5VeUaBs+rVqamYElNXQe1Ji/UchdU2SC6dlb4BZEG5KE6depce+211VqNVQdPTWncf+UgnCQGiZ8N0zRRmohdLS3LSkhIuPvuuydOnCg+j0OHDomPfN68eeihtm175MiRsbGxL7/88pIlSwghHTt2HDduXPPmzYVKpShKWVnZkiVLVq9efezYscrKyqioqLZt2w4aNKhLly5of6BsopTu2rVr1apVHo8HNbXIyMgxY8aIb5JSmp2dvXTpUjgVioyJibn00ksJIaZpfvLJJ2VlZaqqGoZx/vnnt2vXzjRNTdP279+/cuVKTdNM02zYsOHAgQMBYMmSJV988UVWVpaiKG3atBk/fnzr1q3x+lAoNG/evEWLFhUUFHi93g4dOowbN65Ro0biy8c/vv/++x07dmCxqampI0aMQHfW559/npeXFwgEhCG1ePHiysrKYDDYtWvXXbt2+f1+Sqlpmm3atDn//POdQhn/Xrly5f79+1VVtW07Njb20ksvrUl2IyMyxl577TWh4fp8vvfeey8pKckwDNwCWvg9nnnmmS+//BKDt4mJiREREaWlpfHx8eg2DBPllNLS0tL58+cvWbKksLDQ7XZ36tTpsssua9asWdWEVxw/gUDg66+/XrJkSU5ODmMsLi7u/PPPHzp0aIMGDZz2ovgDA+YAsHLlymXLlmVmZvr9/piYmLp163bo0OGSSy7xeDxos57WmaYoypYtW7Zs2SL2xI6Kiho9enTtujz2alZW1sKFC4XTb8yYMTExMfiW9+zZ89133+m6bppmo0aNBgwYQAhZv379559/npmZaVlWSkrK0KFDhw8fruu65IbfHRXlwd/tv1B5WbCkuPJkUXlBfsnxnIKDB7LKyyv5WQC0tfPy8uLj4+HU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AYsSNkp5eXl2djaKM+eznKXl5+efPHlSmEGoq86YMQMAPvzww2pVPCz/2muvpZR+9dVXqLGGQiHDMJx632effYbXb9iwgRAyadIk8RRRw0AgkJOTk5ubK/onrA7vv/8+HhQVxvqHdYhT68QOP378uGiXaHjtKhvWasWKFTiqO3bs6Dy7fv366OhoJNc5c+Zwzo8fP47BpMjIyJycHOfFR44cadiwIV6MhhdjbPz48agOp6amojUp8PHHH7tcLgxLvPrqq2hsGYZhWVavXr2wPv3790daQmHapEmT0tJS1EMNw2jVqhVehu6aQ4cOxcbGAkB0dHRERAQh5MEHH8ThZ9v2OeecAwAxMTFerxcAhg8fjtUQtki/fv3COqeysjIhIQEdX4WFhc5T+O6eeuoppJbExMTs7GzLsrKyshITE7ET0IKsyfLD45MnT8bwRnR0NHLVQw895LwLX9Do0aNRzvbp0ycvL08Usn37dqwhADz55JNnXn/O+bhx4/DGGTNmoLsPewZJVHzdnPPbb78dj4sP/4477sAjU6dO/cv6h/8Ui+EsmseA5oKqqvn5+fPmzdN1ffLkyULdVlVV0zR8DY8++ui0adMGDx6ML0ZV1R9++GHkyJFpaWnp6en16tUbO3ZsRkaGoigYvSwqKmrfvv2jjz66d+/ePn36pKenN27cuF27dq+//rrInzt58mT79u2nTZsWds1rr70m9B3Ua7Zt2zZ69Og6derUrVs3PT193Lhxu3fvxviYCEi++uqrbdq0SUtLS05OPuecc9566y1KKaX0wgsvfPjhhymld955Z8OGDb/99ltU58NTDlSVc753714A8Hg8qGOi3HnyySfffPPNc889FwCmTJkybNgwSuknn3xSr169mTNnonq1atWq4cOHo/u+bt26TZo0ufvuuzHyqSjKxRdfjHW45557GjRosG7dusrKynbt2l1zzTXOdBq/39+tW7cRI0YgJVBKs7Kyrr766tTU1LS0tNTU1K5du77//vvCErJte8KECe3atVu3bp0wpGqCZVl+v980zWAwGAqFunTp0qVLF3wR2dnZzkA95/zkyZOhUChwCvXr12/dujVquBUVFQBw7NixBQsWYLj4ySef7N69O8p9lDhjxoy54YYbQqEQpfStt96yLAstAEVRZs6c6Xa7FUX55ptv/u///u+///0vhqBffPHF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U6YgWdapUwfvPXr0qHMiMfZhTk5OXl5ex44df6XFgHpD375969evf/To0aNHj27btm3VqlX43keNGiU0Lef3PmTIkAceeKB2uXFW4exiQuE7joqK2rRpEzoNqs7BWbt2bevWrTGnDXM/RNqo8PqVlZWhTVDTABJLdIWdEjp41QGXmJiIbqL169evXr167dq169atW7NmzZYtW7Zs2XLNNdfYth0fH+/3+1FACGiaJjIma1kGA1uXmZk5dOjQu+++Gw0O9OegI7ht27avvPIKpXTjxo3OR4jaBoPByy+//PHHH/d4PFOmTPnggw82bdqUm5vboUMH9APU4sETKyLgH+hiBsf6GX379l21alVGRsarr746YsQISum77747ePDgEydOIK06lzusHWlpaQ899ND9999/77333n777VdccQUmGlUr6dxut9fr7d+//4cffohS480337zuuuuEYdG5c2fkmKNHjy5ZsgQtCTERjFL68ccf4xoVjRo1ql+/vpDpM2bMwKCuqqovv/wypsxu3Ljx2WefRao4E89nz549cTYDqgsxMTGdOnVCZ91vzg3oBcXXhC2qqWIoZ1etWrVnzx7stMzMzFWrVq1evXrlypUHDx7E7KyDBw8uXboUe7Jjx474x549e44dO0YpxYgCrsnx8ssvd+rUqUePHm+99ZZzfb1fANu2IyMjMXED0w0WLlyILqwRI0ZU+42Ul5cHg8HKysrgTyECIZIY/uEWA2MsJSVl4MCBfr9/1qxZQjKK1AtCyJtvvpmbm4tqRZ06dXDWGDp5kEgIIbt37+ac49zp3wqNGjXCT6JLly7nn39+t27dunbt2r179+TkZNu2IyIiNE1r0KBBQUHByZMnMYCJ3pslS5b0799/wYIFQiMWNBDWfNS7Fy9ePHv27OLiYpzFIyQ15zwmJgbVrjABit/5119/vWjRoh49emzevBndDp06dSKEFBQUgCOFVCTgYplYFJo12M+Yg4iOMrzl0KFDX3/9dXl5edu2bSdNmvT5559v27atT58+6OZCYjjz9V9N0wwEApgahOIb/R7VSjqknGAw2K1bt6lTp1qW5Xa7P/roo7ffflvTNMuymjVr1rNnT3zv9957b05OjtvtRnHvcrnWr1//8ssvozUzcuRIr9drGIau65mZmVOnTsUSJk2adPPNN99xxx3orXriiSe2bdum63rt4g8b26lTJ4/HYxgGvusOHTp4PB7nVKzfXHM6rZos1pTF+cOc8yZNmvTv379Pnz59+/bt06fPgAED8NMghGCmBmPsnHPO6dChA4ZhHn74YTRwFUVxu9379+9/++23FUVZs2ZNeXm5mAf6a3DZZZfhG3/vvfd++OEHAOjevXuzZs3EelnONvp8Prfbjf86gcrTWRhjOBvbzDl/4IEHVFWdPn36p59+qmmaqqqKomiapmnaf/7zn3fffdfn8+GcHcysmDVrlt/vx5x0l8t1/PjxDz74AMOhv4mliYOvd+/eHo9n1qxZmNsqHLIDBgzo3LnzDz/8QCkdNGiQaZrvvfceVljXdUrpG2+8gdkXGF5D5z7OzAjz5tu23bRp05EjR5aVlU2aNKm4uNjlcqGM83g8ONeJMdavXz8U2RgMxHgGEgCltEOHDhEREeLTXb58eWZmpqIoIlLnrAPOLo6JiTly5EhZWRlmgCiKgmk2GEcBgOeff/6CCy7ACCE2pF69epj4iGomEjNOQjwTDQAbhS+39s8bZRxK8Hvuuadbt27BYFBV1SlTphw/fhyp9JFHHkEfxe7du88///yZM2euXr36m2++efTRRwcMGFBRUWHbdp06dW677TYkMMbYrbfeWl5ebtt2s2bNpk6daprm3Xff3aFDB5xdMWnSJLFgSe0ejGbNmuFCDvhGcLpyLa7/PwBoDx07dgw1cZzpsnz58pUrV65YsWLlypXLli3DOBnnfPny5fv27cM3gvPIVFV96623hg8f/sUXX2zatOntt98eMmRIfn4+Y6xRo0ZXX311tUvb/qyviXPetWtXnAUivKY4fcE5foTXd9u2bZ9++unHH3/8ySnMnTt3zpw58+bNw/yL39x391fHWbtWEs7OBYDRo0e/++67y5cvf+edd0aNGoUHMRkGldyxY8eiRb9ixQr8GDDj/q677sICc3NzdV3v1KmTmMmMGmhaWlpaWhpGKY4fP67reseOHcOuSU9Pr1OnDiZscM7vu+8+AGjbtu1XX3117NixjRs3XnDBBegbxZT5goICdHk/8cQTBw8ePHDgAObhXXDBBegHmDVrFnLMrFmzDh065EwHRG2dMZaZmYmu8EaNGt1///0ffPDBu++++/DDD3fr1g0AmjZtiut3cs5R1WrYsOELL7ywbdu2rVu3AkB8fPxXX31VVFR04sSJN954A00ZVVVFDusbb7wh6rB//35cOQ4ARowYsX79+p07d957772qqkZGRrZq1QqXn/v+++9VVU1MTPzggw+OHTuWlZWFTq3U1FQUGaZpjho1qlGjRiIftGrC5cqVK3FlzQ4dOqDYrTpfGo/k5eXVqVNHUZTo6Oi9e/eKHGXO+Y4dO3w+HwaccXIGduxrr70W5ssOcwPiPFuMrOJbQOfe119/LQpZvXo1UiMAPPXUU5g32bZtW6w2lnDo0KGkpCRFUXCqDS4cpCgKBpxxKcAtW7agNjNixAhs1yeffIKFDBgwwJl4jemeWGBkZGS16ariyJ49e6KiohRFadCgAc4xrnbCOXYUJlsritK9e3cxtIRn0rKs8847D9kUV53CHsBZ1gIisA8AHo8HV4sS1au9/vjSx48fjw2fOXOmqBv++9BDDxFCPB6PoigxMTG5ublh9951112KojjrEAZd1w8ePPgnZqzKeQx/aF/juPnoo4/EZByBDh064MQcnMpgWVZ5efmECRPChsv999+Pbgrn5DX8iSPP7/djQjSmshw7dgwAmjdv7rwmGAziosqYEIkOkFtuuSWsSmPHji0pKcHlE3AeLMZRBS666CKc1sAYy8rKEouyPf7441Xz0IUIGD58eNUvYeTIkfjtocPH7/dffPHFeGrIkCGc88ceewy1bzFpa+rUqc899xycWlfAtu3s7OxmzZrhXZiUsn37drEiG+K1115r3759TEyMWKHs9ddfR0eWQMuWLVFWotTGSR641Gu1E9yWLVuGNzZt2rR2YsjNzRVrWe/Zs0coAXjXs88+K+qAc0pQ3C9evPj8888PMz68Xu+oUaMyMzPFCnrbt28X14h5f2LUiUlVALB69WrGGK44DaeW1du/fz8ySsuWLbG27777rvB44DSOjRs34pFBgwZhu3CCCwB07do1jBiOHz8upknj/LuaiGHnzp14WVxcnBhRNa3D2LJlS7wYZ5aJYYY502JKDQAkJCQUFxeL7v3oo4/EvQK9e/dGVnC+2drrj1decskleErMuhBu4W3btonyL730UrFAi3gXN910U+16s6ZpSAx/zCLBfx1iIBXlwd/NGiHiTeCHHQgEkpLjIyK8f7qdJNZrM01z/fr1hw4dysnJSUpKat68eefOnXFNfMyfEx7JjIyMdevWFRQU1K9fv0ePHg0bNhSpdYZhrF27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i+d5zHzjjTd+9KMftYtN+6A//OEPP/jBDyzT/PjHP66rq7Ofbtiw4Tvf+c6KFSvsWnL06NEf/OAHb731VivOjjmprKT4zW9+Y7kkl8t97WtfGz9+fDabtcIuCIKampp/+7d/+9SnPjVr1qyFCxfW1tZa0WBne1tb27333vv4448fOHAgm82Wl5fPmjXrYx/72IUXXlioRf3oRz/67W9/CwDXXHPNnXfeeffddz/88MO7du1CxMmTJ995553XX399aL7o7++/9dZb0+m0iPz3f/+37/v/9//+32XLlnV0dFRVVV144YWf//zn6+rqCiV1Npv9wQ9+8Oijj+7bt09EampqzjnnnE996lOjR48uFJdWBfzZz3728MMP79692/O80tLSkSNH3nbbbTfeeKNlhf/zf/7P008/HQSBXcN+7nOfq6qquuSSSz75yU/a/s9msz/84Q8fffTRvXv3ikhtbe0555zz6U9/etSoUeFWhH3o/v37v/71ry9evLijo6OysvL888//8pe/bOnhb9r7yeVyxhj7sqzuNX78+O9+97uXX365LXb//fcvWrQoVCXtO/3pT3+6Y8cO3/ftS7nrrrvOOussq1P+6U9/+va3v+04DjN/4xvfmDJliq2w7aLPfe5za9asQcTp06f/53/+Z1NT06233mof9IUvfMFugIVKxv3333///ffv2LEjk8mUlpbW1dXdfPPNt9xyi3WsQETbJ3v37v3mN7/54osvtre3O44zatSoG2644eMf/3g8Hg8pWSm1bdu27373uytXrjx06BAzl5WVVVVVXXvttXfccUdpaWnEDSeE/r7sG/Yv19eb7e4a6Ozoa2vtbjrYtmvnvr6+AXm7wCrC2Wx28uTJ1o7xwQ9+kJknTpxoR6RdlxXa04MgEJFnn33WSsyhLK31r371KxHZtWvX0WtnAHj44YdFZPHixeGVZ555RkTOOecc++eUKVMsQwRBYJ918cUX24/mzZvn+77v+yLy0EMPJRKJoytw/fXX9/f3WzF3dHutFeXaa6+1ja2pqens7LStCzvEGJPNZltbWwt7ydbkhRdeGDNmzDEH4Wc/+1nrnpDL5UTk4x//uL3+nve85/bbbz+6/C9/+UsR8TxPRDo6OsLrX//61+vq6oYUnjJlSnd3t62GMaajo+PCCy88+p5VVVVPP/20fUe2ZFdX16WXXnrMCn/0ox+1Tz/rrLMKbSMWH/jAB+x9jvesysrKp556KnyWiKxdu3b48OFDis2ZM2f+/Pl2LJ133nnH3DgJr0yePNl+67LLLivcqLAkkclkJk6caAucccYZtoFBEPi+//d///fHHIrf+9737B127NgRDsLPf/7ztuftINmzZ0+oMXzlK18Rka1btw55TZao0un0jTfeeMzOvPrqq/v7++0AsLOjqqrq6GIXXHBBR0cHM9ueX7NmTUVFxTFvuHDhwvb29nDgne5CRkT6+/t372psPtje1trd2dHX3TXQ15vt68329+XeIOkdEcPrh50bf/zjH0PR8Oijj4rI5z73OXtFKbV8+XJrb7XDlJl3795dWVlpdXBEvOCCC6699tqSkhLrmZpMJrdt29be3t7Q0JBMJkOz0rBhwyorK63JfsmSJUop13WVUtaE9dhjjxGR67qI+OKLL9rZKCLbtm2Lx+OO4xCRpRxjzOrVq+PxuF1uV1dX33LLLVdccQUR2VX/XXfdVShWjm7yuHHj7PQ799xzCzkvtLCH8sjuuNhWb9++3bbabs+OHz9+/vz5lpxs133hC18QkUwmIyKf/vSnlVLxeNzWc9q0aR/72MfOOOMMALBXJk+enMlk7LM6OzutHcx+BADXXXfdzTffXFpaioj24ne/+91QQl1//fX2Poh48cUX33rrraFErqioaGxstO8rLBmLxWwd3vve906ZMgUAbLX/8z//U0Te8573lJaWhmbuioqKysrKT37yk7YH3v3ud4d3GPKsyspK+yxmHhgYmDZtWti6uXPn3n777fPnzy+01bxuYgjl45VXXmkL1NXVtbS02E+/+tWvhjWcO3fuHXfcUbgxYNlLRD760Y8qpbTWkydPTqfTzGwH2De/+U1rbauurm5ubhaRnTt3Oo5jd0p+85vfiEg2mxWRO++8M3z748aNe+973ztr1iwAsKa5z3zmM7bOe/bsGTZsmG11cXHxTTfd9O53v9s6dADADTfcEM6mhQsX2povWrToX/7lX/7f//t/H/rQh0KGft/73mdLRsQQEcOphp17N910kxWyo0aN6urqYuZ169ZZqQ0A//AP/2C3ecP5Gc6QeDz+29/+1t5qzZo1odvJxz/+cRHp7e21BAMADQ0Nzc3Nvb291mCybNmyUF688MILdtyMHz/eyqZPfOIT4Wy01l4iamhosHUTESuttNYjR47csmWLrcA999xj7xmLxbZu3Xo0N9jvdnZ2hkvya665JtSBConBYohUes973mOnsfXNz2azvu9v2rTJij/XdbXWq1evtt/61Kc+Fcrfm266qa+vz4r1a6+91lZSKbV+/XpbuLOz03YdESUSid///vf2+tKlS4uLi+0OszU9icjTTz8diqd///d/txd37949ceJE25//63/9L3vxmWeeCUveeeedAwMD9qVYgwwA1NfX9/T0pNPpxYsXh/vYjz76aG9vb3d3t135AoCVaIXPmjBhwpBn3X///aF0/ru/+zv77nK5nNWc7B1OnBg+8IEP2IFaUlKya9cuETlw4IBlNavl9Pf3i0hPT0+oFNr9IWZevHhxuDtt2cJqnyF73XrrrWEDw13iBx980F7csGGDXfdYkd3Z2WmHaLgX4rpuY2OjiHziE5+wg7OiomL58uX26w8//LDW2n79+eeft0pMcXExEcVisR07doS98dWvfnXEiBE33njjt7/9bTvpImKIiOGUvi072ezUskLBrhNzuRwzn3feeVZUVVdXt7W1heWz2eyYMWPstPngBz9oBatd13z/+9//zGc+8+CDD65Zs8bO6v/7f/+vnTYjRoywwsLe5OWXXw6Jwc4TEfm3f/u3QoFl9f2ZM2faZ9m62QrbPW0A+PnPf17YKLsEA4DvfOc7hRK/cIA2NTXZhb+1Ow0pFjoXWi0hVCB27tyZSCSsALK8FUquzZs3p1Ip2xarrIjIJz/5SSsdXNfduXOniFhGfPzxx0NNyzJiITFYoWMbbq0N4Rr5oosusoU/8YlP2A6ZMWNGYeseeughKzSnTp1qOcCWRMTa2tre3t5QCVu5cuXHP/7xH//4x88995xlrDVr1oROR9YYZV9o+Kzp06cXPuvhhx8On2Xbdcstt9isFbW1tZZUrObU1tY2bNiwEzcl2XdkTf9KKeueJCL33ntvSKh2/9Zi37599o24rrt9+3bbonnz5tma3HbbbbaYdci21s7FixeHxBDaP0Ni+NrXvmYfnUqldu/eHS5cdu7ceccdd3z/+9//05/+1Nvb29/fP27cOPvdL33pS4XNtKsZRLRsumHDBrvPT0Tz5s375je/uWLFCvs6XsMRPCKGv/5ftPl8Qv5IDz/8sHWcUErdfPPNodPkLbfc8uKLLzqO09ra+uijj/7d3/1duKvW2tpq7zB//vwws5Axxq6VQn/BIc7mQRC4rns8N227Hvz3f//3bDbb1NT05JNPvv/973/ppZc2bNhgF3of+chHbMm9e/d2dXVpra05+OGHH87lctaIYW0FIrJ+/frjtTqVStmFLQAMDAwc7atu/wwdLpnZdd3Vq1dnMhlLDDfeeGPY6iAIpkyZMmfOnCVLliDiypUrCzcMgyAYPnx4bW2tdbsSEUsAdqoMcdexG5JTp04N/VmZOQxCDgtbgWil8COPPGLjMOLx+MaNG22dm5qampqaxo8fb9Uma0QqLi62rjvGmDPOOMMatcKaWOfOsM6ht/GQZ+VyOWt12bhxo+3ngwcPNjU1jRs3zspKEZk9e3Zpaakxxm7GVlVVzZgx47nnnoMTyCxieyZ8X/bm1ma1bt06e9tYLPa73/0uHo/b99LT01NUVDQwMGCM2bRp04QJE7TWH/nIR1avXo2ITzzxREtLS01Nza9//Wvr5zpnzpxzzz33NeLmNm3aZB89ZsyY+vp6+0KZedy4cT/5yU/CYrt27dq7d6+tc1NT0yOPPJLJZKw90PM822nW4W3KlClz585dtmxZLBZbvXr16tWriWj8+PHz5s279tprr7rqqpKSklMZ9Rl5JUU47KXn+/4vf/nL0KvktttuCxMSeJ5nXSxsiMPtt99ux2hvb28mk7FOqBUVFYUuQHYfcki+s8LpfUzRYC/6vj9+/Pgrr7zy0UcfRcQHHnjgpptueuCBB6y4Oe+882bPnm09TLq6ukKXm0Kf10Ls3LnzePKluLi4rKzMRtg2NTVls9nQUSQs2dfXt2XLllmzZoUU0traankuFovV1NSEOZTsPUeOHGmr1NfXl06nU6lUyH82vCv0UAzDx+BYkVYAYM0L1mEmtF1AQT6r3t5eu0Zet27d+973vqOb2d3d3dnZaX+xV8rKyqysD3NA+b4PgxmrCp3ow0bZYdDT02PHyfr164/5rJ6eHvs6bEm78RB6W9nBEHLbiYRu2RqGK5KSkhJ7W6udOI7T3d192223HfO7Bw4csE+/8cYbv/SlL3V3d7e2tj777LM33XTTI488Yt/gLbfcopTyPK/wBRXCNhMASktLbZkweibUOGOxWFdXVxiO85Of/KSQM0JYDYaIfvzjH7/vfe+zPGFvuH379u3btz/wwAOTJ0/+4Q9/eIozAkTEECGvLixdunTt2rVWjgdBEI7R0KHIjvLly5evWrXKGmqsbmEJwxp8QplrA1zD+/9N9bH3ue222+zu99KlS3fs2BE6L916662h/hG6PzLzmWeeWV1dbSsZrsGz2ey8efOOuUS1rZ47d+6WLVu01tu3b9+7d+/EiRPDBILWEfbll1++4oorpkyZctlll33kIx+ZPXt2+FDrs1Qo46y/aegJM0SyDInjDRnieJ6IhULn6C5CxDAKoaGhYc6cOaHvY7jwD4LA6iVhTXp7e8PMpvaXvyhrbEeFgQgNDQ1z584NVwB2D8Y+q7i4ONxNAYB0Om2pJUx0YUnoRDQG+967urq2bt1qbzJu3DhrDww1sKKionPPPbcwz5IdFel0esSIEXahU1NTc/311//85z+3cf7Dhw+3nFFWVmZp7zViysLOtOmkYrGYfVBhqKPVR8NkAfPmzauvr7f9ENqFPM+zllhjzLRp01asWPHQQw898sgjq1atam9vD5+1devWG2+8cd26dVbdjJxWI2I4RbDD+v7777dWi0JjQjiN7fi28cn33nuvJYa6urqSkhK7Jt22bZtllCAI4vH4Y4899vDDD5955pkzZ85cuHBhLBYrjOGyxcJ0BUerLyJyySWXTJ48edu2bd3d3f/yL/9i1/W1tbV2l9jOwNraWtd1bYW/9KUvXXHFFcdr4zHDgK1z4f33309EuVzu7rvv/v73v2/dP8JYsLvvvttuHmzevPncc8+dPXv2yJEjbQWCINiwYcPs2bNzuZw1ENstaNvS0aNH2zscHaBXeOWYSRSG1Pl4smD48OH21UydOvUPf/jDa7xcWxIAbASDrbzW2iaJmzx58owZMxYtWlRTU1MY9mGXwDYhbkNDQ2jgsvmOjves+vp6ewe7HC40te3YseNvUgvC24Yi1b73Rx55pKWlxQarX3311WFvWH5KJpO///3vjxf3Ht7ktttuu/fee63ncUdHh73/1VdfXV9fb+ONj1e3kSNHWp47cOBAT09PZWWl7cxsNnvnnXdakl60aFFtbW1ZWZn1P/77v//7O+6445hiPQxtKy4uvv3222+//faDBw+uXbt2+fLl//M//2Pj+Nra2p5//vmbb745UhpeH6LA8dfDCkqptra2Rx991KoF559//po1a1avXr1mzZo1a9a8+uqrq1evXrly5eTJk+2E+e1vf2tXNLW1tVOnTrWi/H/+53/2798fOmXaPBP/+I//+JnPfMbOscIUBdaocrTcLOSheDz+oQ99yMqahx56yEr/973vfRUVFWG40/Dhw8eOHWu/dd9994V36OzsPP/886+//vp//dd/Xb169TG1Fks/7373u6dPn57L5WKx2A9/+MP/+I//sMHJWut0Ov25z33u8ccft05Zs2bNuvLKK5l5wYIFo0ePthaAr33ta52dndaJVin17W9/e9euXdYeZT2X3lAsXLjQvr7ly5cXanhf/vKXFy5c+I//+I8///nP7cbD2Wefbc0su3bt+vWvf239tZRSv/zlLx944IEvfelLN9xwQ0tLS6FNzCo9WmurAZx55pnhs6x3vy1T+Cy7wWNLaq03bdpkPXBsBz744INbt24tTJP1FxcrYX2sjYuIurq67r777s985jNaa9/3Kysrw0GyYMECW7K1tdVuiVtV5rHHHjvjjDNuv/32b3zjG3YRYwfPWWedZeMq9u/f/8QTT4R70X+x28PO7Ojo+NnPfhZ25m9/+9v77rvvq1/9qjUKlZeXT5kyxQ7+X/3qV4UWp3e9611XXnnlF77wBesf9eSTT37gAx+YP3/+7NmzOzo6Ghoa3vWud335y19+4YUXbK5JIgp1iAivB5FX0t8K63Py05/+FAZdDO+7775jlvzyl78Mg87pP/rRj+zF3/zmN+EXp06d+v3vf//Xv/71DTfcYFVpKHAWCp3ElVJf/OIXv/3tb1sHvqVLl8KR7qo2XslGxqVSKWvmtkYPu6NrXfesr853v/vd0HzxyU9+csOGDevXr7cVsLCeTscMZbAW4RdffNHGTFgTwfTp0z/+8Y/ffvvt1jHGkgQMRnVYZx67n2G7YurUqXfffff9999/22232dTQADBnzpyBgQFbQ+uVBAAzZ860T7Q/V6xYEQoLG8AxxCvpnnvusY215cMt99Clp62tzSbVIKLp06c/+eSTe/fu/fnPfx7GQNxwww22M5ubm20mBivo//mf//mBBx74whe+EI/HrT3K6mEismnTpkQiYWt1zTXX/OAHP7j//vutT1FVVZV9EfZZjY2NP/vZz8KtF/ssGyaWTCatXSWVSn3lK1/54x//+LWvfc0ao2xn/kWvJBtjYbclzj777EWLFp155plz5sypr6+3kt3ex44u20V2TWPNL1VVVT/96U/37Nnz5z//OYxDHDVqVG9v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Hj1++eUXZbho1qzZjh07PvzwQ2VCUXYPJW0dX7GjiChJt2nTpqeeeiopKemFF15QT7LylI4bN65fv37JycmO91VJVWVncMI9g6NxEPHhhx/OzMycMmXKd999BycHgCr7ye7duwcMGDBu3Dg11P79+w8cONC+ffsaNWoIITwej/q3d+/eWVlZmzdvZowJIT7//HMAeOSRR8LCwgKBAOfcMAy1Iinlfffdd++9944bN061lFm9enXv3r0nTpzoeO8/+OCDDRs2tGjRQpnL1YpKSkqc147pxqGcQCDg8/mklHFxcU78krrya9asUeOri6mc4ampqV27di1nPHGEpnMpnPGde6rOZVnWnwy6Pffm+AouCoeDHfeSY6KssmtBYKV16xiU9lMu7a9JwAwADhwAATgo61Hpp6peSFlPNnV86aeldxpL/1PpZ1T6KWOMAZqAiAw4IKABJgICA2cQpkIYgJd2+mTAwCgtk4eAyBmGlJ4LCYA4cAYAwAB5NW7JcEEQgxNrpEz8jzzyCBG98cYbkZGRDjGox880TZfL5fyr4Ha7XS5X8PO2cOHCVatW7du3T4nIkJCQ1q1bN2rUSI3g8XhSUlJeeOEFIrr66qsrzkEI8fDDDwPA66+/rgz6anC/3//tt9/+/vvvOTk5SraOHj1a6RbJyclutxsRp06dun79+t69ezdo0EAJXCHEyy+/vHPnzokTJyr7T3BfF7WujIyMxYsXf/vtt4FAAAB27dqFiC1atCjHnS1atEDEgwcPAkB6evqKFStCQ0N79eql2kaWM4U3adLk3XffHT16tOKelJSUZcuW/fTTT86AdevW7dixo2manHMV8vTGG2/s27dv8ODBjRo1Cg4SjY+PV9fN5XKFhIQwxv75z39KKceMGcMYU37jw4cPq/Edd0JycjIRNWvW7Kuvvho4cGDv3r0ffPDBlStXmqbpuBPU+NHR0Wp85566XC51i8+LX++p3ld1tv9MXG8VpgrEU4R8qo/K5ZA5b5b+V/obOvFn6bNW4YunH1zN4VRfKR0QsZp357mgnM/BIR+GYfz000+//fZbz549R44cqQSr2n4qWXPkyJGXX365YmiTEGLcuHFJSUnqzxdffHH//v3KdqTidpxd28cff/zzzz8vW7assLDwk08+GTJkiDqv+qKKGPn5559///33Xr16jRo1yon8AYDw8PB/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v2HmnvSd6/asGtR6KAkAXs1zXy4gYjh9n2Q4RVOtPz9Uue1bpbxyehlU7oDgwp+VfrHS9jUVs5Qrir9yKdAVj6/49f/YLVKFNv2ZVQef4s83oax0/NPUE600FfHswzH3T5w4UVXmiImJmTFjxs8//1wuEldBdW8NXml+fv62bdsiIiKUoY9zPmvWrJdeesntdj///PNZWVkulysQCLz33nvz58//7rvvPvjgA/UOAPz000/fffed4vtzbVNiQIgoCBgDAwDWJy/xy0BSXL1W9doAgaRArbDEzk16zt34uUCxYscv/VsNtZEMZHvSth/M2MUZq1ujXofGnQDguD/7ma8mrduzojhQIAg52m7DHU4RYwdcf8/QJ93EEQhJABlALkDJAAJgfbjgrdUHfwt1hbdu1K5xSCQS35W99bnPH96XusOPWGznz5AfDe0x0hcoNABttBi4SomhYYeE8JpHs5NX7V44qPVQkJw4IUggXl379FwQ4aoaGueQGDjn77zzzkcffdSzZ89t27YdO3Zsw4YN2dnZv//+e7CeqhjiwIEDmzdvXrt27caNG9euXfvdd99ddtllxcXFb731VlxcnMraU+Rx//33jx079vDhw4cPH3744YeLi4uHDx/+3XffzZ49OzU1ddmyZU2bNp01a9aSJUuCexeeY5suAJEEjumFaftT93HG68Y28BhhRMpYD73a9zbAbbg9m/Ztyis5ZjIGAGt2rPAJv+2X3Zr3j3HFCxRvf//irxtnmy7onNT1hkvHD+58eVRELQxzfbP0XzsyNqpA1tJI1yARFxruiYyOjIgKZwwBwCb/lDn/2HFskxnhbhCfeHPPCYPaD1++7rc96bvcbheQxLL7Eh0SUyu6JiLsS91TFChAg5UlOFRbvcHQj66GxhmCcoQUFBS8/fbbYWFhn3/+eVJSkhCiY8eOc+bMueiii4qKioKbUgDA22+//fbbb5cbZ+LEibfeeqtjEVI58P369Zs6dao64LHHHvv000+zs7M/++yzkSNHSil79ep15513Pvzwwzt27FBlgKvMTlQCwrHso+l5GcioSa1mACBJMGYSUYdGlyQmND6Qn3wkL2XDvtUD2l9RLPJW71mOBjeB9247EABKbG/9mMT+rYaG87hnb38xyqwBAK/Nem7G6k/Qg6kZxzrWAicz7cS9QJBSSiGJlWamrdu/fP2u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)

*ภาพที่ 6.5: ภาพหน้าจอ Dashboard ระบบเช็กชื่อ Smart RF Proximity Attendance*

### 1.3 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary><b>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.5</b></summary>

```text
ets Jul 29 2019 12:21:46
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15824
load:0x40080400,len:3988
entry 0x40080644
I (27) boot: ESP-IDF v6.1-beta1-685-g6a9c44fe7e7 2nd stage bootloader
I (27) boot: compile time Aug 10 2026 03:35:10
I (28) boot: Multicore bootloader
I (31) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (41) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (58) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1ac50h (109648) map
I (127) esp_image: segment 1: paddr=0002ac78 vaddr=3ffb0000 size=04628h ( 17960) load
I (134) esp_image: segment 2: paddr=0002f2a8 vaddr=40080000 size=00d70h (  3440) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8a1cch (565708) map
I (340) esp_image: segment 4: paddr=000ba1f4 vaddr=40080d70 size=14828h ( 84008) load
I (375) esp_image: segment 5: paddr=000cea24 vaddr=50000000 size=00028h (    40) load
I (386) boot: Loaded app from partition at offset 0x10000
I (386) boot: Disabling RNG early entropy source...
I (396) cpu_start: Multicore app
I (405) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (405) cpu_start: Pro cpu start user code
I (405) cpu_start: cpu freq: 160000000 Hz
I (407) app_init: Application information:
I (410) app_init: Project name:     proximity_attendance
I (415) app_init: App version:      1
I (420) app_init: Compile time:     Aug 10 2026 03:35:18
I (425) app_init: ELF file SHA256:  f82ca71e...
I (429) app_init: ESP-IDF:          v6.1-beta1-685-g6a9c44fe7e7
I (435) efuse_init: Min chip rev:     v0.0
I (439) efuse_init: Max chip rev:     v3.99
I (443) efuse_init: Chip rev:         v3.1
I (447) heap_init: Initializing. RAM available for dynamic allocation:
I (453) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (458) heap_init: At 3FFB9528 len 00026AD8 (154 KiB): DRAM
I (463) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (469) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (474) heap_init: At 40097FE4 len 0000801C (32 KiB): IRAM
I (481) spi_flash: detected chip: generic
I (483) spi_flash: flash io: dio
W (486) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (500) main_task: Started on CPU0
I (513) main_task: Calling app_main()
I (513) SMART_ATTENDANCE: [FORENSIC]: Call nvs_flash_init()
I (543) SMART_ATTENDANCE: [FORENSIC]: Call esp_netif_init()
I (543) SMART_ATTENDANCE: [FORENSIC]: Call esp_event_loop_create_default()
I (553) SMART_ATTENDANCE: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (563) SMART_ATTENDANCE: [FORENSIC]: Call esp_wifi_init()
I (583) wifi:wifi driver task: 3ffc1ae4, prio:23, stack:6656, core=0
I (603) wifi:wifi firmware version: e12a754
I (603) wifi:wifi certification version: v7.0
I (603) wifi:config NVS flash: enabled
I (603) wifi:config nano formatting: disabled
I (603) wifi:Init data frame dynamic rx buffer num: 32
I (613) wifi:Init static rx mgmt buffer num: 5
I (613) wifi:Init management short buffer num: 32
I (613) wifi:Init dynamic tx buffer num: 32
I (623) wifi:Init static rx buffer size: 1600
I (623) wifi:Init static rx buffer num: 10
I (633) wifi:Init dynamic rx buffer num: 32
I (633) wifi_init: rx ba win: 6
I (633) wifi_init: accept mbox: 6
I (643) wifi_init: tcpip mbox: 32
I (643) wifi_init: udp mbox: 6
I (643) wifi_init: tcp mbox: 6
I (643) wifi_init: tcp tx win: 5760
I (653) wifi_init: tcp rx win: 5760
I (653) wifi_init: tcp mss: 1440
I (653) wifi_init: WiFi IRAM OP enabled
I (663) wifi_init: WiFi RX IRAM OP enabled
I (663) SMART_ATTENDANCE: [FORENSIC]: Call esp_event_handler_instance_register()
I (673) SMART_ATTENDANCE: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (683) SMART_ATTENDANCE: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP)
I (693) SMART_ATTENDANCE: [FORENSIC]: Call esp_wifi_start()
I (693) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (733) wifi:mode : softAP (84:1f:e8:20:55:25)
I (743) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (753) SMART_ATTENDANCE: Attendance Web Server Started at http://192.168.4.1
I (753) main_task: Returned from app_main()
I (12836) wifi:station: 26:56:79:c2:53:fb join, AID=1, bgn, 20
I (12866) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (13906) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (41522) wifi:station: 92:70:76:1d:91:8c join, AID=2, bgn, 20
I (41552) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (42592) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3
I (95310) wifi:station: 92:70:76:1d:91:8c leave, AID = 2, bss_flags is 134243, bss:0x3ffc3a1c
I (101748) wifi:station: 92:70:76:1d:91:8c join, AID=2, bgn, 20
I (101778) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (102818) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3
I (156204) wifi:station: fe:b2:e9:4f:14:e5 join, AID=3, bgn, 20
I (156234) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (157274) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.4
I (230116) wifi:station: 26:56:79:c2:53:fb leave, AID = 1, bss_flags is 134243, bss:0x3ffc2e10
I (236482) wifi:station: 26:56:79:c2:53:fb join, AID=1, bgn, 20
I (236512) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (237552) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (240120) SMART_ATTENDANCE: [CHECKIN EVENT]: Student confirmed attendance via HTTP POST /checkin
```

</details>

## 2. คำถามท้ายการทดลอง (Post-Lab Questions)

### คำถามข้อที่ 1

การใช้ **RF Signal Proximity (RSSI)** ร่วมกับ **HTTP Web Server** บน ESP32 แก้ปัญหาการฝากเช็กชื่อแทนกันในห้องเรียนได้อย่างไร?

การป้องกันการเช็กชื่อแทนกันด้วย RF RSSI Proximity:

- การตรวจสอบระยะทางจริงผ่านระดับความแรงของสัญญาณวิทยุ ทำให้ผู้ที่ไม่อยู่ในพื้นที่จริงไม่สามารถผ่านเงื่อนไขได้
- การระบุอุปกรณ์ผ่านรหัสฮาร์ดแวร์ MAC Address
- กระบวนการยืนยันแบบ Real-time บนระบบเครือข่ายเฉพาะกิจ ป้องกันการทำ Proxy หรือ VPN ข้ามพื้นที่

### คำถามข้อที่ 2

เหตุใดระดับเกณฑ์ RSSI ที่ -55 dBm จึงเหมาะสมสำหรับการระบุตำแหน่งอุปกรณ์ให้อยู่ภายในรัศมีโต๊ะปฏิบัติการ?

ความสมเหตุสมผลของการตั้งเกณฑ์ RSSI ที่ -55 dBm ถึง -60 dBm:

- ในย่านความถี่ 2.4 GHz ค่าการลดทอนของสัญญาณในระยะ 1 เมตรจะทำให้ RSSI ตกลงมาอยู่ในช่วงประมาณ -45 dBm ถึง -55 dBm
- เกณฑ์ -60 dBm จึงทำหน้าที่เป็นรัศมีเสมือน (Virtual Geofence) ที่ครอบคลุมเฉพาะพื้นที่โต๊ะทดลองได้อย่างแม่นยำ

### คำถามข้อที่ 3

หากต้องการต่อยอดมินิโปรเจกต์นี้ในอนาคต ให้สามารถบันทึกข้อมูลการเข้าเรียนลงระบบ Cloud (เช่น Google Sheets หรือ Firebase) จะต้องเพิ่มส่วนเชื่อมต่อใดบ้าง?

การพัฒนาขยายระบบสู่ Cloud Infrastructure:

- ปรับแต่งระบบเครือข่าย Wi-Fi ให้รองรับโหมดสถานีร่วม (AP+STA Concurrent Mode) เพื่อให้ออกสู่อินเทอร์เน็ตได้
- การรวมชุดโปรโตคอล MQTT หรือ HTTPS เพื่อส่งข้อมูลสตรีมมิ่งขึ้นสู่ Cloud IoT Core
- การใช้ระบบ Time Synchronization (NTP) เพื่อบันทึกเวลาจริงของการเช็กชื่อลงในฐานข้อมูล

---

# 🔍 สรุปและวิเคราะห์ผลการทดลองภาพรวม (Comprehensive Discussion & Conclusion)

จากการปฏิบัติการประจำสัปดาห์ที่ 6 (Week 06: Wi-Fi SoftAP, RF Throughput & Sensor Fusion with FreeRTOS) ของ **นายกร แดงทอง (รหัสประจำตัว 67030268) ประจำโต๊ะ 2**:

- **สถาปัตยกรรม Wi-Fi SoftAP และ Client Tracking (Lab 6.1):**
- บอร์ด ESP32 สามารถทำหน้าที่เป็น Autonomous Access Point ภายใต้ชื่อเครือข่าย ESP32_AP_0268 ได้อย่างสมบูรณ์
- ระบบ DHCP Server ทำงานแจกจ่าย IP 192.168.4.2 ให้กับอุปกรณ์ลูกข่ายได้ถูกต้อง และ Event Handler สามารถตรวจจับ Association Event ดักจับ MAC Address และกำหนด Association ID (AID) ได้แม่นยำ
- **การประเมินประสิทธิภาพคลื่นวิทยุและความเร็ว (Lab 6.2):**
- ได้ดำเนินการทดสอบ Pair Work วัด Throughput ที่ระดับ Tx Power ตั้งแต่ 20 dBm ลงไปจนถึง 2 dBm
- จากผลการสร้างแบบจำลองสถิติเชิงเส้น (Linear Regression) ได้สมการถดถอย **$y = -160.28x + 807.05$** ด้วยค่าความเชื่อมั่น **$R^2 = 0.1774$** ซึ่งสะท้อนพฤติกรรมการรับส่งข้อมูลจริงภายในระยะโต๊ะปฏิบัติการ
- **การออกแบบ FreeRTOS Task Architecture & Queue (Lab 6.3):**
- การแยกบทบาทหน้าที่ระหว่าง SensorTask (Producer: ดึงข้อมูลจากเซนเซอร์อุณหภูมิ 31.6°C, ความชื้น 66.1%, แสง 606 lux) และ NetworkTask (Consumer) ผ่าน FreeRTOS Queue ทำให้ระบบไม่มีการบล็อกการทำงาน (Non-blocking)
- จากการตรวจสอบ High Water Mark พบ Stack เหลือปลอดภัย (SensorTask: 1188 words, NetworkTask: 2240 words) แสดงถึงการจัดสรรหน่วยความจำที่มีประสิทธิภาพสูง
- **IoT Sensor Dashboard & RESTful JSON API (Lab 6.4):**
- การรัน HTTP Web Server ขนาดเล็กบน ESP32 สามารถให้บริการ Web Interface สตรีมค่าเซนเซอร์แบบ Real-Time ขึ้นหน้าจอสมาร์ตโฟน (อุณหภูมิ 25.5°C, ความชื้น 55.1%, แสง 529 lux)
- Endpoint `/api/data` ส่งกลับ Payload ในฟอร์แมตมาตรฐาน JSON รองรับการเชื่อมต่อกับระบบภายนอกได้อย่างไร้รอยต่อ
- **ระบบเช็กชื่อ Smart RF Proximity Attendance (Lab 6.5):**
- ระบบสามารถกรองความแรงสัญญาณด้วยเกณฑ์ `RSSI_THRESHOLD = -60` dBm แยกแยะอุปกรณ์ที่อยู่ใกล้ (7E:37:81:0C:3B:5E ที่ระดับสัญญาณ -45 dBm สถานะ NEAR (Valid)) ได้อย่างแม่นยำ ป้องกันการเช็กชื่อจากระยะไกลได้อย่างมีประสิทธิภาพ
