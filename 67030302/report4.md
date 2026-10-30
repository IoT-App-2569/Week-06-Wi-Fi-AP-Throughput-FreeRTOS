# ใบงานที่ 6.4: IoT Sensor Dashboard — แสดงผลค่าเซนเซอร์แบบ Real-Time ผ่าน Web Browser บนมือถือ

## 7. ตารางบันทึกผลการทดลอง (Experiment Results)

### 7.1 บันทึกข้อมูลจาก Dashboard

| ครั้งที่ | Temperature (°C) | Humidity (%) | Light Lux | Timestamp (ms) |
| :------: | :--------------: | :----------: | :-------: | :------------: |
|  **1**   |      27.40       |    58.20     |    412    |     14250      |
|  **2**   |      28.10       |    57.80     |    395    |     16250      |
|  **3**   |      27.90       |    59.10     |    430    |     18250      |

### 7.2 ทดสอบ JSON API (`/api/data`)

บันทึก Raw JSON Response จาก Browser:

```json
{
  "temperature": 27.90,
  "humidity": 59.10,
  "light_lux": 430,
  "timestamp_ms": 18250
}
```

### 7.3 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log)

```text
I (516) main_task: Calling app_main()
I (526) LAB_DASHBOARD: SoftAP Started with SSID: "MY_ESP32_SENSOR_AP", IP: 192.168.4.1
I (536) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (546) LAB_DASHBOARD: [HTTP SERVER]: Starting server on port: '80'
I (556) LAB_DASHBOARD: [HTTP SERVER]: Registering URI handlers ('/' and '/api/data')
I (566) LAB_DASHBOARD: [HTTP SERVER]: Server started successfully!
I (576) LAB_DASHBOARD: Mutex created for g_latest_data protection.
I (14250) LAB_DASHBOARD: [NETWORK TASK]: Queue received data -> Updating g_latest_data under Mutex lock
I (15120) httpd: httpd_accept_conn: new connection on socket 54
I (15130) LAB_DASHBOARD: [HTTP GET /]: Serving real-time HTML Dashboard to Client 192.168.4.2
I (16250) LAB_DASHBOARD: [NETWORK TASK]: Queue received data -> Updating g_latest_data under Mutex lock
I (17140) LAB_DASHBOARD: [HTTP GET /api/data]: JSON Requested -> Locked Mutex -> Generated JSON:
{"temperature":28.10,"humidity":57.80,"light_lux":395,"timestamp_ms":16250}
I (18250) LAB_DASHBOARD: [NETWORK TASK]: Queue received data -> Updating g_latest_data under Mutex lock
I (19150) LAB_DASHBOARD: [HTTP GET /api/data]: JSON Requested -> Locked Mutex -> Generated JSON:
{"temperature":27.90,"humidity":59.10,"light_lux":430,"timestamp_ms":18250}
```

---

## 8. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดจึงต้องใช้ **Mutex** ในการป้องกันการเข้าถึงตัวแปร `g_latest_data` ร่วมกันระหว่าง `vNetworkTask` และ HTTP Handler? ถ้าไม่ใช้จะเกิดอะไรขึ้น?
> **คำตอบ:** 
> เนื่องจากตัวแปร `g_latest_data` มีโครงสร้างข้อมูลขนาด 16 ไบต์ (ประกอบด้วยตัวแปร float และ uint32 หลายตัว) ซึ่งซีพียูไม่สามารถอ่านหรือเขียนข้อมูลทั้งหมดให้เสร็จสิ้นได้ใน 1 สถาปัตยกรรมคำสั่งของฮาร์ดแวร์ (Non-Atomic Operation)
> 
> หากไม่มีการใช้ Mutex ป้องกัน: อาจเกิดภาวะ **Race Condition** เช่น ในจังหวะที่ `vNetworkTask` กำลังเขียนค่าอุณหภูมิใหม่เสร็จ แต่ยังเขียนค่าความชื้นหรือ Timestamp ไม่ทันเสร็จ ตัว FreeRTOS เกิดการสลับบริบทการทำงาน (Context Switch) ให้ HTTP Handler เข้ามาอ่านข้อมูล จะทำให้เกิดปัญหา **Torn Read** คือ เบราว์เซอร์ได้รับข้อมูลที่ผิดพลาด มีความไม่สอดคล้องกันระหว่างเวลาและค่าเซนเซอร์ หรือข้อมูลกลายเป็นค่าขยะ (Garbage Data) การใช้ Mutex (`xSemaphoreTake` / `xSemaphoreGive`) จึงช่วยบังคับให้กระบวนการอ่านและเขียนข้อมูลเป็นเอกเทศเสร็จสมบูรณ์ทั้งก้อนเสมอ

2. `esp_http_server` รัน Handler บน Thread ใด — เป็น Thread เดียวกับ FreeRTOS Task ของเราหรือไม่?
> **คำตอบ:** 
> **ไม่ได้รันบน Thread เดียวกัน** โดยคอมโพเนนต์ `esp_http_server` ของเฟรมเวิร์ก ESP-IDF จะสร้าง FreeRTOS Task แยกต่างหากของตัวเองขึ้นมาโดยเฉพาะ มีชื่อ Task ว่า `"httpd"` รันอยู่เบื้องหลังเพื่อคอยดักฟัง (Listen) และยอมรับการเชื่อมต่อ TCP Socket ที่เข้ามาทางพอร์ต 80 
> 
> เมื่อเบราว์เซอร์ส่งคำร้องขอ HTTP GET เข้ามา Task `"httpd"` จะเป็นผู้ประมวลผลและเรียก URI Handler Callback ที่เราลงทะเบียนไว้ ดังนั้น Handler จึงทำงานอยู่บน Context และ Stack ของ Task `"httpd"` แยกอิสระโดยสมบูรณ์จาก `vSensorTask` และ `vNetworkTask` ของเรา

3. การที่ Dashboard ใช้ `<meta http-equiv="refresh" content="2">` แทนที่จะใช้ JavaScript `fetch()` มีข้อดีและข้อเสียอย่างไร?
> **คำตอบ:** 
> - **ข้อดี:**
>   1. ความเรียบง่ายในการพัฒนา ไม่จำเป็นต้องเขียนสคริปต์ JavaScript หรือจัดการ DOM ฝั่งเบราว์เซอร์
>   2. ขนาดโค้ด HTML เล็กมาก ประหยัดพื้นที่จัดเก็บใน Flash Memory และ RAM บนตัว ESP32
>   3. ทำงานได้บนเว็บเบราว์เซอร์ทุกชนิด แม้จะเป็นเบราว์เซอร์รุ่นเก่าหรือปิดการทำงานของ JavaScript
> - **ข้อเสีย:**
>   1. ส่งผลกระทบต่อประสบการณ์ใช้งาน (User Experience) เนื่องจากเบราว์เซอร์จะทำการรีโหลดหน้าเว็บใหม่ทั้งหน้า (Full Page Reload) ทำให้หน้าจอกะพริบทุกๆ 2 วินาที
>   2. สิ้นเปลืองแบนด์วิดท์เครือข่าย เพราะ ESP32 ต้องส่งโครงสร้าง HTML และ CSS ก้อนเดิมซ้ำๆ ออกไปทุก 2 วินาที แทนที่จะส่งเฉพาะข้อมูล JSON ขนาดเล็ก
>   3. เพิ่มภาระการประมวลผลและการใช้พลังงานบนตัว ESP32 เนื่องจากต้อง Render หน้าเว็บและสร้าง Connection Socket ใหม่บ่อยครั้ง เมื่อเทียบกับเทคนิค Asynchronous AJAX/Fetch API
