/*
 * ESP8266 Servo Motor Control With Web Server 
 * https://circuits4you.com
 * servo pe D3 =GPIO 0
 * merge prin router local
 * https://circuits4you.com/2019/01/12/esp8266-servo-motor-control/
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);


#include "camera_index.h"

#define LED 14   //D5 is GPIO14
#define ServoPin 0  //D3 is GPIO 0 (zero) 

//WiFi Connection configuration

const char* ssid = "nume router";
const char* password = "parola";



Servo myservo;  
ESP8266WebServer server(80);

void handleServo(){
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();

  myservo.write(2*pos);//roteste cu 180 cu pas de 2

  display.clearDisplay(); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Servo Pos=");
  display.print(pos);
  display.display();
  
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  digitalWrite(LED,!(digitalRead(LED))); //Toggle LED
  server.send(200, "text/plane","");
}

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  pinMode(LED,OUTPUT);
  myservo.attach(ServoPin); // attaches the servo on GIO2 to the servo object
  
  //Connect to wifi Network
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  //Initialize Webserver
  server.on("/",handleRoot);
  server.on("/setPOS",handleServo); //Sets servo position from Web request
  server.begin();  

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay(); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Servo Gauge ESP8266 IP=");
  display.print(WiFi.localIP());
  display.display();
  delay(2000);

}


void loop() {
 server.handleClient();
}
