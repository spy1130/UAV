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
#include "Drv_Uart.h"

float rol,pit,yaw,yaw_now,yaw_last,yaw_round;//imu输出的欧拉角，单位度
int16_t vel_x,vel_y,vel_z;//速度，单位cm/s
int32_t hight;//高度,单位cm
int32_t dis_x,dis_y;//累积的距离,单位cm
double hight_target,dis_x_target,dis_y_target,line_dis_target=180;
int my_give_vel_x,my_give_vel_y,my_give_vel_z,my_give_vel_yaw;//赋给实时控制帧的数据
double dis_yaw_target;
int my_code_control_flag=0;
int keep_hight_flag;
uint8_t OpenMV_mode=0,receive_OpenMV_mode;

u8 data_1,data_2,data_3,data_4,data_5;//OpenMV_line_error低八位，高八位，OpenMV_line_slope低八位，高八位，
int16_t OpenMV_line_error,OpenMV_line_slope,OpenMV_core_x,OpenMV_core_y;
int16_t OpenMV_pole_error;
int line_patro_flag,keep_x_flag,keep_y_flag,keep_yaw_flag,keep_pole_flag,keep_core_flag,keep_line_dis_flag,around_pole_flag;
float line_patro_Kp=0.3,keep_pole_Kp=0.3,keep_line_dis_Kp=0.3,around_pole_Kp=0.6;
float keep_xy_Kp=3,keep_hight_Kp=3,keep_yaw_Kp=2;

int line_dis;

int time_cnt,beep_flag;

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


void around_pole(void)
{
	my_give_vel_y=-6;
	my_give_vel_yaw=-15;
	my_give_vel_yaw =  -15+OpenMV_pole_error*around_pole_Kp;
	my_give_vel_yaw = Limit_max_int(my_give_vel_yaw,30);
}

void keep_pole(void)
{
	my_give_vel_y = -OpenMV_pole_error*keep_pole_Kp;
	my_give_vel_y = Limit_max_int(my_give_vel_y,20);
}

void keep_core(void)
{
	my_give_vel_y = -OpenMV_core_x*keep_pole_Kp;
	my_give_vel_y = Limit_max_int(my_give_vel_y,20);
}

void keep_line_dis(void)
{
	if((line_dis<=1000))
	{
		my_give_vel_x = (line_dis-line_dis_target)*keep_line_dis_Kp;
		my_give_vel_x = Limit_max_int(my_give_vel_x,15);
	}
}

void line_patro(void)
{
	my_give_vel_z = OpenMV_line_error*line_patro_Kp;
	my_give_vel_z = Limit_max_int(my_give_vel_z,10);
}

void keep_hight(void)
{
	my_give_vel_z = (hight_target-hight)*keep_hight_Kp;
	my_give_vel_z = Limit_max_int(my_give_vel_z,20);
}

void keep_dis_x(void)
{
	my_give_vel_x = (dis_x_target-dis_x)*keep_xy_Kp;
	my_give_vel_x = Limit_max_int(my_give_vel_x,20);
}

void keep_dis_y(void)
{
	my_give_vel_y = (dis_y_target-dis_y)*keep_xy_Kp;
	my_give_vel_y = Limit_max_int(my_give_vel_y,20);
}

void keep_yaw(void)
{
	my_give_vel_yaw = (dis_yaw_target-yaw)*keep_yaw_Kp;
	my_give_vel_yaw = Limit_max_int(my_give_vel_yaw,20);
}

void my_one_key_land(void)
{
	static int step=0;
	if(step==0){hight_target=0;if(hight<10){time_cnt++;if(time_cnt>5)step=1;}else time_cnt=0;}
	if(step==1){FC_Lock();}
}

void User_Task_Delay(int ms)
{
	if(Task_time_dly_cnt_ms<ms){Task_time_dly_cnt_ms+=20;}
	else{Task_time_dly_cnt_ms=0;mission_step++;}			
}

void MY_urst2_Receive(uint8_t data)//用凌霄ut3接收OpenMV传输来的数据，格式为：线离中点误差、线的斜率、帧尾0x0A
{
	static int16_t data_cnt=0;
	if((data_cnt==0)&&(data==0x0A))data_cnt=1;
	else if(data_cnt==1){data_1=data;data_cnt=2;}
	else if(data_cnt==2){data_2=data;data_cnt=3;}
	else if(data_cnt==3){data_3=data;data_cnt=4;}
	else if(data_cnt==4){data_4=data;data_cnt=5;}
	else if(data_cnt==5){data_5=data;data_cnt=0;}
	else data_cnt=0;
	receive_OpenMV_mode=data_1;
	if(OpenMV_mode==0)
	{
		OpenMV_line_error = data_3;
		OpenMV_line_error<<=8;
		OpenMV_line_error |=data_2;
		
		OpenMV_line_slope = data_5;
		OpenMV_line_slope<<=8;
		OpenMV_line_slope |=data_4;
	}
	
	if(receive_OpenMV_mode==1)
	{
		OpenMV_pole_error = data_3;
		OpenMV_pole_error<<=8;
		OpenMV_pole_error |=data_2;
//		OpenMV_pole_error-=160;
	}
	if(receive_OpenMV_mode==2)
	{
		OpenMV_core_x = data_3;
		OpenMV_core_x<<=8;
		OpenMV_core_x |=data_2;
		
		OpenMV_core_y = data_5;
		OpenMV_core_y<<=8;
		OpenMV_core_y |=data_4;
	}
	if(receive_OpenMV_mode==0) OpenMV_pole_error=0,OpenMV_core_x=0;
	
}

void MY_urst2_Send(void)
{
	u8 Buf[]={OpenMV_mode,0x0A};
	DrvUart2SendBuf(Buf,sizeof(Buf));
}
