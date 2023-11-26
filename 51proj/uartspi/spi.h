#ifndef __SPI_H_
#define __SPI_H_
#include <reg52.h>
#include <intrins.h>
#define u8 unsigned char
#define u16 unsigned int
sbit ce = P1^1;
sbit clk = P1^2;
sbit dio = P1^3;

#endif /** __SPI_H_ */