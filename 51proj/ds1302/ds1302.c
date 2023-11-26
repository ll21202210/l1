#include "reg52.h"
#include <intrins.h>
#include <stdio.h>
#include "spi.h"

sbit led = P0^0;
u8 DisplayData[8] = {0xff,0xff,0x40,0xff,0xff,0x40,0xff,0xff};
u8 code smgduan[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ
sbit LSA = P1^3;
sbit LSB = P1^4;
sbit LSC = P1^5;
void delay(unsigned int t)
{
	while(t--)
		_nop_();
}
void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		P0=DisplayData[i];//���Ͷ���
		delay(100); //���һ��ʱ��ɨ��	
		P0=0x00;//����
	}
}
void Process()
{
	u8 i,sh,sl,s;
	
	i = spir8bit(0x81);
	sh = (i&0x70)>>4;
	sl = i&0x0f;
	s = sh*10+sl;
	DisplayData[6] = smgduan[(s/10)%10];
	DisplayData[7] = smgduan[s%10];
	
	i = spir8bit(0x83);
	sh = (i&0x70)>>4;
	sl = i&0x0f;
	s = sh*10+sl;
	DisplayData[3] = smgduan[(s/10)%10];
	DisplayData[4] = smgduan[s%10];
	i = spir8bit(0x85);
	sh = (i&0x70)>>4;
	sl = i&0x0f;
	s = sh*10+sl;
	DisplayData[0] = smgduan[(s/10)%10];
	DisplayData[1] = smgduan[s%10];
	
}
void DateInit(void)
{
	u8 i;
	i = spir8bit(0xc1);
	if(i != 0x51) // 
	{
		spiw8bit(0x8e,0x00);
		spiw8bit(0xc0,0x51);
		spiw8bit(0x80,0x38);
		spiw8bit(0x82,0x59);
		spiw8bit(0x84,0x23); //ss mm hh
		
	}
	spiw8bit(0x8e,0x80);
}	

void main(void)
{ 
	
	ce = 0;
	DateInit();
//	spiw8bit(0x80,0x00);
	while(1)
	{
		Process();
		DigDisplay();
	}
}