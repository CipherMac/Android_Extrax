const int lm35_pin = A1;
const int Cell1_pin = A2;
const int Cell2_pin = A3;
const int Cell3_pin = A4;
const int inputCurrent = A5;
const int outputCurrent = A6;

String str;

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);pinMode(9,OUTPUT);pinMode(10,OUTPUT);pinMode(11,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,LOW);digitalWrite(9,LOW);digitalWrite(10,LOW);digitalWrite(11,LOW);
}

void loop() {
  int cell1_adc_val;
  float cell1_voltage;
  cell1_adc_val = analogRead (Cell1_pin);
  cell1_voltage = cell1_adc_val * (3.0 / 1023.0);
  Serial.println("cell1 voltage : ");
  Serial.print(cell1_voltage);
  Serial.println();
  //Serial1.println(cell1_voltage);                     //Cell 1
  delay(100);
  int cell2_adc_val;
  float cell2_voltage;
  cell2_adc_val = analogRead (Cell2_pin);
  cell2_voltage = cell2_adc_val * (3.0 / 1023.0);
   cell2_voltage = cell2_voltage - cell1_voltage; 
  Serial.println("cell2 voltage : ");
  Serial.print( cell2_voltage);
  //Serial.println();
  //Serial1.println( cell2_voltage);                    //Cell 2
  delay (500);
   int cell3_adc_val;
  float cell3_voltage;
  cell3_adc_val = analogRead (Cell2_pin);
  cell3_voltage = cell3_adc_val * (3.0 / 1023.0);
   cell3_voltage = cell3_voltage - cell2_voltage; 
  Serial.println("cell3 voltage : ");
  Serial.print( cell3_voltage);                         // cell 3
  Serial.println();
  //Serial1.println( cell3_voltage);
  delay(100);
  int temp_adc_val;
  float temp_val;
  temp_adc_val = analogRead(lm35_pin);
  temp_val = (temp_adc_val * 4.88);
  temp_val = (temp_val/10);
  Serial.println(temp_val);                            //TEMP
  //Serial1.println(temp_val);
  delay(500);
  float inputCurrent_adc_value;
  float inputCurrent_value;
  inputCurrent_adc_value = analogRead (inputCurrent);
  inputCurrent_value = (inputCurrent_adc_value/1024)*5000;
  Serial.println(inputCurrent_value);
  //Serial1.println(inputCurrent_value);                      //INPUT CURRENT
  delay(500);
  float outputCurrent_adc_value;
  float outputCurrent_value;
  outputCurrent_adc_value = analogRead (outputCurrent);
  outputCurrent_value = (outputCurrent_adc_value/1024)*5000;
  Serial.println(outputCurrent_value);
  //Serial1.println(outputCurrent_value);                     //OUTPUT CURRENT
  delay(500);

str=String(cell1_voltage)+String(cell2_voltage)+String(cell3_voltage)+String(temp_val)+String(inputCurrent_value)+String(outputCurrent_value);

  Serial1.println(str);
  delay(5000);
  
}
