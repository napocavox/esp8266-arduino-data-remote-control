/*
 * terminal pe V6, afiseaza pe Oled
 * text trimis de pe Android cu Terminal pe V6
 */

#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_ST7735.h>   // include Adafruit ST7735 TFT library
// ST7735 TFT module connections
#define TFT_RST   D4     // TFT RST pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS    D3     // TFT CS  pin is connected to NodeMCU pin D4 (GPIO0)
#define TFT_DC    D2     // TFT DC  pin is connected to NodeMCU pin D4 (GPIO4)
//#define TFT_RST   D1    //se poate defini RST cu D1
//DC=A0
// initialize ST7735 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)=SDA
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);



#define BLYNK_TEMPLATE_ID "TMPLljpFJSc-"
#define BLYNK_TEMPLATE_NAME "4 led"
#define BLYNK_AUTH_TOKEN "goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "SSID";
char pass[] = "pass";


BLYNK_WRITE(V6){ 

Serial.print(  "text=");
Serial.println( param.asStr());

//tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab//necesar
  tft.fillScreen(ST7735_BLACK);//
//tft.fillScreen(ST7735_BLUE);
  tft.setRotation(3);//roteste ecranul
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  //tft.setTextSize(3);
  tft.drawPixel(tft.width(), tft.height(), ST7735_GREEN);
  //tft.setTextColor(ST7735_RED);
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextWrap(true);//nu suprapune
tft.print("text=");
tft.print(param.asStr());
}


void setup() {
  Serial.begin(115200);
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab//necesar
  
  tft.fillScreen(ST7735_BLACK);//afiseaza pe coloana
  //tft.fillScreen(ST7735_GREEN);
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  //tft.drawPixel(tft.width(), tft.height(), ST7735_GREEN);
  tft.setTextColor(ST7735_MAGENTA);
  //tft.setTextWrap(true);
  tft.print("Pager Blynk text");  
  delay(2000);
  //tft.fillScreen(ST7735_BLACK);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }

void loop() {
  Blynk.run();
      }

      
