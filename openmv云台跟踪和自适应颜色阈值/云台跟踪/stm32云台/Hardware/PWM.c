#include "stm32f10x.h"                  // Device header

/*************************************
*函  数  名	：PWM_Init()
*函数功能	：PWM初始化
*输	入	：无
*输	出	：无
*************************************/
void PWM_Init(void)
{
	//RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//配置GPIO，PWM波形需要借用GPIO口来输出
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置时基单元
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;										//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;										//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//初始化输出比较单元
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
*函  数  名	：void PWM_SetCompare_x(uint16_t Compare_x)
*函数功能	：设置x轴PWM的CCR的值
*输	入	：PID算法后的驱动值x
*输	出	：无
*************************************/
void PWM_SetCompare_x(uint16_t Compare_x)														//在运行中更改CCR的值，CCR初始化为0
{
	TIM_SetCompare1(TIM3, Compare_x);																	//这是设置CCR的值，并不是直接设置占空比
}



/*************************************
*函  数  名	：void PWM_SetCompare_y(uint16_t Compare_y)
*函数功能	：设置y轴PWM的CCR的值
*输	入	：PID算法后的驱动值y
*输	出	：无
*************************************/
void PWM_SetCompare_y(uint16_t Compare_y)
{
	TIM_SetCompare2(TIM3, Compare_y);																	//这是设置CCR的值，并不是直接设置占空比
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
*函  数  名	：HSE_sysclock_config()
*函数功能	：由于我们的pcb板的晶振有问题，这里需要配置系统时钟，并且打开魔法棒配置Xtal为8.0MHz（可删）
*输	入	：无
*输	出	：无
*************************************/
void HSE_sysclock_config(void)
{
    RCC_DeInit();    //先复位RCC寄存器
    RCC_HSEConfig( RCC_HSE_ON );    //使能HSE
    //检测HSE是否启动成功
    if ( SUCCESS == RCC_WaitForHSEStartUp() )
    {
        //使能预取指，这是FLASH固件中的函数
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        //设置FLASH等待周期。因为倍频成72M 所以等待两个周期。
        FLASH_SetLatency(FLASH_Latency_2);  
        //配置三个总线的倍频因子
        //HCLK --> AHB 最大为72M,所以只需要1分频
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        //PCLK1 --> APB1 最大为36M,所以需要2分频
		RCC_PCLK1Config(RCC_HCLK_Div2);
        //PCLK2 --> APB2 最大为72M,所以只需要1分频
		RCC_PCLK2Config(RCC_HCLK_Div1);
        //先配置锁相环 PLLCLK = HSE * 倍频因子
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);        //使能PLL
        while ( RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET );  //等待PLL稳定
        //选择系统时钟（选择锁相环输出）
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        //等待选择稳定
        while ( RCC_GetSYSCLKSource() != 0x08 );
    }
    else
    {
        //HSE启动失败
    }

}

