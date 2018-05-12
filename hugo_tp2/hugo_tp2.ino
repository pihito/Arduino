//la fonction setup n'est exécutée que une fois au démarage de la board
void setup()
{
  //met la pin 10 en sortie  
  //pinMode permet de définr si la pin est en entrée ou en sortie
  pinMode(10, OUTPUT);

}

//la fonction loop est exécutée après la fonction setup, une fois quelle est finie
// elle recommence au début ( c'est une boucle, loop en anglais)
void loop() {
  //allume la led
  //met la pi 10 à 5V, le 5V est l'état haut (HIGH en anglais)
  //digitalWrite pemet de changer l'état d'une pin, il y a deux état haut (HIGH) et bas (LOW) 
  digitalWrite(10, HIGH);
  //delay met le programme en pause pour la durée passée en paramètre ici 1s (1000ms)
  delay(1000);
  //eteint la led
  //met la pin à l'état BAS
  digitalWrite(10, LOW);
  
  
  //exercice : La led verte doit clignoter 2 fois puis la led rouge et bleu clignote 3 fois puis la led orange clignote 1x puis ça recommence 
