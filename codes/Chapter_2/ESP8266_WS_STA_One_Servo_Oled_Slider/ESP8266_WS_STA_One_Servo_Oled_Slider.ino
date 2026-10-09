/*servo on GPIO 15=D9
 * Oled 
 * board Node MCU ESP8266
 * prin server local STA Mode
*/



#include <Servo.h>   
Servo Servo1; 
static const int ServoPin = 15; 

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "nume router";
const char* password = "password";

String Sval = "15";

const char* INPUT_PARAMETER = "value";

// Instatiate the AsyncWebServer object on port 80
AsyncWebServer webServer(80);
//activare Oled
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

// pagina web HTML 
const char htmlCode[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <!  define meta data >
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <! define the style CSS of your page >
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h1 {font-size: 2.1rem;}
    h2 {font-size: 2.1rem;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 30px;}
    .slider { -webkit-appearance: none; margin: 14px; width: 300px; height: 15px; border-radius: 5px; background: magenta; outline: none; -webkit-transition: .2s; transition: opacity .2s;}
    .slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 25px; height: 25px; border-radius: 12px; background: green ; cursor: pointer;}
    .slider::-moz-range-thumb { width: 25px; height: 25px; border-radius: 12px; background: #F74D4D; cursor: pointer; } 
  </style>
</head>
<body>
  
  <h2>ESP8266 WsServo</h2>  
  <! Displays the value of the slider >
  <p><span id="textSliderValue">%SLIDERVALUE%</span> &#37</p>
  <! displays the range of the slider 0 - 180 in steps of 1 >
  <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="180" value="%SLIDERVALUE%" step="1" class="slider"></p>
<script>
function updateSliderPWM(element) {
  var Sval = document.getElementById("pwmSlider").value;
  document.getElementById("textSliderValue").innerHTML = Sval;
  console.log(Sval);
  var httpRequest = new XMLHttpRequest();
  httpRequest.open("GET", "/slider?value="+Sval, true);
  httpRequest.send();
}
</script>
</body>
</html>
)rawliteral";

String updateButton(const String& var){
  if (var == "SLIDERVALUE"){
    return Sval;
  }
  return String();
}

void setup(){
  Serial.begin(115200);
  Servo1.attach(ServoPin); 

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", htmlCode, updateButton);
  });

  
  webServer.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(INPUT_PARAMETER)) {
      inputMessage = request->getParam(INPUT_PARAMETER)->value();
      Sval = inputMessage;

Servo1.write(Sval.toInt());  
         
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Servo pos=");
  display.print(Sval);
  display.display();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  webServer.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Servo IP=");
  display.print(WiFi.localIP());
  display.display();
  delay(2000);
}
  
void loop() {
  
}
