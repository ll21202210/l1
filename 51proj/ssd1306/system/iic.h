#ifndef __IIC_H_
#define __IIC_H_

#include "stm32f4xx.h"

#define 	OLED_ADDR			0x78
#define 	OLED_CMD			0x00
#define 	OLED_DATA			0x40
#define 	MPU6050_IICADDR		0xd0
#define 	MPU_IIC				I2C2

void IIC_Config(void);
void IIC2_Config(void);

void IIC_DMAConfig(uint8_t* buffer, uint32_t size);
void IIC_WriteData(uint8_t addr, uint8_t data);
uint8_t IIC_ReadData(uint8_t addr);
void OLED_SendCmd(uint8_t cmd);
void OLED_SendData(uint8_t data);
void OLED_SendStart(void);



#endif /** __IIC_H_ */
