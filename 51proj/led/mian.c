#include <reg52.h>
#include <intrins.h>


sbit led = P1^0;


void delay(unsigned int time)
{
	while(time--);
}
void main()
{
	
	while(1)
	{
		delay(10000);
		led = ~led;
	}
	
	
	
}


