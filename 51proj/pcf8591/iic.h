#ifndef __IIC_H
#define __IIC_H 
typedef unsigned int u16;
typedef unsigned char u8;
typedef unsigned long u32;

sbit clk = P2^1;
sbit dio = P2^0;

void Delay5us();
void iicstart(void);
void iicstop(void);
void iicresp(u8 i);
void iicwait(void);
void iics8bit(u8 da);
u8 iicread8bit(void);
void PCF8591read(u8 cmd);
u8 PCF8591radc();
void PCF8591sadc(u8 cmd);
void PCF8591sdac(u8 cmd,u8 dat);

#endif