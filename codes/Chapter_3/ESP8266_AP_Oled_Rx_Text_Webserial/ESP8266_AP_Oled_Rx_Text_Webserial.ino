/*
  generates Access Point server with
  IP 192.168.4.1
   
  after upload, on Oled and
  Serial monitor the IP address 192.169.4.1 appears
  Open a Chrome page on Android
  and enter 192.168.4.1/webserial
  apare pagina web
  any text edited on the phone is displayed on Oled
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

const char* ssid = "ESP8266-AP";    
const char* password = "12345678"; 
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

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
  display.print(d);//displays transmitted text on Oled
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
}
