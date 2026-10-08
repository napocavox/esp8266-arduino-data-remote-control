/*
 * buton pe vrtual V13 led pe D13
 * feddback pe A)
 * gauge pe V3 pentru feedback min=0 max=1023
 * Oled pe SDA, SCL, GND si +3.3V
 */
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);


#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;

char ssid[] = "UPCF4821BC";
char pass[] = "password";



#define analogPin A0 
 int analog = 0;

BLYNK_WRITE(V6){ 

Serial.print(  "text=");
Serial.println( param.asStr());
display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.print("mesaj=");
  display.print(param.asStr());
  display.display();

}


//Get the button value

BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); 
}


 
void setup() {
  Serial.begin(115200);
  timer.setInterval(100L, sendUptime); 
  
  pinMode(13, OUTPUT); 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.print("Pager si comanda led cu feedback si Blynk");
  
  display.display();
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
  timer.run();
  
      }

      void sendUptime()
        {
    analog= analogRead(analogPin); 
      Blynk.virtualWrite(3, analog);
        }
