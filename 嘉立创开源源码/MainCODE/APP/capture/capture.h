#ifndef __capture_H
#define __capture_H

#include "stm32f10x.h"
#include "bit_operation.h"

void TIM2_Capture_Init(unsigned int pre,unsigned int arr);

extern unsigned int flag;
extern unsigned int dat;
#endif
