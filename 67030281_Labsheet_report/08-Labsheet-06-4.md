## 7. ตารางบันทึกผลการทดลอง (Experiment Results)

### 7.1 บันทึกข้อมูลจาก Dashboard

| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :------: | :--------------: | :----------: | :-------: | :------------: |
|  **1**   |  28.5                |    65.2          |    450       |     12040           |
|  **2**   |   28.7               |   64.8           |  455         |   14045             |
|  **3**   |     28.6             |    65.0          |    448       |  16050              |

### 7.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response จาก Browser:

```json
{ "temperature": 28.6,"humidity": 65.0,"light_lux": 448,"uptime_ms": 16050 }
```

---

## 8. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
```
ป้องกันปัญหาข้อมูลถูกอ่านในขณะที่กำลังถูกเขียนอัปเดตครึ่งๆ กลางๆ (Data Corruption / Race Condition)
```

2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?

```
รันอยู่บน FreeRTOS Task แยกต่างหากที่ถูกสร้างขึ้นโดยไลบรารี HTTP Server ของ ESP-IDF ไม่ใช่ Task หลักของเรา
```

3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
```
ข้อดี: โค้ดง่าย ไม่ต้องเขียนโค้ด JS ฝั่ง client เพิ่มเติม

ข้อเสีย: หน้าเว็บจะกระพริบ (Reload ทั้งหน้า) ทุกๆ 2 วินาที และเปลืองทรัพยากรการโหลดมากกว่าการใช้ AJAX/Fetch อัปเดตเฉพาะจุด
```
