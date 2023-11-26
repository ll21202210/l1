#ifndef __IIC_H_
#define __IIC_H_
#include <reg52.h>
#include <intrins.h>


#define u8 unsigned char
#define u16 unsigned int


#define IIC_Addr  0x78


sbit SCL = P2^2;
sbit SDA = P2^3;

void IIC_Send(u8 dat);
void IIC_Start();
void IIC_Stop();
void SSD1306_WriteCMD(u8 CMD);
void SSD1306_WriteDATA(u8 *dat, u16 count);
void SSD1306_Init();
void SSD1306_SetCon(u8 Contrast);


void SSD1306_SetPageAddr(u8 StartAddr, u8 EndAddr);
void SSD1306_SetColAddr(u8 StartAddr, u8 EndAddr);
void SSD1306_Clear();
void SSD1306_SetPos(u8 x, u8 y);
void SSD1306_DrawCh(u8 ch, u8 x, u8 y);



void ltyd();



#endif /** __IIC_H_ */