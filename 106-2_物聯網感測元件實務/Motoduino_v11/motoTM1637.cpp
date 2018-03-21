//  Author:Frankie.Chu
//  Date:9 April,2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/
#include "motoTM1637.h"
#include <Arduino.h>
static int8_t TubeTab[] = {0x3f, 0x06, 0x5b, 0x4f,
                           0x66, 0x6d, 0x7d, 0x07,
                           0x7f, 0x6f, 0x77, 0x7c,
                           0x39, 0x5e, 0x79, 0x71,
                           0xbf, 0x86, 0xdb, 0xcf,
                           0xe6, 0xed, 0xfd, 0x87,
                           0xff, 0xef, 0xf7, 0xfc,
                           0xb9, 0xde, 0xf9, 0xf1, 0, 0x40
                          };//0~9,A,b,C,d,E,F,-,NUL


TM1637::TM1637(uint8_t Clk, uint8_t Data)
{
  Clkpin = Clk;
  Datapin = Data;
  pinMode(Clkpin,OUTPUT);
  pinMode(Datapin,OUTPUT);
  set();
  clearDisplay();
}

void TM1637::reset(uint8_t Clk, uint8_t Data)
{
    Clkpin = Clk;
    Datapin = Data;
    pinMode(Clkpin, OUTPUT);
    pinMode(Datapin, OUTPUT);
    set();
    clearDisplay();
}

void TM1637::init(void)
{
  clearDisplay();
}

void TM1637::writeByte(int8_t wr_data)
{
  uint8_t i,count1;   
  for(i=0;i<8;i++)        //sent 8bit data
  {
    digitalWrite(Clkpin,LOW);      
    if(wr_data & 0x01)digitalWrite(Datapin,HIGH);//LSB first
    else digitalWrite(Datapin,LOW);
    wr_data >>= 1;      
    digitalWrite(Clkpin,HIGH);
      
  }  
  digitalWrite(Clkpin,LOW); //wait for the ACK
  digitalWrite(Datapin,HIGH);
  digitalWrite(Clkpin,HIGH);     
  pinMode(Datapin,INPUT);
  while(digitalRead(Datapin))    
  { 
    count1 +=1;
    if(count1 == 200)//
    {
     pinMode(Datapin,OUTPUT);
     digitalWrite(Datapin,LOW);
     count1 =0;
    }
   // pinMode(Datapin,INPUT);
  }
  pinMode(Datapin,OUTPUT);
  
}
//send start signal to TM1637
void TM1637::start(void)
{
  digitalWrite(Clkpin,HIGH);//send start signal to TM1637
  digitalWrite(Datapin,HIGH); 
  digitalWrite(Datapin,LOW); 
  digitalWrite(Clkpin,LOW); 
} 
//End of transmission
void TM1637::stop(void)
{
  digitalWrite(Clkpin,LOW);
  digitalWrite(Datapin,LOW);
  digitalWrite(Clkpin,HIGH);
  digitalWrite(Datapin,HIGH); 
}

void TM1637::display(uint16_t value)
{
    display((int)value);
    // display((double)value,0);
}

void TM1637::display(int16_t value)
{
    display((double)value, 0);
}

void TM1637::display(double value, uint8_t digits)
{


AA:
    int8_t buf[4] = {' ', ' ', ' ', ' '};
    int8_t tempBuf[4];
    uint8_t b = 0;
    uint8_t bit_num = 0;
    uint8_t  int_num = 0;
    uint8_t isNeg = 0;
    double number = value;
    if (number >= 9999.5 || number <= -999.5);
    else
    {
        // Handle negative numbers
        if (number < 0.0)
        {
            number = -number;
            isNeg = 1 ;
        }
        // Round correctly so that print(1.999, 2) prints as "2.00"
        double rounding = 0.5;
        for (uint8_t i = 0; i < digits; ++i)
            rounding /= 10.0;
        number += rounding;

        // Extract the integer part of the number and print it
        uint16_t int_part = (uint16_t )number;
        double remainder = number - (double)int_part;
        do
        {
            uint16_t m = int_part;
            int_part /= 10;
            char c = m - 10 * int_part;
            tempBuf[int_num] = c;
            int_num++;
        }
        while(int_part);

        bit_num = isNeg + int_num + digits;

        if(bit_num > 4)
        {
            bit_num = 4;
            digits = 4 - (isNeg + int_num);
            goto AA;
        }
        b = 4 - bit_num;
        if(isNeg)buf[b++] = 0x21;

        for(uint8_t i = int_num; i > 0; i--)buf[b++] = tempBuf[i-1];
        // Print the decimal point, but only if there are digits beyond
        if (digits > 0)
        {
            buf[b-1] += 0x10;
            // Extract digits from the remainder one at a time
            while (digits-- > 0)
            {
                remainder *= 10.0;
                int toPrint = int(remainder);
                buf[b++] = toPrint;
                remainder -= toPrint;
            }
        }
    }
    display(buf);
}

void TM1637::write(int8_t SegData[])
{
    uint8_t i;
    start();          //start signal sent to TM1637 from MCU
    writeByte(ADDR_AUTO);
    stop();
    start();
    writeByte(Cmd_SetAddr);
    for(i = 0; i < 4; i ++)
    {
        writeByte(SegData[i]);
    }
    stop();
    start();
    writeByte(Cmd_DispCtrl);
    stop();
}
void TM1637::write(uint8_t BitAddr, int8_t SegData)
{
    start();          //start signal sent to TM1637 from MCU
    writeByte(ADDR_FIXED);
    stop();
    start();
    writeByte(BitAddr | 0xc0);
    writeByte(SegData);
    stop();
    start();
    writeByte(Cmd_DispCtrl);
    stop();
}
//display function.Write to full-screen.
void TM1637::display(int8_t DispData[])
{
    int8_t SegData[4];
    uint8_t i;
    for(i = 0; i < 4; i ++)
    {
        SegData[i] = DispData[i];
    }
    coding(SegData);
    write(SegData);
 //
}
//******************************************
void TM1637::display(uint8_t BitAddr,int8_t DispData)
{
    int8_t SegData;

    if((DispData >= 'A' && DispData <= 'F'))DispData = DispData - 'A' + 10;
    else if((DispData >= 'a' && DispData <= 'f'))DispData = DispData - 'a' + 10;
    SegData = coding(DispData);
    write(BitAddr, SegData); //
}

void TM1637::clearDisplay(void)
{
    int8_t buf[4] = {' ', ' ', ' ', ' '};
    display(buf);
}
//To take effect the next time it displays.
void TM1637::set(uint8_t brightness,uint8_t SetData,uint8_t SetAddr)
{
  Cmd_SetData = SetData;
  Cmd_SetAddr = SetAddr;
  Cmd_DispCtrl = 0x88 + brightness;//Set the brightness and it takes effect the next time it displays.
}

//Whether to light the clock point ":".
//To take effect the next time it displays.
void TM1637::point(boolean PointFlag)
{
  _PointFlag = PointFlag;
}
void TM1637::coding(int8_t DispData[])
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0; 
  for(uint8_t i = 0;i < 4;i ++)
  {
    if(DispData[i] == 0x7f)DispData[i] = 0x00;
    else DispData[i] = TubeTab[DispData[i]] + PointData;
  }
}
int8_t TM1637::coding(int8_t DispData)
{
  uint8_t PointData;
  if(_PointFlag == POINT_ON)PointData = 0x80;
  else PointData = 0; 
  if(DispData == 0x7f) DispData = 0x00 + PointData;//The bit digital tube off
  else DispData = TubeTab[DispData] + PointData;
  return DispData;
}
