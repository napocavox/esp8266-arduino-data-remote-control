/*necesita libr IRremoteESP8266
 * board node mcu esp8266
 
 * led IR comandat cu BC238 si 20 ohn=mi in colector
 * baza prin 10K pe D4=GPIO2
 brik fotorezistor  GND, +3.3v, S la A0
in Blyk joystick pe virtual V0, modul simplu cu min=-1, max=0, default=0
feedback cu terminal pe virtial V6
feedback analog cu gauge pe V3, 
*/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;

#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
char auth[] = "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"; 
char ssid[] = "nume router";
char pass[] = "password";

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
#include <IRremoteESP8266.h>
#define analogPin A0 //photoresistor to A0
#include <IRsend.h>
int analog = 0;
IRsend irsend(2);
 

  void setup() {

  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
 
  mySwitch.enableTransmit(2);  //IR pin D4
  irsend.begin();
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
//displays on V3 the values read by the photoresistor
    }

  BLYNK_WRITE(V1) 
    {
    if (param.asInt() == 1){
    for (int i = 0; i < 4; i++)
    { 
    irsend.send(NEC,0xF7C03F, 32);  //touch ON for led strip
    }
    Blynk.virtualWrite(6, " strip ON"); 
    }

  if (param.asInt() == -1){
    for (int i = 0; i < 4; i++)
    {
    irsend.send(NEC,0xF740BF, 32);// touch OFF led strip
    }
    Blynk.virtualWrite(6, " strip OFF"); 
    }
    }
