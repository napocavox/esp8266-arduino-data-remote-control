
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>

#include <LiquidCrystal.h>


#define D0 3 // GPIO3 maps to Ardiuno D0
#define D1 1 // GPIO1 maps to Ardiuno D1
#define D2 16 // GPIO16 maps to Ardiuno D2
#define D3 5 // GPIO5 maps to Ardiuno D3
#define D4 4 // GPIO4 maps to Ardiuno D4
#define D5 14 // GPIO14 maps to Ardiuno D5
#define D6 12 // GPIO12 maps to Ardiuno D6
#define D7 13 // GPIO13 maps to Ardiuno D7
#define D8 0 // GPIO0 maps to Ardiuno D8
#define D9 2 // GPIO2 maps to Ardiuno D9
#define D10 15 // GPIO15 maps to Ardiuno D10


char auth[] = "auth token";
char ssid[] = "nume router";
char pass[] = "password";


SimpleTimer timer;

LiquidCrystal lcd(D8,D9,D4,D5,D6,D7); 

#define analogPin A0 
void setup()
{  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  int cursorPosition=0;
  lcd.begin(16, 2);
  lcd.print("pager blynk");  
  timer.setInterval(1000L, sendUptime);
  
  delay(500);
}

BLYNK_WRITE(V6){ //terminal pe V6
Serial.print(  "text=");
Serial.println( param.asStr());
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("text=");
  lcd.print(param.asStr());  
}

void sendUptime() {
int analog= analogRead(analogPin); 
//gauge pe V3, afiseaza valoare butoane
Blynk.virtualWrite(3, analog);

  lcd.setCursor(9,1);
  lcd.print("A0=");
  lcd.print(analog); 
  lcd.print("     "); 
}
void loop()
{
  Blynk.run();
  timer.run(); // Initiates SimpleTimer   
}
