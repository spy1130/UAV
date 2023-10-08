#ifndef __LX_DT_H
#define __LX_DT_H 

#include <stdio.h>
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#define BYTE0(dwTemp) (*((char *)(&dwTemp)))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

typedef union
{
	s16 Data[2];
	u8 byet[4];
}S16_Byte;

typedef union
{
	s16 Data;
	u8 byet[2];
}S16_1Byte;

void Flight_DataReceive(u8 data);
u8 DataSend(u8 key);
void JY62_DataReceive(u8 data);
void Nano_DataSend(void);

#endif 




