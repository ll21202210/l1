#ifndef __UART_H_
#define __UART_H_

#include <reg52.h>
#include <stdio.h>

#define u8 unsigned char
#define u16 unsigned int



void UART_Config(void);
void UART_Sendchar(u8 ch);





#endif /** __UART_H_ */
