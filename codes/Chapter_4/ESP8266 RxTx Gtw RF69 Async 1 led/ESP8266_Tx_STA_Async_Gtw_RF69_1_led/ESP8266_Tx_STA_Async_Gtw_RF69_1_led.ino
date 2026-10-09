/*
 * 
 * generates web page with 2 buttons ON and OFF
 * each button sends a value
 * for activating the LED
 * theData.Pot_0 =;
 * and theData.Pot_0 =1;
 * transmits from the phone to the first module
 * ESP8266 with RF69 acting as Tx
 * is received by Rx
the Rx code is
ESP8266_Rx_Gtw_RF69_for_Tx_Async_1_led

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

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define LED 5

const char ssid[]="UPCF4821BC";
const char password[]="Gherla1956";
AsyncWebServer server(80);

#include <ESP8266WiFi.h>

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
   int Pot_0;   //create transmit variable & store data potentiometer 0 data
 } 
 Payload;
 Payload theData;  

const char LEDcontrolwebpage[] PROGMEM = R"=====(
<html>
  <head>
    <center><title>ESP8266 Async LED Control</title>
  </head>
  <body>
    <p>Select LED State</p>
    <center><a href="/on"><button>ON</button></a>
    <a href="/off"><button>OFF</button></a></body>
</html>
)=====";
 
void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  Serial.printf("Connecting to %s....\n", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() != WL_CONNECTED){
    Serial.printf("WiFi connection failed!Rebooting ...\n");
    delay(1000);
    ESP.restart();
    }
  Serial.printf("Connected to %s\n", ssid);
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", LEDcontrolwebpage);
    }
    );

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){     
    digitalWrite(LED,HIGH); 
    theData.Pot_0 =1;
    printf("LED On\n"); 
    request->redirect("/");
    }
    );

  server.on("/off", HTTP_GET,
  [](AsyncWebServerRequest *request){    
    digitalWrite(LED, LOW);
    theData.Pot_0 =0;
    printf("LED Off\n");
    request->redirect("/");
    }
    );

  server.begin();

delay(200);
  Serial.begin(SERIAL_BAUD);//added for ESP8266
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
    Serial.print(radio.readRSSI());Serial.print("]");
    Serial.println();
    //the part above is optional
   
    radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  

    Serial.print("Sending struct (");
    Serial.print(sizeof(theData));
    Serial.println(" bytes) ");
    Serial.println();
  delay(100);
  }
