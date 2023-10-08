#ifndef __MOTO_H
#define	__MOTO_H

#include "stm32f10x.h"
#include "Pid.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
void motoA(int mode);
void motoB(int mode);
int Velocity_A(int TargetVelocity, int CurrentVelocity);
int Velocity_B(int TargetVelocity, int CurrentVelocity);
 
void InitDirection(void);

void SetMotor(u8 motor,int Velocity);
//void MotorContorl();//Ã»É¶ÓÃ
void StraightMove(int Velocity,u16 delaytime);
void TurnAround(int degree);

u8 TurnAround_Plus(int degree);

#define ABS(x) ((x) > 0 ? (x) : -(x))

#endif
