/*compatibil Arduino 1.8.13
 * WeMos D1 R2 cu Joystick Shield
  buton A pe  pin D5 definit GPIO 14
  buton B pe  pin D6 definit GPIO 4
  buton C pe  pin D3 definit GPIO 5
  buton D pe  pin D4 definit GPIO 16
  Joystick pe A0
  */
  #include <ESP8266WiFi.h>
  #include <espnow.h>
  
  //se introduce adresa MAC a receptorului 
  //2C:3A:E8:08:D9:C5 adresa 1 modul 7
  uint8_t broadcastAddress1[] = {0x2C, 0x3A, 0xE8, 0x08, 0xD9, 0xC5};
  uint8_t broadcastAddress2[] = {0x84, 0x0D, 0x8E, 0xAA, 0xA3, 0xA3};
  
  //84:0D:8E:B0:F3:E8 adresa 3 modul A
  uint8_t broadcastAddress3[] = {0x84, 0x0D, 0x8E, 0xB0, 0xF3, 0xE8};
  
  #define analogPin A0  //Joystick conectat la A0
  // Structura datelor trimise; trebuie să fie identică pentru Sender şi Receiver
  typedef struct test_struct {
      int x;  
      int y;  
      int z;  
      int q;  
      int w;
          } 
  test_struct;
  // generează o structură numită test care memorează variabilele ce vor fi trimise
  test_struct test;
  unsigned long lastTime = 0;  
  unsigned long timerDelay = 200;  
  
    void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    char macStr[18];
    Serial.print("Packet to:");
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
    mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);  
    Serial.print(" send status: ");
    if (sendStatus == 0){   
    Serial.println("Delivery success");   }
    else{ Serial.println("Delivery fail");  
    }   
    }
    void setup() {  
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);   // activează funcţia Wi-Fi
    WiFi.disconnect();
    if (esp_now_init() != 0) {  // activează protocolul ESP-NOW
    Serial.println("Error initializing ESP-NOW");   return;   }
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
 
    esp_now_register_send_cb(OnDataSent);
    // satabilire roluri Master/Slave şi conctare
    //esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    //esp_now_add_peer(broadcastAddress2, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
    esp_now_add_peer(broadcastAddress3, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
        }
    void loop() {
    if ((millis() - lastTime) > timerDelay) {
  
    test.x =  analogRead(analogPin);  //potenţiometru
   
    test.y=digitalRead(14); //buton A 
    test.z=digitalRead(4);  //buton B
    test.q=digitalRead(5);  //buton C
    test.w=digitalRead(16); //buton D
  
    
    esp_now_send(0, (uint8_t *) &test, sizeof(test));
    lastTime = millis();  
    Serial.print("x: ");  
    Serial.println(test.x);
    Serial.print("y: ");  
    Serial.println(test.y);
    Serial.print("z: ");  
    Serial.println(test.z);
    Serial.print("q: ");  
    Serial.println(test.q);
    Serial.print("w: ");  
    Serial.println(test.w);
          } 
          }
  //End of the code
