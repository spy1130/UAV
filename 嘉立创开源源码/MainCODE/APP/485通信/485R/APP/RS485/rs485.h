#ifndef __RS485_H
#define __RS485_H

#include "stm32f10x.h"	 								  
#include "bit_operation.h"

extern uint8_t RS485_RX_BUF[64]; 		//���ջ���,���64���ֽ�
extern uint8_t RS485_RX_CNT;   			//���յ������ݳ���

//ģʽ����
//��һ��STM32
#define RS485_TX_EN		PAout(8)	//485ģʽ����.0,����;1,����.

void RS485_Init(uint32_t bound);
void RS485_Send_Data(uint8_t *buf,uint8_t len);
void RS485_Receive_Data(uint8_t *buf,uint8_t *len);


#endif	   
















