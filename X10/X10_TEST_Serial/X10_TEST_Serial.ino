// constants won't change. They're used here to 
// set pin numbers:
const int btOnPin = 7;     
const int btOffPin = 8;
const int ledOnPin =  5;      
const int ledOffPin =  6;      

#define OFF 0x00
#define ON 0x01
#define BRIGHT 0x02
#define DIM 0x03
#define LED 13
#define X10 12

const byte house_code[] = { 0x60, 0x70, 0x40, 0x50, 0x80, 0x90, 0xA0, 0xB0, 0xE0, 0xF0, 0xC0, 0xD0, 0x00, 0x10, 0X20, 0x30 } ;
const byte unit_code[] = { 0x00, 0x10, 0x08, 0x18, 0x40, 0x50, 0x48, 0x58 } ;

byte HouseCode = 'C' ;
byte UnitCode = 1 ;



// variables will change:
int btOnState = 0;         // variable for reading the pushbutton status
int btOffState = 0;         // variable for reading the pushbutton status


// --- Fonctions X10 ---
// Envoi entÃªte :
void x10_sendpreamble(void)
{
  digitalWrite(X10,LOW) ;
  delay(40) ;
  digitalWrite(X10,HIGH) ;
  delay(9) ;
  digitalWrite(X10, LOW) ;
  delay(4) ;
  delayMicroseconds(500) ;
}

// ----------------------
// Envoi bit :
void x10_sendbit(void)
{
  digitalWrite(X10,HIGH) ;
  delayMicroseconds(560) ;
  digitalWrite(X10,LOW) ;
  delayMicroseconds(560) ;
}

// ----------------------
// Envoi d'un octet X10 RF :
void x10_sendbyte(byte X10octet)
{
  unsigned char nobit, valbit;
  for (nobit=0; nobit<=7; nobit++)
  {
    valbit=X10octet & 0x80;
    X10octet=(X10octet << 1);

    x10_sendbit();
    if ( valbit )
    {
      delayMicroseconds(1200) ;
    }
  }
}


// Envoie trame X10, House Code / Unit Code / Action (ON/OFF/DIM/BRIGHT)
void x10_sendcmd(byte House, byte Unit, byte Action)
{
  byte hc, uc ;

  hc = house_code[House - 0x41] ; // Lit code correspondant dans tableau house_code.
  if (Unit > 0x08)
    hc |= 0x04 ;                  // Si Unit Code > 8 alors bit 2 House Code Ã  1.

  uc = unit_code[Unit] ;          // Lit code correspondant dans tableau unit_code.
  
  if (Action==OFF)
    uc |= 0x20 ;                  // si Action = OFF, mise Ã  '1' bit 5 unit code.
  else if(Action==BRIGHT)
    uc = 0x88 ;
  else if(Action==DIM)
    uc = 0x98 ;
	
  // Envoie commande X10 hc/uc.
  x10_sendpreamble() ;
  x10_sendbyte(hc) ;		// house code
  x10_sendbyte(~hc) ;		// ~house code
  x10_sendbyte(uc) ;		// unit code
  x10_sendbyte(~uc) ;		// ~unit code
  x10_sendbit() ;
}

byte value=0;
byte previous=0;

void setup() {
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  //initialisation des Led
  pinMode(ledOnPin, OUTPUT);
  pinMode(ledOffPin, OUTPUT);  
  pinMode(12, OUTPUT); //port pour le module AUREL
  pinMode(13, OUTPUT); //visualisation LED
  digitalWrite(LED,HIGH);
  x10_sendcmd(HouseCode, UnitCode, OFF);
  delay(5000);
  digitalWrite(LED,LOW);
}

void loop(){
  int i = 0;
  byte value[3];
  byte incomingByte;
  /*while (i<3)
  {
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      // say what you got:
      Serial.print("I received: ");
      Serial.write(incomingByte);
      value[i++] = incomingByte;
      
    }
  }
  
  digitalWrite(ledOnPin, HIGH); 
  Serial.write("\nsend commande\n");
  //if(value[2] == 1) {
    //x10_sendcmd(HouseCode, UnitCode, ON) ;
    //Serial.write("ON\n"); }
  //if(value[2] == 0){*/
    x10_sendcmd(HouseCode, UnitCode, OFF) ;
    x10_sendcmd(HouseCode, UnitCode, OFF) ;
    x10_sendcmd(HouseCode, UnitCode, OFF) ;
    x10_sendcmd(HouseCode, UnitCode, OFF) ;
    x10_sendcmd(HouseCode, UnitCode, OFF) ;
  //Serial.write("*****OFF****\n");
  //}
  //Serial.write("end commande\n");
  
  delay(5000);
  digitalWrite(ledOnPin, LOW); 

}
