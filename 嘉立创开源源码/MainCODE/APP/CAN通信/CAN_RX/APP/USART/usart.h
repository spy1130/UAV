#ifndef __usart_H
#define __usart_H 

#include "stm32f10x.h"
#include "stdio.h"

#define   LEN 100  //接收到字符串长度最大是100
static unsigned char usart1_data[LEN]={0};//用于保存串口1接收到数据
static unsigned int sta = 0;    //1用于计数变量和判断换行符

void Usart1_Init(unsigned int baud);

#endif 




