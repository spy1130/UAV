#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PWMA2   TIM8->CCR1  
#define PWMA1   TIM1->CCR1 

#define PWMB2   TIM8->CCR2 
#define PWMB1   TIM1->CCR2 

#define PWMC2   TIM1->CCR3
#define PWMC1   TIM8->CCR3

#define PWMD1   TIM8->CCR4
#define PWMD2   TIM1->CCR4 
void MiniBalance_PWM_Init(u16 arr,u16 psc);
#endif
