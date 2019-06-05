#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // rx tx

String phone = "+917020135545";

void setup() {

  Serial.begin(115200); // to A6 module
  while (!Serial) {
    ; 
  }
  
  mySerial.begin(115200); // serial breakout with SoftwareSerial (for monitoring)
  
  Serial.println("AT+CMGF=1");    
  delay(200);
  Serial.println("AT+CMGS=\"" + phone + "\"\r");
  delay(200);
  Serial.print("test message from A6");
  Serial.println (char(26)); // ctrl-z

}

void loop(){

  if (Serial.available()) {
    mySerial.write(Serial.read());
  }

  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }

}
