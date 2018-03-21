#include <motoTM1637.h>

float  i;
TM1637 tm1637led(2,3);

void setup()
{
  i = 0;
}

void loop()
{
    i = i + 0.1;
    tm1637led.display(i);
    delay(1000);

}
