#ifndef __MPU6050_H_
#define __MPU6050_H_

#include "stm32f4xx.h"


#define 	MPU6050_PWR_MGMT_1			0x6b
#define 	MPU6050_PWR_MGMT_2			0x6c
#define 	MPU6050_SMPLRT_DIV			0x19
#define 	MPU6050_CONFIG				0x1a
#define 	MPU6050_GYRO_CONFIG			0x1b
#define 	MPU6050_ACCEL_CONFIG		0x1c
#define 	MPU6050_ACCEL_XOUT_H		0x3b
#define 	MPU6050_ACCEL_XOUT_L		0x3c
#define 	MPU6050_ACCEL_YOUT_H		0x3d
#define 	MPU6050_ACCEL_YOUT_L		0x3e
#define 	MPU6050_ACCEL_ZOUT_H		0x3f
#define 	MPU6050_ACCEL_ZOUT_L		0x40
#define 	MPU6050_TEMP_OUT_H			0x41
#define 	MPU6050_TEMP_OUT_L			0x42
#define 	MPU6050_GYRO_XOUT_H			0x43
#define 	MPU6050_GYRO_XOUT_L			0x44
#define 	MPU6050_GYRO_YOUT_H			0x45
#define 	MPU6050_GYRO_YOUT_L			0x46
#define 	MPU6050_GYRO_ZOUT_H			0x47
#define 	MPU6050_GYRO_ZOUT_L			0x48

typedef struct {
	uint16_t accle_x;
	uint16_t accle_y;
	uint16_t accle_z;
	uint16_t gyro_x;
	uint16_t gyro_y;
	uint16_t gyro_z;
	uint16_t temp;
}MPU6050_DataTypdef;
	

void MPU6050_Config(void);
uint8_t MPU6050_ReadReg(uint8_t addr);
void MPU6050_WriteReg(uint8_t addr, uint8_t data);
void MPU6050_Read(int16_t *AX, int16_t *AY, int16_t *AZ, int16_t *GX, int16_t *GY, int16_t *GZ);


#endif 
