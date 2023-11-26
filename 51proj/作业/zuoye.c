#include <reg52.h>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

#define KEY		P2
#define DIG		P0
sbit lsa = P1^0;
sbit lsb = P1^1;
sbit lsc = P1^2;
u8 Bri = 0,tBri = 0;
u8 data smgdata[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; // 0 到 F 
u8 DisplayData[8] = {0x5b,0x3f,0x5b,0x06,0x40,0x40,0x88,0x80};
//        
void delay(u16 t);
u8 keydect(void);
void DIGDisplay(void);

void main(void)
{
	u8 kv;
	while(1)
	{
		kv = keydect();
		if(kv >= 12)
			kv = 255;
		if(kv != 255)
		{
			Bri = 100;
			kv++;
			DisplayData[6] = smgdata[(kv/10)%10];
			DisplayData[7] = smgdata[kv%10];
			DIGDisplay();
		}
		else
			DIG = 0x00;
//		if(Bri != tBri)
//		{
//			if(Bri < tBri)
//				{
//				Bri++;
//			}
//			else
//			{
//				Bri--;
//			}
//		}
		delay(100);
		
	}
}

void DIGDisplay(void) //显示Displaydata[8] 的内容
{
	u8 i;
	for(i = 0; i < 8; i++)
	{
		switch(i) //位选
		{
			case 0:
				lsa = 0; lsb = 0; lsc = 0;break;
			case 1:
				lsa = 0; lsb = 0; lsc = 1;break;
			case 2:
				lsa = 0; lsb = 1; lsc = 0;break;
			case 3:
				lsa = 0; lsb = 1; lsc = 1;break;
			case 4:
				lsa = 1; lsb = 0; lsc = 0;break;
			case 5:
				lsa = 1; lsb = 0; lsc = 1;break;
			case 6:
				lsa = 1; lsb = 1; lsc = 0;break;
			case 7:
				lsa = 1; lsb = 1; lsc = 1;break;
		}
		DIG = DisplayData[i]; //显示及消隐
		delay(100);
		DIG = 0x00;
	}
}

u8 keydect(void)
{
	u8 KeyVal = 255;
	KEY = 0x0f;
	if(KEY != 0x0f)
	{
		delay(200);
		if(KEY != 0x0f)
		{
			
			switch(KEY)
			{
				case 0x0e:
					KeyVal = 3;break;
				case 0x0d:
					KeyVal = 2;break;
				case 0x0b:
					KeyVal = 1;break;
				case 0x07:
					KeyVal = 0;break;
				default:
					KeyVal = 255;break;
			}
			KEY = 0xf0;
			switch(KEY)
			{
				case 0xe0:
					KeyVal += 12;break;
				case 0xd0:
					KeyVal += 8;break;
				case 0xb0:
					KeyVal += 4;break;
				case 0x70:
					KeyVal += 0;break;
				default:
					KeyVal = 255;break;
			}
		}
	}
	return KeyVal;
}

void delay(u16 t)
{
	while(t--)
		_nop_();
}