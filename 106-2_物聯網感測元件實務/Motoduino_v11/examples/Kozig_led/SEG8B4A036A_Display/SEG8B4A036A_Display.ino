/*
    ZT.Seg8b4a036aDisplayDec(uint8_t,unsigned short, uint8_t, uint8_t);
    函数功能 ：显示十进制数据  
    ZT.Seg8b4a036aDisplayHex(uint8_t,unsigned short, uint8_t, uint8_t);
    函数功能 ：显示十六进制数据  
    
    第1个参数：为模块的地址
    第2个参数：要显示的数据 0~9999/0~0xFFFF
    第3个参数：要显示的位数，从右边数起,直接调用库函数的宏定义
               #define DISP_0BIT      全部关掉
               #define DISP_1BIT      显示1位数据   
               #define DISP_2BIT      显示2位数据 
               #define DISP_3BIT      显示3位数据
               #define DISP_4BIT      显示4位数据
               #define DISP_AUTO      自动显示位数，高位为0则不显示 
    第4个参数：要显示的数据 要显示点的位，直接调用库的宏定义 
                DOT_NONE 不显示任何小数点        
                DOT_BIT1 显示第1位的小数点
                DOT_BIT2 显示第2位的小数点
                DOT_BIT3 显示第3位的小数点
                DOT_BIT4 显示第4位的小数点 要显示多维小数点的用 | 运算

    ZT.Seg8b4a036aDisplayBuff(uint8_t,uint8_t *);
    函数功能 ：显示任意数据  
    第1个参数：为模块的地址
    第2个参数：所要填充和显示的内容，按标准8为共阴数码管计算
*/

#include <motoZtLib.h>
#include <Wire.h>
#define ZTSEG8B4A036A_ADDR  0x51

float test=0;
unsigned short temp;
uint8_t nb;

void setup()
{
   ZT.I2cInit();
   digitalWrite(13, HIGH);
   Serial.begin(9600);
   ZT.Seg8b4a036aUnSleep(ZTSEG8B4A036A_ADDR);
}

void loop()
{
     //虽然写有4为数据0xABCD,但要求只显示两位数据，结果显示两位数据CD，点亮第2位数据的小数点
     ZT.Seg8b4a036aDisplayHex(ZTSEG8B4A036A_ADDR, 0xABCD, DISP_2BIT, DOT_BIT2);
     delay(1500);
     //显示两位数据，结EF，点亮第1位数据的小数点
     ZT.Seg8b4a036aDisplayHex(ZTSEG8B4A036A_ADDR, 0xEF, DISP_2BIT, DOT_BIT1);
     delay(1500);
     //自动显示数据，将显示缩写内容 ABC, 点亮第2位数据的小数点
     ZT.Seg8b4a036aDisplayHex(ZTSEG8B4A036A_ADDR, 0xABC, DISP_AUTO, DOT_BIT2);
     delay(1500);
     
     //点亮对应的断码，显示的数据位3210
     {
       uint8_t buf[4] ={0x3F,0x06,0x5B,0x4F};
       ZT.Seg8b4a036aDisplayBuff(ZTSEG8B4A036A_ADDR, buf);
     }
     delay(1500);
     
     //显示小数
     for (unsigned short i=0; i<110; i++)
     {
         test += 0.1;
         temp = test;
         if (temp<10)     nb = DISP_2BIT;
         else nb = DISP_AUTO;
         temp = test*10;
         ZT.Seg8b4a036aDisplayDec(ZTSEG8B4A036A_ADDR, temp, nb, DOT_BIT1);
         delay(20);
     }
     
}
