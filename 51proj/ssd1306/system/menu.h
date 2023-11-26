#ifndef __MENU_H_
#define __MENU_H_

#include "stm32f4xx.h"


typedef enum 
{
	UI_Type_FILE = 0,
	UI_Type_MAIN,
	UI_Type_PLAYING
}UI_Type;
typedef enum {
	BATTERY = 0,
	PLAY
}ProgressBar_Type;





void DrawProgressBar(uint8_t* buffer, ProgressBar_Type pro_typ, uint8_t y, uint8_t x, uint8_t len, uint8_t perc);



#endif /** __MENU_H_*/
