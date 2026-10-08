/* fdbck numai pe servo conectat la A0
*/
#include <Servo.h>
  Servo Servo1;
  int angle=80;
  #define analogPin A0 //feedback potenţiometru conectat la A0
  #include <ESP8266WiFi.h>
  #include <espnow.h>

  //se introduce adresa MAC a emiţătorului, 
  //ESP8266 Board MAC Address:  5C:CF:7F:C2:E1:C7
uint8_t broadcastAddress[] = {0x5C, 0xCF, 0x7F, 0xC2, 0xE1, 0xC7};
 
  float analog;
  
  // variabile primite
  int incomingLED1; 
  int incomingLED2; 
  int incomingLED3; 
  int incomingLED4;
  
  float incomingAn;
  const long interval = 200; unsigned long previousMillis = 0;    
  String success;
  //Structura datelor transmise 
  typedef struct struct_message { 
    int L1; 
    int L2; 
    int L3; 
    int L4; 
    float ana;
  } 
  struct_message;
  struct_message Readings;
  // generare structură date primite
  struct_message incomingReadings;
  
    void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0){ Serial.println("Delivery success");   }
    else{ 
      Serial.println("Delivery fail");      
      } 
      }
    
    void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
    Serial.print("Bytes received: ");
    Serial.println(len); 
    
      }
      
    void getReadings(){
    
    analog =  analogRead(analogPin);   
  } 
  
    void setup() { 
      pinMode(15, OUTPUT); 
      pinMode(14, OUTPUT);
      pinMode(13, OUTPUT); 
      pinMode(12, OUTPUT); 
    
    digitalWrite(15, LOW);
    digitalWrite(14, LOW); 
    digitalWrite(13, LOW); 
    digitalWrite(12, LOW);
  
    Servo1.attach(0); //servo conectata la D3
    
  Serial.begin(115200); 
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect();
  if (esp_now_init() != 0) { 
    Serial.println("Error initializing ESP-NOW");
    return;     
    }
  // Setare rol combinat emisie/recepţie
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_send_cb(OnDataSent);
    // înregistrare adresă partener
    esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_register_recv_cb(OnDataRecv);   }
    
    void loop() {
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; getReadings();
  
      Readings.ana = analog;
  // trimitere variabile via ESP-NOW
  esp_now_send(broadcastAddress, (uint8_t *) &Readings, sizeof(Readings));

if (incomingReadings.L1 == 0) { digitalWrite(14, HIGH); 
  digitalWrite(14, HIGH); 
  }
  
    else 

    if (incomingReadings.L2 == 0){
      
        digitalWrite(15, HIGH); 
      
      }
      
    else
    if (incomingReadings.L3 == 0){
     
        digitalWrite(13, HIGH);        
        }
        
      else  
      if (incomingReadings.L4 == 0){
     
        digitalWrite(12, HIGH);        
        }
        
      else
      { 
        digitalWrite(15, LOW); 
        digitalWrite(12, LOW); 
        digitalWrite(14, LOW);
        digitalWrite(13, LOW);  
        }
        
  angle = map(incomingReadings.ana, 0, 1023, 0, 180); 
  
  //angle = map(incomingAn, 0, 1023, 0, 180); 
  Servo1.write(angle);     
      } 
      }
//End of the code
