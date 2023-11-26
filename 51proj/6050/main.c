#include <reg52.h>
#include "uart.h"
#include "6050.h"



u8 USART_rdata = 0;



void main()
{
	UART_Config();
	printf("stc89c52 test \n ok");
	while(1)
	{
		
	}
}
