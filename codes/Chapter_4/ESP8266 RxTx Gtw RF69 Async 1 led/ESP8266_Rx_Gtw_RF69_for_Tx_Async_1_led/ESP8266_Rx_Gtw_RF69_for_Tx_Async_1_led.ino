/*
 * primeste date de la Tx care
 * genereaza pag web cu  butoane 
 * fiecare buton trimite valoarea 0 sau 1
 * de exemplu
 * theData.Pot_0 =0;
 * theData.Pot_0 =1;
cod Tx
ESP8266_Tx_STA_Async_Gtw_RF69_1_led

 * led pe D1 definit GPIO5
 * s-a folosit libr modificata
 * RFM69(modificata ESP8266)
 * Modificarea apare in fila CPP
 * //void RFM69::isr0() { _haveData = true; }//original

modificare
#if defined(ESP8266)
ICACHE_RAM_ATTR void RFM69::isr0() { _haveData =true; }
#else
void RFM69::isr0() { <what ever is specified in the currentversion>}
#endif
//modificat acum
conexiuni RF69 la ESP8266
 * RFM69HCW breakout ESP8266 NodeMCU ESP8266 Huzzah
VIN VU (5V) VBAT (5V)
GND     GND     GND
EN      n/c     n/c
G0      D2 (GPIO04) GPIO04 //cred ca este DIO0
SCK     D5 (GPIO14/HSCLK) GPIO14
MISO    D6 (GPIO12/HMISO) GPIO12
MOSI    D7 (GPIO13/HMOSI) GPIO13
CS      D8 (GPIO15/HCS) GPIO15 //cred ca este NSS
RST     D4 (GPIO02) GPIO2

 */

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

//de aici ESP8266
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

 int led1 = 5;    //led pe D1=GPIO5 
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
  pinMode(led1, OUTPUT);
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
  }


  void loop() 
  {  
  if (radio.receiveDone()) 
  {  
      theData = *(Payload*)radio.DATA;  
      Serial.print(" Data_led1 ");     
      Serial.println(theData.Pot);   
      digitalWrite(led1, theData.Pot);   
      Serial.println();
      }
   }
