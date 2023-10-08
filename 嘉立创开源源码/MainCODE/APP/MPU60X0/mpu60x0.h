#ifndef __mpu60x0_H
#define __mpu60x0_H
#include "myiic.h"
#include "usart.h"
#include "delay.h"


#define MPU6050_ID 0X68 
#define MPU6050_SLAVE_ID 0XD0 

#define PWR_1 0x6b
#define TEMP_H 0X41
#define TEMP_L 0X42
	
void mpu60x0_init(void);

float read_mpu60x0_tempratue(unsigned char *dat);
unsigned char my_mpu6050_test(void);


#endif

