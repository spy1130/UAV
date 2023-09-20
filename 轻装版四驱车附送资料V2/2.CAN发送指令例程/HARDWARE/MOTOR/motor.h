#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
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
