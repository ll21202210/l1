#include <reg52.h>
#include <intrins.h>

#define u8 unsigned char
#define u16 unsigned int

sbit cs = P1^0;
sbit clk = P1^1;
sbit din = P1^2;
u8 i;

u8 dacdata;
u8 outenable = 1;
void delay(u16 t)
{
	while(t--)
	_nop_();
}
void SerInit()
{
	SM1 = 1;
	SM0 = 0;
	REN = 1;
	PCON |= 0x80;		//使能波特率倍速位SMOD
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD = 0x20;
	TH1 = 0xf3;
	TL1 = 0xf3;
	TR1 = 1;
	EA = 1;
	ES = 1;
	
}

void main(void)
{
	u16 ii;
	SerInit();
	dacdata = 0xff;
	ii = 1;
	while(1)
	{
//			clk = 0;
//			_nop_();
//			cs = 0;
//			_nop_();
//			for(i = 0; i < 12; i++)
//			{
//				din = dacdata>>7;
//				_nop_();
//				clk = 1;
//				dacdata <<=1;
//				clk = 0;
//			}
//			cs = 1;
//			clk = 1;
//			outenable = 0;
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//			Delay14us();Delay14us();
//		}
//		if(ii == 1)
//			dacdata = 0x00,ii = 0;
//		else
//			dacdata = 0xff, ii = 1;
	}
}
void Serinterrupt(void) interrupt 4
{
	if(RI)
	{
//		outenable = 1;
		dacdata = SBUF;
		REN = 0;
		din = 0;
		while(1)
		{
			_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
			if(dacdata > 8)
				dacdata -= 8;
			else
				break;
		}
		din = 1;
		RI = 0;
		REN = 1;
	}
	if(TI)
	TI = 0;
}

