#include <SoftwareSerial.h>

/* CREATE SOFTWARE SERIAL OBJECT TO COMMUNICATE WITH SIM800L */
SoftwareSerial mySerial(3, 2); /* SIM800L TX & RX IS CONNECTED TO ARDUINO PIN #3 & #2 */

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
  
  mySerial.println("AT+CNMI=1,2,0,0,0"); /* DECIDES HOW NEWLY ARRIVED SMS MESSAGES SHOULD BE HANDLED */ 
  updateSerial();
  
  /* SEND AS SMS*/  
  mySerial.println("AT+CMGS=\"+85587281632\""); /* CHANGE PHONE NUMBER TO RECIPIENT'S NUMBER */
  updateSerial();
  mySerial.print("hello boyloy 0007"); /* TEXT CONTENT */
  updateSerial();
  mySerial.write(26); /* SEND SMS (Ctrl+Z) */
  delay(5000); /* WAIT FOR THE SMS TO SEND BEFORE CHECKING FOR INCOMING MESSAGES */ 
}

void loop()
{
  updateSerial(); /* CONTINUOUSLY CHECK FOR ANY INCOMING MESSAGES */ 
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());/* FORWARD WHAT SERIAL RECEIVED TO SOFTWARE SERIAL PORT */
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());/* FORWARD WHAT SOFTWARE SERIAL RECEIVED TO SERIAL PORT */
  }
}
