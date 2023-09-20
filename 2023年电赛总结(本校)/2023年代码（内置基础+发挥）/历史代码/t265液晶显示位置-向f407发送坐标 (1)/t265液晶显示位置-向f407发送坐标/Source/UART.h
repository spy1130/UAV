#ifndef _UART_H
#define _UART_H

#include "config.h"

void UART3_Init(u32 baud);



void UART2_Init(u32 baud);
void UART2_SendStr(uc8 *dat);
void UART2_Send(u8 UARTdat);
void UART2_SendStr_xm(uc8 *DataToSend, u8 data_num);


void UART1_Init(u32 baud);
void UART1_Send(u8 UARTdat);
void UART1_SendStr(uc8 *dat);


#endif
