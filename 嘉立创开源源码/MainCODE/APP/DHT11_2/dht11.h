#ifndef __dht11_H
#define __dht11_H

#include "stm32f10x.h"
#include "bit_operation.h"  

#define DHT11_SIGNAL_OUT PBout(12)
#define DHT11_SIGNAL_IN  PBin(12)


typedef struct 
{
	unsigned char tmperature[2];
	unsigned char humidty[2];
	unsigned char checksum;
}DHT11;

extern struct DHT11 dht11;

//CRH:19-16

//输入：0100  0x4
//输出：0011  0x3

//0000 0000  0000 0000 0000 0000  0000 1111  0xf

//0000 0000  0000 1111 0000 0000 0000 0000   0XF << 16

//1111 1111  1111 0000 1111 1111 1111 1111   ~(0XF << 16)

//xxxx xxxx  xxxx xxxx xxxx xxxx xxxx xxxx  GPIOB->CRH

//xxxx xxxx xxxx  0000 xxxx xxxx xxxx xxxx  GPIOB->CRH &= ~(0XF << 16)

//0000 0000  0000 0000 0000 0000  0000 0100 0x4

//xxxx xxxx xxxx  0100 xxxx xxxx xxxx xxxx  (0X4 << 16)

//xxxx xxxx xxxx  0000 xxxx xxxx xxxx xxxx

//xxxx xxxx xxxx  0100 xxxx xxxx xxxx xxxx 

//GPIOB->CRH = 0X4 << 16

#define DHT11_PIN_MODE_IN()   {GPIOB->CRH &= ~(0XF << 16); GPIOB->CRH |= (0X4 << 16);};
#define DHT11_PIN_MODE_OUT()  {GPIOB->CRH &= ~(0XF << 16); GPIOB->CRH |= (0X3 << 16);};



//函数声明
unsigned char Dht11_Init(void);
void Dht11_Start(void);
unsigned char Dht11_Check(void);

unsigned char Dht11_ReadBit(void);
unsigned char Dht11_ReadByte(void);
unsigned char DHT11_Read_Data(void);

#endif

