/*
ZT.Seg8b4a036aSetLumin(uint8_t, uint8_t, uint8_t)
函数功能 ：设置ZT.Seg8b4a036a模块显示的亮度
第1个参数：为模块的地址
第2个参数：亮度的极性
第3个参数：暗度的极性 
注明：亮度和暗度相互影响显示的亮度效果，在可接受的亮度下，暗度值越到越省电
*/
#include <motoZtLib.h>
#include <Wire.h>
#define ZTSEG8B4_ADDR  0x51
uint8_t buff[4];
uint8_t Nopdelay;
unsigned short testnum=0;

void Test()
{
    uint8_t i;
    Nopdelay = 1000;
    for (i=0 ;i<8; i++)
    {
        buff[0]=buff[1]=buff[2]=buff[3] = (1<<i);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4_ADDR, buff);
        delay(Nopdelay);
    }
    Nopdelay = 100;
    for (i=3 ;i>0; i--)
    {
        buff[0]=buff[1]=buff[2]=buff[3] = 0;
        buff[i] = (1<<4);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<5);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<0);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<1);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<2);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4_ADDR, buff);
        delay(Nopdelay);
    }
     buff[0]=buff[1]=buff[2]=buff[3] = 0xFF;
     ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4_ADDR, buff);
     delay(1000);
}
void setup()
{
  uint8_t verbuff[15];
  Wire.begin(); 
  Serial.begin(9600);
  
  pinMode(13, OUTPUT); 
  pinMode(13, INPUT); 
  ZT.Seg8b4a036aUnSleep(ZTSEG8B4_ADDR);
  Test();
  Nopdelay = 2000;
}
void loop()
{
  if (testnum == 10) Nopdelay = 1000;
  else if (testnum == 20)  Nopdelay = 500;
  else if (testnum == 30)  Nopdelay = 200;
  else if (testnum == 40)  Nopdelay = 100;
  else if (testnum == 50)  Nopdelay = 50;
  else if (testnum == 100)  Nopdelay = 20;
  else if (testnum ==150)  Nopdelay = 10;
  else if (testnum == 600)  Nopdelay = 0;
  if (++testnum>9999)  testnum = 0;
  ZT.Seg8b4a036aDisplayDec(ZTSEG8B4_ADDR,testnum, DISP_4BIT, DOT_NONE);
  digitalWrite(13,LOW);
  delay(Nopdelay);
  if (testnum < 200) ZT.Seg8b4a036aSetBrightness(ZTSEG8B4_ADDR,(uint8_t)testnum,0xFF);
  digitalWrite(13,HIGH);
  delay(Nopdelay);
}

