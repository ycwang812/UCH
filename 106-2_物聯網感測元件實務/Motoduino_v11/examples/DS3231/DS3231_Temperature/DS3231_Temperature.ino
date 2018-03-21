
#include <motoDS3231.h>

// Init the DS3231 using the hardware interface
motoDS3231  rtc(SDA, SCL);

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();
}

void loop()
{
  // Send current temperature
  Serial.print("Temperature: ");
  Serial.print(rtc.getTemp());
  Serial.println(" C");
  delay (1000);
}
