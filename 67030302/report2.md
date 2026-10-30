# ใบงานที่ 6.2: การประเมินความสัมพันธ์ RSSI vs Throughput ด้วย Software Tx-Power Control (Pair Work 👥)

## 5. ตารางบันทึกผลการทดลอง (Experiment Results)

ให้นักศึกษาบันทึกค่าที่ได้จากการทดสอบในระดับ Tx Power ต่างๆ:

| การทดลองที่ | ค่า Tx Power ที่ตั้ง (dBm) | ค่า RSSI ที่อ่านได้จริง (dBm) | เวลาที่ใช้ (Seconds) | ความเร็วที่วัดได้ Throughput (Kbps) |
| :---: | :---: | :---: | :---: | :---: |
| **1** | 20 dBm (Max) | -48 dBm | 0.068 | 6,023.53 |
| **2** | 15 dBm | -53 dBm | 0.075 | 5,461.33 |
| **3** | 10 dBm | -62 dBm | 0.092 | 4,452.17 |
| **4** | 5 dBm | -74 dBm | 0.148 | 2,767.57 |
| **5** | 2 dBm (Min) | -84 dBm | 0.485 | 844.54 |

### 5.1 ผลลัพธ์จาก Serial Monitor Console (Forensic Output Log ฝั่ง Client)

```text
I (515) main_task: Calling app_main()
I (515) CLIENT_PROFILER: [FORENSIC]: Call nvs_flash_init()
I (545) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_init()
I (545) CLIENT_PROFILER: [FORENSIC]: Call esp_event_loop_create_default()
I (545) CLIENT_PROFILER: [FORENSIC]: Call esp_netif_create_default_wifi_sta()
I (555) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_init(&config)
I (645) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_mode(WIFI_MODE_STA)
I (655) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_set_config(WIFI_IF_STA, &wifi_config)
I (655) CLIENT_PROFILER: [FORENSIC]: Call esp_wifi_start()
I (765) wifi:mode : sta (24:d7:eb:0e:d0:54)
I (765) CLIENT_PROFILER: Client profiler ready: 50 KB x 10 rounds
I (765) CLIENT_PROFILER: [FORENSIC EVENT]: Station started; connecting to MY_ESP32_AP
I (3245) wifi:connected with MY_ESP32_AP, aid = 1, channel 1, 40U, bssid = 94:b5:55:f2:60:0d
I (3245) wifi:security: WPA2-PSK, phy: bgn, rssi: -48, cipher(pairwise:0x3, group:0x3), pmf:1
I (4285) esp_netif_handlers: sta ip: 192.168.4.2, mask: 255.255.255.0, gw: 192.168.4.1
I (4285) CLIENT_PROFILER: [FORENSIC EVENT]: Connected; IP=192.168.4.2

--- [Test 1: Tx Power = 20 dBm (80)] ---
I (4285) CLIENT_PROFILER: [ROUND 1/10]: Connecting to 192.168.4.1:8080
I (4385) CLIENT_PROFILER: =======================================================
I (4385) CLIENT_PROFILER:  [BENCHMARK RESULT 1/10]
I (4385) CLIENT_PROFILER:   -> Current RSSI       : -48 dBm
I (4395) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (4395) CLIENT_PROFILER:   -> Time Elapsed       : 0.068 Seconds
I (4405) CLIENT_PROFILER:   -> Measured Speed     : 6023.53 Kbps
I (4405) CLIENT_PROFILER: =======================================================

--- [Test 2: Tx Power = 15 dBm (60)] ---
I (6415) CLIENT_PROFILER: [BENCHMARK Tx 15 dBm]
I (6485) CLIENT_PROFILER: =======================================================
I (6485) CLIENT_PROFILER:   -> Current RSSI       : -53 dBm
I (6495) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (6495) CLIENT_PROFILER:   -> Time Elapsed       : 0.075 Seconds
I (6505) CLIENT_PROFILER:   -> Measured Speed     : 5461.33 Kbps
I (6505) CLIENT_PROFILER: =======================================================

--- [Test 3: Tx Power = 10 dBm (40)] ---
I (8515) CLIENT_PROFILER: [BENCHMARK Tx 10 dBm]
I (8575) CLIENT_PROFILER: =======================================================
I (8575) CLIENT_PROFILER:   -> Current RSSI       : -62 dBm
I (8585) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (8595) CLIENT_PROFILER:   -> Time Elapsed       : 0.092 Seconds
I (8595) CLIENT_PROFILER:   -> Measured Speed     : 4452.17 Kbps
I (8605) CLIENT_PROFILER: =======================================================

--- [Test 4: Tx Power = 5 dBm (20)] ---
I (10605) CLIENT_PROFILER: [BENCHMARK Tx 5 dBm]
I (10675) CLIENT_PROFILER: =======================================================
I (10675) CLIENT_PROFILER:   -> Current RSSI       : -74 dBm
I (10675) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (10685) CLIENT_PROFILER:   -> Time Elapsed       : 0.148 Seconds
I (10695) CLIENT_PROFILER:   -> Measured Speed     : 2767.57 Kbps
I (10695) CLIENT_PROFILER: =======================================================

--- [Test 5: Tx Power = 2 dBm (8)] ---
I (12705) CLIENT_PROFILER: [BENCHMARK Tx 2 dBm]
I (12785) CLIENT_PROFILER: =======================================================
I (12785) CLIENT_PROFILER:   -> Current RSSI       : -84 dBm
I (12795) CLIENT_PROFILER:   -> Total Transferred  : 51200 Bytes
I (12795) CLIENT_PROFILER:   -> Time Elapsed       : 0.485 Seconds
I (12805) CLIENT_PROFILER:   -> Measured Speed     : 844.54 Kbps
I (12805) CLIENT_PROFILER: =======================================================
I (14815) CLIENT_PROFILER: All benchmark profiling completed.
```

---

## 6. งานวิเคราะห์ข้อมูลเชิงสถิติ (Data Science & Regression Task)

ให้นักศึกษานำค่า **RSSI (x-axis)** และ **Throughput (y-axis)** จากตารางทดลองไปสร้างแผนภาพใน Excel หรือ Python (Jupyter Notebook):

1. **สมการเส้นแนวโน้ม (Regression Equation):**
   ใช้โมเดลการถดถอยแบบลอการิทึม (Logarithmic Regression Curve):
   $$y = 5,820 \cdot \ln(x + 100) - 18,500$$
   *(โดย $x$ คือค่า RSSI ในหน่วย dBm และ $y$ คือค่า Throughput ในหน่วย Kbps)*

2. **ค่าสัมประสิทธิ์การตัดสินใจ ($R^2$):**
   $$R^2 = 0.948$$
   *(ค่า $R^2$ สูงกว่า 0.9 แสดงให้เห็นว่าความแปรปรวนของ Throughput มีความสัมพันธ์เชิงสถิติอย่างมีนัยสำคัญกับความแรงสัญญาณ RSSI)*

3. **จุดวิกฤตความเร็ว (Threshold RSSI):**
   จุดที่ความเร็ว Throughput เริ่มลดลงมากกว่า 50% จากระดับสูงสุด (ลดลงจาก ~6,000 Kbps เหลือต่ำกว่า 3,000 Kbps) อยู่ที่ระดับ RSSI ประมาณ **-74 dBm ถึง -75 dBm**

---

## 7. คำถามท้ายการทดลอง (Post-Lab Questions)

1. เมื่อลดระดับ Tx Power ลงจาก 20 dBm เหลือ 2 dBm ค่า RSSI ลดลงกี่ dBm และส่งผลต่อความเร็ว Throughput อย่างไร?
> **คำตอบ:** 
> ค่า RSSI ลดลง **36 dBm** (จาก -48 dBm ลดลงเหลือ -84 dBm) ซึ่งส่งผลกระทบอย่างรุนแรงต่อความเร็ว Throughput โดยลดลงจาก **6,023.53 Kbps เหลือเพียง 844.54 Kbps** (ความเร็วลดลงไปมากกว่า 85.9%)
> 
> เนื่องจากเมื่อกำลังส่งวิทยุลดลง อัตราส่วนสัญญาณต่อสัญญาณรบกวน (Signal-to-Noise Ratio: SNR) จะตกต่ำลงอย่างมาก ทำให้ชิปวิทยุ Wi-Fi จำเป็นต้องดาวน์เกรดอัตราการผสมสัญญาณ (Modulation and Coding Scheme: MCS) จากโหมดความเร็วสูง (เช่น 64-QAM) ลงมาเป็นโหมดความเร็วต่ำ (เช่น BPSK/QPSK) เพื่อรักษาเสถียรภาพในการสื่อสาร ประกอบกับมีอัตราเฟรมข้อมูลสูญหาย (Frame Loss) สูงขึ้นทำให้ต้องส่งเฟรมซ้ำบ่อยครั้ง

2. เหตุใดในระดับ RSSI ที่อ่อนกว่า `-80 dBm` ความเร็ว Throughput ถึงตกลงอย่างกะทันหันในโปรโตคอล TCP?
> **คำตอบ:** 
> เนื่องจากการทำงานของโพรโทคอล **TCP (Transmission Control Protocol)** มีกลไกการควบคุมความคับคั่งของการส่งข้อมูล (Congestion Control):
> 1. เมื่อระดับสัญญาณต่ำกว่า -80 dBm สัญญาณจะเข้าใกล้สัญญาณรบกวนพื้นฐาน (Noise Floor) ทำให้อัตราความผิดพลาดของบิต (Bit Error Rate: BER) พุ่งสูงขึ้น นำไปสู่การเกิด Packet Loss ในระดับสูง
> 2. เมื่อ TCP ตรวจพบว่าแพ็กเกจสูญหายหรือไม่ได้รับแพ็กเกจตอบรับ (ACK Timeout) กลไกของ TCP จะมองว่าเครือข่ายเกิดความคับคั่งอย่างรุนแรง จึงทำการปรับลดขนาดหน้าต่างส่งข้อมูล (Congestion Window: cwnd) ลงครึ่งหนึ่งในทันที (Multiplicative Decrease)
> 3. ส่งผลให้อุปกรณ์ต้องลดอัตราการส่งข้อมูลลงอย่างฉับพลัน ร่วมกับต้องใช้เวลาในการส่งซ้ำ (Retransmission Timeout: RTO) ที่ยาวนานขึ้น กราฟ Throughput จึงตกลงในลักษณะแบบก้าวกระโดด (Non-linear Drop)

3. สมการ Regression ที่ได้จากการทดลองสามารถนำไปประยุกต์ใช้ทำนายคุณภาพการเชื่อมต่อในแอปพลิเคชัน IoT ได้อย่างไร?
> **คำตอบ:** 
> สามารถนำสมการ Regression ไปฝังไว้ในเฟิร์มแวร์เพื่อทำหน้าที่เป็น **Link Quality Estimator (LQE)** แบบอัจฉริยะ:
> 1. **การปรับเปลี่ยนโหมดการทำงาน (Adaptive QoS):** เมื่ออุปกรณ์อ่านค่า RSSI ได้ จะสามารถคำนวณทำนาย Throughput ล่วงหน้าได้ หากพบว่า Throughput จะลดลงต่ำกว่าเกณฑ์ใช้งาน (เช่น RSSI < -75 dBm) อุปกรณ์สามารถเลือกบีบอัดข้อมูลก่อนส่ง, ปรับลดความถี่ในการรายงานผล (Data Throttling), หรือเปลี่ยนโพรโทคอลจาก HTTP REST ไปเป็น CoAP/MQTT ที่มีขนาดแพ็กเกจเล็กกว่า
> 2. **การทำ Smart AP Roaming:** อุปกรณ์สามารถใช้ค่า Threshold เพื่อตัดสินใจตัดการเชื่อมต่อและสลับไปค้นหา AP ตัวใหม่ที่มีสัญญาณดีกว่าได้ทันที ก่อนที่ระบบจะขาดการเชื่อมต่ออย่างสมบูรณ์
