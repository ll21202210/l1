#ifndef __OLED_H_
#define __OLED_H_

#include "stm32f4xx.h"


#define		OLED_ADDRMODE_HORI				0x00
#define		OLED_ADDRMODE_VERT				0x01
#define		OLED_ADDRMODE_PAGE				0x02




void OLED_Init(void);
void OLED_SetContrast(uint8_t con);
void OLED_SetAddrMode(uint8_t mode);
void OLED_DMAConfig(uint8_t* buffer);
void OLED_SetPos(uint8_t x, uint8_t y);
void OLED_GRAMClear(uint8_t* buffer, uint8_t x_start, uint8_t x_end, uint8_t y_start, uint8_t y_end);
void OLED_ShowStr(uint8_t* buff,char* str, uint8_t x, uint8_t y);
void OLED_ShowNum(uint8_t* buff,uint32_t num, uint8_t len, uint8_t x, uint8_t y);
void OLED_InverseArea(uint8_t* buffer, uint8_t x_start, uint8_t x_stop, uint8_t y_start, uint8_t y_stop);
void OLED_SendBBuffer(uint8_t *buf);

#endif /** __OLED_H_ */

