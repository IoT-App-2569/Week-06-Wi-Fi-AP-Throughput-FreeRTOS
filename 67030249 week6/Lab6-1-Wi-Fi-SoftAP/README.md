# Worksheet Lab6\-1\-Wi\-Fi\-SoftAP

## Build Flash and monitor

__Build command \(Docker\)__

```
docker run --rm --mount "type=bind,source=$((Get-Location).Path),target=/workspace" -w /workspace/ESP32_Project/Lab6-1-Wi-Fi-SoftAP espressif/idf:release-v6.1  idf.py -B build-v6 build
```

__Flash command \(Window\)__

```
python -m esptool --chip esp32 -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size 2MB --flash_freq 40m 0x1000 build-v6\bootloader\bootloader.bin 0x8000 build-v6\partition_table\partition-table.bin 0x10000 build-v6\wifi_softap_tracking.bin && idf monitor
```

## References

__Build command \(Docker\)__

```
docker run --rm \

  --mount "type=bind,source=$((Get-Location).Path),target=/workspace" \

  -w /workspace/ESP32_Project/Lab6-1-Wi-Fi-SoftAP \

  espressif/idf:release-v6.1 \

  idf.py -B build-v6 build
```

🧱 1\) docker run สั่งให้ Docker สร้างและรัน container จาก image ที่กำหนด

🧹 2\) \-\-rm เมื่อ container ทำงานเสร็จ ให้ลบทิ้งทันที ไม่เก็บ container ค้างไว้ → workspace สะอาด

📁 3\) \-\-mount "type=bind,source=\.\.\.,target=\.\.\." เอาโฟลเดอร์บนเครื่องจริง \(Windows\) มาเชื่อมต่อเข้าไปใน container

type=bind → ผูกโฟลเดอร์จริงเข้ากับ container

source=$\(\(Get\-Location\)\.Path\) → path ปัจจุบันของ PowerShell

target=/workspace → container จะเห็นโฟลเดอร์นี้เป็น /workspace

นี่คือจุดที่ผิดบ่อยที่สุด ถ้า PowerShell อยู่ผิดที่ → container จะเห็นโครงสร้างไฟล์ไม่ตรงกับที่คุณคิด

📌 4\) \-w /workspace/\.\.\. ตั้ง working directory ของ container เหมือน cd เข้าไปในโฟลเดอร์นั้นก่อนรันคำสั่ง

Docker จะเข้าไปใน:

```
/workspace/ESP32_Project/Lab6-2-RSSI-Speed-Profiler
```

แล้วรันคำสั่งต่อไป

ถ้าโฟลเดอร์นี้ไม่มีจริง → Docker จะบอกว่าไม่เจอ CMakeLists\.txt

🧰 5\) espressif/idf:release\-v6\.1 ชื่อ image ที่จะใช้รัน เป็น ESP\-IDF เวอร์ชัน 6\.1 ที่ Espressif ทำไว้ให้

🛠️ 6\) idf\.py \-B build\-v6 build คำสั่งที่รันใน container

idf\.py → ตัว build system ของ ESP\-IDF

\-B build\-v6 → ให้สร้าง build directory ชื่อ build\-v6

build → คำสั่งให้ compile project

🎯 สรุปแบบสั้นที่สุด \(จำง่าย\)

__Argument__

__ความหมาย__

\-\-rm

รันเสร็จลบ container

\-\-mount

ผูกโฟลเดอร์ Windows → container

source=

โฟลเดอร์จริงบน Windows

target=

โฟลเดอร์ที่ container จะเห็น

\-w

โฟลเดอร์ที่ container จะเข้าไปทำงาน

espressif/idf:release\-v6\.1

ESP\-IDF image

idf\.py \-B build\-v6 build

คำสั่ง build ESP\-IDF

__Flash command \(Window\)__

```
cd ESP32_Project/Lab6-1-Wi-Fi-SoftAP

python -m esptool -p COM24 --chip esp32 -b 460800 --before default_reset --after hard_reset write_flash --flash_mode dio --flash_size 2MB --flash_freq 40m 0x1000 build-v6\bootloader\bootloader.bin 0x8000 build-v6\partition_table\partition-table.bin 0x10000 build-v6\wifi_softap_tracking.bin && idf monitor -p COM24
```

__Argument / Parameter__

__ความหมายและการทำงาน__

python \-m esptool

เรียกใช้งานเครื่องมือ esptool \(โมดูลสำหรับจัดการโปรแกรม ESP32 ของ Espressif\) ผ่าน Python

\-p COMx

ผ่าน COM port x

\-\-chip esp32

ระบุตระกูลของชิปเป้าหมายเป็น __ESP32__

\-b 460800 \(หรือ \-\-baud\)

กำหนด Baud Rate สื่อสารในการเขียน Flash เป็น __460,800 bps__ \(ช่วยให้เขียนโปรแกรมได้เร็วขึ้น\)

\-\-before default\_reset

สถานะก่อนการแฟลช: สั่งให้ส่งสัญญาณ DTR/RTS เข้าสู่ __Download/Bootloader Mode__ อัตโนมัติ

\-\-after hard\_reset

สถานะหลังแฟลชเสร็จ: สั่งให้ทำ __Hardware Reset__ บอร์ด เพื่อให้ ESP32 เริ่มทำงานทันที

write\_flash

คำสั่งหลักในการสั่งให้เขียนไฟล์ Binary ลงในหน่วยความจำ Flash

\-\-flash\_mode dio

กำหนดโหมดการสื่อสารกับหน่วยความจำ SPI Flash เป็น __DIO__ \(Dual I/O \- ใช้สายข้อมูล 2 เส้น\)

\-\-flash\_size 2MB

กำหนดขนาดของ Flash Memory ที่ใช้งานเป็น __2MB__

\-\-flash\_freq 40m

กำหนดความถี่สัญญาณนาฬิกาในการรับส่งข้อมูลกับ Flash เป็น __40 MHz__

0x1000 build\-v6\\bootloader\\\.\.\.bin

__\[Address \+ File 1\]__ แฟลชไฟล์ Bootloader ที่ตำแหน่งหน่วยความจำ 0x1000

0x8000 build\-v6\\partition\_table\\\.\.\.bin

__\[Address \+ File 2\]__ แฟลชไฟล์ Partition Table ที่ตำแหน่งหน่วยความจำ 0x8000

0x10000 build\-v6\\wifi\_softap\_tracking\.bin

__\[Address \+ File 3\]__ แฟลชไฟล์ Application \(โปรแกรมหลัก\) ที่ตำแหน่งหน่วยความจำ 0x10000

&&

ตัวเชื่อมคำสั่ง: ถ้ารันคำสั่งแฟลชสำเร็จ จะรันคำสั่งถัดไปทันที

idf monitor

เปิดโปรแกรม Serial Monitor ของ ESP\-IDF เพื่อดูข้อมูล Log จากบอร์ด
