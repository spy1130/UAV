#ifndef __MY_CODE_H
#define __MY_CODE_H

#include "stdint.h"

extern float rol,pit,yaw;//imu输出的欧拉角，单位0.01度
extern int16_t vel_x,vel_y,vel_z;//速度，单位cm/s
extern int32_t hight;//高度,单位cm
extern int32_t dis_x,dis_y;//累积的距离,单位cm
extern double dis_yaw_target;//记录角度
extern double hight_target,dis_x_target,dis_y_target,line_dis_target;
extern int my_give_vel_x,my_give_vel_y,my_give_vel_z,my_give_vel_yaw;//赋给实时控制帧的数据
extern int my_code_control_flag;//是否使用实时控制帧的标志位
extern int keep_hight_flag;
extern int line_patro_flag,keep_x_flag,keep_y_flag,keep_yaw_flag,keep_pole_flag,keep_core_flag,keep_line_dis_flag,around_pole_flag;
extern int line_dis;
extern uint8_t OpenMV_mode,receive_OpenMV_mode;
extern int16_t OpenMV_pole_error,OpenMV_core_x,OpenMV_core_y;
extern int time_cnt,beep_flag;

float Limit_max_float(float input,float max);//限幅函数
int Limit_max_int(int input,int max);//限幅函数
void get_data(void);
void around_pole(void);
void keep_core(void);
void keep_pole(void);
void keep_line_dis(void);
void line_patro(void);
void keep_hight(void);
void User_Task_Delay(int ms);
void my_one_key_land(void);
void keep_dis_x(void);
void keep_dis_y(void);
void keep_yaw(void);
void MY_urst2_Receive(uint8_t data);//用凌霄ut3接收OpenMV传输来的数据，格式为：线离中点误差、线的斜率、帧尾0x0A
void MY_urst2_Send(void);

#endif
