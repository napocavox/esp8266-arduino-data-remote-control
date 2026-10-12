/*
 * sends data via RF69 from pot on A2 pro Mini
 * the original library was used
 * RFM69(original)

 */



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

RFM69 radio;
  int potpin0 = A2; // analog pin used to connect the potentiometer
  
 typedef struct 
 {    
    int Pot_0;   //create transmit variable & store data potentiometer 0 data
    
 } 
 Payload;
 Payload theData; 
 
void setup()
{
  Serial.begin(SERIAL_BAUD);//added for ESP8266

  if (!radio.initialize(FREQUENCY,MYNODEID,NETWORKID)) {
    Serial.println("radio.initialize failed!");
  }
  if (IS_RFM69HCW) {
    radio.setHighPower();    // Only for RFM69HCW & HW!
  }
  radio.setPowerLevel(31); // power output ranges from 0 (5dBm) to 31 (20dBm)

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
    //the part above is optional
    
    theData.Pot_0 = analogRead(potpin0);                                              // assign servo position to transmit packet variable.
    radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  
delay(500);
  
  }
