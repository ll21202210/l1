#include "18b20.h"
#include <reg52.h>
#include <intrins.h>

unsigned char code smgd[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
sbit lsa = P1^1;
sbit lsb = P1^2;
sbit lsc = P1^3;
void delay(u16 t);
void smgdisplay(long dat);
void main(void)
{
	long tem;
	
	while(1)
	{
		tem = dsmeasuretemp();
//		tem = 32;
		smgdisplay(tem);
	}
	
}

void smgdisplay(long dat)
{
	u8 i;
	u8 ddat[8] = {0};
	if(dat<0)
	{
		ddat[3] = 0x40; //正负显示
		dat = ~dat + 1; //取绝对值
	}
	ddat[0] = smgd[dat%10];
	ddat[1] = smgd[(dat/10)%10];
	ddat[1] |= 0x80;
	ddat[2] = smgd[(dat/100)%10];
//	ddat[3] = smgd[(dat/1000)%10];
//	ddat[4] = smgd[(dat/10000)%10];
//	ddat[5] = smgd[(dat/100000)%10];
//	ddat[6] = smgd[(dat/1000000)%10];
	for(i = 0; i<8; i++)
	{
		switch(i%8)
		{
			case 0:
				lsa = 0;lsb = 0; lsc = 0;
				P0 = ddat[7];
				break;
			case 1:
				lsa = 0;lsb = 0; lsc = 1;
				P0 = ddat[6];
				break;
			case 2:
				lsa = 0;lsb = 1; lsc = 0;
				P0 = ddat[5];
				break;
			case 3:
				lsa = 0;lsb = 1; lsc = 1;
				P0 = ddat[4];
				break;
			case 4:
				lsa = 1;lsb = 0; lsc = 0;
				P0 = ddat[3];
				break;
			case 5:
				lsa = 1;lsb = 0; lsc = 1;
				P0 = ddat[2];
				break;
			case 6:
				lsa = 1;lsb = 1; lsc = 0;
				P0 = ddat[1];
				break;
			case 7:
				lsa = 1;lsb = 1; lsc = 1;
				P0 = ddat[0];
				break;
		}
		delay(100);
		P0 = 0x00;
	}
}

void delay(u16 t)
{
	while(t--)
		_nop_();
}
