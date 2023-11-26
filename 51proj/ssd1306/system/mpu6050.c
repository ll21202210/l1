#include "mpu6050.h"
#include "iic.h"




void MPU6050_Config(void)
{
	IIC2_Config();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x01);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x00);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x00);
	
}
uint8_t MPU6050_ReadReg(uint8_t addr)
{
	return IIC_ReadData(addr);
}

void MPU6050_WriteReg(uint8_t addr, uint8_t data)
{
	IIC_WriteData(addr, data);
}

void MPU6050_Read(int16_t *AX, int16_t *AY, int16_t *AZ, int16_t *GX, int16_t *GY, int16_t *GZ)
{
	*AX = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AX |= MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8;
	
	*AY = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AY |= MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8;
	
	*AZ = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AZ |= MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8;
	
	*GX = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GX |= MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8;
	
	*GY = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GY |= MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8;
	
	*GZ = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GZ |= MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8;
	
}
void MPU6050_ReadTemp(uint16_t *TMP)
{
	*TMP = MPU6050_ReadReg(MPU6050_TEMP_OUT_L);
	*TMP |= MPU6050_ReadReg(MPU6050_TEMP_OUT_H) << 8;
}
