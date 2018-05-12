#include <Wire.h> 
#include <LiquidCrystal_I2C.h>




// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address

void setup()   
{
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
  lcd.print("love lolo");
}

void loop() 
{
    
   for (int positionCounter = 0; positionCounter < 10; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(200);
  }


}
