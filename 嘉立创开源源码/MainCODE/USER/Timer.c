#include "Timer.h"
#include "LX_DT.h"

/*
1,ʱ��ʹ��
2,����Ԥ��Ƶ���Զ���װֵ���ظ�����ֵ
3,����жϱ�־λ��������Ƚ�һ���жϣ�
4,ʹ��TIM�жϣ�ѡ���ж�Դ
5,�����ж����ȼ�
6,ʹ��TIMx����

arr���Զ���װֵ  
psc��ʱ��Ԥ��Ƶ��  
*/

extern u8 dat;

void Timer1_Init(u16 arr,u16 psc)  

{  

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  NVIC_InitTypeDef NVIC_InitStructure;  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��  
  
  TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ�������ֵ  
  TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);//����Ԥ��Ƶֵ 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//�ظ���������  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //������ʼ��  

  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���жϱ�־λ  

  TIM_ITConfig(      //ʹ�ܻ���ʧ��ָ����TIM�ж�  
    TIM1,            //TIM1  
    TIM_IT_Update  | //TIM �����ж�Դ  
    TIM_IT_Trigger,  //TIM �����ж�Դ   
    ENABLE           //ʹ��  
    );  
    
  //�������ȼ�  

  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0��  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //�����ȼ�0��  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);   

  TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx����  
}  


void TIM1_UP_IRQHandler(void)   //TIM1�ж�
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM1�жϷ������:TIM1 �ж�Դ 
	{
	   TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM1 �ж�Դ 
	   
		//USART_SendData(USART1,dat);
		//DataSend();
		//USART_SendData(USART2,i ++);
		
	   /* ����д�ж� */
	
	}
}




