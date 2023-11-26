#include "spi.h"

void spiw8bit(u8 dat1,u8 dat2) //写两字节
{
	u8 i;
	clk = 0;
	_nop_(); 
	ce = 0;
	_nop_();
	for(i = 0; i<8; i++)
	{
		dio = dat1&0x01;
		_nop_(); 
		clk = 1;
		_nop_();
		clk = 0;
		dat1 >>= 1;
		_nop_();
	}
	dio = 1;
	for(i = 0; i<8; i++)
	{
		dio = dat2&0x01;
		_nop_();
		clk = 1;
		_nop_(); 
		clk = 0;
		dat2 >>= 1;
		_nop_(); 
	}
	ce = 1;
}


u8 spir8bit(u8 dat1)  //写一字节， 读一字节
{
	u8 i,rdat;
	clk = 0;
	_nop_(); 
	ce = 0;
	for(i = 0; i<8; i++)
	{
		dio = dat1&0x01;
		_nop_(); 
		clk = 1;
		_nop_(); 
		clk = 0;
		dat1 >>= 1;
		_nop_(); 
	}
	dio = 1; //释放
	_nop_(); 
	for(i = 0; i<8; i++)
	{
		rdat = (rdat>>1) | ((u8)dio<<7);
		_nop_();
		clk = 1;
		_nop_(); 
		clk = 0;
		
		_nop_(); 
	}
	ce = 1;
	return rdat;
}