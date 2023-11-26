#include <reg52.h>
#include <intrins.h>

#define u8 unsigned char
#define u16 unsigned int 
	
sbit out1 = P1^0;
sbit out2 = P1^1;
sbit out3 = P1^2;

u8 rad1 = 14,rad2 = 14,rad3 = 14;
u8 i = 0;

void delay(u16 time);
void TimerInit(void);

void main(void)
{
//	u8 temp = 5;
	u8 i;
	TimerInit();
	while(1)
	{
		for(i = 5; i<= 25; i++)
		{
			rad1 = i;
			delay(10000);
		}
		for(i = 5; i<= 25; i++)
		{
			rad2 = i;
			delay(10000);
		}
		for(i = 5; i<= 25; i++)
		{
			rad3 = i;
			delay(10000);
		}
//		rad1 = 20;
//		delay(50000);
//		rad1 = 15;
//		delay(50000);
//		rad2 = 20;
//		delay(50000);
//		rad2 = 15;
//		delay(50000);
//		rad3 = 20;
//		delay(50000);
//		rad3 = 15;
//		delay(50000);
//		if(rad != temp)
//		{
//			if(rad < temp)
//				rad++;
//			else
//				rad--;
//		}
//		delay(10000);
//		if(rad == 23)
//			temp = 5;
//		if(rad == 5)
//			temp = 23;
	}
	
}
void delay(u16 time)
{
	while(time--)
		_nop_();
}
void T0int(void) interrupt 1
{
	TH0 = 0xff; //0.1ms
	TL0 = 0x9c;
	i++;
	if(i == 200) //20ms
		i = 0;
	if(rad1 > i)
		out1 = 1;
	else
		out1 = 0;
	if(rad2 > i)
		out2 = 1;
	else
		out2 = 0;
	if(rad3 > i)
		out3 = 0xff;
	else
		out3 = 0;
}
void TimerInit(void)
{
	TMOD = 0x01;
	TH0 = 0xff;
	TL0 = 0x9c;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}