# ใบงานที่ 6.2: การประเมินความสัมพันธ์ RSSI vs Throughput ด้วย Software Tx-Power Control (Pair Work 👥)

## 1
```
--- 0x40080400: _invalid_pc_placeholder at C:/Users/09677/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/09677/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1-dirty 2nd stage bootloader
I (29) boot: compile time Aug 10 2026 10:05:04
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19a00h (104960) map
I (124) esp_image: segment 1: paddr=00029a28 vaddr=3ffb0000 size=03eech ( 16108) load
I (131) esp_image: segment 2: paddr=0002d91c vaddr=40080000 size=026fch (  9980) load
I (135) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=870e8h (553192) map
I (325) esp_image: segment 4: paddr=000b7110 vaddr=400826fc size=15710h ( 87824) load
I (359) esp_image: segment 5: paddr=000cc828 vaddr=50000000 size=00020h (    32) load
I (371) boot: Loaded app from partition at offset 0x10000
I (371) boot: Disabling RNG early entropy source...
I (382) cpu_start: Multicore app
I (390) cpu_start: Pro cpu start user code
I (390) cpu_start: cpu freq: 160000000 Hz
I (390) app_init: Application information:
I (390) app_init: Project name:     rssi_speed_profiler
I (395) app_init: App version:      029da6d-dirty
I (400) app_init: Compile time:     Aug 10 2026 10:03:35
I (405) app_init: ELF file SHA256:  2840285e2...
I (409) app_init: ESP-IDF:          v5.5.1-dirty
I (413) efuse_init: Min chip rev:     v0.0
I (417) efuse_init: Max chip rev:     v3.99 
I (421) efuse_init: Chip rev:         v3.1
I (425) heap_init: Initializing. RAM available for dynamic allocation:
I (431) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (436) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (442) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (447) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (452) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
W (459) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (471) spi_flash: detected chip: generic
I (474) spi_flash: flash io: dio
W (477) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (490) main_task: Started on CPU0
I (500) main_task: Calling app_main()
I (500) CLIENT_PROFILER: [FORENSIC]: Call nvs_flash_init()
I (540) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_init()
I (540) CLIENT_PROFILER: [FORENSIC]: Call esp_event_loop_create_default()
I (540) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (550) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_init(&config)
I (560) wifi:wifi driver task: 3ffc006c, prio:23, stack:6656, core=0
I (580) wifi:wifi firmware version: 14da9b7
I (580) wifi:wifi certification version: v7.0
I (580) wifi:config NVS flash: enabled
I (580) wifi:config nano formatting: disabled
I (580) wifi:Init data frame dynamic rx buffer num: 32
I (590) wifi:Init static rx mgmt buffer num: 5
I (590) wifi:Init management short buffer num: 32
I (600) wifi:Init dynamic tx buffer num: 32
I (600) wifi:Init static rx buffer size: 1600
I (610) wifi:Init static rx buffer num: 10
I (610) wifi:Init dynamic rx buffer num: 32
I (610) wifi_init: rx ba win: 6
I (620) wifi_init: accept mbox: 6
I (620) wifi_init: tcpip mbox: 32
I (620) wifi_init: udp mbox: 6
I (620) wifi_init: tcp mbox: 6
I (630) wifi_init: tcp tx win: 5760
I (630) wifi_init: tcp rx win: 5760
I (630) wifi_init: tcp mss: 1440
I (640) wifi_init: WiFi IRAM OP enabled
I (640) wifi_init: WiFi RX IRAM OP enabled
I (640) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (650) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (660) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_start()
I (660) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (750) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (780) wifi:mode : sta (88:57:21:ad:64:98)
I (780) wifi:enable tsf
I (780) CLIENT_PROFILER: Client profiler ready: 50 KB x 10 rounds
I (780) CLIENT_PROFILER: [FORENSIC EVENT]: Station started; connecting to ESP32_AP_0351
I (790) main_task: Returned from app_main()
I (1140) wifi:new:<1,1>, old:<1,0>, ap:<255,255>, sta:<1,1>, prof:1, snd_ch_cfg:0x0
I (1140) wifi:state: init -> auth (0xb0)
I (1150) wifi:state: auth -> assoc (0x0)
I (1160) wifi:state: assoc -> run (0x10)
I (1180) wifi:connected with ESP32_AP_0351, aid = 1, channel 1, 40U, bssid = 88:57:21:ae:44:85
I (1180) wifi:security: WPA2-PSK, phy: bgn, rssi: -78
I (1250) wifi:pm start, type: 1

I (1250) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1250) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (2280) esp_netif_handlers: sta ip: 192.168.4.2, mask: 255.255.255.0, gw: 192.168.4.1
I (2280) CLIENT_PROFILER: [FORENSIC EVENT]: Connected; IP=192.168.4.2
I (2280) CLIENT_PROFILER: [ROUND 1/10]: Connecting to 192.168.4.1:8080
I (2300) wifi:<ba-add>idx:0 (ifx:0, 88:57:21:ae:44:85), tid:0, ssn:0, winSize:64
I (2910) CLIENT_PROFILER: =======================================================
I (2920) CLIENT_PROFILER:  [BENCHMARK RESULT 1/10]
I (2920) CLIENT_PROFILER:   -> Current RSSI       : -72 dBm
I (2920) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (2930) CLIENT_PROFILER:   -> Time Elapsed       : 0.204 Seconds
I (2930) CLIENT_PROFILER:   -> Measured Speed     : 2007.73 Kbps
I (2940) CLIENT_PROFILER: =======================================================
I (4950) CLIENT_PROFILER: [ROUND 2/10]: Connecting to 192.168.4.1:8080
I (5190) CLIENT_PROFILER: =======================================================
I (5200) CLIENT_PROFILER:  [BENCHMARK RESULT 2/10]
I (5200) CLIENT_PROFILER:   -> Current RSSI       : -71 dBm
I (5200) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (5210) CLIENT_PROFILER:   -> Time Elapsed       : 0.242 Seconds
I (5210) CLIENT_PROFILER:   -> Measured Speed     : 1695.64 Kbps
I (5220) CLIENT_PROFILER: =======================================================
I (7230) CLIENT_PROFILER: [ROUND 3/10]: Connecting to 192.168.4.1:8080
I (7560) CLIENT_PROFILER: =======================================================
I (7560) CLIENT_PROFILER:  [BENCHMARK RESULT 3/10]
I (7560) CLIENT_PROFILER:   -> Current RSSI       : -73 dBm
I (7570) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (7570) CLIENT_PROFILER:   -> Time Elapsed       : 0.328 Seconds
I (7580) CLIENT_PROFILER:   -> Measured Speed     : 1250.18 Kbps
I (7590) CLIENT_PROFILER: =======================================================
I (9590) CLIENT_PROFILER: [ROUND 4/10]: Connecting to 192.168.4.1:8080
I (9830) CLIENT_PROFILER: =======================================================
I (9830) CLIENT_PROFILER:  [BENCHMARK RESULT 4/10]
I (9830) CLIENT_PROFILER:   -> Current RSSI       : -70 dBm
I (9830) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (9840) CLIENT_PROFILER:   -> Time Elapsed       : 0.225 Seconds
I (9840) CLIENT_PROFILER:   -> Measured Speed     : 1821.50 Kbps
I (9850) CLIENT_PROFILER: =======================================================
I (11860) CLIENT_PROFILER: [ROUND 5/10]: Connecting to 192.168.4.1:8080
I (12130) CLIENT_PROFILER: =======================================================
I (12130) CLIENT_PROFILER:  [BENCHMARK RESULT 5/10]
I (12130) CLIENT_PROFILER:   -> Current RSSI       : -72 dBm
I (12140) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (12140) CLIENT_PROFILER:   -> Time Elapsed       : 0.268 Seconds
I (12150) CLIENT_PROFILER:   -> Measured Speed     : 1530.20 Kbps
I (12150) CLIENT_PROFILER: =======================================================
I (14160) CLIENT_PROFILER: [ROUND 6/10]: Connecting to 192.168.4.1:8080
I (14500) CLIENT_PROFILER: =======================================================
I (14500) CLIENT_PROFILER:  [BENCHMARK RESULT 6/10]
I (14500) CLIENT_PROFILER:   -> Current RSSI       : -73 dBm
I (14500) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (14510) CLIENT_PROFILER:   -> Time Elapsed       : 0.333 Seconds
I (14510) CLIENT_PROFILER:   -> Measured Speed     : 1230.15 Kbps
I (14520) CLIENT_PROFILER: =======================================================
I (16530) CLIENT_PROFILER: [ROUND 7/10]: Connecting to 192.168.4.1:8080
I (16940) CLIENT_PROFILER: =======================================================
I (16940) CLIENT_PROFILER:  [BENCHMARK RESULT 7/10]
I (16940) CLIENT_PROFILER:   -> Current RSSI       : -79 dBm
I (16950) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (16960) CLIENT_PROFILER:   -> Time Elapsed       : 0.410 Seconds
I (16960) CLIENT_PROFILER:   -> Measured Speed     : 998.03 Kbps
I (16970) CLIENT_PROFILER: =======================================================
I (18980) CLIENT_PROFILER: [ROUND 8/10]: Connecting to 192.168.4.1:8080
I (19200) CLIENT_PROFILER: =======================================================
I (19200) CLIENT_PROFILER:  [BENCHMARK RESULT 8/10]
I (19200) CLIENT_PROFILER:   -> Current RSSI       : -72 dBm
I (19200) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (19210) CLIENT_PROFILER:   -> Time Elapsed       : 0.214 Seconds
I (19220) CLIENT_PROFILER:   -> Measured Speed     : 1916.45 Kbps
I (19220) CLIENT_PROFILER: =======================================================
I (21230) CLIENT_PROFILER: [ROUND 9/10]: Connecting to 192.168.4.1:8080
I (21550) CLIENT_PROFILER: =======================================================
I (21560) CLIENT_PROFILER:  [BENCHMARK RESULT 9/10]
I (21560) CLIENT_PROFILER:   -> Current RSSI       : -72 dBm
I (21560) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (21570) CLIENT_PROFILER:   -> Time Elapsed       : 0.321 Seconds
I (21570) CLIENT_PROFILER:   -> Measured Speed     : 1275.81 Kbps
I (21580) CLIENT_PROFILER: =======================================================
I (23590) CLIENT_PROFILER: [ROUND 10/10]: Connecting to 192.168.4.1:8080
I (23880) CLIENT_PROFILER: =======================================================
I (23880) CLIENT_PROFILER:  [BENCHMARK RESULT 10/10]
I (23880) CLIENT_PROFILER:   -> Current RSSI       : -71 dBm
I (23890) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (23890) CLIENT_PROFILER:   -> Time Elapsed       : 0.286 Seconds
I (23900) CLIENT_PROFILER:   -> Measured Speed     : 1433.41 Kbps
I (23900) CLIENT_PROFILER: =======================================================
I (25910) CLIENT_PROFILER: All benchmark rounds completed
```
## 2
```
I (2580) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (2640) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (3610) esp_netif_handlers: sta ip: 192.168.4.2, mask: 255.255.255.0, gw: 192.168.4.1
I (3610) CLIENT_PROFILER: [FORENSIC EVENT]: Connected; IP=192.168.4.2
I (3610) CLIENT_PROFILER: [ROUND 1/10]: Connecting to 192.168.4.1:8080
I (3630) wifi:<ba-add>idx:0 (ifx:0, 88:57:21:ae:44:85), tid:0, ssn:0, winSize:64
I (3820) CLIENT_PROFILER: =======================================================
I (3820) CLIENT_PROFILER:  [BENCHMARK RESULT 1/10]
I (3820) CLIENT_PROFILER:   -> Current RSSI       : -55 dBm
I (3830) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (3830) CLIENT_PROFILER:   -> Time Elapsed       : 0.179 Seconds
I (3840) CLIENT_PROFILER:   -> Measured Speed     : 2290.97 Kbps
I (3840) CLIENT_PROFILER: =======================================================
I (5850) CLIENT_PROFILER: [ROUND 2/10]: Connecting to 192.168.4.1:8080
I (6010) CLIENT_PROFILER: =======================================================
I (6010) CLIENT_PROFILER:  [BENCHMARK RESULT 2/10]
I (6010) CLIENT_PROFILER:   -> Current RSSI       : -54 dBm
I (6010) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (6020) CLIENT_PROFILER:   -> Time Elapsed       : 0.153 Seconds
I (6020) CLIENT_PROFILER:   -> Measured Speed     : 2684.63 Kbps
I (6030) CLIENT_PROFILER: =======================================================
I (8040) CLIENT_PROFILER: [ROUND 3/10]: Connecting to 192.168.4.1:8080
I (8180) CLIENT_PROFILER: =======================================================
I (8180) CLIENT_PROFILER:  [BENCHMARK RESULT 3/10]
I (8180) CLIENT_PROFILER:   -> Current RSSI       : -55 dBm
I (8190) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (8190) CLIENT_PROFILER:   -> Time Elapsed       : 0.138 Seconds
I (8200) CLIENT_PROFILER:   -> Measured Speed     : 2968.72 Kbps
I (8200) CLIENT_PROFILER: =======================================================
I (10210) CLIENT_PROFILER: [ROUND 4/10]: Connecting to 192.168.4.1:8080
I (10330) CLIENT_PROFILER: =======================================================
I (10330) CLIENT_PROFILER:  [BENCHMARK RESULT 4/10]
I (10330) CLIENT_PROFILER:   -> Current RSSI       : -54 dBm
I (10340) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (10340) CLIENT_PROFILER:   -> Time Elapsed       : 0.110 Seconds
I (10350) CLIENT_PROFILER:   -> Measured Speed     : 3726.79 Kbps
I (10350) CLIENT_PROFILER: =======================================================
I (12360) CLIENT_PROFILER: [ROUND 5/10]: Connecting to 192.168.4.1:8080
I (12490) CLIENT_PROFILER: =======================================================
I (12490) CLIENT_PROFILER:  [BENCHMARK RESULT 5/10]
I (12490) CLIENT_PROFILER:   -> Current RSSI       : -56 dBm
I (12500) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (12500) CLIENT_PROFILER:   -> Time Elapsed       : 0.128 Seconds
I (12510) CLIENT_PROFILER:   -> Measured Speed     : 3202.35 Kbps
I (12520) CLIENT_PROFILER: =======================================================
I (14520) CLIENT_PROFILER: [ROUND 6/10]: Connecting to 192.168.4.1:8080
I (14620) CLIENT_PROFILER: =======================================================
I (14620) CLIENT_PROFILER:  [BENCHMARK RESULT 6/10]
I (14620) CLIENT_PROFILER:   -> Current RSSI       : -55 dBm
I (14630) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (14630) CLIENT_PROFILER:   -> Time Elapsed       : 0.095 Seconds
I (14640) CLIENT_PROFILER:   -> Measured Speed     : 4293.05 Kbps
I (14650) CLIENT_PROFILER: =======================================================
I (16650) CLIENT_PROFILER: [ROUND 7/10]: Connecting to 192.168.4.1:8080
I (16770) CLIENT_PROFILER: =======================================================
I (16770) CLIENT_PROFILER:  [BENCHMARK RESULT 7/10]
I (16780) CLIENT_PROFILER:   -> Current RSSI       : -53 dBm
I (16780) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (16790) CLIENT_PROFILER:   -> Time Elapsed       : 0.119 Seconds
I (16790) CLIENT_PROFILER:   -> Measured Speed     : 3451.41 Kbps
I (16800) CLIENT_PROFILER: =======================================================
I (18810) CLIENT_PROFILER: [ROUND 8/10]: Connecting to 192.168.4.1:8080
I (18980) CLIENT_PROFILER: =======================================================
I (18980) CLIENT_PROFILER:  [BENCHMARK RESULT 8/10]
I (18980) CLIENT_PROFILER:   -> Current RSSI       : -53 dBm
I (18990) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (18990) CLIENT_PROFILER:   -> Time Elapsed       : 0.166 Seconds
I (19000) CLIENT_PROFILER:   -> Measured Speed     : 2464.57 Kbps
I (19010) CLIENT_PROFILER: =======================================================
I (21010) CLIENT_PROFILER: [ROUND 9/10]: Connecting to 192.168.4.1:8080
I (21180) CLIENT_PROFILER: =======================================================
I (21180) CLIENT_PROFILER:  [BENCHMARK RESULT 9/10]
I (21180) CLIENT_PROFILER:   -> Current RSSI       : -54 dBm
I (21190) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (21190) CLIENT_PROFILER:   -> Time Elapsed       : 0.162 Seconds
I (21200) CLIENT_PROFILER:   -> Measured Speed     : 2535.63 Kbps
I (21200) CLIENT_PROFILER: =======================================================
I (23210) CLIENT_PROFILER: [ROUND 10/10]: Connecting to 192.168.4.1:8080
I (23300) CLIENT_PROFILER: =======================================================
I (23300) CLIENT_PROFILER:  [BENCHMARK RESULT 10/10]
I (23300) CLIENT_PROFILER:   -> Current RSSI       : -55 dBm
I (23310) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (23310) CLIENT_PROFILER:   -> Time Elapsed       : 0.088 Seconds
I (23320) CLIENT_PROFILER:   -> Measured Speed     : 4640.52 Kbps
I (23330) CLIENT_PROFILER: =======================================================
I (25330) CLIENT_PROFILER: All benchmark rounds completed

```

## 3
```
I (840) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (840) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (1870) esp_netif_handlers: sta ip: 192.168.4.2, mask: 255.255.255.0, gw: 192.168.4.1
I (1870) CLIENT_PROFILER: [FORENSIC EVENT]: Connected; IP=192.168.4.2
I (1870) CLIENT_PROFILER: [ROUND 1/10]: Connecting to 192.168.4.1:8080
I (1890) wifi:<ba-add>idx:0 (ifx:0, 88:57:21:ae:44:85), tid:0, ssn:0, winSize:64
I (2150) CLIENT_PROFILER: =======================================================
I (2150) CLIENT_PROFILER:  [BENCHMARK RESULT 1/10]
I (2150) CLIENT_PROFILER:   -> Current RSSI       : -68 dBm
I (2150) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (2160) CLIENT_PROFILER:   -> Time Elapsed       : 0.246 Seconds
I (2160) CLIENT_PROFILER:   -> Measured Speed     : 1667.41 Kbps
I (2170) CLIENT_PROFILER: =======================================================
I (4180) CLIENT_PROFILER: [ROUND 2/10]: Connecting to 192.168.4.1:8080
I (4330) CLIENT_PROFILER: =======================================================
I (4330) CLIENT_PROFILER:  [BENCHMARK RESULT 2/10]
I (4330) CLIENT_PROFILER:   -> Current RSSI       : -63 dBm
I (4330) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (4340) CLIENT_PROFILER:   -> Time Elapsed       : 0.143 Seconds
I (4340) CLIENT_PROFILER:   -> Measured Speed     : 2869.91 Kbps
I (4350) CLIENT_PROFILER: =======================================================
I (6360) CLIENT_PROFILER: [ROUND 3/10]: Connecting to 192.168.4.1:8080
I (6480) CLIENT_PROFILER: =======================================================
I (6480) CLIENT_PROFILER:  [BENCHMARK RESULT 3/10]
I (6480) CLIENT_PROFILER:   -> Current RSSI       : -66 dBm
I (6480) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (6490) CLIENT_PROFILER:   -> Time Elapsed       : 0.114 Seconds
I (6490) CLIENT_PROFILER:   -> Measured Speed     : 3594.40 Kbps
I (6500) CLIENT_PROFILER: =======================================================
I (8510) CLIENT_PROFILER: [ROUND 4/10]: Connecting to 192.168.4.1:8080
I (8630) CLIENT_PROFILER: =======================================================
I (8630) CLIENT_PROFILER:  [BENCHMARK RESULT 4/10]
I (8630) CLIENT_PROFILER:   -> Current RSSI       : -65 dBm
I (8640) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (8640) CLIENT_PROFILER:   -> Time Elapsed       : 0.112 Seconds
I (8650) CLIENT_PROFILER:   -> Measured Speed     : 3658.51 Kbps
I (8650) CLIENT_PROFILER: =======================================================
I (10660) CLIENT_PROFILER: [ROUND 5/10]: Connecting to 192.168.4.1:8080
I (10760) CLIENT_PROFILER: =======================================================
I (10760) CLIENT_PROFILER:  [BENCHMARK RESULT 5/10]
I (10760) CLIENT_PROFILER:   -> Current RSSI       : -66 dBm
I (10770) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (10770) CLIENT_PROFILER:   -> Time Elapsed       : 0.096 Seconds
I (10780) CLIENT_PROFILER:   -> Measured Speed     : 4261.56 Kbps
I (10780) CLIENT_PROFILER: =======================================================
I (12790) CLIENT_PROFILER: [ROUND 6/10]: Connecting to 192.168.4.1:8080
I (12930) CLIENT_PROFILER: =======================================================
I (12930) CLIENT_PROFILER:  [BENCHMARK RESULT 6/10]
I (12930) CLIENT_PROFILER:   -> Current RSSI       : -66 dBm
I (12940) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (12940) CLIENT_PROFILER:   -> Time Elapsed       : 0.137 Seconds
I (12950) CLIENT_PROFILER:   -> Measured Speed     : 2998.76 Kbps
I (12960) CLIENT_PROFILER: =======================================================
I (14960) CLIENT_PROFILER: [ROUND 7/10]: Connecting to 192.168.4.1:8080
I (15090) CLIENT_PROFILER: =======================================================
I (15090) CLIENT_PROFILER:  [BENCHMARK RESULT 7/10]
I (15090) CLIENT_PROFILER:   -> Current RSSI       : -68 dBm
I (15090) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (15100) CLIENT_PROFILER:   -> Time Elapsed       : 0.122 Seconds
I (15110) CLIENT_PROFILER:   -> Measured Speed     : 3346.08 Kbps
I (15110) CLIENT_PROFILER: =======================================================
I (17120) CLIENT_PROFILER: [ROUND 8/10]: Connecting to 192.168.4.1:8080
I (17240) CLIENT_PROFILER: =======================================================
I (17240) CLIENT_PROFILER:  [BENCHMARK RESULT 8/10]
I (17240) CLIENT_PROFILER:   -> Current RSSI       : -66 dBm
I (17240) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (17250) CLIENT_PROFILER:   -> Time Elapsed       : 0.108 Seconds
I (17250) CLIENT_PROFILER:   -> Measured Speed     : 3783.41 Kbps
I (17260) CLIENT_PROFILER: =======================================================
I (19270) CLIENT_PROFILER: [ROUND 9/10]: Connecting to 192.168.4.1:8080
I (19360) CLIENT_PROFILER: =======================================================
I (19360) CLIENT_PROFILER:  [BENCHMARK RESULT 9/10]
I (19370) CLIENT_PROFILER:   -> Current RSSI       : -64 dBm
I (19370) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (19380) CLIENT_PROFILER:   -> Time Elapsed       : 0.090 Seconds
I (19380) CLIENT_PROFILER:   -> Measured Speed     : 4570.41 Kbps
I (19390) CLIENT_PROFILER: =======================================================
I (21400) CLIENT_PROFILER: [ROUND 10/10]: Connecting to 192.168.4.1:8080
I (21510) CLIENT_PROFILER: =======================================================
I (21510) CLIENT_PROFILER:  [BENCHMARK RESULT 10/10]
I (21510) CLIENT_PROFILER:   -> Current RSSI       : -64 dBm
I (21510) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (21520) CLIENT_PROFILER:   -> Time Elapsed       : 0.101 Seconds
I (21520) CLIENT_PROFILER:   -> Measured Speed     : 4069.63 Kbps
I (21530) CLIENT_PROFILER: =======================================================
I (23540) CLIENT_PROFILER: All benchmark rounds completed

```
## 4
```
I (840) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (880) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (1860) esp_netif_handlers: sta ip: 192.168.4.2, mask: 255.255.255.0, gw: 192.168.4.1
I (1860) CLIENT_PROFILER: [FORENSIC EVENT]: Connected; IP=192.168.4.2
I (1860) CLIENT_PROFILER: [ROUND 1/10]: Connecting to 192.168.4.1:8080
I (1880) wifi:<ba-add>idx:0 (ifx:0, 88:57:21:ae:44:85), tid:0, ssn:0, winSize:64
I (2170) CLIENT_PROFILER: =======================================================
I (2170) CLIENT_PROFILER:  [BENCHMARK RESULT 1/10]
I (2170) CLIENT_PROFILER:   -> Current RSSI       : -65 dBm
I (2180) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (2180) CLIENT_PROFILER:   -> Time Elapsed       : 0.281 Seconds
I (2190) CLIENT_PROFILER:   -> Measured Speed     : 1458.19 Kbps
I (2190) CLIENT_PROFILER: =======================================================
I (4200) CLIENT_PROFILER: [ROUND 2/10]: Connecting to 192.168.4.1:8080
I (4450) CLIENT_PROFILER: =======================================================
I (4450) CLIENT_PROFILER:  [BENCHMARK RESULT 2/10]
I (4450) CLIENT_PROFILER:   -> Current RSSI       : -68 dBm
I (4450) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (4460) CLIENT_PROFILER:   -> Time Elapsed       : 0.238 Seconds
I (4470) CLIENT_PROFILER:   -> Measured Speed     : 1722.65 Kbps
I (4470) CLIENT_PROFILER: =======================================================
I (6480) CLIENT_PROFILER: [ROUND 3/10]: Connecting to 192.168.4.1:8080
I (6600) CLIENT_PROFILER: =======================================================
I (6600) CLIENT_PROFILER:  [BENCHMARK RESULT 3/10]
I (6600) CLIENT_PROFILER:   -> Current RSSI       : -65 dBm
I (6610) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (6610) CLIENT_PROFILER:   -> Time Elapsed       : 0.117 Seconds
I (6620) CLIENT_PROFILER:   -> Measured Speed     : 3486.76 Kbps
I (6630) CLIENT_PROFILER: =======================================================
I (8630) CLIENT_PROFILER: [ROUND 4/10]: Connecting to 192.168.4.1:8080
I (8770) CLIENT_PROFILER: =======================================================
I (8780) CLIENT_PROFILER:  [BENCHMARK RESULT 4/10]
I (8780) CLIENT_PROFILER:   -> Current RSSI       : -63 dBm
I (8780) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (8790) CLIENT_PROFILER:   -> Time Elapsed       : 0.141 Seconds
I (8790) CLIENT_PROFILER:   -> Measured Speed     : 2909.07 Kbps
I (8800) CLIENT_PROFILER: =======================================================
I (10810) CLIENT_PROFILER: [ROUND 5/10]: Connecting to 192.168.4.1:8080
I (10910) CLIENT_PROFILER: =======================================================
I (10910) CLIENT_PROFILER:  [BENCHMARK RESULT 5/10]
I (10910) CLIENT_PROFILER:   -> Current RSSI       : -63 dBm
I (10920) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (10930) CLIENT_PROFILER:   -> Time Elapsed       : 0.093 Seconds
I (10930) CLIENT_PROFILER:   -> Measured Speed     : 4389.53 Kbps
I (10940) CLIENT_PROFILER: =======================================================
I (12940) CLIENT_PROFILER: [ROUND 6/10]: Connecting to 192.168.4.1:8080
I (13110) CLIENT_PROFILER: =======================================================
I (13110) CLIENT_PROFILER:  [BENCHMARK RESULT 6/10]
I (13110) CLIENT_PROFILER:   -> Current RSSI       : -74 dBm
I (13120) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (13120) CLIENT_PROFILER:   -> Time Elapsed       : 0.165 Seconds
I (13130) CLIENT_PROFILER:   -> Measured Speed     : 2480.82 Kbps
I (13130) CLIENT_PROFILER: =======================================================
I (15140) CLIENT_PROFILER: [ROUND 7/10]: Connecting to 192.168.4.1:8080
I (15250) CLIENT_PROFILER: =======================================================
I (15250) CLIENT_PROFILER:  [BENCHMARK RESULT 7/10]
I (15250) CLIENT_PROFILER:   -> Current RSSI       : -65 dBm
I (15250) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (15260) CLIENT_PROFILER:   -> Time Elapsed       : 0.104 Seconds
I (15270) CLIENT_PROFILER:   -> Measured Speed     : 3947.88 Kbps
I (15270) CLIENT_PROFILER: =======================================================
I (17280) CLIENT_PROFILER: [ROUND 8/10]: Connecting to 192.168.4.1:8080
I (17390) CLIENT_PROFILER: =======================================================
I (17390) CLIENT_PROFILER:  [BENCHMARK RESULT 8/10]
I (17390) CLIENT_PROFILER:   -> Current RSSI       : -66 dBm
I (17390) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (17400) CLIENT_PROFILER:   -> Time Elapsed       : 0.105 Seconds
I (17400) CLIENT_PROFILER:   -> Measured Speed     : 3915.91 Kbps
I (17410) CLIENT_PROFILER: =======================================================
I (19420) CLIENT_PROFILER: [ROUND 9/10]: Connecting to 192.168.4.1:8080
I (19520) CLIENT_PROFILER: =======================================================
I (19520) CLIENT_PROFILER:  [BENCHMARK RESULT 9/10]
I (19520) CLIENT_PROFILER:   -> Current RSSI       : -67 dBm
I (19530) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (19530) CLIENT_PROFILER:   -> Time Elapsed       : 0.095 Seconds
I (19540) CLIENT_PROFILER:   -> Measured Speed     : 4327.93 Kbps
I (19550) CLIENT_PROFILER: =======================================================
I (21550) CLIENT_PROFILER: [ROUND 10/10]: Connecting to 192.168.4.1:8080
I (21690) CLIENT_PROFILER: =======================================================
I (21690) CLIENT_PROFILER:  [BENCHMARK RESULT 10/10]
I (21690) CLIENT_PROFILER:   -> Current RSSI       : -67 dBm
I (21690) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (21700) CLIENT_PROFILER:   -> Time Elapsed       : 0.132 Seconds
I (21700) CLIENT_PROFILER:   -> Measured Speed     : 3111.97 Kbps
I (21710) CLIENT_PROFILER: =======================================================
I (23720) CLIENT_PROFILER: All benchmark rounds completed

```

## 5
```

```
```
I (27) boot: ESP-IDF v6.0.2 2nd stage bootloader
I (27) boot: compile time Aug 10 2026 09:19:08
I (27) boot: Multicore bootloader
I (29) boot: chip revision: v3.1
I (32) boot.esp32: SPI Speed      : 40MHz
I (35) boot.esp32: SPI Mode       : DIO
I (39) boot.esp32: SPI Flash Size : 2MB
I (42) boot: Enabling RNG early entropy source...
I (47) boot: Partition Table:
I (49) boot: ## Label            Usage          Type ST Offset   Length
I (56) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (62) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (69) boot:  2 factory          factory app      00 00 00010000 00100000
I (75) boot: End of partition table
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1a290h (107152) map
I (124) esp_image: segment 1: paddr=0002a2b8 vaddr=3ffb0000 size=04528h ( 17704) load
I (132) esp_image: segment 2: paddr=0002e7e8 vaddr=40080000 size=01830h (  6192) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=87eb4h (556724) map
I (334) esp_image: segment 4: paddr=000b7edc vaddr=40081830 size=13dd8h ( 81368) load
I (368) esp_image: segment 5: paddr=000cbcbc vaddr=50000000 size=00028h (    40) load
I (379) boot: Loaded app from partition at offset 0x10000
I (379) boot: Disabling RNG early entropy source...
I (389) cpu_start: Multicore app
I (398) cpu_start: GPIO 3 and 1 are used as console UART I/O pins
I (398) cpu_start: Pro cpu start user code
I (398) cpu_start: cpu freq: 160000000 Hz
I (400) app_init: Application information:
I (404) app_init: Project name:     wifi_softap_tracking
I (409) app_init: App version:      9d8bbf5-dirty
I (413) app_init: Compile time:     Aug 10 2026 10:08:16
I (418) app_init: ELF file SHA256:  832266500...
I (422) app_init: ESP-IDF:          v6.0.2
I (426) efuse_init: Min chip rev:     v0.0
I (430) efuse_init: Max chip rev:     v3.99 
I (434) efuse_init: Chip rev:         v3.1
I (438) heap_init: Initializing. RAM available for dynamic allocation:
I (444) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (449) heap_init: At 3FFB8A20 len 000275E0 (157 KiB): DRAM
I (454) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (460) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (465) heap_init: At 40095608 len 0000A9F8 (42 KiB): IRAM
W (472) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig
I (484) spi_flash: detected chip: generic
I (487) spi_flash: flash io: dio
W (490) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (504) main_task: Started on CPU0
I (504) main_task: Calling app_main()
I (504) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (554) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (554) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (554) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (564) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbddb8 (Default IP: 192.168.4.1)
I (574) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (584) wifi:wifi driver task: 3ffc053c, prio:23, stack:6656, core=0
I (604) wifi:wifi firmware version: 00ad238
I (604) wifi:wifi certification version: v7.0
I (604) wifi:config NVS flash: enabled
I (604) wifi:config nano formatting: disabled
I (604) wifi:Init data frame dynamic rx buffer num: 32
I (614) wifi:Init static rx mgmt buffer num: 5
I (614) wifi:Init management short buffer num: 32
I (624) wifi:Init dynamic tx buffer num: 32
I (624) wifi:Init static rx buffer size: 1600
I (624) wifi:Init static rx buffer num: 10
I (634) wifi:Init dynamic rx buffer num: 32
I (634) wifi_init: rx ba win: 6
I (634) wifi_init: accept mbox: 6
I (644) wifi_init: tcpip mbox: 32
I (644) wifi_init: udp mbox: 6
I (644) wifi_init: tcp mbox: 6
I (654) wifi_init: tcp tx win: 5760
I (654) wifi_init: tcp rx win: 5760
I (654) wifi_init: tcp mss: 1440
I (664) wifi_init: WiFi IRAM OP enabled
I (664) wifi_init: WiFi RX IRAM OP enabled
I (664) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (674) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (684) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (694) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (694) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06
I (774) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (854) wifi:mode : softAP (88:57:21:ae:44:85)
I (864) wifi:Total power save buffer number: 16
I (864) wifi:Init max length of beacon: 752/752
I (864) wifi:Init max length of beacon: 752/752
I (864) LAB_SOFTAP: [LAB 6.2]: Set Max Tx Power to 80 (20 dBm)
I (864) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (884) LAB_SOFTAP: ==================================================================
I (884) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "ESP32_AP_0351", Channel: 1
I (894) LAB_SOFTAP: ==================================================================
I (904) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (904) main_task: Returned from app_main()
I (209764) wifi:station: 88:57:21:ad:64:98 join, AID=1, bgn, 40U
I (209794) LAB_SOFTAP: =======================================================
I (209794) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (209804) LAB_SOFTAP:   -> Client MAC Address : 88:57:21:AD:64:98
I (209804) LAB_SOFTAP:   -> Assigned AID       : 1
I (209814) LAB_SOFTAP: =======================================================
I (209884) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (210924) wifi:<ba-add>idx:2 (ifx:1, 88:57:21:ad:64:98), tid:0, ssn:0, winSize:64
I (211334) LAB_SOFTAP: =======================================================
I (211344) LAB_SOFTAP: [TCP SERVER SESSION 1]: Client connected from 192.168.4.2:52959
I (211574) LAB_SOFTAP: [TCP SERVER SESSION 1]: Transfer complete
I (211574) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (211574) LAB_SOFTAP: =======================================================
I (213564) LAB_SOFTAP: =======================================================
I (213574) LAB_SOFTAP: [TCP SERVER SESSION 2]: Client connected from 192.168.4.2:52960
I (213834) LAB_SOFTAP: [TCP SERVER SESSION 2]: Transfer complete
I (213834) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (213834) LAB_SOFTAP: =======================================================
I (215864) LAB_SOFTAP: =======================================================
I (215864) LAB_SOFTAP: [TCP SERVER SESSION 3]: Client connected from 192.168.4.2:52961
I (216204) LAB_SOFTAP: [TCP SERVER SESSION 3]: Transfer complete
I (216204) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (216204) LAB_SOFTAP: =======================================================
I (218214) LAB_SOFTAP: =======================================================
I (218214) LAB_SOFTAP: [TCP SERVER SESSION 4]: Client connected from 192.168.4.2:52962
I (218454) LAB_SOFTAP: [TCP SERVER SESSION 4]: Transfer complete
I (218454) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (218454) LAB_SOFTAP: =======================================================
I (220484) LAB_SOFTAP: =======================================================
I (220484) LAB_SOFTAP: [TCP SERVER SESSION 5]: Client connected from 192.168.4.2:52963
I (220774) LAB_SOFTAP: [TCP SERVER SESSION 5]: Transfer complete
I (220774) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (220774) LAB_SOFTAP: =======================================================
I (222784) LAB_SOFTAP: =======================================================
I (222784) LAB_SOFTAP: [TCP SERVER SESSION 6]: Client connected from 192.168.4.2:52964
I (223174) LAB_SOFTAP: [TCP SERVER SESSION 6]: Transfer complete
I (223184) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (223184) LAB_SOFTAP: =======================================================
I (225154) LAB_SOFTAP: =======================================================
I (225154) LAB_SOFTAP: [TCP SERVER SESSION 7]: Client connected from 192.168.4.2:52965
I (225594) LAB_SOFTAP: [TCP SERVER SESSION 7]: Transfer complete
I (225594) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (225594) LAB_SOFTAP: =======================================================
I (227604) LAB_SOFTAP: =======================================================
I (227604) LAB_SOFTAP: [TCP SERVER SESSION 8]: Client connected from 192.168.4.2:52966
I (227834) LAB_SOFTAP: [TCP SERVER SESSION 8]: Transfer complete
I (227834) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (227834) LAB_SOFTAP: =======================================================
I (229854) LAB_SOFTAP: =======================================================
I (229854) LAB_SOFTAP: [TCP SERVER SESSION 9]: Client connected from 192.168.4.2:52967
I (230184) LAB_SOFTAP: [TCP SERVER SESSION 9]: Transfer complete
I (230184) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (230184) LAB_SOFTAP: =======================================================
I (232204) LAB_SOFTAP: =======================================================
I (232204) LAB_SOFTAP: [TCP SERVER SESSION 10]: Client connected from 192.168.4.2:52968
I (232514) LAB_SOFTAP: [TCP SERVER SESSION 10]: Transfer complete
I (232514) LAB_SOFTAP:   -> Total Received : 51200 Bytes
I (232514) LAB_SOFTAP: =======================================================

```
## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกค่าที่ได้จากการทดสอบในระดับ Tx Power ต่างๆ:

| การทดลองที่ | ค่า Tx Power ที่ตั้ง (dBm) | ค่า RSSI ที่อ่านได้จริง (dBm) | เวลาที่ใช้ (Seconds) | ความเร็วที่วัดได้ Throughput (Kbps) |
| :---------: | :------------------------: | :---------------------------: | :------------------: | :---------------------------------: |
|    **1**    |        20 dBm (Max)        |             -72.5             |        0.283         |               1515.91               |
|    **2**    |         15 dBm             |             -54.6             |        0.134         |               3225.86               |
|    **3**    |           10 dBm           |             -65.6             |        0.127         |               3482.00               |
|    **4**    |           5 dBm            |             -66.3             |        0.147         |               3175.07               |
|    **5**    |        2 dBm (Min)         |             -61.3             |        0.149         |               3100.10               |

---

## 6. งานวิเคราะห์ข้อมูลเชิงสถิติ (Data Science & Regression Task)

ให้นักศึกษานำค่า **RSSI (x-axis)** และ **Throughput (y-axis)** จากตารางทดลองไปสร้างแผนภาพใน Excel หรือ Python (Jupyter Notebook):

1. สร้างแผนภาพ **Scatter Plot** แสดงจุดข้อมูลระหว่าง RSSI กับ Speed
2. สร้างเส้นแนวโน้ม **Trendline / Regression Curve** (เช่น Logarithmic Regression: $y = a \cdot \ln(x) + b$)
3. คำนวณค่า **$R^2$ (Coefficient of Determination)** เพื่อประเมินความแม่นยำของสมการ
4. ระบุจุด **Threshold RSSI (dBm)** ที่ความเร็วเริ่มลดลงมากกว่า 50% จากระดับสูงสุด


---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?
		**ตอบ:** การลด Tx Power ลงจะทำให้ความแรงสัญญาณไร้สายลดลง สัญญาณครอบคลุมได้สั้นลง หากระยะห่างเท่าเดิม สัญญาณที่อ่อนลงจะทำให้อัตราการสูญเสียแพ็กเกจ (Packet Loss) และสัญญาณรบกวนสูงขึ้น ส่งผลให้ความเร็ว Throughput เฉลี่ยลดลงเนื่องจากโปรโตคอลต้องใช้เวลาในการส่งข้อมูลซ้ำ

2. เหตุใดในระดับ RSSI ที่อ่อนกว่า `-80 dBm` ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?
		**ตอบ:** เนื่องจาก RSSI ที่อ่อนกว่า -80 dBm มีความแรงใกล้เคียงกับ Noise Floor ทำให้เกิด Packet Loss สูงมาก โปรโตคอล TCP มีกลไก Congestion Control ที่เมื่อพบว่าแพ็กเกจสูญหาย จะเข้าใจว่าเครือข่ายหนาแน่น จึงทำการปรับลดขนาด Congestion Window (cwnd) ลงแบบ Exponential และต้องทำการ Retransmission แพ็กเกจซ้ำหลายครั้ง ส่งผลให้ Throughput ลดลงอย่างกะทันหัน

3. สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?
		**ตอบ:** สามารถนำสมการ Regression (ความสัมพันธ์ระหว่าง RSSI และ Speed) ไปเขียนไว้ในระบบวัดผลของโหนด IoT เพื่อทำนายความเร็วเน็ตล่วงหน้าจากค่า RSSI ที่อ่านได้ หากพบว่า RSSI ต่ำจนอยู่ในช่วงที่ความเร็วตก โหนด IoT สามารถปรับโหมดทำงานเพื่อประหยัดพลังงาน เช่น บีบอัดไฟล์ก่อนส่ง ลดความถี่ในการส่งข้อมูล (Telemetry Rate) หรือชะลอการส่งจนกว่าสัญญาณจะดีขึ้นได้

