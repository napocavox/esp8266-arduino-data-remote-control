/*
analog feedback with gauge on V3,

brik fotorezistor  
+3.3v to A0

*/

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;


#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
char auth[] = "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"; 
char ssid[] = "UPCF4821BC";
char pass[] = "Gherla1956";


#define analogPin A0 //photoresistor to A0
//#include <IRsend.h> 
int analog = 0;

BLYNK_WRITE(V6){ 

Serial.print(  "text=");
Serial.println( param.asStr());
display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.print("message=");
  display.print(param.asStr());
  display.display();

}

void setup() {

  pinMode(12, OUTPUT); // Led 1
  pinMode(13, OUTPUT); // Led 2
  pinMode(2, OUTPUT); // Led 3
  pinMode(15, OUTPUT); // Led 4

display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.print("Pager and RGB control with feedback and Blynk");
  
  display.display();
  
  
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  
  
  timer.setInterval(500L, sendUptime);

 
}
void loop() {
  Blynk.run(); 
 timer.run(); 
}

void sendUptime()
{
analog= analogRead(analogPin); 
  //Blynk.virtualWrite(5, analog);
  Blynk.virtualWrite(3, analog);
  //displays on V5 the values read by the photoresistor
}

BLYNK_WRITE(V12) {
  digitalWrite(12, param.asInt()); // led 1 
  //in cod GPIO 12,13,14,15
}
BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); // Led 2
}


BLYNK_WRITE(V15) {
  digitalWrite(15, param.asInt()); // Led 4
}

BLYNK_WRITE(V14) {
  digitalWrite(2, param.asInt()); // Led 4
}
