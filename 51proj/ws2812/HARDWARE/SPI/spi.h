#ifndef __SPI_H
#define __SPI_H
#include "stm32f4xx.h"

void SPI1_Init(void);			 //��ʼ��SPI1��
//void SPI3_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�
void SPI1_OnlyWriteByte(u8 TxData);

void SPI3_Init(void);			 //��ʼ��SPI1��
void SPI3_SetSpeed(u8 SpeedSet); //����SPI1�ٶ�   
u8 SPI3_ReadWriteByte(u8 TxData);//SPI1���߶�дһ���ֽ�
void SPI3_OnlyWriteByte(u8 TxData);

#endif

