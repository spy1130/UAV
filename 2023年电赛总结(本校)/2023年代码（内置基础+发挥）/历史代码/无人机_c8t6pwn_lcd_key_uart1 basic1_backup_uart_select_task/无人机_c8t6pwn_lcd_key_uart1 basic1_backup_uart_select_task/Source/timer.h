#ifndef _TIMER_H
#define _TIMER_H

#include "config.h"

void TIM2Init(u16 period, u16 prescaler);
void TIM3_PWM_Init(u16 arr,u16 psc);


void key_scan(void);
void TIM2_Int_Init(u16 arr,u16 psc);

#endif
