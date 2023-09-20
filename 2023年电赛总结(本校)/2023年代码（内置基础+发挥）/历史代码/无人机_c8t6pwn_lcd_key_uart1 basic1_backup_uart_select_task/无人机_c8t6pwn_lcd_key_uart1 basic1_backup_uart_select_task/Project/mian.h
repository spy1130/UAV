#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>


//==定义
typedef struct
{
//	uint8_t offline;
//	uint8_t mode_sta;
	uint8_t ctrl_mode;
	//原始坐标[T265坐标系]
	int16_t pos_x;
	int16_t pos_y;
	int16_t pos_z;
	//原始速度
	int16_t v_x;
	int16_t v_y;
	int16_t v_z;
	//原始欧拉角
	int16_t pitch;
	int16_t roll;
	int16_t yaw;
	
	//转换后坐标[匿名坐标系]
	int16_t pos_x_f;
	int16_t pos_y_f;
	int16_t pos_z_f;
	//转换后速度
	int16_t v_x_f;
	int16_t v_y_f;
	int16_t v_z_f;
	//转换后欧拉角
	int16_t pi_f;
	int16_t ro_f;
	int16_t ya_f;
	
}T265_Data;

#endif
