//LV la +3v. HV la +5v  pinul VU de la Node)
 //LV1 la D4, Lv2 la D3, 
 //HV1 la Clk mouse, 
/*
  genereaza Hot Spot AP cu 
  IP 192.168.4.1
  dupa incarcare pe Oled si Serial Monitor 
  apare adresa IP 192.169.4.1
  Se dexchide pe Android Chrome
  Se introdice 192.168.4.1/webserial
  apare pagina web 
*/
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

#include <Arduino.h>
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

const char* ssid = "ESP8266-AP"; // Your WiFi AP SSID 
const char* password = "12345678"; // Your WiFi Password

//#define MDATA 14//D5
//#define MCLK 12//D7, pot defini cum doresc

//#define MDATA 0 //D3
//#define MCLK 2 //D4, pot defini cum doresc

#define MDATA 2 //D3
#define MCLK 0 //D4, pot defini cum doresc


int distance =0;
int distancey =0;// pentru distanta pe Oy
int distancez =0;// pentru distanta pe Oz
unsigned long time1=0, time2=0,delta=0, sp=0, spy=0, spz=0;

void gohi(int pin)
{
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

void golo(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void mouse_write(char data)
{
  char i;
  char parity = 1;

  //  Serial.print("Sending ");
  //  Serial.print(data, HEX);
  //  Serial.print(" to mouse\n");
  //  Serial.print("RTS");
  /* put pins in output mode */
  gohi(MDATA);
  gohi(MCLK);
  delayMicroseconds(300);
  golo(MCLK);
  delayMicroseconds(300);
  golo(MDATA);
  delayMicroseconds(10);
  /* start bit */
  gohi(MCLK);
  /* wait for mouse to take control of clock); */
  while (digitalRead(MCLK) == HIGH)
    ;
  /* clock is low, and we are clear to send data */
  for (i=0; i < 8; i++) {
    if (data & 0x01) {
      gohi(MDATA);
    } 
    else {
      golo(MDATA);
    }
    /* wait for clock cycle */
    while (digitalRead(MCLK) == LOW)
      ;
    while (digitalRead(MCLK) == HIGH)
      ;
    parity = parity ^ (data & 0x01);
    data = data >> 1;
  }  
  /* parity */
  if (parity) {
    gohi(MDATA);
  } 
  else {
    golo(MDATA);
  }
  while (digitalRead(MCLK) == LOW)
    ;
  while (digitalRead(MCLK) == HIGH)
    ;
  /* stop bit */
  gohi(MDATA);
  delayMicroseconds(50);
  while (digitalRead(MCLK) == HIGH)
    ;
  /* wait for mouse to switch modes */
  while ((digitalRead(MCLK) == LOW) || (digitalRead(MDATA) == LOW))
    ;
  /* put a hold on the incoming data. */
  golo(MCLK);
  //  Serial.print("done.\n");
}

/*
 * Get a byte of data from the mouse
 */
char mouse_read(void)
{
  char data = 0x00;
  int i;
  char bit = 0x01;

  //  Serial.print("reading byte from mouse\n");
  /* start the clock */
  gohi(MCLK);
  gohi(MDATA);
  delayMicroseconds(50);
  while (digitalRead(MCLK) == HIGH)
    ;
  delayMicroseconds(5);  /* not sure why */
  while (digitalRead(MCLK) == LOW) /* eat start bit */
    ;
  for (i=0; i < 8; i++) {
    while (digitalRead(MCLK) == HIGH)
      ;
    if (digitalRead(MDATA) == HIGH) {
      data = data | bit;
    }
    while (digitalRead(MCLK) == LOW)
      ;
    bit = bit << 1;
  }
  /* eat parity bit, which we ignore */
  while (digitalRead(MCLK) == HIGH)
    ;
  while (digitalRead(MCLK) == LOW)
    ;
  /* eat stop bit */
  while (digitalRead(MCLK) == HIGH)
    ;
  while (digitalRead(MCLK) == LOW)
    ;

  /* put a hold on the incoming data. */
  golo(MCLK);
  //  Serial.print("Recvd data ");
  //  Serial.print(data, HEX);
  //  Serial.print(" from mouse\n");
  return data;
}

void mouse_init()

 { char mouseId;
   //depisteaza automat tipul de mouse
  gohi(MCLK);
  gohi(MDATA);
  //  Serial.print("Sending reset to mouse\n");
  mouse_write(0xff);
  mouse_read();  /* ack byte */
  //  Serial.print("Read ack byte1\n");
  mouse_read();  /* blank */
  mouse_read();  /* blank */
  //  Serial.print("Setting sample rate 200\n");
  mouse_write(0xf3);  /* Set rate command */
  mouse_read();  /* ack */
  mouse_write(0xC8);  /* Set rate command */
  mouse_read();  /* ack */
  //  Serial.print("Setting sample rate 100\n");
  mouse_write(0xf3);  /* Set rate command */
  mouse_read();  /* ack */
  mouse_write(0x64);  /* Set rate command */
  mouse_read();  /* ack */
  //  Serial.print("Setting sample rate 80\n");
  mouse_write(0xf3);  /* Set rate command */
  mouse_read();  /* ack */
  mouse_write(0x50);  /* Set rate command */
  mouse_read();  /* ack */
  //  Serial.print("Read device type\n");
  mouse_write(0xf2);  /* Set rate command */
  mouse_read();  /* ack */
  mouse_read();  /* mouse id, if this value is 0x00 mouse is standard, if it is 0x03 mouse is Intellimouse */
  //  Serial.print("Setting wheel\n");
  mouse_write(0xe8);  /* Set wheel resolution */
  mouse_read();  /* ack */
  mouse_write(0x03);  /* 8 counts per mm */
  mouse_read();  /* ack */
  mouse_write(0xe6);  /* scaling 1:1 */
  mouse_read();  /* ack */
  mouse_write(0xf3);  /* Set sample rate */
  mouse_read();  /* ack */
  mouse_write(0x28);  /* Set sample rate */
  mouse_read();  /* ack */
  mouse_write(0xf4);  /* Enable device */
  mouse_read();  /* ack */

  //  Serial.print("Sending remote mode code\n");
  mouse_write(0xf0);  /* remote mode */
  mouse_read();  /* ack */
  //  Serial.print("Read ack byte2\n");
  delayMicroseconds(100);
}

/* Message callback of WebSerial */
/*
void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
    Serial.println(d);
    
  }
  WebSerial.println(d);
}
*/
void setup() {
    Serial.begin(115200);
     mouse_init();
     
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    /* Attach Message Callback */
    //WebSerial.msgCallback(recvMsg);
    //functia de sus blocheaza serverul
    server.begin();
  
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("ESP8266 webserial IP=");
  
  display.print(IP);
  //display.print(WiFi.localIP());
  display.display();
  delay(2000);
}

void loop() {

//de la mouse
  char mstat;
  char mx;
  char my;    //pentru Oy
  char mz;    //pentru Oz

  /* get a reading from the mouse */
  mouse_write(0xeb);  /* give me data! */
  mouse_read();      /* ignore ack */
  mstat = mouse_read();
  mx = mouse_read();
  my = mouse_read();  //pentru Oy
  mz = mouse_read();  //pentru Oz
  
  time2=millis(); // Get the time
  delta = time2-time1; //Calculate the increment
  
  if (delta>0) sp = 1000*abs(mx)/delta;
  distance+=mx;//THIS DISTANCE IS IN MOUSE TICKS, see the tutorial for measuring real distances (calibration);
  //We only need to multiply the 'distance' variable with the constant we get from calibration.
  //if (delta>0); 
  spy = 1000*abs(my)/delta;//adaug viteza pe OY
  distancey+=my;  //adaug pentru Oy

//if (delta>0);
spz = 1000*abs(mz)/delta;//adaug viteza pe OZ
  distancez+=10*mz;  //adaug pentru OZ


  /* send the data back up */
// cu galben am scos afisare pe monitor
  Serial.print(delta, DEC);
  Serial.print("\t");
  Serial.print(time1, DEC);
  Serial.print("\t");
  Serial.print(time2, DEC);
  Serial.print("\tX=");
  Serial.print(mx, DEC);
  Serial.print("\tV=");
  Serial.print(sp, DEC);
  Serial.print("\t");
  Serial.print(distance, DEC);
  Serial.println();
  delay(20);  /* twiddle */
  time1=time2; //Set the current time to be the previous
 
    
WebSerial.print(" Mx=");
    WebSerial.print(mx); 
    WebSerial.println(" cm");
    

    WebSerial.print(" dist=");
    WebSerial.print(distance); 
    WebSerial.println(" cm");
    Serial.println();
    
    //delay(20);
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("x=");
  display.println(mx);

  //display.print("y=");
  //display.println(data.position.y);

  display.print("dist=");
  display.print(distance);
  
  display.display();
  //de la mouse
  delay(1000); 
            }
