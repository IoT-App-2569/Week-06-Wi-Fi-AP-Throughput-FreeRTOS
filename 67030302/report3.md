# ใบงานที่ 6.3: การออกแบบ FreeRTOS Task Architecture & Sensor Data Fusion ผ่าน Queue

## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :--- | :---: | :---: | :---: |
| **`SensorCollectorTask`** | 3072 | 486 Words (1,944 Bytes) | ปลอดภัยมาก (คงเหลือพื้นที่สแตก 63.3%) |
| **`NetworkCommTask`** | 4096 | 618 Words (2,472 Bytes) | ปลอดภัยมาก (คงเหลือพื้นที่สแตก 60.4%) |

### 6.2 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log)

```text
I (516) main_task: Calling app_main()
I (516) LAB_FREERTOS_QUEUE: ==================================================================
I (516) LAB_FREERTOS_QUEUE:   Lab 6.3: FreeRTOS Multi-Tasking & Sensor Data Queue Fusion
I (526) LAB_FREERTOS_QUEUE: ==================================================================
I (536) LAB_FREERTOS_QUEUE: [TASK CREATED]: Sensor Collector Task Started on Core 1
I (536) LAB_FREERTOS_QUEUE: [TASK CREATED]: Network Task Started on Core 0
I (546) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 27.4 C, Hum: 58.2 %, Lux: 412
I (556) FORENSIC_STACK:   -> SensorTask Stack Remaining: 486 words (1944 bytes)
I (556) LAB_FREERTOS_QUEUE: =======================================================
I (566) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (566) LAB_FREERTOS_QUEUE:   -> Timestamp   : 14250 ms
I (576) LAB_FREERTOS_QUEUE:   -> Temperature : 27.40 degC
I (576) LAB_FREERTOS_QUEUE:   -> Humidity    : 58.20 %
I (586) LAB_FREERTOS_QUEUE:   -> Light Lux   : 412 lux
I (586) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (596) LAB_FREERTOS_QUEUE: =======================================================
I (596) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 618 words (2472 bytes)

I (2050) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 28.1 C, Hum: 57.8 %, Lux: 395
I (2050) FORENSIC_STACK:   -> SensorTask Stack Remaining: 486 words (1944 bytes)
I (2060) LAB_FREERTOS_QUEUE: =======================================================
I (2060) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (2070) LAB_FREERTOS_QUEUE:   -> Timestamp   : 16250 ms
I (2070) LAB_FREERTOS_QUEUE:   -> Temperature : 28.10 degC
I (2080) LAB_FREERTOS_QUEUE:   -> Humidity    : 57.80 %
I (2080) LAB_FREERTOS_QUEUE:   -> Light Lux   : 395 lux
I (2090) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (2090) LAB_FREERTOS_QUEUE: =======================================================
I (2100) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 618 words (2472 bytes)

I (3550) LAB_FREERTOS_QUEUE: [SENSOR TASK]: Pushing Data -> Temp: 27.9 C, Hum: 59.1 %, Lux: 430
I (3550) FORENSIC_STACK:   -> SensorTask Stack Remaining: 486 words (1944 bytes)
I (3560) LAB_FREERTOS_QUEUE: =======================================================
I (3560) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Data Received from Queue!
I (3570) LAB_FREERTOS_QUEUE:   -> Timestamp   : 18250 ms
I (3570) LAB_FREERTOS_QUEUE:   -> Temperature : 27.90 degC
I (3580) LAB_FREERTOS_QUEUE:   -> Humidity    : 59.10 %
I (3580) LAB_FREERTOS_QUEUE:   -> Light Lux   : 430 lux
I (3590) LAB_FREERTOS_QUEUE: [NETWORK TASK]: Preparing JSON Packet for Wi-Fi Transmission...
I (3590) LAB_FREERTOS_QUEUE: =======================================================
I (3600) FORENSIC_STACK:   -> NetworkTask Stack Remaining: 618 words (2472 bytes)
```

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
> **คำตอบ:** 
> การใช้ FreeRTOS Queue มีความปลอดภัยระดับ Thread-Safe สูงกว่าตัวแปร Global ด้วยเหตุผลหลัก 3 ประการ:
> 1. **การปกป้องหน่วยความจำแบบ Atomic (Critical Sections):** ภายในฟังก์ชัน `xQueueSend()` และ `xQueueReceive()` จะมีการจัดการ Interrupt และ Spinlock อัตโนมัติ ป้องกันไม่ให้เกิดสภาวะแย่งชิงทรัพยากร (**Race Condition**) หรือการอ่านข้อมูลในขณะที่อีก Task กำลังเขียนไม่เสร็จ (**Torn Read/Write**)
> 2. **การส่งผ่านข้อมูลแบบ Pass-by-Value:** ข้อมูลที่ส่งผ่าน Queue จะถูกคัดลอก (Deep Copy) ไปเก็บไว้ในบัฟเฟอร์ของ Queue โดยตรง ทำให้ Task ต้นทางและ Task ปลายทางไม่ได้แชร์พอยน์เตอร์หรือพื้นที่หน่วยความจำเดียวกัน ข้อมูลจึงไม่ถูกเขียนทับโดยไม่ตั้งใจ
> 3. **กลไกการซิงโครไนซ์แบบ Event-Driven (Blocking Mechanism):** Queue สามารถสั่งให้ Task ผู้รับเข้าสู่สถานะ Blocked (พักการทำงานโดยไม่กินพลังงานและซีพียู) จนกว่าจะมีข้อมูลส่งเข้ามาในคิว ซึ่งดีกว่าการใช้ตัวแปร Global ที่ต้องใช้ Busy-waiting Loop ในการวนตรวจสอบตลอดเวลา

2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
> **คำตอบ:** 
> ฟังก์ชัน `uxTaskGetStackHighWaterMark()` มีประโยชน์อย่างยิ่งในการตรวจสอบและวิเคราะห์การใช้งานหน่วยความจำของ Task:
> 1. **ตรวจวัดขนาดสแตกคงเหลือน้อยที่สุด (Minimum Free Stack):** ส่งคืนค่าปริมาณหน่วยความจำสแตกที่เหลืออยู่ในจุดที่ถูกใช้งานหนักที่สุด (Worst-case Usage) นับตั้งแต่สร้าง Task ขึ้นมา
> 2. **ป้องกันปัญหา Stack Overflow:** หากค่า High Water Mark ลู่เข้าใกล้ 0 แสดงว่าระบบมีความเสี่ยงสูงมากที่จะเกิดความล้มเหลวจาก Stack Overflow ซึ่งจะทำให้หน่วยความจำข้างเคียงเสียหายและเกิด Fatal System Crash/Panic
> 3. **การปรับแต่งประสิทธิภาพหน่วยความจำ (RAM Optimization):** หากพบว่าค่า High Water Mark เหลือมากเกินไป (เช่น เหลือเกิน 60–70%) นักพัฒนาสามารถปรับลดขนาด Stack ใน `xTaskCreate()` ลงมาได้ เพื่อประหยัดพื้นที่ RAM ให้กับระบบส่วนอื่น

3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
> **คำตอบ:** 
> - **สิ่งที่เกิดขึ้นกับ Queue:** ข้อมูลโครงสร้าง `sensor_data_t` ที่ถูกส่งเข้ามาจะสะสมอย่างรวดเร็วจนเต็มความจุของ Queue (Queue Full - ในการทดลองกำหนดไว้ 10 ไอเทม) และเมื่อคิวเต็ม ฟังก์ชัน `xQueueSend(xSensorQueue, &data, pdMS_TO_TICKS(100))` จะรอจนหมด Timeout 100 ms จากนั้นจะคืนค่า `errQUEUE_FULL` ทำให้ข้อมูลเซนเซอร์ชุดใหม่ถูกปฏิเสธและทิ้งไป (`Packet Dropped`)
> - **แนวทางการรับมือและแก้ไขทางสถาปัตยกรรม:**
>   1. **การใช้ Ring Buffer หรือโหมด Overwrite:** หากระบบต้องการเฉพาะข้อมูลสถานะล่าสุด สามารถเปลี่ยนมาใช้ `xQueueOverwrite()` เพื่อเขียนทับข้อมูลเก่าที่ค้างอยู่ในคิวทันที
>   2. **การทำ Data Aggregation / Pre-filtering:** ปรับให้ `vSensorTask` ทำการรวบรวมข้อมูล, สุ่มตัวอย่าง (Downsampling) หรือคำนวณค่าเฉลี่ยทางสถิติก่อน แล้วจึงส่งสรุปเข้า Queue ทุกๆ 500 ms ให้สอดคล้องกับความเร็วของฝั่ง Network
>   3. **การเพิ่มขนาด Queue:** หากมี RAM เพียงพอและต้องการเก็บข้อมูลให้ครบทุกเม็ด สามารถขยายขนาดคิวเพื่อรองรับการกระชากของข้อมูล (Burst Buffering) ได้
