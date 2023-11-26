#include <reg52.h>
#include <intrins.h>
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define s	300

sbit ma = P1^0;
sbit mb = P1^1;
sbit mc = P1^2;
sbit md = P1^3;
sbit ena = P1^4;
sbit enb = P1^5;
u8 i = 0;
u8 pwm_duty = 62;
void delay(u16 t)
{
	while(t--)
	_nop_();
}
void  initt0()
{
	TMOD = 0x02;
	TH0 = 156;
	TL0 = 156;
	TR0 = 1;
	EA = 1;
	ET0 = 1;
}
void main(void)
{
	initt0();
	while(1)
	{
		ma = 1;
		mb = 0;
		mc = 0;
		md = 0;
		delay(s);
		ma = 1;
		mb = 0;
		mc = 1;
		md = 0;
		delay(s);
		ma = 0;
		mb = 0;
		mc = 1;
		md = 0;
		delay(s);
		ma = 0;
		mb = 1;
		mc = 1;
		md = 0;
		delay(s);
		ma = 0;
		mb = 1;
		mc = 0;
		md = 0;
		delay(s);
		ma = 0;
		mb = 1;
		mc = 0;
		md = 1;
		delay(s);
		ma = 0;
		mb = 0;
		mc = 0;
		md = 1;
		delay(s);
		ma = 1;
		mb = 0;
		mc = 0;
		md = 1;
		delay(s);
	}
}
void IRQ_T0() interrupt 1
{
	if(i < 100)
		i++;
	else
		i = 0;
	if(i < pwm_duty)
	{
		ena = 1;
		enb = 1;
	}
	else
	{
		ena = 0;
		enb = 0;
	}
}