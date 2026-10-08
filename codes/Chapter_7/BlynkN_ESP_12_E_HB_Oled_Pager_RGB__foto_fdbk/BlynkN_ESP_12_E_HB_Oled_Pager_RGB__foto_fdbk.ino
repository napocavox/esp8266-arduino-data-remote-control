/*
  feedback analog cu gauge pe V3, 
  mesaje pe Terminal V6
  fotorezistor la A0
  punte H cu intrari IN1-IN4 la GPIO 16, 14, 12, 13
  red rosu integrat la GPIO 02
  led placa albastru la GPIO 15

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

int analog = 0;

  BLYNK_WRITE(V6){ 

  Serial.print(  "text=");
  Serial.println( param.asStr());
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.print("mesaj=");
  display.print(param.asStr());
  display.display();
  }

void setup() {

  pinMode(12, OUTPUT); // Led green
  pinMode(13, OUTPUT); // Led blue
  pinMode(2, OUTPUT);  // Led blue placa
  pinMode(15, OUTPUT); // Led red
  pinMode(14, OUTPUT); // fara led
  pinMode(16, OUTPUT); // fara led
  

display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Pager RGB HB foto fdbk Blynk");
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
 
  Blynk.virtualWrite(3, analog);
  
  //display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  //display.setCursor(0,0);
  display.print("A0=");
  display.print(analog);
  display.display();
}

BLYNK_WRITE(V12) {
  digitalWrite(12, param.asInt()); // RGB green IN 3 motor
  //in cod GPIO 12,13,14,15
  }
BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); // RGB blue IN 4 motor
  }

BLYNK_WRITE(V14) {
  digitalWrite(14, param.asInt()); // IN2 motor fara led
  }

BLYNK_WRITE(V16) {
  digitalWrite(16, param.asInt()); // IN1 motor fara led
  }

  BLYNK_WRITE(V2) {
  digitalWrite(2, param.asInt()); // Led red 
  }

BLYNK_WRITE(V15) {
  digitalWrite(15, param.asInt()); // Led blue placa
}
