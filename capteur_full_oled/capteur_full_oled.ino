#include "U8glib.h" //for OLED I2C Screen
#include <Wire.h>
#include <dht.h>

//DHT sur digital pin 3 
//gaz sur Analog pin 0
#define NODE_ID 1
#define DHT22_PIN 3
#define MQ135_PIN 0

dht DHT;
const int SCR_TEMP = 0; 
const int SCR_HUM = 1;
const int SCR_GAZ = 2;
float screenValue[3];
int DhtChk = 0;

/* SLboat Add Device */
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED 

void draw(void) {
  int base_line = 22;
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.setPrintPos(0,base_line);
  if(DhtChk == DHTLIB_OK) {
    u8g.print("temp: " );
    u8g.print(screenValue[SCR_TEMP],1 );
    u8g.setPrintPos(0,base_line+19);
    u8g.print("Hum: " );
    u8g.print(screenValue[SCR_HUM],1 );
  }
  else
    u8g.print(printDHTError(DhtChk));
  
  u8g.setPrintPos(0,base_line+19*2);
  u8g.print("gaz: " );
  u8g.print(screenValue[SCR_GAZ],1 );
}

String printDHTError(int chk)
{
  String ret;
  switch (chk) {
      case DHTLIB_ERROR_CHECKSUM:
          ret = "Checksum error";
          break;
      case DHTLIB_ERROR_TIMEOUT:
          ret = "Time out error";
          break;
      case DHTLIB_ERROR_CONNECT:
          ret = "Connect error";
          break;
      case DHTLIB_ERROR_ACK_L:
          ret = "Ack Low error";
          break;
      case DHTLIB_ERROR_ACK_H:
          ret = "Ack High error";
          break;
      default:
          ret = "Unknown error";
          break;
      }
      return ret;
}
void refreshDHT()
{
  DhtChk = DHT.read22(DHT22_PIN);
  float fHum = 0;
  float fTemp = 0;
  if (DhtChk == DHTLIB_OK)
  {
    screenValue[SCR_HUM] = DHT.humidity;
    screenValue[SCR_TEMP] = DHT.temperature;
  }
  else
  {
    screenValue[SCR_HUM] = 0;
    screenValue[SCR_TEMP] = 0;
  }
}

void refreshGaz()
{
  screenValue[SCR_GAZ] = analogRead(MQ135_PIN);
}

void refreshPIR()
{
  Serial.print("PIR : ");
  int state = digitalRead(4);
  if(state) {
    digitalWrite(5,HIGH);
    Serial.println("active");
  }
  else {
    digitalWrite(5,LOW);
    Serial.println("spleep");
  }
    
  
  
}
void sendData(void)
{
  //chaine : ID;temp;hum; ;gaz;\n
  //chaine DHTError : ID;E;E;Error Value;gaz;\n
  Serial.print(NODE_ID);
  Serial.print(';');
  if(DhtChk == DHTLIB_OK) {
    Serial.print(screenValue[SCR_TEMP]);
    Serial.print(';');
    Serial.print(screenValue[SCR_HUM]);
    Serial.print("; ;");
  }
  else {
    Serial.print('E');
    Serial.print(';');
    Serial.print('E');
    Serial.print(";");
    Serial.print(printDHTError(DhtChk));
    Serial.print(";");
  }
  Serial.print(screenValue[SCR_GAZ]);
  Serial.println(';');
}

void setup(void) {
  
    Serial.begin(9600);
  
  // flip screen, if required
  // u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
  
  //pinMode(4, INPUT); 
  //pinMode(5, OUTPUT);
}

void loop(void) {
    refreshDHT();  
    refreshGaz();
    //refreshPIR();
  // picture loop
  sendData();
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(5000);
}
