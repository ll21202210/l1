#include <reg52.h>
#include <intrins.h>
#define u8 unsigned char
#define u16 unsigned int

u16 TK_val = 0;
u16 TK_tval = 0;
u8 TKEY_Flag = 0;
u8 kes = 0;
u8 dutyup = 0;
u16 press_cnt = 0;
u8 pwm_duty = 100;

sfr IE_EX = 0xe8;
sfr P1_MOD_OC = 0x92;
sfr P1_MOD_PU = 0x93;
sfr PIN_FUNC = 0xc6; // gpio af reg
// 按键
sfr TKEY_CTRL = 0xc3;
sfr TKEY_DATH = 0xc5;
sfr TKEY_DATL = 0xc4;


// pwm
sfr PWM_CK_SE = 0x9e;
sfr PWM_CTRL = 0x9d;
sfr PWM_DATA1 = 0x9c;



sbit P30 = P3^0; // led

void delay(u16 time)
{
	while(time--)
		_nop_();
}
void Init_TK(void)
{
	P1_MOD_OC = 0xfd;
	P1_MOD_PU = 0xfd;
	TKEY_CTRL |= 0x12; // p11
	IE_EX |= 0x02; 
	EA = 1;
	
}
void Init_PWM(void)
{
	PWM_CK_SE = 1;
	PWM_CTRL = 0x04;
	PWM_DATA1 = 0;
	
}
void addduty(void)
{
	if(PWM_DATA1 < 255)
		PWM_DATA1++;
}
void decduty(void)
{
	if(PWM_DATA1)
		PWM_DATA1--;
}
void key_event(u8 keyflag)
{
	if(keyflag == 1)
	{
		if(kes == 0)
		{
			kes = 1;
			if(dutyup)
				dutyup = 0;
			else
				dutyup = 1;
			
		}
		else if(kes == 1)
		{
			if(press_cnt < 200)
			{
				press_cnt++;
			}
			else
			{
				if(dutyup)
				{
					addduty();
				}
				else
				{
					decduty();
				}
			}
		}
	}
	else if(keyflag == 0 && (press_cnt < 200 && press_cnt > 0))
	{
		if(PWM_DATA1)
		{
			pwm_duty = PWM_DATA1;
			PWM_DATA1 = 0;
		}
		else
			PWM_DATA1 = pwm_duty;
		kes = 0;
		press_cnt = 0;
	}
	else
	{
		kes = 0;
		press_cnt = 0;
	}
}
void main(void)
{
	
	Init_TK();
	Init_PWM();
	
	while(1)
	{
		key_event(TKEY_Flag);
		delay(3000);
	}
}

void IRQ_TK(void) interrupt 7
{
	TK_tval = TKEY_DATL;
	TK_tval |= (TKEY_DATH & 0xef) << 8; // 
	if(TK_val == 0)
	{
		//init
		TK_val = TK_tval;
		TKEY_CTRL |= 0x12;
		return;
	}
	if(TK_tval >=  TK_val) // 变大 按键松开
	{
		if((TK_tval - TK_val) > 2000)
		{
			TKEY_Flag = 0;
		}
	}
	else if(TK_tval <  TK_val) // 变小 按键按下
	{
		if((TK_val - TK_tval) > 2000)
		{
			TKEY_Flag = 1;
		}
	}
	TK_val = TK_tval;
	TKEY_CTRL |= 0x12; // p11
}

