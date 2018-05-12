
/**
4 7segment vith 595 controler
-------------------------------
The MIT License (MIT)
Copyright (c) 2015 ArtOfCode
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-------------------------------
**/

//      A
//  F       B
//      G  
//  E       C
//      D       DP 


//FE = seg A
//FD = seg B
//FB = seg C    
//F7 = seg D
//EF = seg E
//DF = seg F
//BF = seg G
//7F = seg DP


#define SEG_A  0xFE
#define SEG_B  0xFD
#define SEG_C  0xFB
#define SEG_D  0xF7
#define SEG_E  0xEF
#define SEG_F  0xDF
#define SEG_G  0xBF
#define SEG_DP = 0x7F

#define LED4  0x01 
#define LED3  0x02
#define LED2  0x04
#define LED1  0x08

unsigned char LED_OFFSET[] = {LED1, LED2, LED3, LED4};

unsigned char LED_MATRICE[] = 
{
  // 0  1    2    3      4    5    6    7    8    9   10  11   12    13   14   15  16   17    18
  // 0  1    2    3      4    5    6    7    8    9    A   b    C    d    E    F    -   L    blank
  0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xbf,0xC7, 0xFF
};


//pin setup
int SCLK = 12;
int RCLK = 11;
int DIO = 10; 

int trig = 6; 
int echo = 7; 
long lecture_echo; 
long cm;

unsigned char seg[] = {LED_MATRICE[18],LED_MATRICE[18],LED_MATRICE[18],LED_MATRICE[18]}; 

long timer;

void setup ()
{
  pinMode(SCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(DIO,OUTPUT); 

  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT); 
  Serial.begin(9600); 

  timer = millis();
}


void loop()
{
  if((millis() - timer) > 1000) {
   readCapteur_HC_SR04();
    timer = millis();
  }else {
  
 
 seg[0] = LED_MATRICE[18];
 seg[1] = LED_MATRICE[8];
 seg[2] = LED_MATRICE[1];
 seg[3] = LED_MATRICE[1];
  display(seg); 
 
//   delay(1000); 

}
}
//ecris le tableau de 4 led sur la sortie 
void display(unsigned char  *led4)
{
  for( int i = 0; i <=4 ; i++)
  {
      LED_OUT(led4[i]);
      LED_OUT(LED_OFFSET[i]); 
      pulse(RCLK); 
  } 
  
}

//Ecrit un afficheur
void LED_OUT(unsigned char X)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    //on test le bit du haut pour voir si il est à 1 ou à 0
    if (X&0x80) 
            {
              digitalWrite(DIO,HIGH);
             }  
            else 
            {
              digitalWrite(DIO,LOW);
            }
    //on décale pour écrire le prochain bit 
    //(on injecte des 1 car 0 envoie low et c'est une cathode commune donc low pour allumer )
    X<<=1;

    pulse(SCLK);
  }
}

//envoie une pulsation sur la pin SCLK / RCLK
void pulse(int pin)
{
  digitalWrite(pin,LOW);
  digitalWrite(pin,HIGH);
}

void readCapteur_HC_SR04()
{
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  cm = lecture_echo / 58; 
  Serial.print("Distancem : "); 
  Serial.println(cm); 
}
