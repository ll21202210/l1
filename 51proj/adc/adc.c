#include <reg52.h>
#include <intrins.h>
#include "spi.h"

#define dig P0

sbit lsa = P1^0;
sbit lsb = P1^1;
sbit lsc = P1^2;
sbit led = P2^4;

u8 DData[8] = {0};
u8 code smgduan[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//œ‘ æ0~Fµƒ÷µ
unsigned long val;
u8 count = 0,bri = 0;

void delay(u16 i)
{
	while(i--)
		_nop_();
}
void Display(void)
{	
	u8 i;
	for(i = 0; i < 8; i++)
	{
		switch(i)
		{
			case 0:
				lsa = 0;lsb = 0;lsc = 0;
				break;
			case 1:
				lsa = 0;lsb = 0;lsc = 1;
				break;
			case 2:
				lsa = 0;lsb = 1;lsc = 0;
				break;
			case 3:
				lsa = 0;lsb = 1;lsc = 1;
				break;
			case 4:
				lsa = 1;lsb = 0;lsc = 0;
				break;
			case 5:
				lsa = 1;lsb = 0;lsc = 1;
				break;
			case 6:
				lsa = 1;lsb = 1;lsc = 0;
				break;
			case 7:
				lsa = 1;lsb = 1;lsc = 1;
				break;
		}
		dig = DData[7-i];
		delay(100);
		dig = 0x00;
	}
	
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
void Proc(void)
{
	
	val = xpt2046r(0X94); //a0 - a2 1010 0100 0xa4
	DData[0] = smgduan[val%10];
	DData[1] = smgduan[(val/10)%10];
	DData[2] = smgduan[(val/100)%10];
	DData[3] = smgduan[(val/1000)%10];
//	DData[4] = smgduan[(val/10000)%10];
//	DData[5] = smgduan[(val/100000)%10];
//	DData[6] = smgduan[(val/1000000)%10];
//	DData[7] = smgduan[(val/10000000)%10];
}
void main(void)
{
	u8 i,tbri;
	float brig;
	TimerInit();
	while(1)
	{
		Proc();
		tbri = (val*100)/8192;
//		tbri = brig ;
		
			
		for(i = 0; i< 3; i++)
		{
			if(tbri != bri)
		{
			if(tbri < bri)
				bri--;
			else
				bri++;
		}
			Display();
		}
	}
}

void T0int() interrupt 1
{
	TH0 = 0xff;
	TL0 = 0x9c;
	
	if(count == 100)
		count = 0;
	if(bri > count)
		led = 0;
	else
		led = 1;
	count++;
}