#include <U8g2lib.h>
#include <Wire.h>

/******************************** FULL BUFFER ****************************************************/ 

/*U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_fub20_tf );
    u8g2.drawStr(0,24,"Hello");
    u8g2.drawStr(0,50,"World!");
  u8g2.sendBuffer();
}

/***************************** BUFFER par page ************************************************/ 
/*U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_fub20_tf );
    // u8g2.drawStr(0,24," ");
    u8g2.drawStr(0,24,"Hello");
    u8g2.drawStr(0,50,"World!");
  } while ( u8g2.nextPage() );
}*/

/***************************** text mode pas de buffer  ************************************************/ 

U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE); 

void setup(void) {
  u8x8.begin();
}

void loop(void) {
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(0,1,"Hello World!");
}

