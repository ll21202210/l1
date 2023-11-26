#include "16.h"

void Delay200us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	i = 150;
	while (--i);
}
void LCM16wcmd(u8 cmd)
{
	LCM16WR = 0;
	LCM16RD = 0;
	LCM16Dat = cmd;
	_nop_();
	LCM16EN = 1;
	Delay200us();
	LCM16EN = 0;
	_nop_();
	
}
void LCM16wdat(u8 dat)
{
	LCM16WR = 0;
	LCM16RD = 1;
	LCM16Dat = dat;
	_nop_();
	LCM16EN = 1;
	Delay200us();
	LCM16EN = 0;
	_nop_();
}
void LCM1602Init(void)
{
	LCM16EN = 0;
	LCM16wcmd(modes1);
	LCM16wcmd(dison);
	LCM16wcmd(i1s0);
	LCM16wcmd(cls);
	Delay2ms();
}
void Delay2ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 4;
	j = 225;
	do
	{
		while (--j);
	} while (--i);
}