//include for I2C
#include <Wire.h>


const int addr1=0x20; //colonne : A et vert : B
const int addr2=0x21; //Bleu : A et rouge : B

//registre du MCP2317
const int IODIRA = 0x00;
const int IODIRB = 0x01;
const int GPPUA  = 0x0C;
const int GPPUB  = 0x0D;
const int GPIOA  = 0x12;
const int GPIOB  = 0x13;
const int OLATA  = 0x14;
const int OLATB  = 0x15;

const int COLL = GPIOA;
const int GREEN = GPIOA;
const int BLUE = GPIOA;
const int RED = GPIOB;

const int cStepDuration = 500;

//{nbr Step,0,0,0},{Step 1},{Step 2} ...}
//Step Definition : 
//{byte Col,byte Green,byte Blue,byte Red}
byte bClear[][4] = {{1,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111}};


byte bRedPoint1[][4] = {{2,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b10000000,0b11111111,0b11111111,0b01111111}};
                              
byte bGreenPoint1[][4] = {{2,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b10000000,0b01111111,0b11111111,0b11111111}};

byte bBluePoint1[][4] = {{2,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b10000000,0b01111111,0b01111111,0b11111111}};                          
                              
byte bAllVert[][4] = {{1,0,0,0},{0b11111111,0b00000000,0b11111111,0b11111111}};


byte bGreenSquare1[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b11111111,0b01111110,0b11111111,0b11111111},
                              {0b10000001,0b00000000,0b11111111,0b11111111}};
                          
byte bGreenSquare2[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b01111110,0b10111101,0b11111111,0b11111111},
                              {0b01000010,0b10000001,0b11111111,0b11111111}};
                            
byte bGreenSquare3[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00111100,0b11011011,0b11111111,0b11111111},
                              {0b00100100,0b11000011,0b11111111,0b11111111}};

byte bGreenSquare4[][4] = {{2,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00011000,0b11100111,0b11111111,0b11111111}};

byte bRedSquare1[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b11111111,0b11111111,0b11111111,0b01111110},
                              {0b10000001,0b11111111,0b11111111,0b00000000}};
                          
byte bRedSquare2[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b01111110,0b11111111,0b11111111,0b10111101},
                              {0b01000010,0b11111111,0b11111111,0b10000001}};
                            
byte bRedSquare3[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00111100,0b11111111,0b11111111,0b11011011},
                              {0b00100100,0b11111111,0b11111111,0b11000011}};

byte bRedSquare4[][4] = {{2,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00011000,0b11111111,0b11111111,0b11100111}}; 
 
byte bBlueSquare1[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b11111111,0b11111111,0b01111110,0b11111111},
                              {0b10000001,0b11111111,0b00000000,0b11111111}};
                          
byte bBlueSquare2[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b01111110,0b11111111,0b10111101,0b11111111},
                              {0b01000010,0b11111111,0b10000001,0b11111111}};
                            
byte bBlueSquare3[][4] = {{3,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00111100,0b11111111,0b11011011,0b11111111},
                              {0b00100100,0b11111111,0b11000011,0b11111111}};

byte bBlueSquare4[][4] = {{2,0,0,0},{0b00000000,0b11111111,0b11111111,0b11111111},
                              {0b00011000,0b11111111,0b11100111,0b11111111}}; 
                              
void setup() {
  Serial.begin(9600); //init serial for trace&debug
  Wire.begin(); // join i2c bus (address optional for master)
  setupComponentOnOuput(addr1);
  setupComponentOnOuput(addr2);
  
  Wire.beginTransmission(addr1); 
  Wire.write(GPIOA);             
  Wire.write(0x00); 
  Wire.write(0xFF); //write IODIRB with the auto increment
  Wire.endTransmission(); 
  
  Wire.beginTransmission(addr2); 
  Wire.write(GPIOA);             
  Wire.write(0xFF); 
  Wire.write(0xFF); //write IODIRB with the auto increment
  Wire.endTransmission(); 
}



void setupComponentOnOuput(int addr)
{
 // use table 1.4 from data sheet addressing scheme BANK=0 by default
  //put bank A&B on output
  Wire.beginTransmission(addr); 
  Wire.write(IODIRA);             
  Wire.write(0x00); 
  Wire.write(0x00); //write IODIRB with the auto increment
  Wire.endTransmission();  
}

void DrawGreenSquare(int StepDuration)
{
  drawIcon2(StepDuration,bGreenSquare1);
  drawIcon2(StepDuration,bGreenSquare2);
  drawIcon2(StepDuration,bGreenSquare3);
  drawIcon2(StepDuration,bGreenSquare4);  
}

void DrawBlueSquare(int StepDuration)
{
  drawIcon2(StepDuration,bBlueSquare1);
  drawIcon2(StepDuration,bBlueSquare2);
  drawIcon2(StepDuration,bBlueSquare3);
  drawIcon2(StepDuration,bBlueSquare4);  
}
void DrawRedSquare(int StepDuration)
{
  drawIcon2(StepDuration,bRedSquare1);
  drawIcon2(StepDuration,bRedSquare2);
  drawIcon2(StepDuration,bRedSquare3);
  drawIcon2(StepDuration,bRedSquare4);  
}

void loop() {
  DrawGreenSquare(cStepDuration);
  DrawBlueSquare(cStepDuration);
  DrawRedSquare(cStepDuration);
  drawIcon2(500,bRedPoint1);
  drawIcon2(500,bGreenPoint1);
  drawIcon2(500,bBluePoint1);
}


void drawIcon2(int iStepDuration,byte bSteps[][4]) {
  unsigned long previousMillis = millis();
  unsigned long currentMillis = 0;
  int iSteps = bSteps[0][0];
  do {
    for (int x = 1; x <= iSteps; x++) {
        Wire.beginTransmission(addr1);
        Wire.write(COLL);
        Wire.write(bSteps[x][0]);
        Wire.write(bSteps[x][1]);
        Wire.endTransmission();
       
        Wire.beginTransmission(addr2);
        Wire.write(BLUE);
        Wire.write(bSteps[x][2]);
        Wire.write(bSteps[x][3]);
        Wire.endTransmission();
        
        Wire.beginTransmission(addr1); //reser the col, to avoid scratch
        Wire.write(COLL);
        Wire.write(0x00);
        Wire.endTransmission();
    }
    currentMillis = millis();;
  }while (currentMillis - previousMillis < iStepDuration); 
}

