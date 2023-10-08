#ifndef __inputCapture_H
#define __inputCapture_H

#include "stm32f10x.h"
#include "bit_operation.h"

void TIM2_Capture_Init(unsigned int pre,unsigned int arr);

extern unsigned char flag;
extern unsigned char dat;

#endif
