#include "button.h"
#include "led.h"
#include "delay.h"

//��������Ϊ��������
void Button_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//����AFIOʱ��
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin   = BUTTON_PORT_PIN;//����Ϊ��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUTTON_PORT ,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource13);
	
	EXTI_InitStruct.EXTI_Line=     EXTI_Line5;//GPIOB_5
	//EXTI_InitStruct.EXTI_Line=     EXTI_Line13;//GPIOB_13
	EXTI_InitStruct.EXTI_LineCmd =  ENABLE;
	EXTI_InitStruct.EXTI_Mode    =  EXTI_Mode_Interrupt;//�ж�ģʽ
	EXTI_InitStruct.EXTI_Trigger =  EXTI_Trigger_Falling;//�½��ش���
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	//NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=  2;      
	NVIC_Init(&NVIC_InitStruct);
	
}

uint8_t button_flag = 0;

void EXTI9_5_IRQHandler(void)
{
	//������Ҫ����
	//EXTI_GetFlagStatus ����ֵ1 ���жϲ���
	if(EXTI_GetFlagStatus(EXTI_Line5) == 1)
	{
		delay_ms(20);
		if(EXTI_GetFlagStatus(EXTI_Line5) == 1)//���жϲ���
		{
			button_flag = 1;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line5);
}

void EXTI15_10_IRQHandler(void)
{
	//������Ҫ����
	//EXTI_GetFlagStatus ����ֵ1 ���жϲ���
	if(EXTI_GetFlagStatus(EXTI_Line13) == 1)
	{
		delay_ms(20);
		if(EXTI_GetFlagStatus(EXTI_Line13) == 1)//���жϲ���
		{
			button_flag = ! button_flag;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line13);
}




