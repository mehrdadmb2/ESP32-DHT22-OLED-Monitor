[![GitHub repo](https://img.shields.io/badge/GitHub-Repository-blue?logo=github)](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor)
[![Platform](https://img.shields.io/badge/Platform-ESP32-green?logo=espressif)](https://www.espressif.com/)
[![Language](https://img.shields.io/badge/Language-C++-blue?logo=arduino)](https://www.arduino.cc/)

---

# 📟 ESP32 DHT22 OLED Monitor

## 📖 معرفی پروژه

این پروژه برای **نمایش دما و رطوبت محیط** با استفاده از سنسور **DHT22** و نمایشگر **OLED SSD1306** روی برد **ESP32** طراحی شده است.
اطلاعات به صورت **زیبا، دسته‌بندی‌شده و خوانا** روی صفحه نمایش داده می‌شوند و همزمان در سریال مانیتور نیز چاپ می‌شوند.

🔗 لینک ریپوزیتوری:
[ESP32-DHT22-OLED-Monitor](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor)

---

## ⚙️ سخت‌افزار مورد نیاز

برای اجرای این پروژه نیاز به قطعات زیر دارید:

* 🔌 **برد ESP32** (مثلاً Wemos D1 R32 یا هر ماژول توسعه ESP32 دیگر)
* 🌡️ **سنسور DHT22** (برای دما و رطوبت)
* 🖥️ **نمایشگر OLED SSD1306 (128x64, I2C)**
* 🧵 سیم جامپر (Male-Female)
* ⚡ کابل USB برای اتصال ESP32 به کامپیوتر

---

## 🛠️ نرم‌افزارهای مورد نیاز

1. **Arduino IDE** — از سایت رسمی دانلود و نصب کن. (Windows / macOS / Linux)
2. **اضافه کردن پشتیبانی ESP32** به Arduino IDE با استفاده از "Additional Boards Manager URL" (آدرس دقیق در ادامه داده شده).
3. **نصب کتابخانه‌ها** از طریق Library Manager:

   * **Adafruit SSD1306**
   * **Adafruit GFX Library**
   * **DHT sensor library for ESPx** (یا DHTesp)

---

## 🔽 لینک‌های مفید (مرجع دانلود)

* Arduino IDE: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
* ESP32 boards URL (برای اضافه کردن در Arduino IDE -> File -> Preferences -> Additional Boards Manager URLs):

```
https://dl.espressif.com/dl/package_esp32_index.json
```

* CP210x USB-to-UART driver (اگر برد شما از CP2102 استفاده می‌کند): [https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

---

## 🔌 نحوه سیم‌کشی (Wiring)

اتصالات سخت‌افزاری مطابق جدول زیر انجام می‌شود (مطابق با کد این پروژه):

| ESP32 Pin | وظیفه              |
| --------- | ------------------ |
| GPIO 5    | OLED SDA           |
| GPIO 4    | OLED SCL           |
| 3.3V      | OLED VCC / DHT VCC |
| GND       | OLED GND / DHT GND |
| GPIO 13   | DHT22 Data         |

> نکته: بعضی از ماژول‌های OLED دارای پایه‌های متفاوت یا برچسب متفاوت هستند. همیشه با دیتاشیت مطمئن شو.
datasheet:
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/com-03-071-new-8.jpg)

📸 تصاویر پروژه (بخش Pic):
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/1.jpg)
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/2.jpg)
![Setup](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/Pic/3.jpg)

---

## ✅ فایل کد پروژه

فایل اصلی در ریپوزیتوری:
👉 [ESP32_Temp.ino](https://github.com/mehrdadmb2/ESP32-DHT22-OLED-Monitor/blob/main/ESP32_Temp.ino)

عملکرد کلی کد:

1. **خواندن دما و رطوبت** از سنسور DHT22.
2. **محاسبه Heat Index (احساس واقعی دما)** و نمایش آن.
3. **نمایش اطلاعات روی OLED** در دو بخش:

* بخش بالایی: دما + "feels like" (Heat Index)
* بخش پایینی: رطوبت

4. **چاپ داده‌ها در سریال مانیتور** برای بررسی و دیباگ.

---

## 🧩 توضیح بخش‌های کد (قدم‌به‌قدم برای مبتدی‌ها)

### 1) نصب Arduino IDE و آماده‌سازی اولیه

1. وارد سایت Arduino شو و نسخه مربوط به سیستم‌عاملت رو دانلود و نصب کن.
2. بعد از اجرا، از منوی **File > Preferences** باز کن.
3. در فیلد **Additional Boards Manager URLs** آدرس زیر رو اضافه کن:

```
https://dl.espressif.com/dl/package_esp32_index.json
```

4. سپس به **Tools > Board > Boards Manager** برو، عبارت "esp32" رو جستجو کن و پکیج رسمی Espressif رو نصب کن.

### 2) نصب درایور CP2102 (در صورت نیاز)

* اگر وقتی برد رو وصل می‌کنی درایور نصب نمیشه یا پورت COM نمایش داده نمیشه، احتمالاً برد از چیپ CP210x استفاده می‌کنه. درایور CP210x رو از سایت Silicon Labs دانلود و نصب کن (Windows: نصب exe، macOS: pkg، Linux: udev rule).
* بعد از نصب، برد رو وصل کن و در **Device Manager** یا با `ls /dev/tty*` بررسی کن که پورت ظاهر شده.

### 3) نصب کتابخانه‌ها

* Arduino IDE رو باز کن: **Sketch > Include Library > Manage Libraries...**
* هر کدام از این کتابخانه‌ها را جستجو و نصب کن:

  * **Adafruit SSD1306**
  * **Adafruit GFX Library**
  * **DHT sensor library for ESPx** یا **DHTesp**

> نکته: اگر چند نسخه از یک کتابخانه موجود بود، آخرین نسخه پایدار را نصب کن.

### 4) انتخاب برد و پورت در Arduino IDE

* از منوی **Tools > Board**، برد مناسب مثل "Wemos D1 R32" یا "ESP32 Dev Module" رو انتخاب کن.
* سپس از **Tools > Port** پورت مربوط به برد (مثلاً COM3، /dev/ttyUSB0) رو انتخاب کن.

### 5) آماده‌سازی برای آپلود: دکمه BOOT/EN

* برخی بردها برای آپلود نیاز دارند که دکمه "BOOT" رو نگه داری تا عملیات شناسایی انجام بشه. اگر در آپلود با خطای ارتباط مواجه شدی، هنگام شروع آپلود دکمه BOOT را نگه دار تا آپلود شروع شود، سپس بعد از شروع ریست، دکمه را رها کن.

### 6) آپلود اولین برنامه (Blink test)

* قبل از آپلود کد اصلی، برای تست پورت و برد، یک برنامه ساده مثل Blink را آپلود کن و مطمئن شو که LED روی برد چشمک میزنه. این قدم خیلی مهمه تا مطمئن شیم اوّل چیزها درست نصب شده.

---

## 🐞 رفع مشکلات رایج (Troubleshooting)

**خطا: "A fatal error occurred: Failed to connect to ESP32: Timed out"**

* راه حل‌ها:

  * دکمه BOOT را هنگام آپلود نگه دار و بعد از شروع رها کن.
  * کابل USB را عوض کن (برخی کابل‌ها فقط شارژ هستند و دیتا ندارند).
  * در Device Manager بررسی کن که درایور CP210x نصب شده باشد.
  * پورت COM صحیح را انتخاب کرده باشی.

**خطا: "espcomm_open failed" یا "espcomm_upload_mem failed"**

* معمولاً مشکل پورت یا درایور است، یا نیاز به فشردن BOOT/EN دارد.

**خواندن نادرست از سنسور (NaN)**

* ممکن است سیم‌کشی درست نباشد.
* ولتاژ تغذیه را بررسی کن (DHT22 نیاز به 3.3V یا 5V دارد، با برد ESP32 از 3.3V استفاده کن).
* اگر خطا موقتیه، در کد یک retry اضافه شده که تا سه بار تلاش می‌کنه.

**نمایش ناقص روی OLED**

* آدرس I2C ممکن است متفاوت باشد (معمولاً 0x3C یا 0x3D). اگر نمایشگر چیزی نشان نمیدهد، آدرس را چک کن یا از I2C scanner استفاده کن.

---

## 🔧 نکات فنی و پیشنهادات توسعه

* اگر می‌خوای دیتا رو لاگ کنی، می‌تونی هر دو ثانیه دیتا رو در یک فایل CSV روی SD ذخیره کنی یا با ESP-NOW / MQTT به یک سرور بفرستی.
* پیشنهاد بهبود UI: اضافه کردن آیکون وضعیت سنسور، smoothing برای داده‌ها، و قابلیت تغییر بازه خواندن از طریق منوی لمسی یا دکمه.

---

## 🎯 نتیجه نهایی

با اجرای پروژه:

* دما، رطوبت و شاخص گرما (Feels like) به صورت خوانا روی OLED نمایش داده می‌شوند.
* داده‌ها در سریال مانیتور نیز قابل مشاهده هستند.
* پروژه کاملاً پایدار است و در هر ۲ ثانیه مقادیر جدید را به‌روزرسانی می‌کند.

---

## 👨‍💻 توسعه‌دهنده

* 🔹 **Mehrdad**
* 📍 Shiraz, Iran

---

## 💾 کد به‌روز شده (ESP32_Temp.ino)

```
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>

// Pin config
#define OLED_SDA 5
#define OLED_SCL 4
#define DHT_PIN  13
#define DHT_TYPE DHTesp::DHT22

// Display config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHTesp dht;

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL_MS = 2000;

// helper functions
inline int fontHeight(int size){ return 8 * size; }
inline int fontCharWidth(int size){ return 6 * size; }

int centerX(const char* txt, int size){
  int w = strlen(txt) * fontCharWidth(size);
  return (SCREEN_WIDTH - w) / 2;
}

void drawDegree(int16_t x, int16_t y, int16_t r){
  display.fillCircle(x, y, r, SSD1306_WHITE);
}

// Compute heat index (feels like) using NOAA formula (convert to F, compute, back to C)
float computeHeatIndexC(float tempC, float hum){
  if (isnan(tempC) || isnan(hum)) return NAN;
  float T = tempC * 9.0 / 5.0 + 32.0; // to F
  float R = hum;
  float HI = -42.379 + 2.04901523 * T + 10.14333127 * R - 0.22475541 * T * R
             - 6.83783e-3 * T * T - 5.481717e-2 * R * R
             + 1.22874e-3 * T * T * R + 8.5282e-4 * T * R * R
             - 1.99e-6 * T * T * R * R;
  // Adjustment for low humidity or low temp is skipped for simplicity
  float hic = (HI - 32.0) * 5.0 / 9.0; // back to C
  return hic;
}

void renderUI(float temperature, float humidity, float heatIndex, bool ok){
  display.clearDisplay();

  // -------- Temperature (TOP) --------
  const int topBoxH = 32;
  display.drawLine(0, topBoxH, SCREEN_WIDTH, topBoxH, SSD1306_WHITE);

  // Label
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  int tLabelX = centerX("Temperature", 1);
  display.setCursor(tLabelX, 2);
  display.print("Temperature");

  // Value
  char tbuf[16];
  if (!isnan(temperature)) snprintf(tbuf, sizeof(tbuf), "%.1f", temperature);
  else strcpy(tbuf, "--.-");

  display.setTextSize(2); // big number
  int tValX = centerX(tbuf, 2);
  display.setCursor(tValX, 14);
  display.print(tbuf);

  // degree symbol + C
  int tValW = strlen(tbuf) * fontCharWidth(2);
  int degX = tValX + tValW + 4;
  int degY = 20;
  drawDegree(degX, degY, 2);
  display.setTextSize(1);
  display.setCursor(degX + 6, 18);
  display.print("C");

  // Feels like (heat index) - smaller text under temperature
  char fibuf[20];
  if (!isnan(heatIndex)) snprintf(fibuf, sizeof(fibuf), "Feels: %.1f C", heatIndex);
  else strcpy(fibuf, "Feels: --.- C");
  display.setTextSize(1);
  int fiX = centerX(fibuf, 1);
  display.setCursor(fiX, 30);
  display.print(fibuf);

  // -------- Humidity (BOTTOM) --------
  display.setTextSize(1);
  int hLabelX = centerX("Humidity", 1);
  display.setCursor(hLabelX, topBoxH + 4);
  display.print("Humidity");

  char hbuf[16];
  if (!isnan(humidity)) snprintf(hbuf, sizeof(hbuf), "%.1f", humidity);
  else strcpy(hbuf, "--.-");

  display.setTextSize(2);
  int hValX = centerX(hbuf, 2);
  display.setCursor(hValX, topBoxH + 16);
  display.print(hbuf);

  int hValW = strlen(hbuf) * fontCharWidth(2);
  display.setTextSize(1);
  display.setCursor(hValX + hValW + 6, topBoxH + 20);
  display.print("%");

  // status icon (ok / fail)
  if (ok){
    // small check mark
    display.setCursor(2, SCREEN_HEIGHT - 10);
    display.setTextSize(1);
    display.print("OK ✅");
  } else {
    display.setCursor(2, SCREEN_HEIGHT - 10);
    display.setTextSize(1);
    display.print("Sensor ERROR ⚠️");
  }

  display.display();
}

void setup(){
  Serial.begin(115200);
  delay(100);
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  display.clearDisplay();
  display.display();

  Serial.println("ESP32 + DHT22 started...");
  dht.setup(DHT_PIN, DHT_TYPE);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Booting...");
  display.display();
  delay(500);
}

void loop(){
  unsigned long now = millis();
  if (now - lastRead >= READ_INTERVAL_MS){
    lastRead = now;
    float humidity = NAN;
    float temperature = NAN;
    bool ok = false;

    // retry logic: up to 3 attempts
    const int maxAttempts = 3;
    for (int attempt = 0; attempt < maxAttempts; attempt++){
      humidity = dht.getHumidity();
      temperature = dht.getTemperature();
      if (!isnan(humidity) && !isnan(temperature)){
        ok = true;
        break;
      }
      delay(200);
    }

    float heatIndex = NAN;
    if (ok) {
      heatIndex = computeHeatIndexC(temperature, humidity);
      Serial.printf("T: %.2f C | H: %.2f %% | Feels: %.2f C\n", temperature, humidity, heatIndex);
    } else {
      Serial.println("Sensor read failed after retries.");
    }

    renderUI(temperature, humidity, heatIndex, ok);
  }
}
```

---

## 📝 نکات نهایی
.Sketch uses 323304 bytes (24%) of program storage space. Maximum is 1310720 bytes.
Global variables use 23692 bytes (7%) of dynamic memory, leaving 303988 bytes for local variables. Maximum is 327680 bytes.

A fatal error occurred: Could not open COM3, the port is busy or doesn't exist.
(could not open port 'COM3': FileNotFoundError(2, 'The system cannot find the file specified.', None, 2))

Hint: Check if the port is correct and ESP connected

esptool v5.1.0
Serial port COM3:
Failed uploading: uploading error: exit status 2
Thought for 5s

عالی — خطا رو خوندَم. این خطای “Could not open COM3, the port is busy or doesn't exist” یعنی آردوینو/esptool نمیتونه پورت سریال رو باز کنه. زیر با یک چک‌لیست قدم‌به‌قدم و عملی می‌ذارم که سریع و تضمینی مشکل رو پیدا و رفع کنی — آخرش هم کد کاملِ به‌روز‌شده رو هم می‌ذارم (بدون کم و کسر). بیخیال حرف اضافه، مستقیم میریم سر اصل مطلب 😎

1) چک‌لیست سریع — 10 ثانیه‌ای (قبل از هر چیز)

کابل USB رو عوض کن (حتماً کابل دیتا باشه، بعضی کابل‌ها فقط شارژن).

برد رو از USB جدا کن و دوباره وصل کن. پورت USB دیگه (مستقیم کامپیوتر، نه هاب) رو امتحان کن.

Arduino IDE را ببند و دوباره باز کن. قبل از آپلود، Serial Monitor رو ببند.

کامپیوتر رو یک‌بار ریست کن (اگر وقت داری؛ خیلی مواقع حل می‌کنه).

اگر هنوز مشکل بود، ادامه بده.

2) بررسی اینکه پورت واقعاً وجود دارد یا نه
Windows

باز کن Device Manager → بخش Ports (COM & LPT) ببین آیا چیزی (مثل CP210x USB to UART یا USB Serial (COMx)) لیست شده یا نه.

یا در CMD اجرا کن:

wmic path Win32_SerialPort get DeviceID,Caption


یا در PowerShell:

Get-WmiObject Win32_SerialPort | Format-Table DeviceID,Caption


اگر چیزی نمایش داده نمیشه → یعنی درایور نصب نیست یا برد شناخته نشده.

Linux / macOS

در ترمینال:

ls /dev/ttyUSB* /dev/ttyACM* /dev/tty.* 2>/dev/null


اگر لیستی نشون نداد، برد شناسایی نشده.

3) اگر پورت نمایش داده نمی‌شود → درایور

چیپ USB-to-UART رایج: CP210x (Silicon Labs) یا CH340 (WCH).

نصب درایور مناسب:

CP210x → دانلود از سایت Silicon Labs (CP210x VCP driver).

CH340 → درایور CH340 (WCH).
(بعد از نصب، برد رو دوباره وصل و Device Manager رو چک کن.)

4) اگر پورت هست ولی باز نمی‌شود (port busy)

از Arduino IDE: مطمئن شو Tools > Port پورت صحیح (مثلاً COM3) انتخاب شده.

ببند هر برنامه‌ای که ممکنه پورت رو گرفته باشه (Serial Monitor، VSCode + PlatformIO، Putty، Node/serial برنامه‌ها، نرم‌افزارهای موبایل که USB رو میکشن).

در ویندوز: برنامه‌ای ممکنه پورت رو قفل کرده باشه. راه‌حل‌ها:

بستن نرم‌افزارهایی که ممکنه پورت استفاده کنند.

باز کردن Task Manager و بستن فرایندهای مشکوک (مثلاً برنامه‌های ترمینال).

اگر می‌خوای دقیق‌تر بدونی چه پردازشی پورت رو گرفته: از Process Explorer یا Sysinternals Handle استفاده کن (پیشرفته).

سپس دوباره آپلود کن.

5) تست سرعتِ اتصال / دسترسی (گزینه سریع)

از یک ابزار ساده که پورت‌ها رو لیست می‌کنه استفاده کن (مثلاً دستور بالا یا python -m serial.tools.list_ports اگر پایتون داری).

اگر پورت تغییر کرده (مثلاً از COM3 به COM6) حتماً در Tools > Port آردوینو هم همون رو انتخاب کن.

6) اگر موقع آپلود با "Failed to connect" مواجه میشی — روش فشردن BOOT/EN

برخی بردها نیاز دارن BOOT / EN (RESET) موقع آپلود استفاده بشه:

در Arduino IDE روی Upload کلیک کن.

اگر آپلود خطا داد و منتظر هست برای ارتباط، دکمه BOOT روی برد رو نگه دار.

وقتی پیام «Connecting…» یا تلاش برای باز شدن پورت اومد، دکمه رو رها کن (یا بالعکس روی بعضی بردها: نگه دار تا آپلود شروع شه، بعد رها کن).

اگر بردت دکمه EN داره: گاهی یکبار زدن EN/RST قبل از آپلود کمک می‌کنه.

(هر برد متفاوته؛ تجربه کن: معمولاً نگه داشتن BOOT هنگام شروع آپلود جواب میده.)

7) دسترسی و پرمیشن‌ها (Windows)

اجرای Arduino IDE به صورت Run as Administrator گاهی کمک می‌کنه.

آنتی‌ویروس/Firewall بعضی‌وقت‌ها مانع باز شدن پورت میشه — موقتا غیرفعال کن و امتحان کن.

8) USB hub یا کابل بد = علت خیلی شایع

اگر از هاب USB استفاده می‌کنی، برد رو مستقیم به پورت پشت کیس بزن.

کابل‌های فِرِی بازار: خیلی از کابل‌ها دیتا ندارن. حتماً کابل دیگه تست کن.

9) خطاهای ویژه esptool / خروجی کامل

اگر خروجی مثل این دیدی:

esptool v5.1.0
Serial port COM3:
Failed uploading: uploading error: exit status 2


یعنی esptool نتونسته پورت رو باز کنه — یکی از موارد بالا علتش هست (پورت وجود نداره، اشغال شده، یا درایور نصب نشده).

10) اگر تمام موارد بالا رو انجام دادی و هنوز مشکل هست — آخرین مراحلی که من همیشه انجام میدم

برد رو از USB جدا کن.

نصب کامل درایور CP210x یا CH340 دوباره (uninstall + reinstall از Device Manager).

امتحان کردن برد روی یک کامپیوتر دیگه (اگر ممکنه) — اگر روی سیستم دیگه شناسایی شد یعنی مشکل سیستم/درایور خودته.

اگر برد از قبل کار می‌کرد و ناگهان خطا داد: یک ری‌استارت ساده ویندوز معمولاً پورت رو آزاد می‌کنه.

چند فرمان مفید برای تشخیص سریع (کپی-پیست)
Windows (CMD)
wmic path Win32_SerialPort get DeviceID,Caption

PowerShell
Get-WmiObject Win32_SerialPort | Format-Table DeviceID,Caption

Linux / macOS
ls /dev/ttyUSB* /dev/ttyACM* /dev/tty.* 2>/dev/null

خلاصه‌ی پیشنهادیِ فوری (Do this now)

Arduino IDE رو ببند و Serial Monitor رو ببند.

کابل USB رو عوض کن و مستقیماً به پورت کامپیوتر وصل کن.

Device Manager رو باز کن و دنبال COM باش. اگر نبود، درایور CP210x یا CH340 نصب کن.

دوباره Arduino IDE باز کن، برد مناسب و پورت صحیح رو انتخاب کن، و آپلود کن (اگه لازم شد BOOT رو نگه دار).
۵. اگه هنوز نه: ریستارت کن.

---

### منابع و قطعات پیشنهادی

* [https://thecaferobot.com/store/female-female-40p-21cm](https://thecaferobot.com/store/female-female-40p-21cm)
* [https://thecaferobot.com/store/dht22-digital-temperature-and-humidity-sensor](https://thecaferobot.com/store/dht22-digital-temperature-and-humidity-sensor)
* [https://thecaferobot.com/store/esp32-wemos-oled-wifi-bluetooth-development-board](https://thecaferobot.com/store/esp32-wemos-oled-wifi-bluetooth-development-board)
