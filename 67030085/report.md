## 05-Labsheet-06-1-ESP32-SoftAP-Tracking
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

| อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android) | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ (ถ้าทราบ) |
| :--------------------------------------- | :----------------------- | :------------------: | :---------------------------------: |
| **อุปกรณ์ที่ 1**                         | A2:09:09:4E:95:8B        |          1           |             192.168.4.2             |
| **อุปกรณ์ที่ 2**                         | BC:09:1B:AB:EA:37        |          2           |             192.168.4.3             |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?
	* **ตอบ:** ค่า `192.168.4.1` เป็นค่า Default ที่ทางผู้พัฒนา (Espressif) กำหนดไว้ล่วงหน้าในระบบ (Hardcoded) สำหรับโหมด SoftAP เพื่อป้องกันปัญหาหมายเลข IP ชน (IP Conflict) กับเร้าเตอร์ตามบ้านเรือนทั่วไปที่มักใช้วง `192.168.1.1` หรือ `192.168.0.1` โดย DHCP Server ที่ฝังอยู่ใน ESP32 จะเริ่มต้นแจกหมายเลข IP ให้กับอุปกรณ์ (Client) เครื่องแรกที่เชื่อมต่อสำเร็จที่หมายเลข **`192.168.4.2`** และนับเรียงต่อกันไปเรื่อยๆ ตามลำดับ
2. สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?
	* **ตอบ:** ตัวแปร `mac` จะดึงค่าที่อยู่ทางกายภาพ (MAC Address) ขนาด 6 ไบต์ ของอุปกรณ์ที่เชื่อมต่อเข้ามาได้โดยตรง โปรแกรมเมอร์สามารถนำค่านี้ไปประยุกต์ใช้ทำ MAC Filtering ได้โดยการนำค่า `mac` ไปตรวจสอบเปรียบเทียบกับรายการที่อนุญาต (Whitelist) ที่บันทึกไว้ในฐานข้อมูลหรือโค้ด หากอุปกรณ์นั้นไม่มีรายชื่ออยู่ในระบบ สามารถสั่งตัดการเชื่อมต่อได้ทันทีโดยเรียกใช้คำสั่ง `esp_wifi_deauth_sta(mac)` เพื่อบังคับเตะอุปกรณ์แปลกปลอมออก
3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?
	* **ตอบ:** ไดรเวอร์ Wi-Fi ของ ESP32 จะตัดสิทธิ์การเข้าถึงตั้งแต่ระดับการเชื่อมโยงข้อมูล (Data Link Layer) โดยเมื่อเครื่องที่ 5 ส่งคำร้องขอเข้าสู่เครือข่าย (Association Request) บอร์ดจะไม่อนุมัติและตอบกลับด้วยเฟรมปฏิเสธ (Deauthentication หรือ Disassociation Frame) พร้อมแจ้งรหัสความผิดพลาด เช่น `WIFI_REASON_ASSOC_TOOMANY` กลับไป ทำให้อุปกรณ์เครื่องที่ 5 เชื่อมต่อ Wi-Fi ไม่สำเร็จตั้งแต่แรก และไม่สามารถเข้าสู่เฟสการขอ IP Address ได้


Log
```text
entry 0x40080638
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug 11 2026 09:16:45
I (29) boot: Multicore bootloader
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19a78h (105080) map
I (124) esp_image: segment 1: paddr=00029aa0 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002d994 vaddr=40080000 size=02684h (  9860) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=87d78h (556408) map
I (325) esp_image: segment 4: paddr=000b7da0 vaddr=40082684 size=15788h ( 87944) load
I (360) esp_image: segment 5: paddr=000cd530 vaddr=50000000 size=00020h (    32) load
--- 0x40080400: _invalid_pc_placeholder at C:/Users/Thanu/esp/v5.5.1/esp-idf/components/xtensa/xtensa_vectors.S:2235
--- 0x40080638: call_start_cpu0 at C:/Users/Thanu/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (372) boot: Loaded app from partition at offset 0x10000
I (372) boot: Disabling RNG early entropy source...
I (382) cpu_start: Multicore app
I (391) cpu_start: Pro cpu start user code
I (391) cpu_start: cpu freq: 160000000 Hz
I (391) app_init: Application information:
I (391) app_init: Project name:     wifi_softap_tracking
I (396) app_init: App version:      029da6d-dirty
I (400) app_init: Compile time:     Aug 11 2026 09:15:55
I (405) app_init: ELF file SHA256:  b3b333917...
I (410) app_init: ESP-IDF:          v5.5.1
I (413) efuse_init: Min chip rev:     v0.0
I (417) efuse_init: Max chip rev:     v3.99 
I (421) efuse_init: Chip rev:         v3.1
I (425) heap_init: Initializing. RAM available for dynamic allocation:
I (432) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (436) heap_init: At 3FFB7FC8 len 00028038 (160 KiB): DRAM
I (442) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (447) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (453) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
I (459) spi_flash: detected chip: generic
I (462) spi_flash: flash io: dio
W (465) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (478) main_task: Started on CPU0
I (488) main_task: Calling app_main()
I (488) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (518) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (518) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (518) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (528) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbd808 (Default IP: 192.168.4.1)
I (538) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (548) wifi:wifi driver task: 3ffbff48, prio:23, stack:6656, core=0
I (568) wifi:wifi firmware version: 14da9b7
I (568) wifi:wifi certification version: v7.0
I (568) wifi:config NVS flash: enabled
I (568) wifi:config nano formatting: disabled
I (568) wifi:Init data frame dynamic rx buffer num: 32
I (578) wifi:Init static rx mgmt buffer num: 5
I (578) wifi:Init management short buffer num: 32
I (588) wifi:Init dynamic tx buffer num: 32
I (588) wifi:Init static rx buffer size: 1600
I (588) wifi:Init static rx buffer num: 10
I (598) wifi:Init dynamic rx buffer num: 32
I (598) wifi_init: rx ba win: 6
I (598) wifi_init: accept mbox: 6
I (608) wifi_init: tcpip mbox: 32
I (608) wifi_init: udp mbox: 6
I (608) wifi_init: tcp mbox: 6
I (618) wifi_init: tcp tx win: 5760
I (618) wifi_init: tcp rx win: 5760
I (618) wifi_init: tcp mss: 1440
I (628) wifi_init: WiFi IRAM OP enabled
I (628) wifi_init: WiFi RX IRAM OP enabled
I (628) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (638) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (648) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (658) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (658) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (738) wifi:mode : softAP (14:33:5c:0e:94:45)
I (748) wifi:Total power save buffer number: 16
I (748) wifi:Init max length of beacon: 752/752
I (748) wifi:Init max length of beacon: 752/752
I (748) LAB_SOFTAP: ==================================================================
I (748) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (768) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "MY_ESP32_AP_0085", Channel: 1
I (768) LAB_SOFTAP: ==================================================================
I (778) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (788) main_task: Returned from app_main()
I (78098) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (78098) wifi:station: a2:09:09:4e:95:8b join, AID=1, bgn, 20
I (78158) LAB_SOFTAP: =======================================================
I (78158) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (78158) LAB_SOFTAP:   -> Client MAC Address : A2:09:09:4E:95:8B
I (78168) LAB_SOFTAP:   -> Assigned AID       : 1
I (78168) LAB_SOFTAP: =======================================================
I (78168) wifi:<ba-add>idx:2 (ifx:1, a2:09:09:4e:95:8b), tid:0, ssn:0, winSize:64
I (78598) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (665708) wifi:new:<1,1>, old:<1,0>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (665708) wifi:station: bc:09:1b:ab:ea:37 join, AID=2, bgn, 40U
I (665748) LAB_SOFTAP: =======================================================
I (665748) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (665748) LAB_SOFTAP:   -> Client MAC Address : BC:09:1B:AB:EA:37
I (665758) LAB_SOFTAP:   -> Assigned AID       : 2
I (665758) LAB_SOFTAP: =======================================================
I (665878) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3
I (666578) wifi:<ba-add>idx:3 (ifx:1, bc:09:1b:ab:ea:37), tid:0, ssn:19, winSize:64
I (919258) wifi:station: bc:09:1b:ab:ea:37 leave, AID = 2, reason = 1, bss_flags is 756835, bss:0x3ffb9b68
I (919258) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (919268) wifi:<ba-del>idx:3, tid:0
I (919268) wifi:new:<1,1>, old:<1,0>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
```

---

## 06-Labsheet-06-2-RSSI-Speed-Profiling
## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกค่าที่ได้จากการทดสอบในระดับ Tx Power ต่างๆ:

| การทดลองที่ | ค่า Tx Power ที่ตั้ง (dBm) | ค่า RSSI ที่อ่านได้จริง (dBm) | เวลาที่ใช้ (Seconds) | ความเร็วที่วัดได้ Throughput (Kbps) |
| :---------: | :------------------------: | :---------------------------: | :------------------: | :---------------------------------: |
|    **1**    |        20 dBm (Max)        |             -55.6             |        0.124         |               3453.20               |
|    **2**    |           15 dBm           |             -46.7             |        0.117         |               3630.46               |
|    **3**    |           10 dBm           |             -62.2             |        0.129         |               3322.71               |
|    **4**    |           5 dBm            |             -62.6             |        0.113         |               3687.95               |
|    **5**    |        2 dBm (Min)         |             -57.4             |        0.126         |               3363.37               |

---

## 6. งานวิเคราะห์ข้อมูลเชิงสถิติ (Data Science & Regression Task)

ให้นักศึกษานำค่า **RSSI (x-axis)** และ **Throughput (y-axis)** จากตารางทดลองไปสร้างแผนภาพใน Excel หรือ Python (Jupyter Notebook):

#### 6.1 แผนภาพ Scatter Plot และ Regression Line

<img width="1222" height="712" alt="Screenshot 2026-08-12 230201" src="https://github.com/user-attachments/assets/bc9c29f0-3c67-4c1f-8fe4-721b7d26af57" />


#### 6.2 สรุปผลการวิเคราะห์ทางสถิติ

1. **สมการ Regression (Linear Regression Model):** $y = 7.2436 \cdot x + 3903.6970$ _(เมื่อ $y$ คือ ความเร็ว Throughput (Kbps) และ $x$ คือ สัญญาณ RSSI (dBm))_
    - **Logarithmic Model: **$y = -423.89 \cdot \ln(-x) + 5202.27$ ($R^2 = 0.0974$)

2. **ค่า R2 (Coefficient of Determination):** $R^2 = 0.0974$ (อ้างอิงจากสมการ Logarithmic ที่มีความแม่นยำสูงกว่าเล็กน้อย แสดงให้เห็นว่าระดับความแรงสัญญาณ RSSI ในการทดสอบรอบนี้มีอิทธิพลต่อความเร็วค่อนข้างน้อย เนื่องจากความเร็วยังคงรักษาระดับได้ดีแม้สัญญาณจะอ่อนลง)
    
3. **ระดับความเร็วสูงสุด (Max Speed):** 3687.95 Kbps
    
4. **จุด Threshold RSSI (dBm) ที่ความเร็วลดลงมากกว่า 50%:**
    - ความเร็วเป้าหมาย 50% จากระดับสูงสุด = 3687.95 × 0.5 = 1843.98 Kbps
    - จากผลการทดลองและการประเมินจากสมการ Logarithmic พบว่าจุด Threshold RSSI ในทางทฤษฎีอยู่ที่ประมาณ -2758.60 dBm (โดยที่ระดับสัญญาณ -2758.60 dBm ความเร็วจะตกลงเหลือ 1843.98 Kbps ซึ่งลดลง 50% จากระดับสูงสุด 3687.95 Kbps)*

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?
	**ตอบ:**  จากผลการทดลองจริงที่เก็บบันทึกได้ เมื่อลดกำลังส่ง (Tx Power) จาก 20 dBm (การทดลองที่ 1) ลงเหลือ 2 dBm (การทดลองที่ 5) พบว่า: 
	* **ค่า RSSI:** ลดลงเพียงเล็กน้อย จาก **-55.6 dBm** เป็น **-57.4 dBm** (ลดลง 1.8 dBm) 
	* **ความเร็ว Throughput:** ลดลงจาก **3453.20 Kbps** เป็น **3363.37 Kbps** (ลดลง 89.83 Kbps) 
	* **สรุปผล:** การลดกำลังส่งลงถึงระดับต่ำสุดไม่ได้ทำให้สัญญาณอ่อนลงหรือความเร็วตกลงอย่างมีนัยสำคัญในการทดสอบนี้ ซึ่งอาจเป็นผลมาจากระยะห่างระหว่าง Node A และ Node B ที่อยู่ใกล้กันมาก หรือไม่มีสิ่งกีดขวาง ทำให้ชิปรับส่งสัญญาณยังคงรักษาระดับคุณภาพการเชื่อมต่อ (Modulation) ไว้ได้ดีเยี่ยมแม้กำลังส่งจะต่ำลง

2. เหตุใดในระดับ RSSI ที่อ่อนกว่า `-80 dBm` ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?
	**ตอบ:**  สาเหตุหลักมาจากกลไกการทำงานของโปรโตคอล TCP ที่เน้นความน่าเชื่อถือของข้อมูล (Reliability): 
	* เมื่อสัญญาณอ่อนกว่า -80 dBm อัตราส่วนสัญญาณต่อสัญญาณรบกวน (SNR) จะต่ำมาก ทำให้เกิดข้อมูลสูญหาย (Packet Loss) และ Error ในระดับ Physical Layer ได้ง่าย 
	* เมื่อ TCP ฝั่งรับไม่ได้รับข้อมูลที่สมบูรณ์ ก็จะไม่ส่ง Acknowledgment (ACK) กลับไป 
	* TCP ฝั่งส่งเมื่อไม่ได้รับ ACK จะมองว่าเกิดปัญหาความคับคั่งในเครือข่าย (Congestion) จึงกระตุ้นกลไก **Congestion Control** โดยลดขนาดหน้าต่างการส่ง (Window Size) ลงอย่างฮวบฮาบ และทำการส่งข้อมูลซ้ำ (Retransmission) 
	* กระบวนการรอและส่งซ้ำนี้ทำให้เกิดความหน่วง (Latency) มหาศาล ส่งผลให้ความเร็ว Throughput สุทธิร่วงหล่นอย่างกะทันหัน

3. สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?
	**ตอบ:**  สมการ Regression สามารถนำมาเป็นเครื่องมือช่วยตัดสินใจในการออกแบบและประเมินประสิทธิภาพของสถาปัตยกรรมเครือข่ายก่อนการติดตั้งจริงได้: 
	* **การประเมินแบนด์วิดท์ล่วงหน้า:** ตัวอย่างเช่น ในการพัฒนาระบบปลูกพืชไร้ดินแบบแอโรโปนิกส์อัตโนมัติที่มีการมอนิเตอร์ระยะไกล เราสามารถใช้สมการนี้คำนวณได้ว่า หากนำไมโครคอนโทรลเลอร์ไปติดตั้งในโรงเรือนจุดที่สัญญาณ Wi-Fi ไปถึงที่ระดับ -75 dBm ระบบจะยังมีแบนด์วิดท์เพียงพอสำหรับส่งข้อมูล Log เซนเซอร์ หรือภาพถ่ายกลับมาที่เซิร์ฟเวอร์แบบเรียลไทม์หรือไม่ 
	* **การวางแผนสถาปัตยกรรมเครือข่าย:** หากสมการทำนายว่า Throughput จะต่ำเกินไป เราสามารถวางแผนเพิ่มจุดกระจายสัญญาณ (Repeater) หรือปรับเปลี่ยนตำแหน่งของโหนดได้ล่วงหน้า ช่วยลดปัญหาคอขวดของข้อมูลในระบบ IoT ได้อย่างมีประสิทธิภาพ


Log 
* Node A
```text
I (27) boot: ESP-IDF v6.0.2 2nd stage bootloader 
I (27) boot: compile time Aug 11 2026 11:14:17 
I (27) boot: Multicore bootloader 
I (29) boot: chip revision: v3.1 
I (32) boot.esp32: SPI Speed : 40MHz 
I (35) boot.esp32: SPI Mode : DIO 
I (39) boot.esp32: SPI Flash Size : 2MB 
I (42) boot: Enabling RNG early entropy source... 
I (47) boot: Partition Table: 
I (49) boot: ## Label Usage Type ST Offset Length 
I (56) boot: 0 nvs WiFi data 01 02 00009000 00006000 
I (62) boot: 1 phy_init RF data 01 01 0000f000 00001000 
I (69) boot: 2 factory factory app 00 00 00010000 00100000 
I (75) boot: End of partition table 
I (79) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19e00h (105984) map 
I (124) esp_image: segment 1: paddr=00029e28 vaddr=3ffb0000 size=04528h ( 17704) load 
I (131) esp_image: segment 2: paddr=0002e358 vaddr=40080000 size=01cc0h ( 7360) load 
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=8794ch (555340) map 
I (333) esp_image: segment 4: paddr=000b7974 vaddr=40081cc0 size=13948h ( 80200) load 
I (366) esp_image: segment 5: paddr=000cb2c4 vaddr=50000000 size=00028h ( 40) load I (377) boot: Loaded app from partition at offset 0x10000 
I (377) boot: Disabling RNG early entropy source... 
I (388) cpu_start: Multicore app 
I (396) cpu_start: GPIO 3 and 1 are used as console UART I/O pins 
I (396) cpu_start: Pro cpu start user code 
I (396) cpu_start: cpu freq: 160000000 Hz 
I (398) app_init: Application information: 
I (402) app_init: Project name: rssi_speed_profiler 
I (407) app_init: App version: 029da6d-dirty 
I (412) app_init: Compile time: Aug 11 2026 11:13:09 
I (417) app_init: ELF file SHA256: d7bd9fdf9... 
I (421) app_init: ESP-IDF: v6.0.2 
I (425) efuse_init: Min chip rev: v0.0 
I (429) efuse_init: Max chip rev: v3.99 
I (433) efuse_init: Chip rev: v3.1 
I (437) heap_init: Initializing. RAM available for dynamic allocation: 
I (443) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM 
I (448) heap_init: At 3FFB8A20 len 000275E0 (157 KiB): DRAM 
I (453) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM 
I (458) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM 
I (464) heap_init: At 40095608 len 0000A9F8 (42 KiB): IRAM 
W (470) spi_flash: Detected boya flash chip but using generic driver. For optimal functionality, enable `SPI_FLASH_SUPPORT_BOYA_CHIP` in menuconfig 
I (482) spi_flash: detected chip: generic 
I (486) spi_flash: flash io: dio 
W (489) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header. 
I (503) main_task: Started on CPU0 
I (503) main_task: Calling app_main() 
I (563) wifi:wifi driver task: 3ffc04fc, prio:23, stack:6656, core=0 
I (583) wifi:wifi firmware version: 00ad238 
I (583) wifi:wifi certification version: v7.0 
I (583) wifi:config NVS flash: enabled 
I (583) wifi:config nano formatting: disabled 
I (583) wifi:Init data frame dynamic rx buffer num: 32 
I (593) wifi:Init static rx mgmt buffer num: 5 
I (593) wifi:Init management short buffer num: 32 
I (603) wifi:Init dynamic tx buffer num: 32 
I (603) wifi:Init static rx buffer size: 1600 
I (603) wifi:Init static rx buffer num: 10 
I (613) wifi:Init dynamic rx buffer num: 32 
I (613) wifi_init: rx ba win: 6 
I (623) wifi_init: accept mbox: 6 
I (623) wifi_init: tcpip mbox: 32 
I (623) wifi_init: udp mbox: 6 
I (623) wifi_init: tcp mbox: 6 
I (633) wifi_init: tcp tx win: 5760 
I (633) wifi_init: tcp rx win: 5760 
I (633) wifi_init: tcp mss: 1440 
I (643) wifi_init: WiFi IRAM OP enabled 
I (643) wifi_init: WiFi RX IRAM OP enabled 
I (653) phy_init: phy_version 4863,a3a4459,Oct 28 2025,14:30:06 
I (743) wifi:mode : softAP (14:08:08:a4:b6:61) 
I (753) wifi:Total power save buffer number: 16 
I (753) wifi:Init max length of beacon: 752/752 
I (753) wifi:Init max length of beacon: 752/752 
I (753) AP_SERVER: ESP32 SoftAP Running! SSID: "ESP32_AP_134", Channel: 1 
I (753) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1 
I (763) AP_SERVER: [TCP SERVER]: Listening on port 8080 
I (773) main_task: Returned from app_main() 
I (39723) wifi:station: 14:33:5c:0e:94:44 join, AID=1, bgn, 40U 
I (39753) AP_SERVER: ======================================================= 
I (39753) AP_SERVER: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP! 
I (39763) AP_SERVER: -> Client MAC Address : 14:33:5c:0e:94:44 
I (39763) AP_SERVER: -> Assigned AID : 1 
I (39773) AP_SERVER: ======================================================= 
I (39793) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2 
I (40823) wifi:<ba-add>idx:2 (ifx:1, 14:33:5c:0e:94:44), tid:0, ssn:0, winSize:64 
I (41013) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (43203) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (45393) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (47543) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (49753) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (51893) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (54063) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (56213) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (58343) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client 
I (60483) AP_SERVER: [TCP SERVER]: Received total 51200 bytes from client
```

* Node B
```text
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug 11 2026 10:36:15
I (29) boot: Multicore bootloader
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=19a00h (104960) map
I (124) esp_image: segment 1: paddr=00029a28 vaddr=3ffb0000 size=03eech ( 16108) load
I (130) esp_image: segment 2: paddr=0002d91c vaddr=40080000 size=026fch (  9980) load
I (134) esp_image: segment 3: paddr=00030020 vaddr=400d0020 size=870e8h (553192) map
I (324) esp_image: segment 4: paddr=000b7110 vaddr=400826fc size=15710h ( 87824) load
I (359) esp_image: segment 5: paddr=000cc828 vaddr=50000000 size=00020h (    32) load
I (371) boot: Loaded app from partition at offset 0x10000
I (371) boot: Disabling RNG early entropy source...
I (381) cpu_start: Multicore app
I (389) cpu_start: Pro cpu start user code
I (390) cpu_start: cpu freq: 160000000 Hz
I (390) app_init: Application information:
I (390) app_init: Project name:     rssi_speed_profiler
I (395) app_init: App version:      029da6d-dirty
I (399) app_init: Compile time:     Aug 11 2026 10:35:01
I (404) app_init: ELF file SHA256:  ca6a37d40...
I (408) app_init: ESP-IDF:          v5.5.1
I (412) efuse_init: Min chip rev:     v0.0
I (416) efuse_init: Max chip rev:     v3.99 
I (420) efuse_init: Chip rev:         v3.1
I (424) heap_init: Initializing. RAM available for dynamic allocation:
I (430) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (435) heap_init: At 3FFB7FD0 len 00028030 (160 KiB): DRAM
I (440) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (446) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (451) heap_init: At 40097E0C len 000081F4 (32 KiB): IRAM
I (458) spi_flash: detected chip: generic
I (460) spi_flash: flash io: dio
W (463) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (476) main_task: Started on CPU0
I (486) main_task: Calling app_main()
I (486) CLIENT_PROFILER: [FORENSIC]: Call nvs_flash_init()
I (516) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_init()
I (516) CLIENT_PROFILER: [FORENSIC]: Call esp_event_loop_create_default()
I (516) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (526) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_init(&config)
I (536) wifi:wifi driver task: 3ffbffa8, prio:23, stack:6656, core=0
I (556) wifi:wifi firmware version: 14da9b7
I (556) wifi:wifi certification version: v7.0
I (556) wifi:config NVS flash: enabled
I (556) wifi:config nano formatting: disabled
I (566) wifi:Init data frame dynamic rx buffer num: 32
I (566) wifi:Init static rx mgmt buffer num: 5
I (566) wifi:Init management short buffer num: 32
I (576) wifi:Init dynamic tx buffer num: 32
I (576) wifi:Init static rx buffer size: 1600
I (586) wifi:Init static rx buffer num: 10
I (586) wifi:Init dynamic rx buffer num: 32
I (596) wifi_init: rx ba win: 6
I (596) wifi_init: accept mbox: 6
I (596) wifi_init: tcpip mbox: 32
I (596) wifi_init: udp mbox: 6
I (606) wifi_init: tcp mbox: 6
I (606) wifi_init: tcp tx win: 5760
I (606) wifi_init: tcp rx win: 5760
I (606) wifi_init: tcp mss: 1440
I (616) wifi_init: WiFi IRAM OP enabled
I (616) wifi_init: WiFi RX IRAM OP enabled
I (626) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (636) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (696) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_start()
I (696) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (776) wifi:mode : sta (14:33:5c:0e:94:44)
I (776) wifi:enable tsf
I (776) CLIENT_PROFILER: Client profiler ready: 50 KB x 10 rounds
I (776) main_task: Returned from app_main()
I (776) CLIENT_PROFILER: [FORENSIC EVENT]: Station started; connecting to ESP32_AP_134
I (1056) wifi:new:<1,1>, old:<1,0>, ap:<255,255>, sta:<1,1>, prof:1, snd_ch_cfg:0x0
I (1066) wifi:state: init -> auth (0xb0)
I (1066) wifi:state: auth -> assoc (0x0)
I (1086) wifi:state: assoc -> run (0x10)
I (1106) wifi:connected with ESP32_AP_134, aid = 1, channel 1, 40U, bssid = 14:08:08:a4:b6:61
I (1106) wifi:security: WPA2-PSK, phy: bgn, rssi: -57
I (1126) wifi:pm start, type: 1

I (1126) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (1126) wifi:AP's beacon interval = 102400 us, DTIM period = 1
I (2146) esp_netif_handlers: sta ip: 192.168.4.2, mask: 255.255.255.0, gw: 192.168.4.1
I (2146) CLIENT_PROFILER: [FORENSIC EVENT]: Connected; IP=192.168.4.2
I (2146) CLIENT_PROFILER: [ROUND 1/10]: Connecting to 192.168.4.1:8080
I (2156) wifi:<ba-add>idx:0 (ifx:0, 14:08:08:a4:b6:61), tid:0, ssn:0, winSize:64
I (2346) CLIENT_PROFILER: =======================================================
I (2346) CLIENT_PROFILER:  [BENCHMARK RESULT 1/10]
I (2346) CLIENT_PROFILER:   -> Current RSSI       : -53 dBm
I (2346) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (2356) CLIENT_PROFILER:   -> Time Elapsed       : 0.169 Seconds
I (2366) CLIENT_PROFILER:   -> Measured Speed     : 2420.07 Kbps
I (2366) CLIENT_PROFILER: =======================================================
I (4376) CLIENT_PROFILER: [ROUND 2/10]: Connecting to 192.168.4.1:8080
I (4526) CLIENT_PROFILER: =======================================================
I (4526) CLIENT_PROFILER:  [BENCHMARK RESULT 2/10]
I (4526) CLIENT_PROFILER:   -> Current RSSI       : -55 dBm
I (4526) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (4536) CLIENT_PROFILER:   -> Time Elapsed       : 0.140 Seconds
I (4546) CLIENT_PROFILER:   -> Measured Speed     : 2931.33 Kbps
I (4546) CLIENT_PROFILER: =======================================================
I (6556) CLIENT_PROFILER: [ROUND 3/10]: Connecting to 192.168.4.1:8080
I (6736) CLIENT_PROFILER: =======================================================
I (6736) CLIENT_PROFILER:  [BENCHMARK RESULT 3/10]
I (6736) CLIENT_PROFILER:   -> Current RSSI       : -57 dBm
I (6736) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (6746) CLIENT_PROFILER:   -> Time Elapsed       : 0.168 Seconds
I (6746) CLIENT_PROFILER:   -> Measured Speed     : 2432.43 Kbps
I (6756) CLIENT_PROFILER: =======================================================
I (8766) CLIENT_PROFILER: [ROUND 4/10]: Connecting to 192.168.4.1:8080
I (8886) CLIENT_PROFILER: =======================================================
I (8886) CLIENT_PROFILER:  [BENCHMARK RESULT 4/10]
I (8886) CLIENT_PROFILER:   -> Current RSSI       : -56 dBm
I (8896) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (8896) CLIENT_PROFILER:   -> Time Elapsed       : 0.110 Seconds
I (8906) CLIENT_PROFILER:   -> Measured Speed     : 3737.40 Kbps
I (8916) CLIENT_PROFILER: =======================================================
I (10916) CLIENT_PROFILER: [ROUND 5/10]: Connecting to 192.168.4.1:8080
I (11096) CLIENT_PROFILER: =======================================================
I (11096) CLIENT_PROFILER:  [BENCHMARK RESULT 5/10]
I (11096) CLIENT_PROFILER:   -> Current RSSI       : -54 dBm
I (11096) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (11106) CLIENT_PROFILER:   -> Time Elapsed       : 0.107 Seconds
I (11106) CLIENT_PROFILER:   -> Measured Speed     : 3821.64 Kbps
I (11116) CLIENT_PROFILER: =======================================================
I (13126) CLIENT_PROFILER: [ROUND 6/10]: Connecting to 192.168.4.1:8080
I (13236) CLIENT_PROFILER: =======================================================
I (13236) CLIENT_PROFILER:  [BENCHMARK RESULT 6/10]
I (13236) CLIENT_PROFILER:   -> Current RSSI       : -54 dBm
I (13236) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (13246) CLIENT_PROFILER:   -> Time Elapsed       : 0.099 Seconds
I (13246) CLIENT_PROFILER:   -> Measured Speed     : 4140.89 Kbps
I (13256) CLIENT_PROFILER: =======================================================
I (15266) CLIENT_PROFILER: [ROUND 7/10]: Connecting to 192.168.4.1:8080
I (15396) CLIENT_PROFILER: =======================================================
I (15396) CLIENT_PROFILER:  [BENCHMARK RESULT 7/10]
I (15396) CLIENT_PROFILER:   -> Current RSSI       : -57 dBm
I (15406) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (15406) CLIENT_PROFILER:   -> Time Elapsed       : 0.127 Seconds
I (15416) CLIENT_PROFILER:   -> Measured Speed     : 3236.74 Kbps
I (15416) CLIENT_PROFILER: =======================================================
I (17426) CLIENT_PROFILER: [ROUND 8/10]: Connecting to 192.168.4.1:8080
I (17546) CLIENT_PROFILER: =======================================================
I (17546) CLIENT_PROFILER:  [BENCHMARK RESULT 8/10]
I (17546) CLIENT_PROFILER:   -> Current RSSI       : -60 dBm
I (17556) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (17556) CLIENT_PROFILER:   -> Time Elapsed       : 0.115 Seconds
I (17566) CLIENT_PROFILER:   -> Measured Speed     : 3573.24 Kbps
I (17566) CLIENT_PROFILER: =======================================================
I (19576) CLIENT_PROFILER: [ROUND 9/10]: Connecting to 192.168.4.1:8080
I (19696) CLIENT_PROFILER: =======================================================
I (19696) CLIENT_PROFILER:  [BENCHMARK RESULT 9/10]
I (19696) CLIENT_PROFILER:   -> Current RSSI       : -55 dBm
I (19696) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (19706) CLIENT_PROFILER:   -> Time Elapsed       : 0.108 Seconds
I (19706) CLIENT_PROFILER:   -> Measured Speed     : 3781.81 Kbps
I (19716) CLIENT_PROFILER: =======================================================
I (21726) CLIENT_PROFILER: [ROUND 10/10]: Connecting to 192.168.4.1:8080
I (21826) CLIENT_PROFILER: =======================================================
I (21826) CLIENT_PROFILER:  [BENCHMARK RESULT 10/10]
I (21826) CLIENT_PROFILER:   -> Current RSSI       : -55 dBm
I (21836) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (21836) CLIENT_PROFILER:   -> Time Elapsed       : 0.092 Seconds
I (21846) CLIENT_PROFILER:   -> Measured Speed     : 4456.44 Kbps
I (21846) CLIENT_PROFILER: =======================================================
I (23856) CLIENT_PROFILER: All benchmark rounds completed
```

---

## 07-Labsheet-06-3-FreeRTOS-Sensor-Queue
## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task        | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :------------------------ | :-----------------------------------------: | :--------------------------------------------: | :------------------: |
| **`SensorCollectorTask`** |                    3072                     |            1196 Words / 1196 Bytes             |       ปลอดภัย        |
| **`NetworkCommTask`**     |                    4096                     |            2248 Words / 2248 Bytes             |       ปลอดภัย        |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
	**ตอบ:**  
	* **การจัดการ Race Condition:** หากใช้ตัวแปร Global แล้วมีหลาย Task พยายามอ่านและเขียนข้อมูลพร้อมกัน (เช่น Task หนึ่งกำลังเขียนข้อมูลยังไม่ทันเสร็จ แต่อีก Task เข้ามาอ่านไปก่อน) จะทำให้เกิดปัญหาข้อมูลผิดเพี้ยน (Data Corruption) การใช้ Queue ของ FreeRTOS จะมีกลไกป้องกันการเข้าถึงพร้อมกัน (Internal Locking / Critical Section) อยู่เบื้องหลัง ทำให้มั่นใจได้ว่าการส่งและรับข้อมูลจะเป็นไปอย่างสมบูรณ์ทีละชุดเสมอ 
	* **กลไกการรอ (Blocking):** Queue มีกลไกให้ Task สามารถหยุดรอ (Block state) ได้อย่างปลอดภัย เช่น รอจนกว่าจะมีข้อมูลเข้ามา หรือรอจนกว่าคิวจะว่าง โดยระหว่างที่รอนั้นจะไม่กินทรัพยากร CPU (ไม่ต้องวนลูปเช็คค่าตัวแปร) ทำให้ระบบโดยรวมมีประสิทธิภาพสูงขึ้น

2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
	**ตอบ:**  
	* **ป้องกันระบบล่ม (Stack Overflow):** ค่า High Water Mark คือการวัด "พื้นที่หน่วยความจำขั้นต่ำที่สุด" (Minimum Free Stack) ที่ Task นั้นๆ เคยใช้งานลงไปลึกที่สุดตั้งแต่เริ่มทำงาน หากค่านี้ลดลงจนใกล้ 0 หรือเป็น 0 แสดงว่าหน่วยความจำที่จองไว้ใกล้จะทะลุ (Stack Overflow) ซึ่งเป็นสาเหตุหลักที่ทำให้บอร์ดไมโครคอนโทรลเลอร์ค้างหรือรีสตาร์ทตัวเองแบบสุ่ม 
	* **การปรับจูนหน่วยความจำ (Memory Optimization):** หากค่า High Water Mark เหลือเยอะมาก (เช่น จองไว้ 4096 แต่เหลือตั้ง 3000) เราสามารถใช้ข้อมูลนี้กลับไปปรับลดขนาด Stack ในคำสั่ง `xTaskCreate` ได้ เพื่อคืนพื้นที่ RAM (Heap) กลับไปให้ระบบนำไปใช้ประโยชน์ในส่วนอื่นๆ ต่อไป

3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
	**ตอบ:**  
	* **สภาวะคิวเต็ม (Queue Full):** เมื่อความเร็วของฝั่งสร้างข้อมูล (Producer) เร็วกว่าฝั่งประมวลผล (Consumer) ข้อมูลจะค่อยๆ สะสมจนเต็มความจุของคิว (เช่น ในโค้ดเราจองคิวไว้ขนาด 10 ชุด ข้อมูลก็จะค้างเต็ม 10 ชุดอย่างรวดเร็ว) 
	* **การรับมือของระบบ:** เมื่อคิวเต็ม คำสั่ง `xQueueSend` ใน `vSensorTask` จะไม่สามารถนำข้อมูลใหม่ใส่ลงไปได้ทันที ระบบจะทำงานตามเงื่อนไขเวลา (Timeout) ที่เราตั้งไว้ เช่น ในโค้ดตั้งไว้ให้รอ `pdMS_TO_TICKS(100)` (รอ 100 มิลลิวินาที) หากภายใน 100ms คิวยังไม่ว่าง คำสั่งจะคืนค่าล้มเหลว (`pdFALSE`) ส่งผลให้ข้อมูลเซนเซอร์ชุดนั้นถูกทิ้งไป (Drop) พร้อมกับพิมพ์ข้อความแจ้งเตือน "[QUEUE WARNING]: Queue Full!" วิธีการนี้ช่วยป้องกันไม่ให้ระบบหยุดค้าง (Deadlock) หรือเกิดปัญหาหน่วยความจำเต็ม (Out of Memory)


Log
```text
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/Thanu/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug 13 2026 12:22:12
I (29) boot: Multicore bootloader
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=09e38h ( 40504) map
I (102) esp_image: segment 1: paddr=00019e60 vaddr=3ffb0000 size=023d8h (  9176) load
I (106) esp_image: segment 2: paddr=0001c240 vaddr=40080000 size=03dd8h ( 15832) load
I (112) esp_image: segment 3: paddr=00020020 vaddr=400d0020 size=13850h ( 79952) map
I (141) esp_image: segment 4: paddr=00033878 vaddr=40083dd8 size=0934ch ( 37708) load
I (156) esp_image: segment 5: paddr=0003cbcc vaddr=50000000 size=00020h (    32) load
I (162) boot: Loaded app from partition at offset 0x10000
I (162) boot: Disabling RNG early entropy source...
I (174) cpu_start: Multicore app
I (182) cpu_start: Pro cpu start user code
I (182) cpu_start: cpu freq: 160000000 Hz
I (182) app_init: Application information:
I (182) app_init: Project name:     freertos_sensor_queue
I (187) app_init: App version:      029da6d-dirty
I (192) app_init: Compile time:     Aug 13 2026 12:21:40
I (197) app_init: ELF file SHA256:  76c7e9406...
I (201) app_init: ESP-IDF:          v5.5.1
I (205) efuse_init: Min chip rev:     v0.0
I (209) efuse_init: Max chip rev:     v3.99 
I (213) efuse_init: Chip rev:         v3.1
I (217) heap_init: Initializing. RAM available for dynamic allocation:
I (223) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (228) heap_init: At 3FFB2CA8 len 0002D358 (180 KiB): DRAM
I (233) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (239) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (244) heap_init: At 4008D124 len 00012EDC (75 KiB): IRAM
I (251) spi_flash: detected chip: generic
I (253) spi_flash: flash io: dio
W (256) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (269) main_task: Started on CPU0
I (279) main_task: Calling app_main()
I (279) LAB_FREERTOS_QUEUE: ==================================================================
I (279) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (289) LAB_FREERTOS_QUEUE: ==================================================================
I (299) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 0
I (299) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 31.1 C, Hum: 69.7 %, Lux: 510
I (309) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (319) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (319) LAB_FREERTOS_QUEUE: =======================================================
I (329) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (339) LAB_FREERTOS_QUEUE:   -> Timestamp   : 30 ms
I (339) LAB_FREERTOS_QUEUE:   -> Temperature : 31.10 degC
I (349) LAB_FREERTOS_QUEUE:   -> Humidity    : 69.70 %
I (349) LAB_FREERTOS_QUEUE:   -> Light Lux   : 510 lux
I (359) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (369) LAB_FREERTOS_QUEUE: =======================================================
I (369) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (379) main_task: Returned from app_main()
I (1819) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 31.8 C, Hum: 57.0 %, Lux: 511
I (1819) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (1819) LAB_FREERTOS_QUEUE: =======================================================
I (1829) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (1829) LAB_FREERTOS_QUEUE:   -> Timestamp   : 1550 ms
I (1839) LAB_FREERTOS_QUEUE:   -> Temperature : 31.80 degC
I (1839) LAB_FREERTOS_QUEUE:   -> Humidity    : 57.00 %
I (1849) LAB_FREERTOS_QUEUE:   -> Light Lux   : 511 lux
I (1849) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (1859) LAB_FREERTOS_QUEUE: =======================================================
I (1869) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (3319) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 25.0 C, Hum: 66.0 %, Lux: 549
I (3319) LAB_FREERTOS_QUEUE: =======================================================
I (3319) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (3319) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (3329) LAB_FREERTOS_QUEUE:   -> Timestamp   : 3050 ms
I (3339) LAB_FREERTOS_QUEUE:   -> Temperature : 25.00 degC
I (3339) LAB_FREERTOS_QUEUE:   -> Humidity    : 66.00 %
I (3349) LAB_FREERTOS_QUEUE:   -> Light Lux   : 549 lux
I (3349) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (3359) LAB_FREERTOS_QUEUE: =======================================================
I (3369) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (4829) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 33.1 C, Hum: 52.0 %, Lux: 431
I (4829) LAB_FREERTOS_QUEUE: =======================================================
I (4829) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (4829) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (4839) LAB_FREERTOS_QUEUE:   -> Timestamp   : 4560 ms
I (4849) LAB_FREERTOS_QUEUE:   -> Temperature : 33.10 degC
I (4849) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.00 %
I (4859) LAB_FREERTOS_QUEUE:   -> Light Lux   : 431 lux
I (4859) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (4869) LAB_FREERTOS_QUEUE: =======================================================
I (4879) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (6339) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 32.6 C, Hum: 69.5 %, Lux: 283
I (6339) LAB_FREERTOS_QUEUE: =======================================================
I (6339) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (6339) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (6349) LAB_FREERTOS_QUEUE:   -> Timestamp   : 6070 ms
I (6359) LAB_FREERTOS_QUEUE:   -> Temperature : 32.60 degC
I (6359) LAB_FREERTOS_QUEUE:   -> Humidity    : 69.50 %
I (6369) LAB_FREERTOS_QUEUE:   -> Light Lux   : 283 lux
I (6369) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (6379) LAB_FREERTOS_QUEUE: =======================================================
I (6389) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (7849) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.2 C, Hum: 50.0 %, Lux: 539
I (7849) LAB_FREERTOS_QUEUE: =======================================================
I (7849) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (7849) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (7859) LAB_FREERTOS_QUEUE:   -> Timestamp   : 7580 ms
I (7869) LAB_FREERTOS_QUEUE:   -> Temperature : 34.20 degC
I (7869) LAB_FREERTOS_QUEUE:   -> Humidity    : 50.00 %
I (7879) LAB_FREERTOS_QUEUE:   -> Light Lux   : 539 lux
I (7879) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (7889) LAB_FREERTOS_QUEUE: =======================================================
I (7899) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (9359) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 25.5 C, Hum: 68.3 %, Lux: 247
I (9359) LAB_FREERTOS_QUEUE: =======================================================
I (9359) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (9359) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (9369) LAB_FREERTOS_QUEUE:   -> Timestamp   : 9090 ms
I (9379) LAB_FREERTOS_QUEUE:   -> Temperature : 25.50 degC
I (9379) LAB_FREERTOS_QUEUE:   -> Humidity    : 68.30 %
I (9389) LAB_FREERTOS_QUEUE:   -> Light Lux   : 247 lux
I (9389) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (9399) LAB_FREERTOS_QUEUE: =======================================================
I (9409) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (10869) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 33.0 C, Hum: 68.7 %, Lux: 668
I (10869) LAB_FREERTOS_QUEUE: =======================================================
I (10869) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (10869) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (10879) LAB_FREERTOS_QUEUE:   -> Timestamp   : 10600 ms
I (10889) LAB_FREERTOS_QUEUE:   -> Temperature : 33.00 degC
I (10889) LAB_FREERTOS_QUEUE:   -> Humidity    : 68.70 %
I (10899) LAB_FREERTOS_QUEUE:   -> Light Lux   : 668 lux
I (10899) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (10909) LAB_FREERTOS_QUEUE: =======================================================
I (10919) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (12379) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 33.8 C, Hum: 52.7 %, Lux: 207
I (12379) LAB_FREERTOS_QUEUE: =======================================================
I (12379) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (12379) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (12389) LAB_FREERTOS_QUEUE:   -> Timestamp   : 12110 ms
I (12399) LAB_FREERTOS_QUEUE:   -> Temperature : 33.80 degC
I (12399) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.70 %
I (12409) LAB_FREERTOS_QUEUE:   -> Light Lux   : 207 lux
I (12409) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (12419) LAB_FREERTOS_QUEUE: =======================================================
I (12429) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (13889) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 33.6 C, Hum: 60.7 %, Lux: 624
I (13889) LAB_FREERTOS_QUEUE: =======================================================
I (13889) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (13889) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (13899) LAB_FREERTOS_QUEUE:   -> Timestamp   : 13620 ms
I (13909) LAB_FREERTOS_QUEUE:   -> Temperature : 33.60 degC
I (13909) LAB_FREERTOS_QUEUE:   -> Humidity    : 60.70 %
I (13919) LAB_FREERTOS_QUEUE:   -> Light Lux   : 624 lux
I (13919) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (13929) LAB_FREERTOS_QUEUE: =======================================================
I (13939) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (15399) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 33.4 C, Hum: 50.0 %, Lux: 281
I (15399) LAB_FREERTOS_QUEUE: =======================================================
I (15399) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (15399) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (15409) LAB_FREERTOS_QUEUE:   -> Timestamp   : 15130 ms
I (15419) LAB_FREERTOS_QUEUE:   -> Temperature : 33.40 degC
I (15419) LAB_FREERTOS_QUEUE:   -> Humidity    : 50.00 %
I (15429) LAB_FREERTOS_QUEUE:   -> Light Lux   : 281 lux
I (15429) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (15439) LAB_FREERTOS_QUEUE: =======================================================
I (15449) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (16909) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 26.1 C, Hum: 52.1 %, Lux: 486
I (16909) LAB_FREERTOS_QUEUE: =======================================================
I (16909) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (16909) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (16919) LAB_FREERTOS_QUEUE:   -> Timestamp   : 16640 ms
I (16929) LAB_FREERTOS_QUEUE:   -> Temperature : 26.10 degC
I (16929) LAB_FREERTOS_QUEUE:   -> Humidity    : 52.10 %
I (16939) LAB_FREERTOS_QUEUE:   -> Light Lux   : 486 lux
I (16939) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (16949) LAB_FREERTOS_QUEUE: =======================================================
I (16959) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (18419) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 32.4 C, Hum: 58.0 %, Lux: 277
I (18419) LAB_FREERTOS_QUEUE: =======================================================
I (18419) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (18419) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (18429) LAB_FREERTOS_QUEUE:   -> Timestamp   : 18150 ms
I (18439) LAB_FREERTOS_QUEUE:   -> Temperature : 32.40 degC
I (18439) LAB_FREERTOS_QUEUE:   -> Humidity    : 58.00 %
I (18449) LAB_FREERTOS_QUEUE:   -> Light Lux   : 277 lux
I (18449) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (18459) LAB_FREERTOS_QUEUE: =======================================================
I (18469) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (19929) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 27.3 C, Hum: 60.3 %, Lux: 599
I (19929) LAB_FREERTOS_QUEUE: =======================================================
I (19929) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (19929) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (19939) LAB_FREERTOS_QUEUE:   -> Timestamp   : 19660 ms
I (19949) LAB_FREERTOS_QUEUE:   -> Temperature : 27.30 degC
I (19949) LAB_FREERTOS_QUEUE:   -> Humidity    : 60.30 %
I (19959) LAB_FREERTOS_QUEUE:   -> Light Lux   : 599 lux
I (19959) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (19969) LAB_FREERTOS_QUEUE: =======================================================
I (19979) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (21439) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 33.6 C, Hum: 65.1 %, Lux: 358
I (21439) LAB_FREERTOS_QUEUE: =======================================================
I (21439) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (21439) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (21449) LAB_FREERTOS_QUEUE:   -> Timestamp   : 21170 ms
I (21459) LAB_FREERTOS_QUEUE:   -> Temperature : 33.60 degC
I (21459) LAB_FREERTOS_QUEUE:   -> Humidity    : 65.10 %
I (21469) LAB_FREERTOS_QUEUE:   -> Light Lux   : 358 lux
I (21469) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (21479) LAB_FREERTOS_QUEUE: =======================================================
I (21489) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (22949) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 29.3 C, Hum: 60.6 %, Lux: 285
I (22949) LAB_FREERTOS_QUEUE: =======================================================
I (22949) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (22949) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (22959) LAB_FREERTOS_QUEUE:   -> Timestamp   : 22680 ms
I (22969) LAB_FREERTOS_QUEUE:   -> Temperature : 29.30 degC
I (22969) LAB_FREERTOS_QUEUE:   -> Humidity    : 60.60 %
I (22979) LAB_FREERTOS_QUEUE:   -> Light Lux   : 285 lux
I (22979) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (22989) LAB_FREERTOS_QUEUE: =======================================================
I (22999) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (24459) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 25.7 C, Hum: 63.7 %, Lux: 607
I (24459) LAB_FREERTOS_QUEUE: =======================================================
I (24459) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (24459) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (24469) LAB_FREERTOS_QUEUE:   -> Timestamp   : 24190 ms
I (24479) LAB_FREERTOS_QUEUE:   -> Temperature : 25.70 degC
I (24479) LAB_FREERTOS_QUEUE:   -> Humidity    : 63.70 %
I (24489) LAB_FREERTOS_QUEUE:   -> Light Lux   : 607 lux
I (24489) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (24499) LAB_FREERTOS_QUEUE: =======================================================
I (24509) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (25969) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 34.8 C, Hum: 61.7 %, Lux: 449
I (25969) LAB_FREERTOS_QUEUE: =======================================================
I (25969) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (25969) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (25979) LAB_FREERTOS_QUEUE:   -> Timestamp   : 25700 ms
I (25989) LAB_FREERTOS_QUEUE:   -> Temperature : 34.80 degC
I (25989) LAB_FREERTOS_QUEUE:   -> Humidity    : 61.70 %
I (25999) LAB_FREERTOS_QUEUE:   -> Light Lux   : 449 lux
I (25999) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (26009) LAB_FREERTOS_QUEUE: =======================================================
I (26019) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
I (27479) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 32.5 C, Hum: 54.0 %, Lux: 274
I (27479) LAB_FREERTOS_QUEUE: =======================================================
I (27479) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1196 words (1196 bytes)
I (27479) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (27489) LAB_FREERTOS_QUEUE:   -> Timestamp   : 27210 ms
I (27499) LAB_FREERTOS_QUEUE:   -> Temperature : 32.50 degC
I (27499) LAB_FREERTOS_QUEUE:   -> Humidity    : 54.00 %
I (27509) LAB_FREERTOS_QUEUE:   -> Light Lux   : 274 lux
I (27509) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (27519) LAB_FREERTOS_QUEUE: =======================================================
I (27529) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2248 words (2248 bytes)
```

---

## 08-Labsheet-06-4-IoT-Sensor-Dashboard
## 7. ตารางบันทึกผลการทดลอง (Experiment Results)

### 7.1 บันทึกข้อมูลจาก Dashboard

| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :------: | :--------------: | :----------: | :-------: | :------------: |
|  **1**   |      27.90       |    66.40     |    506    |      7950      |
|  **2**   |      33.30       |    56.60     |    437    |      9460      |
|  **3**   |      33.20       |    63.80     |    255    |     15490      |

### 7.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response จาก Browser:

```json
{
	"temperature":33.20,
	"humidity":63.80,
	"light_lux":255,
	"timestamp_ms":15490
}
```

---
#### Webapp
<img width="894" height="1829" alt="278130" src="https://github.com/user-attachments/assets/c7c7c45a-2b4b-4c66-9104-7fcbe7b8133c" />

---
## 8. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
	**ตอบ:**  
	* **เหตุผลที่ต้องใช้:** ตัวแปร `g_latest_data` เป็น Shared Resource (ทรัพยากรที่ใช้ร่วมกัน) ชนิด Struct ที่ประกอบไปด้วยข้อมูลหลายฟิลด์ Mutex จะทำหน้าที่เป็นกุญแจ (Lock) เพื่อให้มั่นใจว่าในจังหวะที่มีการอ่านหรือเขียนข้อมูล จะมีเพียงแค่ Task เดียวเท่านั้นที่สามารถจัดการตัวแปรนี้ได้จนกว่าจะทำงานเสร็จ (Atomic Operation) 
	* **ถ้าไม่ใช้จะเกิดอะไรขึ้น:** จะเกิดความเสี่ยงเรื่อง **Race Condition** และ **Data Tearing (ข้อมูลแหว่ง)** ตัวอย่างเช่น หาก `vNetworkTask` กำลังเขียนข้อมูลชุดใหม่ลงไป (เพิ่งเขียนอุณหภูมิเสร็จ แต่ยังไม่ได้เขียน Timestamp) แล้วถูกระบบ (Scheduler) ตัดสลับให้ HTTP Handler เข้ามาอ่านข้อมูลพอดี ผลลัพธ์คือผู้ใช้งานจะได้ข้อมูล JSON ที่เป็นอุณหภูมิของรอบใหม่ แต่ Timestamp เป็นของรอบเก่า ทำให้ข้อมูลผสมกันและผิดเพี้ยน

2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?
	**ตอบ:**  
	* **ไม่ใช่ Thread เดียวกัน** เมื่อเราเรียกใช้คำสั่ง `httpd_start()` ไลบรารีจะทำการสร้าง FreeRTOS Task เบื้องหลังของตัวมันเองขึ้นมาใหม่โดยอัตโนมัติ (มักจะใช้ชื่อ Task ว่า `httpd`) เพื่อคอยวนลูปรับ Request จาก Client 
	* ดังนั้น ฟังก์ชัน Handler ต่างๆ (เช่น `api_data_handler`) จะถูกรันและประมวลผลอยู่บน Context ของ Thread ของ HTTP Server ซึ่งแยกทำงานอิสระ (Asynchronous) จาก `vSensorTask` และ `vNetworkTask` ของเราอย่างสิ้นเชิง (นี่คือสาเหตุหลักที่บังคับให้เรา "ต้อง" ใช้ Mutex ในข้อ 1 เพื่อรับส่งข้อมูลข้าม Thread อย่างปลอดภัย)

3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
	**ตอบ:**  
	* **ข้อดี:** นำไปใช้งานได้ง่ายมาก โค้ดสั้น ไม่มีความซับซ้อน และสามารถทำงานได้ในอุปกรณ์หรือเบราว์เซอร์รุ่นเก่ามากๆ ที่อาจจะปิดการทำงานของ JavaScript เอาไว้ 
	* **ข้อเสีย:** 
		* **กินทรัพยากร ESP32:** เบราว์เซอร์จะสั่งโหลดข้อมูลหน้าเว็บใหม่ "ทั้งหมด" (ทั้งก้อน HTML และ CSS) ทุกๆ 2 วินาที ทำให้บอร์ด ESP32 ต้องรับภาระประมวลผลส่งข้อมูลก้อนใหญ่ตลอดเวลา 
		* **เสียประสบการณ์การใช้งาน (UX):** หน้าจอจะเกิดอาการกระพริบ (Flicker) ทุกครั้งที่รีเฟรช และสถานะบนหน้าเว็บทั้งหมดจะถูกรีเซ็ต (เช่น หากผู้ใช้เลื่อน Scroll bar ลงมา มันจะเด้งกลับขึ้นไปด้านบนสุดใหม่ทุกๆ 2 วินาที) 
		* *(แตกต่างจาก `fetch()` ในแล็บนี้ ที่ดึงมาเฉพาะตัวเลข JSON เล็กๆ แล้วนำมาอัปเดตแทนที่ข้อความเดิม (DOM) ทำให้หน้าเว็บลื่นไหลและประหยัดแบนด์วิดท์มากกว่ามหาศาล)*

Log
```text
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/Thanu/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug 13 2026 13:21:20
I (29) boot: Multicore bootloader
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1cc08h (117768) map
I (128) esp_image: segment 1: paddr=0002cc30 vaddr=3ffb0000 size=033e8h ( 13288) load
I (133) esp_image: segment 2: paddr=00030020 vaddr=400d0020 size=8ecdch (584924) map
I (333) esp_image: segment 3: paddr=000bed04 vaddr=3ffb33e8 size=00b04h (  2820) load
I (335) esp_image: segment 4: paddr=000bf810 vaddr=40080000 size=17fc4h ( 98244) load
I (376) esp_image: segment 5: paddr=000d77dc vaddr=50000000 size=00020h (    32) load
I (388) boot: Loaded app from partition at offset 0x10000
I (388) boot: Disabling RNG early entropy source...
I (398) cpu_start: Multicore app
I (406) cpu_start: Pro cpu start user code
I (407) cpu_start: cpu freq: 160000000 Hz
I (407) app_init: Application information:
I (407) app_init: Project name:     iot_sensor_dashboard
I (412) app_init: App version:      029da6d-dirty
I (416) app_init: Compile time:     Aug 13 2026 13:20:53
I (421) app_init: ELF file SHA256:  924dc08eb...
I (425) app_init: ESP-IDF:          v5.5.1
I (429) efuse_init: Min chip rev:     v0.0
I (433) efuse_init: Max chip rev:     v3.99 
I (437) efuse_init: Chip rev:         v3.1
I (441) heap_init: Initializing. RAM available for dynamic allocation:
I (447) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (452) heap_init: At 3FFB7FE8 len 00028018 (160 KiB): DRAM
I (458) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (463) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (468) heap_init: At 40097FC4 len 0000803C (32 KiB): IRAM
I (475) spi_flash: detected chip: generic
I (477) spi_flash: flash io: dio
W (480) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (494) main_task: Started on CPU0
I (504) main_task: Calling app_main()
I (504) MAIN: [FORENSIC]: Call nvs_flash_init()
I (534) MAIN: =======================================================
I (534) MAIN:   Lab 6-4: IoT Sensor Dashboard
I (534) MAIN:   SoftAP + FreeRTOS Queue + HTTP Server
I (534) MAIN: =======================================================
I (544) MAIN: [FORENSIC]: Call xSemaphoreCreateMutex()
I (544) MAIN: [FORENSIC]: Mutex created at 0x3ffbb684
I (554) MAIN: [FORENSIC]: Call xQueueCreate(10, sizeof(sensor_data_t))
I (554) MAIN: [FORENSIC]: Queue created at 0x3ffbb6dc
I (564) SOFTAP: [FORENSIC]: Call esp_netif_init()
I (574) SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (574) SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (584) SOFTAP: [FORENSIC]: SoftAP netif created at 0x3ffbd97c (IP: 192.168.4.1)
I (584) SOFTAP: [FORENSIC]: Call esp_wifi_init()
I (604) wifi:wifi driver task: 3ffc00bc, prio:23, stack:6656, core=0
I (624) wifi:wifi firmware version: 14da9b7
I (624) wifi:wifi certification version: v7.0
I (624) wifi:config NVS flash: enabled
I (624) wifi:config nano formatting: disabled
I (624) wifi:Init data frame dynamic rx buffer num: 32
I (634) wifi:Init static rx mgmt buffer num: 5
I (634) wifi:Init management short buffer num: 32
I (634) wifi:Init dynamic tx buffer num: 32
I (644) wifi:Init static rx buffer size: 1600
I (644) wifi:Init static rx buffer num: 10
I (654) wifi:Init dynamic rx buffer num: 32
I (654) wifi_init: rx ba win: 6
I (654) wifi_init: accept mbox: 6
I (664) wifi_init: tcpip mbox: 32
I (664) wifi_init: udp mbox: 6
I (664) wifi_init: tcp mbox: 6
I (664) wifi_init: tcp tx win: 5760
I (674) wifi_init: tcp rx win: 5760
I (674) wifi_init: tcp mss: 1440
I (674) wifi_init: WiFi IRAM OP enabled
I (684) wifi_init: WiFi RX IRAM OP enabled
I (684) SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (694) SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (694) SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP)
I (714) SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (714) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (794) wifi:mode : softAP (14:33:5c:0e:94:45)
I (794) wifi:Total power save buffer number: 16
I (794) wifi:Init max length of beacon: 752/752
I (794) wifi:Init max length of beacon: 752/752
I (804) SOFTAP: =======================================================
I (804) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (814) SOFTAP:   SoftAP Running! SSID: "MY_ESP32_SENSOR_AP_0085", Channel: 1
I (824) SOFTAP:   -> Connect your phone to: MY_ESP32_SENSOR_AP_0085
I (824) SOFTAP:   -> Then open browser:      http://192.168.4.1
I (834) SOFTAP: =======================================================
I (844) HTTP_SERVER: [FORENSIC]: Call httpd_start()
I (844) HTTP_SERVER: =======================================================
I (854) HTTP_SERVER: [HTTP SERVER]: Started successfully
I (854) HTTP_SERVER:   -> Dashboard : http://192.168.4.1/
I (864) HTTP_SERVER:   -> JSON API  : http://192.168.4.1/api/data
I (864) HTTP_SERVER: =======================================================
I (874) MAIN: [FORENSIC]: Call xTaskCreate(vSensorTask)  Stack=3072
I (884) SENSOR_TASK: [FORENSIC]: Sensor Collector Task started on Core 0
I (884) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 34.2 C, Hum: 56.7 %, Lux: 464
I (894) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1184 words (1184 bytes)
I (904) MAIN: [FORENSIC]: Call xTaskCreate(vNetworkTask) Stack=4096
I (904) NETWORK_TASK: [FORENSIC]: Network Task started on Core 0
I (914) NETWORK_TASK: =======================================================
I (924) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (924) NETWORK_TASK:   -> Timestamp   : 390 ms
I (924) NETWORK_TASK:   -> Temperature : 34.20 degC
I (934) NETWORK_TASK:   -> Humidity    : 56.70 %
I (934) NETWORK_TASK:   -> Light Lux   : 464 lux
I (944) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (944) NETWORK_TASK: =======================================================
I (954) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (964) MAIN: =======================================================
I (964) MAIN:   System Ready! Open browser at http://192.168.4.1
I (974) MAIN: =======================================================
I (984) main_task: Returned from app_main()
I (2404) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 32.2 C, Hum: 61.2 %, Lux: 641
I (2404) NETWORK_TASK: =======================================================
I (2404) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1184 words (1184 bytes)
I (2404) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (2414) NETWORK_TASK:   -> Timestamp   : 1910 ms
I (2424) NETWORK_TASK:   -> Temperature : 32.20 degC
I (2424) NETWORK_TASK:   -> Humidity    : 61.20 %
I (2434) NETWORK_TASK:   -> Light Lux   : 641 lux
I (2434) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (2444) NETWORK_TASK: =======================================================
I (2444) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (3914) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 31.4 C, Hum: 61.7 %, Lux: 628
I (3914) NETWORK_TASK: =======================================================
I (3914) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1184 words (1184 bytes)
I (3914) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (3924) NETWORK_TASK:   -> Timestamp   : 3420 ms
I (3934) NETWORK_TASK:   -> Temperature : 31.40 degC
I (3934) NETWORK_TASK:   -> Humidity    : 61.70 %
I (3944) NETWORK_TASK:   -> Light Lux   : 628 lux
I (3944) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (3954) NETWORK_TASK: =======================================================
I (3954) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (5424) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 28.6 C, Hum: 59.4 %, Lux: 337
I (5424) NETWORK_TASK: =======================================================
I (5424) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1184 words (1184 bytes)
I (5424) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (5434) NETWORK_TASK:   -> Timestamp   : 4930 ms
I (5444) NETWORK_TASK:   -> Temperature : 28.60 degC
I (5444) NETWORK_TASK:   -> Humidity    : 59.40 %
I (5454) NETWORK_TASK:   -> Light Lux   : 337 lux
I (5454) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (5464) NETWORK_TASK: =======================================================
I (5464) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (6934) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 28.4 C, Hum: 52.2 %, Lux: 320
I (6934) NETWORK_TASK: =======================================================
I (6934) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1184 words (1184 bytes)
I (6934) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (6944) NETWORK_TASK:   -> Timestamp   : 6440 ms
I (6954) NETWORK_TASK:   -> Temperature : 28.40 degC
I (6954) NETWORK_TASK:   -> Humidity    : 52.20 %
I (6964) NETWORK_TASK:   -> Light Lux   : 320 lux
I (6964) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (6974) NETWORK_TASK: =======================================================
I (6974) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (7664) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (7664) wifi:station: 96:2f:5a:c4:fd:fd join, AID=1, bgn, 20
I (7804) SOFTAP: =======================================================
I (7804) SOFTAP: [FORENSIC EVENT]: Client Connected to SoftAP!
I (7804) SOFTAP:   -> Client MAC : 96:2F:5A:C4:FD:FD
I (7814) SOFTAP:   -> AID        : 1
I (7814) SOFTAP: =======================================================
I (7814) wifi:<ba-add>idx:2 (ifx:1, 96:2f:5a:c4:fd:fd), tid:0, ssn:0, winSize:64
I (8014) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (8444) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 27.9 C, Hum: 66.4 %, Lux: 506
I (8444) NETWORK_TASK: =======================================================
I (8444) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1184 words (1184 bytes)
I (8444) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (8454) NETWORK_TASK:   -> Timestamp   : 7950 ms
I (8464) NETWORK_TASK:   -> Temperature : 27.90 degC
I (8464) NETWORK_TASK:   -> Humidity    : 66.40 %
I (8474) NETWORK_TASK:   -> Light Lux   : 506 lux
I (8474) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (8474) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (8484) NETWORK_TASK: =======================================================
I (8484) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (8494) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (8504) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":27.90,"humidity":66.40,"light_lux":506,"timestamp_ms":7950}
I (9104) HTTP_SERVER: [FORENSIC]: GET / (Dashboard) requested
I (9114) HTTP_SERVER: [FORENSIC]: HTML Dashboard sent (2730 bytes)
I (9954) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 33.3 C, Hum: 56.6 %, Lux: 437
I (9954) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (9954) NETWORK_TASK: =======================================================
I (9964) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (9964) NETWORK_TASK:   -> Timestamp   : 9460 ms
I (9974) NETWORK_TASK:   -> Temperature : 33.30 degC
I (9974) NETWORK_TASK:   -> Humidity    : 56.60 %
I (9984) NETWORK_TASK:   -> Light Lux   : 437 lux
I (9984) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (9994) NETWORK_TASK: =======================================================
I (9994) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (10454) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (10454) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (10464) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":33.30,"humidity":56.60,"light_lux":437,"timestamp_ms":9460}
W (11294) httpd_txrx: httpd_sock_err: error in recv : 104
I (11454) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 27.9 C, Hum: 53.9 %, Lux: 206
I (11454) NETWORK_TASK: =======================================================
I (11454) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (11454) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (11464) NETWORK_TASK:   -> Timestamp   : 10960 ms
I (11474) NETWORK_TASK:   -> Temperature : 27.90 degC
I (11474) NETWORK_TASK:   -> Humidity    : 53.90 %
I (11484) NETWORK_TASK:   -> Light Lux   : 206 lux
I (11484) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (11494) NETWORK_TASK: =======================================================
I (11494) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (12964) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 28.6 C, Hum: 62.5 %, Lux: 563
I (12964) NETWORK_TASK: =======================================================
I (12964) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (12964) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (12974) NETWORK_TASK:   -> Timestamp   : 12470 ms
I (12984) NETWORK_TASK:   -> Temperature : 28.60 degC
I (12984) NETWORK_TASK:   -> Humidity    : 62.50 %
I (12994) NETWORK_TASK:   -> Light Lux   : 563 lux
I (12994) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (13004) NETWORK_TASK: =======================================================
I (13004) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (14474) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 28.5 C, Hum: 65.4 %, Lux: 438
I (14474) NETWORK_TASK: =======================================================
I (14474) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (14474) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (14484) NETWORK_TASK:   -> Timestamp   : 13980 ms
I (14494) NETWORK_TASK:   -> Temperature : 28.50 degC
I (14494) NETWORK_TASK:   -> Humidity    : 65.40 %
I (14504) NETWORK_TASK:   -> Light Lux   : 438 lux
I (14504) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (14514) NETWORK_TASK: =======================================================
I (14514) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (15984) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 33.2 C, Hum: 63.8 %, Lux: 255
I (15984) NETWORK_TASK: =======================================================
I (15984) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (15984) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (15994) NETWORK_TASK:   -> Timestamp   : 15490 ms
I (16004) NETWORK_TASK:   -> Temperature : 33.20 degC
I (16004) NETWORK_TASK:   -> Humidity    : 63.80 %
I (16014) NETWORK_TASK:   -> Light Lux   : 255 lux
I (16014) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (16024) NETWORK_TASK: =======================================================
I (16024) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (16604) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (16604) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (16614) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":33.20,"humidity":63.80,"light_lux":255,"timestamp_ms":15490}
I (16644) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (16644) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (16654) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":33.20,"humidity":63.80,"light_lux":255,"timestamp_ms":15490}
I (17494) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 29.1 C, Hum: 69.9 %, Lux: 562
I (17494) NETWORK_TASK: =======================================================
I (17494) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (17494) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (17504) NETWORK_TASK:   -> Timestamp   : 17000 ms
I (17514) NETWORK_TASK:   -> Temperature : 29.10 degC
I (17514) NETWORK_TASK:   -> Humidity    : 69.90 %
I (17524) NETWORK_TASK:   -> Light Lux   : 562 lux
I (17524) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (17534) NETWORK_TASK: =======================================================
I (17534) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (18274) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (18274) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (18284) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":29.10,"humidity":69.90,"light_lux":562,"timestamp_ms":17000}
I (19004) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 25.4 C, Hum: 58.2 %, Lux: 321
I (19004) NETWORK_TASK: =======================================================
I (19004) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (19004) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (19014) NETWORK_TASK:   -> Timestamp   : 18510 ms
I (19024) NETWORK_TASK:   -> Temperature : 25.40 degC
I (19024) NETWORK_TASK:   -> Humidity    : 58.20 %
I (19034) NETWORK_TASK:   -> Light Lux   : 321 lux
I (19034) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (19044) NETWORK_TASK: =======================================================
I (19044) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (20264) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (20274) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (20274) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":25.40,"humidity":58.20,"light_lux":321,"timestamp_ms":18510}
I (20514) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 27.3 C, Hum: 50.4 %, Lux: 345
I (20514) NETWORK_TASK: =======================================================
I (20514) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (20514) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (20524) NETWORK_TASK:   -> Timestamp   : 20020 ms
I (20534) NETWORK_TASK:   -> Temperature : 27.30 degC
I (20534) NETWORK_TASK:   -> Humidity    : 50.40 %
I (20544) NETWORK_TASK:   -> Light Lux   : 345 lux
I (20544) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (20554) NETWORK_TASK: =======================================================
I (20554) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (22024) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 26.9 C, Hum: 68.3 %, Lux: 224
I (22024) NETWORK_TASK: =======================================================
I (22024) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (22024) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (22034) NETWORK_TASK:   -> Timestamp   : 21530 ms
I (22044) NETWORK_TASK:   -> Temperature : 26.90 degC
I (22044) NETWORK_TASK:   -> Humidity    : 68.30 %
I (22054) NETWORK_TASK:   -> Light Lux   : 224 lux
I (22054) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (22064) NETWORK_TASK: =======================================================
I (22064) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (22274) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (22284) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (22284) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":26.90,"humidity":68.30,"light_lux":224,"timestamp_ms":21530}
I (23534) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 28.4 C, Hum: 50.6 %, Lux: 428
I (23534) NETWORK_TASK: =======================================================
I (23534) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (23534) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (23544) NETWORK_TASK:   -> Timestamp   : 23040 ms
I (23554) NETWORK_TASK:   -> Temperature : 28.40 degC
I (23554) NETWORK_TASK:   -> Humidity    : 50.60 %
I (23564) NETWORK_TASK:   -> Light Lux   : 428 lux
I (23564) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (23574) NETWORK_TASK: =======================================================
I (23574) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (24274) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (24274) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (24284) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":28.40,"humidity":50.60,"light_lux":428,"timestamp_ms":23040}
I (25044) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 34.4 C, Hum: 63.6 %, Lux: 609
I (25044) NETWORK_TASK: =======================================================
I (25044) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (25044) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (25054) NETWORK_TASK:   -> Timestamp   : 24550 ms
I (25064) NETWORK_TASK:   -> Temperature : 34.40 degC
I (25064) NETWORK_TASK:   -> Humidity    : 63.60 %
I (25074) NETWORK_TASK:   -> Light Lux   : 609 lux
I (25074) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (25084) NETWORK_TASK: =======================================================
I (25084) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
I (26274) HTTP_SERVER: [FORENSIC]: GET /api/data requested
I (26274) HTTP_SERVER: [FORENSIC]: Mutex acquired & released for /api/data
I (26274) HTTP_SERVER: [FORENSIC]: Response sent: {"temperature":34.40,"humidity":63.60,"light_lux":609,"timestamp_ms":24550}
I (26554) SENSOR_TASK: [SENSOR TASK]: Pushing -> Temp: 33.8 C, Hum: 60.9 %, Lux: 457
I (26554) NETWORK_TASK: =======================================================
I (26554) FORENSIC_STACK:   -> SensorTask Stack Remaining: 1152 words (1152 bytes)
I (26554) NETWORK_TASK: [NETWORK TASK]: Data Received from Queue!
I (26564) NETWORK_TASK:   -> Timestamp   : 26060 ms
I (26574) NETWORK_TASK:   -> Temperature : 33.80 degC
I (26574) NETWORK_TASK:   -> Humidity    : 60.90 %
I (26584) NETWORK_TASK:   -> Light Lux   : 457 lux
I (26584) NETWORK_TASK: [NETWORK TASK]: g_latest_data updated (Mutex OK)
I (26594) NETWORK_TASK: =======================================================
I (26594) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 2220 words (2220 bytes)
```

---

## 09-Labsheet-06-5-Proximity-Attendance-System
## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

### 5.1 ตารางบันทึกการเช็กชื่อผ่าน RF Proximity

| ลำดับที่ | ชื่อสมาร์ตโฟน / MAC Address | ระดับ RSSI (dBm) | ระยะทางประเมิน (Near/Far) | ผลการลงชื่อ (Passed/Rejected) |
| :------: | :-------------------------- | :--------------: | :-----------------------: | :---------------------------: |
|  **1**   | E6:58:40:30:9F:CD           |     -26 dBm      |       NEAR (Valid)        |            PASSED             |
|  **2**   | BC:09:1B:AB:EA:37           |     -38 dBm      |       NEAR (Valid)        |            PASSED             |

---
#### Webapp
<img width="894" height="1829" alt="278135" src="https://github.com/user-attachments/assets/aa92bb1d-a8aa-4439-aa1c-9fecbe471741" />

---
## 6. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การใช้ **RF Signal Proximity (RSSI)** ร่วมกับ **HTTP Web Server** บน ESP32 แก้ปัญหาการฝากเช็กชื่อแทนกันในห้องเรียนได้อย่างไร?
	**ตอบ:**  ระบบนี้ใช้ความแรงของสัญญาณวิทยุ (RSSI) เป็นตัวชี้วัดระยะห่างทางกายภาพ (Physical Proximity) ของอุปกรณ์ เมื่อนักศึกษากดปุ่มเช็กชื่อผ่าน Web Server ตัวบอร์ด ESP32 จะดึงค่า MAC Address ของเครื่องที่กดปุ่มไปเทียบกับค่า RSSI แบบเรียลไทม์ ดังนั้น แม้จะมีการส่งลิงก์ฝากเพื่อนกดเช็กชื่อจากนอกห้องเรียน หรือเพื่อนพยายามเอาสมาร์ทโฟนหลายเครื่องมากดให้กัน ระบบก็จะปฏิเสธการเช็กชื่อ (Rejected) หากตัวเครื่องไม่ได้อยู่ในรัศมีที่กำหนด ทำให้ต้องนำอุปกรณ์ของตนเองมาอยู่ในพื้นที่เรียนจริงเท่านั้น

2. เหตุใดระดับเกณฑ์ RSSI ที่ `-55 dBm` จึงเหมาะสมสำหรับการระบุตำแหน่งอุปกรณ์ให้อยู่ภายในรัศมีโต๊ะปฏิบัติการ?
	**ตอบ:**  ค่าความแรงสัญญาณ (RSSI) ที่ระดับ -55 dBm ถือเป็นสัญญาณที่แรงมาก ซึ่งในทางปฏิบัติมักจะหมายถึงอุปกรณ์รับส่งสัญญาณอยู่ห่างกันในระยะใกล้ชิด (ประมาณ 1-3 เมตร ขึ้นอยู่กับสภาพแวดล้อม) การตั้งเกณฑ์ไว้ที่ระดับนี้จึงเป็นการบีบรัศมีให้ครอบคลุมเพียงแค่บริเวณโต๊ะปฏิบัติการหรือโซนหน้าห้องเรียน ป้องกันไม่ให้นักศึกษาที่ยืนอยู่หน้าประตูห้อง แอบอยู่ริมระเบียง หรืออยู่ไกลออกไป สามารถกดเช็กชื่อได้สำเร็จ

3. หากต้องการต่อยอดมินิโปรเจกต์นี้ในอนาคต ให้สามารถบันทึกข้อมูลการเข้าเรียนลงระบบ Cloud (เช่น Google Sheets หรือ Firebase) จะต้องเพิ่มส่วนเชื่อมต่อใดบ้าง?
	**ตอบ:**  หากต้องการต่อยอดระบบให้บันทึกขึ้น Cloud จะต้องเพิ่มส่วนประกอบหลัก 3 ส่วน ได้แก่:
	* **การปรับโหมด Wi-Fi (Network Topology):** ต้องเปลี่ยนหรือเพิ่มโหมดจาก SoftAP เดี่ยวๆ ให้เป็นโหมด Station (STA) เพื่อให้บอร์ด ESP32 สามารถเชื่อมต่อกับอินเทอร์เน็ตของมหาวิทยาลัยหรือฮอตสปอตได้
    * **การเพิ่ม HTTP/HTTPS Client:** ต้องเขียนโค้ดฝั่ง ESP32 ให้ทำหน้าที่เป็น Client (ผู้ส่งคำร้อง) เพื่อแพ็กข้อมูล MAC Address และ Timestamp ส่งออกไปเป็น HTTP POST Request
    * **การจัดการด้านความปลอดภัย (Security & API):** ต้องนำเข้าใบรับรองความปลอดภัย (TLS/SSL Certificates) เพื่อให้สามารถเชื่อมต่อกับบริการ Cloud อย่าง Firebase หรือ Google Apps Script ได้อย่างปลอดภัย

Log
```text
entry 0x40080638
--- 0x40080638: call_start_cpu0 at C:/Users/Thanu/esp/v5.5.1/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v5.5.1 2nd stage bootloader
I (29) boot: compile time Aug 13 2026 14:36:17
I (29) boot: Multicore bootloader
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
I (81) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=1c198h (115096) map
I (127) esp_image: segment 1: paddr=0002c1c0 vaddr=3ffb0000 size=03e58h ( 15960) load
I (133) esp_image: segment 2: paddr=00030020 vaddr=400d0020 size=8ea24h (584228) map
I (333) esp_image: segment 3: paddr=000bea4c vaddr=3ffb3e58 size=00094h (   148) load
I (334) esp_image: segment 4: paddr=000beae8 vaddr=40080000 size=17f8ch ( 98188) load
I (375) esp_image: segment 5: paddr=000d6a7c vaddr=50000000 size=00020h (    32) load
I (387) boot: Loaded app from partition at offset 0x10000
I (387) boot: Disabling RNG early entropy source...
I (398) cpu_start: Multicore app
I (406) cpu_start: Pro cpu start user code
I (406) cpu_start: cpu freq: 160000000 Hz
I (406) app_init: Application information:
I (406) app_init: Project name:     proximity_attendance
I (411) app_init: App version:      029da6d-dirty
I (416) app_init: Compile time:     Aug 13 2026 14:35:50
I (421) app_init: ELF file SHA256:  5ce7d7192...
I (425) app_init: ESP-IDF:          v5.5.1
I (429) efuse_init: Min chip rev:     v0.0
I (433) efuse_init: Max chip rev:     v3.99 
I (437) efuse_init: Chip rev:         v3.1
I (441) heap_init: Initializing. RAM available for dynamic allocation:
I (447) heap_init: At 3FFAE6E0 len 00001920 (6 KiB): DRAM
I (452) heap_init: At 3FFB8118 len 00027EE8 (159 KiB): DRAM
I (457) heap_init: At 3FFE0440 len 00003AE0 (14 KiB): D/IRAM
I (463) heap_init: At 3FFE4350 len 0001BCB0 (111 KiB): D/IRAM
I (468) heap_init: At 40097F8C len 00008074 (32 KiB): IRAM
I (475) spi_flash: detected chip: generic
I (477) spi_flash: flash io: dio
W (480) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (493) main_task: Started on CPU0
I (503) main_task: Calling app_main()
I (543) wifi:wifi driver task: 3ffc00f0, prio:23, stack:6656, core=0
I (563) wifi:wifi firmware version: 14da9b7
I (563) wifi:wifi certification version: v7.0
I (563) wifi:config NVS flash: enabled
I (563) wifi:config nano formatting: disabled
I (563) wifi:Init data frame dynamic rx buffer num: 32
I (573) wifi:Init static rx mgmt buffer num: 5
I (573) wifi:Init management short buffer num: 32
I (573) wifi:Init dynamic tx buffer num: 32
I (583) wifi:Init static rx buffer size: 1600
I (583) wifi:Init static rx buffer num: 10
I (593) wifi:Init dynamic rx buffer num: 32
I (593) wifi_init: rx ba win: 6
I (593) wifi_init: accept mbox: 6
I (603) wifi_init: tcpip mbox: 32
I (603) wifi_init: udp mbox: 6
I (603) wifi_init: tcp mbox: 6
I (603) wifi_init: tcp tx win: 5760
I (613) wifi_init: tcp rx win: 5760
I (613) wifi_init: tcp mss: 1440
I (613) wifi_init: WiFi IRAM OP enabled
I (623) wifi_init: WiFi RX IRAM OP enabled
I (903) phy_init: phy_version 4861,b71b5ad,Aug  5 2025,11:16:06
I (983) wifi:mode : softAP (14:33:5c:0e:94:45)
I (993) wifi:Total power save buffer number: 16
I (993) wifi:Init max length of beacon: 752/752
I (993) wifi:Init max length of beacon: 752/752
I (993) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1003) SMART_ATTENDANCE: [SERVER]: Attendance Web Server Started at http://192.168.4.1
I (1013) SMART_ATTENDANCE: =======================================================
I (1013) SMART_ATTENDANCE:  Smart Classroom Proximity Attendance System Ready!
I (1023) SMART_ATTENDANCE:  Connect Wi-Fi: CLASSROOM_ATTENDANCE_AP_0085 (Pass: 12345678)
I (1033) SMART_ATTENDANCE:  Open Browser  : http://192.168.4.1
I (1033) SMART_ATTENDANCE: =======================================================
I (1043) main_task: Returned from app_main()
I (12433) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (12433) wifi:station: e6:58:40:30:9f:cd join, AID=1, bgn, 20
I (12483) SMART_ATTENDANCE: 🎉 [PROXIMITY DETECTED]: Device E6:58:40:30:9F:CD connected to Attendance AP!
I (12483) wifi:<ba-add>idx:2 (ifx:1, e6:58:40:30:9f:cd), tid:0, ssn:0, winSize:64
I (12743) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (13013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
I (13933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (14513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
I (16013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
I (17513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
I (19013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
W (19903) httpd_uri: httpd_uri: URI '/api/data' not found
W (19973) httpd_uri: httpd_uri: URI '/favicon.ico' not found
I (19993) SMART_ATTENDANCE: [HTTP]: GET / requested
I (20513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
W (21883) httpd_uri: httpd_uri: URI '/api/data' not found
I (21903) SMART_ATTENDANCE: [HTTP]: GET / requested
I (22013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
I (23513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
W (23903) httpd_uri: httpd_uri: URI '/api/data' not found
I (23923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (25013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
W (25893) httpd_uri: httpd_uri: URI '/api/data' not found
I (25923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (26513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
W (27903) httpd_uri: httpd_uri: URI '/api/data' not found
I (27933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (28013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
I (29513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
W (29893) httpd_uri: httpd_uri: URI '/api/data' not found
I (29903) SMART_ATTENDANCE: [HTTP]: GET / requested
I (31013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-24 dBm
W (31893) httpd_uri: httpd_uri: URI '/api/data' not found
I (31913) SMART_ATTENDANCE: [HTTP]: GET / requested
I (32513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-25 dBm
W (33893) httpd_uri: httpd_uri: URI '/api/data' not found
I (33903) SMART_ATTENDANCE: [HTTP]: GET / requested
I (34013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (35513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (35893) httpd_uri: httpd_uri: URI '/api/data' not found
I (35913) SMART_ATTENDANCE: [HTTP]: GET / requested
I (37013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (37893) httpd_uri: httpd_uri: URI '/api/data' not found
I (37913) SMART_ATTENDANCE: [HTTP]: GET / requested
I (38513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (39893) httpd_uri: httpd_uri: URI '/api/data' not found
I (39913) SMART_ATTENDANCE: [HTTP]: GET / requested
I (40013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (41513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (41893) httpd_uri: httpd_uri: URI '/api/data' not found
I (41923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (43013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (43913) httpd_uri: httpd_uri: URI '/api/data' not found
I (43933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (44513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (45903) httpd_uri: httpd_uri: URI '/api/data' not found
I (45923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (46013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (47513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (47893) httpd_uri: httpd_uri: URI '/api/data' not found
I (47913) SMART_ATTENDANCE: [HTTP]: GET / requested
I (49013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (49903) httpd_uri: httpd_uri: URI '/api/data' not found
I (49933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (50513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (51903) httpd_uri: httpd_uri: URI '/api/data' not found
I (51933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (52013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (53513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (53893) httpd_uri: httpd_uri: URI '/api/data' not found
I (53923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (55013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (55913) httpd_uri: httpd_uri: URI '/api/data' not found
I (55933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (56513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (57913) httpd_uri: httpd_uri: URI '/api/data' not found
I (57933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (58013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (59513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (59903) httpd_uri: httpd_uri: URI '/api/data' not found
I (59923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (61013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (61893) httpd_uri: httpd_uri: URI '/api/data' not found
I (61923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (62513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (63903) httpd_uri: httpd_uri: URI '/api/data' not found
I (63933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (64013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (65513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
W (65913) httpd_uri: httpd_uri: URI '/api/data' not found
I (65933) SMART_ATTENDANCE: [HTTP]: GET / requested
I (67013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (67743) SMART_ATTENDANCE: [HTTP]: GET / requested
W (67833) httpd_uri: httpd_uri: URI '/favicon.ico' not found
I (67853) SMART_ATTENDANCE: [HTTP]: GET / requested
I (68513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (68813) SMART_ATTENDANCE: [HTTP]: GET / requested
W (68873) httpd_uri: httpd_uri: URI '/favicon.ico' not found
I (68923) SMART_ATTENDANCE: [HTTP]: GET / requested
I (70013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (71513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (71973) SMART_ATTENDANCE: [HTTP]: POST /checkin received
W (72023) httpd_uri: httpd_uri: URI '/favicon.ico' not found
I (72043) SMART_ATTENDANCE: [HTTP]: GET / requested
I (73013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (74513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-29 dBm
I (76013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (77513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (79013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (80513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (82013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (83513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (85013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (86513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (88013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (89513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (91013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (92513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (94013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (95513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (97013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (98513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (100013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (101513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (103013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-33 dBm
I (104513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (106013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (107513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (109013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (110513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (112013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (113513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (115013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (116513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (118013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (119513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (121013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (122513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (124013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (125513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (127013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (128513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (130013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (131513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (133013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (134513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-32 dBm
I (136013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-31 dBm
I (137513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-29 dBm
I (139013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-29 dBm
I (140513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-27 dBm
I (142013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (143513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-26 dBm
I (145013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-27 dBm
I (146513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-27 dBm
I (148013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-31 dBm
I (149513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-31 dBm
I (151013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-31 dBm
I (151863) SMART_ATTENDANCE: [HTTP]: GET / requested
W (151973) httpd_uri: httpd_uri: URI '/favicon.ico' not found
I (152003) SMART_ATTENDANCE: [HTTP]: GET / requested
I (152513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-34 dBm
I (154013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-35 dBm
I (155513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-35 dBm
I (157013) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-31 dBm
I (158513) SMART_ATTENDANCE: [PROXIMITY SCAN]: STA[0] MAC=E6:58:40:30:9F:CD RSSI=-31 dBm
```

---
