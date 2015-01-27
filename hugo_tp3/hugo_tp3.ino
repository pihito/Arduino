/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led_rouge = 7;
int led_verte = 8;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(A0, INPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led_rouge, HIGH);
  digitalWrite(led_verte, LOW);
  delay(1000);               // wait for a second
  digitalWrite(led_rouge, LOW);
  digitalWrite(led_verte, HIGH);  
  delay(1000);               // wait for a second
}
