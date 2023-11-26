#include <reg52.h>
#include <intrins.h>
#define u8 unsigned char
sbit io = P0^7;
void Delay40us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 17;
	while (--i);
}
void send(u8 g, u8 r, u8 b)
{
	u8 i = 8;
	io = 0;
	while(i--)
	{
		if(g >> 7)
		{
			io = 1;
			_nop_();_nop_();
			io = 0;
		}else
		{
			io = 1;
			_nop_();
			io = 0;
		}
		g <<=1;
	}
	Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
	i = 8;
	while(i--)
	{
		if(r >> 7)
		{
			io = 1;
			_nop_();_nop_();
			io = 0;
		}else
		{
			io = 1;
			_nop_();
			io = 0;
		}
		r <<=1;
	}
	Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
	i = 8;
	while(i--)
	{
		if(b >> 7)
		{
			io = 1;
			_nop_();_nop_();
			io = 0;
		}else
		{
			io = 1;
			_nop_();
			io = 0;
		}
		b <<=1;
	}
	Delay40us();Delay40us();Delay40us();Delay40us();
	Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
}
void main()
{
	u8 i;
	io = 0;
	Delay40us();Delay40us();
	while(1)
	{
		send(0xff,0xff,0);
		send(0xff,0,255);
		send(0,255,0xff);
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		Delay40us();Delay40us();Delay40us();Delay40us();
		io = 1;
		Delay40us();Delay40us();Delay40us();Delay40us();
	}
	
}