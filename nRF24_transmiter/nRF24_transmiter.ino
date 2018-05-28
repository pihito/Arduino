/*******************************************************************
 Chaque seconde, un nombre est émis par une carte Arduino munie
 d'un module nRF24L01.
 Ce message peut être capté par un autre Arduino, ou par un Raspberry Pi.
 http://electroniqueamateur.blogspot.ca/2017/02/communication-par-nrf24l01-entre-deux.html
********************************************************************/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int compteur = 0;

RF24 radio(7, 8);

uint8_t addresses[][6]={"Node1","Node2"};

const int taille = 32;

char message[taille + 1];



void setup(void)
{
  Serial.begin(115200);

  Serial.println("Emetteur de donnees");

   Serial.println("Recepteur RF24");
  if(!radio.begin())
    Serial.println("failed to intialise");
  else
    Serial.println("initialisé");

  radio.setCRCLength(RF24_CRC_16);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(10);
  radio.setPALevel(RF24_PA_MAX);

  radio.openWritingPipe(addresses[1]);
  radio.setPayloadSize(sizeof(int));
  
  //Serial.print("nrf available test: "); Serial.println(radio.available());
  //radio.printDetails ();
}

void loop(void)
{
  
  compteur++;

  itoa(compteur, message, 10);

  Serial.print("J'envoie maintenant ");
  Serial.println(compteur);

  radio.write( &compteur, sizeof(taille) );

  delay(1000);

}

