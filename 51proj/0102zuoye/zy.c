#include "reg52.h"
#include "intrins.h"
#define u8 unsigned char
#define u16 unsigned int
#define DIG P0

sbit lsa = P2^0;
sbit lsb = P2^1;
sbit lsc = P2^2;
sbit beep = P2^3; 

u8 code smgduan[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
u8 ddata[8] = {0x3f,0x3f,0x40,0x00,0x00,0x40,0x00,0x00};
u8 cout = 0;
u16 time = 0;

void Delay500us()		//不是500us
{
	unsigned char i;
	_nop_();
	i = 50;
	while (--i);
}

void TimerInit(void)
{
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0xb0;
    TR0 = 1;
    EA = 1;
    ET0 = 1;
    
}
void proc()
{
    //时
    ddata[3] = smgduan[(((time/3600)%24)/10)%10];
    ddata[4] = smgduan[((time/3600)%24)%10];
    //分
    ddata[3] = smgduan[(((time/60)%60)/10)%10];
    ddata[4] = smgduan[((time/60)%60)%10];
    //秒
    ddata[6] = smgduan[((time%60)/10)%10];
    ddata[7] = smgduan[(time%60)%10];
    
}
void Display()
{
    u8 i;
    for(i = 0; i < 8; i++)
    {
        switch(i)
        {
            case 0:
               lsa = 0; lsb = 0; lsc = 0; 
                break;
            case 1:
               lsa = 1; lsb = 0; lsc = 0; 
                break;
            case 2:
               lsa = 0; lsb = 1; lsc = 0; 
                break;
            case 3:
               lsa = 1; lsb = 1; lsc = 0; 
                break;
            case 4:
               lsa = 0; lsb = 0; lsc = 1; 
                break;
            case 5:
               lsa = 1; lsb = 0; lsc = 1; 
                break;
            case 6:
               lsa = 0; lsb = 1; lsc = 1; 
                break;
            case 7:
               lsa = 1; lsb = 1; lsc = 1; 
                break;
        }
        DIG = ddata[i];
        Delay500us();
        DIG = 0x00;
    }
    
}
void beepc()
{
    if(time >= 60 && time < 70) //响十秒
    {
        beep = ~beep;
    }
    else
    {
        beep = 1;
    }
}

void main(void)
{
    TimerInit();
    while(1)
    {
        
        proc();
        Display();
        beepc();
    }
    
}
void int1(void) interrupt 1
{
    TH0 = 0x3c;
    TL0 = 0xb0;
    cout++;
    if(cout >= 20)
    {
        cout = 0;
        time++;
    }
}