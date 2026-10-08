/*
 * servo pe D8=GPIO15 
 * comandat cu slider
 */
#include <Servo.h>
Servo Servo0;

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Hash.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
            case WStype_DISCONNECTED:
            USE_SERIAL.printf("[%u] Disconnected!\n", num);
            break;
            
      
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.print(ip);
            USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocket.sendTXT(num, "Connected");
        }
          //optional
            break;
        case WStype_TEXT:
            USE_SERIAL.printf("[%u] get Text: %s\n", num, payload);
 
            if(payload[0] == '#') {
                
                uint32_t rgbs = (uint32_t) strtol((const char *) &payload[1], NULL, 16);
  Servo0.write(((rgbs >> 0) & 0xFF)); 
            }
            break;
            }
            }

  void setup() {
    
    Servo0.attach(15);
    
    USE_SERIAL.begin(115200);

    WiFiMulti.addAP("nume router", "parola router");
    

    while(WiFiMulti.run() != WL_CONNECTED) {

        delay(100);
    }

    // start webSocket server
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    if(MDNS.begin("esp8266")) {
        USE_SERIAL.println("MDNS responder started");
    }
    
    // handle index
    server.on("/", []() {
        server.send(200, "text/html", "<html><center><head><script>var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);connection.onopen = function () {  connection.send('Connect ' + new Date()); }; connection.onerror = function (error) {    console.log('WebSocket Error ', error);};connection.onmessage = function (e) {  console.log('Server: ', e.data);};function sendrgbs() {  var r = parseInt(document.getElementById('r').value).toString(16);                                                                        if(r.length < 2) { r = '0' + r; }                                           var rgbs = '#'+r;      console.log('rgbs: ' + rgbs); connection.send(rgbs); }</script></head><body>  LED Control:<br/><br/>      R: <input id=\"r\" type=\"range\" min=\"0\" max=\"255\" step=\"1\" oninput=\"sendrgbs();\" /><br/><br/></body></html>");
    });

    server.begin();
    // Add service to MDNS
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", 81);
}

void loop() {
    webSocket.loop();
    server.handleClient();   
}
