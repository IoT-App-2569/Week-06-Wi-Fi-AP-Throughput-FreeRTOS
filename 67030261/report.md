## Lab 1

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

| อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android) | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ (ถ้าทราบ) |
| :--- | :--- | :---: | :---: |
| **อุปกรณ์ที่ 1** | 02:E4:C0:11:FB:CC|1 |192.168.4.2 |
| **อุปกรณ์ที่ 2** |DA:26:AE:32:3B:AB |2 |192.168.4.3 |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?
```
ทุกครั้งที่เรียกฟังก์ชัน esp_netif_create_default_wifi_ap() โดยไม่ได้ตั้งค่า IP เอง ระบบจะดึงค่า struct ตัวนี้มาใช้เป็นค่าเริ่มต้น คือ 192.168.4.0/24 ก็เป็น private IP range ตาม RFC 1918 แต่ Espressif เลือกใช้ subnet .4.x เพื่อไม่ให้ชนกับ subnet เราเตอร์บ้านที่มักใช้ .0.x หรือ .1.x เวลา ESP32 ทำงานเป็น AP ควบคู่กับเครือข่ายอื่น

DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมาย 192.168.4.2
```
2. สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?
```
mac ที่ได้จาก event ทำหน้าที่เป็น กุญแจ สำหรับเทียบกับ whitelist/blacklist ของ MAC ที่อนุญาต แล้วใช้ esp_wifi_deauth_sta(aid) เป็นกลไกบังคับในการตัดการเชื่อมต่อ Client ที่ไม่ได้รับอนุญาตออกจาก SoftAP โดยอัตโนมัติ เป็นความปลอดภัยชั้นเสริมจาก WPA2
```
3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?
```
Client เครื่องที่ 5 จะถูก ESP32 ปฏิเสธด้วยการส่ง Deauthentication frame ออกไปทันทีในระดับสัญญาณวิทยุ ไดรเวอร์ Wi-Fi ของ ESP32 จะตัดสัญญาณ Client รายนั้นออกจาก BSS โดยอัตโนมัติ เนื่องจากจำนวน Station ที่เชื่อมต่ออยู่ครบ max_connection = 4 แล้ว ผลคือฝั่ง Client จะเห็นการเชื่อมต่อล้มเหลว/หลุดทันทีหลังพยายามเชื่อมต่อ
```


### Log จริง
```
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15848
load:0x40080400,len:3920
--- 0x40080400: _invalid_pc_placeholder at /Users/ittikorntongsima/My-Library/esp-idf/components/xtensa/xtensa_vectors.S:2259
entry 0x40080644
--- 0x40080644: call_start_cpu0 at /Users/ittikorntongsima/My-Library/esp-idf/components/bootloader/subproject/main/bootloader_start.c:27
I (27) boot: ESP-IDF v6.1-dev-3480-g44c77cbf46 2nd stage bootloader
I (27) boot: compile time Aug 23 2026 21:52:12
I (28) boot: Multicore bootloader
I (30) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (40) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (57) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (80) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a1f4h (106996) map
I (126) esp_image: segment 1: paddr=0002a21c vaddr=3ffb0000 size=045a8h ( 17832) load
I (133) esp_image: segment 2: paddr=0002e7cc vaddr=40080000 size=0184ch (  6220) load
I (136) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=87748h (554824) map
I (335) esp_image: segment 4: paddr=000b7770 vaddr=4008184c size=13dc0h ( 81344) load
I (368) esp_image: segment 5: paddr=000cb538 vaddr=50000000 size=00028h (    40) load
I (379) boot: Loaded app from partition at offset 0x10000
I (380) boot: Disabling RNG early entropy source...
I (390) cpu_start: Multicore app
I (398) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (399) cpu_start: Pro cpu start user code
I (399) cpu_start: cpu freq: 160000000 Hz
I (400) app_init: Application information:
I (404) app_init: Project name:     lab1
I (408) app_init: App version:      1
I (411) app_init: Compile time:     Aug 23 2026 21:52:09
I (416) app_init: ELF file SHA256:  594158b91...
I (421) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
I (426) efuse_init: Min chip rev:     v0.0
I (430) efuse_init: Max chip rev:     v3.99
I (434) efuse_init: Chip rev:         v3.1
I (438) heap_init: Initializing. RAM available for dynamic allocation:
I (444) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (449) heap_init: At 3FFB8A88 len 00027578 (157 KiB): DRAM
I (454) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (460) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (465) heap_init: At 4009560C len 0000A9F4 (42 KiB): IRAM
I (472) spi_flash: detected chip: generic
I (474) spi_flash: flash io: dio
W (477) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (491) main_task: Started on CPU0
I (501) main_task: Calling app_main()
I (501) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (521) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (521) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (521) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (531) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbdd7c (Default IP: 192.168.4.1)
I (531) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (551) wifi:wifi driver task: 3ffc0500, prio:23, stack:6656, core=0
I (561) wifi:wifi firmware version: 5d0a58b
I (561) wifi:wifi certification version: v7.0
I (561) wifi:config NVS flash: enabled
I (561) wifi:config nano formatting: disabled
I (561) wifi:Init data frame dynamic rx buffer num: 32
I (571) wifi:Init static rx mgmt buffer num: 5
I (571) wifi:Init management short buffer num: 32
I (581) wifi:Init dynamic tx buffer num: 32
I (581) wifi:Init static rx buffer size: 1600
I (581) wifi:Init static rx buffer num: 10
I (591) wifi:Init dynamic rx buffer num: 32
I (591) wifi_init: rx ba win: 6
I (591) wifi_init: accept mbox: 6
I (601) wifi_init: tcpip mbox: 32
I (601) wifi_init: udp mbox: 6
I (601) wifi_init: tcp mbox: 6
I (611) wifi_init: tcp tx win: 5760
I (611) wifi_init: tcp rx win: 5760
I (611) wifi_init: tcp mss: 1440
I (621) wifi_init: WiFi IRAM OP enabled
I (621) wifi_init: WiFi RX IRAM OP enabled
I (621) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (631) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (641) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (651) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (651) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (741) wifi:mode : softAP (8c:94:df:45:93:e5)
I (751) wifi:Total power save buffer number: 16
I (751) wifi:Init max length of beacon: 752/752
I (751) wifi:Init max length of beacon: 752/752
I (751) LAB_SOFTAP: ==================================================================
I (751) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (761) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "ESP32_AP_0261", Channel: 1
I (771) LAB_SOFTAP: ==================================================================
I (781) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (781) main_task: Returned from app_main()
I (22741) wifi:new:<1,0>, old:<1,1>, ap:<1,0>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (22741) wifi:station: 02:e4:c0:11:fb:cc join, AID=1, bgn, 20
I (22771) LAB_SOFTAP: =======================================================
I (22781) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (22781) LAB_SOFTAP:   -> Client MAC Address : 02:E4:C0:11:FB:CC
I (22781) LAB_SOFTAP:   -> Assigned AID       : 1
I (22791) LAB_SOFTAP: =======================================================
I (22931) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (23331) wifi:<ba-add>idx:2 (ifx:1, 02:e4:c0:11:fb:cc), tid:0, ssn:2, winSize:64
I (28011) wifi:<ba-add>idx:3 (ifx:1, 02:e4:c0:11:fb:cc), tid:1, ssn:0, winSize:64
I (28041) wifi:<ba-add>idx:4 (ifx:1, 02:e4:c0:11:fb:cc), tid:5, ssn:0, winSize:64
I (40511) wifi:station: 02:e4:c0:11:fb:cc leave, AID = 1, reason = 8, bss_flags is 691315, bss:0x3ffb9e3c
I (40511) wifi:new:<1,0>, old:<1,0>, ap:<1,0>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (40521) wifi:<ba-del>idx:2, tid:0
I (40521) wifi:<ba-del>idx:3, tid:1
I (40531) wifi:<ba-del>idx:4, tid:5
W (40531) LAB_SOFTAP: =======================================================
W (40541) LAB_SOFTAP: [FORENSIC EVENT]: Client Disconnected from ESP32 SoftAP!
W (40541) LAB_SOFTAP:   -> Client MAC Address : 02:E4:C0:11:FB:CC
W (40551) LAB_SOFTAP:   -> Released AID       : 1
W (40551) LAB_SOFTAP: =======================================================
I (40541) wifi:new:<1,1>, old:<1,0>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
W (40571) wifi:no need to send deauth when softap is sending deauth
I (40841) wifi:new:<1,0>, old:<1,1>, ap:<1,0>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (40841) wifi:station: 02:e4:c0:11:fb:cc join, AID=1, bgn, 20
I (40861) LAB_SOFTAP: =======================================================
I (40861) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (40871) LAB_SOFTAP:   -> Client MAC Address : 02:E4:C0:11:FB:CC
I (40871) LAB_SOFTAP:   -> Assigned AID       : 1
I (40881) LAB_SOFTAP: =======================================================
I (41011) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (41841) wifi:<ba-add>idx:2 (ifx:1, 02:e4:c0:11:fb:cc), tid:0, ssn:2, winSize:64
I (41941) wifi:<ba-add>idx:3 (ifx:1, 02:e4:c0:11:fb:cc), tid:1, ssn:0, winSize:64
E (41941) wifi:CCMP replay detected: A1=8c:94:df:45:93:e5 A2=02:e4:c0:11:fb:cc PN=11, RSC=11 seq=58352
I (42221) wifi:<ba-add>idx:4 (ifx:1, 02:e4:c0:11:fb:cc), tid:5, ssn:0, winSize:64
I (48811) wifi:new:<1,0>, old:<1,0>, ap:<1,0>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (48811) wifi:station: da:26:ae:32:3b:ab join, AID=2, bgn, 20
I (48841) LAB_SOFTAP: =======================================================
I (48841) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (48841) LAB_SOFTAP:   -> Client MAC Address : DA:26:AE:32:3B:AB
I (48851) LAB_SOFTAP:   -> Assigned AID       : 2
I (48851) LAB_SOFTAP: =======================================================
I (50061) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3

```
---

## Lab2

## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกค่าที่ได้จากการทดสอบในระดับ Tx Power ต่างๆ:

| การทดลองที่ | ค่า Tx Power ที่ตั้ง (dBm) | ค่า RSSI ที่อ่านได้จริง (dBm) | เวลาที่ใช้ (Seconds) | ความเร็วที่วัดได้ Throughput (Kbps) |
| :---: | :---: | :---: | :---: | :---: |
| **1** | 20 dBm (Max) |-53.2  |0.1675 |1130.92 |
| **2** | 15 dBm | -46.44 |0.1139 | 3,607.86|
| **3** | 10 dBm | -50.1 |0.1323 | 3,644.65|
| **4** | 5 dBm |-48.9 | 0.1051|3,974.27 |
| **5** | 2 dBm (Min) |-47.9 |0.1307 |3,232.71 |

---

## 6. งานวิเคราะห์ข้อมูลเชิงสถิติ (Data Science & Regression Task)

ให้นักศึกษานำค่า **RSSI (x-axis)** และ **Throughput (y-axis)** จากตารางทดลองไปสร้างแผนภาพใน Excel หรือ Python (Jupyter Notebook):

1. สร้างแผนภาพ **Scatter Plot** แสดงจุดข้อมูลระหว่าง RSSI กับ Speed
2. สร้างเส้นแนวโน้ม **Trendline / Regression Curve** (เช่น Logarithmic Regression: $y = a \cdot \ln(x) + b$)
3. คำนวณค่า **$R^2$ (Coefficient of Determination)** เพื่อประเมินความแม่นยำของสมการ
4. ระบุจุด **Threshold RSSI (dBm)** ที่ความเร็วเริ่มลดลงมากกว่า 50% จากระดับสูงสุด

<img width="741" height="477" alt="image" src="https://github.com/user-attachments/assets/b1cbd364-8c48-47d3-9ed9-facb26549969" />

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?
```
ค่า RSSI เพิ่มขึ้นจาก -53.2 เป็น -47.9 ซึ่งเพิ่มขึ้นมา 5.3 ความเร็วที่วัดได้ Throughput เพิ่มขึ้นมา -2,101.79
```
2. เหตุใดในระดับ RSSI ที่อ่อนกว่า `-80 dBm` ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?
```
PHY layer ปรับ Modulation ลงเมื่อสัญญาณอ่อนมาก Wi-Fi driver จะลด modulation scheme ลงอัตโนมัติ เพื่อรักษาความถูกต้องของข้อมูล แลกกับ raw bitrate ที่ลดลงมาก
TCP Retransmission/Congestion Control  ที่ RSSI ต่ำมาก Bit Error Rate สูงขึ้นมาก ทำให้ packet loss สูง TCP จะตีความว่ามี congestion แล้วลด window size ลงอัตโนมัติ ยิ่งลด throughput ซ้ำเข้าไปอีกชั้น  เป็นเหตุผลที่กราฟ RSSI vs Throughput มักมี จุดหักเห ชัดเจนแถว -70 ถึง -80 dBm ไม่ใช่ค่อย ๆ ลาดลงเรื่อย ๆ
```
3. สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?
```
    - Adaptive Data Rate อุปกรณ์ปลายทางอ่านค่า RSSI แล้วคำนวณ throughput ที่คาดว่าจะได้ล่วงหน้า เพื่อตัดสินใจว่าจะส่งข้อมูลขนาดใหญ่  หรือส่งแค่ข้อมูล sensor เล็ก ๆ ตอนนั้น
    - Predictive Handover/Reconnect ถ้าทำนายว่า Throughput กำลังจะตกต่ำกว่าเกณฑ์ที่ยอมรับได้ ระบบสามารถเตือนผู้ใช้ให้ขยับตำแหน่งอุปกรณ์ หรือสลับไปใช้ AP ตัวอื่นก่อนที่การเชื่อมต่อจะหลุดจริง
    - QoS-aware Buffering ปรับขนาด Queue/Buffer ของระบบ ให้ใหญ่ขึ้นล่วงหน้าเมื่อ RSSI มีแนวโน้มอ่อนลง เพื่อรองรับ throughput ที่จะลดลง โดยไม่ทำให้ sensor data สูญหาย
```


### Log จริง

## AP
```
I (3600) LAB_SOFTAP: =======================================================
I (3600) LAB_SOFTAP: [TCP SERVER SESSION 1]: Client connected from 192.168.4.2:60850
I (3760) LAB_SOFTAP: [TCP SERVER SESSION 1]: Transfer complete
I (3760) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (3760) LAB_SOFTAP: =======================================================
I (5770) LAB_SOFTAP: =======================================================
I (5780) LAB_SOFTAP: [TCP SERVER SESSION 2]: Client connected from 192.168.4.2:60851
I (5940) LAB_SOFTAP: [TCP SERVER SESSION 2]: Transfer complete
I (5940) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (5940) LAB_SOFTAP: =======================================================
I (7970) LAB_SOFTAP: =======================================================
I (7970) LAB_SOFTAP: [TCP SERVER SESSION 3]: Client connected from 192.168.4.2:60852
I (8120) LAB_SOFTAP: [TCP SERVER SESSION 3]: Transfer complete
I (8120) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (8120) LAB_SOFTAP: =======================================================
I (10150) LAB_SOFTAP: =======================================================
I (10150) LAB_SOFTAP: [TCP SERVER SESSION 4]: Client connected from 192.168.4.2:60853
I (10270) LAB_SOFTAP: [TCP SERVER SESSION 4]: Transfer complete
I (10270) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (10270) LAB_SOFTAP: =======================================================
I (12310) LAB_SOFTAP: =======================================================
I (12310) LAB_SOFTAP: [TCP SERVER SESSION 5]: Client connected from 192.168.4.2:60854
I (12430) LAB_SOFTAP: [TCP SERVER SESSION 5]: Transfer complete
I (12430) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (12430) LAB_SOFTAP: =======================================================
I (14470) LAB_SOFTAP: =======================================================
I (14470) LAB_SOFTAP: [TCP SERVER SESSION 6]: Client connected from 192.168.4.2:60855
I (14570) LAB_SOFTAP: [TCP SERVER SESSION 6]: Transfer complete
I (14570) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (14570) LAB_SOFTAP: =======================================================
I (16600) LAB_SOFTAP: =======================================================
I (16600) LAB_SOFTAP: [TCP SERVER SESSION 7]: Client connected from 192.168.4.2:60856
I (16730) LAB_SOFTAP: [TCP SERVER SESSION 7]: Transfer complete
I (16730) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (16730) LAB_SOFTAP: =======================================================
I (18750) LAB_SOFTAP: =======================================================
I (18750) LAB_SOFTAP: [TCP SERVER SESSION 8]: Client connected from 192.168.4.2:60857
I (18860) LAB_SOFTAP: [TCP SERVER SESSION 8]: Transfer complete
I (18860) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (18860) LAB_SOFTAP: =======================================================
I (20900) LAB_SOFTAP: =======================================================
I (20900) LAB_SOFTAP: [TCP SERVER SESSION 9]: Client connected from 192.168.4.2:60858
I (21120) LAB_SOFTAP: [TCP SERVER SESSION 9]: Transfer complete
I (21120) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (21120) LAB_SOFTAP: =======================================================
I (23130) LAB_SOFTAP: =======================================================
I (23130) LAB_SOFTAP: [TCP SERVER SESSION 10]: Client connected from 192.168.4.2:60859
I (23250) LAB_SOFTAP: [TCP SERVER SESSION 10]: Transfer complete
I (23250) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (23250) LAB_SOFTAP: =======================================================
```

## Client
```
I (11681) CLIENT_PROFILER: =======================================================
I (11681) CLIENT_PROFILER:  [BENCHMARK RESULT 1/10]
I (11681) CLIENT_PROFILER:   -> Current RSSI       : -52 dBm
I (11681) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (11691) CLIENT_PROFILER:   -> Time Elapsed       : 0.145 Seconds
I (11691) CLIENT_PROFILER:   -> Measured Speed     : 2822.10 Kbps
I (11701) CLIENT_PROFILER: =======================================================
I (13711) CLIENT_PROFILER: [ROUND 2/10]: Connecting to 192.168.4.1:8080
I (13871) CLIENT_PROFILER: =======================================================
I (13871) CLIENT_PROFILER:  [BENCHMARK RESULT 2/10]
I (13871) CLIENT_PROFILER:   -> Current RSSI       : -53 dBm
I (13871) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (13881) CLIENT_PROFILER:   -> Time Elapsed       : 0.154 Seconds
I (13891) CLIENT_PROFILER:   -> Measured Speed     : 2653.67 Kbps
I (13891) CLIENT_PROFILER: =======================================================
I (15901) CLIENT_PROFILER: [ROUND 3/10]: Connecting to 192.168.4.1:8080
I (16051) CLIENT_PROFILER: =======================================================
I (16051) CLIENT_PROFILER:  [BENCHMARK RESULT 3/10]
I (16051) CLIENT_PROFILER:   -> Current RSSI       : -50 dBm
I (16061) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (16061) CLIENT_PROFILER:   -> Time Elapsed       : 0.145 Seconds
I (16071) CLIENT_PROFILER:   -> Measured Speed     : 2829.16 Kbps
I (16071) CLIENT_PROFILER: =======================================================
I (18081) CLIENT_PROFILER: [ROUND 4/10]: Connecting to 192.168.4.1:8080
I (18211) CLIENT_PROFILER: =======================================================
I (18211) CLIENT_PROFILER:  [BENCHMARK RESULT 4/10]
I (18211) CLIENT_PROFILER:   -> Current RSSI       : -46 dBm
I (18211) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (18221) CLIENT_PROFILER:   -> Time Elapsed       : 0.121 Seconds
I (18231) CLIENT_PROFILER:   -> Measured Speed     : 3376.97 Kbps
I (18231) CLIENT_PROFILER: =======================================================
I (20241) CLIENT_PROFILER: [ROUND 5/10]: Connecting to 192.168.4.1:8080
I (20361) CLIENT_PROFILER: =======================================================
I (20371) CLIENT_PROFILER:  [BENCHMARK RESULT 5/10]
I (20371) CLIENT_PROFILER:   -> Current RSSI       : -44 dBm
I (20371) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (20381) CLIENT_PROFILER:   -> Time Elapsed       : 0.117 Seconds
I (20381) CLIENT_PROFILER:   -> Measured Speed     : 3504.63 Kbps
I (20391) CLIENT_PROFILER: =======================================================
I (22401) CLIENT_PROFILER: [ROUND 6/10]: Connecting to 192.168.4.1:8080
I (22501) CLIENT_PROFILER: =======================================================
I (22501) CLIENT_PROFILER:  [BENCHMARK RESULT 6/10]
I (22501) CLIENT_PROFILER:   -> Current RSSI       : -44 dBm
I (22511) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (22511) CLIENT_PROFILER:   -> Time Elapsed       : 0.098 Seconds
I (22521) CLIENT_PROFILER:   -> Measured Speed     : 4171.93 Kbps
I (22531) CLIENT_PROFILER: =======================================================
I (24531) CLIENT_PROFILER: [ROUND 7/10]: Connecting to 192.168.4.1:8080
I (24651) CLIENT_PROFILER: =======================================================
I (24651) CLIENT_PROFILER:  [BENCHMARK RESULT 7/10]
I (24651) CLIENT_PROFILER:   -> Current RSSI       : -47 dBm
I (24661) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (24661) CLIENT_PROFILER:   -> Time Elapsed       : 0.117 Seconds
I (24671) CLIENT_PROFILER:   -> Measured Speed     : 3497.24 Kbps
I (24671) CLIENT_PROFILER: =======================================================
I (26681) CLIENT_PROFILER: [ROUND 8/10]: Connecting to 192.168.4.1:8080
I (26801) CLIENT_PROFILER: =======================================================
I (26801) CLIENT_PROFILER:  [BENCHMARK RESULT 8/10]
I (26801) CLIENT_PROFILER:   -> Current RSSI       : -48 dBm
I (26801) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (26811) CLIENT_PROFILER:   -> Time Elapsed       : 0.112 Seconds
I (26811) CLIENT_PROFILER:   -> Measured Speed     : 3653.00 Kbps
I (26821) CLIENT_PROFILER: =======================================================
I (28831) CLIENT_PROFILER: [ROUND 9/10]: Connecting to 192.168.4.1:8080
I (29021) CLIENT_PROFILER: =======================================================
I (29021) CLIENT_PROFILER:  [BENCHMARK RESULT 9/10]
I (29031) CLIENT_PROFILER:   -> Current RSSI       : -47 dBm
I (29031) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (29041) CLIENT_PROFILER:   -> Time Elapsed       : 0.183 Seconds
I (29041) CLIENT_PROFILER:   -> Measured Speed     : 2241.31 Kbps
I (29051) CLIENT_PROFILER: =======================================================
I (31061) CLIENT_PROFILER: [ROUND 10/10]: Connecting to 192.168.4.1:8080
I (31181) CLIENT_PROFILER: =======================================================
I (31181) CLIENT_PROFILER:  [BENCHMARK RESULT 10/10]
I (31181) CLIENT_PROFILER:   -> Current RSSI       : -48 dBm
I (31191) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (31191) CLIENT_PROFILER:   -> Time Elapsed       : 0.115 Seconds
I (31201) CLIENT_PROFILER:   -> Measured Speed     : 3577.04 Kbps
I (31201) CLIENT_PROFILER: =======================================================
I (33211) CLIENT_PROFILER: All benchmark rounds completed
```
---

## Lab 3


## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :--- | :---: | :---: | :---: |
| **`SensorCollectorTask`** | 3072 |2020 | ปลอดภัย เหลือ 34.24% |
| **`NetworkCommTask`** | 4096 |3072 | ปลอดภัย เหลือ 25%|

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
```
Queue มีกลไก mutual exclusion ในตัวอยู่แล้ว ทำให้การอ่าน เขียนข้อมูลระหว่าง 2 Task เกิดขึ้นแบบอะตอมิก ไม่มีทาง race condition หรือข้อมูลถูกเขียนทับกลางคัน ต่างจาก Global Variable ที่ถ้า Task หนึ่งกำลังเขียนอยู่แล้วอีก Task แย่ง context switch เข้ามาอ่านพร้อมกัน จะได้ข้อมูลครึ่งเก่าครึ่งใหม่ นอกจาก Queue ยังมี buffer รองรับให้ Task ที่ผลิตข้อมูลเร็วกว่าไม่ต้องรอ Task ที่บริโภคช้ากว่าทันที
```
2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
```
ใช้เป็นตัวชี้วัดว่า Task นั้นเคยใช้ Stack ไปมากที่สุดกี่ byte ตลอดการทำงาน ถ้าค่าที่เหลือ ใกล้ 0 หรือติดลบ = สัญญาณเตือนล่วงหน้าของ Stack Overflow ซึ่งเป็นสาเหตุคลาสสิกของอาการค้างหรือ รีเซ็ตแบบสุ่มใน RTOS ที่ debug ยากมากถ้าไม่มีค่านี้ จึงใช้ปรับขนาด Stack ให้พอดี ไม่มากเกินจนเปลือง RAM ไม่น้อยเกินจนเต็ม
```
3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
```
Queue จะเริ่มเต็ม เพราะ Sensor Task สร้างข้อมูลเร็วกว่า Network Task ใช้มากเมื่อ Queue เต็ม พฤติกรรมขึ้นกับการเรียกใช้ xQueueSend()
ถ้าตั้ง timeout ไว้  Sensor Task จะ block รอจนกว่าจะมีที่ว่าง ทำให้ Sensor Task ทำงานช้าลงตาม Network Task ไปด้วย ถ้าไม่รอ ข้อมูลที่ส่งไม่ทันจะสูญหาย ไม่ถูกเก็บ

วิธีเเก้คือเพิ่มขนาด Queue ให้รองรับ burst ได้ระดับหนึ่ง ใช้ overwrite ค่าล่าสุด ถ้าสนใจแค่ค่าปัจจุบัน ไม่สนใจค่าเก่าหรือปรับให้ Network Task ทำงานเร็วขึ้น ลดความถี่การส่งของ Sensor Task ลงให้สมดุลกัน
```

### Log 
```
rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
configsip: 0, SPIWP:0xee
clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
mode:DIO, clock div:2
load:0x3fff0040,len:6272
load:0x40078000,len:15848
load:0x40080400,len:3920
--- 0x40080400: _invalid_pc_placeholder at /Users/ittikorntongsima/My-Library/esp-idf/components/xtensa/xtensa_vectors.S:2259
entry 0x40080644
--- 0x40080644: call_start_cpu0 at /Users/ittikorntongsima/My-Library/esp-idf/components/bootloader/subproject/main/bootloader_start.c:27
I (27) boot: ESP-IDF v6.1-dev-3480-g44c77cbf46 2nd stage bootloader
I (27) boot: compile time Aug 23 2026 22:47:51
I (28) boot: Multicore bootloader
I (30) boot: chip revision: v3.1
I (33) boot.esp32: SPI Speed      : 40MHz
I (37) boot.esp32: SPI Mode       : DIO
I (40) boot.esp32: SPI Flash Size : 2MB
I (44) boot: Enabling RNG early entropy source...
I (49) boot: Partition Table:
I (51) boot: ## Label            Usage          Type ST Offset   Length
I (57) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (64) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (71) boot:  2 factory          factory app      00 00 00010000 00100000
I (77) boot: End of partition table
I (80) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=08b58h ( 35672) map
I (101) esp_image: segment 1: paddr=00018b80 vaddr=3ffb0000 size=02a7ch ( 10876) load
I (105) esp_image: segment 2: paddr=0001b604 vaddr=40080000 size=04a14h ( 18964) load
I (113) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=0c770h ( 51056) map
I (131) esp_image: segment 4: paddr=0002c798 vaddr=40084a14 size=062a4h ( 25252) load
I (142) esp_image: segment 5: paddr=00032a44 vaddr=50000000 size=00028h (    40) load
I (148) boot: Loaded app from partition at offset 0x10000
I (148) boot: Disabling RNG early entropy source...
I (160) cpu_start: Multicore app
I (168) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (169) cpu_start: Pro cpu start user code
I (169) cpu_start: cpu freq: 160000000 Hz
I (170) app_init: Application information:
I (174) app_init: Project name:     lab3
I (178) app_init: App version:      1
I (181) app_init: Compile time:     Aug 23 2026 22:47:43
I (186) app_init: ELF file SHA256:  a91c577e7...
I (191) app_init: ESP-IDF:          v6.1-dev-3480-g44c77cbf46
I (196) efuse_init: Min chip rev:     v0.0
I (200) efuse_init: Max chip rev:     v3.99
I (204) efuse_init: Chip rev:         v3.1
I (208) heap_init: Initializing. RAM available for dynamic allocation:
I (214) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (219) heap_init: At 3FFB3430 len 0002CBD0 (178 KiB): DRAM
I (224) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (230) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (235) heap_init: At 4008ACB8 len 00015348 (84 KiB): IRAM
I (242) spi_flash: detected chip: generic
I (244) spi_flash: flash io: dio
W (247) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (261) main_task: Started on CPU0
I (271) main_task: Calling app_main()
I (271) LAB_FREERTOS_QUEUE: ==================================================================
I (271) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (281) LAB_FREERTOS_QUEUE: ==================================================================
I (281) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 0
I (291) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.2 C, Hum: 61.6 %, Lux: 546
I (301) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (311) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (311) LAB_FREERTOS_QUEUE: =======================================================
I (321) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (331) LAB_FREERTOS_QUEUE:   -> Timestamp   : 30 ms
I (331) LAB_FREERTOS_QUEUE:   -> Temperature : 29.20 degC
I (341) LAB_FREERTOS_QUEUE:   -> Humidity    : 61.60 %
I (341) LAB_FREERTOS_QUEUE:   -> Light Lux   : 546 lux
I (351) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (361) LAB_FREERTOS_QUEUE: =======================================================
I (361) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)
I (371) main_task: Returned from app_main()
I (1811) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 30.5 C, Hum: 52.7 %, Lux: 347
I (1811) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (1811) LAB_FREERTOS_QUEUE: =======================================================
I (1821) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (1821) LAB_FREERTOS_QUEUE:   -> Timestamp   : 1550 ms
I (1831) LAB_FREERTOS_QUEUE:   -> Temperature : 30.50 degC
I (1831) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.70 %
I (1841) LAB_FREERTOS_QUEUE:   -> Light Lux   : 347 lux
I (1841) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (1851) LAB_FREERTOS_QUEUE: =======================================================
I (1861) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)
I (3311) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.2 C, Hum: 61.7 %, Lux: 419
I (3311) LAB_FREERTOS_QUEUE: =======================================================
I (3311) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (3311) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (3321) LAB_FREERTOS_QUEUE:   -> Timestamp   : 3050 ms
I (3331) LAB_FREERTOS_QUEUE:   -> Temperature : 26.20 degC
I (3331) LAB_FREERTOS_QUEUE:   -> Humidity    : 61.70 %
I (3341) LAB_FREERTOS_QUEUE:   -> Light Lux   : 419 lux
I (3341) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (3351) LAB_FREERTOS_QUEUE: =======================================================
I (3361) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)
I (4821) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.1 C, Hum: 64.2 %, Lux: 531
I (4821) LAB_FREERTOS_QUEUE: =======================================================
I (4821) FORENSIC_STACK:   -> SensorTask Stack Remaining: 2020 words (2020 bytes)
I (4821) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (4831) LAB_FREERTOS_QUEUE:   -> Timestamp   : 4560 ms
I (4841) LAB_FREERTOS_QUEUE:   -> Temperature : 28.10 degC
I (4841) LAB_FREERTOS_QUEUE:   -> Humidity    : 64.20 %
I (4851) LAB_FREERTOS_QUEUE:   -> Light Lux   : 531 lux
I (4851) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (4861) LAB_FREERTOS_QUEUE: =======================================================
I (4871) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 3072 words (3072 bytes)

Done
ittikorntongsima@Sloth lab3 %
```
---

## lab 4

## 7. ตารางบันทึกผลการทดลอง (Experiment Results)

### 7.1 บันทึกข้อมูลจาก Dashboard

| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :------: | :--------------: | :----------: | :-------: | :------------: |
|  **1**   |      33.6            |    56.0          |     485      |       41160         |
|  **2**   |       26.8           |      64.5        |    602       |       69850         |
|  **3**   |     33.6             |    66.0          |   469       |    72870            |

### 7.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response จาก Browser:

```json
{"temperature":29.30,"humidity":66.40,"light_lux":676,"timestamp_ms":106090}
```

---

## 8. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
```
vNetworkTaskเขียนค่าลง g_latest_data เป็นระยะๆ ส่วน HTTP Handler จะอ่านค่านี้ไปสร้างหน้า Dashboard ทุกครั้งที่มี Client ยิง Request เข้ามา ทั้งสองฝั่งทำงานคนละ Task กัน จึงอาจถูก Scheduler สลับ context เข้ามาแทรกกลางคันได้ตลอด
```
2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?
```
ไม่ใช่ Thread เดียวกับ FreeRTOS Task  
esp_http_server component จะสร้าง FreeRTOS Task ของตัวเองขึ้นมาต่างหาก เพื่อรัน accept loop และเรียก URI Handler ที่ลงทะเบียนไว้ 
```
3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
```
meta refresh
   - ข้อดี ทำง่าย ไม่ต้องเขียน JS เลย, ใช้ได้แม้ browser ปิด JavaScript
   - ข้อเสีย ต้องโหลดทั้งหน้าใหม่ทุกครั้ง , เปลืองแบนด์วิดท์เพราะดาวน์โหลด HTML/CSS ซ้ำทุกรอบทั้งที่ข้อมูลเปลี่ยนแค่ตัวเลขไม่กี่ตัว, ปรับ interval แบบไดนามิกไม่ได้
JS fetch()
   - ข้อดี อัปเดตเฉพาะข้อมูลที่เปลี่ยน  ไม่กระพริบจอ ไม่เสียตำแหน่ง scroll, ประหยัด bandwidth กว่ามาก, ควบคุม logic เพิ่มได้
   - ข้อเสีย ต้องเขียนโค้ด JS เพิ่ม, ถ้า client ปิด JS จะใช้ไม่ได้เลย, ต้องจัดการ timeout เองถ้า ESP32 ตอบช้า
```

<img width="1080" height="810" alt="IMG_0038" src="https://github.com/user-attachments/assets/63f0e9c8-8bda-4d3e-ae8b-adf41fe8bf1a" />

---

## lab 5


## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

### 5.1 ตารางบันทึกการเช็กชื่อผ่าน RF Proximity

| ลำดับที่ | ชื่อสมาร์ตโฟน / MAC Address | ระดับ RSSI (dBm) | ระยะทางประเมิน (Near/Far) | ผลการลงชื่อ (Passed/Rejected) |
| :---: | :--- | :---: | :---: | :---: |
| **1** |B6:42:F6:1E:E6:07 | -45 dBm| NEAR (Valid)|Passed |
| **2** |06:EF:A5:A9:F3:72| -45 dBm|NEAR (Valid) |Passed |

---

## 6. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การใช้ **RF Signal Proximity (RSSI)** ร่วมกับ **HTTP Web Server** บน ESP32 แก้ปัญหาการฝากเช็กชื่อแทนกันในห้องเรียนได้อย่างไร?
```
ปัญหาของระบบเช็กชื่อผ่านเว็บทั่วไป คือทำจากที่ไหนก็ได้ ใครก็กดแทนกันได้โดยไม่ต้องอยู่ในห้องจริง การเพิ่มเงื่อนไข RSSI เข้าไปโดยให้ ESP32 ยอมรับคำขอเช็กชื่อ เฉพาะอุปกรณ์ที่มีค่าความแรงสัญญาณเกินเกณฑ์ที่กำหนดเท่านั้น ซึ่งหมายความว่ามือถือของนักศึกษาต้องอยู่ใกล้ ESP32 จริง ๆ จึงจะเช็กชื่อผ่าน ทำให้ไม่สามารถฝากเพื่อนกดเช็กชื่อจากนอกห้องหรือระยะไกลได้อีกต่อไป 
```
2. เหตุใดระดับเกณฑ์ RSSI ที่ `-55 dBm` จึงเหมาะสมสำหรับการระบุตำแหน่งอุปกรณ์ให้อยู่ภายในรัศมีโต๊ะปฏิบัติการ?
```
โดยหลักการทั่วไป ค่า RSSI ของ Wi-Fi ในอาคาร มักลดลงตามระยะทางแบบไม่เป็นเชิงเส้น เนื่องจากการลดทอนสัญญาณจากผนัง อุปกรณ์ และสิ่งกีดขวาง ค่าประมาณคร่าว ๆ ที่ใช้กันทั่วไปคือ
    -30 ถึง -50 dBm = สัญญาณดีมาก ระยะใกล้มาก 
    -50 ถึง -60 dBm = สัญญาณดี ระยะใกล้-ปานกลาง ประมาณ 2–5 เมตร
    -60 dBm ลงไป = สัญญาณเริ่มอ่อน ระยะไกลขึ้นหรือมีสิ่งกีดขวาง
ค่า -55 dBm จึงอยู่ในช่วงกึ่งกลางของ สัญญาณดี ซึ่งมักตรงกับระยะไม่กี่เมตรพอดี ใกล้เคียงกับขนาดของโต๊ะปฏิบัติการ 1 ตัว ทำให้ตัดขอบเขตได้ค่อนข้างแม่น
```
3. หากต้องการต่อยอดมินิโปรเจกต์นี้ในอนาคต ให้สามารถบันทึกข้อมูลการเข้าเรียนลงระบบ Cloud (เช่น Google Sheets หรือ Firebase) จะต้องเพิ่มส่วนเชื่อมต่อใดบ้าง?
```
- HTTP Client (esp_http_client) ของเดิม ESP32 ทำหน้าที่เป็น Web Server (รับ request) แต่การส่งข้อมูลออกไป Cloud ต้องให้ ESP32 เป็น Client ยิง HTTP POST ออกไปแทน
- โหมด Wi-Fi แบบ STA หรือ AP+STA  เพราะ SoftAP เดิมไม่มีทางออกอินเทอร์เน็ต ต้องต่อ ESP32 เข้ากับเครือข่ายที่มีอินเทอร์เน็ตจริง จึงจะยิงข้อมูลออก Cloud ได้
- TLS/SSL support เพราะทั้ง Google Apps Script และ Firebase REST API ใช้ HTTPS ทั้งคู่ ต้องมี certificate bundle รองรับ
- ตัวกลางรับข้อมูล (Endpoint)
    Google Sheets ต้องสร้าง Google Apps Script Web App เป็นตัวกลางก่อน แล้วยิง HTTP POST ไปที่ URL ของ Web App นั้น
    Firebase ใช้ Firebase Realtime Database REST API หรือ Firestore REST API ได้โดยตรง ผ่าน API Key/Database Secret
- JSON Library สำหรับแปลงข้อมูล MAC, เวลาที่เช็กชื่อ, RSSI ให้เป็น JSON payload ก่อนส่ง
- SNTP Client  ซิงก์เวลาให้ ESP32 มี timestamp ที่ถูกต้อง เพราะ ESP32 เองไม่มีนาฬิกาเรียลไทม์ในตัว
- NVS  เก็บ Wi-Fi credentials และ API Key/URL ของ Cloud อย่างปลอดภัย ไม่ hardcode ในซอร์สโค้ด
```
---

<img width="1080" height="810" alt="IMG_0037" src="https://github.com/user-attachments/assets/b2951eb0-f515-42c6-9951-60a20d10fb01" />
