#include <reg52.h>
#include <intrins.h>
#include "iic.h"

void iicstart(void)
{
	dio = 1;
	clk = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	dio = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
}
void iicstop(void)
{
	
	dio = 0;
	clk = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	dio = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
}
void iics8bit(u8 da)
{
	u8 i;
	clk = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	for(i = 0; i<8; i++)
	{
		dio = da>>7;
		da = da<<1;
		_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
		clk = 1;
		_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
		clk = 0;
		_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	}
}
void iicresp(u8 i)
{
	if(i)
		dio = 1;
	else
		dio = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	clk = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	clk = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	dio = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
}

u8 iicread8bit(void)
{
	u8 dat,i;
	clk = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	dio = 1; //释放
	
	for(i = 0; i<8; i++)
	{
		dat = dat<<1;
		clk = 1;
		_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
		dat |= dio;
		_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
		clk = 0;
		_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	}
	return dat;
}
void iicwait(void)
{
	u8 i = 250;
	dio = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	clk = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
	while(dio && i--)
	{
		_nop_();_nop_();_nop_();_nop_(); 
	} //1ms
	if(i == 0)
		led = 0;
	clk = 0;
	_nop_();_nop_();_nop_();_nop_();_nop_(); //5us
}