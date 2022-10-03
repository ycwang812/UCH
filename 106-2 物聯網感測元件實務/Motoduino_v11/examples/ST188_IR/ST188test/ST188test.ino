///////////////////////////////////////////////
// Description: ST188 IR Test 
// Author: Motoduino
// Date April 2016
/////////////////////////////////////////////


const int st188Pin = 2;     // the number of the st188 sensor pin
const int ledPin =  13;      // the number of the LED pin

int sensorState = 0;         // variable for reading the sensor status

void setup() {

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);     
  // initialize the st188 sensor pin as an input:
  pinMode(st188Pin, INPUT);    

}


void loop(){

  sensorState = digitalRead(st188Pin);

  if (sensorState == HIGH) {    
    // turn LED on:   
    digitalWrite(ledPin, HIGH); 
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

}
