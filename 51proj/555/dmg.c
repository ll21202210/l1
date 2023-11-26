#include <intrins.h>
#include <reg52.h>
#define u8 unsigned char
#define u16 unsigned int
u8 ddata[8] = {0};

unsigned char bdata chdata;
sbit chdata1 = chdata^0;
sbit chdata2 = chdata^1;
sbit chdata3 = chdata^2;
sbit CHA = P1^0;
sbit CHB = P1^1;
sbit CHC = P1^2;

u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
u16 freq = 85, tcount = 0, tmpfreq = 0;
void delay(u16 t)
{
	while(t--);
}
	
void Display()
{
	u8 i;
	for(i = 0; i < 8; i++)
	{
		chdata = i;
		CHA = chdata1;CHB = chdata2;CHC = chdata3; //数码管位选
		P0 = ddata[i];
		delay(100);
		P0 = 0x00; //段选 消隐
	}
}
void Tinit()
{
	TMOD = 0x51;
	TH0 = 15536 >> 8;
	TL0 = 15536 & 0xff;
	TH1 = 0;
	TL1 = 0;
	EA = 1;
	ET0 = 1;
	ET1 = 1;
	TR0 = 1;
	TR1 = 1;
}
void Run()
{
	ddata[7] = smgduan[(freq) % 10];
	ddata[6] = smgduan[(freq / 10) % 10];
	ddata[5] = smgduan[(freq / 100) % 10];
	ddata[4] = smgduan[(freq / 1000) % 10];
	ddata[3] = smgduan[(freq / 10000) % 10];
}
sbit lll = P3^3;
void main()
{
	Tinit();
	
	while(1)
	{
		Display();
		Run();
		lll = ~lll;
	}
}
void IRQ_T0() interrupt 1
{
	TH0 = 15536 >> 8;
	TL0 = 15536 & 0xff;
	if(tcount < 20)
		tcount++;
	else
	{
		tcount = 0;
		freq = TH1 << 8;
		freq += TL1;
		freq += tmpfreq;
		tmpfreq = 0;
		TH1 = 0;
		TL1 = 0;
	}
}
void IRQ_T1() interrupt 3
{
	tmpfreq += 65536;
}


