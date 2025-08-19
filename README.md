
[![GitHub repo](https://img.shields.io/badge/GitHub-Repository-blue?logo=github)](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor)
[![Platform](https://img.shields.io/badge/Platform-ESP32-green?logo=espressif)](https://www.espressif.com/)
[![Language](https://img.shields.io/badge/Language-C++-blue?logo=arduino)](https://www.arduino.cc/)

---

## 📖 معرفی پروژه  
این پروژه برای **نمایش دما و رطوبت محیط** با استفاده از سنسور **DHT22** و نمایشگر **OLED SSD1306** روی برد **ESP32** طراحی شده است.  
اطلاعات به صورت **زیبا، دسته‌بندی‌شده و خوانا** روی صفحه نمایش داده می‌شوند و همزمان در سریال مانیتور نیز چاپ می‌شوند.  

🔗 لینک ریپوزیتوری:  
[ESP32-DHT22-OLED-Monitor](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor)

---

## ⚙️ سخت‌افزار مورد نیاز
برای اجرای این پروژه نیاز به قطعات زیر دارید:

- 🔌 **برد ESP32**  
- 🌡️ **سنسور DHT22** (برای دما و رطوبت)  
- 🖥️ **نمایشگر OLED SSD1306 (128x64, I2C)**  
- 🧵 سیم جامپر (Male-Female)  
- ⚡ کابل USB برای اتصال ESP32 به کامپیوتر  

---

## 🛠️ نرم‌افزارهای مورد نیاز
- [Arduino IDE](https://www.arduino.cc/en/software)  
- نصب برد ESP32 در Arduino IDE از مسیر:  
  `File > Preferences > Additional Boards Manager URLs`  
  و اضافه کردن لینک:  
```

[https://dl.espressif.com/dl/package\_esp32\_index.json](https://dl.espressif.com/dl/package_esp32_index.json)

````
- نصب کتابخانه‌ها از طریق Library Manager:
- 📦 **Adafruit SSD1306**
- 📦 **Adafruit GFX Library**
- 📦 **DHT sensor library for ESPx**

---

## 🔌 نحوه سیم‌کشی
اتصالات سخت‌افزاری مطابق جدول زیر انجام می‌شود:

| ESP32 Pin | OLED Pin | DHT22 Pin |
|-----------|----------|-----------|
| GPIO 5    | SDA      | -         |
| GPIO 4    | SCL      | -         |
| 3.3V      | VCC      | VCC       |
| GND       | GND      | GND       |
| GPIO 13   | -        | Data      |

📸 تصاویر پروژه (بخش Pic):  
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/1.jpg)  
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/2.jpg)  
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/3.jpg)  
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/4.jpg)  
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/5.jpg)  

---

## 💻 کد پروژه
فایل اصلی در ریپوزیتوری:  
👉 [ESP32_Temp.ino](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/ESP32_Temp.ino)

عملکرد کلی کد:  
1. **خواندن دما و رطوبت** از سنسور DHT22.  
2. **محاسبه Heat Index** (شاخص گرما).  
3. **نمایش اطلاعات روی OLED** در دو بخش:
 - بخش بالایی (زرد): دما + شاخص گرما  
 - بخش پایینی (آبی): رطوبت  
4. **چاپ داده‌ها در سریال مانیتور** برای بررسی و دیباگ.  

---

## 🧩 توضیح بخش‌های کد
- **کتابخانه‌ها**:  
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>
````

برای ارتباط I2C با OLED و خواندن سنسور DHT22.

* **تعریف پایه‌ها**:

  ```cpp
  #define OLED_SDA 5
  #define OLED_SCL 4
  #define DHT_PIN  13
  ```

  این پایه‌ها طبق سیم‌کشی تنظیم شده‌اند.

* **نمایش روی OLED**:
  داده‌ها به صورت **باکس‌بندی و دسته‌بندی** شده‌اند تا هم‌پوشانی ایجاد نشود.

* **سریال مانیتور**:

  ```
  Temperature: 25.60 C | Humidity: 40.25 %
  ```

---

## 🚧 مشکلات و نحوه رفع آن‌ها

در حین انجام پروژه با مشکلات زیر برخورد کردیم:

* ❌ **خطای اتصال ESP32 (Failed to connect)**
  ✅ حل: نگه داشتن دکمه `BOOT` هنگام آپلود و سپس رها کردن.

* ❌ **همپوشانی نوشته‌ها روی OLED**
  ✅ حل: تغییر سایز فونت‌ها، تقسیم‌بندی دقیق صفحه و استفاده از خطوط جداکننده.

* ❌ **نمایش ناقص یا ناخوانا**
  ✅ حل: استفاده از باکس‌بندی و محدود کردن حداکثر سایز فونت به 3.

---

## 🎯 نتیجه نهایی

📊 با اجرای پروژه:

* دما، رطوبت و شاخص گرما به صورت خوانا روی OLED نمایش داده می‌شوند.
* داده‌ها در سریال مانیتور نیز قابل مشاهده هستند.
* پروژه کاملاً پایدار است و در هر ۲ ثانیه مقادیر جدید را به‌روزرسانی می‌کند.

---

## 👨‍💻 توسعه‌دهنده

* 🔹 **Mehrdad**
* 📍 Shiraz, Iran

---


---

می‌خوای من همینو بهت فایل `README.md` آماده کنم تا مستقیم بذاری تو گیت؟
```
