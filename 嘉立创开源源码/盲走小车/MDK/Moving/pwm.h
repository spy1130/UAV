#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"
#include "stm32f10x_tim.h"

void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void PWM_Int(u16 arr,u16 psc);


void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare1);//Compare1Õ¼¿Õ±È£º0~300


#endif
