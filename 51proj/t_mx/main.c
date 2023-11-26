#include <reg52.h>

#define uint unsigned int
#define uchar unsigned char

sbit P1_0=P3^5;//控制音乐播放按键
sbit SPK =P3^6;//扬声器
uchar STH0,STL0;

uint code tone[] = {63777,63968,64139,64215,64360,64488,64603,64654,64750,64836,64875,64948,65012,65069,65095,65143,65186,65206,65242,65274,65301,0};
//音符对应T初值(从左到右，分别为7个低音，7个中音，7个高音，1个0)
uchar code music [] = {9,11,11,12,11,9,7,7,8,9,9,8,7,8,21,9,11,11,12,11,9,7,7,8,9,9,8,8,7,21,10,10,10,12,11,11,9,8,21,9,11,11,12,11,9,7,7,8,9,9,8,8,7,21};//音乐的琴谱,需要对照tone

uchar code rhythm[] = {4,4,6,2,4,4,4,2,2,4,4,4,4,8,8,4,4,6,2,4,4,4,2,2,4,4,4,4,8,8,10,10,4,6,10,4,4,8,8,4,4,6,2,4,4,4,2,2,4,4,4,4,8,8,};//控
void delay(uint time)//延时子函数
{
	uint m = 0;
	for(;time >0;time--)
		for(m = 0;m < 125;m++);
}
void int_srv1( ) interrupt 1//中断函数
{
	TH0 =STH0;//装载计数初值
	TL0 = STL0;
	SPK =~SPK;//P1.0反向
}
void main(void)
{
	uchar i;
	TMOD=0X01;//T0方式1
	IE = 0x82;//开启总中断和相应的中断源中断
	while(1)
	{
		if(P1_0==0)//按下播放按钮
		{
			for(i=0;i <54;i++) //i的值和music应该一致
			{
				if(music[i]==music[i +1])//检测相邻的音符是否一致
				{
					TR0=1;//开启T0
					STH0=tone[music[i]]/256;//定时器高八位
					STL0=tone[music[i]]%256;//定时器低八位
					delay(70 *rhythm[i]);//延时,从而让声音按照一定的规律发声
					SPK = 1;
					TR0=0;//关闭T0
					delay(15);
				}
				else
				{
					TR0 = 1;
					STH0 = tone[music[i]] /256;
					STL0= tone[music[i]] %256;
					delay(70 * rhythm[i]);
				}
			}
		}
		TR0 = 0;
	}
}
