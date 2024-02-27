#ifndef __USER_TASK_H
#define __USER_TASK_H

#include "SysConfig.h"
#include "stm32f4xx.h"

void UserTask_OneKeyCmd(void);
extern u16 Task_time_dly_cnt_ms;
extern u8 mission_step;

#endif
