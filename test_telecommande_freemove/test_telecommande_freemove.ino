#define BT0 2
#define BT1 3
#define BT2 4

#include <SPI.h>                      //the communication interface with the modem
#include "RF24.h"                     //the library which helps us to control the radio modem

int msg[1];

RF24 radio(9,10);   

const uint64_t pipe = 0xE8E8F0F0E1LL; //the address of the modem, that will receive data from Arduino.


int bt[3] = {0,0,0};


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
}


void loop() {
  bt[0]  = digitalRead(BT0);
  bt[1]  = digitalRead(BT1);
  bt[2]  = digitalRead(BT2);

  for(int i=0;i<=2;i++) {
    if(bt[i] == LOW)
    Serial.print(i);
    Serial.print(":");
    msg[0] = 1; 
    radio.write(msg, 1);
  }
  Serial.print("\n--------------------------\n");
}

/*
void loop() {
  int lecture = 0;
  for(int i=0;i<=5;i++) {
    lecture = analogRead(i);
    Serial.print(i);
    Serial.print(":");
    Serial.print(lecture);
    Serial.print(" ");
    if(i==5) { Serial.print("--------------------------\n");
  }
 }
 
  
}
*/
