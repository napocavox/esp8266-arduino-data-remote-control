
/*conectare prin server local
 * IP 192.168.0.206
 * 4 leduri pe GPIO 12, 13, 14 si led 2 placa
 * */
 // Importing necessary libraries
 
//https://microcontrollerslab.com/esp32-asynchronous-web-server-espasyncwebserver-library/

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "UPCF4821BC";
const char* password = "Gherla1956";

const char* input_parameter1 = "output";
const char* input_parameter2 = "state";

// Creating a AsyncWebServer object 
AsyncWebServer server(80);

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP8266 4 led Async</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: grey; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: yellow; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: magenta}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP8266 Asynk 4 Led</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Output - GPIO 12...Output - GPIO 13</h4><br><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"12\" " + outputState(12) + "><span class=\"slider\"></span></label>";

    buttons += "   <label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"13\" " + outputState(13) + "><span class=\"slider\"></span></label>";

    buttons += "<h4>Output - GPIO 15...Output - GPIO 2</h4><br><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"15\" " + outputState(15) + "><span class=\"slider\"></span></label>";

    buttons += " <label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(2) + "><span class=\"slider\"></span></label>";

    return buttons;
  }
  return String();
}

String outputState(int output){
  if(digitalRead(output)){
    return "checked";
  }
  else {
    return "";
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

pinMode(12,OUTPUT);
digitalWrite(12, LOW);
pinMode(13, OUTPUT);
digitalWrite(13, LOW);
pinMode(15, OUTPUT);
digitalWrite(15, LOW);
pinMode(2, OUTPUT);
digitalWrite(2, LOW);

  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(input_parameter1) && request->hasParam(input_parameter2)) {
      inputMessage1 = request->getParam(input_parameter1)->value();
      inputMessage2 = request->getParam(input_parameter2)->value();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("GPIO: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");

    display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("GPIO=");
  display.println(inputMessage1);
//afiseaza pinul ledului comandat
  display.print("state=");
  display.print(inputMessage2);
//afiseaza starea ledului comandat, 0 sau 1  
  display.display();
  });

  // Start server
  server.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP 12 E IP=");
  display.print(WiFi.localIP());
  display.display();
  delay(2000);
}

void loop() {

}
