#include <Wire.h>
#include <moto_GFX.h>
#include "moto_LEDBackpack.h"

moto_8x16matrix  led16x8_0x70= moto_8x16matrix();

void led16x8_StringShow_0x70(String showStr) {
       led16x8_0x70.clear();
         led16x8_0x70.setTextSize(1);
         led16x8_0x70.setTextWrap(false);
         led16x8_0x70.setTextColor(LED_ON);
         int strlength = showStr.length() * 6; // about width of a char
        for (int16_t x=7; x>=-strlength; x--) {
           led16x8_0x70.clear();
           led16x8_0x70.setCursor(x,0);
           led16x8_0x70.print(showStr);
           led16x8_0x70.writeDisplay();
          delay(100);
        }
}

 uint8_t  led16x8data_0x70_10639693304[]={0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,};

void led16x8display_0x70(uint8_t led16x8data[]){
       led16x8_0x70.clear();
       for(int i=0; i<128; i++)
       {
         int x= i%16;
         int y= i/16;
         if(led16x8data[i] == 1)
           led16x8_0x70.drawPixel(x, y, LED_ON);
         else
           led16x8_0x70.drawPixel(x, y, LED_OFF);
       }
       led16x8_0x70.writeDisplay();
};

void setup()
{
  led16x8_0x70.begin(0x70);
  led16x8_0x70.setRotation(3);

}


void loop()
{
    led16x8_0x70.clear();
    led16x8_0x70.writeDisplay();
    led16x8_StringShow_0x70("Motoduino");
    for (int i = 1; i <= 3; i=i+1) {
      led16x8display_0x70(led16x8data_0x70_10639693304);
      delay(1000);
      led16x8_0x70.clear();
      led16x8_0x70.writeDisplay();
      delay(1000);
    }

}