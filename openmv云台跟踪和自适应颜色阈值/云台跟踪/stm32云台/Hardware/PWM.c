#include "stm32f10x.h"                  // Device header

/*************************************
*��  ��  ��	��PWM_Init()
*��������	��PWM��ʼ��
*��	��	����
*��	��	����
*************************************/
void PWM_Init(void)
{
	//RCC����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//����GPIO��PWM������Ҫ����GPIO�������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����ʱ����Ԫ
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;										//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;										//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//��ʼ������Ƚϵ�Ԫ
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;																	//CCR
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM3, ENABLE);
}

/*************************************
*��  ��  ��	��void PWM_SetCompare_x(uint16_t Compare_x)
*��������	������x��PWM��CCR��ֵ
*��	��	��PID�㷨�������ֵx
*��	��	����
*************************************/
void PWM_SetCompare_x(uint16_t Compare_x)														//�������и���CCR��ֵ��CCR��ʼ��Ϊ0
{
	TIM_SetCompare1(TIM3, Compare_x);																	//��������CCR��ֵ��������ֱ������ռ�ձ�
}



/*************************************
*��  ��  ��	��void PWM_SetCompare_y(uint16_t Compare_y)
*��������	������y��PWM��CCR��ֵ
*��	��	��PID�㷨�������ֵy
*��	��	����
*************************************/
void PWM_SetCompare_y(uint16_t Compare_y)
{
	TIM_SetCompare2(TIM3, Compare_y);																	//��������CCR��ֵ��������ֱ������ռ�ձ�
}

void Servo_SetAngle_x(float Angle)
{
	PWM_SetCompare_x(Angle / 180 * 2000 + 500);
}

void Servo_SetAngle_y(float Angle)
{
	PWM_SetCompare_y(Angle / 180 * 2000 + 500);
}


/*************************************
*��  ��  ��	��HSE_sysclock_config()
*��������	���������ǵ�pcb��ľ��������⣬������Ҫ����ϵͳʱ�ӣ����Ҵ�ħ��������XtalΪ8.0MHz����ɾ��
*��	��	����
*��	��	����
*************************************/
void HSE_sysclock_config(void)
{
    RCC_DeInit();    //�ȸ�λRCC�Ĵ���
    RCC_HSEConfig( RCC_HSE_ON );    //ʹ��HSE
    //���HSE�Ƿ������ɹ�
    if ( SUCCESS == RCC_WaitForHSEStartUp() )
    {
        //ʹ��Ԥȡָ������FLASH�̼��еĺ���
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        //����FLASH�ȴ����ڡ���Ϊ��Ƶ��72M ���Եȴ��������ڡ�
        FLASH_SetLatency(FLASH_Latency_2);  
        //�����������ߵı�Ƶ����
        //HCLK --> AHB ���Ϊ72M,����ֻ��Ҫ1��Ƶ
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        //PCLK1 --> APB1 ���Ϊ36M,������Ҫ2��Ƶ
		RCC_PCLK1Config(RCC_HCLK_Div2);
        //PCLK2 --> APB2 ���Ϊ72M,����ֻ��Ҫ1��Ƶ
		RCC_PCLK2Config(RCC_HCLK_Div1);
        //���������໷ PLLCLK = HSE * ��Ƶ����
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);        //ʹ��PLL
        while ( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET );  //�ȴ�PLL�ȶ�
        //ѡ��ϵͳʱ�ӣ�ѡ�����໷�����
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        //�ȴ�ѡ���ȶ�
        while ( RCC_GetSYSCLKSource() != 0x08 );
    }
    else
    {
        //HSE����ʧ��
    }

}

