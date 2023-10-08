#ifndef __RS485_H
#define __RS485_H

#include "stm32f10x.h"	 								  
#include "bit_operation.h"

extern uint8_t RS485_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern uint8_t RS485_RX_CNT;   			//接收到的数据长度

//模式控制
//第一个STM32
#define RS485_TX_EN		PAout(8)	//485模式控制.0,接收;1,发送.

void RS485_Init(uint32_t bound);
void RS485_Send_Data(uint8_t *buf,uint8_t len);
void RS485_Receive_Data(uint8_t *buf,uint8_t *len);


#endif	   
















