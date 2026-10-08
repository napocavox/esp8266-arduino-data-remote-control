/*
 * 
 ESP8266 cu ST7735 TFT1.8 inch
 voltmetru analogic 
 potentiometru 10K pe 3v, GND si Ao
afiseaza pe TFT tensiunea 
si trimite prin Blynk pentru Gauge pe V3
 */
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
char auth[] ="goLXmyUSeC5KoAd2antGXx6tZwLHm8Nd";

#define analogPin A0

SimpleTimer timer;

// Define meter size
#define M_SIZE 0.667//original cel mai bun

#include <Adafruit_GFX.h>      // include Adafruit graphics library
#include <Adafruit_ST7735.h>   // include Adafruit ST7735 ST7735 library


// ST7735 ST7735 module connections
#define ST7735_RST   D4     // ST7735 RST pin is connected to NodeMCU pin D4 (GPIO2)
#define ST7735_CS    D3     // ST7735 CS  pin is connected to NodeMCU pin D4 (GPIO0)
#define ST7735_DC    D2     // ST7735 DC  pin is connected to NodeMCU pin D4 (GPIO4)

// initialize ST7735 ST7735 library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)=SDA
Adafruit_ST7735 ST7735 = Adafruit_ST7735(ST7735_CS, ST7735_DC, ST7735_RST);
     // Invoke custom library

#define ST7735_GREY 0x5AEB
#define ST7735_ORANGE      0xFD20      /* 255, 165,   0 */

float ltx = 0;    // Saved x coord of bottom of needle
uint16_t osx = M_SIZE*120, osy = M_SIZE*120; // Saved x & y coords
uint32_t updateTime = 0;       // time for next update

int old_analog =  -999; // Value last displayed

int value[6] = {0, 0, 0, 0, 0, 0};
int old_value[6] = { -1, -1, -1, -1, -1, -1};
int d = 0;

void setup(void) {

  Blynk.begin(auth, "SSID", "pass"); //insert here your SSID and password
 timer.setInterval(1000L, sendUptime);
  delay(500);
  
  ST7735.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  uint16_t time = millis();
  ST7735.fillScreen(ST7735_BLACK);
  time = millis() - time;
  ST7735.setRotation(1);
  //zero afiseaza landscape
  //1 afiseaza portrait
  delay(500);

  analogMeter(); // Draw analogue meter
  
ST7735.setCursor(0, 90);
ST7735.setTextColor(ST7735_YELLOW);
ST7735.setTextSize(1); 
     ST7735.print("analog volt U[%] Blynk");
  updateTime = millis(); // Next update time
}

void sendUptime() {
//trimite analog pe virtual V3, gauge
int analog= analogRead(analogPin); 
Blynk.virtualWrite(3,"analog=");
Blynk.virtualWrite(3, analog);
    ST7735.setCursor(0, 100);
    //ST7735.setTextSize(2); //optional
    ST7735.print("U=");
    ST7735.print(analog);
}

BLYNK_WRITE(V6){ 

//primeste mesaj de la Blynk Android
Serial.print(  "text=");      //optional
Serial.println( param.asStr()); //optional
     ST7735.print(" mesaj=");
     ST7735.print(param.asStr());
}

void loop() {

  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
  
  if (updateTime <= millis()) {
    updateTime = millis() + 35; // Update meter every 35 milliseconds
 
int analog = analogRead(A0);
//pot 10K legat la +3,3V, GND si Ao
value[0]=map(analog,0,1023,0,100);
    
    plotNeedle(value[0], 0); // It takes between 2 and 14ms to replot the needle with zero delay
    //Serial.println(millis()-tt);
  }
}


// #########################################################################
//  Draw the analogue meter on the screen
// #########################################################################
void analogMeter()
  {
  // Meter outline
  ST7735.fillRect(0, 0, M_SIZE*239, M_SIZE*131, ST7735_GREY);
  ST7735.fillRect(1, M_SIZE*3, M_SIZE*234, M_SIZE*125, ST7735_WHITE);

  ST7735.setTextColor(ST7735_BLACK);  // Text colour

  // Draw ticks every 5 degrees from -50 to +50 degrees (100 deg. FSD swing)
  for (int i = -50; i < 51; i += 5) {
    // Long scale tick length
    int tl = 15;

    // Coodinates of tick to draw
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    uint16_t y0 = sy * (M_SIZE*100 + tl) + M_SIZE*150;
    uint16_t x1 = sx * M_SIZE*100 + M_SIZE*120;
    uint16_t y1 = sy * M_SIZE*100 + M_SIZE*150;

    // Coordinates of next tick for zone fill
    float sx2 = cos((i + 5 - 90) * 0.0174532925);
    float sy2 = sin((i + 5 - 90) * 0.0174532925);
    int x2 = sx2 * (M_SIZE*100 + tl) + M_SIZE*120;
    int y2 = sy2 * (M_SIZE*100 + tl) + M_SIZE*150;
    int x3 = sx2 * M_SIZE*100 + M_SIZE*120;
    int y3 = sy2 * M_SIZE*100 + M_SIZE*150;

    // Yellow zone limits  //se poate renunta la yellow
    if (i >= -50 && i < 0) {
      ST7735.fillTriangle(x0, y0, x1, y1, x2, y2, ST7735_YELLOW);
      ST7735.fillTriangle(x1, y1, x2, y2, x3, y3, ST7735_YELLOW);
    }

    // Green zone limits
    if (i >= 0 && i < 25) {
      ST7735.fillTriangle(x0, y0, x1, y1, x2, y2, ST7735_GREEN);
      ST7735.fillTriangle(x1, y1, x2, y2, x3, y3, ST7735_GREEN);
    }

    // Orange zone limits
    if (i >= 25 && i < 50) {
      ST7735.fillTriangle(x0, y0, x1, y1, x2, y2, ST7735_ORANGE);
      ST7735.fillTriangle(x1, y1, x2, y2, x3, y3, ST7735_ORANGE);
    }

    // Short scale tick length
    if (i % 25 != 0) tl = 8;

    // Recalculate coords in case tick lenght changed
    x0 = sx * (M_SIZE*100 + tl) + M_SIZE*120;
    y0 = sy * (M_SIZE*100 + tl) + M_SIZE*150;
    x1 = sx * M_SIZE*100 + M_SIZE*120;
    y1 = sy * M_SIZE*100 + M_SIZE*150;

    // Draw tick
    ST7735.drawLine(x0, y0, x1, y1, ST7735_BLACK);

    // Check if labels should be drawn, with position tweaks
    if (i % 25 == 0) {
      // Calculate label positions


   //pozitioneaza zero la stanga 
      x0 = cos((-50 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sin((-50 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*150; 
     
     ST7735.setCursor(x0+4, y0-4);
     ST7735.print("0");

//pozitioneaza 25% deplasat 
      x0 = cos((-50+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sin((-50+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*150;     
     
     ST7735.setCursor(x0-3, y0);
     ST7735.print("25%");
     
//pozitioneaza 50% la mijloc 
      x0 = cos((-50+25+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sin((-50+25+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*150;   
     
     ST7735.setCursor(x0-10, y0);
     ST7735.print("50%");

//pozitioneaza 75% la 3/4 din scala
      x0 = cos((-50+25+25+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sin((-50+25+25+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*150;   
     
     ST7735.setCursor(x0-3, y0);
     ST7735.print("75%");

//pozitioneaza 100% la dreapta
      x0 = cos((-50+25+25+25+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*120;
      y0 = sin((-50+25+25+25+25 - 90) * 0.0174532925) * (M_SIZE*100 + tl + 10) + M_SIZE*150;   
     
     ST7735.setCursor(x0-15, y0);  //
     ST7735.print("100%");    
    }

    // Now draw the arc of the scale
    sx = cos((i + 5 - 90) * 0.0174532925);
    sy = sin((i + 5 - 90) * 0.0174532925);
    x0 = sx * M_SIZE*100 + M_SIZE*120;
    y0 = sy * M_SIZE*100 + M_SIZE*150;
    // Draw scale arc, don't draw the last part
    if (i < 50) ST7735.drawLine(x0, y0, x1, y1, ST7735_BLACK);
  }

  plotNeedle(0, 0); // Put meter needle at 0
}

// #########################################################################
// Update needle position
// This function is blocking while needle moves, time depends on ms_delay
// 10ms minimises needle flicker if text is drawn within needle sweep area
// Smaller values OK if text not in sweep area, zero for instant movement but
// does not look realistic... (note: 100 increments for full scale deflection)
// #########################################################################


void plotNeedle(int value, byte ms_delay)
{
  ST7735.setTextColor(ST7735_BLACK, ST7735_WHITE);
  char buf[8]; 
  dtostrf(value, 4, 0, buf);
 // ST7735.drawRightString(buf, 33, M_SIZE*(119 - 20), 2);

  if (value < -10) value = -10; // Limit value to emulate needle end stops
  if (value > 110) value = 110;

  // Move the needle until new value reached
  while (!(value == old_analog)) {
    if (old_analog < value) old_analog++;
    else old_analog--;

    if (ms_delay == 0) old_analog = value; // Update immediately if delay is 0

    float sdeg = map(old_analog, -10, 110, -150, -30); // Map value to angle
    // Calculate tip of needle coords
    float sx = cos(sdeg * 0.0174532925);
    float sy = sin(sdeg * 0.0174532925);

    // Calculate x delta of needle start (does not start at pivot point)
    float tx = tan((sdeg + 90) * 0.0174532925);

    // Erase old needle image
    ST7735.drawLine(M_SIZE*(120 + 24 * ltx) - 1, M_SIZE*(150 - 24), osx - 1, osy, ST7735_WHITE);
    ST7735.drawLine(M_SIZE*(120 + 24 * ltx), M_SIZE*(150 - 24), osx, osy, ST7735_WHITE);
    ST7735.drawLine(M_SIZE*(120 + 24 * ltx) + 1, M_SIZE*(150 - 24), osx + 1, osy, ST7735_WHITE);

    // Re-plot text under needle
    ST7735.setTextColor(ST7735_BLACK, ST7735_WHITE);

    // Store new needle end coords for next erase
    ltx = tx;
    osx = M_SIZE*(sx * 98 + 120);
    osy = M_SIZE*(sy * 98 + 150);

    // Draw the needle in the new postion, magenta makes needle a bit bolder
    // draws 3 lines to thicken needle
    ST7735.drawLine(M_SIZE*(120 + 24 * ltx) - 1, M_SIZE*(150 - 24), osx - 1, osy, ST7735_RED);
    ST7735.drawLine(M_SIZE*(120 + 24 * ltx), M_SIZE*(150 - 24), osx, osy, ST7735_MAGENTA);
    ST7735.drawLine(M_SIZE*(120 + 24 * ltx) + 1, M_SIZE*(150 - 24), osx + 1, osy, ST7735_RED);

    // Slow needle down slightly as it approaches new postion
    if (abs(old_analog - value) < 10) ms_delay += ms_delay / 5;

    // Wait before next update
    delay(ms_delay);
  }
}
