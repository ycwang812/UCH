/*
ZT.Seg8b4a036aReadVersion(uint8_t, uint8_t *, uint8_t)
函数功能 ：读取ZT.Seg8b4a036a的版本号
第1个参数：为模块的地址
第2个参数：模块版本号的缓存
第3个参数：所要读取版本号的位数
*/
#include <motoZtLib.h>
#include <Wire.h>
#define ZTSEG8B4A036A_ADDR  0x51
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
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buff);
        delay(Nopdelay);
    }
    Nopdelay = 100;
    for (i=3 ;i>0; i--)
    {
        buff[0]=buff[1]=buff[2]=buff[3] = 0;
        buff[i] = (1<<4);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<5);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<0);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<1);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buff);
        delay(Nopdelay);
        buff[i] = (1<<2);
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buff);
        delay(Nopdelay);
    }
     buff[0]=buff[1]=buff[2]=buff[3] = 0xFF;
     ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buff);
     delay(1000);
}
void setup()
{
  uint8_t verbuff[19];
  uint16_t vx;
  uint8_t temp;
  ZT.I2cInit(); 
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  pinMode(13, INPUT); 
  ZT.Seg8b4a036aUnSleep(ZTSEG8B4A036A_ADDR);
  Test();
  temp = ZT.Seg8b4a036aReadVersion(ZTSEG8B4A036A_ADDR,verbuff);
  for (int i=0; i<temp; i++)
  { 
    Serial.print((char)verbuff[i]);  
  }
  Serial.print('\n'); 
  vx = (verbuff[16] - '0')*10 + (verbuff[18]) - '0';
  ZT.Seg8b4a036aDisplayDec(ZTSEG8B4A036A_ADDR, vx, DISP_2BIT, DOT_BIT2);
}
void loop()
{
}

