#ifndef __18B20_HEAD_FILE_
#define _18B20_HEAD_FILE_

#include <reg52.h>
#include <intrins.h>

#define u8 unsigned char
#define u16 unsigned int 
	
sbit dio = P1^0;

void Delay45us();
void dsinit(void);
void dsw8bit(u8 dat);
u8 dsr8bit(void);
void Delay550us();
int dsmeasuretemp(void);


#endif