/* modul ESP8266
 *  leduri sau intrările punţii H conectate  
 *  la D5, 6, 7, 8 definiţi în cod prin
*  GPIO14, GPIO12, GPIO13, GPIO15
*  comandate de Tx WeMos D1 cu Joystick Shield
*  butoane A, B, C, D
* servo comandat de D3-GPIO 0 
*/
  #include <ESP8266WiFi.h>
  #include <espnow.h>
  #include <Servo.h>
  Servo Servo1; 
  int angle=80;
  // Structura datelor primite, identică pentru Rx şi Tx  
  typedef struct test_struct {  
    int x; 
    int y; 
    int z; 
    int q; 
    int w; 
    } 
    test_struct;
  // Creare unei structuri numită myData
    test_struct myData;
// Callback function that will be executed when data is received
    void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);  
    Serial.println();
    }
    void setup() {
    Servo1.attach(0); //servo conectat la D3 definit GPIO 0
    pinMode(14, OUTPUT);  //led pe D5
    pinMode(12, OUTPUT);  //led pe D6
    pinMode(13, OUTPUT);  //led pe D7 
    pinMode(15, OUTPUT);  //led pe D8 
    //leduri sau punte H pe D5, 6, 7, 8
    digitalWrite(14,LOW); 
    digitalWrite(13,LOW);
    digitalWrite(12,LOW); 
    digitalWrite(15,LOW);
    
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);  //activare WiFi
    WiFi.disconnect();
    if (esp_now_init() != 0) { //activare protocol ESP-NOW
    Serial.println("Error initializing ESP-NOW"); 
    return;   
    }
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);  //setare rol SLAVE
    esp_now_register_recv_cb(OnDataRecv);       
    }
    
    void loop() {
    angle = map(myData.x, 0, 1023, 0, 180); 
    Servo1.write(angle); 
    Serial.println(" angle="); 
    Serial.print(angle);
  //acţionare servo 
  //activare leduri sau punte H     
    if (myData.y == 1) { 
      digitalWrite(14, LOW);   
      } 
      else {
        digitalWrite(14, HIGH); 
        } 
        Serial.println(" y="); 
        Serial.print(myData.y);
        if (myData.z == 1) {
          digitalWrite(15, LOW);  
          } 
    else {
      digitalWrite(15, HIGH); 
      } Serial.println(" z="); 
      Serial.print(myData.z);
      
    if (myData.q == 1) {
    digitalWrite(12, LOW);  
    }
        
     else {
        digitalWrite(12, HIGH); 
        } Serial.println(" q="); 
        Serial.print(myData.q);
        
    if (myData.w == 1) {
      digitalWrite(13, LOW);  
      }
  else {
    digitalWrite(13, HIGH);
  } 
  Serial.println(" w="); 
  Serial.print(myData.w);
    }
  //End of the code
