#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PWMA1   TIM1->CCR1  
#define PWMB1   TIM1->CCR2 
#define PWMC1   TIM1->CCR3 

#define PWMA2   TIM3->CCR3  
#define PWMB2   TIM3->CCR1 
#define PWMC2   TIM3->CCR2 
void MiniBalance_PWM_Init(u16 arr,u16 psc);
void MiniBalance_Motor_Init(void);
#endif
