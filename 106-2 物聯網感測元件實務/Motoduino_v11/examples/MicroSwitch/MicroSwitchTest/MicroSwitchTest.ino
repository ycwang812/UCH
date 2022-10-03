///////////////////////////////////////////////
// Description: Micro Switch Test 
// Author: Motoduino
// Date April 2016
/////////////////////////////////////////////


const int switchPin = 2;// the number of the switch pin
const int ledPin =  13; // the number of the LED pin

int switchState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);     
  // initialize the switch pin as an input:
  pinMode(switchPin, INPUT);    

}

void loop(){
  // read the state of the pushbutton value:
  switchState = digitalRead(switchPin);
   // check if the switch is pressed.
  // if it is, the buttonState is HIGH:
  if (switchState == HIGH) {    
    // turn LED on:   
    digitalWrite(ledPin, HIGH); 
  }
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}  
