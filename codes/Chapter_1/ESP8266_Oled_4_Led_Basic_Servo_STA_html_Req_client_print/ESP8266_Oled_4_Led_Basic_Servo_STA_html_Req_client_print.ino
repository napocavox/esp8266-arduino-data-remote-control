
#include <ESP8266WiFi.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

const char* ssid = "nume router";
const char* password = "parola";

#include <Servo.h>
Servo Servo1; 
//static const int ServoPin = 0; 
//varianta cu servo pe D3
static const int ServoPin = 2; 
//varianta cu servo pe D4

int ledPin = 15;
int ledPin2 = 12;
int ledPin3 = 13;
int ledPin4 = 14;

WiFiServer server(80);

String request;

String valueString ;
int positon1 = 0;
int positon2 = 0;

void setup() 
{
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);

  pinMode(ledPin2,OUTPUT);
  digitalWrite(ledPin2,LOW);
  
  pinMode(ledPin3,OUTPUT);
  digitalWrite(ledPin3,LOW);
  
  pinMode(ledPin4,OUTPUT);
  digitalWrite(ledPin4,LOW);
  Servo1.attach(ServoPin); 
Serial.begin(115200); 
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);

    }
server.begin();
 
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay(); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("oled Req ESP8266 html IP=");
  display.print(WiFi.localIP());
  display.display();
delay(2000);
}

void loop() {
  // verifica daca un client este conectat
  WiFiClient client = server.available();

// trimite clientului un raspuns 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  client.println("<center><h1>4 LED REQUEST</h1>");
         
  client.println("<br><br>");
  client.println("<center><a href=\"/LED=ON\"\"><button=\"button style=\"font-size:200%\">Led 1 On </button></a>");
  client.println("---<a href=\"/LED=OFF\"\"><button=\"button style=\"font-size:200%\">Led 1 Off </button></a>");
  client.println("<br><br>");
 
  client.println("<a href=\"/LED2=ON\"\"><button=\"button style=\"font-size:200%\">Led 2 On </button></a>");
  client.println("---<a href=\"/LED2=OFF\"\"><button=\"button style=\"font-size:200%\">Led 2 Off </button></a>");
  
  client.println("<br><br>");

  client.println("<a href=\"/LED3=ON\"\"><button=\"button style=\"color: green; font-size:200%\">Led 3 On </button></a>");
  client.println("---<a href=\"/LED3=OFF\"\"><button=\"button style=\"color: red; font-size: 200%\">Led 3 Off </button></a>");
  
  client.println("<br><br>");

  client.println("<a href=\"/LED4=ON\"\"><button=\"button style=\"background-color: yellow; font-size:200%;  \">Led 4 On </button></a>");
  client.println("---<a href=\"/LED4=OFF\"\"><button=\"button style=\"background-color: pink; font-size:200%\">Led 4 Off </button></a>");

client.println("</html>");


  
  if (!client) {
    return;
  }
  
  // asteapta date de la client 
   while(!client.available()){
    delay(1);
  }
  // citeste prima linie din solicitarea clientului, request
  String request = client.readStringUntil('\r');
  client.flush();


client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
client.println(".slider { width: 300px; }</style>");
client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
client.println("</head><body><h1>ESP8266 with Servo</h1>");

client.println("<p>Position: <span id=\"servoPos\"></span></p>"); 
//afiseaza text cu pozitia, optional


client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider\" onchange=\"servo(this.value)\" value=\""+request+"\"/>");
//afiseaza slider
client.println("<script>var slider = document.getElementById(\"servoSlider\");");

client.println("var servoP = document.getElementById(\"servoPos\"); servoP.innerHTML = slider.value;");
//linia de sus furnizeaza pozitia, optional
client.println("slider.oninput = function() { slider.value = this.value; servoP.innerHTML = this.value; }");
//linia de sus este legata de cea anterioara , furnizeaza pozitia doar pentr pentru afisare 


  
client.println("$.ajaxSetup({timeout:1000}); function servo(pos) { ");

client.println("$.get(\"/?value=\" + pos + \"&\"); {Connection: close};}</script>");

//rotate the servo
if(request.indexOf("GET /?value=")>=0) 
{
positon1 = request.indexOf('=');
positon2 = request.indexOf('&');
valueString = request.substring(positon1+1, positon2);

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

//comanda leduri
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
  }

 if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
  }
  
if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(ledPin3, HIGH);
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(ledPin3, LOW);
  }

  if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(ledPin4, HIGH);
  }
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(ledPin4, LOW);
  }
  delay(1);
    }
