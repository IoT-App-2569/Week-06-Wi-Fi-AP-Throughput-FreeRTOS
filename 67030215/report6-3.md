## 6. ตารางบันทึกผลการทดลอง (Experiment Results)

### 6.1 บันทึกข้อมูล Forensic Stack High Water Mark

| ชื่อ FreeRTOS Task | ขนาด Stack ที่กำหนดใน `xTaskCreate` (Bytes) | ค่า High Water Mark ที่อ่านได้ (Words / Bytes) | สถานะความปลอดภัยสแตก |
| :--- | :---: | :---: | :---: |
| **`SensorCollectorTask`** | 3072 |1876 Bytes |ปลอดภัย |
| **`NetworkCommTask`** | 4096 |1848 Bytes |ปลอดภัย |

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เหตุใดการใช้ **FreeRTOS Queue** จึงมีความปลอดภัย (Thread-Safe) มากกว่าการใช้ตัวแปรแบบ Global ในการรับส่งข้อมูลระหว่างสอง Task?
```
FreeRTOS Queue ปลอดภัยกว่าเพราะมีกลไก Critical Section และ Atomic Operation ในตัว ทำให้การอ่าน-เขียนข้อมูลระหว่าง Task ไม่เกิด Race Condition และ
ยังมีระบบ Blocking ช่วย synchronize การทำงานโดยอัตโนมัติ ส่วนตัวแปร Global ไม่มีการป้องกันใดๆ หาก Task ถูก Preempt กลางคันขณะเขียนค่า อาจทำให้ข้อมูลผิดเพี้ยนหรือไม่สมบูรณ์ได้
```
2. ค่า **Stack High Water Mark** มีประโยชน์อย่างไรในการตรวจวินิจฉัยปัญหาบั๊กในระบบเรียลไทม์ (RTOS)?
```
เป็นค่าที่บอกพื้นที่ Stack เหลือน้อยที่สุดที่เคยเกิดขึ้นของแต่ละ Task เรียกดูได้ด้วย uxTaskGetStackHighWaterMark() ช่วยให้รู้ว่า Task ใดจัดสรร Stack น้อยเกินไปจนเสี่ยง Stack Overflow ซึ่งเป็นสาเหตุของอาการ Crash แบบสุ่มที่วินิจฉัยยากในระบบเรียลไทม์ ทำให้สามารถปรับขนาด Stack ให้เหมาะสมก่อนเกิดปัญหาจริง
```
3. หาก `vSensorTask` ส่งข้อมูลเร็วมาก (เช่น ทุก 10ms) แต่ `vNetworkTask` ส่งข้อมูลออก Wi-Fi ได้ช้า (เช่น ใช้เวลา 500ms) จะเกิดอะไรขึ้นกับ Queue และระบบจะรับมืออย่างไร?
```
Queue จะเริ่มสะสมข้อมูลค้างอยู่เรื่อยๆ เพราะ vSensorTask ผลิตข้อมูลเร็วกว่าที่ vNetworkTask จะดึงไปใช้ทัน หากไม่จัดการใดๆ Queue จะเต็มในที่สุด ทำให้ vSensorTask ที่พยายาม xQueueSend ต้อง Block รอ หรือหากตั้งค่า timeout เป็น 0 ข้อมูลใหม่จะถูกทิ้งทันที การรับมือที่เหมาะสมคือกำหนดขนาด Queue ให้พอเหมาะ ใช้ xQueueOverwrite สำหรับข้อมูล sensor ที่สนใจแค่ค่าล่าสุด หรือลดความถี่การส่งของ vSensorTask ให้สอดคล้องกับความสามารถของ vNetworkTask มากขึ้น
```
