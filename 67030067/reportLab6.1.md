#Lab6.1
I (31) boot: ESP-IDF v5.1.2-dirty 2nd stage bootloader
I (31) boot: compile time Oct 25 2026 16:24:32
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
I (96) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1fdbch (130492) map
I (152) esp_image: segment 1: paddr=0002fde4 vaddr=3ffb0000 size=00234h (  564) load
I (152) esp_image: segment 2: paddr=00030020 vaddr=400d0020 size=82f60h (536416) map
I (351) esp_image: segment 3: paddr=000b2f88 vaddr=3ffb0234 size=03848h (14408) load
I (357) esp_image: segment 4: paddr=000b67d8 vaddr=40080000 size=15c3ch (89148) load
I (405) boot: Loaded app from partition at offset 0x10000
I (406) boot: Disabling RNG early entropy source...
I (417) cpu_start: Multicore app
I (417) cpu_start: Pro cpu up.
I (418) cpu_start: Starting app cpu, entry point is 0x40081390
--- 0x40081390: call_start_cpu1 at /Users/kittikarnkaewnual/esp/esp-idf/components/esp_system/port/cpu_start.c:157
I (0) cpu_start: App cpu up.
I (435) cpu_start: Pro cpu start user code
I (435) cpu_start: cpu freq: 160000000 Hz
I (435) cpu_start: Application information:
I (440) cpu_start: Project name:     wifi_softap_tracking
I (446) cpu_start: App version:      029da6d
I (451) cpu_start: Compile time:     Oct 25 2026 16:24:25
I (457) cpu_start: ELF file SHA256:  2fa5f79acd845e1d...
I (463) cpu_start: ESP-IDF:          v5.1.2-dirty
I (469) cpu_start: Min chip rev:     v0.0
I (473) cpu_start: Max chip rev:     v3.99 
I (478) cpu_start: Chip rev:         v3.1
I (483) heap_init: Initializing. RAM available for dynamic allocation:
I (490) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (496) heap_init: At 3FFB7B18 len 000284E8 (161 KiB): DRAM
I (502) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (509) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (515) heap_init: At 40095C3C len 0000A3C4 (40 KiB): IRAM
I (523) spi_flash: detected chip: generic
I (526) spi_flash: flash io: dio
W (530) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (544) app_start: Starting scheduler on CPU0
I (548) app_start: Starting scheduler on CPU1
I (548) main_task: Started on CPU0
I (558) main_task: Calling app_main()
I (558) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (598) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (608) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (608) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (608) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbd598 (Default IP: 192.168.4.1)
I (618) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (638) wifi:wifi driver task: 3ffbfc38, prio:23, stack:6656, core=0
I (658) wifi:wifi firmware version: 91b9630
I (658) wifi:wifi certification version: v7.0
I (658) wifi:config NVS flash: enabled
I (658) wifi:config nano formating: disabled
I (668) wifi:Init data frame dynamic rx buffer num: 32
I (668) wifi:Init static rx mgmt buffer num: 5
I (668) wifi:Init management short buffer num: 32
I (678) wifi:Init dynamic tx buffer num: 32
I (678) wifi:Init static rx buffer size: 1600
I (688) wifi:Init static rx buffer num: 10
I (688) wifi:Init dynamic rx buffer num: 32
I (698) wifi_init: rx ba win: 6
I (698) wifi_init: tcpip mbox: 32
I (698) wifi_init: udp mbox: 6
I (708) wifi_init: tcp mbox: 6
I (708) wifi_init: tcp tx win: 5744
I (708) wifi_init: tcp rx win: 5744
I (718) wifi_init: tcp mss: 1440
I (718) wifi_init: WiFi IRAM OP enabled
I (728) wifi_init: WiFi RX IRAM OP enabled
I (728) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (738) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (748) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (758) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (758) phy_init: phy_version 4780,16b31a7,Sep 22 2023,20:42:16
I (838) wifi:mode : softAP (84:1f:e8:39:b4:49)
I (848) wifi:Total power save buffer number: 16
I (848) wifi:Init max length of beacon: 752/752
I (848) wifi:Init max length of beacon: 752/752
I (848) LAB_SOFTAP: ==================================================================
I (858) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF withIP: 192.168.4.1
I (868) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "MY_ESP32_AP", Channel:1
I (878) LAB_SOFTAP: ==================================================================
I (888) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (888) main_task: Returned from app_main()

kittikarnkaewnual@MM-2 Week-06-Wi-Fi-AP-Throughput-FreeRTOS % nc -v 192.168.4.1 8080
Connection to 192.168.4.1 port 8080 [tcp/http-alt] succeeded!
Hello ESP32





#คำถามท้ายบท
1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น 192.168.4.1 และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?
ตอบ เนื่องจาก ESP32 กำหนด IP Address เริ่มต้นของ SoftAP เป็น 192.168.4.1 เพื่อใช้เป็น Gateway ของเครือข่าย และ DHCP Server จะเริ่มแจกจ่าย IP Address ให้ Client โดยเริ่มจาก 192.168.4.2

2. สมาชิกตัวแปร mac ในโครงสร้าง wifi_event_ap_staconnected_t สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?
ตอบ สามารถนำ MAC Address ของอุปกรณ์ที่เชื่อมต่อมาเปรียบเทียบกับรายการ MAC Address ที่ได้รับอนุญาต หากตรงกับรายการจึงอนุญาตให้เชื่อมต่อหรือใช้งานระบบได้ แต่หากไม่ตรงจะปฏิเสธการเชื่อมต่อ ทั้งนี้ MAC Filtering เพียงอย่างเดียวไม่ใช่ระบบรักษาความปลอดภัยที่สมบูรณ์

3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า max_connection = 4) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?
ตอบ ESP32 จะไม่อนุญาตให้ Client เครื่องที่ 5 เชื่อมต่อเข้าสู่ SoftAP เนื่องจากมีจำนวนการเชื่อมต่อครบตามที่กำหนด โดยอุปกรณ์อาจส่งคำขอเชื่อมต่อผ่านคลื่นวิทยุได้ แต่ ESP32 จะปฏิเสธการเชื่อมต่อ ทำให้ไม่สามารถเข้าสู่เครือข่าย Wi-Fi ได้