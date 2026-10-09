

 //requires the PS2 mouse library
 //requires a logic level converter
 //LV to +3v. HV to +5v  the VU pin of the Node)
 //LV1 to D4, Lv2 to D3,
 //HV1 to mouse Clk,

#include "PS2Mouse.h"

//#define DATA_PIN 0    //D3 
//#define CLOCK_PIN 2   //D4

#define DATA_PIN 2    //D4 
#define CLOCK_PIN 0   //D3

PS2Mouse mouse(CLOCK_PIN, DATA_PIN);

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
  
void setup() {
  Serial.begin(9600);
  mouse.initialize();

  WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    server.begin();   
    delay(1000);
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
    
  delay(1000);
}
