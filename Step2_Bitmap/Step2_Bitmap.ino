#include <U8g2lib.h>
#include <Wire.h>
#include "temperature.h"



U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);

void draw(void) {
  u8g2.drawXBMP( 0, 0, 128, 64, temperature);
  //u8g2.drawXBM( 0, 0, test_width, test_height, test_bits);
  int base_line = 15;
   u8g2.setFont(u8g2_font_ncenB14_tr);
   u8g2.drawStr(0,24,"21");
}

void setup() {
  u8g2.begin();
}

void loop() {
   u8g2.firstPage();  
    do {
      draw();
    } while( u8g2.nextPage() );
}
