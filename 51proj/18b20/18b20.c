#include "18b20.h"
void Delay550us()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 14;
	do
	{
		while (--j);
	} while (--i);
}
void Delay45us()		//@12.000MHz
{
	unsigned char i;

	i = 20;
	while (--i);
}


void dsinit(void)
{
	dio = 0;
	Delay550us();
	dio = 1;
	Delay550us();
}
void dsw8bit(u8 dat)
{
	u8 i,j;
	for(j = 0; j<8; j++)
	{
		dio = 0;
		_nop_();//1us
		dio = dat&0x01; //先发低位
		i = 6;
		while(i--);//68us
		dio = 1;
		dat = dat>>1;
	}
}
u8 dsr8bit(void)
{
	u8 j,dat = 0x00,di;
	for(j = 0; j<8; j++)
	{
		dio = 0;
		_nop_();//3us
		dio = 1;
		_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();
		di = dio;
		dat = (dat >> 1) | (di << 7);	
		Delay45us();
	}
	return dat;
}
int dsmeasuretemp(void)
{
	u8 l,h;
	float t;
	int temp = 0;
	dsinit();
	dsw8bit(0xcc); //跳过rom
	dsw8bit(0x44); //启动转换
	
	dsinit();
	dsw8bit(0xcc); //跳过rom
	dsw8bit(0xbe); //读取温度
	l = dsr8bit();
	h = dsr8bit();
	temp = h;
	temp = temp<<8;
	temp |= l;
	temp *= 0.625;
	return temp;
}
