///////////////////////////////////////////////
// Description: XY Joystick Test (XY搖桿測試)
// Author: Motoduino
// Date: April 2016
/////////////////////////////////////////////

const int analogInPin1 = A3;  // 搖桿接到 S4A Sensor Board A3/A4 孔位
const int analogInPin2 = A4;  // 搖桿接到 S4A Sensor Board A3/A4 孔位

const int analogOutPin1 = 10; // D10 LED is attached 
const int analogOutPin2 = 11; // D11 LED is attached 

int sensorValue1 = 0;        // X軸讀到數值
int outputValue1 = 0;        //  輸出到LED數值
int sensorValue2 = 0;        // Y軸讀到數值 
int outputValue2 = 0;        //  輸出到LED數值

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analog in value:
  sensorValue1 = analogRead(analogInPin1);            
  sensorValue2 = analogRead(analogInPin2);            

  // map it to the range of the analog out:
  outputValue1 = map(sensorValue1, 0, 1023, 0, 255);  
  outputValue2 = map(sensorValue2, 0, 1023, 0, 255);  

  // change the analog out value:
  analogWrite(analogOutPin1, outputValue1);           
  analogWrite(analogOutPin2, outputValue2);           

  // print the results to the serial monitor:
  Serial.print("X = " );                       
  Serial.print(sensorValue1);      
  Serial.print("   outputX = ");      
  Serial.println(outputValue1);   

  Serial.print("Y = " );                       
  Serial.print(sensorValue2);      
  Serial.print("   outputY = ");      
  Serial.println(outputValue2);   

  delay(500);                     
}
