#include "led.h"
#include "bit_operation.h"

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOA��ʱ��
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//��һ��STM32 LED��Ӧ���ŵĳ�ʼ��
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStruct);
	
//	//��һ��STM32 ������Ӧ���ŵĳ�ʼ��
//	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
//	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB ,&GPIO_InitStruct);
	
	//GPIO_SetBits(GPIOA,GPIO_Pin_1|GPIO_Pin_7);
	
//	//�ڶ���STM32 LED��Ӧ���ŵĳ�ʼ��
//	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
//	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4|GPIO_Pin_5;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA ,&GPIO_InitStruct);
//	
//	//�ڶ���STM32 ������Ӧ���ŵĳ�ʼ��
//	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
//	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB ,&GPIO_InitStruct);
//	
//	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);
}
 
