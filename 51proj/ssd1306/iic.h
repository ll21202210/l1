#ifndef __IIC_H_
#define __IIC_H_
#include <reg52.h>
#include <intrins.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit scl = P1^0;
sbit sda = P1^1;

void iicstart(void);
void iicstop(void);
void iics8bit(u8 da);
void ssd1306init(void);
void ssdscmd(u8 cmd);
void ssdsdat(u8 dat);
#endif /** __IIC_H_ */