#include <reg52.h>
#include <intrins.h>
#include "1602.h"

sbit led = P2^4;
u8 bri = 0,tbri = 80,tcount = 0;
u8 str[16] = "Hello World!";

void Delay2ms()		//@12.000MHz
{
	unsigned char i, j;
	i = 4;
	j = 225;
	do
	{
		while (--j);
	} while (--i);
}
void T0Init()
{
	TMOD = 0x01;
	TH0 = 0xff;
	TL0 = 0x9c;
	TR0 = 1;
	EA = 0;
	ET0 = 1;
}
void Briproc()
{
	if(tbri != bri)
	{
		if(bri > tbri)
			bri --;
		else
			bri ++;
	}
}
void delay(u16 t)
{
	while(t--)
		_nop_();
}
void cgramw()
{
	u8 cgr[8][8] = {{0x00,0x0A,0x1C,0x0F,0x0A,0x0F,0x0A,0x00},
	{0x00,0x07,0x11,0x1A,0x1F,0x0A,0x06,0x00},
	{0x00,0x00,0x16,0x1F,0x16,0x10,0x1F,0x00},
	{0x00,0x0E,0x0E,0x0E,0x1B,0x0A,0x1A,0x00}};
	u8 n,m;
//	for(n = 0; n < 4; n++)
//	{
		LCM16wadd(0x00);
		Delay2ms();
		LCM16wdat(0x00);
		
//		LCM16wcmd(0x40 ); //+ 8*n
//		Delay100us();
//		for(m = 0; m<8; m++)
//		{
//			LCM16wdat(cgr[0][m]);
//			Delay100us();
//		}
		
//	}
	
}
void main(void)
{
	u8 i;
	T0Init();
	LCM1602init();
	Delay2ms();
	LCM16wcmd(dison);
	cgramw();
	while(1);
//	while(1)
//	{
//		LCM16wadd(0x00);
//		Delay2ms();
//		for(i = 0; i < 12; i++)
//		{
//			if(i == 6)
//				delay(50000);
//			LCM16wdat(str[i]);
//			if(i == 5)
//			{
//				continue;
//			}
//			delay(15000);
//			
//		}
//		LCM16wadd(0x40);
//		Delay2ms();
//		for(i = 0; i < 6; i++)
//		{
//			switch(i)
//			{
//				case 0:
//					LCM16wdat(0);
//					break;
//				case 1:
//					LCM16wdat(1);
//					break;
//				case 2:
//					LCM16wdat(' ');
//					continue;
//					break;
//				case 3:
//					LCM16wdat(2);
//					break;
//				case 4:
//					LCM16wdat(3);
//					break;
//				case 5:
//					LCM16wdat('!');
//					break;
//			}
//			delay(20000);
//			
//		}
//		delay(40000);
//		LCM16wcmd(cls);
//		delay(50000);
//		Delay100us();
//		Briproc();
//		Delay2ms();Delay2ms();Delay2ms();Delay2ms();Delay2ms();
////		LCM16wdat('A');
//	}
}

