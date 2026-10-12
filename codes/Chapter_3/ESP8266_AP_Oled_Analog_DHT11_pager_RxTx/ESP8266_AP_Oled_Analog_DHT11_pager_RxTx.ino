/*
  DHT 11 connected to gnd, +3.3V, GPIO 2= D4
  
 Oled connected: SDA to D2 SCK to D1
  
  generates Hot Spot AP with
  IP 192.168.4.1
  after upload, on Oled and Serial Monitor
  the IP address 192.169.4.1 appears
  Open Chrome on Android
  Enter 192.168.4.1/webserial
  apare pagina web
  everything edited  on the phone appears on Oled
 sends temperature, humidity data
 spre telefon
 Another phone can be connected with the same IP
 
*/
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

const char* ssid = "ESP8266-AP";  // Your WiFi AP SSID 
const char* password = "12345678"; // Your WiFi Password


#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

const int DHTPin = 2;   //DHT on pin D4
DHT dht(DHTPin, DHTTYPE);

int potpin0 = A0; // analog pin used to connect the potentiometer
  int val0 = 0; // variable initialized for storing potpin0 value

/* Message callback of WebSerial */
void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
    Serial.println(d);
    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Primit=");
  display.print(d);//displays transmitted text on oled
  display.display();
  }
  WebSerial.println(d);
}

void setup() {
    Serial.begin(115200);
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
     WebSerial.begin(&server);
     WebSerial.msgCallback(recvMsg);
    server.begin();
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 webserial IP=");
  
  display.print(IP);
  display.display();
  delay(5000);
}

void loop() {

  float analog = map(analogRead(potpin0), 0, 1023, 0, 179);                                              
  WebSerial.print("A=");
  WebSerial.print(analog); 
  WebSerial.println(" V");

  float temp = dht.readTemperature();
  WebSerial.print("T=");
  WebSerial.print(temp); 
  WebSerial.println(" C");
  
  float humi = dht.readHumidity();
  WebSerial.print("H=");
  WebSerial.print(humi); 
  WebSerial.println(" %");
  delay(2000); 
            }
