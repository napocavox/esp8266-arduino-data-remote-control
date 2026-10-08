/*ProMini
 * necesita libraria RF69(original)
 * se introduce asa nu trebuie modificat numele
 * incarcare cu FTDI
 * primeste date de la Tx care
 * genereaza pag web cu  slider sau gauge 
 * trimite date
 * theData.Pot
 * servo pe D6 
 alimentare cu 3V, dar servo tebuie alim cu 5V

 */

#include <Servo.h>
 
//#include <ESP8266WiFi.h>
#include <RFM69.h>    // apelare librării
#include <SPI.h>      // apelare librării
#define NETWORKID       0     // acelaşi pentru ambele noduri
#define MYNODEID        2   // adresa  ID a primului nod
#define TONODEID        1     // adresa ID a celui de al doilea nod 
//#define FREQUENCY     RF69_868MHZ   //setare frecvenţă
#define FREQUENCY     RF69_433MHZ

#define ENCRYPT       true  
#define ENCRYPTKEY    "TOPSECRETPASSWRD" 
//stabilire password, 16-byte, acelaşi pentru ambele noduri
#define USEACK        true    // activare funcţia de confirmare (ACK)

//de aici adaugat pentru ESP8266
#define IS_RFM69HCW   true // set to 'true' if you are using an RFM69HCW module
#define SERIAL_BAUD   115200


RFM69 radio;

 Servo Servo0;
 
 typedef struct 
 {    
  int Pot;  
 } 
 
 Payload;
 Payload theData;

void setup()
{
  Serial.begin(SERIAL_BAUD);//adaugat pentru ESP8266
// Hard Reset the RFM module
  

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

Servo0.attach(3);//servo pe D3 pro mini
}


void loop() 
 {  
  if (radio.receiveDone()) 

  {  
      theData = *(Payload*)radio.DATA;  
      Serial.print(" Data_Servo0 ");     
      Serial.println(theData.Pot);   
      Servo0.write(theData.Pot);   
      Serial.println();
   
      }
   }
