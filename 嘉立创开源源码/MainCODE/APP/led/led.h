
#ifndef __led_H
#define __led_H

#include "stm32f10x.h"
#include "bit_operation.h"

#define LED_PORT      GPIOA
#define LED_PORT_PIN  GPIO_Pin_7
#define led PCout(13)

void Led_Init(void);
//void LED_Operation(unsigned int flag);
#endif

