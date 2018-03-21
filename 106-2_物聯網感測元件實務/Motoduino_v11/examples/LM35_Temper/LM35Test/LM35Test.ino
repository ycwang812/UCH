///////////////////////////////////////////////
// Description: LM35 Test 
// Author: Motoduino
// Date April 2016
/////////////////////////////////////////////

int analogPin = A3;//LM35接在A3
int readValue = 0;

float temperature = 0;
float temperatureF = 0;

int times = 0;
float Total_temperature = 0;

void setup()
{
    Serial.begin(9600);//設置baud rate
    pinMode (10, OUTPUT);//LED接在d10
    pinMode (11, OUTPUT);//LED接在d11
}

void loop()
{
  readValue = analogRead(analogPin);
  //Serial.println(readValue);
  temperature = (readValue * 0.0049);
  temperature = temperature * 100;
  temperatureF = (temperature * 1.8) + 32;
  Total_temperature = Total_temperature + temperature;
  times = times + 1;
  if(times == 10)
  {
    temperature = Total_temperature / times;
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("C ");
    Serial.print(temperatureF);
    Serial.println("F");
    if (temperature <= 30)
      {
        digitalWrite (10, LOW);
        digitalWrite (11, HIGH);
      }
      if (temperature > 30)
      {
       digitalWrite (10, HIGH);
        digitalWrite (11, LOW);
      }   
      times = 0;
      Total_temperature = 0;
  }
    delay(100);
}  
