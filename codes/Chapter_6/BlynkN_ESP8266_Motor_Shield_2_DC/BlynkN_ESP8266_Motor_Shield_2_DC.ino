/*
 * varianta NodeMcu 2102 si motor shield
 * butoane pe vrtual V12,13,14,15 pentru 
 * PWMA si PWMB
 * DA Si DB pentru sens
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


int PWMA=5; //run motor A pe D1
int PWMB=4; //run motor B pe D2
int DA=0;   //sens motor A pe D3
int DB=2;   //sens motor A pe D4


BLYNK_WRITE(V12) {    //FW
  digitalWrite(5, param.asInt()); // PWMA pe D1 
  digitalWrite(4, param.asInt()); // PWMB pe D2 
  digitalWrite(0, HIGH); // DA pe D3 sens
  digitalWrite(2, HIGH); // DB pe D2 sens 
}

BLYNK_WRITE(V13) {    //LEFT
  digitalWrite(5, param.asInt()); // PWMA pe D1 
  digitalWrite(4, LOW); // PWMB pe D2 
  digitalWrite(0, HIGH); // DA pe D3 sens
  digitalWrite(2, HIGH); // DB pe D2 sens 
  
}

BLYNK_WRITE(V14) {    //RIGHT 
  digitalWrite(5, LOW); // PWMA pe D1 
  digitalWrite(4, param.asInt()); // PWMB pe D2 
  digitalWrite(0, HIGH); // DA pe D3 sens
  digitalWrite(2, HIGH); // DB pe D2 sens 
  
}

BLYNK_WRITE(V15) {      //BW  
  digitalWrite(5, param.asInt()); // PWMA pe D1 
  digitalWrite(4, param.asInt()); // PWMB pe D2 
  digitalWrite(0, LOW); // DA pe D3 sens
  digitalWrite(2, LOW); // DB pe D2 sens 
  
}

BLYNK_WRITE(V2) {      //STOP  //optional
  digitalWrite(5, LOW); // In1 
  digitalWrite(4, LOW); // In2 
  digitalWrite(0, LOW); // In3
  digitalWrite(2, LOW); // In4 
  
}
void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT); // PWMA pe D1 
  pinMode(4, OUTPUT); // PWMB pe D2 
  pinMode(0, OUTPUT); // DA pe D3 sens
  pinMode(2, OUTPUT); // DB pe D2 sens 
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
      }
