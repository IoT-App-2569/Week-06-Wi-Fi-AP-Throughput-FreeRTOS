# Week 06: Wi-Fi SoftAP, RF Performance Profiling & Sensor Fusion with FreeRTOS

## 1. บทนำ (Introduction)
ในสัปดาห์ที่ 6 นี้ เราจะย้ายจากการทำงานในโหมด Station (`WIFI_STA`) มาสู่การกำหนดให้ ESP32 ทำงานเป็น **Access Point (SoftAP Mode)** เพื่อสร้างเครือข่ายไร้สายส่วนตัวของตนเอง 

นอกจากนี้นักศึกษาจะได้เรียนรู้และทดลองวัดประสิทธิภาพสัญญาณคลื่นวิทยุจริงผ่าน **RF Signal Physics (RSSI vs Speed/Throughput)** ด้วยการปรับกำลังส่ง (`esp_wifi_set_max_tx_power`) และวัดการชะลอตัวของสัญญาณเมื่อมีระยะทางหรือสิ่งกีดขวาง จากนั้นประยุกต์ใช้ **FreeRTOS Multi-Tasking & Queues** เพื่อรวมพลังกับเซนเซอร์ในการทำ **Sensor & Signal Fusion** สร้างแอปพลิเคชัน IoT ที่ใช้งานได้จริงในชีวิตประจำวัน เช่น **ระบบเช็กชื่อและประเมินระยะทางอัจฉริยะ (Proximity Attendance System)**

---

## 2. เนื้อหาการเรียนรู้ประจำสัปดาห์ (Lesson Roadmap)

1. **[01-Wi-Fi-SoftAP-Architecture.md](01-Wi-Fi-SoftAP-Architecture.md)** - สถาปัตยกรรม SoftAP Mode, DHCP Server (`dhcps`), Beacon Interval และ Event Handling (`WIFI_EVENT_AP_STACONNECTED`)
2. **[02-RF-Signal-Physics-and-TxPower.md](02-RF-Signal-Physics-and-TxPower.md)** - ฟิสิกส์คลื่นวิทยุ RSSI (dBm), Path Loss, การปรับกำลังส่งด้วย `esp_wifi_set_max_tx_power` และการวัด Throughput/Speed (Kbps)
3. **[03-FreeRTOS-Task-Design-for-IoT-Nodes.md](03-FreeRTOS-Task-Design-for-IoT-Nodes.md)** - สถาปัตยกรรม Multi-Tasking ด้วย FreeRTOS, การแบ่งงาน Network vs Sensor, และการสื่อสารผ่าน FreeRTOS Queues
4. **[04-Glossary.md](04-Glossary.md)** - อภิธานศัพท์ คำย่อ และนิยามทางเทคนิคประจำสัปดาห์ที่ 6

---

## 3. ใบงานปฏิบัติการประจำสัปดาห์ (Labsheets)

1. **[05-Labsheet-06-1-ESP32-SoftAP-Tracking.md](05-Labsheet-06-1-ESP32-SoftAP-Tracking.md)** - ใบงานที่ 6.1: การคอนฟิก ESP32 SoftAP และการสกัด Forensic Log ข้อมูล Client (MAC Address & AID)
2. **[06-Labsheet-06-2-RSSI-Speed-Profiling.md](06-Labsheet-06-2-RSSI-Speed-Profiling.md)** - ใบงานที่ 6.2: การประเมินความสัมพันธ์ RSSI vs Throughput ด้วย Software Tx-Power Control (Pair Work 👥)
3. **[07-Labsheet-06-3-FreeRTOS-Sensor-Queue.md](07-Labsheet-06-3-FreeRTOS-Sensor-Queue.md)** - ใบงานที่ 6.3: การออกแบบ FreeRTOS Task Architecture & Sensor Data Fusion ผ่าน Queue
4. **[08-Labsheet-06-4-Proximity-Attendance-System.md](08-Labsheet-08-4-Proximity-Attendance-System.md)** - ใบงานที่ 6.4: มินิโปรเจกต์ระบบเช็กชื่อและยืนยันตัวตนอัจฉริยะในห้องเรียนด้วย RF Proximity & Sensor Fusion

---

ปรับปรุงล่าสุด: 3 สิงหาคม 2569
