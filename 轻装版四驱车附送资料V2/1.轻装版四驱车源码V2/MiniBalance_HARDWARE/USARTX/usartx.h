#ifndef __USRAT3_H
#define __USRAT3_H 
#include "sys.h"	  	
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
void usart3_send(u8 data);
void uart3_init(u32 bound);
void USART3_IRQHandler(void);
#endif

