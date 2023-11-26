#include <reg52.h>
#include <intrins.h>
#include <absacc.h>

void delay(unsigned int t)
{
	while(t--)
		_nop_();
}

void main(void)
{

	while(1)
	{
		XBYTE[0x8000] = 0x3f;
		delay(60000);
		XBYTE[0x8000] = 0x6b;
		delay(60000);
		delay(60000);
		delay(60000);
	}
}

