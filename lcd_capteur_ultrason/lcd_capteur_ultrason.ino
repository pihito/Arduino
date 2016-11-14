#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG  12 
#define ECHO  11
 



// décrit comment est connecté l'écan LCD au composant I2C
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


void setup() {
   Serial.begin(9600);
   setup_Capteur_HC_SR04(TRIG,ECHO); //fonction qui initialise les Pin du capteur 
   lcd.begin(16,2);         // initialise l'écran en 16 caractère par 2 lignes 

}

void loop() {
  //Lit le capteur ultrason
  long dist = readCapteur_HC_SR04(TRIG,ECHO);
  
  //Ecrit la valeur sur l'écran 
  lcd.setCursor(0,0);  
  lcd.print("dsit :  ");
  lcd.setCursor(6,0);
  lcd.print(dist,DEC);
  
 

}

/* fonction d'initialisation du capteur HC SR04
 * int trig : pin de l'arduino pour la patte trig du capteur  
 * int echo : pin de l'arduino pour la patte echo du capteur
 */
void setup_Capteur_HC_SR04(int trig,int echo)
{
  pinMode(trig, OUTPUT); 
  digitalWrite(trig, LOW); 
  pinMode(echo, INPUT);  
}

/* fonction de lecture du capteur HC SR04, renvoie la distance en cm et l'écrit sur le port serie 
 * int trig : pin de l'arduino pour la patte trig du capteur  
 * int echo : pin de l'arduino pour la patte echo du capteur
 * retour long : renvoie la distance en cm 
 */
long readCapteur_HC_SR04(int trig,int echo)
{
  long cm = 0; 
  long lecture_echo =0;
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig, LOW); 
  lecture_echo = pulseIn(echo, HIGH); 
  cm = lecture_echo / 58; 
  Serial.print("Distancem : "); 
  Serial.println(cm); 
  return cm;
}
