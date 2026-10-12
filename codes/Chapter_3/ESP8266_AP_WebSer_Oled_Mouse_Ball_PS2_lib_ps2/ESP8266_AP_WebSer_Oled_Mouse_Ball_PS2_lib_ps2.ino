
//displays the coordinates only when it moves
//when it stops they return to zero

 //requires the PS2 mouse library
 //but I must use a logic level converter
 //LV to +3v. HV to +5v  the VU pin of the ESP8266
 //LV1 to D4, Lv2 to D3,
 //HV1 to mouse Clk,

#include "PS2Mouse.h"
//#define DATA_PIN 4
//#define CLOCK_PIN 5

//#define DATA_PIN 0    //D3 also works this way
//#define CLOCK_PIN 2   //D4

#define DATA_PIN 2    //D3 also works this way
#define CLOCK_PIN 0   //D4

PS2Mouse mouse(CLOCK_PIN, DATA_PIN);

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);


#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

const char* ssid = "ESP8266-AP"; // Your WiFi AP SSID 
const char* password = "12345678"; // Your WiFi Password

/*
void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
    Serial.println(d);
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);//required
  display.setCursor(0,0);
  display.print("Primit=");
  display.print(d);//displays transmitted text on oled
  display.display();
  delay(2000);
  }
  WebSerial.println(d);
}
*/
////the function above blocks the server and it must be reconnected
   
void setup() {
  Serial.begin(9600);
  mouse.initialize();display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);

  WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    //WebSerial.msgCallback(recvMsg);
    //the function above blocks the server and it must be reconnected
    
    server.begin();
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 webserial IP=");
  
  display.print(IP);
  //display.print(WiFi.localIP());
  display.display();
  delay(2000);
}

void loop() {
    MouseData data = mouse.readData();
    Serial.print(data.status, BIN);
    Serial.print("\tx=");
    Serial.print(data.position.x);
    Serial.print("\ty=");
    Serial.print(data.position.y);
    Serial.print("\twheel=");
    Serial.print(data.wheel);
    Serial.println();

      WebSerial.print("x=");
      WebSerial.println(data.position.x);

      WebSerial.print("y=");
      WebSerial.println(data.position.y);
      
      WebSerial.print("wheel=");
      WebSerial.println(data.wheel);
    delay(20);

    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("x=");
  display.println(data.position.x);

  display.print("y=");
  display.println(data.position.y);

  display.print("wheel=");
  display.print(data.wheel);
  
  //display.print(WiFi.localIP());
  display.display();
  delay(1000);
}
