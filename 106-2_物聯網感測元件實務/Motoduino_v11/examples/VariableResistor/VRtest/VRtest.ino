///////////////////////////////////////////////
// Description: VR Test 
// Author: Motoduino
// Date April 2016
/////////////////////////////////////////////


const int analogInPin = A1; 
int sensorValue = 0;// value read from the pot
int outputValue = 0;// value output to the PWM (analog out)

void setup() {

 // initialize serial communications at 9600 bps:
  Serial.begin(9600);

}

void loop() {

  // read the analog in value:
  sensorValue = analogRead(analogInPin);           

  // map it to the range of the analog out:
  outputValue = map(sensorValue, 0, 1023, 0, 255); 
  // print the results to the serial monitor:

  Serial.print("sensor = " );                      
  Serial.print(sensorValue);     
  Serial.print("\t output = ");     
  Serial.println(outputValue);  

  delay(100);                    

}
