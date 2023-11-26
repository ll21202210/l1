#include <reg52.h>
#include <intrins.h>
#include "iic.h"
void Delay5us()		//@12.000MHz
{
	unsigned char i;

	i = 12;
	while (--i);
}
void iicstart(void)
{
	dio = 1;
	clk = 1;
	Delay5us();
	dio = 0;
	Delay5us();
}
void iicstop(void)
{
	
	dio = 0;
	clk = 1;
	Delay5us();
	dio = 1;
	Delay5us();
}
void iics8bit(u8 da)
{
	u8 i;
	clk = 0;
	Delay5us();
	for(i = 0; i<8; i++)
	{
		dio = da>>7;
		da = da<<1;
		Delay5us();
		clk = 1;
		Delay5us();
		clk = 0;
		Delay5us();
	}
}
void iicresp(u8 i)
{
	if(i)
		dio = 1;
	else
		dio = 0;
	Delay5us();
	clk = 1;
	Delay5us();
	clk = 0;
	Delay5us();
}

u8 iicread8bit(void)
{
	u8 dat,i;
	clk = 0;
	Delay5us();
	dio = 1; //释放
	
	for(i = 0; i<8; i++)
	{
		dat = dat<<1;
		clk = 1;
		Delay5us();
		dat |= dio;
		Delay5us();
		clk = 0;
		Delay5us();
	}
	return dat;
}
void iicwait(void)
{
	u8 i = 250;
	dio = 1;
	Delay5us();
	clk = 1;
	Delay5us();
	while(dio && i--)
	{
		Delay5us();
	} //1ms
	clk = 0;
	Delay5us();
}

void PCF8591sadc(u8 cmd)
{
	iicstart();
	iics8bit(0x90);
	iicwait();
	iics8bit(cmd);
	iicwait();
	iicstop();
}
u8 PCF8591radc()
{
	u8 dat;
	iicstart();
	iics8bit(0x91);
	iicwait();
	dat = iicread8bit();
	iicstop();
	return dat;
}
void PCF8591sdac(u8 cmd,u8 dat)
{
	iicstart();
	iics8bit(0x90);
	iicwait();
	iics8bit(cmd);
	iicwait();
	iics8bit(dat);
	iicwait();
	iicstop();
}