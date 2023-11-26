#include "uart.h"

sfr AUXR = 0x8e;
extern u8 USART_rdata;

void UART_Config(void)
{
	SCON = 0x50;
	AUXR = 0x00;
	TMOD = 0x20;
	TL1 = 0xFD;		//设置定时初始值
	TH1 = 0xFD;
	TR1 = 1;
	EA = 1;
	ES = 1;
}

char putchar(char c)
{
	UART_Sendchar(c);
	return c;
}
void UART_Sendchar(u8 ch)
{
	SBUF = ch;
	while(!TI);
	TI = 0;
}
void IRQ_UART(void) interrupt 4
{
	if(RI)
	{
		RI = 0;
	}
}
