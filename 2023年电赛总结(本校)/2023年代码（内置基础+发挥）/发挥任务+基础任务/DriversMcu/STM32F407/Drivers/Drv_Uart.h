#ifndef _USART_H
#define _USART_H

#include "SysConfig.h"

extern u8 rx_buff[44];
extern u8 rx_end_flag;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
extern u8 rx_star_flag;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
extern u8 rx_num;
extern u8 first_frame_end;
extern u8 second_frame_end;
extern u8 find_pole_flag;


extern float angle_min;
extern float dis_min;
extern float dis_min_kalman;
extern u8 rx_end_flag_com1;



void DrvUart1Init(u32 br_num);
void Usart1_IRQ(void);
void DrvUart1SendBuf(unsigned char *DataToSend, u8 data_num);

extern u8 Rx_Buf[];
void DrvUart2Init(u32 br_num);
void Usart2_IRQ(void);
void DrvUart2SendBuf(unsigned char *DataToSend, u8 data_num);

void DrvUart3Init(u32 br_num);
void Usart3_IRQ(void);
void DrvUart3SendBuf(unsigned char *DataToSend, u8 data_num);

void DrvUart4Init(u32 br_num);
void Uart4_IRQ(void);
void DrvUart4SendBuf(unsigned char *DataToSend, u8 data_num);

void DrvUart5Init(u32 br_num);
void Uart5_IRQ(void);
void DrvUart5SendBuf(unsigned char *DataToSend, u8 data_num);

void DrvUartDataCheck(void);
#endif
