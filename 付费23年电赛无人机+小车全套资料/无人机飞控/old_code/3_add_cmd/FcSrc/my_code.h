#ifndef __MY_CODE_H
#define __MY_CODE_H

#include "stdint.h"

extern int16_t rol,pit,yaw;//imu输出的欧拉角，单位0.01度
extern int16_t vel_x,vel_y,vel_z;//速度，单位cm/s
extern int32_t hight;//高度,单位cm
extern int32_t dis_x,dis_y;//累积的距离,单位cm
extern int yaw_record;//记录角度
extern int hight_target,dis_x_target,dis_y_target;//赋给实时控制帧的目标数据
extern int my_give_vel_x,my_give_vel_y,my_give_vel_z;//赋给实时控制帧的数据
extern int my_code_control_flag;//是否使用实时控制帧的标志位
extern int keep_hight_flag;

float Limit_max_float(float input,float max);//限幅函数
int Limit_max_int(int input,int max);//限幅函数
void get_data(void);
void keep_hight(void);
void User_Task_Delay(int ms);
void my_one_key_land(void);
void keep_dis_x(void);
void keep_dis_y(void);

#endif
