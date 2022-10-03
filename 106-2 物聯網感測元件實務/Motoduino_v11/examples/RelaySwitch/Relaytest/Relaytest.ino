///////////////////////////////////////////////
// Description: Relay Test 
// Author: Motoduino
// Date April 2016
/////////////////////////////////////////////


int Relay_Pin = 2;  // 繼電器模組 I/O 位置 D2

void setup() 
{               
   // initialize the digital pin as an output.
   pinMode(Relay_Pin, OUTPUT);    

}

void loop() {

   digitalWrite(Relay_Pin, HIGH);  
   delay(10000);              
   digitalWrite(Relay_Pin, LOW);   
   delay(10000);              

}
 
