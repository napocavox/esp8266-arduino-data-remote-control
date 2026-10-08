/*
 * ESP8266 Servo Motor Control With Web Server 
 * https://circuits4you.com
 * servo pe D3 =GPIO 0
 * merge prin router local
 * https://circuits4you.com/2019/01/12/esp8266-servo-motor-control/
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
//#include <Servo.h>

#include "camera_index.h"

const char* ssid = "nume router";
const char* password = "password";


ESP8266WebServer server(80);
#define RECEIVER      2  
//#include <ESP8266WiFi.h>
#include <RFM69.h>    // apelare librării
#include <SPI.h>      // apelare librării
#define NETWORKID       0     // aceeaşi pentru ambele noduri
#define MYNODEID        1     // adresa  ID a primului nod
#define TONODEID        2     // adresa ID a celui de al doilea nod 
//#define FREQUENCY     RF69_868MHZ   //setare frecvenţă
#define FREQUENCY     RF69_433MHZ

#define ENCRYPT       true  
#define ENCRYPTKEY    "TOPSECRETPASSWRD" 
//stabilire password, 16-byte, acelaşi pentru ambele noduri
#define USEACK        true    
// activare funcţia de confirmare (ACK)

#define IS_RFM69HCW   true 
// set to 'true' if you are using an RFM69HCW module
#define SERIAL_BAUD   115200

#if defined(ESP8266)
#define RFM69_CS      15  // GPIO15/HCS/D8
#define RFM69_IRQ     4   // GPIO04/D2    
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ)
#define RFM69_RST     2   // GPIO02/D4    
#define LED           0   // GPIO00/D3, onboard blinky for Adafruit Huzzah
#endif

RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);

  int potpin0 = A0; // analog pin used to connect the potentiometer
  //int val0 = 0; // variable initialized for storing potpin0 value

 typedef struct 
 {    
   int Pot_0;   //create transmit variable & store data potentiometer 0 data
 } 
 Payload;
 Payload theData; 
//================================================
void handleServo(){
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();
  theData.Pot_0 = pos;
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  //digitalWrite(LED,!(digitalRead(LED))); //Toggle LED
  server.send(200, "text/plane","");
}

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

 // pinMode(LED,OUTPUT);
  //myservo.attach(ServoPin); // attaches the servo on GIO2 to the servo object
  
  //Connect to wifi Network
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  //Initialize Webserver
  server.on("/",handleRoot);
  server.on("/setPOS",handleServo); //Sets servo position from Web request
  server.begin();  
  delay(2000);
  ////////////////

  Serial.begin(SERIAL_BAUD);//adaugat pentru ESP8266
  // Hard Reset the RFM module
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, HIGH);
  delay(100);
  digitalWrite(RFM69_RST, LOW);
  delay(100);

  if (!radio.initialize(FREQUENCY,MYNODEID,NETWORKID)) {
    Serial.println("radio.initialize failed!");
  }
  if (IS_RFM69HCW) {
    radio.setHighPower();    // Only for RFM69HCW & HW!
  }
  radio.setPowerLevel(31); // power output ranges from 0 (5dBm) to 31 (20dBm)


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
  radio.encrypt(ENCRYPTKEY);    // activare criptare, modul (AES)

  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff);
      }


void loop() {
 server.handleClient();
 for (byte i = 0; i < radio.DATALEN; i++)
    Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");
    Serial.print(radio.readRSSI());Serial.print("]");
    Serial.println();
    //partea de sus este optionala
    
    //normalizare valori pentru servomotor.    
    //theData.Pot_0 = map(analogRead(potpin0), 0, 1023, 0, 179);                                              // assign servo position to transmit packet variable.
    //Serial.println(theData.Pot_0);
 
    radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  

    Serial.print("Sending struct (");
    Serial.print(sizeof(theData));
    Serial.println(" bytes) ");
    Serial.println();
  delay(500);
}
