#include <SoftwareSerial.h>

//Create software serial object to communicate with A6
SoftwareSerial mySerial(3, 2); //A6 Tx & Rx is connected to Arduino #3 & #2

String incomingData;   // for storing incoming serial data
String message = " ";   // A String for storing the message

void setup()
{
  Serial.begin(115200); // baudrate for serial monitor

  Serial.print("AT+CMGF=1\r"); // set SMS mode to text mode
  delay(100);
  Serial.print("AT+CNMI=2,2,0,0,0\r");  // set gsm module to tp show the output on serial out
  delay(100);
  

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
  receive_message();
   
  if(incomingData.indexOf("Led_on")>=0)   // if received command is to turn on relay
{
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
}
  else 
{
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(5000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(5000);
}
  
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}


void receive_message()
{
  if (Serial.available() > 0)
  {
    incomingData = Serial.readString(); // Get the data from the serial port.
    Serial.print(incomingData); 
    delay(10); 
  }
}

void send_message(String message)
{
  Serial.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);  
  Serial.println("AT+CMGS=\"+917020135545\""); // Replace it with your mobile number
  delay(100);
  Serial.println("WELCOME");   // The SMS text you want to send
  delay(100);
  Serial.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  Serial.println();
  delay(1000);  
}
