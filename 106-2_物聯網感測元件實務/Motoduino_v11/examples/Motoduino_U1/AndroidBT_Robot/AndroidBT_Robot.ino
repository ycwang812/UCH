/*
  Motoduino : Arduino with motors driver
  
   author: http://motoduino.com - Feb. 2016
*/
const int Motor_E1 = 5;  // Speed Control pin 5 of Arduino (PWM)  
const int Motor_E2 = 6; // Speed Control pin 6 of Arduino (PWM)    
const int Motor_M1 = 10;    // Direction Control pin 10 of Arduino
const int Motor_M2 = 11;     // Direction Control pin 11 of Arduino
char val;  // variable to receive data from the serial port(bluetooth)

void setup()  
{
  // Start serial communication at 57600
  Serial.begin(57600); 
  pinMode(Motor_E1, OUTPUT);
  pinMode(Motor_E2, OUTPUT);
  pinMode(Motor_M1, OUTPUT);
  pinMode(Motor_M2, OUTPUT);
  
}

void loop()
{
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
    }    
    
  }

}

void motorstop(byte flag, byte motorspeed)
{
  Serial.println("Stop!");
  digitalWrite( Motor_E1, motorspeed);
  digitalWrite( Motor_E2, motorspeed);

}

void forward(byte flag, byte motorspeed)
{
  Serial.println("Forward!");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
  
}

void backward(byte flag, byte motorspeed)
{
  Serial.println("Backward!");

  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, motorspeed);
   
}

void left(byte flag, byte motorspeed)
{
  Serial.println("Turn Right! ");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, motorspeed);
  analogWrite( Motor_E2, 0);
  
}

void right(byte flag, byte motorspeed)
{
  Serial.println("Turn Left!");

  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);

  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, motorspeed);
  
}

