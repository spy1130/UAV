#ifndef __CAN_H
#define __CAN_H	 
#include "bit_operation.h"	    
#include "stm32f10x.h"

//CAN����RX0�ж�ʹ��
#define CAN_RX0_INT_ENABLE	1		//0,��ʹ��;1,ʹ��.								    
extern uint8_t can_flag;
extern uint8_t buf;

uint8_t CAN_Mode_Init(uint8_t tsjw,uint8_t tbs2,uint8_t tbs1,uint16_t brp,uint8_t mode);//CAN��ʼ��
 
uint8_t Can_Send_Msg(uint8_t* msg,uint8_t len);						//��������
uint8_t Can_Receive_Msg(uint8_t *buf, uint8_t len);

void my_can_send_byte(uint8_t data) ;

#endif

















