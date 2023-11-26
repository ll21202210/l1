#ifndef __TM1637_H_
#define __TM1637_H_
#include <reg52.h>
#include <intrins.h>

#define u8 unsigned char
#define u16 unsigned int


sbit IIC_SCL = P3^7;
sbit IIC_SDA = P3^6;

void tm1637_WriteSRAM(u8 *buffer);

#endif /**__TM1637_H_*/
