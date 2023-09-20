/*==========================================================================
 * 描述    ：用户程控函数
 * 更新时间：2023年3月26日
 * 作者		 ：	LHB
===========================================================================*/
#ifndef __USER_CTRL_
#define __USER_CTRL_


#include "Drv_Uart.h"
#include "uart.h"
#include "hw_ints.h"
#include "hw_gpio.h"
#include "hw_types.h"
#include "Ano_DT_LX.h"
#include "Drv_UbloxGPS.h"
#include "Drv_AnoOf.h"
#include "Drv_AnoOf.h"
#include "User_T265.h"

////////////////////////////////////////
/*位置角度环PID参数定义*/
#define loc_ctrl_dis_p 0.8f
#define loc_ctrl_dis_i 0.0f
#define loc_ctrl_dis_d 0.02f  

#define loc_ctrl_ang_p 0.1f
#define loc_ctrl_ang_i 0.0f
#define loc_ctrl_ang_d 0.0f

#define loc_ctrl_att_p 0.6f
#define loc_ctrl_att_i 0.0f
#define loc_ctrl_att_d 0.0f

////////////////////////////////////////
extern s16 CMDvalue[4];//实时控制帧发送数据

extern u8 LocCtrlEnable;
extern u8 AngCtrlEnable;
extern u8 AttCtrlEnable;

extern u8 ProgramAutoLand;//程控自动降落

void Program_Ctrl_User_Set_Speed(s16 xpcm, s16 ypcm, s16 zpcm, s16 degpres);//向飞控发送期望速度
void User_Loc_Ctrl(s16 true_x_cm,s16 true_y_cm,s16 true_z_cm,s16 true_yaw_deg,s16 exp_x_cm,s16 exp_y_cm,s16 exp_z_cm,s16 exp_yaw_deg,u8 freq);//位置环控制

#endif

