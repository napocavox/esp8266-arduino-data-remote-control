/*ProMini
 * requires the RF69 library(original)
 * entered without modifying the name
 * upload with FTDI
 * receives data from the Tx that
 * generates web page with 4 buttons
 * ESP8266_STA_Tx_Gtw_RF69_client_print_4_led_buton
 * sends data
 * theData.Pot
 * 
 power supply with 3V,

 */


#include <RFM69.h>    // apelare librării
#include <SPI.h>      // apelare librării
#define NETWORKID       0     // the same for both nodes
#define MYNODEID        2   // ID address of the first node
#define TONODEID        1     // ID address of the second node
//#define FREQUENCY     RF69_868MHZ   //setare frecvenţă
#define FREQUENCY     RF69_433MHZ

#define ENCRYPT       true  
#define ENCRYPTKEY    "TOPSECRETPASSWRD" 
//set password, 16-byte, the same for both nodes
#define USEACK        true    // enable the acknowledgment function (ACK)


#define IS_RFM69HCW   true // set to 'true' if you are using an RFM69HCW module
#define SERIAL_BAUD   115200


RFM69 radio;

 int led1 = 6;
 int led2 = 7;
 int led3 = 8;
 int led4 = 9;
 
 typedef struct 
 {    
  int Pot;  
 } 
 
 Payload;
 Payload theData;

void setup()
{
  Serial.begin(SERIAL_BAUD);//added for ESP8266
// Hard Reset the RFM module
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

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

//Servo0.attach(3);//servo on D3 pro mini
}


void loop() 
 {  
  if (radio.receiveDone()) 

  {  
      theData = *(Payload*)radio.DATA;  
      Serial.print(" Data_Servo0 ");     
      Serial.println(theData.Pot);   
      if (theData.Pot== 1){
      digitalWrite(led1, HIGH);   
      Serial.println();
      }
      else if (theData.Pot== 0){
      digitalWrite(led1, LOW);   
      }

      else if (theData.Pot== 2){
      digitalWrite(led2, HIGH);   
      }
      else if (theData.Pot== 3){
      digitalWrite(led2, LOW);   
      }

else if (theData.Pot== 4){
      digitalWrite(led3, HIGH);   
      }
      else if (theData.Pot== 5){
      digitalWrite(led3, LOW);   
      }

else if (theData.Pot== 6){
      digitalWrite(led4, HIGH);   
      }
      else if (theData.Pot== 7){
      digitalWrite(led4, LOW);   
      }
   
      }
   }
