/*
读取模块的当前状态，并从UART PRINTF出来
ZT.Seg8b4a036aReadState(uint8_t);
函数功能 ：读取ZT.SEG8B4A036A模块的当前状态
第1个参数：为模块的地址
返回值：   当前的状态
注：重复做这个测试时，务必在ARDUINO复位前先复位模块
*/
#include <motoZtLib.h>
#include <Wire.h>
#define SEG8B4A036A_ADDRESS    0x51

void UartPrintState(uint8_t state)
{
  if (state==STATUS_RUN)
  {
      Serial.print("ZT.SEG8B4A036A->Display Normal State:\n");
  }
  else if (state==STATUS_SLEEP)
  {
      Serial.print("ZT.SEG8B4A036A->Sleep State:\n");
  }
  else if (state==STATUS_SET_ADDRESS)
  {
      Serial.print("ZT.SC-SEG8B4A036A->Set Address Mode State:\n");
  }
  else
  {
      Serial.print("ZT.SEG8B4A036A->erro:\n\n");
  }

}
uint8_t temp;
void setup()
{
  Serial.begin(9600);
  ZT.I2cInit();
  Serial.print("Start...\n\n Berfor Set UnSleep()\n");
  temp=ZT.Seg8b4a036aReadState(SEG8B4A036A_ADDRESS);
  UartPrintState(temp);
  
  ZT.Seg8b4a036aUnSleep(SEG8B4A036A_ADDRESS);
  Serial.print("After SetUnSleep()\n");
  temp=ZT.Seg8b4a036aReadState(SEG8B4A036A_ADDRESS);
  UartPrintState(temp);
  
}
uint8_t Nopdelay=2000;
uint8_t buff[4];
unsigned short testnum=0;
void loop()
{
  if (testnum == 10) Nopdelay = 1000;
  else if (testnum == 20)  Nopdelay = 500;
  else if (testnum == 30)  Nopdelay = 200;
  else if (testnum == 40)  Nopdelay = 100;
  else if (testnum == 50)  Nopdelay = 50;
  else if (testnum == 99) {testnum = 0; Nopdelay = 2000;};
  ZT.Seg8b4a036aDisplayDec(SEG8B4A036A_ADDRESS,testnum++, 2, 0);
  digitalWrite(13,LOW);
  delay(Nopdelay);
  if (testnum < 200) ZT.Seg8b4a036aSetBrightness(SEG8B4A036A_ADDRESS,(uint8_t)testnum,0xFF);
  digitalWrite(13,HIGH);
  delay(Nopdelay);
  if (testnum == 10)
  {  
  Serial.print("Befor Set Sleep 1\n");
  delay(1000);
  temp=ZT.Seg8b4a036aReadState(SEG8B4A036A_ADDRESS);
  UartPrintState(temp);
  ZT.Seg8b4a036aSleep(SEG8B4A036A_ADDRESS);
  Serial.print("After Set Sleep 2\n");
  delay(1000);
  temp=ZT.Seg8b4a036aReadState(SEG8B4A036A_ADDRESS);
  UartPrintState(temp);
   Serial.print('\n'); 
  delay(5000);
  }
  else if (testnum == 20)
  {
      ZT.Seg8b4a036aSleep(SEG8B4A036A_ADDRESS);
      delay(5000);
      ZT.Seg8b4a036aUnSleep(SEG8B4A036A_ADDRESS);
      Serial.print("After Set UnSleep 1\n");
      temp=ZT.Seg8b4a036aReadState(SEG8B4A036A_ADDRESS);
      UartPrintState(temp);
  }
}
