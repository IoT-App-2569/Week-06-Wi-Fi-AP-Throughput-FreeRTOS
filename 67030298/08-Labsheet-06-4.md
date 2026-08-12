## 7. ตารางบันทึกผลการทดลอง (Experiment Results)

### 7.1 บันทึกข้อมูลจาก Dashboard

| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :------: | :--------------: | :----------: | :-------: | :------------: |
|  **1**   |       30.3       |     66.9     |    446    |      24880     |
|  **2**   |       26.7       |     64.7     |    437    |      27900     |
|  **3**   |       32.0       |     59.4     |    318    |      36970     |

<img width="670" height="635" alt="33" src="https://github.com/user-attachments/assets/8d9ea1f6-92a6-45a4-845d-4fbb9b81a388" />

<img width="727" height="637" alt="34" src="https://github.com/user-attachments/assets/1c47e4b9-a0df-4c05-b5cd-a979e0a6a196" />

<img width="722" height="676" alt="35" src="https://github.com/user-attachments/assets/57314211-bdea-4539-b1e7-f6e30fe98251" />

### 7.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response จาก Browser:

```json
{"temperature":33.20,"humidity":63.60,"light_lux":486,"timestamp_ms":46030}
```

<img width="617" height="152" alt="36" src="https://github.com/user-attachments/assets/ad510af9-564a-4ad4-a607-4b1c4e781efc" />

---

## 8. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
> การใช้ Mutex จะช่วยป้องกันปัญหา Race Condition ได้ หากเราไม่ใช้งานอาจทำให้เกิดการอ่านข้อมูลในขณะที่กำลังเขียนข้อมูลลงไปอยู่ (Torn Read) ซึ่งจะส่งผลให้ข้อมูลที่ดึงมาผิดเพี้ยนหรือไม่สมบูรณ์

2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?
> ตัว `esp_http_server` จะทำการสร้าง Thread (Task) ของตัวเองแยกออกมาต่างหาก โดยจะไม่ได้รันอยู่บน Thread เดียวกันกับ `vNetworkTask` หรือ `vSensorTask` ที่เราสร้างไว้

3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
> วิธีนี้มีข้อดีตรงที่สามารถใช้งานได้ง่ายและไม่ต้องเขียนโค้ด JavaScript เพิ่มเติม แต่มีข้อเสียคือเบราว์เซอร์จะทำการโหลดเว็บใหม่ทั้งหมดทั้งหน้า ทำให้หน้าจอกระพริบและสิ้นเปลืองข้อมูลอินเทอร์เน็ตมากกว่า ซึ่งแตกต่างจากการใช้ `fetch()` ที่ดึงมาเฉพาะแค่ตัวข้อมูล (JSON) เพื่อนำมาอัพเดต จึงทำให้หน้าเว็บแสดงผลได้เนียนตาและรวดเร็วกว่า
