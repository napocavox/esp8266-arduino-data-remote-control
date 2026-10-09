/*
  analog feedback with gauge on V3,
  messages on Terminal V6
  photoresistor to A0
  H-bridge with inputs IN1-IN4 to GPIO 16, 14, 12, 13
  built-in red LED on GPIO 02  and servo 1
  blue board LED on GPIO 15  and servo 2
  I set the joystick on V15 and V2 with values between 0 and 180
  the red LED and the blue board LED also work
  however, when I connect I must disconnect
  the servo input on GPIO 2, otherwise it freezes
  but if I connect after it starts, then it works
  
  it would be best to connect the servo to D14 and D16, which have no LEDs
  and to connect HB to D2 , D15, D12, D13
  on GPIO15 it works without problems
  I tried with only one servo
  

*/

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;


#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
char auth[] = "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"; 
char ssid[] = "UPCF4821BC";
char pass[] = "Gherla1956";

#include <Servo.h>
//Servo Servo1;// on D2, in code GPIO 2
Servo Servo2;// on D15, in code GPIO 15

//int tetha;
int tetha2;

#define analogPin A0 //photoresistor to A0

int analog = 0;

BLYNK_WRITE(V6){ 

  Serial.print(  "text=");
  Serial.println( param.asStr());
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("message=");
  display.print(param.asStr());
  display.display();
  }

void setup() {

  pinMode(12, OUTPUT); // Led green
  pinMode(13, OUTPUT); // Led blue
  pinMode(2, OUTPUT);  // Blue board LED and servo
  pinMode(15, OUTPUT); // Red LED and servo
  pinMode(14, OUTPUT); //no LED
  pinMode(16, OUTPUT);  //no LED

  //Servo1.attach(2); //attach servo 1 to D2
  Servo2.attach(15); //attach servo 2 to D15
  
  

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Pager Servo HB RGB fdbk Blynk");
  display.display();
  
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
    
  timer.setInterval(500L, sendUptime);
    }
    
  void loop() {
  Blynk.run(); 
  timer.run(); 
 /*
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
  */
  }

  void sendUptime()
  {
  analog= analogRead(analogPin);  
  Blynk.virtualWrite(3, analog);
  
  //display.clearDisplay();
  //display.setTextSize(2);
  //display.setTextColor(WHITE);
  //display.setCursor(0,0);
  //display.print("A0=");
  //display.print(analog);
  
  //display.display();
  }

BLYNK_WRITE(V12) {
  digitalWrite(12, param.asInt()); // RGB green IN 3 motor
  //in cod GPIO 12,13,14,15
}

BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); // RGB blue IN 4 motor
}


BLYNK_WRITE(V14) {
  digitalWrite(14, param.asInt()); // IN2 motor no LED
}

BLYNK_WRITE(V16) {
  digitalWrite(16, param.asInt()); // IN1 motor no LED
}

BLYNK_WRITE(V2) {
  digitalWrite(2, param.asInt()); // Led red 
  //digitalWrite(0, param.asInt()); // Led red 
//tetha = param.asInt();//servo on GPIO 02
//Servo1.write(tetha);  //rotate the servo1
}

BLYNK_WRITE(V15) {
  digitalWrite(15, param.asInt()); // Blue board LED
  tetha2 = param.asInt();//servo on GPIO 15
  Servo2.write(tetha2); //rotate the servo2
  }
