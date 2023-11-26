#include <reg52.h>
#include <intrins.h>
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

sfr AUXR = 0x8e;
#define s	300
sbit ina = P0^0;
sbit inb = P0^1;
sbit led  = P1^0;
u8 ina_last, inb_last;
u8 pwm_duty = 10; // ×ó

void TimerInit()
{
	TMOD = 0x02;
	TH0 = 156;
	TL0 = 156; // 100us
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}
void delay(u32 t)
{
	while(t--)
	_nop_();
}
char Scan()
{
	char Scanv = 0;
	if(ina != ina_last)
	{
		if(ina == 1)
		{
			if(inb == 1 && inb_last == 0)
			{
				Scanv = 1;
			}
			else if(inb == 0 && inb_last == 1)
			{
				Scanv = -1;
			}
			else if(inb == inb_last && inb == 1)
			{
				Scanv = -1;
			}
			else if(inb == inb_last && inb == 0)
			{
				Scanv = 1;
			}
		}
		else
		{
			if(inb == 1 && inb_last == 0)
			{
				Scanv = -1;
			}
			else if(inb == 0 && inb_last == 1)
			{
				Scanv = 1;
			}
			else if(inb == inb_last && inb == 1)
			{
				Scanv = 1;
			}
			else if(inb == inb_last && inb == 0)
			{
				Scanv = -1;
			}
		}
		ina_last = ina;
		inb_last = inb;
	}
	return Scanv;
}
void main(void)
{
	TimerInit();
	ina_last = ina;
	inb_last = inb;
	while(1)
	{
		delay(10);
		switch(Scan())
		{
			case -1:
				if(pwm_duty > 5)
					pwm_duty--;
				break;
			case 1:
			if(pwm_duty < 25)
				pwm_duty++;
				break;
			case 0:
				break;
			default:
				break;
		}
	}
}
void IRQ_T0() interrupt 1
{
	static u8 i = 0;
	if(i < 25)
		i++;
	else
		i = 0;
	if(i < (pwm_duty))
		led = 1;
	else
		led = 0;
	
}

