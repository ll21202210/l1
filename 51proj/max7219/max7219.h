#ifndef __IIC_H
#define __IIC_H 

typedef unsigned int u16;
typedef unsigned char u8;
typedef unsigned long u32;

sbit clk = P2^2;
sbit dio = P2^0;
sbit cs = P2^1;

void max7219w(u8 da1,u8 da2);
#endif