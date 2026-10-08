/*********
 biblio
 https://randomnerdtutorials.com/esp8266-dht11dht22-temperature-and-humidity-web-server-with-arduino-ide/

lik icons
https://microcontrollerslab.com/esp8266-nodemcu-web-server-using-littlefs-flash-file-system/

https://fontawesome.com/icons/lightbulb?s=solid&f=classic
*********/


#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_Sensor.h>

#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
double tt;

// Replace with your network credentials
const char* ssid = "nume router";
const char* password = "password";

AsyncWebServer server(80);

unsigned long previousMillis = 0;    // will store last time DHT was updated

const long interval = 2000;  

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 2.0rem; }
    p { font-size: 2.0rem; }
    .units { font-size: 1.2rem; }
    .mpu-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <p>ESP8266 MPU Server</p>

  <p>
    <i class="fas fa-sharp fa-solid fa-cube" style="color:orange;"></i> 
    <span class="mpu-labels">coordx</span> 
    <span id="ax">%COORDX%</span>
    <sup class="units">deg</sup>
  </p>

  <p>
    <i class="fas fa-solid fa-cubes" style=color:magenta;"></i> 
    <span class="mpu-labels">coordy</span> 
    <span id="ay">%COORDY%</span>
    <sup class="units">deg</sup>
  </p>


  <p>
    <i class="fas fa-solid fa-cubes" style="color:blue;"></i> 
    <span class="mpu-labels">coordz</span> 
    <span id="az">%COORDZ%</span>
    <sup class="units">deg</sup>
  </p>
  
  
  <p>
    <i class="fas fa-thermometer-half" style="color:red;"></i> 
    <span class="mpu-labels">Temp</span> 
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  
  
  
</body>
<script>

  setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ax").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/ax", true);
  xhttp.send();
  }, 1000 ) ;


  setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ay").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/ay", true);
  xhttp.send();
  }, 1000 ) ;


  setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("az").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/az", true);
  xhttp.send();
  }, 1000 ) ;



  setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
  }, 1000 ) ;


</script>
</html>)rawliteral";

String processor(const String& var){
 
if(var == "coordx"){
    return String(x);
  }
  
  else 
  if(var == "coordy"){
    return String(y);
  }

else 
  if(var == "coordz"){
    return String(z);
  }

  else if(var == "TEMPERATURE"){
    return String(tt);
  }
 
  return String();
}

void setup(){
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

server.on("/ax", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(x).c_str());
  });

server.on("/ay", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(y).c_str());
  });

server.on("/az", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(z).c_str());
  });
  
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(tt).c_str());
  });
  
  // Start server

Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
  
  server.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Async TCP IP=");
  display.print(WiFi.localIP());
  display.display();
  delay(2000);
}
 
void loop(){  

Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
Tmp=Wire.read()<<8|Wire.read();

int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
tt=Tmp/340.00+36.53;


  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
  float newX = x;
    if (isnan(newX)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      x = newX;
      Serial.println(x);
    }


    float newY = y;
    if (isnan(newY)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      y = newY;
      Serial.println(y);
    }


    float newZ = z;
    if (isnan(newZ)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      z = newZ;
      Serial.println(z);
    }


    float newT = tt;
    if (isnan(newT)) {
      Serial.println("Failed to read from DHT sensor!");
    }
    else {
      tt = newT;
      Serial.println(tt);
    }
    
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  
  display.print("x=");
  display.println(x);
  
  display.print("y=");
  display.println(y);
  
  display.print("z=");
  display.println(z);

  display.print("t=");
  display.print(tt);
  
  display.display();
  
  delay(2000);
  }
}
