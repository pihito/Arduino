/***********************************************/
/* Emetteur X10 RF Ã  partir d'un potentiomÃ¨tre */
/* Version : 27/12/2010 - www.domocreation.fr  */
/***********************************************/

#define OFF 0x00b 
#define ON 0x01
#define BRIGHT 0x02
#define DIM 0x03
#define LED 13
#define X10 12

const byte house_code[] = { 0x60, 0x70, 0x40, 0x50, 0x80, 0x90, 0xA0, 0xB0, 0xE0, 0xF0, 0xC0, 0xD0, 0x00, 0x10, 0X20, 0x30 } ;
const byte unit_code[] = { 0x00, 0x10, 0x08, 0x18, 0x40, 0x50, 0x48, 0x58 } ;

byte HouseCode = 'C' ;
byte UnitCode = 1 ;

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
byte sensor=0;
byte previous=0;

void setup(){
  pinMode(12, OUTPUT); //port pour le module AUREL
  pinMode(13, OUTPUT); //visualisation LED
  digitalWrite(LED,HIGH);
  x10_sendcmd(HouseCode, UnitCode, OFF) ; //extinction du module pour connaÃ®tre l'Ã©tat initial
  delay(5000);
  digitalWrite(LED,LOW);
  previous=analogRead(0)/100;
}

void loop(){
  digitalWrite(LED,LOW); 
  x10_sendcmd(HouseCode, UnitCode, OFF) ; //extinction du module pour connaÃ®tre l'Ã©tat initial
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW); 
  x10_sendcmd(HouseCode, UnitCode, ON) ; //extinction du module pour connaÃ®tre l'Ã©tat initial
  digitalWrite(LED,HIGH);
}
