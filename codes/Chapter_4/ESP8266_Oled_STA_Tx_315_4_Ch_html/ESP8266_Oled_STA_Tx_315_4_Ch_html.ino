
/*requires rc_switch libr
 * does NOT work with the old libr RCswitch
 * Tx 315 Mhz,  antena L/4=23cm
 * Attention, the module
 * must be powered with 5V
 * otherwise it does not work
 * Rx Data connected to D4, defined in code GPIO 2
 * 
 * generates html page with 4 buttons
 *  for 4-channel TLC,
 * 
 * the font size is increased using the line
 * client.println("<a href=\"/LED=ON\"\"><button=\" button style=\"font-size:400%\">Turn On </button></a><br />");
 instead of
 client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a><br />");
 <br/> means new line
 the line client.println("<br><br>"); inserts spaces between buttons

 for centered text I use the line
 client.println("<center><a href=\"/LED=ON\"\"><button=\"button style=\"font-size:400%\">Turn On </button></a>");
  on the left
  client.println("<left><a href=\"/LED=ON\"\"><button=\"button style=\"font-size:400%\">Turn On </button></a>");
  
 */

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char* ssid = "nume router";
const char* password = "password";

int ledA = 12;
int ledB = 14;
int ledC = 15;
int ledD = 13;

WiFiServer server(80);

void setup() 
{
  
  pinMode(ledA,OUTPUT);
  pinMode(ledB,OUTPUT);
  pinMode(ledC,OUTPUT);
  pinMode(ledD,OUTPUT);
  digitalWrite(ledA,LOW);
  digitalWrite(ledB,LOW);
  digitalWrite(ledC,LOW);
  digitalWrite(ledD,LOW);
  

mySwitch.enableTransmit(2);
 
Serial.begin(115200); 
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);

    }
server.begin();
 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay(); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("oled Req ESP8266 html IP=");
  display.print(WiFi.localIP());
  display.display();
delay(2000);
}

void loop() {
  // check if a client is connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data 
   while(!client.available()){
    delay(1);
  }

   // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();

   // Match the request

if (request.indexOf("LEDA=ON") != -1)  {
    mySwitch.send(5592332, 24);   
    //mySwitch.send("10101010101010100001100");    //cod binar
    digitalWrite(ledA, HIGH);digitalWrite(ledB, LOW);digitalWrite(ledC, LOW);digitalWrite(ledD, LOW);
  }

if (request.indexOf("LEDB=ON") != -1)  {
    mySwitch.send(5592512, 24);  
    //mySwitch.send("10101010101010111000000"); //cod binar  
    digitalWrite(ledA, LOW);digitalWrite(ledB, HIGH);digitalWrite(ledC, LOW);digitalWrite(ledD, LOW);
  }


  if (request.indexOf("LEDC=ON") != -1)  {
    mySwitch.send(5592323, 24);   
    //mySwitch.send("10101010101010100000011");   
    digitalWrite(ledA, LOW);digitalWrite(ledB, LOW);digitalWrite(ledC, HIGH);digitalWrite(ledD, LOW);   
  }

if (request.indexOf("LEDD=ON") != -1)  {
    mySwitch.send(5592368, 24);  //pun alte coduri
    //mySwitch.send("10101010101010100110000");
    digitalWrite(ledA, LOW);digitalWrite(ledB, LOW);digitalWrite(ledC, LOW);digitalWrite(ledD, HIGH);
  }
  
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width,   initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin:  0px auto; text-align: center;}");
  client.println(".button { background-color: #4CAF50; border: 2px solid #4CAF50;;  color: white; padding: 14px 32px; text-align: center; text-decoration: none; display:   inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor:  pointer;}"); 
// Web Page Heading
  client.println("</style></head>");
  client.println("<body><center><h1>Tx 4 Ch ESP8266 </h1></center>");
  client.println("<form><center>");
   client.println("<br><br>");
  client.println("<button class=\"button\" name=\"LEDA\" value=\"ON\"   type=\"submit\">LEDA ON</button>");
  client.println("<button class=\"button\" name=\"LEDB\" value=\"ON\"   type=\"submit\">LEDB ON</button></center>");
  client.println("<button class=\"button\" name=\"LEDC\" value=\"ON\"   type=\"submit\">LEDC ON</button>") ;
  client.println("<button class=\"button\" name=\"LEDD\" value=\"ON\"   type=\"submit\">LEDD ON</button></center>");
  client.println("</center></form></body></html>");
  delay(1);
    }
