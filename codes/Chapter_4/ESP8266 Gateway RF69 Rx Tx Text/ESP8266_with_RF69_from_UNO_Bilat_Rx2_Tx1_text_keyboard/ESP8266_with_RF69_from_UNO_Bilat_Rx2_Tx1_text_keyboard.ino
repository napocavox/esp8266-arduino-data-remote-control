/*
 * the modified library is used
 * RFM69(modified ESP8266 works)
 * Modificarea apare in fila CPP
 * //void RFM69::isr0() { _haveData = true; } //original

#if defined(ESP8266)
ICACHE_RAM_ATTR void RFM69::isr0() { _haveData =true; }
#else
void RFM69::isr0() { <what ever is specified in the currentversion>}
#endif
//modified

 * RFM69HCW breakout ESP8266 NodeMCU ESP8266 Huzzah
VIN VU (5V) VBAT (5V)
GND     GND     GND
EN      n/c     n/c
G0      D2 (GPIO04) GPIO04 //I think it is DIO0
SCK     D5 (GPIO14/HSCLK) GPIO14
MISO    D6 (GPIO12/HMISO) GPIO12
MOSI    D7 (GPIO13/HMOSI) GPIO13
CS      D8 (GPIO15/HCS) GPIO15 //I think it is NSS
RST     D4 (GPIO02) GPIO2

 */

#include <ESP8266WiFi.h>
#include <RFM69.h>    // apelare librării
#include <SPI.h>      // apelare librării
#define NETWORKID       0     // the same for both nodes
#define MYNODEID        2     // ID address of the first node
#define TONODEID        1     // ID address of the second node
//#define FREQUENCY     RF69_868MHZ   //setare frecvenţă
#define FREQUENCY     RF69_433MHZ

#define ENCRYPT       true  
#define ENCRYPTKEY    "TOPSECRETPASSWRD" 
//set password, 16-byte, the same for both nodes
#define USEACK        true    // enable the acknowledgment function (ACK)

#define IS_RFM69HCW   true // set to 'true' if you are using an RFM69HCW module
#define SERIAL_BAUD   115200

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega88) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__)
#define RFM69_CS      10
#define RFM69_IRQ     2
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ)
#define RFM69_RST     9
#define LED           13  // onboard blinky
#elif defined(__arm__)//Use pin 10 or any pin you want

#define RFM69_CS      10
#define RFM69_IRQ     5
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ)
#define RFM69_RST     6
#define LED           13  // onboard blinky

#elif defined(ESP8266)
// ESP8266
#define RFM69_CS      15  // GPIO15/HCS/D8
#define RFM69_IRQ     4   // GPIO04/D2
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ)
#define RFM69_RST     2   // GPIO02/D4

#define LED           0   // GPIO00/D3, onboard blinky for Adafruit Huzzah


#else
#define RFM69_CS      10
#define RFM69_IRQ     2
#define RFM69_IRQN    digitalPinToInterrupt(RFM69_IRQ)
#define RFM69_RST     9
#endif
RFM69 radio = RFM69(RFM69_CS, RFM69_IRQ, IS_RFM69HCW, RFM69_IRQN);


void setup()
{
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
}

void loop() {
static char sendbuffer[62]; 
static int sendlength = 0;  //activare buffer caractere

if (Serial.available() > 0) { // enable serial reading from the keyboard
char input = Serial.read();   // read the characters from the keyboard

if (input != '\r')      // if enter is not pressed
    { sendbuffer[sendlength] = input; sendlength++;
    } //the characters read are stored in the buffer

if ((input == '\r') || (sendlength == 61)) 
    {
// if enter is pressed or the buffer is full of characters, the data packet is sent
// transmisia datelor
Serial.print("sending to node "); Serial.print(TONODEID, DEC);
Serial.print(", message [");
for (byte i = 0; i < sendlength; i++) Serial.print(sendbuffer[i]);  Serial.println("]");
 if (USEACK)  { //acknowledgment of data reception is requested
 if (radio.sendWithRetry(TONODEID, sendbuffer, sendlength))
 Serial.println("ACK received!");
      else  Serial.println("no ACK received");
      }
      else       {  radio.send(TONODEID, sendbuffer, sendlength);
        }
      sendlength = 0; // reset the packet of
     }  }
 // Recepţia datelor
 if (radio.receiveDone())   // enable receive mode
 {
Serial.print("received from node ");  
Serial.print(radio.SENDERID, DEC);
Serial.print(", message [");
// The received message is stored in the DATA array and is DATALEN bytes in size:
//each character takes one byte and is read in turn from 0 to DATALEN
for (byte i = 0; i < radio.DATALEN; i++)
Serial.print((char)radio.DATA[i]);
Serial.print("], RSSI "); 
Serial.println(radio.RSSI); //activare funcţia RSSI
if (radio.ACKRequested())         // trimitere confirmare
    { radio.sendACK();  
    Serial.println("ACK sent");
}    }  }
