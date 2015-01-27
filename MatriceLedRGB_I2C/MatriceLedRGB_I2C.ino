//include for I2C
#include <Wire.h>

//addr composant 1
const int addr1=0x20;

//registre du MCP2317
const int IODIRA = 0x00;
const int IODIRB = 0x01;
const int GPPUA  = 0x0C;
const int GPPUB  = 0x0D;
const int GPIOA  = 0x12;
const int GPIOB  = 0x13;
const int OLATA  = 0x14;
const int OLATB  = 0x15;

//{nbr Step,0,0,0},{Step 1},{Step 2} ...}
//Step Definition : 
//{byte Col,byte Green,byte Red,byte Blue}
byte bClear[][4] = {{1,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111}};

byte bAllVert[][4] = {{1,0,0,0},{0b11111111,0b00000000,0b11111111,0b11111111}};


byte btest2[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b11111111,0b01111110,0b00000000,0b00000000},
                              {0b10000001,0b00000000,0b00000000,0b00000000}};
                          
byte btest3[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b01111110,0b10111101,0b00000000,0b00000000},
                              {0b01000010,0b10000001,0b00000000,0b00000000}};
                            
byte btest4[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00111100,0b11011011,0b00000000,0b00000000},
                              {0b00100100,0b11000011,0b00000000,0b00000000}};

byte btest5[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00011000,0b11100111,0b00000000,0b00000000}};
void setup() {
  Serial.begin(9600); //init serial for trace&debug
  Wire.begin(); // join i2c bus (address optional for master)
  // use table 1.4 from data sheet addressing scheme BANK=0 by default
  //put bank A&B on output
  Wire.beginTransmission(addr1); 
  Wire.write(IODIRA);             
  Wire.write(0x00); 
  Wire.write(0x00); //write IODIRB with the auto increment
  Wire.endTransmission();  
   
  Wire.beginTransmission(addr1); 
  Wire.write(GPIOA);             
  Wire.write(0x00); 
  Wire.write(0x00); //write IODIRB with the auto increment
  Wire.endTransmission(); 
}



void loop() {
    //drawIcon2(500,bAllVert);
    //drawIcon2(500,bClear);
    drawIcon2(500,btest2);
    drawIcon2(500,btest3);
    drawIcon2(500,btest4);
    drawIcon2(500,btest5);
    drawIcon2(250,bClear);
    drawIcon2(500,btest5);
    drawIcon2(250,bClear);
    drawIcon2(500,btest5);
    drawIcon2(500,btest4);
    drawIcon2(500,btest3);
    drawIcon2(500,btest2);
}


void drawIcon2(int iStepDuration,byte bSteps[][4]) {
  unsigned long previousMillis = millis();
  unsigned long currentMillis = 0;
  int iSteps = bSteps[0][0];
  do {
    for (int x = 1; x <= iSteps; x++) {
        Wire.beginTransmission(addr1);
        Wire.write(GPIOA);
        Wire.write(bSteps[x][0]);
        Wire.write(bSteps[x][1]);
        Wire.endTransmission();
        Wire.beginTransmission(addr1);
        Wire.write(GPIOA);
        Wire.write(0x00);
        Wire.endTransmission();
    }
    currentMillis = millis();;
  }while (currentMillis - previousMillis < iStepDuration); 
}

