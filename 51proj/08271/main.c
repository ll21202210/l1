#include <reg52.h>

#define uint8 unsigned char
#define uint16 unsigned int

sbit led = P0^1;

void delay(uint16 t)
{
	while(t--)
		;
}

void main()
{
	uint16 i;
	while(1)
	{
		for(i = 0; i < 200; i++)
		{
			led = 1;
			delay(i*16);
			led = 0;
			delay(3200 - 16*i);
		}
		for(i = 0; i < 200; i++)
		{
			led = 0;
			delay(i*16);
			led = 1;
			delay(3200 - 16*i);
		}
	}
}

