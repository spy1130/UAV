
#ifndef __button_H
#define __button_H

#include "stm32f10x.h"

extern uint8_t button_flag;

#define BUTTON_PORT      GPIOB
//��һ��STM32
#define BUTTON_PORT_PIN  GPIO_Pin_5
//�ڶ���STM32
//#define BUTTON_PORT_PIN  GPIO_Pin_13

void Button_Init(void);

#endif



