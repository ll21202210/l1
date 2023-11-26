
#include "1602.h"

void LCM16wdat(u8 dat)
{
	rw = 0;
	rs = 1;
	dio = dat;
	_nop_();
	en = 1;
	Delay100us();Delay100us();Delay100us();
	en = 0;
	dio = 0xff;
	rs = 1;
	rw = 1;
}
void LCM16wcmd(u8 cmd)
{
	rw = 0;
	rs = 0;
	dio = cmd;
	_nop_();
	en = 1;
	Delay100us();Delay100us();Delay100us();
	en = 0;
	dio = 0xff;
	rs = 1;
	rw = 1;
}
void LCM16wadd(u8 add)
{
	add |= 0x80;
	rw = 0;
	rs = 0;
	dio = add;
	_nop_();
	en = 1;
	Delay100us();Delay100us();Delay100us();
	en = 0;
	dio = 0xff;
	rs = 1;
	rw = 1;
}
void LCM1602init()
{
	en = 0;
	LCM16wcmd(modes1);
	LCM16wcmd(i1s0);
	LCM16wcmd(dison|ygb);
	LCM16wcmd(cls);
	
}


void Delay100us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 47;
	while (--i);
}

