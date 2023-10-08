
/*
#include "DrvServo.h"
#include "Ano_Math.h"

void ServoInit(u16 arr,u16 psc){
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    uint16_t PrescalerValue = 0;
    u32 hz_set = ACCURACY * PWM_FRE_HZ;

    GPIO_StructInit(&GPIO_InitStructure);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);

    hz_set = LIMIT(hz_set, 1, 84000000);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_AHB1Periph_GPIOD, ENABLE);


    /////////////////////////////////////////////////////////////////////////////
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14; //GPIO_Pin_0 | GPIO_Pin_1 |
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //  GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
    //  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_TIM4);//--------------------------------------source？？？？？？

    / /Compute the prescaler value 
    PrescalerValue = (uint16_t)((SystemCoreClock / 2) / hz_set) - 1;
    // Time base configuration 
    TIM_TimeBaseStructure.TIM_Period = ACCURACY;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    //   PWM1 Mode configuration: Channel1 
    //  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    //  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    //  TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    //  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

    //   PWM1 Mode configuration: Channel2 
    //  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    //  TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    //  TIM_OC2Init(TIM5, &TIM_OCInitStructure);
    //  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

    // PWM1 Mode configuration: Channel3 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC3Init(TIM5, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

    // PWM1 Mode configuration: Channel4 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC4Init(TIM5, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM5, ENABLE);
    TIM_Cmd(TIM5, ENABLE);
    /////////////////////////////////////////////////////////////////////////////
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_TIM1);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_TIM1);

    // Compute the prescaler value 
    PrescalerValue = (uint16_t)((SystemCoreClock) / hz_set) - 1;
    // Time base configuration 
    TIM_TimeBaseStructure.TIM_Period = ACCURACY;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    // PWM1 Mode configuration: Channel1 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // PWM1 Mode configuration: Channel2
    //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // PWM1 Mode configuration: Channel3 
    //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // PWM1 Mode configuration: Channel4 
    //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
    ////////////////////////////////////////////////////////////////////////////////////

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);

    // Compute the prescaler value 
    PrescalerValue = (uint16_t)((SystemCoreClock) / hz_set) - 1;
    // Time base configuration 
    TIM_TimeBaseStructure.TIM_Period = ACCURACY;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    // PWM1 Mode configuration: Channel3 
    //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC3Init(TIM8, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    // PWM1 Mode configuration: Channel4 
    //TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = INIT_DUTY;
    TIM_OC4Init(TIM8, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_CtrlPWMOutputs(TIM8, ENABLE);
    TIM_ARRPreloadConfig(TIM8, ENABLE);
    TIM_Cmd(TIM8, ENABLE);

#if (ESC_CALI == 1)
    //校准时先给最大油门。
    TIM1->CCR4 = 2 * INIT_DUTY; //1
    TIM1->CCR3 = 2 * INIT_DUTY; //2
    TIM1->CCR2 = 2 * INIT_DUTY; //3
    TIM1->CCR1 = 2 * INIT_DUTY; //4

    TIM5->CCR4 = 2 * INIT_DUTY; //5
    TIM5->CCR3 = 2 * INIT_DUTY; //6
    TIM8->CCR4 = 2 * INIT_DUTY; //7
    TIM8->CCR3 = 2 * INIT_DUTY; //8
#endif


}

*/
