#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>


//==����
typedef struct
{
//	uint8_t offline;
//	uint8_t mode_sta;
	uint8_t ctrl_mode;
	//ԭʼ����[T265����ϵ]
	int16_t pos_x;
	int16_t pos_y;
	int16_t pos_z;
	//ԭʼ�ٶ�
	int16_t v_x;
	int16_t v_y;
	int16_t v_z;
	//ԭʼŷ����
	int16_t pitch;
	int16_t roll;
	int16_t yaw;
	
	//ת��������[��������ϵ]
	int16_t pos_x_f;
	int16_t pos_y_f;
	int16_t pos_z_f;
	//ת�����ٶ�
	int16_t v_x_f;
	int16_t v_y_f;
	int16_t v_z_f;
	//ת����ŷ����
	int16_t pi_f;
	int16_t ro_f;
	int16_t ya_f;
	
}T265_Data;

#endif
