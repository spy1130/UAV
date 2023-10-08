#include "pwm.h"

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM1_PWM_Init(u16 arr,u16 psc)//引脚PA8  PA11
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 使能定时器1
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80KHZ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx  通道1
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx  通道1

	//TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4预装载使能	 
	
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
 
   
}

void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	TIM_OCInitTypeDef TIM_OCInitTypeStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	//要开启复用功能的时钟才能重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE); 
	
	//TIM3部分重映射
	/*
	*查看数据手册，引脚的定时器通道是完全映射，还是部分映射
	*二者调用参数不相同
	*完全映射 ：GPIO_FullRemap_TIM4
	*部分映射 ：GPIO_PartialRemap_TIM4
	*/
	
	//设置该引脚为复用输出功能
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化TIM4
	TIM_TimeBaseStruct.TIM_Period = arr;//重装载值 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;//预分频值 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //时钟分频1、2、4分频	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
	
	//初始化输出比较参数
	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式
	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性
	TIM_OC1Init(TIM4,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1
	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH1
	
	//使能预装载寄存器
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	//使能定时器
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
//	//要开启复用功能的时钟才能重映射
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE); 
//	
//	//TIM3部分重映射
//	/*
//	*查看数据手册，引脚的定时器通道是完全映射，还是部分映射
//	*二者调用参数不相同
//	*完全映射 ：GPIO_FullRemap_TIM4
//	*部分映射 ：GPIO_PartialRemap_TIM4
//	*/
//	
//	//设置该引脚为复用输出功能
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStruct);
//	
//	//初始化TIM4
//	TIM_TimeBaseStruct.TIM_Period = arr;//重装载值 
//	TIM_TimeBaseStruct.TIM_Prescaler = psc;//预分频值 
//	TIM_TimeBaseStruct.TIM_ClockDivision = 0; //时钟分频1、2、4分频	
//	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;//设置计数模式
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);
//	
//	//初始化输出比较参数
//	TIM_OCInitTypeStruct.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式
//	TIM_OCInitTypeStruct.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
//	TIM_OCInitTypeStruct.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性
//	TIM_OC2Init(TIM4,&TIM_OCInitTypeStruct); //选择定时器输出通道 TIM4_CH2
//	
//	//使能预装载寄存器
//	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
//	
//	//使能定时器
//	TIM_Cmd(TIM4,ENABLE);
//}

