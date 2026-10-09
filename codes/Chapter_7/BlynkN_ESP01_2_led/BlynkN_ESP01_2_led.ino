/*
 * blynk
 * buttons on virtual V12,13,
 * controls LEDs on GPIO 0 and GPIO2
 * board
 * generic ESP8266 module
 * am incarcat folosind adaptorul dedicat
 * 
 */
/*
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);
*/
// works without the lines above for oled
//also works without them but only with the dedicated shield
//and only one relay
#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//#include <SimpleTimer.h>
//SimpleTimer timer;

const char* ssid = "UPCF4821BC";//type your ssid
const char* pass = "Gherla1956";//type your password
 

//#include <RCSwitch.h>
//RCSwitch mySwitch = RCSwitch();

//#include <Servo.h>

//Servo Servo1;// on D4, in code GPIO2
//Servo Servo2;// on D3, in code GPIO0

//int tetha;
//int tetha2;

//#define analogPin A0 //connect the cursor of servo potentiometer to A0
//int analog = 0;





BLYNK_WRITE(V12) {
  digitalWrite(2, param.asInt()); // led 1 
  //in cod GPIO 12,13,14,15
}
BLYNK_WRITE(V13) {
  digitalWrite(0, param.asInt()); // Led 2
}



void setup() {
  Serial.begin(115200);
///mySwitch.enableTransmit(2);//Tx on D4
  //display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
   
//  timer.setInterval(200L, sendUptime); 
//  Servo1.attach(2); //attach servo 1 to D4
  //Servo2.attach(0); //attach servo 2 to D3
  
  pinMode(2, OUTPUT); // Led 1
  pinMode(0, OUTPUT); // Led 2
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
  //timer.run();
//  Servo1.write(tetha);  //rotate the servo1
  //Servo2.write(tetha2); //rotate the servo2

      }

      
