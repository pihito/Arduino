#include "U8glib.h" //for OLED I2C Screen
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>

//DHT sur digital pin 3 
//gaz sur Analog pin 0

#define DHT22_PIN 3
#define MQ135_PIN 0

dht DHT;
const int SCR_TEMP = 0; 
const int SCR_HUM = 1;
const int SCR_GAZ = 2;
float screenValue[3];

/* SLboat Add Device */
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED 

void draw(void) {
  int base_line = 22;
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.setPrintPos(0,base_line);
  u8g.print("temp: " );
  u8g.print(screenValue[SCR_TEMP],1 );
  u8g.setPrintPos(0,base_line+19);
  u8g.print("Hum: " );
  u8g.print(screenValue[SCR_HUM],1 );
  u8g.setPrintPos(0,base_line+19*2);
  u8g.print("gaz: " );
  u8g.print(screenValue[SCR_GAZ],1 );
}

void printDHTError(int chk)
{
  switch (chk) {
      case DHTLIB_ERROR_CHECKSUM:
          Serial.print("Checksum error,\t");
          break;
      case DHTLIB_ERROR_TIMEOUT:
          Serial.print("Time out error,\t");
          break;
      case DHTLIB_ERROR_CONNECT:
          Serial.print("Connect error,\t");
          break;
      case DHTLIB_ERROR_ACK_L:
          Serial.print("Ack Low error,\t");
          break;
      case DHTLIB_ERROR_ACK_H:
          Serial.print("Ack High error,\t");
          break;
      default:
          Serial.print("Unknown error,\t");
          break;
      }

}
void refreshDHT()
{
  Serial.print("DHT22, \t");
  int chk = DHT.read22(DHT22_PIN);
  float fHum = 0;
  float fTemp = 0;
  if (chk == DHTLIB_OK)
  {
    screenValue[SCR_HUM] = DHT.humidity;
    screenValue[SCR_TEMP] = DHT.temperature;
    Serial.print("temp : ");
    Serial.println(screenValue[SCR_TEMP],1);
    Serial.print("Hum : ");
    Serial.println(screenValue[SCR_HUM],1);    
  }
  else
  {
    screenValue[SCR_HUM] = 0;
    screenValue[SCR_TEMP] = 0;
    printDHTError(chk);
  }
}

void refreshGaz()
{
  screenValue[SCR_GAZ] = analogRead(MQ135_PIN);
  Serial.print("gaz : ");
  Serial.println(screenValue[SCR_GAZ],1);
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
void setup(void) {
  
    Serial.begin(115200);
    Serial.println("dht22_test.ino");
    Serial.print("LIBRARY VERSION: ");
    Serial.println(DHT_LIB_VERSION);
  
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
  
  pinMode(4, INPUT); 
  pinMode(5, OUTPUT);
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    refreshDHT();  
    refreshGaz();
    refreshPIR();
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(5000);
}
