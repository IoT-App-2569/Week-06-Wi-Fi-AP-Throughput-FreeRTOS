## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :--- | :---: | :---: | :---: |
| **`SensorCollectorTask`** | 3072 | 1280 Words (512 Bytes) | ปลอดภัย (Safe) |
| **`NetworkCommTask`** | 4096 | 1536 Words (1024 Bytes) | ปลอดภัย (Safe) |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
```
เพราะมีการจัดการภาวะแย่งชิงข้อมูล (Mutual Exclusion / Critical Section) ในระดับ kernel ป้องกันอาการ Race Condition เวลาหลาย Task เขียนข้อมูลพร้อมกัน
```
2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
```
ช่วยตรวจวัดพื้นที่ว่างเหลือน้อยที่สุดตั้งแต่ Task เริ่มทำงาน เพื่อป้องกันบั๊ก Stack Overflow ในระบบเรียลไทม์
```
3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
```
Queue จะเต็มอย่างรวดเร็ว (Queue Full) หากไม่มีการจัดการที่ดี ระบบจะบล็อกหรือข้อมูลเก่าจะถูกเขียนทับ (Depending on configuration)
```