#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define USART1_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1			//ʹ�ܣ�1��/��ֹ��0������1���� 	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         			//����״̬���	
void uart1_init(u32 bound);

#define USART2_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART2_RX 			1			//ʹ�ܣ�1��/��ֹ��0������2����
extern u8  USART2_RX_BUF[USART2_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         			//����״̬���	
void uart2_init(u32 bound);
void Usart2Init(unsigned int uiBaud);
void Uart2Send(unsigned char *p_data, unsigned int uiSize);

#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1			//ʹ�ܣ�1��/��ֹ��0������2����
extern u8  USART3_RX_BUF[USART3_REC_LEN]; 	//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         			//����״̬���	
void uart3_init(u32 bound);
#endif
