
#include "Wire.h"
#include "motoTCS34725.h"
 
#define GREENPIN   9   
#define REDPIN     6
#define BLUEPIN    5

motoTCS34725 tcs = motoTCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);
 
void setup() {
 
  Serial.begin(9600);
  
 if (tcs.begin()) {
 Serial.println("Sensor ready!");
 } else {
  Serial.println("TCS34725 not found!");
 while (1); // Halt!
 } 

}
 
void loop() {
 
 uint16_t clearcol, red, green, blue;
 float average, r, g, b;
 delay(100); 
 tcs.getRawData(&red, &green, &blue, &clearcol);
 
 average = (red+green+blue)/3;

 r = red/average;
 g = green/average;
 b = blue/average;
 
 Serial.print("\tClear:"); Serial.print(clearcol);
 Serial.print("\tRed:"); Serial.print(r);
 Serial.print("\tGreen:"); Serial.print(g);
 Serial.print("\tBlue:"); Serial.print(b);
 

 if ((r > 1.4) && (g < 0.9) && (b < 0.9)) {
 Serial.print("\tRED");
   analogWrite(REDPIN, 255);
   analogWrite(GREENPIN, 0);
   analogWrite(BLUEPIN, 0);   
 }
 else if ((r < 0.95) && (g > 1.4) && (b < 0.9)) {
 Serial.print("\tGREEN");
   analogWrite(REDPIN, 0);
   analogWrite(GREENPIN, 255);
   analogWrite(BLUEPIN, 0);   
 }
 else if ((r < 0.8) && (g < 1.2) && (b > 1.2)) {
 Serial.print("\tBLUE");
   analogWrite(REDPIN, 0);
   analogWrite(GREENPIN, 0);
   analogWrite(BLUEPIN, 255);   

 }
 else if ((r > 1.1) && (g > 1.1) && (b < 0.7)) {
 Serial.print("\tYELLOW");
   analogWrite(REDPIN, 250);
   analogWrite(GREENPIN, 250);
   analogWrite(BLUEPIN, 0);   

 }
 else if ((r > 1.4) && (g < 1.0) && (b < 0.7)) {
 Serial.print("\tORANGE");
   analogWrite(REDPIN, 255);
   analogWrite(GREENPIN, 142);
   analogWrite(BLUEPIN, 0);   
 } 
 else {
 Serial.print("\t unknown!"); 
   analogWrite(REDPIN, 0);
   analogWrite(GREENPIN, 0);
   analogWrite(BLUEPIN, 0);   
 }
 
 
 Serial.println("");
 
 delay(100);
 
}
