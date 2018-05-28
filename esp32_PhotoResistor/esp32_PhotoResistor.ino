#include <Arduino.h>

int LDR_Pin = 36; // what pin on the arduino is the LDR output connected to
int photocellReading = 0;

void setup(){
    Serial.begin(115200);
    Serial.println("LDR Light Sensor Example Sketch | cactus.io");
    pinMode(OUTPUT,LDR_Pin);
}

void loop(){
  photocellReading = analogRead(LDR_Pin);
  
  Serial.println(photocellReading);
  delay(1000);
}
