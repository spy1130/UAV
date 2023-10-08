#ifndef __KEYBOARD_h
#define __KEYBOARD_h

#include "stm32f10x.h"
#include "delay.h"
 
 
 
 
 
void Matrix_ssKey_Pin_Init(void);
u8 Matrix_Key_Scan(void);
void KeyBoardSend(u8 key);

 
#endif
