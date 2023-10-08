
#ifndef __button_H
#define __button_H

#include "stm32f10x.h"

#define BUTTON_PORT      GPIOB
#define BUTTON_PORT_PIN  GPIO_Pin_10

void Button_Init(void);

#endif



