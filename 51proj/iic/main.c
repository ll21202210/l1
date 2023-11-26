#include <reg52.h>
#include <intrins.h>
#include "iic.h"

//u8 code sduan[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	//共阴

sbit intk0 = P3^2;
sbit intk1 = P3^3;

void w8b(u8 addr,u8 dat)
{
	iicstart();
	iics8bit(0x78); //设备地址 
	iicwait();
	iics8bit(addr); //存储地址
	iicwait();
	iics8bit(dat);
	iicwait();
	iicstop();
}

u8 r8b(u8 addr)
{
	u8 dat;
	iicstart();
	iics8bit(0x78); //设备地址， 
	iicwait();
	iics8bit(addr); //存储地址
	iicwait();
	iicstart();
	iics8bit(0xa1); //设备地址， 读取
	iicwait();
	
	dat = iicread8bit();
	iicresp(1); //非应答， 结束读取
	iicstop();
	return dat;
}

void delay(u16 i)
{
	while(i--)
		_nop_();
}


void main(void)
{
//	w8b(0x00, 0x39);
//	w8b(0x01, 0x5e);
	EX0 = 1;
	EX1 = 1;
	EA = 1;
	IT0 = 1;
	IT1 = 1;
	while(1)
		{
//			P0 = 0;
//			delay(60000);
//			w8b(0x01, 0x5e);
//			P0 = 1;
//			delay(60000);
//			P0 = r8b(0x00);
//			delay(60000);
		}
}


void int0(void) interrupt 0
{
	delay(100);
	if(intk0 == 0)
	w8b(0x32, 0x31);
}

void int1(void) interrupt 2
{
	delay(100);
	if(intk1 == 0)
	w8b(0x51,0x52 );
}