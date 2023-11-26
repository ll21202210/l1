#include <reg52.h>
#include <intrins.h>
typedef unsigned int u16;
typedef unsigned char u8;
u16 time = 0;
u16 tt = 0;
sbit clk = P1^0;
sbit dio = P1^1;
sbit tri = P1^3;
sbit ssss= P3^2;

unsigned char code sduan[16] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};	//¹²Òõ

u8  code smgd[12] = {0x3f,0x06,0x5b,0x4f,0x66,\
0x6d,0x7d,0x07,0x7f,0x6f,0x5f,0x38};
u8 da[4] = {0x3f,0x06,0x5f,0x38};//4wei 
//sbit kk = P3^2;

void delay(u16 ti)
{
	while(ti--)
		_nop_();
		
}


void tmst(void)
{
	clk = 1;
	dio  =1;
	delay(2);
	dio = 0;
	delay(2);
	
}
void tmstp(void)
{
	clk = 0;
	delay(2);
	dio = 0;
	delay(2);
	clk = 1;
	delay(2);
	dio = 1;
	delay(2);
}
void tmack(void)
{
	u16 ii = 0;
	clk = 0;
	dio = 1;
	delay(5);
	while(dio)
		{
			ii++;
			if(ii > 100)
				break;
		}
	clk = 1;
	delay(5);
	clk = 0;
}
void tmwbyte(u8 daa)
{
	u8 i;
	for(i = 0; i<8; i++)
	{
		clk = 0;
		
		dio = daa & 0x01;
		daa = daa >>1;
		delay(5);
		clk = 1;
		delay(5);
	}
	
}
void smgw(void)
{
	u8 i;
	tmst();
	tmwbyte(0x40);
	tmack();
	tmstp();
	
	tmst();
	tmwbyte(0xc0);
	tmack();
	for( i = 0; i< 4; i++)
	{
		tmwbyte(da[i]);	
		tmack();
	}
	tmstp();
	
	tmst();
	tmwbyte(0x88); //0x88 - 0x8f °µ - ÁÁ
	tmack();
	tmstp();
}

void itinit1(void)
{
	TMOD = 0x09;
	TL0 = 0x0;
	TH0  = 0x0;
//	ET0 = 1;
//	EA = 1;
	TR0 = 1;
	
	
}

int main(void)
{
	unsigned long int ss = 0;
	P0 = 0;
	tri = 0;
//	ssss = 0;
	itinit1();
	while(1)
	{
		
		TL0 = 0x0;
		TH0  = 0x0;
		tri = 1;
		delay(17);
		tri = 0;
		delay(5000);
		ss = TL0;
		ss |= TH0<<8;
		ss = (ss*17)/ 1000 ; //   ss/340 /1000000
		P0 = sduan[ss%10];
		da[3] = smgd[ss%10];
		da[2] = smgd[(ss/10)%10];
		da[1] = smgd[(ss/100)%10];
		da[0] = smgd[(ss/1000)%10];
		smgw();
		delay(5000);
	}
	
	
}

//void keyintr(void) interrupt 1
//{
//	time ++;
//	TL0 = 0x18;
//	TH0  = 0xfc;
//	if(time == 1000)
//		time = 0,key = ~key,tt++;
//	
//}
