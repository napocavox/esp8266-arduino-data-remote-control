

 
#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char* ssid = "nume router";
const char* password = "password router";

int ledPin = 15;

WiFiServer server(80);

void setup() 
{
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  
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
  // verifica daca un client este conectat
  WiFiClient client = server.available();

// trimite clientului un raspuns 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  obligatoriu acesta linie
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body>");
  client.println("<h1>LED REQUEST</h1>");
  
  client.println("<br><br>");
  client.println("<center><a href=\"/LED=ON\"\"><button=\"button style=\"font-size:400%\">Turn On </button></a>");
  client.println("<br><br>");
  client.println("<a href=\"/LED=OFF\"\"><button=\"button style=\"font-size:400%\">Turn Off </button></a>");
  client.println("</html>");
  
  if (!client) {
    return;
  }
  
  // asteapta date de la client 
   while(!client.available()){
    delay(1);
  }
  // citeste prima linie din solicitarea clientului, request
  String request = client.readStringUntil('\r');
  client.flush();
  //efectueaza solicitarea clientuui 

  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
  }
  delay(1);
    }
