#include <U8g2lib.h>
#include <Wire.h>
#include "image.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
}

void draw(){
  //u8g2.drawXBM(0,0,128,64,img_temp);
  u8g2.drawXBMP(0,0,128,64,img_temp);
   int base_line = 15;
   u8g2.setFont(u8g2_font_ncenB14_tr);
   u8g2.drawStr(0,24,"21");
}

void loop() {
  
  u8g2.firstPage();
  do {
    draw();
  } while ( u8g2.nextPage() );

}

