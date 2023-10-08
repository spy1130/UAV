#include "mpu60x0.h"

//MPU6050��غ���
//�Ե����ϣ�
//        1,IIC�ӿں���   2��MPU60X0��дһ���ֽڼ���ʼ������  3��Ӧ�ô������ٶȣ����ٶȣ��ںϽǶȣ��㷨��

void mpu60x0_init(void)
{
	myiic_init();
	sensor_common_write_byte(MPU6050_SLAVE_ID, PWR_1,0x80);
	delay_ms(100);
	sensor_common_write_byte(MPU6050_SLAVE_ID, PWR_1,0x00);
}


float read_mpu60x0_tempratue(unsigned char *dat)
{
	short temp;
	float actual_temperature;
	
	dat[0] = sensor_common_read_byte(MPU6050_SLAVE_ID, TEMP_H);
	dat[1] = sensor_common_read_byte(MPU6050_SLAVE_ID, TEMP_L);
	temp = ((unsigned int)(dat[0]) << 8) | dat[1];
	
	//actual_temperature = temp / 340 + 36.53
	actual_temperature = (float)temp / 340.0 + 36.53;
	
	return actual_temperature;
}

unsigned char my_mpu6050_test(void)
{
	return 0;
}




