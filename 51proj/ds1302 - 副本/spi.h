#ifndef _SPI_H_
#define _SPI_H_

#include "reg52.h"
#include <intrins.h>

#define u8 unsigned char
#define u16 unsigned int
sbit ce = P1^0;
sbit clk = P1^1;
sbit dio = P1^2;

void spiw8bit(u8 dat, u8 dat2);
u8 spir8bit(u8 dat1);
#endif