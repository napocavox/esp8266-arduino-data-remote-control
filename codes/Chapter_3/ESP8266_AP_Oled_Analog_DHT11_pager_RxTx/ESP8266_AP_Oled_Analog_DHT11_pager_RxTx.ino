/*
  DHT 11 conectat la gnd, +3.3V, GPIO 2= D4
  
 Oled conectat: SDA la D2 SCK la D1
  
  genereaza Hot Spot AP cu 
  IP 192.168.4.1
  dupa incarcare pe Oled si Serial Monitor 
  apare adresa IP 192.169.4.1
  Se deschide pe Android Chrome
  Se introdice 192.168.4.1/webserial
  apare pagina web
  tot ce se editeaza  pe telefon apare pe Oled
 trimite datele de temperatura, umiditata 
 spre telefon
 Se poate conecta inca un telefon cu acelasi IP
 
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

const int DHTPin = 2;   //DHT la pin D4
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
  display.print(d);//afiseaza text tranmmsis pe oled
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
