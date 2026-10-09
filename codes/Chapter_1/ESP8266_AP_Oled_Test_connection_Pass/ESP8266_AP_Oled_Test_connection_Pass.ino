

#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char* ssid = "ESP8266 AP Pass SSID";
const char* password = "12345678";

void setup()
{
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 AP Pass SSID"); 
  display.display();
  
  Serial.println();
   boolean result = WiFi.softAP(ssid,password); 
  }

  void loop()
  {
  Serial.printf("connection state = %d\n", WiFi.softAPgetStationNum());
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("connection state =");  //optional
  display.print(WiFi.softAPgetStationNum());
  display.display();
  delay(1000);
  }
