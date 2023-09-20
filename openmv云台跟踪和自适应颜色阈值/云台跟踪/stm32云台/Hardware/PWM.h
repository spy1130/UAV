#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void PWM_SetCompare_x(uint16_t Compare_x);
void PWM_SetCompare_y(uint16_t Compare_y);
void HSE_sysclock_config(void);
void Servo_SetAngle_y(float Angle);
void Servo_SetAngle_x(float Angle);



#endif
