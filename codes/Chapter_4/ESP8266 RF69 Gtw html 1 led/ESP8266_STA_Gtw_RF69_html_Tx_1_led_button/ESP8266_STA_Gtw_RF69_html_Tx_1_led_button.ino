/*
 * genereaza pag web cu 2 butoane
 * fiecare buton trimite o valoare 
 * pentru activare led
 * theData.Pot_0 =;
 * si theData.Pot_0 =1;
 * transmite de la telefon la primul modul
 * ESP8266 cu RF69 care joaca rol de Tx
 * este receptionat de Rx
codul Rx este 
ESP8266 Rx_Gtw_RF69_for Tx html_1_led_button

 * s-a folosit libraria modificata
 * RFM69(modificata ESP8266)
 * Modificarea apare in fila CPP
 * //void RFM69::isr0() { _haveData = true; }//original

#if defined(ESP8266)
ICACHE_RAM_ATTR void RFM69::isr0() { _haveData =true; }
#else
void RFM69::isr0() { <what ever is specified in the currentversion>}
#endif
//modificata

conectare RF69 la ESP8266
RFM69HCW breakout ESP8266 NodeMCU ESP8266 Huzzah
VIN VU (5V) VBAT (5V)
GND     GND     GND
EN      n/c     n/c
NSS      D2 (GPIO04) 
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

 
 typedef struct 
 {    
   int Pot_0;   //create transmit variable & store data potentiometer 0 data
 } 
 Payload;
 Payload theData;  
 
void setup()
{
Serial.begin(115200); 
  WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
}
server.begin();
Serial.print(WiFi.localIP());

delay(2000);
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


void loop() 
{

WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // AWait until the client sends some data 
   while(!client.available()){
    delay(1);
  }

   // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();

   // Match the request
 
  if (request.indexOf("/LED=ON") != -1)  {
    //float theData=20;
    theData.Pot_0 =1;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    //float theData=120;
    theData.Pot_0 =0;
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body>");
  client.println("<br><br>");
  client.println("<center><h1>LED REQUEST</h1>");
  
  client.println("<br><br>");
  client.println("<center><a href=\"/LED=ON\"\"><button=\"button style=\"font-size:600%\">Turn On </button></a>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/LED=OFF\"\"><button=\"button style=\"font-size:600%\">Turn Off </button></a>");
  client.println("</html>");
 
  delay(1);


  ////////////////////////////////////
    for (byte i = 0; i < radio.DATALEN; i++)
    Serial.print((char)radio.DATA[i]);
    Serial.print("   [RX_RSSI:");
    Serial.print(radio.readRSSI());Serial.print("]");
    Serial.println();
    //partea de sus este optionala
   
    radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  

    Serial.print("Sending struct (");
    Serial.print(sizeof(theData));
    Serial.println(" bytes) ");
    Serial.println();
  delay(1000);
  }
