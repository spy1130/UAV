#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "misc.h"

#define USART1_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1			//使能（1）/禁止（0）串口1接收 	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         			//接收状态标记	
void uart1_init(u32 bound);

#define USART2_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART2_RX 			1			//使能（1）/禁止（0）串口2接收
extern u8  USART2_RX_BUF[USART2_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         			//接收状态标记	
void uart2_init(u32 bound);
void Usart2Init(unsigned int uiBaud);
void Uart2Send(unsigned char *p_data, unsigned int uiSize);

#define USART3_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART3_RX 			1			//使能（1）/禁止（0）串口2接收
extern u8  USART3_RX_BUF[USART3_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART3_RX_STA;         			//接收状态标记	
void uart3_init(u32 bound);
#endif
