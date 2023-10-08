#ifndef __dht11_H
#define __dht11_H

#include "stm32f10x.h"
#include "bit_operation.h"

#define DHT11_SIGNAL_OUT PBout(12)
#define DHT11_SIGNAL_IN  PBin(12)

//CRH:19-16

//输入：0100
//输出：0011

//0000 0000  0000 0000 0000 0000  0000 1111
//0000 0000  0000 1111 0000 0000 0000 0000
//1111 1111  1111 0000 1111 1111 1111 1111
//xxxx xxxx  xxxx xxxx xxxx xxxx xxxx xxxx
//xxxx xxxx xxxx  0000 xxxx xxxx xxxx xxxx
//0000 0000  0000 0000 0000 0000  0000 0100
//xxxx xxxx xxxx  0100 xxxx xxxx xxxx xxxx

#define DHT11_PIN_MODE_IN()   {GPIOB->CRH &= ~(0XF << 16); GPIOB->CRH |= (0X4 << 16);};
#define DHT11_PIN_MODE_OUT()  {GPIOB->CRH &= ~(0XF << 16); GPIOB->CRH |= (0X3 << 16);};

//函数声明
unsigned char Dht11_Init(void);
unsigned char Dht11_Check(void);
unsigned char Dht11_ReadBit(void);
unsigned char Dht11_ReadByte(void);
unsigned char DHT11_Read_Data(u8 *temp,u8 *humi);

#endif

