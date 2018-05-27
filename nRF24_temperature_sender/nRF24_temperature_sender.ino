#include <Wire.h>
#include <SPI.h>
#include <dht.h> // for DHT module
#include "RF24.h" // for radio module



//declare dht module and data pin 
#define DHT22_PIN 3
dht DHT;

//declare pin of PIR module
#define PIR_PIN  2


/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 and name of device*/
RF24 radio(7,8);
byte address[6]="SCREEN";

//data structure to transmit must be the same on receiver
#define DATA_TEMP 0 
#define DATA_HUMIDITY 1
#define DATA_PIR 2
float data[] = {0,0,0};

void setup() {
  Serial.begin(9600);

  //start the radio module, and power to low due to the proximity of device during the test in production set to RF24_PA_MAX
  //open a pipe to recieve data and start listing
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address);

  pinMode(PIR_PIN, INPUT);
}

void loop() {
   //read DTH
  Serial.print("DHT22, \t");
  int chk = DHT.read22(DHT22_PIN);
  float fHum = 0;
  float fTemp = 0;
  data[DATA_PIR] = digitalRead(PIR_PIN); 
  if (chk == DHTLIB_OK)
  {
    data[DATA_HUMIDITY] = DHT.humidity;
    data[DATA_TEMP] = DHT.temperature;
    Serial.print("Pir : ");
    Serial.println(data[DATA_PIR]);
    Serial.print("temp : ");
    Serial.println(data[DATA_TEMP],1);
    Serial.print("Hum : ");
    Serial.println(data[DATA_HUMIDITY],1);    
    if (!radio.write( &data, sizeof(data) )){
       Serial.println(F("failed to transmit"));
     }
  }
  else
  {
    Serial.println("Erreur de lecture DTH22");
  }
  delay(5000); 
}
