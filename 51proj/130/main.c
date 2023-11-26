#include "iic.h"

sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sbit P20 = P2^0;
sbit P21 = P2^1;
u8 code buff[20] = {0xff, 0x0f, 0xff, 0xff,0xff,0,0,0};
void delay(u16 time)
{
	while(time--);
}
int main()
{
	unsigned long i = 0;
	P2M0 = 0x03;
	P2M1 = 0x00;
	P20 = 0;
	P21 = 1;
	delay(10000);
	SSD1306_Init();
	SSD1306_Clear();
	
//	ltyd();
	SSD1306_DrawCh(6 + '0', 6, 1);
	SSD1306_SetCon(255);
	while(1)
	{
		SSD1306_SetCon(1);
		delay(60000);delay(60000);delay(60000);delay(60000);delay(60000);
		SSD1306_SetCon(10);
		delay(60000);delay(60000);delay(60000);delay(60000);delay(60000);
//		SSD1306_WriteDATA(buff, 1);
//		SSD1306_DrawCh((i / 100) % 10 + '0', 4, 0);
//		SSD1306_DrawCh((i / 10) % 10 + '0', 5, 0);
//		SSD1306_DrawCh((i) % 10 + '0', 6, 1);
//		
//		SSD1306_DrawCh((i / 1000000000000000) % 10 + '0', 0, 3);
//		SSD1306_DrawCh((i / 100000000000000) % 10 + '0', 1, 3);
//		SSD1306_DrawCh((i / 10000000000000) % 10 + '0', 2, 3);
//		SSD1306_DrawCh((i / 1000000000000) % 10 + '0', 3, 3);
//		SSD1306_DrawCh((i / 100000000000) % 10 + '0', 4, 3);
//		SSD1306_DrawCh((i / 10000000000) % 10 + '0', 5, 3);
//		SSD1306_DrawCh((i / 1000000000) % 10 + '0', 6, 3);
//		SSD1306_DrawCh((i / 100000000) % 10 + '0', 7, 3);
//		SSD1306_DrawCh((i / 10000000) % 10 + '0', 8, 3);
//		SSD1306_DrawCh((i / 1000000) % 10 + '0', 9, 3);
//		SSD1306_DrawCh((i / 100000) % 10 + '0', 10, 3);
//		SSD1306_DrawCh((i / 10000) % 10 + '0', 11, 3);
//		SSD1306_DrawCh((i / 1000) % 10 + '0', 12, 3);
//		SSD1306_DrawCh((i / 100) % 10 + '0', 13, 3);
//		SSD1306_DrawCh((i / 10) % 10 + '0', 14, 3);
//		SSD1306_DrawCh((i) % 10 + '0', 15, 3);
//		delay(2000);
		
		i = 0xffffffff;
	}
}

