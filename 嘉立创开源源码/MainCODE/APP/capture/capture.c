#include "capture.h"

/*
PA2: TIM2_CH3
*/
void TIM2_Capture_Init(unsigned int pre,unsigned int arr)
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
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
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOA��ʱ��
	//GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//?
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;//?
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC3,ENABLE);//���ø����ж�
	
	TIM_Cmd(TIM2, ENABLE);//������ʱ��
}

/*
	flag�����λ�����ڱ�ʾ�ɹ��������½���
		  �˸�λ�����ڱ�ʾ�ɹ�������������
		  ��30λ���ڱ�ʾ�����˶��ٴθ����ж�
*/
/*
����ֵ��num = ((dat-0) + (flag & 0X3F) *arr) 
����ʱ�䣺t = num * (1/clk) 
clk:����ʱ�������ʱ������
*/

//��ʱ���жϺ��� //500ms
unsigned int flag = 0;
unsigned int dat = 0;

void TIM2_IRQHandler(void)
{
	if((flag & 0x80) == 0)
	{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)//�����ж�
		{
			if(flag & 0X40)//���񵽸ߵ�ƽ
			{
				if((flag & 0X3F) == 0X3F)
				{
					flag |= 0X80;//��ǳɹ�������һ��
					dat = 0XFFFF;
				}
				else 
					flag++;
			}	
		}
		
		else if(TIM_GetITStatus(TIM2,TIM_IT_CC3) != RESET)//���벶���ж�
		{
			if(flag & 0X40)		//����һ��������		
			{	  			
				flag |= 0X80;		
				dat = TIM_GetCapture3(TIM2);
				
				TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising); 
			}
			else  							
			{
				flag = 0;			//���
				dat = 0;
				TIM_SetCounter(TIM2,0);
				flag |= 0X40;		//��ǲ�����������
				TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);		
			}	
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update | TIM_IT_CC3);
}



