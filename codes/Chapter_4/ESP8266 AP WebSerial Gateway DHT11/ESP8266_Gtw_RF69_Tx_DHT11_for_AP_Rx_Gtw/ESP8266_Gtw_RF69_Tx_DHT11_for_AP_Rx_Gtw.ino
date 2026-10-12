/*
 * sends data via RF69 from A0 and DHT11
 * to
 * ESP8266_AP_WebSeial_Gtw_RF69_Rx_for_Tx_Gtw_DHT11
 Rx gateway with RF69 that sends via Webserial to the phone
 *Has nothing from WebSerial
 *DHT11 on pin D1=GPIO 5
 *
 * the modified library was used
 * RFM69(modified ESP8266)
 * Modificarea apare in fila CPP
 * //void RFM69::isr0() { _haveData = true; }//original


#if defined(ESP8266)
ICACHE_RAM_ATTR void RFM69::isr0() { _haveData =true; }
#else
void RFM69::isr0() { <what ever is specified in the currentversion>}
#endif
//modified

RF69 connection to ESP8266
RFM69HCW breakout ESP8266 NodeMCU ESP8266 Huzzah
VIN VU (5V) VBAT (5V)
GND     GND     GND
EN      n/c     n/c
NSS      D2 (GPIO04) 
SCK     D5 (GPIO14/HSCLK) GPIO14
MISO    D6 (GPIO12/HMISO) GPIO12
MOSI    D7 (GPIO13/HMOSI) GPIO13
CS      D8 (GPIO15/HCS) GPIO15 //I think it is NSS
RST     D4 (GPIO02) GPIO2
 */

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
//uint8_t DHTPin = 2; //DHT on D4
uint8_t DHTPin = 5; //DHT on D1
DHT dht(DHTPin, DHTTYPE);                


#define RECEIVER      2  

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
#define USEACK        true    
// enable the acknowledgment function (ACK)

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

 typedef struct 
 {    
    int SenzA_0;   
    int SenzT_0;  
    int SenzH_0;
    
 } 
 Payload;
 Payload theData; 
 Payload theDataA; 
 Payload theDataT;
 Payload theDataH;    
 
void setup()
{
  Serial.begin(SERIAL_BAUD);//added for ESP8266

  pinMode(DHTPin, INPUT);
  dht.begin();  
  
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
    Serial.print(radio.readRSSI());
    Serial.print("]");
    Serial.println();
    //the part above is optional
    
   
    //theData.Senz_0 = analogRead(A0);                                              // assign servo position to transmit packet variable.
    radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  
    //the line above initiates data sending
    theData.SenzA_0 = analogRead(A0);
    Serial.println(theData.SenzA_0);
      radio.send(RECEIVER, (const void*)(&theDataA), sizeof(theDataA)); 
    delay(500);
    
    theData.SenzT_0=dht.readTemperature();
    Serial.println(theData.SenzT_0);
    radio.send(RECEIVER, (const void*)(&theDataT), sizeof(theDataT));  

    delay(500);
    theData.SenzH_0=dht.readHumidity();
    Serial.println(theData.SenzH_0);
    radio.send(RECEIVER, (const void*)(&theDataH), sizeof(theDataH));  
    delay(500);
  }
