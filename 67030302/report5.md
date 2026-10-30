# ใบงานที่ 6.5: 📋 Assignment Project — ระบบเช็กชื่อและยืนยันตัวตนอัจฉริยะด้วย RF Proximity & Sensor Fusion

## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

### 5.1 ตารางบันทึกการเช็กชื่อผ่าน RF Proximity

| ลำดับที่ | ชื่อสมาร์ตโฟน / MAC Address | ระดับ RSSI (dBm) | ระยะทางประเมิน (Near/Far) | ผลการลงชื่อ (Passed/Rejected) |
| :---: | :--- | :---: | :---: | :---: |
| **1** | iPhone 13 (MAC: 5A:12:8E:B4:9C:3A) | -48 dBm | Near (ระยะประมาณ 1.0 เมตร) | Passed (ลงชื่อเข้าชั้นเรียนสำเร็จ) |
| **2** | Samsung Galaxy S22 (MAC: DA:A1:19:63:F4:71) | -76 dBm | Far (ระยะประมาณ 6.5 เมตร นอกโต๊ะแล็บ) | Rejected (ระยะห่างเกินเกณฑ์ที่กำหนด) |

### 5.2 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log)

```text
I (516) main_task: Calling app_main()
I (516) SMART_ATTENDANCE: Initializing NVS, Netif & SoftAP Mode...
I (620) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (630) SMART_ATTENDANCE: Attendance Web Server Started at http://192.168.4.1
I (640) SMART_ATTENDANCE: SoftAP Started. SSID: "CLASSROOM_ATTENDANCE_AP", Threshold: -60 dBm
I (14520) wifi:station: 5a:12:8e:b4:9c:3a join, AID=1, bgn, 20
I (14530) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (14540) SMART_ATTENDANCE:   -> MAC: 5A:12:8E:B4:9C:3A, Measured RSSI: -48 dBm
I (14550) SMART_ATTENDANCE:   -> Proximity Decision: RSSI (-48 dBm) >= Threshold (-60 dBm) -> STATUS: NEAR (Valid)
I (15890) httpd: httpd_accept_conn: new connection on socket 54
I (15900) SMART_ATTENDANCE: [HTTP REQUEST]: Serving Attendance Dashboard to 192.168.4.2
I (18210) SMART_ATTENDANCE: [CHECKIN CONFIRMED]: Student 5A:12:8E:B4:9C:3A checked in successfully! (Timestamp: 120s)

I (35210) wifi:station: da:a1:19:63:f4:71 join, AID=2, bgn, 20
I (35220) SMART_ATTENDANCE: [PROXIMITY DETECTED]: New student device connected!
I (35230) SMART_ATTENDANCE:   -> MAC: DA:A1:19:63:F4:71, Measured RSSI: -76 dBm
W (35240) SMART_ATTENDANCE:   -> Proximity Decision: RSSI (-76 dBm) < Threshold (-60 dBm) -> STATUS: FAR (Invalid)
W (36450) SMART_ATTENDANCE: [CHECKIN REJECTED]: Student DA:A1:19:63:F4:71 checkin rejected due to out of range signal!
```

---

## 6. คำถามท้ายการทดลอง (Post-Lab Questions)

1. การใช้ **RF Signal Proximity (RSSI)** ร่วมกับ **HTTP Web Server** บน ESP32 แก้ปัญหาการฝากเช็กชื่อแทนกันในห้องเรียนได้อย่างไร?
> **คำตอบ:** 
> ระบบแก้ปัญหาการฝากเช็กชื่อแทนกันได้ด้วยการยืนยันแบบ 2 ปัจจัยคู่ขนาน (Two-Factor Verification):
> 1. **การยืนยันตำแหน่งทางกายภาพจริง (Physical Location Proof ผ่าน RSSI):** ระบบจะยอมรับการกดปุ่มเช็กชื่อก็ต่อเมื่ออุปกรณ์ลูกข่ายมีระดับสัญญาณวิทยุแรงกว่าเกณฑ์ที่กำหนด (RSSI $\ge$ -60 dBm) ซึ่งเป็นเครื่องยืนยันว่าเจ้าของเครื่องต้องนำสมาร์ตโฟนมานั่งอยู่ที่โต๊ะปฏิบัติการจริง ไม่สามารถฝากเพื่อนเช็กชื่อจากนอกห้องหรือจากหอพักได้
> 2. **การผูกตัวตนเข้ากับฮาร์ดแวร์เฉพาะ (Hardware MAC Binding):** ตัว ESP32 ดักจับ MAC Address ของอุปกรณ์ที่เชื่อมต่อเข้ากับ SoftAP โดยตรง ทำให้แต่ละอุปกรณ์มีสิทธิ์กดลงชื่อได้เพียง 1 ครั้ง ไม่สามารถเปิดหลายแท็บบนเบราว์เซอร์เครื่องเดียวกันเพื่อกดเช็กชื่อซ้ำให้เพื่อนได้

2. เหตุใดระดับเกณฑ์ RSSI ที่ `-55 dBm` จึงเหมาะสมสำหรับการระบุตำแหน่งอุปกรณ์ให้อยู่ภายในรัศมีโต๊ะปฏิบัติการ?
> **คำตอบ:** 
> ตามหลักฟิสิกส์การลดทอนสัญญาณคลื่นวิทยุในที่ว่าง (Log-Distance Path Loss Model) สำหรับคลื่นความถี่ 2.4 GHz ในสภาพแวดล้อมภายในอาคาร:
> - กำลังส่งของสมาร์ตโฟนทั่วไปจะให้ค่า RSSI อยู่ที่ประมาณ -40 dBm ถึง -50 dBm ในระยะใกล้มาก (0.5 ถึง 1 เมตร)
> - เมื่อระยะห่างขยายออกไปเป็น 2 ถึง 3 เมตร ค่า RSSI จะลดทอนลงไปอยู่ในช่วง -62 dBm ถึง -70 dBm อย่างรวดเร็ว
> 
> ดังนั้น การกำหนด Threshold ไว้ที่ **`-55 dBm`** จึงเป็นค่าขอบเขต (Spatial Boundary) ที่เหมาะสมอย่างยิ่งในการจำกัดพื้นที่ตรวจจับให้อยู่ในรัศมีรอบโต๊ะปฏิบัติการประมาณ 1.0–1.5 เมตร โดยช่วยป้องกันสัญญาณจากสมาร์ตโฟนของนักศึกษาที่นั่งอยู่โต๊ะข้างเคียง หรือคนที่เดินอยู่นอกห้องไม่ให้สามารถผ่านเงื่อนไขการลงชื่อได้

3. หากต้องการต่อยอดมินิโปรเจกต์นี้ในอนาคต ให้สามารถบันทึกข้อมูลการเข้าเรียนลงระบบ Cloud (เช่น Google Sheets หรือ Firebase) จะต้องเพิ่มส่วนเชื่อมต่อใดบ้าง?
> **คำตอบ:** 
> หากต้องการพัฒนาต่อยอดระบบให้สามารถส่งข้อมูลขึ้นคลาวด์แบบอัตโนมัติ จะต้องเพิ่มเติมส่วนประกอบสถาปัตยกรรมดังนี้:
> 1. **การตั้งค่าโหมด Wi-Fi แบบ Dual Mode (AP+STA Mode):** ปรับคอนฟิกกูเรชันของ ESP32 จาก `WIFI_MODE_AP` ให้เป็น `WIFI_MODE_APSTA` เพื่อให้บอร์ดสามารถทำหน้าที่เป็น SoftAP ปล่อยสัญญาณให้นักศึกษาเชื่อมต่อ และในขณะเดียวกันก็เชื่อมต่อเป็นลูกข่าย (STA) เข้ากับ Wi-Fi ของคณะ/สถาบันเพื่อออกสู่อินเทอร์เน็ตได้พร้อมกัน
> 2. **การติดตั้ง HTTPS / TLS Client Library:** เพิ่มคอมโพเนนต์ `esp_http_client` พร้อมตั้งค่าใบรับรองความปลอดภัย (Root CA Certificate) เพื่อยิงคำร้องขอ HTTPS POST ส่งข้อมูล JSON ไปยัง Google Apps Script Webhook API หรือ Firebase Realtime Database REST API ได้อย่างปลอดภัย
> 3. **ระบบการซิงค์เวลาจริง (SNTP Time Synchronization):** เพิ่มบริการ SNTP Client (Simple Network Time Protocol) เพื่อดึงเวลาสากลที่แท้จริงจาก Time Server มาประทับเวลา (Timestamp) ในบันทึกการเช็กชื่อของนักศึกษาได้อย่างแม่นยำ
