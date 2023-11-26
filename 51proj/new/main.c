#include <reg52.h>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;
typedef unsigned long u32; 

//u8 code smd[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
//					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

sbit la = P1^0;
sbit lb = P1^1;
sbit lc = P1^2;

void delay(u16 t)
{
	while(t--);
}
void main(void)
{
	u8 j = 0,i;
	u8 temp = 0x3f; //控制显示1357位显示的值
	while(1)
	{
		j++;
		if(j == 255)  //延时
		{
			j = 0;
			if(temp == 0x3f)
				temp = 0x06; //设置显示1
			else
				temp = 0x3f; //设置显示0
		}
		for(i = 0; i<8; i++) // 数码管显示
		{
			switch(i)
			{
					case 0 :
						la = 0,lb = 0,lc = 0; 
						P0 = temp;
						break;
					case 1 :
						la = 0,lb = 0,lc = 1;
						P0 = 0x00;
						break;
					case 2 :
						la = 0,lb = 1,lc = 0;
						P0 = temp;
						break;
					case 3 :
						la = 0,lb = 1,lc = 1;
						P0 =0x00;
						break;
					case 4 :
						la = 1,lb = 0,lc = 0;
						P0 = temp;
						break;
					case 5 :
						la = 1,lb = 0,lc = 1;
						P0 = 0x00;
						break;
					case 6 :
						la = 1,lb = 1,lc = 0;
						P0 = temp;
						break;
					case 7 :
						la = 1,lb = 1,lc = 1;
						P0 = 0x00;
						break;
				}
				
				delay(100); //延时显示
				P0 = 0x00; //消隐
			}
	}
}

