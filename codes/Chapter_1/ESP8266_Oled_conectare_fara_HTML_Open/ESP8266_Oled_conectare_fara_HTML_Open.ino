/*
 * https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html
 * merge cu ESP8266, generaza AP cu numele ESP8266 AP Open
 * si parola 12345678 nu trebuie pentru open
 * daca nu este nimic conectata pe monitor apare zero
 * daca conectez telefonul la acest AP
 * pe monitor apare 1
 * daca deconectez telefonula apare zero
 * nu trebuie IP 
 * Then take your mobile phone or a PC, 
 * open the list of available access points, 
 * find ESPsoftAP_01 and connect to it. 
 * This should be reflected on serial monitor 
 * as a new station connected:
 * SDA pe D2
 * SCK pe D1
 * alim +3V
 * si gnd
 */
 

//#include "WiFi.h"
#include <ESP8266WiFi.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

void setup()
{
  Serial.begin(115200);


display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 AP Open");
  
  display.display();
  
  Serial.println();

  Serial.print("Setting soft-AP ... ");
  //boolean result = WiFi.softAP("ESPsoftAP_01", "pass-to-soft-AP");
  //boolean result = WiFi.softAP("ESPsoftAP_01", "12345678");
  int result = WiFi.softAP("ESP8266 AP Open");
 //nu am precizat password
 //merge direct, adica OPEN
  //merge si cu int in loc de boolean
 /* 
  if(result == true)
  {  
    Serial.println("Ready");     
  }
  else
  {
    Serial.println("Failed!");    
  }
  //merge si fara partea de sus
  */
}

void loop()
{
  Serial.printf("connection state = %d\n", WiFi.softAPgetStationNum());

display.clearDisplay();
display.setCursor(0,0);
display.print("connection state =");
  display.print(WiFi.softAPgetStationNum());
  display.display();
  delay(1000);

}
