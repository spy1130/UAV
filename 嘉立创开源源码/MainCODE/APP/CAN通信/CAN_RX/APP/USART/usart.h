#ifndef __usart_H
#define __usart_H 

#include "stm32f10x.h"
#include "stdio.h"

#define   LEN 100  //���յ��ַ������������100
static unsigned char usart1_data[LEN]={0};//���ڱ��洮��1���յ�����
static unsigned int sta = 0;    //1���ڼ����������жϻ��з�

void Usart1_Init(unsigned int baud);

#endif 




