/*
 * https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-examples.html
 * works with ESP8266, generates AP named ESP8266 AP Open
 * and password 12345678 not needed for open
 * if nothing is connected, zero appears on the monitor
 * if I connect the phone to this AP
 * 1 appears on the monitor
 * if I disconnect the phone, zero appears
 * no IP needed
 * Then take your mobile phone or a PC, 
 * open the list of available access points, 
 * find ESPsoftAP_01 and connect to it. 
 * This should be reflected on serial monitor 
 * as a new station connected:
 * SDA on D2
 * SCK on D1
 * alim +3V
 * and gnd
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
 //I did not specify a password
 //works directly, i.e. OPEN
  //also works with int instead of boolean
 /* 
  if(result == true)
  {  
    Serial.println("Ready");     
  }
  else
  {
    Serial.println("Failed!");    
  }
  //also works without the part above
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
