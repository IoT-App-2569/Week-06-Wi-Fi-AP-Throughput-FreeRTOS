# ใบงานที่ 6.1: การคอนฟิก ESP32 SoftAP และการสกัด Forensic Log ข้อมูล Client (Wi-Fi Access Point Mode)

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

| อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android) | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ (ถ้าทราบ) |
| :--- | :--- | :---: | :---: |
| **อุปกรณ์ที่ 1 (iPhone 13)** | 5A:12:8E:B4:9C:3A | 1 | 192.168.4.2 |
| **อุปกรณ์ที่ 2 (Samsung Galaxy S22)** | DA:A1:19:63:F4:71 | 2 | 192.168.4.3 |

### 6.2 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log)

```text
I (516) main_task: Calling app_main()
I (516) LAB_SOFTAP: [FORENSIC]: Call nvs_flash_init()
I (556) LAB_SOFTAP: [FORENSIC]: Call esp_netif_init()
I (556) LAB_SOFTAP: [FORENSIC]: Call esp_event_loop_create_default()
I (556) LAB_SOFTAP: [FORENSIC]: Call esp_netif_create_default_wifi_ap()
I (566) LAB_SOFTAP: [FORENSIC]: SoftAP Interface created at 0x3ffbf360 (Default IP: 192.168.4.1)
I (576) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_init(&cfg)
I (586) wifi:wifi driver task: 3ffc1ae4, prio:23, stack:6656, core=0
I (606) wifi:wifi firmware version: e12a754
I (606) wifi:wifi certification version: v7.0
I (666) LAB_SOFTAP: [FORENSIC]: Call esp_event_handler_instance_register(WIFI_EVENT)
I (676) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_AP)
I (686) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_AP, &wifi_config)
I (696) LAB_SOFTAP: [FORENSIC]: Call esp_wifi_start()
I (766) wifi:mode : softAP (94:b5:55:f2:60:0d)
I (776) LAB_SOFTAP: ==================================================================
I (786) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (796) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "ESP32_AP_0302", Channel: 1
I (806) LAB_SOFTAP: ==================================================================
I (14520) wifi:new:<1,0>, old:<1,0>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (14530) wifi:station: 5a:12:8e:b4:9c:3a join, AID=1, bgn, 20
I (14540) LAB_SOFTAP: =======================================================
I (14540) LAB_SOFTAP: [FORENSIC EVENT]: WIFI_EVENT_AP_STACONNECTED received!
I (14550) LAB_SOFTAP:   -> Client MAC Address : 5A:12:8E:B4:9C:3A
I (14560) LAB_SOFTAP:   -> Assigned AID       : 1
I (14560) LAB_SOFTAP: =======================================================
I (15210) esp_netif_lwip: DHCPS: Assigned IP 192.168.4.2 to 5a:12:8e:b4:9c:3a
I (28430) wifi:station: da:a1:19:63:f4:71 join, AID=2, bgn, 20
I (28440) LAB_SOFTAP: =======================================================
I (28440) LAB_SOFTAP: [FORENSIC EVENT]: WIFI_EVENT_AP_STACONNECTED received!
I (28450) LAB_SOFTAP:   -> Client MAC Address : DA:A1:19:63:F4:71
I (28450) LAB_SOFTAP:   -> Assigned AID       : 2
I (28460) LAB_SOFTAP: =======================================================
I (29120) esp_netif_lwip: DHCPS: Assigned IP 192.168.4.3 to da:a1:19:63:f4:71
```

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?
> **คำตอบ:** 
> ค่า `192.168.4.1` เป็นค่า Default Gateway ของ Network Interface (`esp_netif`) ในโหมด SoftAP ของเฟรมเวิร์ก ESP-IDF ซึ่งถูกกำหนดไว้เพื่อหลีกเลี่ยงปัญหา IP ชนกัน (IP Address Conflict) กับเครือข่าย Wi-Fi ตามบ้านหรือสำนักงานส่วนใหญ่ที่มักใช้ Subnet วง `192.168.1.0/24` หรือ `192.168.0.0/24` 
> 
> ตัวบริการ DHCP Server (`dhcps`) บน ESP32 จะเริ่มแจกจ่ายหมายเลข IP Address ให้แก่ลูกข่ายเครื่องแรกที่เชื่อมต่อสำเร็จเริ่มที่หมายเลข **`192.168.4.2`** และจะเพิ่มลำดับขึ้นไปเรื่อยๆ (`.3`, `.4`, ...) ตามการจองในตาราง DHCP Lease

2. สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?
> **คำตอบ:** 
> สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` เป็นอาร์เรย์ `uint8_t mac[6]` ที่เก็บหมายเลข Hardware MAC Address ของสเตชันที่เพิ่งเชื่อมต่อเข้ามา สามารถนำไปประยุกต์ใช้ทำ **MAC Address Filtering** ได้โดย:
> 1. สร้างตาราง Whitelist ในโค้ดเพื่อเก็บรายการ MAC Address ของอุปกรณ์ที่ได้รับอนุญาต
> 2. ดักจับ Event `WIFI_EVENT_AP_STACONNECTED` ภายใน Event Handler แล้วนำค่า `event->mac` มาเปรียบเทียบกับตาราง Whitelist
> 3. หากพบว่าเป็นอุปกรณ์ที่ไม่อยู่ในรายการที่อนุญาต ระบบสามารถเรียกฟังก์ชัน `esp_wifi_deauth_sta(event->aid)` เพื่อส่งเฟรม Deauthentication ไปตัดการเชื่อมต่อลูกข่ายเครื่องนั้นในระดับ Link Layer ทันที

3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?
> **คำตอบ:** 
> ในระดับสัญญาณวิทยุตามมาตรฐาน IEEE 802.11 ตัว ESP32 SoftAP จะปฏิเสธการเชื่อมต่อใน **Phase 3 (Association Phase)**:
> 1. ลูกข่ายเครื่องที่ 5 จะผ่าน Phase 2 (Authentication) ได้ปกติ แต่เมื่อส่งเฟรม **802.11 Association Request** มายัง ESP32 SoftAP
> 2. ไดรเวอร์ของ ESP32 จะตรวจพบว่าจำนวนสเตชันที่ลงทะเบียนในหน่วยความจำเต็มตามที่กำหนดไว้ใน `.max_connection = 4` แล้ว
> 3. ESP32 จะตอบกลับด้วยเฟรม **802.11 Association Response** ที่มี Status Code เป็น `17` (*Association denied because AP is unable to handle additional associated stations*)
> 4. ส่งผลให้ลูกข่ายเครื่องที่ 5 หลุดการเชื่อมต่อด้วย Disconnect Reason Code **`WIFI_REASON_ASSOC_TOOMANY`** (Code 5 หรือ 17) และหน้าจอของอุปกรณ์จะแจ้งเตือนว่าไม่สามารถเชื่อมต่อเครือข่ายได้
