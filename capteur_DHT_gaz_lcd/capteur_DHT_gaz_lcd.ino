#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>

#define DHT22_PIN 3
#define MQ135_PIN 0

dht DHT;

// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


void setup()
{
    Serial.begin(9600);
    lcd.begin(16,2);         // initialize the lcd for 16 chars 2 lines and turn on backlight
}



void loop() {
  //read DTH
  Serial.print("DHT22, \t");
  int chk = DHT.read22(DHT22_PIN);
  float fHum = 0;
  float fTemp = 0;
  if (chk == DHTLIB_OK)
  {
    fHum = DHT.humidity;
    fTemp = DHT.temperature;
    Serial.print("temp : ");
    Serial.println(fTemp,1);
    Serial.print("Hum : ");
    Serial.println(fHum,1);    
  }
  else
  {
    Serial.println("Erreur de lecture DTH22");
  }

  //read GAZ
  float fValGaz = analogRead(MQ135_PIN);
  Serial.print("gaz : ");
  Serial.println(fValGaz,1);

  //Print Value
  lcd.setCursor(0,0);  
  lcd.print("T: ");
  lcd.print(fTemp,1);
  lcd.print(" H: ");
  lcd.print(fHum,1);
  lcd.setCursor(0,1);
  lcd.print("air :");
  lcd.print(fValGaz,1);
  
  delay(5000);  
}
