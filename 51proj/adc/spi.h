#ifndef __SPI_H_
#define __SPI_H_

#include <reg52.h>
#include <intrins.h>

#define u16 unsigned int 
#define u8 unsigned char

sbit cs = P2^0;
sbit clk = P2^1;
sbit dout = P2^2;
sbit din = P2^3; //–æ∆¨ ‰»Î


u16 xpt2046r(u8 cmd);



#endif /** __SPI_H_ */