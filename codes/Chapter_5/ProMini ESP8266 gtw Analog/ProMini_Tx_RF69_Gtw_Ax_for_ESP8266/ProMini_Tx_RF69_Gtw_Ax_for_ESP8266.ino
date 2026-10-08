/*
 * trimite date prin RF69 de la pot pe A2 pro Mini  
 * s-a folosit libraria originala
 * RFM69(original)

 */



#define RECEIVER      2  

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
  Serial.begin(SERIAL_BAUD);//adaugat pentru ESP8266

  if (!radio.initialize(FREQUENCY,MYNODEID,NETWORKID)) {
    Serial.println("radio.initialize failed!");
  }
  if (IS_RFM69HCW) {
    radio.setHighPower();    // Only for RFM69HCW & HW!
  }
  radio.setPowerLevel(31); // power output ranges from 0 (5dBm) to 31 (20dBm)

  if (ENCRYPT)
  radio.encrypt(ENCRYPTKEY);    // activare criptare, modul (AES)

  char buff[50];
  sprintf(buff, "\nTransmitting at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
  Serial.println(buff); 
  }


void loop() 
{
    for (byte i = 0; i < radio.DATALEN; i++)
    Serial.print((char)radio.DATA[i]);   
    //partea de sus este optionala
    
    theData.Pot_0 = analogRead(potpin0);                                              // assign servo position to transmit packet variable.
    radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  
delay(500);
  
  }
