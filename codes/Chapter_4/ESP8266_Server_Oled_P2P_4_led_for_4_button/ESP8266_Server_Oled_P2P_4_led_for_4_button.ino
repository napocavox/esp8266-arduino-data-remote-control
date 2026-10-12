//biblio  hammadiqbal12@gmail.com
/*genereaza server acces point
 * but receives data from the partner
 * does not need a local router
 * is independent of any local web network
 * */
 
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#define led0 12               
#define led1 13                
#define led2 14                
#define led3 15                

DynamicJsonBuffer jsonBuffer;

const char *ssid = "hotspot";
const char *password = "12345678";

int value0 = 0;        
int value1 = 0;        
int value2 = 0;        
int value3 = 0;        
String s_values;

ESP8266WebServer server(80);

void handleSentVar() {

  if (server.hasArg("s_reading"))
  {
    s_values = server.arg("s_reading");
    Serial.println(s_values);
  }
  JsonObject& root = jsonBuffer.parseObject(s_values);
//  if (!root.success()) {
//    Serial.println("parseObject() failed");
//    return;
//  }
//  if (root.success())
//  {
    value0          = root["s0_reading"].as<int>();
    value1          = root["s1_reading"].as<int>();
    value2          = root["s2_reading"].as<int>();
    value3          = root["s3_reading"].as<int>();

//  }

  Serial.println(value0);
  Serial.println(value1);
  Serial.println(value2);
  Serial.println(value3);

  toggle_leds();

  server.send(200, "text/html", "Data received");
}


void setup() {
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();

  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  
  server.on("/data/", HTTP_GET, handleSentVar); 
  // when the server receives a request with /data/ in the string then run the handleSentVar function
  server.begin();

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 P2P IP=");
  
  display.print(myIP);
  
  display.display();
  delay(2000);
}

void loop() {
  server.handleClient();
}

void toggle_leds()
{
  if (value0 == 0)  digitalWrite(led0, LOW);
  if (value1 == 0)  digitalWrite(led1, LOW);
  if (value2 == 0)  digitalWrite(led2, LOW);
  if (value3 == 0)  digitalWrite(led3, LOW);

  if (value0 == 1)  digitalWrite(led0, HIGH);
  if (value1 == 1)  digitalWrite(led1, HIGH);
  if (value2 == 1)  digitalWrite(led2, HIGH);
  if (value3 == 1)  digitalWrite(led3, HIGH);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("led state=");
  display.println(value1);
  display.display();
  }
