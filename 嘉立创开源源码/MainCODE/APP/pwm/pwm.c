#include "pwm.h"

//��ʱ��3����ʱ��72M 
void Timer3_Init(unsigned int pre,unsigned int arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ�ܶ�ʱ��3ʱ��
	
	//����2�����÷�Ƶϵ��
	//3�������Զ����ؼĴ�����ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//clk1 //72M
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = pre;

	TIM_TimeBaseInit(TIMER, &TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel= TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ITConfig(TIMER,TIM_IT_Update,ENABLE);//���ø����ж�
	
	TIM_Cmd(TIMER, ENABLE);//������ʱ��
}

//��ʱ���жϺ��� //500ms
void TIM3_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIMER,TIM_FLAG_Update) != RESET)
	{
	}
	TIM_ClearITPendingBit(TIMER,TIM_FLAG_Update);
}

//TIM3_CH1:PA6
void TIM3_PWM_Init(unsigned int pre,unsigned int arr)
{
/*
1�����ն�ʱ���Ķ�ʱ���ܽ�������
2������GPIO��Ӧ�Ĺ���
3������PWM���
*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	Timer3_Init(pre,arr);
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIMER,&TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIMER,TIM_OCPreload_Enable);
}

