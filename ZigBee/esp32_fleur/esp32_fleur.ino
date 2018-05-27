//view readme for lib and wiring

#include <Arduino.h>
#include <U8x8lib.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);



//wifi setup 
const char* ssid     = "Livebox-C186_2GEXT";
const char* password = "QXA4Dy5WmgxKPqCmK4";

void setup () {
  Serial.begin(115200);
  delay(10);

  //we start the screen
  u8x8.begin();
  u8x8.setPowerSave(0);


  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.print("Wait for WiFi... ");
  

  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  delay(500);

  }

void loop(void)
{
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.setCursor(0,12);
  u8x8.print( WiFi.localIP());
  u8x8.refreshDisplay();    // only required for SSD1606/7  
  delay(2000);
}
