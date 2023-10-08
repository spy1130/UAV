#ifndef __LX_DT_H
#define __LX_DT_H 

#include "stm32f10x.h"
#include "delay.h"

#define BYTE0(dwTemp) (*((char *)(&dwTemp)))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

typedef union
{
	s16 Data[2];
	u8 byet[4];
}S16_Byte;
void RT_Location_Send(s16 x,s16 y);
void Fire_Location_Send(s16 x,s16 y);
void DataReceive(u8 data);
void DataReceive2(u8 data);
void DataSend(void);
void Takeoff(u8 data);
void RT_Location_Send_PIC (s16 x,s16 y);


#endif 




