## 6. ตารางบันทึกผลการทดลอง (Experiment Results)
### 6.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

| อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android) | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ (ถ้าทราบ) |
| :--- | :--- | :---: | :---: |
| **อุปกรณ์ที่ 1** |AE:81:89:8D:56:CA |1 |192.168.4.2 |
| **อุปกรณ์ที่ 2** |60:FF:9E:6F:AA:3E |2 |192.168.4.3 |


```c
I (1006) LAB_SOFTAP: ==================================================================
I (1006) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1026) LAB_SOFTAP:   ESP32 SoftAP Running! SSID: "MY_ESP32_AP_215", Channel: 1
I (1036) LAB_SOFTAP: ==================================================================
I (1036) LAB_SOFTAP: [TCP SERVER]: Listening on 192.168.4.1:8080
I (1046) main_task: Returned from app_main()
I (49676) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (49676) wifi:station: ae:81:89:8d:56:ca join, AID=1, bgn, 40U
I (49726) LAB_SOFTAP: =======================================================
I (49726) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (49726) LAB_SOFTAP:   -> Client MAC Address : AE:81:89:8D:56:CA
I (49726) LAB_SOFTAP:   -> Assigned AID       : 1
I (49736) LAB_SOFTAP: =======================================================
I (50076) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (50166) wifi:<ba-add>idx:2 (ifx:1, ae:81:89:8d:56:ca), tid:0, ssn:16, winSize:64
I (268946) wifi:<ba-add>idx:3 (ifx:1, ae:81:89:8d:56:ca), tid:7, ssn:17, winSize:64
I (269446) wifi:<ba-add>idx:4 (ifx:1, ae:81:89:8d:56:ca), tid:6, ssn:16, winSize:64
I (353126) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (353126) wifi:station: 60:ff:9e:6f:aa:3e join, AID=2, bgn, 40U
I (353236) LAB_SOFTAP: =======================================================
I (353236) LAB_SOFTAP: [FORENSIC EVENT]: Client Connected to ESP32 SoftAP!
I (353236) LAB_SOFTAP:   -> Client MAC Address : 60:FF:9E:6F:AA:3E
I (353246) LAB_SOFTAP:   -> Assigned AID       : 2
I (353246) LAB_SOFTAP: =======================================================
I (353486) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3
I (355436) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.3
I (409436) wifi:station: 60:ff:9e:6f:aa:3e leave, AID = 2, reason = 3, bss_flags is 756835, bss:0x3ffb9b68
I (409436) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (409446) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
W (409446) LAB_SOFTAP: =======================================================
W (409456) LAB_SOFTAP: [FORENSIC EVENT]: Client Disconnected from ESP32 SoftAP!
W (409466) LAB_SOFTAP:   -> Client MAC Address : 60:FF:9E:6F:AA:3E
W (409466) LAB_SOFTAP:   -> Released AID       : 2
W (409476) LAB_SOFTAP: =======================================================
```
---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใด IP Address เริ่มต้นของ ESP32 SoftAP จึงเป็น `192.168.4.1` และ DHCP Server บน ESP32 เริ่มแจกจ่าย IP ที่หมายเลขใด?
```
= 192.168.4.1 เป็นค่า default ที่กำหนดไว้ใน ESP-IDF framework โดยในไลบรารี esp_netif ซึ่งเลือกใช้ช่วง IP ในเครือข่ายส่วนตัว private networkตามมาตรฐาน RFC 1918 คือ class C (192.168.x.x)
ซึ่งเป็นย่านที่นิยมใช้กับอุปกรณ์ Router/Access Point ทั่วไป ทาง Espressif กำหนดให้ ESP32 ทำหน้าที่เป็นเกตเวย์ (Gateway) ของเครือข่ายนั้นเอง จึงตั้งตัวเองเป็น .1 ของ subnet เพื่อให้ Client
ทุกตัวที่เชื่อมต่อเข้ามาสามารถอ้างอิงกลับไปยัง ESP32 ในฐานะเกตเวย์ได้ทันที ส่วน DHCP Server บน ESP32 จะเริ่มแจกจ่าย IP ให้ Client ตัวแรกที่หมายเลข 192.168.4.2 เป็นต้นไป
เนื่องจาก .1 ถูกจองไว้ให้ตัว ESP32 เองแล้ว ซึ่งจะเห็นได้จากตัวอย่างในรายงานที่อุปกรณ์ที่ 1 ได้ IP 192.168.4.2 และอุปกรณ์ที่ 2 ได้ 192.168.4.3 ตามลำดับการเชื่อมต่อก่อนหลัง
```
2. สมาชิกตัวแปร `mac` ในโครงสร้าง `wifi_event_ap_staconnected_t` สามารถนำไปประยุกต์ใช้ทำระบบความปลอดภัยขั้นสูง (เช่น MAC Filtering) ได้อย่างไร?
```
= ค่า mac ในโครงสร้างนี้คือ MAC Address เฉพาะตัวของอุปกรณ์ Client ที่เพิ่งเชื่อมต่อเข้ามา ซึ่งสามารถนำไปใช้สร้างระบบความปลอดภัยขั้นสูงได้โดยเมื่อ Event WIFI_EVENT_AP_STACONNECTED ถูกเรียกขึ้น
โปรแกรมสามารถนำค่า mac ที่ได้ไปเปรียบเทียบกับ Whitelist หรือ Blacklist ที่เก็บไว้ล่วงหน้า (เช่นในตัวแปร array, NVS, หรือฐานข้อมูลภายนอก) หากพบว่า MAC Address ไม่ตรงกับรายการที่อนุญาต
ระบบสามารถสั่งตัดการเชื่อมต่อ (deauthenticate) อุปกรณ์นั้นได้ทันทีผ่านฟังก์ชัน esp_wifi_deauth_sta() โดยอ้างอิง AID ของ Client ตัวนั้น วิธีนี้ช่วยป้องกันไม่ให้อุปกรณ์แปลกปลอมที่ไม่ได้รับอนุญาตเข้าถึงเครือข่าย SoftAP ได้
แม้จะรู้รหัสผ่าน Wi-Fi ก็ตาม นอกจากนี้ยังสามารถนำ MAC มาใช้ทำ Logging เพื่อตรวจสอบย้อนหลัง (Forensic) ว่ามีอุปกรณ์ใดเชื่อมต่อเข้ามาบ้างในแต่ละช่วงเวลา
```
3. หากมี Client พยายามเชื่อมต่อเป็นเครื่องที่ 5 (เกินค่า `max_connection = 4`) จะเกิดเหตุการณ์ใดขึ้นในระดับสัญญาณวิทยุ?
```
ในระดับสัญญาณวิทยุ (RF Layer) ESP32 จะยังคงตอบสนองต่อ Beacon Request และ Probe Request ตามปกติ เนื่องจากขั้นตอนการค้นหาเครือข่าย (Scanning) ยังไม่เกี่ยวข้องกับการจำกัดจำนวนการเชื่อมต่อ
แต่เมื่อ Client เครื่องที่ 5 พยายามส่ง Authentication Request และ Association Request เข้ามา ESP32 จะปฏิเสธคำขอในขั้นตอน Association โดยจะส่งเฟรม Association Response กลับไปพร้อม Status Code
ที่ระบุว่าปฏิเสธเนื่องจากทรัพยากรไม่เพียงพอ (เช่น Status Code 17: Association denied because AP is unable to handle additional associated stations) ทำให้ Client
เครื่องนั้นไม่สามารถเข้าสู่สถานะ Associated ได้ และจะไม่ได้รับ AID หรือ IP Address จาก DHCP Server แต่อย่างใด แม้ว่าจะรับรู้สัญญาณ SSID และรหัสผ่านถูกต้องก็ตาม
```
---
