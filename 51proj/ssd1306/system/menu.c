#include "menu.h"



void DrawProgressBar(uint8_t* buffer, ProgressBar_Type pro_typ, uint8_t y, uint8_t x, uint8_t len, uint8_t perc)
{
	for(uint8_t i = x; i < len; i++)
	{
		if((i - x)*100 / len < perc)
			buffer[y * 128 + i] = 0x80;
		else
			buffer[y * 128 + i] = 0x0;
	}
//	buffer[y * 128 + i] |= 0xc0;
}
void Display_Task(void)
{
	// meixie
}

