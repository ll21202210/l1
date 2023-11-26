#include "iic.h"

void IIC_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIOInitStruct.GPIO_OType = GPIO_OType_OD;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIOInitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIOInitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	// pb6 scl pb7 sda
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
	
	I2C_InitTypeDef I2CInitStruct;
	I2CInitStruct.I2C_Ack = I2C_Ack_Enable;
	I2CInitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2CInitStruct.I2C_ClockSpeed = 400000;
	I2CInitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2CInitStruct.I2C_Mode = I2C_Mode_I2C;
	I2CInitStruct.I2C_OwnAddress1 = 0xff;
	
	I2C_Init(I2C1, &I2CInitStruct);
	
	I2C_Cmd(I2C1, ENABLE);
	
}
void IIC2_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIOInitStruct.GPIO_OType = GPIO_OType_OD;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIOInitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIOInitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	// pb6 scl pb7 sda
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF9_I2C2);
	
	
	I2C_InitTypeDef I2CInitStruct;
	I2CInitStruct.I2C_Ack = I2C_Ack_Enable;
	I2CInitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2CInitStruct.I2C_ClockSpeed = 100000;
	I2CInitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2CInitStruct.I2C_Mode = I2C_Mode_I2C;
	I2CInitStruct.I2C_OwnAddress1 = 0xfe;
	
	I2C_Init(I2C2, &I2CInitStruct);
	
	I2C_Cmd(I2C2, ENABLE);
	
}

void OLED_SendCmd(uint8_t cmd)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(I2C1, OLED_ADDR, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	I2C_SendData(I2C1, OLED_CMD);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_SendData(I2C1, cmd);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_GenerateSTOP(I2C1, ENABLE);
}

void IIC_WriteData(uint8_t addr, uint8_t data)
{
	I2C_GenerateSTART(MPU_IIC, ENABLE);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(MPU_IIC, MPU6050_IICADDR, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	I2C_SendData(MPU_IIC, addr);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_SendData(MPU_IIC, data);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_GenerateSTOP(MPU_IIC, ENABLE);
}

uint8_t IIC_ReadData(uint8_t addr)
{
	
	I2C_GenerateSTART(MPU_IIC, ENABLE);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(MPU_IIC, MPU6050_IICADDR, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	I2C_SendData(MPU_IIC, addr);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_GenerateSTART(MPU_IIC, ENABLE);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(MPU_IIC, MPU6050_IICADDR, I2C_Direction_Receiver);
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);
	
	I2C_AcknowledgeConfig(MPU_IIC, DISABLE);
	
	while(I2C_CheckEvent(MPU_IIC, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
	addr = I2C_ReceiveData(MPU_IIC);
	
	I2C_GenerateSTOP(MPU_IIC, ENABLE);
	
	I2C_AcknowledgeConfig(MPU_IIC, ENABLE);
	return addr;
}

void OLED_SendData(uint8_t data)
{
	I2C_GenerateSTART(I2C1, ENABLE);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(I2C1, OLED_ADDR, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	I2C_SendData(I2C1, OLED_DATA);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_SendData(I2C1, data);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
	I2C_GenerateSTOP(I2C1, ENABLE);
}



void IIC_DMAConfig(uint8_t* buffer, uint32_t size)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Stream7);
    while(DMA_GetCmdStatus(DMA1_Stream7) != DISABLE);
	
	DMA_InitTypeDef DMAInitStruct;
	DMAInitStruct.DMA_BufferSize = size;
	DMAInitStruct.DMA_Channel = DMA_Channel_1;
	DMAInitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMAInitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMAInitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMAInitStruct.DMA_Memory0BaseAddr = (uint32_t)buffer;
	DMAInitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMAInitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMAInitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMAInitStruct.DMA_Mode = DMA_Mode_Circular;
	DMAInitStruct.DMA_PeripheralBaseAddr = (uint32_t)&(I2C1->DR);
	DMAInitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMAInitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMAInitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMAInitStruct.DMA_Priority = DMA_Priority_High;
	
	
	DMA_Init(DMA1_Stream7, &DMAInitStruct);
	
	DMA_Cmd(DMA1_Stream7, ENABLE);
	
	I2C_DMACmd(I2C1, ENABLE);
}
void OLED_SendStart(void)
{
	
	I2C_GenerateSTART(I2C1, ENABLE);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);
	
	I2C_Send7bitAddress(I2C1, OLED_ADDR, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);
	
	I2C_SendData(I2C1, OLED_DATA);
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);
	
}
