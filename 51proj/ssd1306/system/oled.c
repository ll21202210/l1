#include "oled.h"
#include "iic.h"
#include "oled_font.h"

void OLED_EntireON(void)
{
	OLED_SendCmd(0xA5); 
}

void OLED_Init(void)
{
	
	IIC_Config();
	
	
	OLED_SendCmd(0xA8);
	OLED_SendCmd(0x3f);
	OLED_SendCmd(0xd3);
	OLED_SendCmd(0x00);
	OLED_SendCmd(0x40);
	OLED_SendCmd(0xA1);
	OLED_SendCmd(0xC8);
	OLED_SendCmd(0xDA);
	OLED_SendCmd(0x12);// diff
	OLED_SendCmd(0x81);
	OLED_SendCmd(0x7f);
	OLED_SendCmd(0xa4);
	OLED_SendCmd(0xa6);
	
	OLED_SendCmd(0xd5);
	OLED_SendCmd(0x80); //freq
	
	OLED_SendCmd(0x8d);
	OLED_SendCmd(0x14);
	OLED_SendCmd(0xaf);
	
//	OLED_EntireON();
	OLED_SetAddrMode(OLED_ADDRMODE_HORI);
	OLED_SetContrast(255);
}

/** Double byte command to select 1 out of 256 
contrast steps. Contrast increases as the value 
increases. 
*/
void OLED_SetContrast(uint8_t con)
{
	OLED_SendCmd(0x81);
	OLED_SendCmd(con);
}

void OLED_SetAddrMode(uint8_t mode)
{
	OLED_SendCmd(0x20);
	OLED_SendCmd(mode);
}

void OLED_DMAConfig(uint8_t* buffer)
{
	OLED_SetPos(0, 0);
	OLED_SendStart();
	IIC_DMAConfig(buffer, 1024);
}
void OLED_SetPos(uint8_t x, uint8_t y)
{
	OLED_SendCmd(0x21);
	OLED_SendCmd(x & 0x7f);
	OLED_SendCmd(127);
	
	OLED_SendCmd(0x22);
	OLED_SendCmd(y & 0x07);
	OLED_SendCmd(7);
}
void OLED_SendBBuffer(uint8_t *buf)
{
	uint16_t i;
	OLED_SetPos(0, 0);
	I2C_GenerateSTART(I2C1, ENABLE);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(I2C1, OLED_ADDR, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	I2C_SendData(I2C1, OLED_DATA);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	for(i = 0; i < 1024; i++)
	{
		I2C_SendData(I2C1, buf[i]);
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
		
	}
	I2C_GenerateSTOP(I2C1, ENABLE);
	
}
// 
void OLED_GRAMClear(uint8_t* buffer, uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end)
{
	if(x_start > x_end || y_start > y_end) return;
	uint8_t x;
	while(y_start <= y_end)
	{
		x = x_start;
		while(x <= x_end)
		{
			buffer[y_start * 128 + x] = 0x00;
			x++;
		}
		y_start++;
	}
}
// y 0 - 64    x 0 - 128 font w8 x h16
void OLED_ShowStr(uint8_t* buff,char* str, uint8_t x, uint8_t y)
{
	uint8_t i, pos, pos2;
	uint16_t font_addr0, font_addr1, buffer_addr0, buffer_addr1, buffer_addr2;
	while(*str != 0)
	{
		
		for(i = 0; i < 8; i++)
		{
			if(x + i < 128 )
			{
				
				font_addr0 = (*str - FONT_POS) * 16 + i;
				font_addr1 = (*str - FONT_POS) * 16 + i + 8;
				buffer_addr0 = (y / 8) * 128 + x + i;
				buffer_addr1 = (y / 8 + 1) * 128 + x + i;
				buffer_addr2 = (y / 8 + 2) * 128 + x + i;
				pos = y % 8;
				pos2 = 8 - (y % 8);
				if((y / 8) < 8)
					buff[buffer_addr0] = oled_font[font_addr0] << pos;
				if(y / 8 + 1 < 8)
					buff[buffer_addr1] = (oled_font[font_addr1] << pos) | \
				(oled_font[font_addr0] >> pos2);
				if(y / 8 + 2 < 8 && y % 8 != 0)
					buff[buffer_addr2] = oled_font[font_addr1] >> pos2;
			}
			
		}
		
		
		x += 8;
		str++;
	}
}
// len 1 - 10 
void OLED_ShowNum(uint8_t* buff,uint32_t num, uint8_t len, uint8_t x, uint8_t y)
{
	uint8_t i, pos, pos2;
	uint16_t font_addr0, font_addr1, buffer_addr0, buffer_addr1, buffer_addr2;
	uint32_t num_pow = 1;
	for(i = 0; i < len-1; i++)
	{
		num_pow *= 10; 
	}
	while(len--)
	{
		
		for(i = 0; i < 8; i++)
		{
			if(x + i < 128 )
			{
				
				font_addr0 = (((num / num_pow) % 10) + '0' - FONT_POS) * 16 + i;
				font_addr1 = (((num / num_pow) % 10) + '0' - FONT_POS) * 16 + i + 8;
				buffer_addr0 = (y / 8) * 128 + x + i;
				buffer_addr1 = (y / 8 + 1) * 128 + x + i;
				buffer_addr2 = (y / 8 + 2) * 128 + x + i;
				pos = y % 8;
				pos2 = 8 - (y % 8);
				if((y / 8) < 8)
					buff[buffer_addr0] = oled_font[font_addr0] << pos;
				if(y / 8 + 1 < 8)
					buff[buffer_addr1] = (oled_font[font_addr1] << pos) | \
				(oled_font[font_addr0] >> pos2);
				if(y / 8 + 2 < 8 && y % 8 != 0)
					buff[buffer_addr2] = oled_font[font_addr1] >> pos2;
			}
			
		}
		
		
		x += 8;
		num_pow /= 10;
	}
}

//reverse
void OLED_InverseArea(uint8_t* buffer, uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end)
{
	uint8_t x_tmp, pos;
	uint16_t buf_addr;
	while(y_start < y_end)
	{
		if(y_start % 8 != 0)
		{
			pos = y_start % 8;
			x_tmp = x_start;
			while(x_tmp <= x_end)
			{
				buf_addr = (y_start / 8) * 128 + x_tmp;
				buffer[buf_addr] ^= 0xff << pos;
				x_tmp++;
			}
			
			y_start += 8 - pos;
		}
		else if((y_end - y_start) > 8)
		{
			x_tmp = x_start;
			while(x_tmp <= x_end)
			{
				buf_addr = (y_start / 8) * 128 + x_tmp;
				buffer[buf_addr] ^= 0xff;
				x_tmp++;
			}
			y_start += 8;
		}
		else
		{
			pos = 8 - (y_end - y_start);
			x_tmp = x_start;
			while(x_tmp <= x_end)
			{
				buf_addr = (y_start / 8) * 128 + x_tmp;
				buffer[buf_addr] ^= 0xff >> pos;
				x_tmp++;
			}
			y_start += y_end - y_start;
		}
		
	}
}

