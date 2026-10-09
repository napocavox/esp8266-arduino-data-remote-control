/*
 * NodeMcu 2102 variant and motor shield
 * buttons on virtual V12,13,14,15 for
 * PWMA and PWMB
 * DA and DB for direction
 * 
 */


#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-a"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nda"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "nume router";
char pass[] = "password";

#include <Servo.h>


int PWMA=5; //run motor A on D1
int PWMB=4; //run motor B on D2
int DA=0;   //direction motor A on D3
int DB=2;   //direction motor A on D4


BLYNK_WRITE(V12) {    //FW
  digitalWrite(5, param.asInt()); // PWMA on D1
  digitalWrite(4, param.asInt()); // PWMB on D2
  digitalWrite(0, HIGH); // DA on D3 direction
  digitalWrite(2, HIGH); // DB on D2 direction
}

BLYNK_WRITE(V13) {    //LEFT
  digitalWrite(5, param.asInt()); // PWMA on D1
  digitalWrite(4, LOW); // PWMB on D2
  digitalWrite(0, HIGH); // DA on D3 direction
  digitalWrite(2, HIGH); // DB on D2 direction
  
}

BLYNK_WRITE(V14) {    //RIGHT 
  digitalWrite(5, LOW); // PWMA on D1
  digitalWrite(4, param.asInt()); // PWMB on D2
  digitalWrite(0, HIGH); // DA on D3 direction
  digitalWrite(2, HIGH); // DB on D2 direction
  
}

BLYNK_WRITE(V15) {      //BW  
  digitalWrite(5, param.asInt()); // PWMA on D1
  digitalWrite(4, param.asInt()); // PWMB on D2
  digitalWrite(0, LOW); // DA on D3 direction
  digitalWrite(2, LOW); // DB on D2 direction
  
}

BLYNK_WRITE(V2) {      //STOP  //optional
  digitalWrite(5, LOW); // In1 
  digitalWrite(4, LOW); // In2 
  digitalWrite(0, LOW); // In3
  digitalWrite(2, LOW); // In4 
  
}
void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT); // PWMA on D1
  pinMode(4, OUTPUT); // PWMB on D2
  pinMode(0, OUTPUT); // DA on D3 direction
  pinMode(2, OUTPUT); // DB on D2 direction
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
      }
