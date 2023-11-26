#include "tm1637.h"

void Delay5us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 12;
	while (--i);
}

void IIC_Start(void)
{
	IIC_SDA = 1;
	IIC_SCL = 1;
	Delay5us();
	IIC_SDA = 0;
	Delay5us();
	IIC_SCL = 0;
}
void IIC_Stop(void)
{
	IIC_SCL = 0;
	IIC_SDA = 0;
	Delay5us();
	IIC_SCL = 1;
	Delay5us();
	IIC_SDA = 1;
	
}
void IIC_Send(u8 dat)
{
	u8 i;
	for(i = 0; i < 8; i++)
	{
		IIC_SCL = 0;
		if(dat & 0x01)
			IIC_SDA = 1;
		else
			IIC_SDA = 0;
		dat >>= 1;
		IIC_SCL = 1;
		Delay5us();
	}
	//ack
	IIC_SCL = 0;
	IIC_SDA = 1;
	Delay5us();
	IIC_SCL = 1;
	Delay5us();
	IIC_SCL = 0;
}


void tm1637_WriteSRAM(u8 *buffer)
{
	u8 i;
	IIC_Start();
	IIC_Send(0x40);
	IIC_Stop();
	
	IIC_Start();
	IIC_Send(0xc0);
	for(i = 0; i < 4; i++)
	{
		IIC_Send(*buffer);
		buffer++;
	}
	IIC_Stop();
	
	IIC_Start();
	IIC_Send(0x88);
	IIC_Stop();
}
