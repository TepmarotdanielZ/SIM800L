#include <SoftwareSerial.h>

/* CREATE SOFTWARE SERIAL OBJECT TO COMMUNICATE WITH SIM800L */
SoftwareSerial mySerial(3, 2); /* SIM800L TX & RX IS CONNECTED TO ARDUINO #3 & #2 */

void setup()
{
  /* BEGIN SERIAL COMMUNICATION WITH ARDUINO AND ARDUINO IDE (SERIAL MONITOR) */
  Serial.begin(9600);
  
  /* BEGIN SERIAL COMMUNICATION WITH ARDUINO AND SIM800L */
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); /* ONCE THE HANDSHAKE TEST IS SUCCESSFUL, IT WILL BACK TO OK */
  updateSerial();

  mySerial.println("AT+CMGF=1"); /* CONFIGURING TEXT MODE */ 
  updateSerial();

  mySerial.println("AT+CMGS=\"+85587281632\""); /* CHANGE ZZ WITH COUNTRY CODE AND +ZZXXXXXXXXXXX WITH PHONE NUMBER TO SMS */

  updateSerial();
  mySerial.print("LOVE YOU BOYLOY"); /* TEXT CONTENT */
  updateSerial();
  mySerial.write(26);
}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read()); /* FORWARD WHAT SERIAL RECEIVED TO SOFTWARE SERIAL PORT */
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read()); /* FORWARD WHAT SOFTWARE SERIAL RECEIVED TO SERIAL PORT */
  }
}
