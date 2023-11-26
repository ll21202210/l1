#include <reg52.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#define u8 unsigned char
#define u16 unsigned int

u8 str[30] = "121211221221";
void UARTSendStr(u8 dat[])
{
	u8 i;
	for(i = 0; dat[i] != '\0'; i++)
	{
		TI = 0;
		SBUF = dat[i];
		while(!TI);
		TI = 0;
	}
}
void delay(u16 t)
{
	while(t--)
		_nop_();
}
void UARTInit(void)
{
	TMOD = 0x20;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	PCON &= 0x3f;
	TH1 = 0xe6;
	TL1 = 0xe6;		//波特率1200
	TR1 = 1;
	EA = 1;
	ES = 1;			//串口中断
}
void UARTInt(void) interrupt 4
{
	if(TI)
	{
//		TI = 0;
	}
	if(RI)
	{
		RI = 0;
		SBUF = SBUF;
	}
	
}

void main(void)
{
	UARTInit();
	UARTSendStr(str);
	while(1)
	{
		UARTSendStr("时间 2021.11.28");
		
		delay(10000);
	}
}
