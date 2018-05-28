#include <Nextion.h>

NexButton b0 = NexButton(0, 3, "b0");  // Button added

NexTouch *nex_listen_list[] = {
  &b0,
  NULL  // String terminated
};

void b0PushCallback(void *ptr)  // Press event for button b1
{
  digitalWrite(8, HIGH);  // Turn ON internal LED
}  // End of press event

void b0PopCallback(void *ptr)  // Release event for button b1
{
  digitalWrite(8, LOW);  // Turn OFF internal LED
}  // End of release event



int valeur = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  nexInit();
  delay(500);  // This dalay is just in case the nextion display didn't start yet, to be sure it will receive the following command.
  /*Serial1.print("baud=115200");  // Set new baud rate of nextion to 115200, but it's temporal. Next time nextion is power on,
                                // it will retore to default baud of 9600.
                                // To take effect, make sure to reboot the arduino (reseting arduino is not enough).
                                // If you want to change the default baud, send the command as "bauds=115200", instead of "baud=115200".
                                // If you change the default baud, everytime the nextion is power ON is going to have that baud rate, and
                                // would not be necessery to set the baud on the setup anymore.
  Serial1.write(0xff);  // We always have to send this three lines after each command sent to nextion.
  Serial1.write(0xff);
  Serial1.write(0xff);

  Serial1.end();  // End the serial comunication of baud=9600

  Serial1.begin(115200);  // Start serial comunication at baud=115200
*/
  b0.attachPush(b0PushCallback);  // Button press
  b0.attachPop(b0PopCallback);  // Button release

  pinMode(8, OUTPUT); 
  /*
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  delay(1000);
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  delay(1000);
  */
}

void loop() {
  valeur ++; 
  if (valeur==500){
    valeur = 0;
  }

  Serial.print("n0.val=");
  Serial.print(valeur);
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);

  nexLoop(nex_listen_list);  // Check for any touch event
}
