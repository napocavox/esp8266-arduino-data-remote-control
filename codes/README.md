# Codes — *Data and Remote Control with ESP8266 and Arduino*

Every sketch is in its own folder (the Arduino IDE requires the folder to have the same name as the `.ino` file). Open the `.ino` file in the Arduino IDE, select the board (*NodeMCU 1.0 (ESP-12E Module)* for most codes) and upload.

## Chapter 1. Server with ESP8266 and Arduino

| Sketch | Book section | Libraries |
|---|---|---|
| [`ESP8266_AP_Oled_Servo_Gauge_html`](Chapter_1/ESP8266_AP_Oled_Servo_Gauge_html) + `camera_index.h` | 1.4.3. Transmission of data upon request. Servomotor control | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_AP_Oled_Test_connection_Pass`](Chapter_1/ESP8266_AP_Oled_Test_connection_Pass) | 1.3. The radio connection | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Basic_Oled_1_Servo_STA_html`](Chapter_1/ESP8266_Basic_Oled_1_Servo_STA_html) | 1.4.3. Transmission of data upon request. Servomotor control | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_4_Led_Basic_Servo_STA_html_Req_client_print`](Chapter_1/ESP8266_Oled_4_Led_Basic_Servo_STA_html_Req_client_print) | 1.4.3. Transmission of data upon request. Servomotor control | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_AP_4_led_HTML_Request_client_print`](Chapter_1/ESP8266_Oled_AP_4_led_HTML_Request_client_print) | 1.4.2. Transmission of data upon request. LEDs control | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_Analog_STA_html_client_print`](Chapter_1/ESP8266_Oled_Analog_STA_html_client_print) | 1.4.1. Continuous transmission of the data | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_DHT11_Analog_STA_html_continuous`](Chapter_1/ESP8266_Oled_DHT11_Analog_STA_html_continuous) | 1.4.1. Continuous transmission of the data | Adafruit_GFX_Library, Adafruit_SSD1306, DHT_sensor_library |
| [`ESP8266_Oled_STA_1_led_HTML_Request`](Chapter_1/ESP8266_Oled_STA_1_led_HTML_Request) | 1.4.2. Transmission of data upon request. LEDs control | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_STA_4_led_Analog_HTML_Request_automat`](Chapter_1/ESP8266_Oled_STA_4_led_Analog_HTML_Request_automat) | 1.4.4. Combined transmission, on demand and continuous | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_STA_4_led_Analog_HTML_Request_refresh`](Chapter_1/ESP8266_Oled_STA_4_led_Analog_HTML_Request_refresh) | 1.4.4. Combined transmission, on demand and continuous | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_STA_4_led_HTML_Request_client_print`](Chapter_1/ESP8266_Oled_STA_4_led_HTML_Request_client_print) | 1.4.2. Transmission of data upon request. LEDs control | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_STA_Gauge_1_Servo`](Chapter_1/ESP8266_Oled_STA_Gauge_1_Servo) + `camera_index.h` | 1.4.3. Transmission of data upon request. Servomotor control | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_connection_without_HTML_Open`](Chapter_1/ESP8266_Oled_connection_without_HTML_Open) | 1.3. The radio connection | Adafruit_GFX_Library, Adafruit_SSD1306 |

## Chapter 2. Asynchronous and WebSocket servers

| Sketch | Book section | Libraries |
|---|---|---|
| [`ESP8266_Oled_STA_Async_MPU6050`](Chapter_2/ESP8266_Oled_STA_Async_MPU6050) | 2.5. Server with MPU 6050 accelerometer | Adafruit_GFX_Library, Adafruit_SSD1306, ESPAsyncWebServer, Adafruit Unified Sensor (not included), ESPAsyncTCP (not included) |
| [`ESP8266_STA_Ws_1_Servo_1_Slider`](Chapter_2/ESP8266_STA_Ws_1_Servo_1_Slider) | 2.1. Servomotor control | arduinoWebSockets |
| [`ESP8266_STA_Ws_4_led_Switch`](Chapter_2/ESP8266_STA_Ws_4_led_Switch) | 2.3. ON/OFF control of more LEDs | ESPAsyncWebServer, ESPAsyncTCP (not included) |
| [`ESP8266_STA_Ws_Oled_4_led_Switch`](Chapter_2/ESP8266_STA_Ws_Oled_4_led_Switch) | 2.3. ON/OFF control of more LEDs | Adafruit_GFX_Library, Adafruit_SSD1306, ESPAsyncWebServer, ESPAsyncTCP (not included) |
| [`ESP8266_STA_Ws_PWM_3_LED_control`](Chapter_2/ESP8266_STA_Ws_PWM_3_LED_control) | 2.2. PWM control of one RGB led | arduinoWebSockets |
| [`ESP8266_WS_STA_One_Servo_Oled_Slider`](Chapter_2/ESP8266_WS_STA_One_Servo_Oled_Slider) | 2.1. Servomotor control | Adafruit_GFX_Library, Adafruit_SSD1306, ESPAsyncWebServer, ESPAsyncTCP (not included) |
| [`ESP8266_Ws_STA_3_led_State`](Chapter_2/ESP8266_Ws_STA_3_led_State) | 2.4. LEDs control with confirmation | ESPAsyncWebServer, ESPAsyncTCP (not included) |
| [`Scan_I2C`](Chapter_2/Scan_I2C) | 2.5. Server with MPU 6050 accelerometer | — (ESP8266 core only) |

## Chapter 3. Servers with WebSerial library

| Sketch | Book section | Libraries |
|---|---|---|
| [`ESP8266_AP_Oled_Analog_DHT11_pager_RxTx`](Chapter_3/ESP8266_AP_Oled_Analog_DHT11_pager_RxTx) | 3.2. Bidirectional text and data transmissions with WebSerial and Android | Adafruit_GFX_Library, Adafruit_SSD1306, AsyncTCP, DHT_sensor_library, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266_AP_Oled_Rx_Text_RGB_Servo_Webserial`](Chapter_3/ESP8266_AP_Oled_Rx_Text_RGB_Servo_Webserial) | 3.3. RGB and servomotor control by text messages with WebSerial | Adafruit_GFX_Library, Adafruit_SSD1306, AsyncTCP, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266_AP_Oled_Rx_Text_Webserial`](Chapter_3/ESP8266_AP_Oled_Rx_Text_Webserial) | 3.1. Unidirectional text transmission with WebSerial and Android | Adafruit_GFX_Library, Adafruit_SSD1306, AsyncTCP, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266_AP_Oled_Text_RGB_Servo_Send_A0_Webserial`](Chapter_3/ESP8266_AP_Oled_Text_RGB_Servo_Send_A0_Webserial) | 3.4. Bidirectional connections and feedback with WebSerial | Adafruit_GFX_Library, Adafruit_SSD1306, AsyncTCP, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266_AP_Oled_Text_RGB_Servo_fdbk_Send_A0_Webserial`](Chapter_3/ESP8266_AP_Oled_Text_RGB_Servo_fdbk_Send_A0_Webserial) | 3.4. Bidirectional connections and feedback with WebSerial | Adafruit_GFX_Library, Adafruit_SSD1306, AsyncTCP, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266_AP_WebS_Oled_PS2_Mouse_x_Dist_no_lib`](Chapter_3/ESP8266_AP_WebS_Oled_PS2_Mouse_x_Dist_no_lib) | 3.5. Tracking movements with a PS2 mouse | Adafruit_GFX_Library, Adafruit_SSD1306, AsyncTCP, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266_AP_WebS_PS2_Mouse_x_Dist_no_lib`](Chapter_3/ESP8266_AP_WebS_PS2_Mouse_x_Dist_no_lib) | 3.5. Tracking movements with a PS2 mouse | AsyncTCP, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266_AP_WebSer_Mouse_Ball_PS2_lib_ps2`](Chapter_3/ESP8266_AP_WebSer_Mouse_Ball_PS2_lib_ps2) | 3.5. Tracking movements with a PS2 mouse | AsyncTCP, ESPAsyncWebServer, WebSerial, arduino_ps2_mouse, ESPAsyncTCP (not included) |
| [`ESP8266_AP_WebSer_Oled_Mouse_Ball_PS2_lib_ps2`](Chapter_3/ESP8266_AP_WebSer_Oled_Mouse_Ball_PS2_lib_ps2) | 3.5. Tracking movements with a PS2 mouse | Adafruit_GFX_Library, Adafruit_SSD1306, AsyncTCP, ESPAsyncWebServer, WebSerial, arduino_ps2_mouse, ESPAsyncTCP (not included) |

## Chapter 4. Peer to Peer (P2P) connections

| Sketch | Book section | Libraries |
|---|---|---|
| [`ESP8266 AP WebSerial Gateway DHT11 / ESP8266_AP_WebSerial_Gtw_RF69_Rx_for_Tx_Gtw_DHT11`](Chapter_4/ESP8266%20AP%20WebSerial%20Gateway%20DHT11/ESP8266_AP_WebSerial_Gtw_RF69_Rx_for_Tx_Gtw_DHT11) | 4.8. Gateway with WebSerial for data sensors | AsyncTCP, ESPAsyncWebServer, RFM69_modified_for_ESP8266 / RFM69_original, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266 AP WebSerial Gateway DHT11 / ESP8266_Gtw_RF69_Tx_DHT11_for_AP_Rx_Gtw`](Chapter_4/ESP8266%20AP%20WebSerial%20Gateway%20DHT11/ESP8266_Gtw_RF69_Tx_DHT11_for_AP_Rx_Gtw) | 4.8. Gateway with WebSerial for data sensors | DHT_sensor_library, RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 Analog / ESP8266_STA_Gtw_Rx_RF69_Analog_Tx_html`](Chapter_4/ESP8266%20Gateway%20RF69%20Analog/ESP8266_STA_Gtw_Rx_RF69_Analog_Tx_html) | 4.4. Gateway for sensor data through Station Mode server | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 Analog / ESP8266_Tx_ERF69_Analog_Gtw`](Chapter_4/ESP8266%20Gateway%20RF69%20Analog/ESP8266_Tx_ERF69_Analog_Gtw) | 4.4. Gateway for sensor data through Station Mode server | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 DHT11 / ESP8266_AP_Gtw_Rx_RF69_Analog_T_H_DHT_11_Tx_html`](Chapter_4/ESP8266%20Gateway%20RF69%20DHT11/ESP8266_AP_Gtw_Rx_RF69_Analog_T_H_DHT_11_Tx_html) | 4.5. Gateway connections in Access Point mode. Sensor data | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 DHT11 / ESP8266_Gtw_RF69_Tx_DHT11_Analog_T_H`](Chapter_4/ESP8266%20Gateway%20RF69%20DHT11/ESP8266_Gtw_RF69_Tx_DHT11_Analog_T_H) | 4.4. Gateway for sensor data through Station Mode server<br>4.5. Gateway connections in Access Point mode. Sensor data | DHT_sensor_library, RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 DHT11 / ESP8266_Gtw_RF69_Tx_DHT11_T_H`](Chapter_4/ESP8266%20Gateway%20RF69%20DHT11/ESP8266_Gtw_RF69_Tx_DHT11_T_H) | 4.4. Gateway for sensor data through Station Mode server | DHT_sensor_library, RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 Rx Tx Text / ESP8266_with_RF69_from_UNO_Bilat_Rx1_Tx_2_text_keyboard`](Chapter_4/ESP8266%20Gateway%20RF69%20Rx%20Tx%20Text/ESP8266_with_RF69_from_UNO_Bilat_Rx1_Tx_2_text_keyboard) | 4.2.2. Bilateral text transmissions with confirmation | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 Rx Tx Text / ESP8266_with_RF69_from_UNO_Bilat_Rx2_Tx1_text_keyboard`](Chapter_4/ESP8266%20Gateway%20RF69%20Rx%20Tx%20Text/ESP8266_with_RF69_from_UNO_Bilat_Rx2_Tx1_text_keyboard) | 4.2.2. Bilateral text transmissions with confirmation | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 / ESP8266_Gateway_Rx_RF69_1_Servo`](Chapter_4/ESP8266%20Gateway%20RF69/ESP8266_Gateway_Rx_RF69_1_Servo) | 4.3.2. Servomotor control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 / ESP8266_STA_Gateway_Tx_Gauge_1_Servo`](Chapter_4/ESP8266%20Gateway%20RF69/ESP8266_STA_Gateway_Tx_Gauge_1_Servo) + `camera_index.h` | 4.3.2. Servomotor control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 / ESP8266_STA_Gateway_html_Tx_RF69_Slider_for_Servo`](Chapter_4/ESP8266%20Gateway%20RF69/ESP8266_STA_Gateway_html_Tx_RF69_Slider_for_Servo) | 4.3.2. Servomotor control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Gateway RF69 / ESP8266_STA_Gtw_Tx_RF69_4_Button_1_Slider_for_Servo`](Chapter_4/ESP8266%20Gateway%20RF69/ESP8266_STA_Gtw_Tx_RF69_4_Button_1_Slider_for_Servo) | 4.3.2. Servomotor control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 RF69 Gtw html 1 led / ESP8266_Rx_Gtw_RF69_for_Tx_html_1_led_button`](Chapter_4/ESP8266%20RF69%20Gtw%20html%201%20led/ESP8266_Rx_Gtw_RF69_for_Tx_html_1_led_button) | 4.3.1. The LEDs control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 RF69 Gtw html 1 led / ESP8266_STA_Gtw_RF69_html_Tx_1_led_button`](Chapter_4/ESP8266%20RF69%20Gtw%20html%201%20led/ESP8266_STA_Gtw_RF69_html_Tx_1_led_button) | 4.3.1. The LEDs control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Rx Tx Servo RF69 / ESP8266_Rx_RF69_1_Servo`](Chapter_4/ESP8266%20Rx%20Tx%20Servo%20RF69/ESP8266_Rx_RF69_1_Servo) | 4.2.3. Data transmissions. Control of one servomotor<br>4.3.1. The LEDs control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 Rx Tx Servo RF69 / ESP8266_Tx_ERF69_Analog_1_Servo`](Chapter_4/ESP8266%20Rx%20Tx%20Servo%20RF69/ESP8266_Tx_ERF69_Analog_1_Servo) | 4.2.3. Data transmissions. Control of one servomotor | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 RxTx Gateway RF69 WebSerial / ESP8266_AP_WebSerial_Tx_Gtw_with_RF69_for_Servo`](Chapter_4/ESP8266%20RxTx%20Gateway%20RF69%20WebSerial/ESP8266_AP_WebSerial_Tx_Gtw_with_RF69_for_Servo) | 4.7. Gateway with WebSerial. Servomotor control by text messages | AsyncTCP, ESPAsyncWebServer, RFM69_modified_for_ESP8266 / RFM69_original, WebSerial, ESPAsyncTCP (not included) |
| [`ESP8266 RxTx Gateway RF69 WebSerial / ESP8266_Gateway_Rx_RF69_1_Servo_for_WebSerial`](Chapter_4/ESP8266%20RxTx%20Gateway%20RF69%20WebSerial/ESP8266_Gateway_Rx_RF69_1_Servo_for_WebSerial) | 4.7. Gateway with WebSerial. Servomotor control by text messages | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 RxTx Gtw RF69 Async 1 led / ESP8266_Rx_Gtw_RF69_for_Tx_Async_1_led`](Chapter_4/ESP8266%20RxTx%20Gtw%20RF69%20Async%201%20led/ESP8266_Rx_Gtw_RF69_for_Tx_Async_1_led) | 4.6. Gateway with asynchronous server. The LED control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266 RxTx Gtw RF69 Async 1 led / ESP8266_Tx_STA_Async_Gtw_RF69_1_led`](Chapter_4/ESP8266%20RxTx%20Gtw%20RF69%20Async%201%20led/ESP8266_Tx_STA_Async_Gtw_RF69_1_led) | 4.6. Gateway with asynchronous server. The LED control | ESPAsyncWebServer, RFM69_modified_for_ESP8266 / RFM69_original, ESPAsyncTCP (not included) |
| [`ESP8266_Client_Server_P2P_4_button_for_4_led`](Chapter_4/ESP8266_Client_Server_P2P_4_button_for_4_led) | 4.1. P2P via Wi-Fi | Adafruit_GFX_Library, Adafruit_SSD1306 |
| [`ESP8266_Oled_STA_Tx_315_4_Ch_html`](Chapter_4/ESP8266_Oled_STA_Tx_315_4_Ch_html) | 4.9. Gateway with RxTx 315/433 MHz modules | Adafruit_GFX_Library, Adafruit_SSD1306, rc_switch |
| [`ESP8266_Server_Oled_P2P_4_led_for_4_button`](Chapter_4/ESP8266_Server_Oled_P2P_4_led_for_4_button) | 4.1. P2P via Wi-Fi | Adafruit_GFX_Library, Adafruit_SSD1306, ArduinoJson (not included) |
| [`UNO_Rx_decoder_315-433_simple`](Chapter_4/UNO_Rx_decoder_315-433_simple) | 4.9. Gateway with RxTx 315/433 MHz modules | rc_switch |

## Chapter 5. Gateway with ESP8266 and Arduino Uno Pro Mini

| Sketch | Book section | Libraries |
|---|---|---|
| [`ESP8266_STA_Gateway_Tx_Gauge_1_Servo_for_ProMini`](Chapter_5/ESP8266_STA_Gateway_Tx_Gauge_1_Servo_for_ProMini) + `camera_index.h` | 5.2. Servomotor control through gateway with Arduino Pro Mini | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ESP8266_STA_Tx_Gtw_Rf69_Slider_1_Servo_for_ProMini`](Chapter_5/ESP8266_STA_Tx_Gtw_Rf69_Slider_1_Servo_for_ProMini) | 5.2. Servomotor control through gateway with Arduino Pro Mini | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ProMini ESP8266 RxTx Gtw RF69 4 led / ESP8266_AP_Tx_Gtw_RF69_client_print_4_led_button`](Chapter_5/ProMini%20ESP8266%20RxTx%20Gtw%20RF69%204%20led/ESP8266_AP_Tx_Gtw_RF69_client_print_4_led_button) | 5.4. Gateway with Arduino Pro Mini for LEDs control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ProMini ESP8266 RxTx Gtw RF69 4 led / ESP8266_STA_Tx_Gtw_RF69_client_print_4_led_button`](Chapter_5/ProMini%20ESP8266%20RxTx%20Gtw%20RF69%204%20led/ESP8266_STA_Tx_Gtw_RF69_client_print_4_led_button) | 5.4. Gateway with Arduino Pro Mini for LEDs control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ProMini ESP8266 RxTx Gtw RF69 4 led / ProMini_Rx_Gtw_RF69_for_ESP8266_Tx_html_4_led`](Chapter_5/ProMini%20ESP8266%20RxTx%20Gtw%20RF69%204%20led/ProMini_Rx_Gtw_RF69_for_ESP8266_Tx_html_4_led) | 5.4. Gateway with Arduino Pro Mini for LEDs control | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ProMini ESP8266 gtw Analog / ESP8266_STA_Gtw_Rx_RF69__for_Tx_Ax_html`](Chapter_5/ProMini%20ESP8266%20gtw%20Analog/ESP8266_STA_Gtw_Rx_RF69__for_Tx_Ax_html) | 5.3. Gateway with Arduino Pro Mini for analog data | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ProMini ESP8266 gtw Analog / ProMini_Tx_RF69_Gtw_Ax_for_ESP8266`](Chapter_5/ProMini%20ESP8266%20gtw%20Analog/ProMini_Tx_RF69_Gtw_Ax_for_ESP8266) | 5.3. Gateway with Arduino Pro Mini for analog data | RFM69_modified_for_ESP8266 / RFM69_original |
| [`ProMini_Rx_Gtw_RF69_RGB_1_Servo_for_ESP8266_Tx`](Chapter_5/ProMini_Rx_Gtw_RF69_RGB_1_Servo_for_ESP8266_Tx) | 5.2. Servomotor control through gateway with Arduino Pro Mini | RFM69_modified_for_ESP8266 / RFM69_original |

## Chapter 6. Transmission of data and orders trough the internet

| Sketch | Book section | Libraries |
|---|---|---|
| [`BlynkN_ESP8266_Motor_Shield_2_DC`](Chapter_6/BlynkN_ESP8266_Motor_Shield_2_DC) | 6.3.2. DC motor control and feedback | Blynk |
| [`BlynkN_ESP8266_Oled_4_led_1_Servo_Tx_315_fdbk_Terminal`](Chapter_6/BlynkN_ESP8266_Oled_4_led_1_Servo_Tx_315_fdbk_Terminal) | 6.4.1. Radio control of a lighting system | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, rc_switch, SimpleTimer (not included) |
| [`BlynkN_ESP8266_Oled_4_led_2_Servo_fdbk`](Chapter_6/BlynkN_ESP8266_Oled_4_led_2_Servo_fdbk) | 6.3.1. Controls of LEDs and servomotors | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, SimpleTimer (not included) |
| [`BlynkN_ESP8266_Oled_DHT11_Ao`](Chapter_6/BlynkN_ESP8266_Oled_DHT11_Ao) | 6.2. Digital and analog data with Blynk | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, DHT_sensor_library, SimpleTimer (not included) |
| [`BlynkN_ESP8266_Oled_HB_2_Servo_fdbk`](Chapter_6/BlynkN_ESP8266_Oled_HB_2_Servo_fdbk) | 6.3.2. DC motor control and feedback | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, SimpleTimer (not included) |
| [`BlynkN_ESP8266_Oled_Pager_Unilat_text`](Chapter_6/BlynkN_ESP8266_Oled_Pager_Unilat_text) | 6.5. Sending texts with Blynk. Unilateral pager | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk |
| [`BlynkN_ESP8266_TFT_18_ST7735_Pager_A0_V_Gauge`](Chapter_6/BlynkN_ESP8266_TFT_18_ST7735_Pager_A0_V_Gauge) | 6.6.2. Analog voltmeter and text pager | Adafruit_GFX_Library, Adafruit_ST7735_and_ST7789_Library, Blynk, SimpleTimer (not included) |
| [`BlynkN_ESP8266_TFT_18_ST7735_pager`](Chapter_6/BlynkN_ESP8266_TFT_18_ST7735_pager) | 6.6.1. Pager with TFT and Blynk | Adafruit_GFX_Library, Adafruit_ST7735_and_ST7789_Library, Blynk |
| [`BlynkN_ESP8266_Tx_IR_DHT11_Photores_fdbk`](Chapter_6/BlynkN_ESP8266_Tx_IR_DHT11_Photores_fdbk) | 6.4.2. IR control of LEDs lighting strip | Blynk, DHT_sensor_library, IRremoteESP8266, rc_switch, SimpleTimer (not included) |
| [`BlynkN_ESP8266_Tx_IR_strip_fdbk`](Chapter_6/BlynkN_ESP8266_Tx_IR_strip_fdbk) | 6.4.2. IR control of LEDs lighting strip | Blynk, IRremoteESP8266, rc_switch, SimpleTimer (not included) |
| [`Blynk_ESP8266_4_led`](Chapter_6/Blynk_ESP8266_4_led) | 6.1. Simple commands with Blynk | Blynk |
| [`Decoder_IR_ESP8266_IRrecvDumpV2_from_examples`](Chapter_6/Decoder_IR_ESP8266_IRrecvDumpV2_from_examples) | 6.4.2. IR control of LEDs lighting strip | IRremoteESP8266 |
| [`UNO_Rx_decoder_315-433_simple`](Chapter_6/UNO_Rx_decoder_315-433_simple) | 6.4.1. Radio control of a lighting system | rc_switch |

## Chapter 7. Equivalent ESP8266 modules

| Sketch | Book section | Libraries |
|---|---|---|
| [`BlynkN_ESP01_2_led`](Chapter_7/BlynkN_ESP01_2_led) | 7.1. ESP8266-01 module | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk |
| [`BlynkN_ESP_12_E_1_Servo_HB_Oled_Pager_RGB_photo_fdbk`](Chapter_7/BlynkN_ESP_12_E_1_Servo_HB_Oled_Pager_RGB_photo_fdbk) | 7.4.3. Control of DC motors and servomotors | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, SimpleTimer (not included) |
| [`BlynkN_ESP_12_E_2_Servo_HB_Oled_Pager_RGB_photo_fdbk`](Chapter_7/BlynkN_ESP_12_E_2_Servo_HB_Oled_Pager_RGB_photo_fdbk) | 7.4.3. Control of DC motors and servomotors | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, SimpleTimer (not included) |
| [`BlynkN_ESP_12_E_Oled_Pager_RGB_Ao_fdbk`](Chapter_7/BlynkN_ESP_12_E_Oled_Pager_RGB_Ao_fdbk) | 7.4.2. Text pager with Oled display | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, SimpleTimer (not included) |
| [`BlynkN_WemosMini_Tx_315_IR_strip_fdbk`](Chapter_7/BlynkN_WemosMini_Tx_315_IR_strip_fdbk) | 7.3. ESP8266-WeMos D1 Mini module | Blynk, IRremoteESP8266, rc_switch, SimpleTimer (not included) |
| [`ESP8266_Get_MAC_Address`](Chapter_7/ESP8266_Get_MAC_Address) | 7.2.5. WeMos D1 R2 P2P connections with Joystick Shield and ESP8266 | — (ESP8266 core only) |
| [`ESP_12_E_Oled_STA_Async_4_led_switch`](Chapter_7/ESP_12_E_Oled_STA_Async_4_led_switch) | 7.4.4. Local server and web page with ESP12-E | Adafruit_GFX_Library, Adafruit_SSD1306, ESPAsyncWebServer, ESPAsyncTCP (not included) |
| [`WeMos D1 Bilat Rx Tx / Rx_Node_Bilat_1_servo_4led_fdbk_simple_2`](Chapter_7/WeMos%20D1%20Bilat%20Rx%20Tx/Rx_Node_Bilat_1_servo_4led_fdbk_simple_2) | 7.2.6. P2P connection and feedback with Joystick Shield | — (ESP8266 core only) |
| [`WeMos D1 Bilat Rx Tx / Tx_Bilat_1_Servo_4_led_Oled_fdbk_simple`](Chapter_7/WeMos%20D1%20Bilat%20Rx%20Tx/Tx_Bilat_1_Servo_4_led_Oled_fdbk_simple) | 7.2.6. P2P connection and feedback with Joystick Shield | Adafruit_SSD1306 |
| [`WeMos D1 Unilat Rx Tx / WeMos_D1_Unilat_Rx_1_Servo_H_Bridge`](Chapter_7/WeMos%20D1%20Unilat%20Rx%20Tx/WeMos_D1_Unilat_Rx_1_Servo_H_Bridge) | 7.2.5. WeMos D1 R2 P2P connections with Joystick Shield and ESP8266 | — (ESP8266 core only) |
| [`WeMos D1 Unilat Rx Tx / WeMos_D1_Unilat_Tx_1_Servo_H_Bridge`](Chapter_7/WeMos%20D1%20Unilat%20Rx%20Tx/WeMos_D1_Unilat_Tx_1_Servo_H_Bridge) | 7.2.5. WeMos D1 R2 P2P connections with Joystick Shield and ESP8266 | — (ESP8266 core only) |
| [`WeMos_D1_R2_Blynk_Oled_Pager_1_led_fdbk`](Chapter_7/WeMos_D1_R2_Blynk_Oled_Pager_1_led_fdbk) | 7.2.4. Pager and led control with feedback and Blynk | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk, SimpleTimer (not included) |
| [`WeMos_D1_R2_Blynk_Pager_LCD_Shield`](Chapter_7/WeMos_D1_R2_Blynk_Pager_LCD_Shield) | 7.2.2. One-sided pager with WeMos D1 R2 | Blynk |
| [`WeMos_D1_R2_Blynk_Pager_LCD_Shield_A0_buttons`](Chapter_7/WeMos_D1_R2_Blynk_Pager_LCD_Shield_A0_buttons) | 7.2.2. One-sided pager with WeMos D1 R2 | Blynk, SimpleTimer (not included) |
| [`WeMos_D1_R2_Oled_Pager_Unilat_text`](Chapter_7/WeMos_D1_R2_Oled_Pager_Unilat_text) | 7.2.3. Connection of the Oled I2C display | Adafruit_GFX_Library, Adafruit_SSD1306, Blynk |
| [`WeMos_D1_R2_STA_Async_4_led_Switch`](Chapter_7/WeMos_D1_R2_STA_Async_4_led_Switch) | 7.2.1. LEDs control by generated server | ESPAsyncWebServer, ESPAsyncTCP (not included) |
| [`WeMos_D1_R2_Webserial_LCD_Shield`](Chapter_7/WeMos_D1_R2_Webserial_LCD_Shield) | 7.2.7. Simple P2P pager with LCD Shield and WebSerial | AsyncTCP, ESPAsyncWebServer, WebSerial, ESPAsyncTCP (not included) |

