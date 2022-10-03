///////////////////////////////////////////////
// Description: Light Sensor(TEMT6000) Test 
// Author: Motoduino
// Date April 2016
/////////////////////////////////////////////
#include <IoTkit.h>    // include IoTkit.h to use the Intel IoT Kit
#include <Ethernet.h>  // must be included to use IoTkit
#include <aJSON.h>
// create an object of the IoTkit class
IoTkit iotkit;        

int temt6000Pin = A1;

void setup() {
  Serial.begin(9600);

  iotkit.begin();

}
 
void loop() {
  int value = analogRead(temt6000Pin);
  Serial.println(value);

  iotkit.send("mylightSensor", value);
  delay(3000); //only here to slow down the output so it is easier to read

}
