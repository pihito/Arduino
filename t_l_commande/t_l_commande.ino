void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);      
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean a=digitalRead(2);// et on l’affecte à la variable "a"
    Serial.println(a);
}
