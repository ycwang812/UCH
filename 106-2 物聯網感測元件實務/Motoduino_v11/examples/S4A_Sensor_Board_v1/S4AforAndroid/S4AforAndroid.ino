/*
  Arduino Interactive Shield (AIS)/S4A sensor board testing sketch
  Input components: Light sensor, microphone, VR slide, Button
  Output components: Red Led, Green Led, Buzzer(speaker)
  
  Author: http://motoduino.com
  Description: S4A sensor board is suitable for arduino. 
 */
 
const int Motor_E1 = 5; // digital pin 5 of Arduino (PWM)    
const int Motor_E2 = 6;  // digital pin 6 of Arduino (PWM)  
const int Motor_M1 = 7;     // digital pin 7 of Arduino
const int Motor_M2 = 8;    // digital pin 8 of Arduino
 

// INPUT PIN
const int VR_InPin = A0;  // Analog input pin that the potentiometer is attached to
const int CDS_InPin = A1;  // Analog input pin that Light Sensor is attached
const int MIC_InPin = A2;  // Analog input pin that the microphone is attached
const int Button_InPin = 2;  // Digitalg input pin 

// OUTPUT PIN
const int Ledred_OutPin = 10; // Analog output pin that the RED LED is attached
const int Ledgreen_OutPin = 11; // Analog output pin that the GREEN LED is attached
const int Buzzer_OutPin = 9; // Analog output pin that the Buzzer is attached

const int OutputPin3 = 3;  // reserve
const int OutputPin4 = 4;  // reserve
const int OutputPin12 = 12;  // reserve

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
char val;  // variable to receive data from the serial port(bluetooth)

int mSwitch1_Status;
int mSwitch2_Status;
int mSwitch3_Status;
int mSwitch4_Status;
int mSwitch5_Status;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(Buzzer_OutPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(Buzzer_OutPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void switch1()
{
  if(mSwitch1_Status == 0)
  {
    digitalWrite(Ledgreen_OutPin, HIGH);
    mSwitch1_Status = 1;
  }
  else
  {
    digitalWrite(Ledgreen_OutPin, LOW);
    mSwitch1_Status = 0;
  }
}

void switch2()
{
    // Buzzer testing
      for (int i = 0; i < length; i++) {
      if (notes[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(notes[i], beats[i] * tempo);
      }
      
      // pause between notes
      delay(tempo / 2); 
    }
}

void switch3()
{
  Serial.println("switch3!");

  if(mSwitch3_Status == 0)
  {
    digitalWrite(OutputPin4, HIGH);
    mSwitch3_Status = 1;
  }
  else
  {
    digitalWrite(OutputPin4, LOW);
    mSwitch3_Status = 0;
  }

}

void switch4()
{
  Serial.println("switch4!");

  if(mSwitch4_Status == 0)
  {
    digitalWrite(OutputPin12, HIGH);
    mSwitch4_Status = 1;
  }
  else
  {
    digitalWrite(OutputPin12, LOW);
    mSwitch4_Status = 0;
  }

}

void switch5()
{
  Serial.println("switch5!");

  if(mSwitch5_Status == 0)
  {
    digitalWrite(OutputPin3, HIGH);
    mSwitch5_Status = 1;
  }
  else
  {
    digitalWrite(OutputPin3, LOW);
    mSwitch5_Status = 0;
  }

}

void motorstop(byte flag, byte motorspeed)
{
//  Serial.println("Stop!");
  digitalWrite( Motor_E1, motorspeed);
  digitalWrite( Motor_E2, motorspeed);

}

void forward(byte flag, byte motorspeed)
{
//  Serial.println("Forward!");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
  
}

void backward(byte flag, byte motorspeed)
{
//  Serial.println("Backward!");

  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
   
}

void right(byte flag, byte motorspeed)
{
//  Serial.println("Turn Right! ");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, 0);
  
}

void left(byte flag, byte motorspeed)
{
//  Serial.println("Turn Left!");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, motorspeed);
  
}

void setup() {
  // initialize serial communications at 57600 bps:
  Serial.begin(57600); 
  
  pinMode(Motor_M1, OUTPUT);
  pinMode(Motor_M2, OUTPUT);
  
  pinMode(Ledred_OutPin, OUTPUT);      
  pinMode(Ledgreen_OutPin, OUTPUT); 
  pinMode(Buzzer_OutPin, OUTPUT); 
 
  pinMode(OutputPin3, OUTPUT);
  pinMode(OutputPin4, OUTPUT);
  pinMode(OutputPin12, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(VR_InPin, INPUT);     
  pinMode(CDS_InPin, INPUT);     
  pinMode(MIC_InPin, INPUT);     
  pinMode(Button_InPin, INPUT);     
 
  mSwitch1_Status = 0;
  mSwitch2_Status = 0;
  mSwitch3_Status = 0;
  mSwitch4_Status = 0;
  mSwitch5_Status = 0;
  
}

void loop() {
  
    if(Serial.available())
  {
    val = Serial.read();
    switch(val)
    {
      case 'f':   // car forward
                forward(0, 255);
                break;
      case 'b':   // car backward
                backward(0, 255);
                break;
      case 'l':   // car turn left
                left(0, 255);
                break;
      case 'r':   // car turn right
                right(0, 255);
                break;
      case 's':   // car stop
                motorstop(0, 0);
                break;
      case '1':  //Switch_1 : ON/OFF
                switch1();
                break;
      case '2':  // Switch_2 : ON/OFF
                switch2();
                break;      
      case '3':  // Switch_3 : ON/OFF
                switch3();
                break;      
      case '4':  // Switch_4 : ON/OFF
                switch4();
                break;      
      case '5':  // Switch_5 : ON/OFF
                switch5();
                break;      
      default:
                break;
    }    
    
  }

    // Test button 
  buttonState = digitalRead(Button_InPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH)     
    // turn LED on:    
    digitalWrite(Ledred_OutPin, HIGH);  
   else
    digitalWrite(Ledred_OutPin, LOW); 
   

  // Test VR 
  // read the analog in value:
  sensorValue = analogRead(VR_InPin);
  if(sensorValue != 0)
  {  
    // map it to the range of the analog out:
    outputValue = map(sensorValue, 0, 1023, 0, 255);  
    // change the analog out value:
    Serial.print("T");   // Send data to android mobile through bluetooth.
    Serial.print(outputValue);  // Send data to android mobile through bluetooth.
    Serial.print("#");  // End of data     // Send data to android mobile through bluetooth.
  }

  // wait 100 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);                     
}
