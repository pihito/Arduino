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

void testBlue()
{
  byte col = 0b00000001;
  byte line= 0b11111110;
  for(int i=0;i<8;i++) {
        Wire.beginTransmission(addr1);
        Wire.write(GPIOA);
        Wire.write(col);
        //Wire.write(0xFF);
        Wire.endTransmission();
        Wire.beginTransmission(addr2);
        Wire.write(GPIOA);
        Wire.write(line);
        Wire.endTransmission();    
        line = line << 1;
        delay(cStepDuration);       
        Wire.beginTransmission(addr2);
        Wire.write(GPIOA);
        Wire.write(0xFF);
        Wire.endTransmission();  
  }
}
void testGreen()
{
  //check Line green
 byte col = 0b00000001;
 byte line= 0b11111110;
  for(int i=0;i<8;i++) {
        Wire.beginTransmission(addr1);
        Wire.write(GPIOA);
        Wire.write(col);
        Wire.write(line);
        Wire.endTransmission();    
        Serial.println(col);
        line = line << 1;
        delay(cStepDuration);       
        Wire.beginTransmission(addr1);
        Wire.write(GPIOB);
        Wire.write(0xFF);
        Wire.endTransmission();          
  }

}

void testCollonne()
{
   byte col = 0b00000001;
  byte line= 0b11111110;
  //check colonne  
  for(int i=0;i<8;i++) {
        Wire.beginTransmission(addr1);
        Wire.write(GPIOA);
        Wire.write(col);
        Wire.write(line);
        Wire.endTransmission();    
        Serial.println(col);
        col = col << 1;
        delay(cStepDuration);       
        Wire.beginTransmission(addr1);
        Wire.write(GPIOA);
        Wire.write(0x00);
        Wire.endTransmission();     
        
  }
}

void testRed()
{
  byte col = 0b00000001;
  byte line= 0b11111110;
  for(int i=0;i<8;i++) {
        Wire.beginTransmission(addr1);
        Wire.write(GPIOA);
        Wire.write(col);
        Wire.endTransmission();
        Wire.beginTransmission(addr2);
        Wire.write(GPIOB);
        Wire.write(line);
        Wire.endTransmission();    
        line = line << 1;
        delay(cStepDuration);       
        Wire.beginTransmission(addr2);
        Wire.write(GPIOB);
        Wire.write(0xFF);
        Wire.endTransmission();     
        
  } 
}

void testMatriceWiring()
{
 testCollonne();
 testGreen();
 testBlue();
 testRed();
}

void loop() {
  testMatriceWiring();
}
