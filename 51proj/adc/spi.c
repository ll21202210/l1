#include "spi.h"

u16 xpt2046r(u8 cmd)
{
	u16 dat = 0x00;
	u8 i;
	clk = 0;
	_nop_();_nop_();_nop_();
	cs = 0;
	for(i = 0; i < 8; i++)
	{
		din = cmd >>7;
		cmd <<= 1;
		clk = 1;
		_nop_();_nop_();
		clk = 0;
		_nop_();
	}
//	for(i=6; i>0; i--);
	_nop_();_nop_();
	clk = 1;
	_nop_();_nop_();
	clk = 0;
	_nop_();_nop_();
	for(i = 0; i < 12; i++)
	{
		dat |= dout;
		dat <<= 1;
		clk = 1;
		_nop_();_nop_();
		clk = 0;
		_nop_();_nop_();
	}
	cs = 1;
	return dat;
}
