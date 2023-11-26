#include <reg52.h>
#include <intrins.h>

#define u16 unsigned int
#define u8 unsigned char
void delay(u8 time);
sbit beep = P1^0;
u8 smgd[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//ÏÔÊ¾0~FµÄÖµ
void main(void)
{
	u16 i = 0, j = 0, beepon = 0;
	while(1)
	{
		P0 = ~smgd[j];
		i++;
		if(i == 2000)
		{
			i = 0;
		}
		if(i%600 == 0)
		{
			j++;
			if(j == 17)
			{
				j = 0;
			}
		}
		
		if(j>= 10)
			beepon = 1;
		else
			beepon = 0;
		if(beepon)
		{
			beep = 0;
			delay(5);
			beep = 1;
			delay(5);
		}else
		delay(10);
	}
	
	
	
}

void delay(u8 time)
{
	while(time--)
		_nop_();
}



