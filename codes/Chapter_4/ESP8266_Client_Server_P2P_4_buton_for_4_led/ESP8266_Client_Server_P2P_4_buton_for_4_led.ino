//biblio  hammadiqbal12@gmail.com
/*
 * se conecteaza la serverul hotspot
 * generat de partener
 * nu are nevoie de router local
 * este independent de vreo retea web locala
 */
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);


#include <ESP8266WiFi.h>



#define buton0 14
#define buton1 2 // buton pe D4
#define buton2 12
#define buton3 13


const char *ssid = "hotspot";
const char *password = "12345678";

int value0 = 0;       
int value1 = 0;        
int value2 = 0;        
int value3 = 0;       

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(buton0, INPUT);
  pinMode(buton1, INPUT);
  pinMode(buton2, INPUT);
  pinMode(buton3, INPUT);


  // set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 P2P IP=");
  
  //display.print(WiFi.status());
  display.print(WiFi.localIP());
  display.display();
  delay(2000);
    
  }

}

void loop() {
if(digitalRead(buton0) == LOW) value0 = 1;
if(digitalRead(buton1) == LOW) value1 = 1;
if(digitalRead(buton2) == LOW) value2 = 1;
if(digitalRead(buton3) == LOW) value3 = 1;

if(digitalRead(buton0) == HIGH) value0 = 0;
if(digitalRead(buton1) == HIGH) value1 = 0;
if(digitalRead(buton2) == HIGH) value2 = 0;
if(digitalRead(buton3) == HIGH) value3 = 0;


  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";            //default IP address
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String url = "/data/";
  url += "?s_reading=";
  url +=  "{\"s0_reading\":\"s0_value\",\"s1_reading\":\"s1_value\",\"s2_reading\":\"s2_value\",\"s3_reading\":\"s3_value\"}";

  url.replace("s0_value", String(value0));
  url.replace("s1_value", String(value1));
  url.replace("s2_value", String(value2));
  url.replace("s3_value", String(value3));

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("led state=");
  display.println(value0);
  display.println(value1);
  display.println(value2);
  display.println(value3);
  display.display();
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}
