#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(7, 8);

uint8_t addresses[][6]={"Node1","Node2"};

const int taille = 32;

char message[taille + 1]; 




void setup(void)
{

  Serial.begin(115200);

  Serial.println("Recepteur RF24");
  if(!radio.begin())
    Serial.println("failed to intialise");
  else
    Serial.println("initialisé");

  radio.setCRCLength(RF24_CRC_16);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(10);
  radio.setPALevel(RF24_PA_MAX);

  radio.openReadingPipe(1,addresses[1]);       
  radio.setPayloadSize( sizeof(int));
  Serial.println("pipe open");

  radio.setAutoAck(false);
  Serial.println("start listning");
  Serial.println("end setup");
}

void loop(void)
{
  radio.startListening();
  //Serial.print(":");
  while ( radio.available() )
  {
    int result= 255;
    
    Serial.println("\nreception");
    radio.read( &result, sizeof(int));

    Serial.print("Message recu : ");

    Serial.println(result);
  }
  delay(500);
}


