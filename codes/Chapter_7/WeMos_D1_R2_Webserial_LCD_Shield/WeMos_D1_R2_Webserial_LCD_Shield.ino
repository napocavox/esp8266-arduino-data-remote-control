// LCD shield
//genereaza server Acces Point 
//cu IP 192.168.4.1/webserial
//afieaza tot ce se editeaza pe telefon
// **************************************************************/

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


#include <LiquidCrystal.h>

#define D0 3 // GPIO3 maps to Ardiuno D0
#define D1 1 // GPIO1 maps to Ardiuno D1
#define D2 16 // GPIO16 maps to Ardiuno D2
#define D3 5 // GPIO5 maps to Ardiuno D3
#define D4 4 // GPIO4 maps to Ardiuno D4
#define D5 14 // GPIO14 maps to Ardiuno D5
#define D6 12 // GPIO12 maps to Ardiuno D6
#define D7 13 // GPIO13 maps to Ardiuno D7
#define D8 0 // GPIO0 maps to Ardiuno D8
#define D9 2 // GPIO2 maps to Ardiuno D9
#define D10 15 // GPIO15 maps to Ardiuno D10



LiquidCrystal lcd(D8,D9,D4,D5,D6,D7); 

void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
    Serial.println(d);
   lcd.clear();
  lcd.setCursor(0,0);
  
  lcd.print("text=");
  lcd.print(d);
  }
  WebSerial.println(d);
}

void setup()
{  
  Serial.begin(9600);
   WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    WebSerial.msgCallback(recvMsg);
    server.begin();
  lcd.begin(16, 2);
  lcd.print("pager webserial"); 
  lcd.setCursor(0,2); 
  lcd.print(IP);
  delay(2000);
}


void loop()
{
  
}
