/* 
                  Client.ino 

Broches utilisees pour le MEGA 2560 
      * MISO -> 50,         * MOSI -> 51       * SCK -> 52 
      * CE -> 48             * CSN -> 49 
      * GND -> GND        * VCC -> 3 Volts du regulateur 
Broches utilisees pour le UNO 
      * MISO -> 12,         * MOSI -> 11       * SCK -> 13 
      * CE -> 8               * CSN -> 7 
      * GND -> GND        * VCC -> 3.3v de la carte UNO 
*/ 


// *--------------------------------* 
// Inclure les librairies 
// *--------------------------------* 
#include <SPI.h> // Pour la gestion du port SPI 
#include <Mirf.h> // Pour la gestion de la communication 
#include <nRF24L01.h> // Pour les definitions des registres du nRF24L01 
#include <MirfHardwareSpiDriver.h> // Pour la communication SPI hardware 
// (revient a  utiliser SPI.h mais avec une surcouche en plus) 
byte message_aller[20] = "Bonjour"; 
byte message_retour[20]; 
byte i ; 
boolean echec ; 
unsigned long debut, seconde, finQuinze, oldSec; 

void setup(){ 
      Serial.begin(9600); // initialisation du port serie 

      // -------------------------------------- 
      // Configuration des broches CSN et CE : 
      Mirf.cePin = 48 ; // 8 pour UNO 
      Mirf.csnPin = 49 ; // 7 pour UNO 
      // configuration du SPI : utiliser le port SPI hardware 
      Mirf.spi = &MirfHardwareSpi; 
      Mirf.init(); // initialisation du module 

      // --------------------------------------------------- 
      // canal et longueur utile doivent Ãªtre identiques 
      // pour le client et le serveur 
      Mirf.channel = 12; 
      Mirf.payload = 7; // taille utile de la donnee transmise 
      // ------------------------------------------------------- 
      // Configuration des adresses de reception et d'emission 
      Mirf.setRADDR((byte *)"clie1"); // adresse de reception du module (de 5 octets) 
      Mirf.setTADDR((byte *)"serv1"); // adresse vers laquelle on transmet (de 5 octets) 
      Mirf.config(); // ecriture de la configuration 

      Serial.println("Programme Client seance du 14 Juin."); 
      Serial.println("init OK"); 
      finQuinze = 0 ; 
} 

void loop(){ 
      // Envoi du message toutes les 15 secondes 
      if ( millis() > finQuinze ) { 
            envoiBonjour(); 
      } 
      // -------------------------------- 
      // Si on recoit un message 
      if (Mirf.dataReady()) { 
            echec = false ; 
            Mirf.getData((byte *) &message_retour); 
            Serial.println(" "); 
            Serial.print("Retour apres "); 
            Serial.print(millis() - debut); 
            Serial.println(" ms"); 
            Serial.print("On a recu : "); 
            for ( i = 0 ; i < Mirf.payload ; i++) { 
                  Serial.write(message_retour[i]); 
            } 
            Serial.println(); 
            Serial.println("-----------------------------------"); 
      }             // sortie de if DataReady 
      else { 
            // on va afficher le comptage des secondes 
            seconde = int (( millis() - debut )) / 1000 ; 
            if (seconde > oldSec) { 
                  Serial.print ( seconde) ; 
                  Serial.print ( " " ) ; 
                  oldSec = seconde ; 
            }       //       sortie du if 
      }             //       sortie du else 
}                   //       sortie de la loop 


void envoiBonjour(void) { 
      Serial.println(" "); 
      if (echec){ 
            Serial.println("------- Time out ------- "); 
      } 
      Serial.println(); 
      Serial.println("Debut envoi"); 
      // ---------------------------------- 
      Mirf.send((byte *)&message_aller); // valeur que l'on veut envoyer 
      while(Mirf.isSending()){ 
            // on attend que le message soit envoye 
      } 
      Serial.println("Envoi Ok"); 
      Serial.println("Attente retour ..."); 
      debut = millis() ; 
      finQuinze = debut + 15000 ; 
      oldSec = 0 ; 
      echec = true ; 
} 

