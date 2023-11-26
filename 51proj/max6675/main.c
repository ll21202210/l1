#include <reg52.h>
#include "max6675.h"
#include "tm1637.h"

u8 tm1637_sram[4];
u8 code smgduan[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	//π≤“ı
float temp;
u16 tmp;

void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 23;
	j = 153;
	k = 245;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void running()
{
	
	if(MAX6675_Check())
	{
		tm1637_sram[0] = smgduan[14];
		tm1637_sram[1] = 0;
		tm1637_sram[2] = 0;
		tm1637_sram[3] = 0;
	}
	else
	{
		temp = MAX6675_Read();
		tm1637_sram[0] = smgduan[(int)(temp / 100) % 10];
		tm1637_sram[1] = smgduan[(int)(temp / 10) % 10];
		tm1637_sram[2] = smgduan[(int)(temp) % 10];
		tm1637_sram[3] = smgduan[(int)(temp * 10) % 10];
	}
	tm1637_WriteSRAM(&tm1637_sram);
	Delay1000ms();
}

void main()
{
	MAX6675_Init();
	
	while(1)
	{
		running();
	}
}


