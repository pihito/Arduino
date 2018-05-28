#include <Wire.h>
#include <SPI.h>
#include "U8glib.h" //for OLED I2C Screen
#include "RF24.h" // for radio module
#include "bitmap.h" // custom bitmap to display on screen 

//OLED screen configuration
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK,U8G_I2C_OPT_FAST, U8G_I2C_OPT_DEV_0);  // I2C 128x64(col2-col129) SH1106,Like HeiTec 1.3' I2C OLED 

#define PAGE_BT 2
int page = 0; 

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 and name of device*/
RF24 radio(7,8);
byte address[6]="SCREEN";


//data structure to transmit must be the same on transmiter
#define DATA_TEMP 0 
#define DATA_HUMIDITY 1
#define DATA_PIR 2
float data[] = {0,0,0};

float old_data[] = {0,0,0};

int temperature = 22;
int humidity = 9;

void draw(void) {
  u8g.drawBitmapP( 0, 0, 16, 64, fond1);
  int base_line = 40;
  // graphic commands to redraw the complete screen should be placed here  
  //u8g.setFont(u8g_font_unifont);
  u8g.setFont(u8g_font_freedoomr25n);
  u8g.setPrintPos(0,base_line);
  u8g.print(data[DATA_TEMP],0 );
  u8g.setFont(u8g_font_osb18);
  u8g.setPrintPos(97,base_line - 10);
  u8g.print(data[DATA_HUMIDITY],0 );
}


void setup() {
  Serial.begin(9600);

  pinMode(PAGE_BT,INPUT_PULLUP);
  //start the radio module, and power to low due to the proximity of device during the test in production set to RF24_PA_MAX
  //open a pipe to recieve data and start listing
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1,address);
  radio.startListening();
  
}

void loop() {
   
   if( radio.available()){ //we have recieve something, we read the payload
      while (radio.available()) {  
        radio.read( &data, sizeof(data) );            
        Serial.print("temp : ");
        Serial.print(data[DATA_TEMP]);
        Serial.print(" Hum : ");
        Serial.print(data[DATA_HUMIDITY]);
        Serial.print(" presence : ");
        Serial.println(data[DATA_PIR]);
      }
   }

    boolean etatBouton=digitalRead(PAGE_BT);
    Serial.print(" BT :"); 
    Serial.println(etatBouton);
   if(etatBouton == LOW) 
    if(page == 1) page = 0;
    else page =1 
   
   if( data[0] != old_data[0] ||  data[1] != old_data[1] || data[2] != old_data[2]){
    old_data[0] = data[0];
    old_data[1] = data[1];
    old_data[2] = data[2];
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
   }
  delay(5000);
<<<<<<< HEAD
}
=======
}
>>>>>>> 27bc503e7bd5b8af67db55fa7c765df5828e5685
