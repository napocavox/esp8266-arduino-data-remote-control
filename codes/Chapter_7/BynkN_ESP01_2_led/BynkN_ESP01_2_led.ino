/*
 * blynk
 * butoane pe vrtual V12,13,
 * comanda leduri pe GPIO 0 si GPIO2
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
// merge fara liniile de sus pentru oled
//merge si fara ele dar numai cu shieldul dedicat
//si numai un releu
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

//Servo Servo1;// pe D4 in cod GPIO2
//Servo Servo2;// pe D3 in cod GPIO0

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
///mySwitch.enableTransmit(2);//Tx pe D4
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

      
