//////////////////////////////////////////////////////////////////////
/*
专门存放陈嘉明写的代码
*/
//////////////////////////////////////////////////////////////////////

#include "my_code.h"
#include "ANO_LX.h"
#include "stm32f4xx.h"
#include "LX_FC_EXT_Sensor.h"
#include "Drv_AnoOf.h"

int16_t rol,pit,yaw;//imu输出的欧拉角，单位0.01度
int16_t vel_x,vel_y,vel_z;//速度，单位cm/s
int32_t dis_z;//高度,单位cm

void get_data(void)//获取各种数据
{
	rol = fc_att.st_data.rol_x100;
	pit = fc_att.st_data.pit_x100;
	yaw = fc_att.st_data.yaw_x100;
		
	vel_x = fc_vel.st_data.vel_x;
	vel_y = fc_vel.st_data.vel_y;
	vel_z = fc_vel.st_data.vel_z;
	
	dis_z = ano_of.of_alt_cm;
}
