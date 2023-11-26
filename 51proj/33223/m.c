#include <reg52.H>


sbit oa = P1^0;
sbit ob = P1^1;

unsigned int s= 3000;

void delay(unsigned int t)
{
	while(t--);
}
void tint()
{
	TMOD = 0x01;
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;
	EA = 1;
	ET0 = 1;
}
void main(void)
{
	
	tint();
	while(1)
	{
		oa = 1;
		ob = 0;
		delay(100+s);
		
		oa = 0;
		ob = 1;
		delay(100+s);
		
	}
}

void irq0() interrupt 1
{
	TH0 = 0;
	TL0 = 0;
	if(s > 1000)
		s-= 5;
	if(s > 700)
		s--;
	else
		TR0 = 0;
}