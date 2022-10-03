/*
步骤：
1.把ZT.SEG8B4模块的ADR管脚拉低，串电阻或者直接拉到地都可以
2.给ZT.SEG8B4模块上电
3.ZT.SEG8B4A036A模块将会显示“_CA_”,表示已经进入设置地址模式，设置地址模式时ZT.SEG8B4A036A的地址为
0x51,如果没有这么显示，请重复第1,2步骤
3.上电运行ARDUINO的这个代码，设置成功后ZT.SEG8B4A036A模块将会显示新地址
4.这是成功后给ZT.SEG8B4A036A模块重新上电进入正常工作模式
*/
#include <motoZtLib.h>
#include <Wire.h>
//为了与通用MCU通用，这里地址参数为标准的8BIT数据，最低位读写位只能为0，否则地址将归零
//ARDUINO 的地址操作不包含最低位的读写位，即左右一位之前的7位读数
//例如，设置地址为0xA2时，ARDUINO平台操作的地址为0x51
#define ZTSEG8B4_ADDR  (0x51<<1) //0xA2 //(1010001xB)要设置的新地址

void setup()
{
   ZT.I2cInit();
   digitalWrite(13, HIGH);
   Serial.begin(9600);
   Serial.print("You shout pull SCL PIN Low during power up, then the module Will go into Set New Address Mode The Mode Address is 0x51\n");
   ZT.Seg8b4a036aSetAddress(ZTSEG8B4_ADDR);//You Must Pull SCL PIN Low During Power up, after the module will Display "_CA_"(1100101xB) then release SCL PIN as I2C SCL
   Serial.print("If you see the new address display on te module, it means the address was change by your set!\n");
   Serial.print("Now you can reset the module and use the new address by the mormal working mode!\n");
}

void loop()
{
}
