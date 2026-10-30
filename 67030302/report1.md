# ใบงานที่ 6.1: การคอนฟิก ESP32 SoftAP และการสกัด Forensic Log ข้อมูล Client (Wi-Fi Access Point Mode)

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Client ที่เชื่อมต่อเข้ากับ ESP32 SoftAP

| อุปกรณ์ที่ใช้ทดสอบ (เช่น iPhone/Android) | MAC Address ที่ดักจับได้ | Association ID (AID) | หมายเลข IP Address ที่ได้ (ถ้าทราบ) |
| :--- | :--- | :---: | :---: |
| **อุปกรณ์ที่ 1 (iPhone 13)** | 5A:12:8E:B4:9C:3A | 1 | 192.168.4.2 |
| **อุปกรณ์ที่ 2 (Samsung Galaxy S22)** | DA:A1:19:63:F4:71 | 2 | 192.168.4.3 |

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
