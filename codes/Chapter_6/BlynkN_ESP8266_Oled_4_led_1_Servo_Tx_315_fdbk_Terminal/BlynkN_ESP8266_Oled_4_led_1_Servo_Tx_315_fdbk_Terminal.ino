/*
 * buttons on virtual V12,13,14,15 for LEDs
 * joystick on V0 for servo mmin=-1 max=1
 * slider on V1 for servo2 mmin=0 max=180
 * gauge on V3 for feedback min=0 max=700
 * fdbk on A0 from LEDs
 * terminal on V6, displays on monitor
 * text sent from Android
 * I have not checked the servo
 */

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;

char ssid[] = "nume router";
char pass[] = "password";

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#include <Servo.h>

//Servo Servo1;// on D4, in code GPIO2
Servo Servo2;// on D3, in code GPIO0

int tetha;
int tetha2;

#define analogPin A0 //connect the cursor of servo potentiometer to A0
int analog = 0;

BLYNK_WRITE(V0) 
{
  tetha = param.asInt();
  if (param.asInt() == 1)
    {
    
    mySwitch.send(9465730, 24);
   //mySwitch2.send("100100000110111110000011"); 
   
   Blynk.virtualWrite(6, " ON Office"); 
   // displays the message cod sent
    //delay(40);
  }

  if (param.asInt() == -1)
  { 
   mySwitch.send("100100000110111110000011"); //works with this code
   //mySwitch.send(9465732, 24);//on /off 4 times, I don't know why
   //office off key code, also works with binary
   Serial.println("OFF birou");//optional
   Blynk.virtualWrite(6, " OFF office"); 
   // displays the message cod sent  
  }
}

BLYNK_WRITE(V1) 
{
  tetha2 = param.asInt();
}

BLYNK_WRITE(V12) {
  digitalWrite(12, param.asInt()); // led 1 
  //in cod GPIO 12,13,14,15
}
BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); // Led 2
}
BLYNK_WRITE(V14) {
  digitalWrite(14, param.asInt()); // Led3
}
BLYNK_WRITE(V15) {
  digitalWrite(15, param.asInt()); // Led 4
}

BLYNK_WRITE(V6){ 

Serial.print(  "text=");
Serial.println( param.asStr());

}
void setup() {
  Serial.begin(115200);
  mySwitch.enableTransmit(2);//Tx on D4
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
   
  timer.setInterval(200L, sendUptime); 
//  Servo1.attach(2); //attach servo 1 to D4
  Servo2.attach(0); //attach servo 2 to D3
  
  pinMode(12, OUTPUT); // Led 1
  pinMode(13, OUTPUT); // Led 2
  pinMode(14, OUTPUT); // Led 3
  pinMode(15, OUTPUT); // Led 4
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
  timer.run();
//  Servo1.write(tetha);  //rotate the servo1
  Servo2.write(tetha2); //rotate the servo2

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("S1=");
  display.println(tetha);
  display.print("S2=");
  display.println(tetha2);
  display.print("A0=");
  display.print(analog);
  display.display();
      }

      void sendUptime()
        {
    analog= analogRead(analogPin); 
      Blynk.virtualWrite(3, analog);
        }
