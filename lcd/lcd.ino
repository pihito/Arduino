#include <LiquidCrystal_I2C.h>


#include <Wire.h> 

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

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
  lcd.print("Hello, world!");
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
