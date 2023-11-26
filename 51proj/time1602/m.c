#include <reg52.h>
#include <intrins.h>

#include "ds1302.h"
#include "16.h"

#define u8 unsigned char
#define u16 unsigned int

u8 hanzi[6][8] = {{0x08,0x1F,0x0E,0x0C,0x1F,0x04,0x04,0x00},//年
{0x0F,0x09,0x0F,0x09,0x0F,0x09,0x13,0x00},//月
{0x0F,0x09,0x09,0x0F,0x09,0x09,0x0F,0x00},//日
{0x0E,0x0E,0x0E,0x14,0x0E,0x04,0x1F,0x00},//星
{0x0B,0x1F,0x0B,0x0B,0x1F,0x15,0x03,0x00},//期
{0x1F,0x04,0x04,0x1F,0x04,0x0A,0x11,0x00}}; //天
u8 ddata1[16] = {'2','0','2','0',0x00,' ','0','1',0x01,'0','1',0x02,' ',' ',' ',' '};
u8 ddata2[16] = {'1','2',':','0','0',':','0','0',' ',0x03,0x04,'1',' ',' ',' ',' '};
u8 ascii[] = {'0','1','2','3','4','5','6','7','8','9'};
u8 y,m, d, h, m, s, w;

sbit kay1 = P1^3; // 模式切换
sbit kay2 = P1^4; // 加
sbit kay3 = P1^5; // 减

u8 mode = 0;// 0显示 1年设置 2月 3日 4时 5分 6秒
void delay(u16 t)
{
	while(t--)
		_nop_();
}
void getdate()
{
	u8 i,tmp,ge,shi,numb;
	for(i = 0; i < 7; i++)
	{
//		tmp = DSread(second + 0x02*i + 1);
//		se = tmp >> 4;
//		ghi = tmp & 0x0f;
//		switch(i)
//		{
//			
//		}
	}
}
void datpproc() //24小时制
{
	u8 tmp,shi,ge;
	tmp = DSread(year + 1);
	shi = tmp >> 4;
	ge = tmp & 0x0f;
	ddata1[2] = ascii[shi];
	ddata1[3] = ascii[ge];
	
	tmp = DSread(month + 1);
	shi = tmp >> 4;
	ge = tmp & 0x0f;
	ddata1[6] = ascii[shi];
	ddata1[7] = ascii[ge];
	
	tmp = DSread(day + 1);
	shi = tmp >> 4;
	ge = tmp & 0x0f;
	ddata1[9] = ascii[shi];
	ddata1[10] = ascii[ge];
	
	tmp = DSread(hour + 1);
	shi = tmp >> 4;
	ge = tmp & 0x0f;
	ddata2[0] = ascii[shi];
	ddata2[1] = ascii[ge];
	
	tmp = DSread(minute + 1);
	shi = tmp >> 4;
	ge = tmp & 0x0f;
	ddata2[3] = ascii[shi];
	ddata2[4] = ascii[ge];
	
	tmp = DSread(second + 1);
	shi = tmp >> 4;
	ge = tmp & 0x0f;
	ddata2[6] = ascii[shi];
	ddata2[7] = ascii[ge];
	
	tmp = DSread(week + 1);
	switch(tmp) //11
	{
		case 1:
			ddata2[11] = '1';
			break;
		case 2:
			ddata2[11] = '2';
			break;
		case 3:
			ddata2[11] = '3';
			break;
		case 4:
			ddata2[11] = '4';
			break;
		case 5:
			ddata2[11] = '5';
			break;
		case 6:
			ddata2[11] = '6';
			break;
		case 7:
			ddata2[11] = 0x05;
			break;
	}
}
void Display()
{
	u8 i;
	LCM16wcmd(0x80);
	for(i = 0; i < 16; i++)
	{
		LCM16wdat(ddata1[i]);
	}
	LCM16wcmd(0xc0);
	for(i = 0; i < 16; i++)
	{
		LCM16wdat(ddata2[i]);
	}
}
void LCM1602Wfont()
{
	u8 i,j;
	
	for(i = 0; i < 6; i++)
	{
		LCM16wcmd(0x40 + 8*i);
		for(j = 0; j < 8; j++)
		{
			LCM16wdat(hanzi[i][j]);
		}
		
	}
}
void main(void)
{
	LCM1602Init();
	LCM1602Wfont();
	while(1)
	{
		Display();
		datpproc();
		delay(10000);
	}
}