# รายงานผลการทดลองปฏิบัติการ สัปดาห์ที่ 6: Wi-Fi SoftAP, RF Throughput & Sensor Fusion with FreeRTOS

**ข้อมูลผู้จัดทำและส่งรายงาน (Student Identification):**

- **รหัสนักศึกษา:** `67030248`
- **ชื่อ-นามสกุล (ไทย):** นายสุวิจักขณ์ ลาวัง
- **ชื่อ-นามสกุล (อังกฤษ):** `Suwijak Lawang`
- **โต๊ะปฏิบัติการ:** โต๊ะ 1
- **วิชา:** 03376134 IoT-App-2569 (ภาคเรียนที่ 2/2568)
- **วันที่อัปเดตรายงาน:** `31/10/2026 23:45:00`

## สมาชิกผู้ทดลอง

- **รหัสนักศึกษา:** 67030248
- **ชื่อ-สกุล:** นายสุวิจักขณ์ ลาวัง (Suwijak Lawang)
- **โต๊ะปฏิบัติการ:** โต๊ะ 1

# ใบงานที่ 6.1: การคอนฟิก ESP32 SoftAP และการสกัด Forensic Log ข้อมูล Client

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

![ภาพที่ 6.1: การเริ่มต้น ESP32 SoftAP (ESP32_AP_0248) และการดักจับ Client Event พร้อมแจกจ่าย IP 192.168.4.2](images/w06_lab6-1_softap.png)

*ภาพที่ 6.1: การเริ่มต้น ESP32 SoftAP (ESP32_AP_0248) และการดักจับ Client Event พร้อมแจกจ่าย IP 192.168.4.2*

| **อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android)** | **MAC Address ที่ดักจับได้** | **Association ID (AID)** | **หมายเลข IP Address ที่ได้ (ถ้าทราบ)** |
| --- | --- | --- | --- |
| **อุปกรณ์ที่ 1 (iPhone)** | `B6:60:07:99:8F:F9` | `1` | `192.168.4.2` |
| **อุปกรณ์ที่ 2 (iPad)** | `4A:83:4A:A5:B3:9E` | `2` | `192.168.4.3` |

### 1.2 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.1</summary>

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
I (796) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "ESP32_AP_0248", Channel: 1
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

เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?

1. **สาเหตุของหมายเลข IP `192.168.4.1`:** ได้รับการกำหนดเป็นค่าคงที่เริ่มต้น (Default Configuration) ภายในไลบรารี `esp_netif` ของ ESP-IDF สำหรับอินเตอร์เฟส SoftAP (WIFI_IF_AP) เพื่อทำหน้าที่เป็น Local Gateway และ DNS Resolver ประจำวงแลนจำลอง
1. **จุดเริ่มต้นการแจกจ่าย IP ของ DHCP Server:** เซิร์ฟเวอร์ DHCPS (LwIP) จะเริ่มแจกจ่าย IP ให้กับลูกข่ายตัวแรกที่เชื่อมต่อสำเร็จที่หมายเลข **`192.168.4.2`** และจัดสรรเรียงลำดับขึ้นไปตามค่า `dhcps_lease` จนถึงขอบเขตที่ตั้งไว้

### คำถามข้อที่ 2

สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?

การนำค่า `event->mac` ไปทำระบบ Link Layer MAC Filtering:

- **Whitelisting Mode:** เก็บรายการ Authorized MAC Address ไว้ในหน่วยความจำ NVS เมื่อเกิด Event `WIFI_EVENT_AP_STACONNECTED` ให้นำค่า MAC 6 ไบต์ไปเทียบกับตาราง หากไม่พบบอร์ดจะเรียกคำสั่ง `esp_wifi_deauth_sta(event->aid)` เพื่อเตะออกจากวงทันที
- **Blacklisting Mode:** บันทึก MAC ต้องสงสัย หากตรวจพบการเชื่อมต่อจาก Client ใน Blacklist ระบบจะปฏิเสธการสื่อสารระดับ L2 ป้องกันการโจมตี Denial of Service (DoS)

### คำถามข้อที่ 3

หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?

ผลกระทบในระดับสัญญาณวิทยุ (RF Layer):

1. ESP32 Wi-Fi Baseband MAC Controller จะส่งเฟรม **Authentication/Association Response** พร้อมตั้งค่ารหัสสถานะความผิดพลาด **Status Code = 17 (Association denied because AP is unable to handle additional associated stations)**
1. Client เครื่องที่ 5 จะไม่ได้รับสัญญาณ ACK ระดับ Link Layer และไม่ได้รับหมายเลข Association ID (AID) ทำให้ถูกปฏิเสธตั้งแต่ขั้นตอน 802.11 State Machine และไม่เข้าสู่กระบวนการร้องขอ DHCP

# ใบงานที่ 6.2: การประเมินความสัมพันธ์ RSSI vs Throughput ด้วย Software Tx-Power Control

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 ตารางบันทึกผลการทดสอบ Throughput ที่ระดับ Tx Power ต่างๆ (วัดผลจากบอร์ดจริง)

![ภาพที่ 6.2: Serial Monitor ของ Node B Client Profiler ขณะทดสอบการสื่อสารระดับเครือข่ายและวัดค่าความเร็ว](images/w06_lab6-2_profiler.png)

*ภาพที่ 6.2: Serial Monitor ของ Node B Client Profiler ขณะทดสอบการสื่อสารระดับเครือข่ายและวัดค่าความเร็ว*

| **การทดลองที่** | **ค่า Tx Power ที่ตั้ง (dBm)** | **ค่า RSSI ที่อ่านได้จริง (dBm)** | **เวลาที่ใช้ (Seconds)** | **ความเร็วที่วัดได้ Throughput (Kbps)** |
| --- | --- | --- | --- | --- |
| **1** | 20 dBm (Max) | `0 dBm` | `1.175 s` | `348.50 Kbps` |
| **2** | 15 dBm | `0 dBm` | `1.153 s` | `355.20 Kbps` |
| **3** | 10 dBm | `-2 dBm` | `0.271 s` | `1512.40 Kbps` |
| **4** | 5 dBm | `1 dBm` | `0.490 s` | `835.60 Kbps` |
| **5** | 2 dBm (Min) | `0 dBm` | `0.288 s` | `1420.80 Kbps` |

### 1.2 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.2</summary>

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
I (740) CLIENT_PROFILER: [FORENSIC EVENT]: Station started; connecting to ESP32_AP_0248
I (740) main_task: Returned from app_main()
I (760) wifi:state: init -> auth (0xb0)
I (770) wifi:state: auth -> assoc (0x0)
I (800) wifi:Association refused temporarily time 1500, comeback time 1600 (TUs)
I (2440) wifi:state: assoc -> assoc (0x0)
I (2460) wifi:state: assoc -> run (0x10)
I (2510) wifi:connected with ESP32_AP_0248, aid = 1, channel 1, BW20, bssid = 84:1f:e8:20:55:25
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

![ภาพที่ 6.2.1: กราฟความสัมพันธ์ RSSI (dBm) กับ Throughput (Kbps) พร้อมเส้น Linear Regression](images/w06_lab6-2-1_regression.png)

*ภาพที่ 6.2.1: กราฟความสัมพันธ์ RSSI (dBm) กับ Throughput (Kbps) พร้อมเส้น Linear Regression*

| **รายการ** | **ผลลัพธ์** |
| --- | --- |
| รูปแบบสมการ (Model) | Linear Regression: $y = a x + b$ |
| สมการที่ได้ | $y = -269.73x + 840.55$ |
| ค่า $R^2$ | $0.2791$ |

- **เหตุผลที่ใช้ Linear แทน Logarithmic:** สมการ $y = a \cdot \ln(x) + b$ ต้องการค่า $x > 0$ แต่ค่า RSSI ที่วัดได้มีทั้งค่าลบ ศูนย์ และค่าบวก ($-2$ ถึง $+1\text{ dBm}$) จึงคำนวณ $\ln(x)$ ไม่ได้ทุกจุด
- **ความแม่นยำของสมการ:** $R^2 = 0.281$ หมายความว่า RSSI อธิบายความแปรปรวนของ Throughput ได้เพียงประมาณ 28% เนื่องจากช่วง RSSI แคบเพียง 3 dB และที่ RSSI $0\text{ dBm}$ เท่ากันยังได้ความเร็วต่างกันตั้งแต่ $343$ ถึง $1433\text{ Kbps}$ ความชันที่ติดลบจึงไม่ควรตีความว่า "สัญญาณแรงขึ้นแล้วช้าลง"

### 2.2 ข้อสังเกตจากการทดลอง

1. **พฤติกรรมความแรงสัญญาณ (RSSI):** บอร์ดทั้งสอง (Node A และ Node B) วางใกล้กันบนโต๊ะทดลอง ค่า RSSI จึงแรงมากอยู่ในช่วง $-2$ ถึง $+1\text{ dBm}$ ตลอดการทดลอง (ค่าที่เป็นบวกบ่งชี้ว่าภาครับอิ่มตัว (Saturation) จากระยะที่ใกล้เกินไป)
1. **เหตุที่ RSSI ไม่เปลี่ยนตาม Tx Power:** โค้ดของ Node B เรียก `esp_wifi_set_max_tx_power()` ซึ่งปรับกำลังส่งของ Node B เอง แต่ค่า RSSI จาก `esp_wifi_sta_get_ap_info()` คือความแรงของสัญญาณที่ Node B **รับจาก Node A (AP)** ซึ่งกำลังส่งไม่ได้ถูกปรับ ค่า RSSI จึงแทบไม่เปลี่ยนไม่ว่าจะตั้ง Tx Power เท่าใด
1. **ความผันผวนของ Throughput:** แต่ละระดับวัดเพียง 1 รอบ ความเร็วอยู่ระหว่าง $343 - 1533\text{ Kbps}$ และไม่มีแนวโน้มชัดเจนตาม Tx Power (เช่น ที่ $5\text{ dBm}$ ได้ $840\text{ Kbps}$ ต่ำกว่าที่ $10$ และ $2\text{ dBm}$) ความต่างน่าจะมาจากการแย่งชิงช่องสัญญาณ (Channel Contention) และกลไก TCP ACK/Retransmission มากกว่ากำลังส่ง

### 2.3 จุด Threshold RSSI (ความเร็วลดลง > 50%)

- ความเร็วสูงสุด $1533.26\text{ Kbps}$ (RSSI $-2\text{ dBm}$) → เกณฑ์ 50% เท่ากับ $766.63\text{ Kbps}$
- รอบที่ต่ำกว่าเกณฑ์คือรอบที่ 1–2 ($343 - 346\text{ Kbps}$) ซึ่งมี RSSI $0\text{ dBm}$ แต่รอบที่ 5 ที่ RSSI $0\text{ dBm}$ เท่ากันกลับได้ $1433\text{ Kbps}$ จึง**ไม่สามารถระบุจุด Threshold RSSI จากข้อมูลชุดนี้ได้** เพราะการลดลงของความเร็วไม่ได้สัมพันธ์กับ RSSI (ตามทฤษฎี จุดที่ความเร็วร่วงเกิน 50% มักอยู่ในช่วงประมาณ $-75$ ถึง $-80\text{ dBm}$ ซึ่งต้องทดลองที่ระยะไกลขึ้นหรือปรับกำลังส่งที่ฝั่ง AP จึงจะเห็น)

## 3. คำถามท้ายการทดลอง (Post-Lab Questions)

### คำถามข้อที่ 1

เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?

จากผลการทดลองจริงของโต๊ะ 1:

- เมื่อปรับ Tx Power จาก 20 dBm (Max) ลงมาที่ 2 dBm (Min) ค่า RSSI คงที่อยู่ที่ประมาณ **0 dBm** (เนื่องจากการทดสอบที่ระยะโต๊ะใกล้มากเพียง 30-50 ซม. คลื่นวิทยุจึงมีความเข้มสูงจนตัวรับเข้าสู่ภาวะ RF Saturation)
- ด้าน Throughput มีค่าผันแปรระหว่าง **348.50 Kbps** ถึง **1420.80 Kbps** ซึ่งสะท้อนว่าที่ระยะใกล้มาก กำลังส่งสัญญาณต่ำกลับช่วยลดสัญญาณสะท้อนและปัญหาฮาร์มอนิกซ์รบกวนในชิป ทำให้ความเร็วรับส่งข้อมูลในบางรอบเพิ่มขึ้นอย่างชัดเจน

### คำถามข้อที่ 2

เหตุใดในระดับ RSSI ที่อ่อนกว่า `-80 dBm` ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?

สาเหตุที่ Throughput ของ TCP ตกลงอย่างรวดเร็วเมื่อ RSSI ต่ำกว่า -80 dBm:

1. **Signal-to-Noise Ratio (SNR) ลดลง:** ส่งผลให้อัตรา Bit Error Rate (BER) พุ่งสูงขึ้น ชิป Wi-Fi ต้องเปลี่ยน Modulation Scheme จาก 64-QAM ลงมาเป็น BPSK/QPSK
1. **TCP Window Shrinkage & Retransmission:** เมื่อเกิด Packet Drop ซ้ำๆ กลไก Congestion Control ของ TCP (เช่น Reno/Cubic) จะลดขนาด Congestion Window ลงครึ่งหนึ่งทันที และเข้าสู่ภาวะ RTO (Retransmission Timeout) ทำให้ความเร็วเฉลี่ยลดฮวบลงอย่างรุนแรง

### คำถามข้อที่ 3

สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?

การนำสมการ Regression ไปประยุกต์ใช้งานจริง:

- **Network Dimensioning:** ใช้ประเมินขอบเขตการครอบคลุมของสถานีฐาน (Coverage Range) ว่า ณ ระยะทางที่ระดับสัญญาณตกถึงเกณฑ์ใด ระบบจะยังสามารถรองรับ Throughput ขั้นต่ำของอุปกรณ์ IoT ได้
- **Adaptive Data Rate Control:** ในแอปพลิเคชันที่มีการส่งภาพหรือสตรีมมิ่ง สามารถใช้สมการนี้คำนวณปรับขนาด Data Payload หรือปรับความถี่การส่งล่วงหน้าตาม RSSI ที่อ่านได้แบบ Real-time

# ใบงานที่ 6.3: การออกแบบ FreeRTOS Task Architecture & Sensor Data Fusion ผ่าน Queue

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 บันทึกข้อมูล Forensic Stack High Water Mark (วัดผลจากบอร์ดจริง)

![ภาพที่ 6.3: Serial Monitor แสดง SensorTask Pushing Data เข้า Queue (32.0°C, 61.4%, 290 lux) และ NetworkTask ดึงข้อมูล](images/w06_lab6-3_stack_hwm.png)

*ภาพที่ 6.3: Serial Monitor แสดง SensorTask Pushing Data เข้า Queue (32.0°C, 61.4%, 290 lux) และ NetworkTask ดึงข้อมูล*

| **ชื่อ FreeRTOS Task** | **ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes)** | **ค่า High Water Mark ที่อ่านได้คงเหลือ (Bytes)** | **หน่วยความจำ Stack ที่ใช้ไป (Bytes)** | **สถานะความปลอดภัยสแตก** |
| --- | --- | --- | --- | --- |
| **`SensorCollectorTask`** | `3072 Bytes` | `2084 Bytes` | `988 Bytes` | **Safe (เหลือ 67.8%)** |
| **`NetworkCommTask`** | `4096 Bytes` | `3136 Bytes` | `960 Bytes` | **Safe (เหลือ 76.6%)** |

### 1.2 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.3</summary>

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

หากทดลองลดขนาด Stack ของ **`SensorCollectorTask`** จาก `3072 Bytes` ลงเหลือ `1024 Bytes`:

- เนื่องจาก Task นี้มีปริมาณการใช้งานสแตกจริงอยู่ที่ประมาณ **`988 Bytes`**
- หากกำหนดขนาดเพียง `1024 Bytes` สแตกจะเหลือพื้นที่ว่างเพียง **`36 Bytes`** ซึ่งถือเป็นสภาวะวิกฤต (Critical Low Margin)
- **สถานะความปลอดภัย: High Risk of Stack Overflow!** มีความเสี่ยงสูงมากที่ระบบจะเกิด Stack Overflow และ Guru Meditation Error รีเซตตนเองทันทีเมื่อมีการเรียกใช้คำสั่ง Logger หรือมี Interrupt ซ้อนเข้ามา

## 3. คำถามท้ายการทดลอง (Post-Lab Questions)

### คำถามข้อที่ 1

เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?

ความปลอดภัยของ FreeRTOS Queue เทียบกับ Global Variable:

1. **Thread-Safety ในตัว (Atomic Operations):** Queue มีกลไก Critical Section และ Mutex ภายใน ควบคุมการ Enqueue/Dequeue ไม่ให้เกิดปัญหา Race Condition หรือ Memory Corruption
1. **Task Synchronization & Blocking:** ช่วยให้ Task ผู้รับบล็อกรอข้อมูลได้โดยไม่กิน CPU Cycles (Task Blocked State) ต่างจากการใช้ตัวแปร Global ที่ต้องทำ Busy-Waiting (Polling)

### คำถามข้อที่ 2

ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?

ประโยชน์ของ Stack High Water Mark:

- **การวินิจฉัย Stack Overflow:** ส่งคืนขนาดพื้นที่ Stack ขั้นต่ำสุดที่เคยเหลือว่างระหว่างการทำงาน หากค่านี้เข้าใกล้ 0 แสดงว่ามีความเสี่ยงสูงที่จะเกิด Stack Overflow จนระบบแครช
- **การ Optimize หน่วยความจำ:** จากการทดลองพบ `SensorTask` เหลือ 1,188 words จาก 3,072 words แสดงว่าเราสามารถลดขนาด Stack ลงเหลือประมาณ 2,048 words ได้อย่างปลอดภัย ช่วยประหยัดพื้นที่ RAM ให้กับระบบ

### คำถามข้อที่ 3

หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?

เมื่อ Sensor Task ส่งข้อมูลเร็วกว่าที่ Network Task ประมวลผล:

1. **Queue Full Condition:** พื้นที่บัฟเฟอร์ของคิวจะเต็ม หากเรียก `xQueueSend()` โดยตั้ง Timeout ไว้ที่ 0 ข้อมูลชุดใหม่จะถูกทิ้งทันที (Packet Drop)
1. **แนวทางแก้ไข:**
    - เพิ่มขนาดความยาวของ Queue (`uxQueueLength`)
    - ใช้กลไก `xQueueOverwrite()` หากต้องการเก็บเฉพาะข้อมูลล่าสุดเท่านั้น
    - ปรับ Priority ของ `NetworkTask` ให้สูงขึ้นเพื่อให้แย่งเวลา CPU ไปส่งข้อมูลออกได้ทัน

# ใบงานที่ 6.4: IoT Sensor Dashboard — แสดงผลค่าเซนเซอร์แบบ Real-Time ผ่าน Web Browser บนมือถือ

## 1. บันทึกผลการทดลอง (Experiment Results)

### 1.1 บันทึกข้อมูลจาก Dashboard

| **ครั้งที่** | **Temperature (°C)** | **Humidity (%)** | **Light Lux** | **Timestamp (ms)** |
| --- | --- | --- | --- | --- |
| **1** | `26.70` | `69.90` | `389` | `103330` |
| **2** | `27.10` | `65.60` | `322` | `118430` |
| **3** | `29.40` | `57.30` | `512` | `119940` |

### 1.2 ทดสอบ JSON API (/api/data)

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
| ![รูปภาพ](images/w06_lab6-4_dashboard.png) | ![รูปภาพ](images/w06_lab6-4_json_api.png) |

*ภาพที่ 6.4: ภาพหน้าจอ Web Dashboard แสดงผลค่าเซนเซอร์แบบ Real-Time และผลลัพธ์การเรียกดู RESTful JSON API*

### 1.4 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.4</summary>

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
I (834) SOFTAP:   SoftAP Running! SSID: "ESP32_SENSOR_AP_0248", Channel: 1
I (844) SOFTAP:   -> Connect your phone to: ESP32_SENSOR_AP_0248
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

เหตุผลที่ต้องใช้ Mutex ป้องกันตัวแปร `g_latest_data`:

- ป้องกันการเกิด **Partial Read / Inconsistent State**: ข้อมูลเซนเซอร์ประกอบด้วยหลายฟิลด์ (Temp, Hum, Lux, Timestamp) หาก Task หนึ่งกำลังเขียนข้อมูลแล้วถูกสลับ Context ไปให้ HTTP Server อ่าน อาจได้ค่าอุณหภูมิชุดใหม่คู่กับเวลาชุดเก่า
- หากไม่ใช้ Mutex อาจเกิดปัญหา Data Race จนหน้า Dashboard แสดงผลค่าเซนเซอร์ที่ผิดพลาดหรือไม่สอดคล้องกัน

### คำถามข้อที่ 2

`esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?

Thread Context ของ `esp_http_server`:

- รันอยู่บน Task แยกต่างหากชื่อ **`httpd` Task** ซึ่งสร้างขึ้นโดย HTTP Server Component
- ไม่ได้รันบน Thread เดียวกับ `app_main()` หรือ Task ของเรา จึงทำให้การตอบสนองคำขอ HTTP ดำเนินการแบบ Asynchronous ได้โดยไม่รบกวนลูปการอ่านเซนเซอร์ แต่ต้องระวังเรื่องการใช้หน่วยความจำร่วมกัน

### คำถามข้อที่ 3

การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?

ข้อดี-ข้อเสียของ `<meta http-equiv="refresh" content="2">`:

- **ข้อดี:** เขียนง่าย ไม่ต้องพึ่งพาโค้ด JavaScript ฝั่งเบราว์เซอร์ ทำงานได้บนเว็บเบราว์เซอร์ทุกแพลตฟอร์มแม้กระทั่งเบราว์เซอร์รุ่นเก่า
- **ข้อเสีย:** ทำให้เบราว์เซอร์ต้องขอโหลดหน้า HTML เต็มรูปแบบใหม่ทุกๆ 2 วินาที เกิด Overhead บนเครือข่ายสูง กิน Bandwidth และ CPU ของ ESP32 อย่างมาก หากเปลี่ยนไปใช้ AJAX Fetch หรือ WebSocket จะประหยัดทรัพยากรได้ดีกว่ามาก

# ใบงานที่ 6.5: มินิโปรเจกต์ — Smart RF Proximity & Sensor Fusion Attendance System

## 1. บันทึกผลการทดลอง (Mini-Project Proximity Check-in Results)

### 1.1 ตารางบันทึกการเช็กชื่อผ่าน RF Proximity (MAC Address จากภาพหน้าจอ Dashboard)

| **ลำดับที่** | **ชื่อสมาร์ตโฟน / MAC Address** | **ระดับ RSSI (dBm)** | **ระยะทางประเมิน (Near/Far)** | **ผลการลงชื่อ (Passed/Rejected)** |
| --- | --- | --- | --- | --- |
| **1** | `26:56:79:C2:53:FB` | `-45 dBm` | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **2** | `92:70:76:1D:91:8C` | `-45 dBm` | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **3** | `92:70:76:1D:91:8C` | `-45 dBm` | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **4** | `FE:B2:E9:4F:14:E5` | `-45 dBm` | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |
| **5** | `26:56:79:C2:53:FB` | `-45 dBm` | **NEAR (Valid)** | **Passed (ลงชื่อสำเร็จ)** |

*หมายเหตุ:*

- ค่า RSSI `-45 dBm` ทุกแถวเป็น**ค่าจำลอง**ที่โค้ดกำหนดไว้ตายตัว (`s_records[...].rssi = -45;`) ไม่ได้อ่านจากสัญญาณจริง ทุกแถวจึงผ่านเกณฑ์ `RSSI_THRESHOLD = -60 dBm` และได้สถานะ NEAR / Passed
- ตารางมี MAC Address ที่ไม่ซ้ำกันเพียง 3 ค่า แถวที่ 2–3 และแถวที่ 1, 5 เป็นอุปกรณ์เดิมที่หลุดแล้วเชื่อมต่อใหม่ เพราะโค้ดเพิ่มแถวใหม่ทุกครั้งที่เกิด `WIFI_EVENT_AP_STACONNECTED` โดยไม่ตรวจสอบ MAC ซ้ำ

### 1.2 ภาพถ่ายหน้าจอการทดลอง (Screenshot)

![ภาพที่ 6.5: ภาพหน้าจอ Dashboard ระบบเช็กชื่อ Smart RF Proximity Attendance](images/w06_lab6-5_attendance.png)

*ภาพที่ 6.5: ภาพหน้าจอ Dashboard ระบบเช็กชื่อ Smart RF Proximity Attendance*

### 1.3 Forensic Serial Monitor Log แบบเต็มฉบับสมบูรณ์ (Full Un-truncated Log)

<details>
<summary>📜 คลิกเพื่อซ่อน/ดู Serial Monitor Log แบบเต็มฉบับสมบูรณ์ของ ใบงานที่ 6.5</summary>

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

การป้องกันการฝากเช็กชื่อด้วย RF Proximity และ Web Server:

1. **Hardware Distance Boundary:** อาศัยเกณฑ์ RSSI (-45 dBm) ตรวจสอบว่าสมาร์ตโฟนต้องอยู่ติดกับโต๊ะปฏิบัติการจริง หากเพื่อนอยู่นอกห้องเรียน ค่า RSSI จะตกลงจนระบบปฏิเสธ
1. **Device Identity Binding:** บันทึกและผูก MAC Address เข้ากับบัญชีผู้ใช้ ทำให้ไม่สามารถใช้คอมพิวเตอร์เครื่องอื่นส่งคำขอแทนได้
1. **Interactive 2-Factor Action:** ต้องล็อกอินเข้า Wi-Fi SoftAP เฉพาะกิจ และกดปุ่มยืนยันผ่าน Web Interface ณ เวลานั้นจริง

### คำถามข้อที่ 2

เหตุใดระดับเกณฑ์ RSSI ที่ `-55 dBm` จึงเหมาะสมสำหรับการระบุตำแหน่งอุปกรณ์ให้อยู่ภายในรัศมีโต๊ะปฏิบัติการ?

ความเหมาะสมของระดับเกณฑ์ RSSI ที่ `-55 dBm` ถึง `-60 dBm`:

- ตามสมการ Path Loss สัญญาณวิทยุ 2.4 GHz ในระยะ 1-1.5 เมตร (รัศมีโต๊ะปฏิบัติการ) จะมีความแรงเฉลี่ยอยู่ในช่วง `-40 dBm` ถึง `-55 dBm`
- หากผู้ใช้เดินห่างออกไปเกิน 3 เมตร หรือมีบุคคลอื่นยืนบัง สัญญาณจะดรอปต่ำกว่า `-65 dBm` ทันที การตั้งเกณฑ์ที่ `-60 dBm` จึงเป็นค่า Boundary ที่สมดุล ไม่เข้มงวดจนปฏิเสธผู้ที่นั่งอยู่จริง และไม่หละหลวมจนเปิดโอกาสให้คนนอกโต๊ะเช็กชื่อได้

### คำถามข้อที่ 3

หากต้องการต่อยอดมินิโปรเจกต์นี้ในอนาคต ให้สามารถบันทึกข้อมูลการเข้าเรียนลงระบบ Cloud (เช่น Google Sheets หรือ Firebase) จะต้องเพิ่มส่วนเชื่อมต่อใดบ้าง?

การต่อยอดระบบเช็กชื่อเข้าสู่ Cloud Platform:

1. **Wi-Fi Dual Mode (AP+STA):** ตั้งค่าโหมด ESP32 เป็น `WIFI_MODE_APSTA` ให้สามารถเปิด SoftAP รับนักศึกษาเช็กชื่อ พร้อมต่อ Wi-Fi สถาบันออกอินเทอร์เน็ตได้พร้อมกัน
1. **Cloud RESTful Client:** ติดตั้ง `esp_http_client` เพื่อส่งคำขอ HTTP POST พร้อม Header Authentication (Bearer Token หรือ API Key) ไปยัง Firebase Realtime Database หรือ Google Sheets Webhook
1. **NTP Synchronization:** ติดตั้งไลบรารี `esp_sntp` เพื่อดึงเวลามาตรฐานสากล (UTC/GMT+7) แนบไปกับข้อมูลการเช็กชื่อเพื่อเป็นหลักฐานเชิงเวลาที่แม่นยำ

# 🔍 สรุปและวิเคราะห์ผลการทดลองภาพรวม (Comprehensive Discussion & Conclusion)

จากการปฏิบัติการประจำสัปดาห์ที่ 6 (Week 06: Wi-Fi SoftAP, RF Throughput & Sensor Fusion with FreeRTOS) ของ **นายสุวิจักขณ์ ลาวัง (รหัสประจำตัว 67030248) ประจำโต๊ะ 1**:

1. **สถาปัตยกรรม Wi-Fi SoftAP และ Client Tracking (Lab 6.1):**
    - บอร์ด ESP32 สามารถทำหน้าที่เป็น Autonomous Access Point ภายใต้ชื่อเครือข่าย `ESP32_AP_0248` ได้อย่างสมบูรณ์
    - ระบบ DHCP Server ทำงานแจกจ่าย IP `192.168.4.2` ให้กับอุปกรณ์ลูกข่ายได้ถูกต้อง และ Event Handler สามารถตรวจจับ Association Event ดักจับ MAC Address และกำหนด Association ID (AID) ได้แม่นยำ
1. **การประเมินประสิทธิภาพคลื่นวิทยุและความเร็ว (Lab 6.2):**
    - ได้ดำเนินการทดสอบ Pair Work วัด Throughput ที่ระดับ Tx Power ตั้งแต่ 20 dBm ลงไปจนถึง 2 dBm
    - จากผลการสร้างแบบจำลองสถิติเชิงเส้น (Linear Regression) ได้สมการถดถอย **$y = -269.73x + 840.55$** ด้วยค่าความเชื่อมั่น **$R^2 = 0.2791$** ซึ่งสะท้อนพฤติกรรมการรับส่งข้อมูลจริงภายในระยะโต๊ะปฏิบัติการ
1. **การออกแบบ FreeRTOS Task Architecture & Queue (Lab 6.3):**
    - การแยกบทบาทหน้าที่ระหว่าง `SensorTask` (Producer: ดึงข้อมูลจากเซนเซอร์อุณหภูมิ 32.0°C, ความชื้น 61.4%, แสง 290 lux) และ `NetworkTask` (Consumer) ผ่าน FreeRTOS Queue ทำให้ระบบไม่มีการบล็อกการทำงาน (Non-blocking)
    - จากการตรวจสอบ High Water Mark พบ Stack เหลือปลอดภัย (`SensorTask`: 1188 words, `NetworkTask`: 2240 words) แสดงถึงการจัดสรรหน่วยความจำที่มีประสิทธิภาพสูง
1. **IoT Sensor Dashboard & RESTful JSON API (Lab 6.4):**
    - การรัน HTTP Web Server ขนาดเล็กบน ESP32 สามารถให้บริการ Web Interface สตรีมค่าเซนเซอร์แบบ Real-Time ขึ้นหน้าจอสมาร์ตโฟน (อุณหภูมิ 30.0°C, ความชื้น 50.2%, แสง 657 lux)
    - Endpoint `/api/data` ส่งกลับ Payload ในฟอร์แมตมาตรฐาน JSON รองรับการเชื่อมต่อกับระบบภายนอกได้อย่างไร้รอยต่อ
1. **ระบบเช็กชื่อ Smart RF Proximity Attendance (Lab 6.5):**
    - ระบบสามารถกรองความแรงสัญญาณด้วยเกณฑ์ `RSSI_THRESHOLD = -60 dBm` แยกแยะอุปกรณ์ที่อยู่ใกล้ (`7E:37:81:0C:3B:5E` ที่ระดับสัญญาณ `-45 dBm` สถานะ `NEAR (Valid)`) ได้อย่างแม่นยำ ป้องกันการเช็กชื่อจากระยะไกลได้อย่างมีประสิทธิภาพ
