/*requires IRremoteESP8266 libr
 
 * RGB on pins D5,6,7,8, controlled by V12, 13, 15
 * 
 feedback with photoresistor
 * 
 IR on D2 with adapter
 Tx 315 on D1
//in code D4 for IR
//in code D5 for 315

displays the codes
in Blyk joystick
virtual V0, V1 simple mode with min=-1, max=0, default=0
feedback with terminal on virtual V6
analog feedback with gauge on V3,

brik fotorezistor  
+3.3v to A0

*/
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
SimpleTimer timer;


#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
char auth[] = "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"; 
char ssid[] = "UPCF4821BC";
char pass[] = "Gherla1956";

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
#include <IRremoteESP8266.h>
#define analogPin A0 //photoresistor to A0
#include <IRsend.h> 
int analog = 0;
IRsend irsend(4);

void setup() {

  pinMode(12, OUTPUT); // Led 1
  pinMode(13, OUTPUT); // Led 2
  pinMode(14, OUTPUT); // Led 3//D5//ground//required for pcb
  pinMode(15, OUTPUT); // Led 4
  
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  
  mySwitch.enableTransmit(5);
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
  //Blynk.virtualWrite(5, analog);
  Blynk.virtualWrite(3, analog);
  //displays on V5 the values read by the photoresistor
}

BLYNK_WRITE(V12) {
  digitalWrite(12, param.asInt()); // led 1 
  //in cod GPIO 12,13,14,15
}
BLYNK_WRITE(V13) {
  digitalWrite(13, param.asInt()); // Led 2
}

BLYNK_WRITE(V15) {
  digitalWrite(15, param.asInt()); // Led 4
}


BLYNK_WRITE(V0)

{
    if (param.asInt() == 1)
    {
    
    mySwitch.send(9465730, 24);
   //mySwitch2.send("100100000110111110000011"); 
   
   //Blynk.virtualWrite(12, " ON OFFICE"); 
   Blynk.virtualWrite(6, " ON OFFICE");
   // displays the message cod sent
    //delay(40);
  }

  if (param.asInt() == -1)
  { 
   mySwitch.send("100100000110111110000011");  
   //mySwitch.send(806192, 24);
   //office off key code, also works with binary
   Serial.println("OFF birou");//optional
   //Blynk.virtualWrite(12, " OFF office"); 
   Blynk.virtualWrite(6, " OFF office"); 
   // displays the message cod sent  
  }
}

////////////////// from here IR
BLYNK_WRITE(V1) 
{
    if (param.asInt() == 1){
     for (int i = 0; i < 4; i++)
  { 
   irsend.send(NEC,0xF7C03F, 32);//touch ON for led strip
     }
    //Blynk.virtualWrite(12, " strip ON");
    Blynk.virtualWrite(6, " strip ON"); 
  }

  //joystick on V1, sends 1=ON,
  //sends -1  OFF
if (param.asInt() == -1){
    for (int i = 0; i < 4; i++)
  {
    irsend.send(NEC,0xF740BF, 32);// touch OFF led strip
    // mySwitch2.send("100100000110111110000011"); 
      
     }
     //Blynk.virtualWrite(12, " strip OFF");
     Blynk.virtualWrite(6, " strip OFF"); 
    //delay(40);
  }
  
}

//code template for other functions
/*
BLYNK_WRITE(V1)

{
    if (param.asInt() == 1){
   
   mySwitch.send("100100000110111110000011");  
   
   //mySwitch.send(806192, 24);
   //office off key code, also works with binary
   Serial.println("OFF birou");//optional
   Blynk.virtualWrite(12, " OFF office"); 
   // displays the message cod sent  
  }
}

BLYNK_WRITE(V8)

{
    if (param.asInt() == 1){
   
   mySwitch.send("000011000100110111000000");   
   //mySwitch.send(806336, 24);
   Serial.println("A Yam");//optional
   Blynk.virtualWrite(12, "A Yam"); 
   // displays the message cod sent
    
  }
}


BLYNK_WRITE(V3)
//button on Virtual V3
{
    if (param.asInt() == 1){  
   mySwitch.send(9465732, 24);
   //also works with decimal//
   //Serial.println("Birou 1");//optional
   Blynk.virtualWrite(12, " OFFICE 1"); 
   // displays the message cod sent
  }
}

BLYNK_WRITE(V13)
//button on Virtual V13, controls key 2 of the office TLC
{
    if (param.asInt() == 1){
   
   //mySwitch.send("100100000110111110001000");   
   //also works with binary
   mySwitch.send(9465736, 24);
   //also works with decimal//
   //Serial.println("Birou 2");//optional
   Blynk.virtualWrite(12, " OFFICE 2"); 
   // displays the message cod sent
  }
}

BLYNK_WRITE(V11)
//button on Virtual V11, controls the Sleep key of the office TLC
{
    if (param.asInt() == 1){
   
   //mySwitch.send("100100000110111110000001");   
   mySwitch.send(9465729, 24);
   //also works with decimal//
   //Serial.println("Birou Sleep");//optional
   Blynk.virtualWrite(12, " SLEEP"); 
   // displays the message cod sent
  }
}
*/
