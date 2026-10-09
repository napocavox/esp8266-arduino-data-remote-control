/*
 * 
 * generates web page with 4 buttons
 * each button sends a value
 * for activating the LEDs, for example
 * theData.Pot_0 =0;
 * and theData.Pot_0 =1;
 * 
 * theData.Pot_0 =4;
 * and theData.Pot_0 =5;
 * theData.Pot_0 =3, 7,8 for button 3, etc
 * at reception the values theData.Pot_0 =abcd; will be selected
 * folosind functia if theData.Pot_0 ==5; digital write led 2=HIGH
 * 
 * transmits from the phone to the first module
 * ESP8266 with RF69 acting as Tx
 * is received by Rx
the Rx code is
Rx cod ProMini_Rx_Gtw_RF69_for_ESP8266_Tx_html_4_led

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

#include <ESP8266WiFi.h>
const char* ssid = "nume router";
const char* password = "password";
WiFiServer server(80);

 
#define RECEIVER      2  
//#include <ESP8266WiFi.h>
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
 /////////////////

 String header;
String outputRedState = "off";
String outputGreenState = "off";
String outputYellowState = "off";
String outputblueState = "off";

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

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

WiFiClient client = server.available();
if (client) { // If a new client connects,
Serial.println("New Client."); // print a message out in the serial port
String currentLine = ""; // make a String to hold incoming data from the client
currentTime = millis();
previousTime = currentTime;
while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
currentTime = millis(); 
if (client.available()) { // if there's bytes to read from the client,
char c = client.read(); // read a byte, then
Serial.write(c); // print it out the serial monitor
header += c;
if (c == '\n') { // if the byte is a newline character
if (currentLine.length() == 0) {
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println("Connection: close");
client.println();

// turns the GPIOs on and off
if (header.indexOf("GET /5/on") >= 0) {//2 motors forward
Serial.println("RED LED is on");
outputRedState = "on";
outputGreenState = "off";
outputYellowState = "off";
outputblueState = "off";  //sets all the others to OFF

    theData.Pot_0 =1;

} else if (header.indexOf("GET /5/off") >= 0) {
Serial.println("RED LED is off");
outputRedState = "off";
    theData.Pot_0 =0;

} else if (header.indexOf("GET /4/on") >= 0) {//2 motors backward
Serial.println("Green LED is on");
outputRedState = "off";
outputGreenState = "on";
outputYellowState = "off";
outputblueState = "off";  //sets all the others to OFF

    theData.Pot_0 =2;

} else if (header.indexOf("GET /4/off") >= 0) {
Serial.println("Green LED is off");
outputGreenState = "off";
theData.Pot_0 =3;

} else if (header.indexOf("GET /0/on") >= 0) {
Serial.println("Yellow LED is on"); //one motor forward, turns right
outputRedState = "off";
outputGreenState = "off";
outputYellowState = "on";
outputblueState = "off";  //sets all the others to OFF

theData.Pot_0 =4;

} else if (header.indexOf("GET /0/off") >= 0) {
Serial.println("Yellow LED is off");
outputYellowState = "off";
theData.Pot_0 =5;

/////////////////

} else if (header.indexOf("GET /2/on") >= 0) {
Serial.println("blue LED is on"); //one motor forward, turns left
outputRedState = "off";
outputGreenState = "off";
outputYellowState = "off";
outputblueState = "on";  //sets all the others to OFF

theData.Pot_0 =6;

} else if (header.indexOf("GET /2/off") >= 0) {
Serial.println("blue LED is off");
outputblueState = "off";
theData.Pot_0 =7;
}
// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
// CSS to style the on/off buttons 
client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");

client.println(".buttonRed { background-color: #ff0000; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

client.println(".buttonGreen { background-color: #00ff00; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

client.println(".buttonYellow { background-color: #feeb36; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

client.println(".buttonblue { background-color: #0000ff; border: none; color: white; padding: 16px 40px; border-radius: 60%;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

client.println(".buttonOff { background-color: #76878A; border: none; color: white; padding: 16px 40px; ");
//square buttons appear in the OFF state
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}</style></head>");


// Web Page Heading
client.println("<body><h1>My LED Control Server</h1>");

// Display current state, and ON/OFF buttons for Red LED 
client.println("<p>Red LED is " + outputRedState + "</p>");
// If the outputRedState is off, it displays the OFF button 
if (outputRedState=="off") {
client.println("<p><a href=\"/5/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/5/off\"><button class=\"button buttonRed\">ON</button></a></p>");
} 

// Display current state, and ON/OFF buttons for Green LED 
client.println("<p>Green LED is " + outputGreenState + "</p>");
// If the outputGreenState is off, it displays the OFF button 
if (outputGreenState =="off") {
client.println("<p><a href=\"/4/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/4/off\"><button class=\"button buttonGreen\">ON</button></a></p>");
}
client.println("</body></html>");

// Display current state, and ON/OFF buttons for GPIO 3 Yellow LED 
client.println("<p>Yellow LED is " + outputYellowState + "</p>");
// If the outputYellowState is off, it displays the OFF button 
if (outputYellowState =="off") {
client.println("<p><a href=\"/0/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/0/off\"><button class=\"button buttonYellow\">ON</button></a></p>");
}
client.println("</body></html>");


// Display current state, and ON/OFF buttons for GPIO 4 blue LED 
client.println("<p>blue LED is " + outputblueState + "</p>");

if (outputblueState =="off") {
client.println("<p><a href=\"/2/on\"><button class=\"button buttonOff\">OFF</button></a></p>");
} else {
client.println("<p><a href=\"/2/off\"><button class=\"button buttonblue\">ON</button></a></p>");
}
client.println("</body></html>");


// The HTTP response ends with another blank line
client.println();
// Break out of the while loop
break;
} else { // if you got a newline, then clear currentLine
currentLine = "";
}
} else if (c != '\r') { // if you got anything else but a carriage return character,
currentLine += c; // add it to the end of the currentLine
}
}
}

// Clear the header variable
header = "";
// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}

    radio.send(RECEIVER, (const void*)(&theData), sizeof(theData));  

    Serial.print("Sending struct (");
    Serial.print(sizeof(theData));
    Serial.println(" bytes) ");
    Serial.println();
  delay(1000);
  }
