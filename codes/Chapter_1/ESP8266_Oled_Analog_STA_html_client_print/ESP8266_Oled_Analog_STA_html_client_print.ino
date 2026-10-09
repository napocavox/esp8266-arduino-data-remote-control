

#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char* ssid = "nume router";
const char* password = "password router";

WiFiServer server(80);

void setup() 
{
Serial.begin(115200); 
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
    }
server.begin();
 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay(); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("oled Analog ESP8266 html IP=");
  display.print(WiFi.localIP());
  display.display();
delay(2000);
}

void loop() {
  WiFiClient client = server.available(); 
  if (client) {
   
        client.println("HTTP/1.1 200 OK");
          
          client.println("Refresh: 1");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("<h1 style=font-size:50px>Analog</h1>");
          
          client.print("<p style=font-size:50px>U=</p>");
          int U = analogRead(A0); //pot on A0
          client.print(U);
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0); 
  display.print(" U=");
  display.print(U);
  display.display();
            
          client.println("</html>");
             
       }
      }
