#include "spi.h"


void spiw8bit(u8 dat1,u8 dat2) //д���ֽ�
{
	u8 i;
	clk = 0;
	_nop_();_nop_();
	ce = 1;
	for(i = 0; i<8; i++)
	{
		dio = dat1&0x01;
		_nop_();_nop_(); 
		clk = 1;
		_nop_();_nop_(); 
		clk = 0;
		dat1 >>= 1;
		_nop_();_nop_();
	}
	for(i = 0; i<8; i++)
	{
		dio = dat2&0x01;
		_nop_();_nop_();
		clk = 1;
		_nop_();_nop_(); 
		clk = 0;
		dat2 >>= 1;
		_nop_();_nop_(); 
	}
	ce = 0;
}


u8 spir8bit(u8 dat1)  //дһ�ֽڣ� ��һ�ֽ�
{
	u8 i,rd,rdat;
	clk = 0;
	_nop_();_nop_();
	ce = 1;
	for(i = 0; i<8; i++)
	{
		dio = dat1&0x01;
		_nop_();_nop_(); 
		clk = 1;
		_nop_();_nop_();
		clk = 0;
		dat1 >>= 1;
		_nop_();_nop_(); 
	}
	dio = 1; //�ͷ�
	for(i = 0; i<8; i++)
	{
		_nop_();_nop_(); 
		clk = 1;
		_nop_();_nop_(); 
		clk = 0;
		rdat >>= 1;
		_nop_();_nop_(); 
		rd = dio;
		rdat |= rd<<7;
	}
	ce = 0;
	return rdat;
}
