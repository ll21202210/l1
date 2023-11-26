#include <reg52.h>
#include <intrins.h>

#define u8 unsigned char
#define u16 unsigned int
#define dig P0
/**
138 的 abc 插 p1 0，1，2
p0 接数码管
*/

unsigned char code smgduan[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	//共阴
u8 ddata[8] = {0x00,0x3f,0x3f,0x40,0x3f,0xbf,0x3f,0x3f};

sbit key1 = P2^0;
sbit key2 = P2^1;
sbit key3 = P2^2;

u16 dms;
u8 trun = 0,minute,td = 1,kdown = 0;

void delay(u16 t)
{
	while(t--)
		_nop_();
}
void TimerInit(void)
{
	TMOD = 0x10;
	EA = 1;
	ET1 = 1;
	TR1 = 1;
	TH1 = 0Xd8;
	TL1 = 0Xf0;
}

void KeyScan(void)
{
	
	if(key1 == 0)
	{
		delay(50);
		if(key1 == 0 && kdown == 0)
		{
			if(trun == 1)
				trun = 0;
			else
				trun = 1;
		}
	}
	if(key2 == 0)
	{
		delay(50);
		if(key2 == 0 && kdown == 0)
		{
			if(td == 1)
				td = 0;
			else
				td = 1;
		}
	}
	if(key3 == 0)
	{
		delay(50);
		if(key3 == 0 && kdown == 0)
		{
			trun = 0;
			dms = 0;
			minute = 0;
			td = 1;
		}
	}
	if(!key1 || !key2 || !key3)
		kdown = 1;
	else
		kdown = 0;
}
void ddatproc()
{
	ddata[7] = smgduan[dms%10];// 百分位
	ddata[6] = smgduan[(dms/10)%10];// 十分位
	ddata[5] = smgduan[(dms/100)%10]; //个
	ddata[4] = smgduan[(dms/1000)%10]; // 十
	ddata[5] |= 0x80; // 小数点
	ddata[2] = smgduan[minute%10];
	ddata[1] = smgduan[(minute/10)%10];
}
void Display(void)
{
	u8 i; 
	for(i = 0; i < 8; i++)
	{
		P1 &= 0xf8;
		P1 |= i;
		dig = ddata[i];
		delay(20);
		dig = 0x00;
	}
}

void main(void)
{
	dms = 0;
	minute = 0;
	TimerInit();
	while(1)
	{
		KeyScan();
		if(td)
		ddatproc();
		Display();
		
	}
}
void irq3(void) interrupt 3
{
	TH1 = 0Xd8;
	TL1 = 0Xf0;
	if(trun)
	{
		dms ++;
		if(dms == 6000)
		{
			dms = 0;
			minute++;
		}
	}
}

