#ifndef _DS1302_H_
#define _DS1302_H_

#include <reg52.h>
#include <intrins.h>
#define u8 unsigned char
#define u16 unsigned int
/** 写指令 读取加1 */
#define second 	0x80
#define minute 	0x82
#define hour 	 	0x84
#define day 		0x86
#define month 	0x88
#define week		0x8a
#define year 		0x8c
/** 功能设置 读取加1*/
#define writeprotect 			0x8e
#define charge						0x90
#define clockf 						0xbe
#define ram0 							0xc0 //0~30依次加0x02
#define ramf							0xfe

sbit ce = P1^0;
sbit clk = P1^1;
sbit dat = P1^2;

u8 DSread(u8 cmd);
void DSwirte(u8 cmd,u8 data1);
void DS1302Init();


#endif /** _DS1302_H_ */