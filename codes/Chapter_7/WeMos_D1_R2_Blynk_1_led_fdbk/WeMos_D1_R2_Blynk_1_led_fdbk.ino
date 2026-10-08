/*
 * butoane pe vrtual V12,13,14,15 pentru leduri
 * merge cu un singur led si fdbk pe D13
 * comandat de buton pe V13
 * leduri pe D12, 111 si butoane pe V12, 14 15 blocheaza
 * gauge pe V3 pentru feedback min=0 max=700
 */



#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;

char ssid[] = "UPCF4821BC";
char pass[] = "Gherla1956";



#define analogPin A0 //connect the cursor of servo potentiometer to A0
 int analog = 0;




//Get the button value

BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); // Relay 2
}


 
void setup() {
  Serial.begin(115200);

  
   
  timer.setInterval(100L, sendUptime); 
  
  
  pinMode(13, OUTPUT); // Relay 2
  
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
  timer.run();
  
      }

      void sendUptime()
        {
    analog= analogRead(analogPin); 
      Blynk.virtualWrite(3, analog);
        }
