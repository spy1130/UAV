/**
  * @file    can1.h(can回环实验)
  * @author  逗比小憨憨
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   STM32的CAN驱动程序（库函数版本）
  ******************************************************************************
  * @attention
  *
  * 实验平台:STM32F103C8T6
  */

#ifndef __can1_H
#define __can1_H
#include "stm32f10x.h"

#define CAN_ID_EXTEND_MODE  	1
#if CAN_ID_EXTEND_MODE
#define CAN_ID 					1314
#define CAN_ID_SHIFT 			3
#define CAN_ID_MODE				CAN_Id_Extended
#else
#define CAN_ID 					520
#define CAN_ID_SHIFT 			21
#define CAN_ID_MODE				CAN_Id_Standard
#endif

#define CAN_SELECTION_FIFO_0  	1 
#define CAN_MODE_CAN_NORMAL     1

#define CAN_PIN_RX 				GPIO_Pin_11
#define CAN_PIN_TX 				GPIO_Pin_12
#define CAN_PORT   				GPIOA

typedef struct CAN_STRUCT{
	uint8_t  flag;
	CanRxMsg RxMessage;
	CanTxMsg TxMessage;
}CAN_STRUCT;
extern struct CAN_STRUCT my_can_struct;

static void can_gpio_config(void);
static void can_filter_config(void);
static void can_nvic_config(void);
static void can_mode_config(uint8_t bs1,uint8_t bs2,uint8_t sjw,uint16_t pre);

void my_can_init(void);
void my_can_transmit_data(uint8_t *dat,uint8_t length);
void my_can_receive_test(void);

#endif


