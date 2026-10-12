# Libraries — *Data and Remote Control with ESP8266 and Arduino*

These are the library versions used and tested by the author. Copy the folders you need into the `libraries` folder of your Arduino sketchbook (usually `Documents/Arduino/libraries`) and restart the Arduino IDE. Each library keeps its original licence file; the copyright belongs to its authors.

| Library | Version | Used by codes in chapters | Original source | Licence |
|---|---|---|---|---|
| [`Adafruit_GFX_Library`](Adafruit_GFX_Library) | 1.11.7 | 1, 2, 3, 4, 6, 7 | [link](https://github.com/adafruit/Adafruit-GFX-Library) | [license.txt](Adafruit_GFX_Library/license.txt) |
| [`Adafruit_MPU6050`](Adafruit_MPU6050) | 2.0.3 | — (supplied by the author, not included directly by the codes) | [link](https://github.com/adafruit/Adafruit_MPU6050) | [license.txt](Adafruit_MPU6050/license.txt) |
| [`Adafruit_SSD1306`](Adafruit_SSD1306) | 1.1.2 | 1, 2, 3, 4, 6, 7 | [link](https://github.com/adafruit/Adafruit_SSD1306) | [license.txt](Adafruit_SSD1306/license.txt) |
| [`Adafruit_ST7735_and_ST7789_Library`](Adafruit_ST7735_and_ST7789_Library) | 1.10.2 | 6 | [link](https://github.com/adafruit/Adafruit-ST7735-Library) | see source |
| [`Arduino_GFX`](Arduino_GFX) | 1.0 | — (supplied by the author, not included directly by the codes) | [link](https://github.com/moononournation/Arduino_GFX) | see source |
| [`Arduino_JSON`](Arduino_JSON) | 0.1.0 | — (supplied by the author, not included directly by the codes) | [link](http://github.com/arduino-libraries/Arduino_JSON) | see source |
| [`arduino_ps2_mouse`](arduino_ps2_mouse) | ? | 3 | — | see source |
| [`arduinoWebSockets`](arduinoWebSockets) | 2.3.1 | 2 | [link](https://github.com/Links2004/arduinoWebSockets) | [LICENSE](arduinoWebSockets/LICENSE) |
| [`AsyncTCP`](AsyncTCP) | 1.1.1 | 3, 4, 7 | [link](https://github.com/me-no-dev/AsyncTCP) | [LICENSE](AsyncTCP/LICENSE) |
| [`Blynk`](Blynk) | 1.2.0 | 6, 7 | [link](https://blynk.io) | [LICENSE](Blynk/LICENSE) |
| [`DHT_sensor_library`](DHT_sensor_library) | 1.1.1 | 1, 3, 4, 6 | [link](https://github.com/adafruit/DHT-sensor-library) | see source |
| [`ESPAsyncWebServer`](ESPAsyncWebServer) | 1.2.3 | 2, 3, 4, 7 | [link](https://github.com/me-no-dev/ESPAsyncWebServer) | see source |
| [`IRremoteESP8266`](IRremoteESP8266) | 2.8.4 | 6, 7 | [link](https://github.com/crankyoldgit/IRremoteESP8266) | [LICENSE.txt](IRremoteESP8266/LICENSE.txt) |
| [`rc_switch`](rc_switch) | 2.6.4 | 4, 6, 7 | [link](https://github.com/sui77/rc-switch) | see source |
| [`RFM69_modified_for_ESP8266`](RFM69_modified_for_ESP8266) | 1.2.0 | 4, 5 | [link](https://github.com/LowPowerLab/RFM69) | [License.txt](RFM69_modified_for_ESP8266/License.txt) |
| [`RFM69_original`](RFM69_original) | 1.2.0 | 4, 5 | [link](https://github.com/LowPowerLab/RFM69) | [License.txt](RFM69_original/License.txt) |
| [`ServoESP32`](ServoESP32) | 1.0.3 | — (supplied by the author, not included directly by the codes) | [link](https://github.com/RoboticsBrno/ServoESP32/) | [LICENSE](ServoESP32/LICENSE) |
| [`WebSerial`](WebSerial) | 1.3.0 | 3, 4, 7 | [link](https://github.com/ayushsharma82/WebSerial) | [LICENSE](WebSerial/LICENSE) |

## RFM69: modified and original versions

`RFM69_modified_for_ESP8266` differs from `RFM69_original` only in `RFM69.cpp`: the interrupt routine `isr0()` is declared `ICACHE_RAM_ATTR` on ESP8266 (see section 4.2.1 of the book), and the standard routine is kept for the other boards, so the modified version can be used both on ESP8266 and on Arduino Pro Mini / Uno (chapter 5). The original library is included for reference. Do not install both at the same time, because they have the same headers.

## Required libraries not included here

The following libraries are used by some codes but are not part of this package. Install them from *Sketch → Include Library → Manage Libraries* or from the links below.

| Library | Source | Note | Codes |
|---|---|---|---|
| ESPAsyncTCP | [link](https://github.com/me-no-dev/ESPAsyncTCP) | required by ESPAsyncWebServer and WebSerial on ESP8266 (AsyncTCP is the ESP32 version) | 20 |
| SimpleTimer | [link](https://github.com/jfturcot/SimpleTimer) | timer used by the Blynk codes | 13 |
| ArduinoJson | [link](https://github.com/bblanchon/ArduinoJson) |  | 1 |
| Adafruit Unified Sensor | [link](https://github.com/adafruit/Adafruit_Sensor) | required by Adafruit_MPU6050 and DHT | 1 |
