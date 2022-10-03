///////////////////////////////////////////////
// Description: Tilt Test (傾斜開關測試)
// Author: Motoduino
// Date: April 2016
/////////////////////////////////////////////

const int tiltPin = 2;     // the number of the tilt pin
const int ledPin =  13;      // the number of the LED pin 

int tiltState = 0;         // variable for reading the tilt status

void setup() {

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);     
  // initialize the tilt pin as an input:
  pinMode(tiltPin, INPUT);    

}

void loop(){
  // read the state of the tiltPin value:
  tiltState = digitalRead(tiltPin);

  if (tiltState == HIGH) {    
    // turn LED on:   
    digitalWrite(ledPin, HIGH); 
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

}    
