///////////////////////////////////////////////
// Description: Reed Switch Test 
// Author: Motoduino
// Date April 2016
/////////////////////////////////////////////

const int switchPin = 2;     // Reed switch to digital pin 3
const int ledPin = 11;       // the pin that the LED is attached to D11

void setup() {

  pinMode(switchPin, INPUT);        // switchPin is an input
  Serial.begin(9600);

}

void loop() { 

    int pgmState = digitalRead(switchPin);

    if (pgmState == HIGH) {
          digitalWrite(ledPin, HIGH);
       }
    else {
          digitalWrite(ledPin, LOW);
       }
  delay(1000);

}  
