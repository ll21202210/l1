#include <reg52.h>
#include <intrins.h>
#define u8 unsigned char
#define u16 unsigned int
#define smg P0
sbit rw = P3^2; //int0
sbit lsa = P1^0;
sbit lsb = P1^1;
sbit lsc = P1^2;
sbit beep = P1^3;

u8 ddata[8] = {0};
u8 code smgduan[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
u8 rdat[4] = {0};
void Delay100us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	i = 47;
	while (--i);
}


void smgw(void)
{
	u8 i;
	for(i = 0; i < 8; i++)
	{
		switch(i)
		{
			case 0:
				lsa = 0; lsb = 0; lsc = 0; break;
			case 1:
				lsa = 0; lsb = 0; lsc = 1; break;
			case 2:
				lsa = 0; lsb = 1; lsc = 0; break;
			case 3:
				lsa = 0; lsb = 1; lsc = 1; break;
			case 4:
				lsa = 1; lsb = 0; lsc = 0; break;
			case 5:
				lsa = 1; lsb = 0; lsc = 1; break;
			case 6:
				lsa = 1; lsb = 1; lsc = 0; break;
			case 7:
				lsa = 1; lsb = 1; lsc = 1; break;
		}
		smg = ddata[7 - i];
		Delay100us();Delay100us();
		smg = 0x00;
	}
}
void proc(void)
{
	u8 temp,i;
	for(i = 0; i < 4; i++)
	{
		temp = rdat[i];
		ddata[7 - 2*i] = smgduan[(temp/16)];
		ddata[6 - 2*i] = smgduan[(temp)%16];
		
	}	
	
	
	
}
void initint()
{
	EA = 1;
	EX0 = 1;
	IT0 = 0;
}

void main(void)
{
	initint();
	while(1)
	{
		smgw();
		proc();
		if(rdat[2] == 0x46)
		{
			beep = 0;
			Delay100us();Delay100us();Delay100us();Delay100us();
			beep = 1;
			
		}
	}
}

void int0(void) interrupt 0
{
	u8 t ,b,i;
	EA = 0;
	t = 0;
	while(!rw && t < 100)
	{
		Delay100us();
		t++;
		
	}//低电平等待
	if(t > 90)
		return;
	t = 0;
	while(rw && t < 55)
	{
		Delay100us();
		t++;
		
	}//低电平等待
	if(t > 45)
		return;
	for(b = 0; b < 4; b++)
	{
		for(i = 0; i<8; i++)
		{
			rdat[b] >>= 1;
			t = 0;
			while(!rw && t < 7)
			{
				Delay100us();
				t++;
			}//低电平等待
			if(t == 0)
				return;
			t = 0;
			while(rw && t < 18)
			{
				Delay100us();
				t++;
			}
			if(t == 0)
				return;
			if(t>10)
				rdat[b] |= 0x80; //
			else
				rdat[b] &= ~0x80;
			
		}
	}
	EA = 1;
	
}
