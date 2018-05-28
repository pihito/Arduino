// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

//M1==>Vert==>1

AF_DCMotor mVert(1);
AF_DCMotor mRouge(2);
AF_DCMotor mBleu(4);
AF_DCMotor mJaune(3);

void testMotor( AF_DCMotor *motor )
{
  Serial.print("tick");
  motor->run(FORWARD);
  delay(1000);
  Serial.print("toc");
  motor->run(BACKWARD);
  delay(1000);
  Serial.print("tech");
  motor->run(RELEASE);
  delay(1000);
}

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  mVert.setSpeed(200);
  mVert.run(RELEASE);

  // turn on motor
  mRouge.setSpeed(200);
  mRouge.run(RELEASE);

   mJaune.setSpeed(200);
  mJaune.run(RELEASE);

   mBleu.setSpeed(200);
  mBleu.run(RELEASE);
}
void roule(uint8_t sp,int d)
{
    mBleu.setSpeed(sp);
  mRouge.setSpeed(sp);
  mVert.setSpeed(sp);
  mJaune.setSpeed(sp);
  
mVert.run(d);
mRouge.run(d);
mBleu.run(d);
mJaune.run(d);
 }
void enAvant(uint8_t sp )
{
  roule( sp, FORWARD);
}

void enArriere(uint8_t sp )
{
  roule( sp, BACKWARD);
}


void loop() {
  uint8_t i;
  
/*Serial.print("moteur vert avant");
testMotor(&mVert);
  Serial.print("moteur rouge arrière");
 testMotor(&mRouge); */
/*  Serial.print("moteur bleu avant");
 testMotor(&mBleu);
   Serial.print("moteur Jaune Arriere");
 testMotor(&mJaune);
 */
 enArriere(200);
}
