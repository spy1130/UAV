#include "timer.h"
#include "led.h"

/*��ʱ����ʱ���ܱ�̲��裺

	1,ѡ��ʱ�ӣ��ڲ�ʱ�ӣ�����Ҫ�Ƿ�Ƶ
	2������APB1���߶�ʱ��2����ʱ�ӣ���ʱ��2�ܵĿ��أ�
	
	3�������Զ����ؼĴ�����ֵ.Ԥ��Ƶֵ
	
	4��������ʱ���ж�
	
	5���������ȼ�
	7��������ʱ��
	
	8����д��ʱ���жϳ���
	��ʱ����������ʱ������
			���벶�񣺽�ϳ���������������  
			����Ƚϣ�����PWM
			IIC��OLED��ʾ��
	��һ�׶Σ�
		
	
*/

//��ʱ��2����ʱ��72M
void Timer_Init(unsigned int pre,unsigned int arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ�ܶ�ʱ��2ʱ��
	
	//����2�����÷�Ƶϵ��
	//3�������Զ����ؼĴ�����ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//clk1 //72M
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = pre;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel= TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//���ø����ж�
	
	
	
	TIM_Cmd(TIM2, ENABLE);//������ʱ��
}

////��ʱ���жϺ��� //500ms
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) != RESET)
//	{
//		led = !led;
//	}
//	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
//}
