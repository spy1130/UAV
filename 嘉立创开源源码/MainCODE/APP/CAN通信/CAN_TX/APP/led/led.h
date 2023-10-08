
#ifndef __led_H
#define __led_H

#include "stm32f10x.h"
#include "bit_operation.h"

//#define led1 PAout(1)
//#define led2 PAout(7)
#define led1 PAout(4)
#define led2 PAout(5)


void Led_Init(void);

#endif

