/*
  S4A sensor board testing sketch
  Input components: Light sensor, microphone, VR slide, Button
  Output components: Red Led, Green Led, Buzzer(speaker)
  
  Author: http://motoduino.com
  Description: S4A sensor board is suitable for arduino. 
 */

// INPUT PIN
const int VR_InPin = A0;  // Analog input pin that the potentiometer is attached to
const int CDS_InPin = A1;  // Analog input pin that Light Sensor is attached to
const int MIC_InPin = A2;  // Analog input pin that the microphone is attached to
const int Button_InPin = 2;  // Analog input pin that the microphone is attached to

// OUTPUT PIN
const int Ledred_OutPin = 5; // Analog output pin that the RED LED is attached to
const int Ledgreen_OutPin = 6; // Analog output pin that the GREEN LED is attached to
const int Ledblue_OutPin = 9; // Analog output pin that the BLUE LED is attached to

const int Led1_OutPin = 10; // Analog output pin that the RED LED is attached to
const int Led2_OutPin = 11; // Analog output pin that the GREEN LED is attached to
const int Led3_OutPin = 12; // Analog output pin that the BLUE LED is attached to

const int Buzzer_OutPin = 9; // Analog output pin that the Buzzer is attached to

int MIC_Value = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int VR_Value = 0;
int CDS_Value = 0;
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
char val;  // variable to receive data from the serial port(bluetooth)


void setup() {
  // initialize serial communications at 57600 bps:
  Serial.begin(57600); 

  pinMode(Ledred_OutPin, OUTPUT);      
  pinMode(Ledgreen_OutPin, OUTPUT); 
  pinMode(Ledblue_OutPin, OUTPUT);      

  pinMode(Led1_OutPin, OUTPUT); 
  pinMode(Led2_OutPin, OUTPUT); 
  pinMode(Led3_OutPin, OUTPUT); 

  pinMode(Buzzer_OutPin, OUTPUT); 
 
  // initialize the pushbutton pin as an input:
  pinMode(VR_InPin, INPUT);     
  pinMode(CDS_InPin, INPUT);     
  pinMode(MIC_InPin, INPUT);     
  pinMode(Button_InPin, INPUT);     

  
}

void loop() {
  int i;
  buttonState = digitalRead(Button_InPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    

    for ( i=0; i<10; i++ ) {
        tone(Buzzer_OutPin,1000, 50);
        analogWrite(Ledgreen_OutPin, 255);
        analogWrite(Ledred_OutPin, 0);
        digitalWrite(Led2_OutPin, HIGH);        
        delay(50);
        tone(Buzzer_OutPin,500, 50);
        analogWrite(Ledgreen_OutPin, 0);
        analogWrite(Ledred_OutPin, 0);
        digitalWrite(Led2_OutPin, LOW);        
        delay(50);
    }
    noTone(Buzzer_OutPin);

        for ( i=0; i<10; i++ ) {
        tone(Buzzer_OutPin,1000, 50);
        analogWrite(Ledgreen_OutPin, 0);
        analogWrite(Ledred_OutPin, 0);
        digitalWrite(Led2_OutPin, HIGH);        
        delay(50);
        tone(Buzzer_OutPin,500, 50);
        analogWrite(Ledgreen_OutPin, 0);
        analogWrite(Ledred_OutPin, 0);
        digitalWrite(Led2_OutPin, LOW);        
        delay(50);
    }
    noTone(Buzzer_OutPin);

  } 

  // Test VR 
  // read the analog in value:
  VR_Value = analogRead(VR_InPin); 
         
      // map it to the range of the analog out:
      outputValue = map(VR_Value, 0, 1023, 0, 255);  
      // change the analog out value:
      analogWrite(Ledred_OutPin, outputValue); 

      // Light sensor testing 
      // read the analog in value
      CDS_Value = analogRead(CDS_InPin);
      outputValue = map(CDS_Value, 0, 1023, 0, 255);  
       analogWrite(Led1_OutPin, outputValue);
   
      // microphone sensor testing 
      // read the analog in value:
      MIC_Value = analogRead(MIC_InPin);            
      // map it to the range of the analog out:
        outputValue = map(MIC_Value, 0, 1023, 0, 255);  
        // change the analog out value:
        analogWrite(Led3_OutPin, outputValue); 

  delay(10);                     
}
