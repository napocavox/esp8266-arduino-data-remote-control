/*
  genereaza server Acces Point AP 
  with
  IP 192.168.4.1
   //biblio partial
   https://randomnerdtutorials.com/control-a-12v-lamp-via-sms-with-arduino/
  after upload, the IP address 192.169.4.1 appears on Oled and Serial monitor
  open Chrome on Android
  enter 192.168.4.1/webserial
  apare pagina web
  everything edited on the phone appears
  on Serial Monitor and on Oled

 controls RGB connected to D5=GPIO 12, D6, D7
 Servo to D4 =GPIO2
 servo controlled with predefined angles
 prin mesaje 20, 120, etc 
 spelling, uppercase and lowercase must be respected
sends data collected on pin A0
but only when
some text is sent from the phone
*/
#include <Servo.h>
Servo Servo0;

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

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

//String textMessage;
//String lampState = "HIGH";
const int led1 = 14;
const int led2 = 12;
const int led3 = 13;
int potpin0 = A0;

/* Message callback of WebSerial */

void recvMsg(uint8_t *data, size_t len){

  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
    Serial.println(d);
/////////////////////
if(d.indexOf("Led1on")>=0){
    digitalWrite(led1, HIGH);
    Serial.println("led1 set to ON"); //optional 
    d = "";   
  }

if(d.indexOf("Led1off")>=0){
    digitalWrite(led1, LOW);
    Serial.println("led1 set to OFF");  
    d = "";   
  }
//////////////////////////
if(d.indexOf("Led2on")>=0){
    digitalWrite(led2, HIGH);
    Serial.println("led2 set to ON");  
    d = "";   
  }

if(d.indexOf("Led2off")>=0){
    digitalWrite(led2, LOW);
    Serial.println("led2 set to OFF");  
    d = "";   
  }
///////////////////////////
if(d.indexOf("Led3on")>=0){
    digitalWrite(led3, HIGH);
//    lampState = "led3on";
    Serial.println("led3 set to ON");  
    d = "";   
  }

if(d.indexOf("Led3off")>=0){
    digitalWrite(led3, LOW);
    Serial.println("led3 set to OFF");  
    d = "";   
  }
    ///////////////////
if(d.indexOf("90")>=0){
    Servo0.write(90);
    Serial.println("servo 90");  
    d = "";   
  }
/////////////////
if(d.indexOf("20")>=0){
    Servo0.write(20);    
    d = "";   
  }
////////////////////
if(d.indexOf("120")>=0){
    Servo0.write(120);    
    d = "";   
  }
    ///////////////////////
    if(d.indexOf("170")>=0){
    Servo0.write(170);    
    d = "";   
    //d += char(data[i]);
  }
    ///////////////////////
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);//required
  display.setCursor(0,0);
  display.print("Primit=");
  display.print(d);//displays transmitted text on oled
  display.display();
  }
  WebSerial.println(d);
  //float analog = analogRead(A0);  //variant                                            // assign servo position to transmit packet variable.
  float analog = map(analogRead(potpin0), 0, 1023, 0, 3300);                        
  WebSerial.print("Us=");
  WebSerial.print(analog); 
  WebSerial.println(" mV");
}

void setup() {
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
Servo0.attach(2);
  
    Serial.begin(115200);
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    WebSerial.msgCallback(recvMsg);
    server.begin();
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 IP=");
  
  display.print(IP);
  display.print("/webserial");
  //display.print(WiFi.localIP());
  display.display();
  delay(2000);
}

void loop() {
  
}
