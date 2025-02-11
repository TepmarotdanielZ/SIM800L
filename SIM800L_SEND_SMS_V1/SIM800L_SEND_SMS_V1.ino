/* SMS */

#include <SoftwareSerial.h>

#define SIM800_TX 3  /* CONNECT TO SIM800L RX */ 
#define SIM800_RX 2  /* CONNECT TO SIM800L TX */ 

SoftwareSerial sim800(SIM800_TX, SIM800_RX);

void setup() {
    Serial.begin(9600);
    sim800.begin(9600);  /* SIM800L BAUD RATE */ 

    Serial.println("Initializing SIM800L...");
    delay(1000);

    /* CHECK IF SIM800L IS RESPONDING */ 
    sim800.println("AT");
    delay(1000);
    if (sim800.available()) {
        Serial.println("SIM800L Ready!");
    } else {
        Serial.println("SIM800L Not Responding...");
        return;
    }

    sendSMS("+85587281632", "hello 00077"); /* CHANGE TO RECIPIENT NUMBER */
}

void loop() {
    /* NOTHING IN LOOP */ 
}

void sendSMS(String number, String message) {
    Serial.println("Sending SMS...");

    sim800.println("AT+CMGF=1");  /* SET SMS TO TEXT MODE */ 
    delay(1000);

    sim800.print("AT+CMGS=\"");
    sim800.print(number);
    sim800.println("\"");
    delay(1000);

    sim800.print(message);
    delay(1000);

    sim800.write(0x1A);  /* SEND CTRL+Z TO SEND THE MESSAGE */ 
    delay(5000);

    Serial.println("Message Sent!");
}

