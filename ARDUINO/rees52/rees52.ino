#include <SoftwareSerial.h>

 

// Create software serial object to communicate with A6

SoftwareSerial mySerial(9, 10);      // A6 Tx & Rx is connected to Arduino #3 & #2

 

/* The setup() function is called when a sketch starts. It is used to initialize variables, pin modes, start using libraries, etc. This function will only run once, after each power up or reset of the Arduino board. */

 

void setup()

{

  // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)

  Serial.begin(9600);

 

  // Begin serial communication with Arduino and A6

  mySerial.begin(9600);

 

  Serial.println("Initializing...");    // Print the Message

  delay(1000);

 

  mySerial.println("AT"); // Once the handshake test is successful, it will back to OK

  

  mySerial.println("AT+CSQ"); // Signal quality test, value range is 0-31 , 31 is the best

  updateSerial();

  mySerial.println("AT+CCID"); // Read SIM information to confirm whether the SIM is plugged

  updateSerial();

  mySerial.println("AT+CREG?"); // Check whether it has registered in the network

  updateSerial();

  mySerial.println("ATI"); // GET the module and revision

  updateSerial();

  mySerial.println("AT+COPS?"); // check which network you are connectted to

  updateSerial();

  mySerial.println("AT+COPS=?"); // return the list of operators present in the network

  updateSerial();

}

 

/* The loop() function executes the program repeatedly until Specified. */

 

void loop()

{

  updateSerial();

}

 

void updateSerial()

{

  delay(500);

  while (Serial.available())

  {

    mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port

  }

  while(mySerial.available())

  {

    Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port

  }

}
