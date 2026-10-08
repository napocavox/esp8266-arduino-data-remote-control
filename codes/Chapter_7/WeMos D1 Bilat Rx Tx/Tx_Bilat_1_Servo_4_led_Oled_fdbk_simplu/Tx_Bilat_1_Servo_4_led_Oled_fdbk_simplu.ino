/*
 * fdbck numai pentru servo pe analog A0
 */
 

  #define analogPin A0 
  #include <Adafruit_SSD1306.h>
  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 64 // OLED display height, in pixels
  #define OLED_RESET -1  
  Adafruit_SSD1306 display(OLED_RESET);
  #include <ESP8266WiFi.h>
  #include <espnow.h>

// adresa MAC a receptorului  
  //uint8_t broadcastAddress[] = {0x2C, 0x3A, 0xE8, 0x08, 0xD9, 0xC5};
   uint8_t broadcastAddress[] = {0x84, 0x0D, 0x8E, 0xB0, 0xF3, 0xE8};
  
  int sendL1; 
  int sendL2; 
  int sendL3; 
  int sendL4; 
  float analog;
  
  
  float incomingAn; 
  //definire date primite de la Receiver 
  
  const long interval = 200; unsigned long previousMillis = 0; 
  String success;

//Structure datelor transmise, trebuie să fie aceeaşi la emisie şi recepţie 
  typedef struct struct_message 
  {
  int L1; 
  int L2; 
  int L3; 
  int L4; 
  float ana;
  } 
  struct_message;
  struct_message Readings; //generează o structură pentru datele de feedback primite
  struct_message incomingReadings;
    
    void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0){ 
    Serial.println("Delivery success");   
    }
    
    else{ 
      Serial.println("Delivery fail");      
      } 
      }
      
  void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
    Serial.print("Bytes received: "); 
    Serial.println(len);

    incomingAn = incomingReadings.ana; //date primite pentru feedback
                      }
                      
    void getReadings(){ //citeşte date de la butoane si A0 pentru tranmitere
    sendL1=digitalRead(14); 
    sendL2=digitalRead(4); 
    sendL3=digitalRead(5);
    sendL4=digitalRead(16); 
    analog=analogRead(analogPin); 
            }
            
    void printIncomingReadings(){ //afişează pe OLED date de feedback
        display.clearDisplay(); 
        display.setTextSize(2); 
        display.setCursor(0,0);
        display.print("An:"); 
        display.print(incomingAn); 
        display.display();
          }
  
  void setup() { 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.setTextColor(WHITE);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect();

  if (esp_now_init() != 0) {Serial.println("Error initializing ESP-NOW");
      return; }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  esp_now_register_recv_cb(OnDataRecv);
    }
    
    void loop() {
   unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) { previousMillis = currentMillis;
      getReadings(); //CITESţE BUTOANE Şi potenţiometru şi trimite datele
      Readings.L1 = sendL1; 
      Readings.L2 = sendL2;
      Readings.L3 = sendL3; 
      Readings.L4 = sendL4; 
      Readings.ana = analog;
  esp_now_send(broadcastAddress, (uint8_t *) &Readings, sizeof(Readings));
      printIncomingReadings();      
      } 
      }
  //End of the code
