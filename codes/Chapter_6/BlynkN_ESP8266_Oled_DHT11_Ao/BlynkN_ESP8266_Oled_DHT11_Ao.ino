/**************************************************************
 biblio
 *   http://playground.arduino.cc/Code/SimpleTimer
 **************************************************************/
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SimpleTimer.h>

#define DHTPIN 2    //este pinul D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

char auth[] ="goLXmyUSeC5KoAd2antGXx6tZwLHm8Nda";
//#define BLYNK_AUTH_TOKEN "goLXmyUSeC5KoAd2antGXx6tZwLHm8Ndb"

SimpleTimer timer;
//float humidity, temp_f; // Values read from sensor
#define analogPin A0 //connect the cursor of servo potentiometer to A0
 
 //int analog = 0;
 
void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, "UPCF4821BC", "Gherla1956"); //insert here your SSID and password
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  
  // seteaza intervalele la care va trimite datele
  timer.setInterval(1000L, sendUptime);
  delay(500);
}


void sendUptime() {

float h = dht.readHumidity();
delay(300);
float t = dht.readTemperature();
delay(300);
Blynk.virtualWrite(4, h);
Blynk.virtualWrite(5, t);

int analog= analogRead(analogPin); 
Blynk.virtualWrite(14,"analog=");
Blynk.virtualWrite(14, analog);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("T=");
  display.print(t);
  display.print("   H=");
  display.println(h);
  display.print("A=");
  display.println(analog);
  display.display();
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
  
}
