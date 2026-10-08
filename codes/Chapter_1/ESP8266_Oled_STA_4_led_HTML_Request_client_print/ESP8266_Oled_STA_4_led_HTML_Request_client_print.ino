 
 
#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char* ssid = "nume router";
const char* password = "password router";
int ledPin = 15;
int ledPin2 = 12;
int ledPin3 = 13;
int ledPin4 = 14;

WiFiServer server(80);

void setup() 
{
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);

  pinMode(ledPin2,OUTPUT);
  digitalWrite(ledPin2,LOW);
  
  pinMode(ledPin3,OUTPUT);
  digitalWrite(ledPin3,LOW);
  
  pinMode(ledPin4,OUTPUT);
  digitalWrite(ledPin4,LOW);
  
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
  display.print("oled Req ESP8266 4 led IP=");
  display.print(WiFi.localIP());
  display.display();
delay(2000);
}

void loop() {

    // Check if a client has connected
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
 
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
  }

 if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
  }
  
if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(ledPin3, HIGH);
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(ledPin3, LOW);
  }

  if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(ledPin4, HIGH);
  }
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(ledPin4, LOW);
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<center><h1>4 LED analog REQUEST</h1>");
  
        client.print("<center><a style=font-size:50px>U=</a>");
          int U = analogRead(A0); //potentiometru pe A0
          client.print(U);
          
  client.println("<br><br>");
  client.println("<center><a href=\"/LED=ON\"\"><button=\"button style=\"font-size:400%\">Led 1 On </button></a>");
  client.println("---<a href=\"/LED=OFF\"\"><button=\"button style=\"font-size:400%\">Led 1 Off </button></a>");
  client.println("<br><br>");
 
  client.println("<a href=\"/LED2=ON\"\"><button=\"button style=\"font-size:400%\">Led 2 On </button></a>");
  client.println("---<a href=\"/LED2=OFF\"\"><button=\"button style=\"font-size:400%\">Led 2 Off </button></a>");
  
  client.println("<br><br>");

  client.println("<a href=\"/LED3=ON\"\"><button=\"button style=\"color: green; font-size:400%\">Led 3 On </button></a>");
  client.println("---<a href=\"/LED3=OFF\"\"><button=\"button style=\"color: red; font-size: 80px\">Led 3 Off </button></a>");
  
  client.println("<br><br>");

  client.println("<a href=\"/LED4=ON\"\"><button=\"button style=\"background-color: yellow; font-size:400%;  \">Led 4 On </button></a>");
  client.println("---<a href=\"/LED4=OFF\"\"><button=\"button style=\"background-color: pink; font-size:400%\">Led 4 Off </button></a>");
client.println("<br><br>");

client.println("<a href=\"/LED4=OFF\"\"><button=\"button style=\"color: magenta ; font-size:600%\">refresh </button></a>");
client.println("<br><br>");

  client.println("</html>");

  delay(1);
    }
