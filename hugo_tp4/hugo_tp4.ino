/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led_rouge = 7;
int led_verte = 8;
int on;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(A0, INPUT);  
  Serial.begin(9600);
  on = 0;
}

// the loop routine runs over and over again forever:
void loop() {
  
  Serial.println(digitalRead(A0));
  if(digitalRead(A0) == 0) {
    if(on == 1) {
      digitalWrite(led_rouge, HIGH);
      digitalWrite(led_verte, LOW);
      on = 0;
    }
    else{
      digitalWrite(led_rouge, LOW);
      digitalWrite(led_verte, HIGH);  
      on = 1;
    }
    
  }
  else {
    digitalWrite(led_rouge, HIGH);
    digitalWrite(led_verte, LOW);  
  }
  delay(1000); 
  
}
