/*
 * primeste date prin RF69 de 
 * la Tx cu DHT11 pe D1=GPIO5  cod
 * ESP8266_Gtw_RF69_Tx_DHT11_for_AP_Rx_Gtw
 * datele sunt: theData.SenzT_0=dht.readTemperature(); etc
 * genereaza server AP tip WebSerial
 * afiseaza pe telefon datele analog si DHT11 primite de la Tx
 * joaca ror de intermediar, nu are conectat nici un periferic
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

const char* ssid = "AP Tx 1"; // Your WiFi AP SSID 
const char* password = "12345678"; // Your WiFi Password


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
    int SenzA;   
    int SenzT;
    int SenzH;
 } 
 Payload;
 Payload theData; 
 Payload theDataA; 
 Payload theDataT;
 Payload theDataH; 

void setup()
{
Serial.begin(115200);
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    
    server.begin();
    delay(2000);
  
  Serial.begin(SERIAL_BAUD);//adaugat pentru ESP8266
// Hard Reset the RFM module
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, HIGH);
  delay(100);
  digitalWrite(RFM69_RST, LOW);
  delay(100);//adaugat pentru ESP8266

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
  //initiere transceiver RF69
  if (radio.receiveDone()) 

  {  
      theData = *(Payload*)radio.DATA;  
      //linia de sus initiaza primirea datelor
   
      Serial.print(" analog ");     
      Serial.println(theData.SenzA); 
      WebSerial.print(" A0="); 
      WebSerial.println(theData.SenzA); 
      
      Serial.print(" Temp DHT11 ");     
      Serial.println(theData.SenzT); 
      WebSerial.print(" T="); 
      WebSerial.println(theData.SenzT);

      Serial.print(" Hum DHT11 ");     
      Serial.println(theData.SenzH); 
      WebSerial.print(" H="); 
      WebSerial.println(theData.SenzH);

      Serial.println();
 
      }
   }
