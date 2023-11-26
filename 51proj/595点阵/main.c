#include <reg52.h>
#include <intrins.h>
typedef  unsigned int u16;
typedef	 unsigned char u8; 
typedef  unsigned long u32;

u8 code ledx[8] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
u8 code dat[48] = {0x00,0x00,0x50,0xA8,0xA8,0xA8,0xA8,0x00,
0x00,0x00,0x70,0x88,0x88,0x88,0x70,0x00,
0x00,0x00,0xB0,0x48,0x48,0x48,0x48,0x00,
0x08,0x08,0x68,0x98,0x88,0x98,0x68,0x00,
0x00,0x00,0xE0,0x10,0x70,0x90,0x68,0x00,//a
0x00,0x00,0x88,0x88,0x98,0x68,0x08,0xF0//y
};
u8 ledy[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

sbit rclk = P3^5;
sbit srclk = P3^6;
sbit ser = P3^4;
void delay(u16 i)
{
	while (i--)
		_nop_();
	
}
void w595(u8 x,u8 y)
{
// œ»–¥y ‘Ÿ–¥x
	u8 i;
	rclk = 0;
	for(i = 0; i<8; i++)
	{
		ser = y&0x1;
		y = y>>1;
		srclk = 0;
		delay(1);
		srclk = 1;
		delay(1);
		
	}
	for(i = 0; i<8; i++)
	{
		ser = x&0x1;
		x = x>>1;
		srclk = 0;
		delay(1);
		srclk = 1;
		delay(1);
	}
	rclk  =1;
	delay(10);
	
}

int main(void)
{
	u8 i;
	u32 j = 0, n =0;
	
    while(1)
	{
		for(i = 0; i<8; i++)
		{
			for(j = 0; j<8; j++)
			{
				ledy[i] = 0x80>>j;
				w595(ledx[7-i],~ledy[i] );
				if(j == 8)
					ledy[i] = 0x00;
				delay(10000);
			}
		}
		
//		for(i = 0; i<8; i++)
//		{
//			ledy[i] = dat[n*8 + i];	
//		}
//		j++;
//		if(j%100 == 0)
//		{
//			n++;
//			if(n >= 6)
//			n = 0;	
//		}
		
//		for(i = 0; i<8; i++)
//		{
//			w595(ledx[7-i],~ledy[i]);
//				
//		}	
	}
    
    
    
	
}
