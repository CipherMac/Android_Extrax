#include <LiquidCrystal.h>
#include <SoftwareSerial.h> // Library for using serial communication
SoftwareSerial SIM900AA(0,1); // Pins 10, 11 are used as used as software serial pins

String incomingData;   // for storing incoming serial data
String message = "";   // A String for storing the message
int relay_pin = 5;    // Initialized a pin for relay module for LED
int relay_pin1 = 4;    // Initialized a pin for relay module for LM35
float tempc;
float tempf;
float vout;

void setup()
{
  Serial.begin(115200); // baudrate for serial monitor
  SIM900A.begin(19200); // baudrate for GSM shield

  pinMode(relay_pin, OUTPUT);   // Setting erlay pin as output pin
  digitalWrite(relay_pin, HIGH);  // Making relay pin initailly low for LED 
  digitalWrite(relay_pin1, HIGH);  // Making relay pin initailly low for LM35

  // set SMS mode to text mode
  SIM900A.print("AT+CMGF=1\r");  
  delay(100);
  
  // set gsm module to tp show the output on serial out
  SIM900A.print("AT+CNMI=2,2,0,0,0\r"); 
  delay(100);

  
}

void loop()
{
  //Function for receiving sms
  receive_message();
  

  // if received command is to turn on relay
  if(incomingData.indexOf("on")>=0)
  {
    digitalWrite(relay_pin, LOW);
    message = "Led is turned ON";
    // Send a sms back to confirm that the relay is turned on
    send_message(message);
  }
  
  // if received command is to turn off relay
  if(incomingData.indexOf("off")>=0)
  {
    digitalWrite(relay_pin, HIGH);
    message = "Led is turned OFF";
    // Send a sms back to confirm that the relay is turned off
    send_message(message);
  }
}

void receive_message()
{
  if (SIM900A.available() > 0)
  {
    incomingData = SIM900A.readString(); // Get the data from the serial port.
    Serial.print(incomingData); 
    delay(10); 
  }
}

void send_message(String message)
{
  SIM900A.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(100);  
  SIM900A.println("AT+CMGS=\"+918550901610\""); // Replace it with your mobile number
  delay(100);
  SIM900A.println(message);   // The SMS text you want to send
  delay(100);
  SIM900A.println((char)26);  // ASCII code of CTRL+Z
  delay(100);
  SIM900A.println();
  delay(1000);  
}
