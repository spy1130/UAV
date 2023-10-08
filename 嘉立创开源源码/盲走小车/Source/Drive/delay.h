#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"

void SysTick_Init(void);
void delay_ms(uint16_t ms);
void delay_us(unsigned int xus);  //1.864S  

#endif

//------------------End of File----------------------------
