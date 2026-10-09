/*requires IRremoteESP8266 libr
 * board node mcu esp8266
 
 * IR LED driven by BC238 with 20 ohms in the collector
 * base through 10K on D4=GPIO2
 photoresistor brick  GND, +3.3v, S to A0
in Blynk joystick on virtual V0, simple mode with min=-1, max=0, default=0
feedback with terminal on virtual V6
analog feedback with gauge on V3,
*/

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <DHT.h>

#define DHTPIN 15//it is pin D8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <SimpleTimer.h>
SimpleTimer timer;
float humidity, temp_f; // Values read from sensor


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
    
    float h = dht.readHumidity();
delay(300);
float t = dht.readTemperature();
delay(300);
Blynk.virtualWrite(4, h);// gauge on V4
Blynk.virtualWrite(5, t);//gauge on V5

    
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
