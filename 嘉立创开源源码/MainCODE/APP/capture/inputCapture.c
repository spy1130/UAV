/*
PA2:TIM2_CH3
*/
/*
输入捕获：
1，配置定时器的基本定时功能
2，配置GPIO
3，配置输入捕获相关参数
4，配置中断
5，编写中断程序
*/
#include "inputCapture.h"

void TIM2_Capture_Init(unsigned int pre,unsigned int arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能定时器2时钟
	
	//设置2，设置分频系数
	//3，设置自动重载寄存器的值
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
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA的时钟

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_3;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICFilter = 0;
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);//开启定时器	
}

/*
	flag：最高位：用于表示成功捕获了下降沿
		  次高位：用于表示成功捕获了上升沿
		  低6位用于表示发生了多少次更新中断
*/
/*
捕获值：num = ((dat-0) + (flag & 0X3F) *arr) 
捕获时间：t = num * (1/clk) 
clk:给定时器输入的时钟周期
*/
unsigned char flag = 0;
unsigned char dat = 0;


void TIM2_IRQHandler(void)
{
	if((flag & 0x80) == 0)//1000 0000
	{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)//更新中断
		{
			if(flag & 0X40)//捕获到高电平  0100 0000
			{
				if((flag & 0X3F) == 0X3F) //最大值处理   0x3f * 0xffff
				{
					flag |= 0X80;//标记成功捕获了一次
					dat = 0XFF;
				}
				else 
					flag++;
			}	
		}
		
		else if(TIM_GetITStatus(TIM2,TIM_IT_CC3) != RESET)//输入捕获中断
		{
			if(flag & 0X40)		//捕获到一个上升沿		
			{	  			
				flag |= 0X80;//捕获到了下降沿		
				dat = TIM_GetCapture3(TIM2);
				
				TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising); 
			}
			else  							
			{
				flag = 0;			//清空
				dat = 0;
				TIM_SetCounter(TIM2,0);
				flag |= 0X40;		//标记捕获到了上升沿
				TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);		
			}	
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update | TIM_IT_CC3);
}


