/** genereaza pag web cu IP
 * 196.168.0.207
 * 
 * genereaza pag web cu slider
 * trimite valorile theData.Pot_0 = valueString.toInt();  
 * de la telefon la Rx/Tx cu ESP8266 si RF69 
 * ce joaca rol de Tx
 * este receptionat de Rx

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

String request;
String valueString = String(0);
int positon1 = 0;
int positon2 = 0;

 
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

  int potpin0 = A0; // analog pin used to connect the potentiometer
  int val0 = 0; // variable initialized for storing potpin0 value

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
//partea wi fi
WiFiClient client = server.available();
  
 if (client)
{ // If a new client connects,

String request = client.readStringUntil('\r');
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html"); 
client.println("Connection: close");    
client.println();

// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");

client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
client.println(".slider { width: 300px; }</style>");
//liniile style editeaza un slider mai mare

client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
//liniile script sunt necesare
// Web Page
client.println("</head><body><h1>Gtw ESP8266 RF69 Servo ProMini</h1>");
//afiseaza titlul, optional

client.println("<p>Position: <span id=\"servoPos\"></span></p>"); 
//afiseaza text cu pozitia, optional

client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");
client.println("<script>var slider = document.getElementById(\"servoSlider\");");

client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
//linia de sus furnizeaza pozitia, optional

client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
//linia de sus este legata de cea anterioara , furnizeaza pozitia doar pentru afisare 

client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");
client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");
client.println("</body></html>"); 


//rotate servo
if(request.indexOf("GET /?value=")>=0) 
{
positon1 = request.indexOf('=');
positon2 = request.indexOf('&');
valueString = request.substring(positon1+1, positon2);
  theData.Pot_0 = valueString.toInt();
  //transforma stringul in date care 
  //sunt trimise modulului RF69  
  } 

request = "";
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}


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
  delay(500);
  }
