#ifndef __SPI_H_
#define __SPI_H_
#include <reg52.h>
#include <intrins.h>
typedef unsigned int u16;
typedef unsigned char u8;

sbit cs = P1^0;
sbit sclk = P1^1;
sbit dat = P1^2;

void spis8bit(u8 cmd, u8 dat);

#endif