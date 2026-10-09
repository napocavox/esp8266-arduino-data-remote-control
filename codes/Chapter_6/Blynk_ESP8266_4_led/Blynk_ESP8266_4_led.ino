
//https://blynk.cloud/dashboard/71282/product/139611/info

#define BLYNK_TEMPLATE_ID "replace with your Blynk ID"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "replace with your Blynk Auth Token"

/* Comment this out to disable prints and save space */
//#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "UPCF4821BC";
char pass[] = "Gherla1956";

//Get the button value
BLYNK_WRITE(V12) {
  digitalWrite(12, param.asInt()); // LEDs on D5,6,7,8
  //in cod GPIO 12,13,14,15
}
BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); 
}
BLYNK_WRITE(V14) {
  digitalWrite(14, param.asInt()); 
  Serial.print(param.asInt());
}
BLYNK_WRITE(V15) {
  digitalWrite(15, param.asInt()); 
}

void setup() {
  Serial.begin(115200);
 
  //Set the Relay pins as an output
  pinMode(12, OUTPUT); // led 1
  pinMode(13, OUTPUT); // led 2
  pinMode(14, OUTPUT); // led 3
  pinMode(15, OUTPUT); // led 4
  //Initialize the Blynk library
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop() {
  //Run the Blynk library
  Blynk.run();
//  Serial.print(param.asInt());
}
