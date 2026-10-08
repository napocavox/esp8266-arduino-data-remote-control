/*
 * primeste date prin RF69 de la Tx cu pot 
 * analog pe A0
 * datele sunt: theData.Pot
 * genereaza pag web 
 * afiseaza pe telefon datele analogice primite
 * 
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

#include <ESP8266WiFi.h>
const char* ssid = "nume router";
const char* password = "password";
WiFiServer server(80);

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
  int Pot;  
 }  
 Payload;
 Payload theData;
 
void setup()
{
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

//generare server WiFi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
    }
//Serial.println("");
//Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
server.begin();
delay(2000);
}


void loop() 
 {  
//activeaza serverul WiFi
WiFiClient client = server.available(); 
  if (client) {
   
        client.println("HTTP/1.1 200 OK");         
          client.println("Refresh: 1");
          //reactualizeaza pagina la 1 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<center><body><div style=\"font-size: 3.5rem;\"><p>ESP8266 Gtw RF69 Analog </p><p>");
        
          client.println("<html>");
          
          //client.print("<h1 style=font-size:50px>Gtw RF69 Analog</h1>");
          
          //client.print("<p style=font-size:50px>U=</p>");
          //client.print("<p style=font-size:50px>Rx Analog=</p>");
           
          //int U = analogRead(A0); //pot pe A0
          //client.print("<p style=font-size:50px>U=</p>");
          //client.print(U);
          //
          client.print("<h1 style=font-size:50px>theData.Pot=</h1>");
          client.println("<div style=\"color: #009191;\">");
         
          client.print(theData.Pot);
          client.println("</html>");
             
       }
  
  //transceiver RF69
  if (radio.receiveDone()) 

  {  
      theData = *(Payload*)radio.DATA;  
      Serial.print(" Data_Analog ");     
      Serial.println(theData.Pot);   
      Serial.println();
      }
   }
