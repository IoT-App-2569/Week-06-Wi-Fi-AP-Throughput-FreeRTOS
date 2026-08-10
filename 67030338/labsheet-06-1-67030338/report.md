# ใบงานที่ 6.1: การคอนฟิก ESP32 SoftAP และการสกัด Forensic Log ข้อมูล Client (Wi-Fi Access Point Mode)


```
--- 0x40080400: _invalid_pc_placeholder at C:/Users/09677/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug 10 2026 09:10:09
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19a68h (105064) map
I (124) esp_image: segment 1: paddr=00029a90 vaddr=3ffb0000 size=03eech ( 16108) load
I (131) esp_image: segment 2: paddr=0002d984 vaddr=40080000 size=02694h (  9876) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=87d7ch (556412) map
I (326) esp_image: segment 4: paddr=000b7da4 vaddr=40082694 size=15778h ( 87928) load
I (360) esp_image: segment 5: paddr=000cd524 vaddr=50000000 size=00020h (    32) load
I (372) boot: Loaded app from partition at offset 0x10000
I (372) boot: Disabling RNG early entropy source...
I (383) cpu_start: Multicore app
I (391) cpu_start: Pro cpu start user code
I (391) cpu_start: cpu freq: 160000000 Hz
I (391) app_init: Application information:
I (391) app_init: Project name:     wifi_softap_tracking
I (396) app_init: App version:      029da6d-dirty
I (401) app_init: Compile time:     Aug 10 2026 09:08:42
I (406) app_init: ELF file SHA256:  f26b1ef4e...
I (410) app_init: ESP-IDF:          v5.5.1-dirty
I (414) efuse_init: Min chip rev:     v0.0
I (418) efuse_init: Max chip rev:     v3.99 
I (422) efuse_init: Chip rev:         v3.1
I (426) heap_init: Initializing. RAM available for dynamic allocation:
I (433) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (438) heap_init: At 3FFB7FC8 len 00028038 (160 KiB): DRAM
I (443) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (448) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (454) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
W (460) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (472) spi_flash: detected chip: generic
I (476) spi_flash: flash io: dio
W (478) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (492) main_task: Started on CPU0
I (502) main_task: Calling app_main()
I (502) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (542) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (542) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (542) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (552) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbd9d4 (Default IP: 192.168.4.1)
I (562) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (572) wifi:wifi driver task: 3ffc0114, prio:23, stack:6656, core=0
I (592) wifi:wifi firmware version: 14da9b7
I (592) wifi:wifi certification version: v7.0
I (592) wifi:config NVS flash: enabled
I (592) wifi:config nano formatting: disabled
I (592) wifi:Init data frame dynamic rx buffer num: 32
I (602) wifi:Init static rx mgmt buffer num: 5
I (602) wifi:Init management short buffer num: 32
I (612) wifi:Init dynamic tx buffer num: 32
I (612) wifi:Init static rx buffer size: 1600
I (622) wifi:Init static rx buffer num: 10
I (622) wifi:Init dynamic rx buffer num: 32
I (622) wifi_init: rx ba win: 6
I (632) wifi_init: accept mbox: 6
I (632) wifi_init: tcpip mbox: 32
I (632) wifi_init: udp mbox: 6
I (632) wifi_init: tcp mbox: 6
I (642) wifi_init: tcp tx win: 5760
I (642) wifi_init: tcp rx win: 5760
I (642) wifi_init: tcp mss: 1440
I (652) wifi_init: WiFi IRAM OP enabled
I (652) wifi_init: WiFi RX IRAM OP enabled
I (652) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (662) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (672) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (682) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (682) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (772) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (842) wifi:mode : softAP (88:57:21:ad:64:99)
I (852) wifi:Total power save buffer number: 16
I (852) wifi:Init max length of beacon: 752/752
I (852) wifi:Init max length of beacon: 752/752
I (852) LAB_SOFTAP: ==================================================================
I (852) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (872) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "eem_Luna", Channel: 1
I (872) LAB_SOFTAP: ==================================================================
I (882) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (892) main_task: Returned from app_main()

```
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

| อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android) | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ (ถ้าทราบ) |
| :--------------------------------------- | :----------------------- | :------------------: | :---------------------------------: |
| **อุปกรณ์ที่ 1** (Android)               | `AA:BB:CC:DD:EE:FF`      |          1           |             192.168.4.2             |
| **อุปกรณ์ที่ 2**                         | `AA:BB:CC:DD:EE:02`      |          2           |             192.168.4.3             |
|                                          |                          |                      |                                     |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?
		Ans
			เป็นค่า Default ที่กำหนดมาในตัวไลบรารี TCP/IP Stack (`esp_netif` / `lwIP`) ของ ESP-IDF โดยจัดอยู่ในกลุ่ม **Private IP Address (RFC 1918) Class C** (ช่วง `192.168.0.0/16`) การเลือกใช้ Subnet `192.168.4.x` ช่วยลดโอกาส IP ชนกับวง LAN/Wi-Fi บ้านทั่วไป ซึ่งมักใช้ `192.168.0.x` หรือ `192.168.1.x`
2. สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?
		Ans
			- **ทำ MAC Whitelisting / Blacklisting:** นำค่า `evt->mac` ที่ได้จาก event `WIFI_EVENT_AP_STACONNECTED` ไปเปรียบเทียบกับรายการ MAC Address ที่อนุญาต (Whitelist) หรือต้องห้าม (Blacklist) ซึ่งบันทึกไว้ใน NVS หรือ Flash Memory
			- **การตัดการเชื่อมต่อทันที (Forced Deauthentication):** หากพบว่า `evt->mac` ไม่อยู่ในรายการที่ได้รับอนุญาต ให้สั่งงานฟังก์ชัน `esp_wifi_deauth_sta(evt->aid)` เพื่อส่งสัญญาณ Deauth ตัดการเชื่อมต่ออุปกรณ์นั้นออกจากระบบทันที
3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?
		Ans
			การจับคู่สัญญาณวิทยุ (Handshake) ล้มเหลว อุปกรณ์ Client จะไม่ได้รับ AID และไม่สามารถข้ามไปสู่ขั้นตอนการขอ IP Address ผ่าน DHCP ได้ บนหน้าจออุปกรณ์ Client จะขึ้นข้อความ เช่น _"Failed to connect to network"_, _"Unable to join the network"_ หรือค้างที่หน้า _"Obtaining IP address..."_ แล้วหลุดไป

