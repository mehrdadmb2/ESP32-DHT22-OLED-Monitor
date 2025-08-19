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

void renderUI(float temperature, float humidity, bool ok){
  display.clearDisplay();

  // -------- Temperature (TOP / YELLOW AREA) --------
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

  // -------- Humidity (BOTTOM / BLUE AREA) --------
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
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    bool ok = !isnan(humidity) && !isnan(temperature);

    if (ok) Serial.printf("T: %.2f C | H: %.2f %%\n", temperature, humidity);
    else Serial.println("Sensor read failed.");

    renderUI(temperature, humidity, ok);
  }
}
