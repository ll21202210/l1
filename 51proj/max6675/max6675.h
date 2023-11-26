#ifndef __MAX6675_H_
#define __MAX6675_H_

#include <reg52.h>


#define u8 unsigned char
#define u16 unsigned int

sbit SPI_SCL = P3^2;
sbit SPI_CS = P3^3;
sbit SPI_SO = P3^4;


u16 SPI_Read(void);

void MAX6675_Init(void);
float MAX6675_Read(void);
u8 MAX6675_Check(void);

#endif /**__MAX6675_H_*/
