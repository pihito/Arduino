/*************************************************** 
  This is an example for our Sunfounder TB6612 Motor driver
  speed and direction test - this will drive 2 motors, speed increase and then decrese

 ****************************************************/

#include <SunFounder_TB6612_Motor_Driver.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

TB6612 motorA (5,6);
TB6612 motorB(9,10);
TB6612 motorC(7,11);
TB6612 motorD(2,3);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup() {
  Serial.begin(9600);
  Serial.println("TB6612 Motor test!");
  // Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol


  lcd.begin(16,2);         // initialize the lcd for 16 chars 2 lines and turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight();
  lcd.setCursor(0,0); 
  lcd.print("coucou theotime");
   lcd.setCursor(0,1); 
   lcd.print("coucou lolo");
   
}

void loop() {
  for(int pwm_value=50; pwm_value<256; pwm_value++){
      motorA.forward(pwm_value);
      motorB.forward(pwm_value);
      motorC.forward(pwm_value);
      motorD.forward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  Serial.println();
  for(int pwm_value=255; pwm_value>50; pwm_value--){
      motorA.forward(pwm_value);
      motorB.forward(pwm_value);
      motorC.forward(pwm_value);
      motorD.forward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  for(int pwm_value=50; pwm_value<256; pwm_value++){
      motorA.backward(pwm_value);
      motorB.backward(pwm_value);
      motorC.backward(pwm_value);
      motorD.backward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  Serial.println();
  for(int pwm_value=255; pwm_value>50; pwm_value--){
      motorA.backward(pwm_value);
      motorB.backward(pwm_value);
      motorC.backward(pwm_value);
      motorD.backward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  Serial.println();
  motorA.reverseDirec();
  motorB.reverseDirec();
}
