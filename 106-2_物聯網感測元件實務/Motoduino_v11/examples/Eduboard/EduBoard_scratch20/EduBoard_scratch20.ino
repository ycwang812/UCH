/*
   Sensor Shield sketch
 
 vers. 1.0 by Daniel José Viana  - danjovic@hotmail.com
 January, 2013
 
 This sketch is based on "Serial Event example" from Arduino
 
 When new serial data arrives, check if its a this data Request from Scratch.
 Then it gets the data from the sensors and send it back to Scratch with  
 400us between bytes
 */

/*   Shield definitions   */
// Discrete signals
#define Button 2
#define Enable_Sound_Channel 7
#define Enable_Light_Channel 6
// Analog Signals
#define ADC_Channel_Resistance_A 5 // 0
#define ADC_Channel_Resistance_B 4 // 1
#define ADC_Channel_Resistance_C 2 // 2
#define ADC_Channel_Resistance_D 1
//#define ADC_Channel_SoundLight   3
#define ADC_Channel_Light   6
#define ADC_Channel_Sound   3
#define ADC_Channel_Slider       0 //5

/*   Scratch definitions   */
// Constants
#define SCRATCH_DATA_REQUEST 0x01
#define Firmware_Version 0x04
// Channels
#define ID_Firmware  15
#define ID_Channel_Resitance_D  0
#define ID_Channel_Resitance_C  1
#define ID_Channel_Resitance_B  2
#define ID_Channel_Button       3
#define ID_Channel_Resitance_A  4
#define ID_Channel_Light_sensor 5
#define ID_Channel_Sound_sensor 6
#define ID_Channel_Slider       7


boolean NewRequest = false;  
char request=0;
unsigned int sensor_value=0;
char data_packet[2]="";


void setup() {
  
  ADMUX = (ADMUX & 0x7F) | 0x40;
  // initialize serial:
  Serial.begin(38400);  
  // initialize discretes
  pinMode(Button, INPUT);
  digitalWrite(Button,HIGH); // activate internall pullup for button pin
//  pinMode(Enable_Sound_Channel, OUTPUT);  
//  pinMode(Enable_Light_Channel, OUTPUT);  
//  digitalWrite(Enable_Sound_Channel, LOW); // disable both ADC imputs
//  digitalWrite(Enable_Sound_Channel, LOW); 
}

void loop() {
  // Send a packet when a new request arrives:
  if (NewRequest) {
    NewRequest = false;
    // send ID
    buildScratchPacket(data_packet, ID_Firmware , Firmware_Version );
    sendScratchPacket(data_packet);

    // send channel 0
    sensor_value=analogRead(ADC_Channel_Resistance_D);
    buildScratchPacket(data_packet, ID_Channel_Resitance_D, sensor_value);
    sendScratchPacket(data_packet);

    // send channel 1
    sensor_value=analogRead(ADC_Channel_Resistance_C);
    buildScratchPacket(data_packet, ID_Channel_Resitance_C, sensor_value);
    sendScratchPacket(data_packet);

    // send channel 2
    sensor_value=analogRead(ADC_Channel_Resistance_B);
    buildScratchPacket(data_packet, ID_Channel_Resitance_B, sensor_value);
    sendScratchPacket(data_packet);

    // send channel 3
    if (digitalRead(Button)) {
      sensor_value=0xffff;
    } 
    else {
      sensor_value=0x0;
    }
    buildScratchPacket(data_packet, ID_Channel_Button, sensor_value);
    sendScratchPacket(data_packet);

    // send channel 4
    sensor_value=analogRead(ADC_Channel_Resistance_A);
    buildScratchPacket(data_packet, ID_Channel_Resitance_A, sensor_value);
    sendScratchPacket(data_packet);

    // send channel 5
 //   digitalWrite(Enable_Light_Channel, HIGH); // Switch ADC to Light sensor
 //   delayMicroseconds(5);    
    sensor_value=analogRead(ADC_Channel_Light);
//    digitalWrite(Enable_Light_Channel, LOW); 
    buildScratchPacket(data_packet, ID_Channel_Light_sensor, sensor_value);
    sendScratchPacket(data_packet);

    // send channel 6
//    digitalWrite(Enable_Sound_Channel, HIGH); // Switch ADC to Light sensor
//    delayMicroseconds(5);    
    sensor_value=analogRead(ADC_Channel_Sound);
 //   digitalWrite(Enable_Sound_Channel, LOW); 
    buildScratchPacket(data_packet, ID_Channel_Sound_sensor, sensor_value);
    sendScratchPacket(data_packet);

    // send channel 7
    sensor_value=analogRead(ADC_Channel_Slider);
    buildScratchPacket(data_packet, ID_Channel_Slider, sensor_value);
    sendScratchPacket(data_packet);
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    if (inChar == SCRATCH_DATA_REQUEST) {
      NewRequest = true;
    } 
  }
}


void buildScratchPacket(char * packet, int channel, int value){
  char upper_data=(char)((value&(unsigned int)0x380)>>7);	//Get the upper 3 bits of the value
  char lower_data=(char)(value&0x7f);	//Get the lower 7 bits of the value
  *packet++=((1<<7)|(channel<<3)|(upper_data));
  *packet++=lower_data;
}

void sendScratchPacket(char * packet){
  Serial.write(*packet++);
  delayMicroseconds(400);
  Serial.write(*packet);
  delayMicroseconds(400);
}



