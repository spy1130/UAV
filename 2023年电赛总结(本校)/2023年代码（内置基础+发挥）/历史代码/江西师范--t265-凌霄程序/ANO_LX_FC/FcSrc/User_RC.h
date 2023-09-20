/*==========================================================================
 * 描述    ：遥控器数据处理：一键停机，功能选择等
 * 更新时间：2023年3月23日
 * 作者		 ：	LHB
===========================================================================*/

#ifndef __USER_RC_H
#define __USER_RC_H

#include "Drv_RcIn.h"
#include "Timer.h"
#include "hw_ints.h"
#include "uart.h"

void User_RC_Check(void);//遥控器用户数据处理
void RC_LOCK_Check(void);//飞控紧急上锁
void RC_LAND_Check(void);//飞控一键降落
void RC_Change_mode(void);//选择速度传感器来源

#endif
