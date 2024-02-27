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
#include "User_Task.h"
#include "LX_FC_Fun.h"

int16_t rol,pit,yaw,yaw_now,yaw_last,yaw_round;//imu输出的欧拉角，单位0.01度
int16_t vel_x,vel_y,vel_z;//速度，单位cm/s
int32_t hight;//高度,单位cm
int32_t dis_x,dis_y;//累积的距离,单位cm
int hight_target,dis_x_target,dis_y_target;//赋给实时控制帧的目标数据
int my_give_vel_x,my_give_vel_y,my_give_vel_z;//赋给实时控制帧的数据

int yaw_record;

int my_code_control_flag=0;
int keep_hight_flag;

int cnt;

void get_data(void)//获取各种数据
{
	rol = (fc_att.st_data.rol_x100)/100;
	pit = (fc_att.st_data.pit_x100)/100;
	
	yaw_now = fc_att.st_data.yaw_x100;
	if((yaw_last>9000)&&(yaw_now<-9000)) yaw_round++;
	if((yaw_last<-9000)&&(yaw_now>9000)) yaw_round--;
	yaw = yaw_round*360 + yaw_now/100;
	yaw_last=yaw_now;
	
	vel_x = ano_of.of2_dx_fix;
	vel_y = ano_of.of2_dy_fix;
	
	dis_x = ano_of.intergral_x;
	dis_y = ano_of.intergral_y;

	
	hight = ano_of.of_alt_cm;
}

float Limit_max_float(float input,float max)//限幅函数
{
	if(input > max)
	{
		input = max;
	}
	else if(input < -max)
	{
		input = -max;
	}
	return input;
}

int Limit_max_int(int input,int max)//限幅函数
{
	if(input > max)
	{
		input = max;
	}
	else if(input < -max)
	{
		input = -max;
	}
	return input;
}


void keep_hight(void)
{
	my_give_vel_z = (hight_target-hight)*3;
	my_give_vel_z = Limit_max_int(my_give_vel_z,20);
}

void keep_dis_x(void)
{
	my_give_vel_x = (dis_x_target-dis_x)*1;
	my_give_vel_x = Limit_max_int(my_give_vel_x,20);
}

void keep_dis_y(void)
{
	my_give_vel_y = (dis_y_target-dis_y)*1;
	my_give_vel_y = Limit_max_int(my_give_vel_y,20);
}

void my_one_key_land(void)
{
	static int step=0;
	if(step==0){hight_target=0;if(hight<10){cnt++;if(cnt>5)step=1;}else cnt=0;}
	if(step==1){FC_Lock();}
}

void User_Task_Delay(int ms)
{
	if(Task_time_dly_cnt_ms<ms){Task_time_dly_cnt_ms+=20;}
	else{Task_time_dly_cnt_ms = 0;mission_step += 1;}			
}

