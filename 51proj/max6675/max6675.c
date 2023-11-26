#include "max6675.h"
#include <intrins.h>


u16 SPI_Read(void)
{
	u8 i;
	u16 readdata = 0;
	SPI_CS = 0;
	for(i = 0; i < 16; i++)
	{
		readdata <<= 1;
		if(SPI_SO)
			readdata |= 0x01;
		
		
		SPI_SCL = 1;
		_nop_();_nop_();_nop_();_nop_();
		SPI_SCL = 0;
		_nop_();_nop_();_nop_();
	}
	SPI_CS = 1;
	return readdata;
}
void MAX6675_Init(void)
{
	SPI_SCL = 0;
	SPI_CS  = 1;
	SPI_SO = 1;
}
float MAX6675_Read(void)
{
	float temp;
	u16 ReceiveData;
	ReceiveData = SPI_Read();
	ReceiveData >>= 3;
	
	temp = ReceiveData * 0.25;
	return temp;
}
// 正常返回值为0 异常为1
u8 MAX6675_Check(void)
{
	u16 ReceiveData;
	ReceiveData = SPI_Read();
	if(ReceiveData & 0x04)
		return 1;
	else
		return 0;
}