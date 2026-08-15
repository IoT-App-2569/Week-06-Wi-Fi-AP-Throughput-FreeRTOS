# ใบงานที่ 6.4: IoT Sensor Dashboard — แสดงผลค่าเซนเซอร์แบบ Real-Time ผ่าน Web Browser บนมือถือ

## 0. กล่าวนำ (Introduction)

ในใบงาน 6.3 นักศึกษาได้สร้างระบบ FreeRTOS Multi-Tasking ที่ `vSensorTask` อ่านค่าเซนเซอร์ → ส่งผ่าน Queue → `vNetworkTask` รับและ "เตรียม JSON" แต่ข้อมูลยังไม่ได้ออกไปสู่โลกภายนอก

ในใบงานนี้ นักศึกษาจะ**ต่อยอดโค้ด Lab 6-3 โดยตรง** โดยเพิ่ม
1. **ESP32 SoftAP** — ให้มือถือเชื่อมต่อ Wi-Fi ตรงโดยไม่ต้อง Router
2. **HTTP Web Server (`esp_http_server`)** — เปิด Endpoint 2 ตัว
   - `GET /` → หน้า Dashboard HTML Auto-refresh ทุก 2 วินาที
   - `GET /api/data` → ส่งค่า JSON ล่าสุดให้ Browser

---

## 1. วัตถุประสงค์ (Objectives)

1. เชื่อมโยง FreeRTOS Queue Pipeline กับ HTTP Web Server เพื่อส่งข้อมูลออกสู่ Browser จริง
2. ใช้งาน `esp_http_server` component ของ ESP-IDF ในการสร้าง REST API Endpoint บน ESP32
3. ออกแบบ ESP32 ให้ทำงานเป็น **SoftAP + HTTP Server** พร้อมกัน
4. เข้าใจการใช้ `SemaphoreHandle_t` (Mutex) เพื่อป้องกัน Race Condition เมื่อ HTTP Handler และ FreeRTOS Task แชร์ข้อมูลร่วมกัน

---

## 2. อุปกรณ์และซอฟต์แวร์ที่ใช้ในการทดลอง (Equipment & Tools)

1. บอร์ดไมโครคอนโทรลเลอร์ ESP32 จำนวน 1 บอร์ด
2. สายเชื่อมต่อ USB จำนวน 1 เส้น
3. สมาร์ตโฟนหรือ PC (สำหรับเปิด Browser ดู Dashboard)

---

## 3. สถาปัตยกรรมระบบ (System Architecture)

```mermaid
sequenceDiagram
    autonumber
    participant Sens as vSensorTask
    participant Queue as FreeRTOS Queue
    participant Net as vNetworkTask
    participant HTTP as HTTP Server (esp_http_server)
    participant Phone as Browser (มือถือ)

    loop ทุกๆ 1.5 วินาที
        Sens->>Queue: xQueueSend(&sensor_data)
        Queue->>Net: xQueueReceive(&rx_data)
        Net->>Net: Mutex Lock → อัพเดต g_latest_data → Mutex Unlock
    end

    Phone->>HTTP: GET /api/data
    HTTP->>Net: Mutex Lock → อ่าน g_latest_data → Mutex Unlock
    HTTP-->>Phone: JSON: {temp, hum, lux, ts}

    Phone->>HTTP: GET /
    HTTP-->>Phone: HTML Dashboard (Auto-refresh ทุก 2s)
```

---

## 4. แนวคิดสำคัญ: Mutex ป้องกัน Race Condition

```
vNetworkTask                    HTTP GET Handler
─────────────────────────       ─────────────────────────
xSemaphoreTake(mutex)           xSemaphoreTake(mutex)
  g_latest_data = rx_data;         read g_latest_data
xSemaphoreGive(mutex)           xSemaphoreGive(mutex)
```

> [!WARNING]
> หากไม่ใช้ Mutex: HTTP Handler อาจอ่านข้อมูลขณะที่ `vNetworkTask` กำลังเขียนอยู่ ทำให้ได้ค่าที่ไม่สมบูรณ์ (Torn Read)

---

## 5. ซอร์สโค้ดการทดลอง (`main/main.c`)

ดูใน `ESP32_Project/Lab6-4-IoT-Sensor-Dashboard/main/main.c`

---

## 6. ขั้นตอนการทดลอง (Experimental Procedures)

1. Build และ Flash โค้ดลงบอร์ด ESP32
2. เปิด Serial Monitor ดู SSID และยืนยัน `[HTTP SERVER]: Started`
3. ใช้มือถือ **เชื่อมต่อ Wi-Fi ชื่อ `MY_ESP32_SENSOR_AP`** (Password: `12345678`)
4. เปิด Browser บนมือถือ แล้วไปที่ `http://192.168.4.1`
5. ควรเห็นหน้า Dashboard แสดง Temperature / Humidity / Light Lux และ Auto-refresh ทุก 2 วินาที
6. ทดสอบ JSON API โดยเปิด `http://192.168.4.1/api/data` ดู Raw JSON

ตัวอย่างหน้า browser
![](images/253776.jpg)


---

## 7. ตารางบันทึกผลการทดลอง (Experiment Results)

### 7.1 บันทึกข้อมูลจาก Dashboard

| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :------: | :--------------: | :----------: | :-------: | :------------: |
|  **1**   |      25.8        |  69.0        | 380          |   269170            |
|  **2**   |       28.5           |    62.1          |    450       |   271170             |
|  **3**   |         31.7         |    50.8          |    340       |   399010             |

### 7.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response จาก Browser:

```json
{"temperature":31.70,"humidity":50.80,"light_lux":340,"timestamp_ms":399010}
```

---

## 8. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
ตอบ เนื่องจาก vNetworkTask (ทำหน้าที่เขียน) และ HTTP Handler (ทำหน้าที่อ่าน) ทำงานอยู่คนละ Task/Thread กันแบบ Asynchronous การอัปเดตข้อมูลโครงสร้าง sensor_data_t ไม่ใช่การทำงานเชิงอะตอม (Non-atomic operation) หากไม่ใช้ Mutex อาจเกิดปัญหา Race Condition หรือ Torn Read (HTTP Handler อ่านข้อมูลในจังหวะที่ vNetworkTask กำลังเขียนข้อมูลค้างอยู่กลางคัน) ส่งผลให้ข้อมูลที่ส่งไปยัง Browser มีค่าผิดพลาด เพี้ยน หรือโครงสร้าง JSON เสียหายได้ 

2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?
ตอบ ไม่ใช่ Thread เดียวกันครับ ตัว esp_http_server ของ ESP-IDF จะสร้าง FreeRTOS Task แยกเฉพาะของตัวเองชื่อ httpd เพื่อคอยจัดการ socket และประมวลผล Web Request ดังนั้น URI Handler (เช่น dashboard_handler หรือ api_data_handler) จะถูกรันบนบริบทของ Task httpd ไม่ได้รันอยู่บน vSensorTask หรือ vNetworkTask ที่เราสร้างขึ้น

3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
ตอบ ข้อดีของ <meta refresh> เขียนโค้ด HTML เรียบง่าย ไม่จำเป็นต้องเขียน JavaScript รองรับ Browser ยุคเก่าทุกรุ่น

ข้อเสียของ <meta refresh> ทำให้เกิดการกระพริบของหน้าเว็บ (Flickering) ทุก 2 วินาที สิ้นเปลืองการส่งข้อมูล (Overhead สูง) เพราะต้องโหลดโครงสร้าง HTML ทั้งหมดใหม่ทุกรอบ ในขณะที่การใช้ JavaScript fetch() (เหมือนในแลปนี้) จะดึงเฉพาะข้อมูล Raw JSON สั้นๆ มาอัปเดตเฉพาะจุด ทำให้หน้าเว็บแสดงผลได้ลื่นไหล ไม่กระพริบ และประหยัด Bandwidth รวมถึงทรัพยากรของ ESP32 มากกว่า
---

## 9. ความรู้เพิ่มเติม: ESP-IDF `esp_http_server` API

| ฟังก์ชัน                                   | ความหมาย                                     |
| :----------------------------------------- | :------------------------------------------- |
| `httpd_start(&server, &config)`            | เริ่มต้น HTTP Server (เปิด Port 80)          |
| `httpd_register_uri_handler(server, &uri)` | ลงทะเบียน Handler สำหรับ URL path            |
| `httpd_resp_send(req, buf, len)`           | ส่ง Response กลับไปยัง Browser               |
| `httpd_resp_set_type(req, type)`           | กำหนด Content-Type (เช่น `application/json`) |
| `xSemaphoreCreateMutex()`                  | สร้าง Mutex สำหรับป้องกัน Race Condition     |
| `xSemaphoreTake(mutex, ticks)`             | Lock Mutex ก่อนอ่าน/เขียน Shared Data        |
| `xSemaphoreGive(mutex)`                    | Unlock Mutex หลังเสร็จ                       |
