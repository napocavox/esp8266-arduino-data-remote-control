/*********
 
 * servo on D3, in code zero
 * generates server with IP 192.168.0.80
 * prin router local
*********/
#include <ESP8266WiFi.h> 
#include <Servo.h>
  
Servo Servo1; 
static const int ServoPin = 0; 
const char* ssid = "nume router";
const char* password = "password";

WiFiServer server(80);
String request;
String valueString = String(0);
int positon1 = 0;
int positon2 = 0;

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

void setup() 
{
Serial.begin(115200); 
Servo1.attach(ServoPin); 
//Serial.print("Making connection to "); //optional monitor
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
//Serial.print(".");  //optional monitor
}
// These lines prints the IP address value on serial monitor 
//Serial.println("");   //optional monitor
//Serial.println("WiFi connected.");  //optional monitor
//Serial.println("IP address: "); //optional monitor
//Serial.println(WiFi.localIP()); //optional monitor
  server.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("oled ESP8266 Servo IP=");
  display.print(WiFi.localIP());
  display.display();
  delay(2000);
}

void loop(){
WiFiClient client = server.available(); 
// Listen for incoming clients

if (client)
{ // If a new client connects,

String request = client.readStringUntil('\r');
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html"); 
client.println("Connection: close");    
client.println();

// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");

client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
client.println(".slider { width: 300px; }</style>");
//the style lines edit a larger slider

client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
//the script lines are required
// Web Page
client.println("</head><body><h1>ESP8266 with Servo</h1>");
//displays the title, optional

//client.println("<p>Position: <span id=\"servoPos\"></span></p>"); 
//displays text with the position, optional

client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+valueString+"\"/>");

client.println("<script>var slider = document.getElementById(\"servoSlider\");");

//client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
//the line above provides the position, optional

//client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
//the line above is linked to the previous one , provides the position for display only

client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");

client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");

client.println("</body></html>"); 


//rotate servo
if(request.indexOf("GET /?value=")>=0) 
{
positon1 = request.indexOf('=');
positon2 = request.indexOf('&');
valueString = request.substring(positon1+1, positon2);

//Rotate the servo
Servo1.write(valueString.toInt());
//Serial.println(valueString); //optional monitor

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Servo pos=");
  display.print(valueString);
  display.display();
  } 
//rotate servo 



request = "";
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
}
}
