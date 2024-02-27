#ifndef _DRV_HC04_H
#define _DRV_HC04_H

#include "SysConfig.h"
#include "Drv_Sys.h"


unsigned int Read_TIM5Distane(void);
void TIM5_CH3_Cap_Init(u32 arr,u16 psc);
#endif
