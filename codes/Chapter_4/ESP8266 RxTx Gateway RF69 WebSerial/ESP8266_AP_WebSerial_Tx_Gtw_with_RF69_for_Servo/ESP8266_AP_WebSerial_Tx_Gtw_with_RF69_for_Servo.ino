/*
  generates Hot Spot AP with
  IP 192.168.4.1
   //biblio partial
   https://randomnerdtutorials.com/control-a-12v-lamp-via-sms-with-arduino/
  after upload, the IP address 192.169.4.1 appears on Serial monitor
  open Chrome on Android
  enter 192.168.4.1/webserial
  apare pagina web
  type 20 on the phone
  sends angle 20 degrees for servo

  type 170 on the phone
  sends angle 170 degrees for servo
  
 controls servo from Rx
 
 spelling, uppercase and lowercase must be respected
  Checkout WebSerial Pro: https://webserial.pro
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

const char* ssid = "ESP8266-AP"; // Your WiFi AP SSID 
const char* password = "12345678"; // Your WiFi Password

#define RECEIVER      2  
#include <ESP8266WiFi.h>
#include <RFM69.h>    // apelare librării
#include <SPI.h>      // apelare librării
#define NETWORKID       0     // the same for both nodes
#define MYNODEID        1     // ID address of the first node
#define TONODEID        2     // ID address of the second node
//#define FREQUENCY     RF69_868MHZ   //setare frecvenţă
#define FREQUENCY     RF69_433MHZ

#define ENCRYPT       true  
#define ENCRYPTKEY    "TOPSECRETPASSWRD" 
//set password, 16-byte, the same for both nodes
#define USEACK        true    // enable the acknowledgment function (ACK)

#define IS_RFM69HCW   true // set to 'true' if you are using an RFM69HCW module
#define SERIAL_BAUD   115200

#if defined(ESP8266)
#define RFM69_CS      15  // GPIO15/HCS/D8
#define RFM69_IRQ     4   // GPIO04/D2    
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ)
#define RFM69_RST     2   // GPIO02/D4  
#define LED           0   // GPIO00/D3, 
#endif

RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);

 typedef struct 
 {    
   int Pot_0;   //create transmit variable & store data potentiometer 0 data
 } 
 Payload;
 Payload theData;  

void recvMsg(uint8_t *data, size_t len){

  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
    Serial.println(d);
    
if(d.indexOf("20")>=0){
    theData.Pot_0 =20;
        d = "";   
  }

if(d.indexOf("170")>=0){
      theData.Pot_0 =170 ;   
    d = "";   
  }
    
if(d.indexOf("120")>=0){   
      theData.Pot_0 =120 ;   
     d = "";   
  }
    
    if(d.indexOf("90")>=0){   
      theData.Pot_0 =90 ;   
     d = "";   
  }
  
  }
  WebSerial.println(d);
}

void setup() {

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
    delay(2000);
    ////////////////
    Serial.begin(SERIAL_BAUD);//added for ESP8266
// Hard Reset the RFM module
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, HIGH);
  delay(100);
  digitalWrite(RFM69_RST, LOW);
  delay(100);//added for ESP8266

  if (!radio.initialize(FREQUENCY,MYNODEID,NETWORKID)) {
    Serial.println("radio.initialize failed!");
  }
  if (IS_RFM69HCW) {
    radio.setHighPower();    // Only for RFM69HCW & HW!
  }
  radio.setPowerLevel(31); // power output ranges from 0 (5dBm) to 31 (20dBm)
//added for ESP8266

Serial.print("\nTransmitting at ");
  Serial.print(FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(" MHz");
  Serial.print("Network "); 
  Serial.print(NETWORKID);
  Serial.print(" Node "); 
  Serial.println(MYNODEID); 
  Serial.println();

Serial.print("Node ");  
Serial.print(MYNODEID,DEC);
Serial.println(" ready"); 

Serial.print("Node ");  

if (ENCRYPT)
radio.encrypt(ENCRYPTKEY);    // enable encryption, mode (AES)

char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff); 
}

void loop() 
{
    for (byte i = 0; i < radio.DATALEN; i++)
    Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");
    Serial.print(radio.readRSSI());Serial.print("]");
    Serial.println();
//the part above is optional
      radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  
 // Output to serial information of # bytes sent.
    Serial.print("Sending struct (");
    Serial.print(sizeof(theData));
    Serial.println(" bytes) ");   
    Serial.println();

  delay(1000);
  }
