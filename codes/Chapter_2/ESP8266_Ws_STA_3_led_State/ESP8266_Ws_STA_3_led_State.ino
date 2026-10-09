

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "nume router";
const char* password = "password";

bool ledState = 0;
//const int ledPin = 2;//blue board LED
const int ledPin = 13;

bool ledState2 = 0;
const int ledPin2 = 12;

bool ledState3 = 0;
const int ledPin3 = 14;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

    const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE HTML><html>
    <head>
    <title>ESP Web Server</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <style>
    html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
    }
    </style>
    </head>

    <body>
    <div class="topnav">
    <h1>ESP 8266</h1>
    <h1>WebSocket</h1>
    <h1>RGB state</h1>
    <h1>state</h1>
    </div>
    <div class="content">
    <div class="card">
      
      <h2><p class="state">state led 1: <span id="state">%STATE%</span></p>
      <h2><p><button id="button" class="button">push1</button></p>

      <h2><p><button id="button2" class="button">push2</button></p>
      
      <h2><p><button id="button3" class="button">push3</button></p>
      
    </div>
  
<script>
  var ledc = `ws://${window.location.hostname}/ws`;
  var websocket1;

  var ledc2 = `ws://${window.location.hostname}/ws`;
  var websocket2;

  var ledc3 = `ws://${window.location.hostname}/ws`;
  var websocket3;
  
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket1 = new WebSocket(ledc);
    websocket2 = new WebSocket(ledc2);
    websocket3 = new WebSocket(ledc3);
    websocket1.onmessage = onMessage; 
    }


    function onMessage(event) {
    var state;
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }   
    document.getElementById('state').innerHTML = state;     
    }
  
    function onLoad(event) {
    initWebSocket();
    initButton();
    }
    function initButton() {
    document.getElementById('button').addEventListener('click', push1);
    
    document.getElementById('button2').addEventListener('click', push2);
  
    document.getElementById('button3').addEventListener('click', push3);
  }
  function push1(){
    websocket1.send('push1');
  }

  function push2(){
    websocket2.send('push2');
  }

  function push3(){
    websocket3.send('push3');
  }
  
</script>
</body>
</html>
)rawliteral";


    void notifyClients() {
    ws.textAll(String(ledState));
    }

    void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "push1") == 0) {
      ledState = !ledState;
      notifyClients();
    }
    
    if (strcmp((char*)data, "push2") == 0) {
      ledState2 = !ledState2;
      notifyClients();
    } 
    
    if (strcmp((char*)data, "push3") == 0) {
      ledState3 = !ledState3;
      notifyClients();
      } 
    }
  }

      void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
      switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }

  if(var == "STATE"){
    if (ledState2){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
  
  if(var == "STATE"){
    if (ledState3){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
  return String();
}


  void setup(){
  
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, LOW);

  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin3, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(ledPin, ledState);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
}
