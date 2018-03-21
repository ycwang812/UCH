#include <motoZtLib.h>
#include <Wire.h>

#define ZTSEG8B4A036A_ADDR  0x51
uint8_t buff[0];
uint8_t Nopdelay=0;
unsigned short testnum=0;

void setgbit(uint8_t gbit, uint8_t val)
{
    if (gbit <3)
    {
        buff[gbit] = val; 
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
    }
}
void setpbit(uint8_t gbit, uint8_t val)
{
    uint8_t pbuf[4] = {0,0,0,0};
    if (gbit <3)
    {
        pbuf[gbit] = val; 
        ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,pbuf);
    }
}


void test1(uint8_t temp1, uint8_t temp2)
{
   int i;
   for (i=0; i<4; i++)
   {
      buff[i] = 0;
   }
    for (i=0; i<4; i++)
    {
       buff[i] = temp1;
       ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
       delay(temp2);
    }
}

void test2(uint8_t temp1, uint8_t temp2)
{
   for (int i=0; i<4; i++)
   {
       buff[i] = 0;
   }
   delay(temp2);
   
    for (int i=0; i<4; i++)
    {
       buff[i] = temp1;
       ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
       delay(temp2);
    }
    
    for (int i=4; i>0; i--)
    {
       buff[i-1] = 0;
       ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
       delay(temp2);
    }
}
void test3(uint8_t temp1, uint8_t temp2)
{;
   for (int i=0; i<4; i++)
   {
       buff[i] = 0;
   }
   delay(temp2);
    for (int i=0; i<4; i++)
    {
       buff[i] = temp1;
       if (i>0) buff[i-1]=0;
       ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
       delay(temp2);
    }
}
void test4(uint8_t pdelay)
{
  for (int i=0; i<4; i++)
  {
    buff[i] = 0;
  }
  for (int i=0; i<13; i++)
  {
    if(i%2) buff[2] |= 0x80;
    else  buff[2] &= 0x7F;
    
    if ((i/2)==1) {buff[2] |= 0x04;buff[1] |= 0x10;}
    else if ((i/2)==2) {buff[2] |= 0x02;buff[1] |= 0x20;}
    else if ((i/2)==3) {buff[2] |= 0x01;buff[1] |= 0x01;}
    else if ((i/2)==4) {buff[3] |= 0x01;buff[0] |= 0x01;}
    else if ((i/2)==5) {buff[3] |= 0x20;buff[0] |= 0x02;}
    else if ((i/2)==6) {buff[3] |= 0x10;buff[0] |= 0x04;}
    ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
    delay(pdelay);
  }
}
void test5(uint8_t pdelay)
{
  uint8_t temp;
  for (int i=0; i<4; i++)
  {
    buff[i] = 0;
  }
  for (int i=0; i<8; i++)
  {
      if (i==0) temp = 1;
      else if (i==1) temp = 3;
      else if (i==2) temp = 5;
      else if (i==3) temp = 7;
      else if (i==4) temp = 10;
      else if (i==5) temp = 20;
      else if (i==6) temp = 30;
      else if (i==7) temp = 130;
      ZT.Seg8b4a036aSetBrightness(ZTSEG8B4A036A_ADDR,temp,0xFF);
      
      if(!(i%2)) buff[i/2] = 0x06;
      else    buff[i/2] |= 0x30;
      ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
      delay(pdelay);
  }
}

void test6(uint8_t pdelay)
{
  for (int i=0; i<4; i++)
  {
    buff[i] = 0;
  }
  for (int i=0; i<=0xFF; i++)
  {
    for (int j=0; j<4; j++)
    {
        buff[j] = i;
        if(i%2) buff[j] |= 0x80;
        else  buff[j] &= 0x7F;
    }
    ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR,buff);
    delay(pdelay);
  }
}

void setup()
{
  Serial.begin(9600);
  ZT.I2cInit();
  digitalWrite(13, HIGH);
  ZT.Seg8b4a036aUnSleep(ZTSEG8B4A036A_ADDR);
}

void loop()
{
  ZT.Seg8b4a036aSetBrightness(ZTSEG8B4A036A_ADDR,0x3F,0xFF);
  for(int x =0; x<10; x++)
  {
    test1(0x7F, 50);
  }
  for(int x =0; x<10; x++)
  {
    test2(0x0C,20);
    test2(0x21,35);
  }
  for(int k=0; k<5; k++)
  {
    test2(0x06,50);
  }
  for(int k=0; k<5; k++)
  {
    test3(0x09,120);
    delay(20);
  }
  for(int k=0; k<5; k++)
  {
     test4(100);
  }
  for(int k=0; k<5; k++)
  {
      test5(100);
  }
  ZT.Seg8b4a036aSetBrightness(ZTSEG8B4A036A_ADDR,0x3F,0xFF);
  test6(100);
}
