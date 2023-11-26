#include <reg52.h>
#include <intrins.h>
#include "max7219.h"

void max7219w(u8 cmd,u8 da2)
{
	u8 i;
	clk = 0;
	_nop_();
	cs =  0;
	for(i = 0; i<8; i++)
	{
		dio = cmd>>7;
		cmd = cmd<<1;
		_nop_();
		clk = 1;
		_nop_();
		clk = 0;
		_nop_();
	}
	for(i = 0; i<8; i++)
	{
		dio = da2>>7;
		da2 = da2<<1;
		_nop_();
		clk = 1;
		_nop_();
		clk = 0;
		_nop_();
	}
	cs =  1;
}