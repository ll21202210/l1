#ifndef __IIC_H
#define __IIC_H 
sbit led = P1^0;
typedef unsigned int u16;
typedef unsigned char u8;
typedef unsigned long u32;

sbit clk = P2^1;
sbit dio = P2^0;

void iicstart(void);
void iicstop(void);
void iicresp(u8 i);
void iicwait(void);
void iics8bit(u8 da);
u8 iicread8bit(void);
#endif