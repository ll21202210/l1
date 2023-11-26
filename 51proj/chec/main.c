#include <reg52.h>
#include <intrins.h>
#include "main.h"

u8 tim_cnt = 0;
u8 pwm_dutya = 0;
u8 pwm_dutyb = 0;
u8 inl_state, inr_state;
u8 count = 0;


sbit pwma = P0^1;
sbit pwmb = P0^0;
sbit ma1 = P0^4;
sbit ma2 = P0^5;
sbit mb1 = P0^2;
sbit mb2 = P0^3;
sbit inl = P2^0;
sbit inm = P2^1;
sbit inr = P2^2;

void main()
{
	SysInit();
	
	
	while(1)
	{
		scan();
		
	}
}
void delay(u16 time)
{
	while(time--);
}
void SysInit(void)
{
	TMOD = 0x02;
	TH0 = 156;
	TL0 = 156;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	inl_state = inl;
	inr_state = inr;
}
void scan()
{
	if((inl == 1) && (inr == 1))
	{
		if(count == 0)
		{
			Set_moto(10, 10, 1);
			count++;
			delay(10000);
		}
		else if(count == 1)
		{
			count++;
			Set_moto(2, 10, 1);
			delay(10000);
		}
		else if(count == 2)
		{
			count++;
			Set_moto(2, 10, 1);
			delay(10000);
		}
		else
		{
			Set_moto(0, 0, 1);
		}
		
	}
	else if(inr == 1)
	{
		Set_moto(0, 10, 1);
	}
	else if(inl == 1)
	{
		Set_moto(10, 0, 1);
	}
	else
	{
		Set_moto(6, 6, 1);
	}
}


void Set_moto(u8 dutya, u8 dutyb, u8 runmode)
{
	if(dutya <= 10)
		pwm_dutya = dutya;
	if(dutyb <= 10)
		pwm_dutyb = dutyb;
	switch(runmode)
	{
		case 1:  //Ç°½ø
			ma1 = 0;
			ma2 = 1;
			mb1 = 0;
			mb2 = 1;
			break;
		case 2:
			ma1 = 1;
			ma2 = 0;
			mb1 = 1;
			mb2 = 0;
			break;
	}
}
void TRQ_T0() interrupt 1
{
	if(tim_cnt < 10)
		tim_cnt++;
	else
		tim_cnt = 0;
	if(pwm_dutya > tim_cnt)
		pwma = 1;
	else
		pwma = 0;
	if(pwm_dutyb > tim_cnt)
		pwmb = 1;
	else
		pwmb = 0;
	
}



