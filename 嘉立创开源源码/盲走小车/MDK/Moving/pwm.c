#include "pwm.h"
void PWM_Int(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;                //����ṹ��GPIO_InitStructure
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      //����ṹ��TIM_TimeBaseStructure   
	TIM_OCInitTypeDef TIM_OCInitStructure;              //����ṹ��TIM_OCInitStructure
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PB�˿�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ�ܶ�ʱ��3
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //����ģʽ���
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1; //PB0 ��PB1
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz;        //IO���ٶ�
	GPIO_Init(GPIOB,&GPIO_InitStructure);        	//GPIO��ʼ��
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr;                //������һ�����»���Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;             //Ԥ����ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;           //ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode= TIM_OCMode_PWM1;             //PWM�����ȵ���1
	TIM_OCInitStructure.TIM_Pulse = 0;                           //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //����TIM�������Ϊ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	
	TIM_CtrlPWMOutputs(TIM3,ENABLE);//�����ʹ��
	
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);//ʹ��Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);              //ʹ���Զ�װ������λ
	TIM_Cmd(TIM3,ENABLE);//������ʱ��3
}
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u16 arr,u16 psc)//����PA8  PA11
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// ʹ�ܶ�ʱ��1
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80KHZ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx  ͨ��1
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx  ͨ��1

	//TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 
	
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
 
   
}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	//Ҫ�������ù��ܵ�ʱ�Ӳ�����ӳ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE); 
	
	//TIM3������ӳ��
	/*
	*�鿴�����ֲᣬ���ŵĶ�ʱ��ͨ������ȫӳ�䣬���ǲ���ӳ��
	*���ߵ��ò�������ͬ
	*��ȫӳ�� ��GPIO_FullRemap_TIM4
	*����ӳ�� ��GPIO_PartialRemap_TIM4
	*/
	
	//���ø�����Ϊ�����������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//��ʼ��TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//��װ��ֵ 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//Ԥ��Ƶֵ 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //ʱ�ӷ�Ƶ1��2��4��Ƶ	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ü���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//��ʼ������Ƚϲ���
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//�������
	TIM_OC1Init(TIM4,&TIM_OCInitTypeStruct); //ѡ��ʱ�����ͨ�� TIM4_CH1
	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //ѡ��ʱ�����ͨ�� TIM4_CH1
	
	//ʹ��Ԥװ�ؼĴ���
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM4,ENABLE);
}

//void TIM4_CH2_PWM_Init(u16 arr,u16 psc)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
//	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
//	
//	//Ҫ�������ù��ܵ�ʱ�Ӳ�����ӳ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE); 
//	
//	//TIM3������ӳ��
//	/*
//	*�鿴�����ֲᣬ���ŵĶ�ʱ��ͨ������ȫӳ�䣬���ǲ���ӳ��
//	*���ߵ��ò�������ͬ
//	*��ȫӳ�� ��GPIO_FullRemap_TIM4
//	*����ӳ�� ��GPIO_PartialRemap_TIM4
//	*/
//	
//	//���ø�����Ϊ�����������
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStruct);
//	
//	//��ʼ��TIM4
//	TIM_TimeBaseStruct.TIM_Period = arr;//��װ��ֵ 
//	TIM_TimeBaseStruct.TIM_Prescaler = psc;//Ԥ��Ƶֵ 
//	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //ʱ�ӷ�Ƶ1��2��4��Ƶ	
//	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ü���ģʽ
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
//	
//	//��ʼ������Ƚϲ���
//	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ
//	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
//	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//�������
//	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //ѡ��ʱ�����ͨ�� TIM4_CH2
//	
//	//ʹ��Ԥװ�ؼĴ���
//	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	
//	//ʹ�ܶ�ʱ��
//	TIM_Cmd(TIM4,ENABLE);
//}

