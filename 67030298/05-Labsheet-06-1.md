## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

| อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android) | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ (ถ้าทราบ) |
| :--- | :--- | :---: | :---: |
| **อุปกรณ์ที่ 1 (โน๊ตบุ๊คของธนบดี 298)** | `EC:2E:98:0B:8F:B9` | `1` | `192.168.4.2` |
| **อุปกรณ์ที่ 2 (มือถือของอาทิตยา 260)** | `7A:DA:84:E9:38:4B` | `2` | `192.168.4.3` |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?
> เพราะเป็นค่าเริ่มต้น (Default) ที่กำหนดไว้ในไลบรารี `esp_netif` ของ ESP-IDF โดย DHCP Server จะเริ่มแจกจ่าย IP ตั้งแต่หมายเลข `192.168.4.2` เป็นต้นไป

2. สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?
> นำค่า `mac` ไปเทียบกับ White List หากค่าไม่ตรงกับที่อนุญาต สามารถสั่งยกเลิกการเชื่อมต่อ (Deauthenticate/Disconnect) อุปกรณ์นั้นได้ทันที ป้องกันคนภายนอกแอบใช้เครือข่าย

3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?
> ESP32 จะตอบกลับด้วยเฟรม `Association Response` สถานะ Fail (AP เต็มแล้ว) หรือส่งเฟรม `Deauthentication` เตะออก ทำให้เครื่องที่ 5 ไม่สามารถเชื่อมต่อได้

---

## Output Log อุปกรณ์ที่ 1 (โน๊ตบุ๊คของธนบดี 298)
```text
I (27) boot: ESP-IDF v6.0.2-dirty 2nd stage bootloader
I (27) boot: compile time Aug 10 2026 09:09:30
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
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a240h (107072) map
I (125) esp_image: segment 1: paddr=0002a268 vaddr=3ffb0000 size=04528h ( 17704) load
I (132) esp_image: segment 2: paddr=0002e798 vaddr=40080000 size=01880h (  6272) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=87e14h (556564) map
I (335) esp_image: segment 4: paddr=000b7e3c vaddr=40081880 size=13d88h ( 81288) load
I (368) esp_image: segment 5: paddr=000cbbcc vaddr=50000000 size=00028h (    40) load
I (379) boot: Loaded app from partition at offset 0x10000
I (379) boot: Disabling RNG early entropy source...
I (390) cpu_start: Multicore app
I (398) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (398) cpu_start: Pro cpu start user code
I (398) cpu_start: cpu freq: 160000000 Hz
I (400) app_init: Application information:
I (404) app_init: Project name:     main
I (408) app_init: App version:      02d10c3
I (411) app_init: Compile time:     Aug 10 2026 09:08:06
I (417) app_init: ELF file SHA256:  23e3edd44...
I (421) app_init: ESP-IDF:          v6.0.2-dirty
I (425) efuse_init: Min chip rev:     v0.0
I (429) efuse_init: Max chip rev:     v3.99
I (433) efuse_init: Chip rev:         v3.1
I (437) heap_init: Initializing. RAM available for dynamic allocation:
I (443) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (448) heap_init: At 3FFB8A20 len 000275E0 (157 KiB): DRAM
I (453) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (459) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (464) heap_init: At 40095608 len 0000A9F8 (42 KiB): IRAM
I (471) spi_flash: detected chip: generic
I (473) spi_flash: flash io: dio
W (476) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (490) main_task: Started on CPU0
I (490) main_task: Calling app_main()
I (490) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (530) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (530) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (530) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (540) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbddfc (Default IP: 192.168.4.1)     
I (540) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (560) wifi:wifi driver task: 3ffc0580, prio:23, stack:6656, core=0
I (580) wifi:wifi firmware version: 00ad238
I (580) wifi:wifi certification version: v7.0
I (580) wifi:config NVS flash: enabled
I (580) wifi:config nano formatting: disabled
I (580) wifi:Init data frame dynamic rx buffer num: 32
I (590) wifi:Init static rx mgmt buffer num: 5
I (590) wifi:Init management short buffer num: 32
I (590) wifi:Init dynamic tx buffer num: 32
I (600) wifi:Init static rx buffer size: 1600
I (600) wifi:Init static rx buffer num: 10
I (610) wifi:Init dynamic rx buffer num: 32
I (610) wifi_init: rx ba win: 6
I (610) wifi_init: accept mbox: 6
I (620) wifi_init: tcpip mbox: 32
I (620) wifi_init: udp mbox: 6
I (620) wifi_init: tcp mbox: 6
I (620) wifi_init: tcp tx win: 5760
I (630) wifi_init: tcp rx win: 5760
I (630) wifi_init: tcp mss: 1440
I (630) wifi_init: WiFi IRAM OP enabled
I (640) wifi_init: WiFi RX IRAM OP enabled
I (640) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (650) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (650) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (940) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (940) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (1030) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (1060) wifi:mode : softAP (84:1f:e8:39:bd:65)
I (1060) wifi:Total power save buffer number: 16
I (1060) wifi:Init max length of beacon: 752/752
I (1060) wifi:Init max length of beacon: 752/752
I (1070) LAB_SOFTAP: ==================================================================
I (1070) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1080) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "ESP32_AP_0298", Channel: 1
I (1090) LAB_SOFTAP: ==================================================================
I (1100) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (1100) main_task: Returned from app_main()
I (62110) wifi:station: ec:2e:98:0b:8f:b9 join, AID=1, bgn, 40U
I (62140) LAB_SOFTAP: =======================================================
I (62140) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (62150) LAB_SOFTAP:   -> Client MAC Address : EC:2E:98:0B:8F:B9
I (62150) LAB_SOFTAP:   -> Assigned AID       : 1
I (62160) LAB_SOFTAP: =======================================================
I (62400) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (65450) wifi:<ba-add>idx:2 (ifx:1, ec:2e:98:0b:8f:b9), tid:0, ssn:98, winSize:64
```

## Output Log อุปกรณ์ที่ 2 (มือถือของอาทิตยา 260)
```text
I (132710) wifi:new:<1,0>, old:<1,1>, ap:<1,0>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (132710) wifi:station: 7a:da:84:e9:38:4b join, AID=2, bgn, 20
I (132740) LAB_SOFTAP: =======================================================
I (132740) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (132750) LAB_SOFTAP:   -> Client MAC Address : 7A:DA:84:E9:38:4B
I (132750) LAB_SOFTAP:   -> Assigned AID       : 2
I (132760) LAB_SOFTAP: =======================================================
I (132820) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (133350) wifi:<ba-add>idx:3 (ifx:1, 7a:da:84:e9:38:4b), tid:0, ssn:2, winSize:64
```