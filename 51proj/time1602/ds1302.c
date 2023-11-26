#include "ds1302.h"


u8 DSread(u8 cmd) // 发送一字节 读取一字节
{
	u8 i,rdat;
	clk = 0;
	_nop_();
	ce = 1;
	for(i = 0; i < 8; i++)
	{
		dat = cmd << 7;
		cmd >>= 1;
		clk = 1;
		_nop_();
		clk = 0;
		_nop_();
	}
	for(i = 0; i < 8; i++)
	{
		rdat >>= 1;
		rdat |= (u8)dat << 7;
		clk = 1;
		_nop_();
		clk = 0;
		_nop_();
	}
	ce = 0;
	clk = 1;
	dat = 1;
	return rdat;
}
void DSwirte(u8 cmd,u8 data1)
{
	u8 i;
	clk = 0;
	_nop_();
	ce = 1;
	for(i = 0; i < 8; i++)
	{
		dat = cmd << 7;
		cmd >>= 1;
		clk = 1;
		_nop_();
		clk = 0;
		_nop_();
	}
	for(i = 0; i < 8; i++)
	{
		dat = data1 << 7;
		data1 >>= 1;
		clk = 1;
		_nop_();
		clk = 0;
		_nop_();
	}
	ce = 0;
	clk = 1;
	dat = 1;
}
void DS1302Init()
{
	
}