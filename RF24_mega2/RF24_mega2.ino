/*Serveur_11_Avril.ino 
      
Broches utilisees pour le MEGA 2560 
      * MISO -> 50, * MOSI -> 51 * SCK -> 52 
      * CE -> 48 * CSN -> 49 
      * GND -> GND * VCC -> 3 Volts du regulateur 
Broches utilisees pour le UNO 
      * MISO -> 12 * MOSI -> 11 * SCK -> 13 
      * CE -> 8 * CSN -> 7 
      * GND -> GND * VCC -> 3.3v de la carte UNO 
*/ 

#include <SPI.h> 
#include <Mirf.h> 
#include <nRF24L01.h> 
#include <MirfHardwareSpiDriver.h> 

byte zone_recep[20]; 
byte zone_renvoi[20]="Bonsoir"; 
byte i; 
      

void setup(){ 
     Serial.begin(9600); 

     Mirf.cePin = 48; // 8 pour UNO 
     Mirf.csnPin = 49; // 7 pour UNO 
     Mirf.spi = &MirfHardwareSpi; 
     Mirf.init(); 

     // canal et payload doivent etre identiques aux 2 modules 
     Mirf.channel = 12; 
     Mirf.payload = 7 ; 
     Mirf.setRADDR((byte *)"serv1"); // Reception = notre propre adresse 
     Mirf.setTADDR((byte *)"clie1"); // Transmission = adresse du destinataire 
     Mirf.config(); 
     Serial.println("Programme Serveur seance du 14 Juin."); 
     Serial.println("Init Ok..."); 
} 

void loop(){ 
     //Si un message a ete recu et aucun message n'est en cours d'emission, 
     if( Mirf.dataReady() && !Mirf.isSending() ){ 
            Mirf.getData(zone_recep); // on recupere le message 
      
            Serial.print("On a recu : "); 
            for (i=0 ; i < Mirf.payload ; i++) { 
                  Serial.write(zone_recep[i]); // write affiche le caractere 
            } 
      Serial.println(" "); 
      
      Serial.print("On renvoie : "); 
      for ( i=0 ; i < Mirf.payload ; i++) { 
            Serial.write(zone_renvoi[i]); 
      } 
      Serial.println(" apres 3 secondes."); 
      delay(3000); 
      Mirf.send(zone_renvoi); // On envoie notre reponse 

      // On boucle tant que le message n'a pas ete envoye 
      while(Mirf.isSending()){ 
            delay(10); 
      } 

      // info pour l'écran (plus tard envisager lcd) 
      Serial.println("Renvoi OK."); 
      Serial.println("-----------------------------------"); 
      Serial.println(); 
     } 
} 
     
