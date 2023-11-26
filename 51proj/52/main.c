#include <reg52.h> 
#include <intrins.h> 

typedef unsigned char u8;
typedef unsigned int u16;
sbit a = P1^1;

void delay(u16 tim)
{
	while(tim--)
	_nop_();
}

int main(void)
{
	u16 i;
	while(1)
	{
		for(i = 0; i < 1000; i+= 10)
		{
			a = 1;
			delay(i);
			a = 0;
			delay(1000 - i);
		}
		a = 1;
		delay(60000);
		for(i = 0; i < 1000; i+= 10)
		{
			a = 1;
			delay(1000 - i);
			a = 0;
			delay(i);
		}
	}
}


