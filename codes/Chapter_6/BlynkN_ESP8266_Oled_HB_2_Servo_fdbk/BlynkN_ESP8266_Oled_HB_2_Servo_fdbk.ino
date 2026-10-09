/*
 * buttons on virtual V12,13,14,15 for LEDs
 * slider on V0 for servo mmin=0 max=180
 * slider on V1 for servo2 mmin=0 max=180
 * gauge on V3 for feedback min=0 max=700
 * H-bridge on D5,6,7,8, works
 * fdbk on A0 from LEDs
 */

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#define BLYNK_TEMPLATE_ID "your Blynk ID"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "your Blynk Auth Token"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;

char ssid[] = "nume router";
char pass[] = "password";

#include <Servo.h>

Servo Servo1;// on D4, in code GPIO2
Servo Servo2;// on D3, in code GPIO0

int tetha;
int tetha2;

#define analogPin A0 //connect the cursor of servo potentiometer to A0
int analog = 0;

BLYNK_WRITE(V0) 
{
  tetha = param.asInt();
}

BLYNK_WRITE(V1) 
{
  tetha2 = param.asInt();
}

BLYNK_WRITE(V12) {    //FW
  digitalWrite(15, param.asInt()); // In1 
  digitalWrite(13, LOW); // In2 
  digitalWrite(12, param.asInt()); // In3
  digitalWrite(14, LOW); // In4 
  //in cod GPIO 12,13,14,15
  //display.print("FW");  //works but is optional
  //display.display();
}

BLYNK_WRITE(V13) {    //LEFT
  digitalWrite(15, LOW); // In1 
  digitalWrite(13, LOW); // In2 
  digitalWrite(12, param.asInt()); // In3
  digitalWrite(14, LOW); // In4 
  //display.print("LEFT");
  //display.display();
}

BLYNK_WRITE(V14) {    //RIGHT 
  digitalWrite(15, param.asInt()); // In1 
  digitalWrite(13, LOW); // In2 
  digitalWrite(12, LOW); // In3
  digitalWrite(14, LOW); // In4 
  //display.print("RIGHT"); //works but is optional
  //display.display();
}

BLYNK_WRITE(V15) {      //BW  
  digitalWrite(15, LOW); // In1 
  digitalWrite(13, param.asInt()); // In2 
  digitalWrite(12, LOW); // In3
  digitalWrite(14, param.asInt()); // In4 
  //display.print("BW");
  //display.display();
}

BLYNK_WRITE(V2) {      //STOP  //not necessary
  digitalWrite(15, LOW); // In1 
  digitalWrite(13, LOW); // In2 
  digitalWrite(12, LOW); // In3
  digitalWrite(14, LOW); // In4 
  //display.print("STOP");  //works but is optional
  //display.display();
}
void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
   
  timer.setInterval(500L, sendUptime); 
  Servo1.attach(2); //attach servo 1 to D4
  Servo2.attach(0); //attach servo 2 to D3
  
  pinMode(12, OUTPUT); // In3
  pinMode(13, OUTPUT); // In3
  pinMode(14, OUTPUT); // In4
  pinMode(15, OUTPUT); // In1
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
  timer.run();
  Servo1.write(tetha);  //rotate the servo1
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
