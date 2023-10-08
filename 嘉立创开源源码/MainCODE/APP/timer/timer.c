#include "timer.h"
#include "led.h"

/*定时器定时功能编程步骤：

	1,选择时钟，内部时钟，还需要是否倍频
	2，开启APB1总线定时器2外设时钟（定时器2总的开关）
	
	3，设置自动重载寄存器的值.预分频值
	
	4，开启定时器中断
	
	5，设置优先级
	7，开启定时器
	
	8，编写定时器中断程序
	定时器：基本定时器功能
			输入捕获：结合超声波传感器（）  
			输出比较，或者PWM
			IIC：OLED显示屏
	第一阶段：
		
	
*/

//定时器2输入时钟72M
void Timer_Init(unsigned int pre,unsigned int arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
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
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//配置更新中断
	
	
	
	TIM_Cmd(TIM2, ENABLE);//开启定时器
}

////定时器中断函数 //500ms
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update) != RESET)
//	{
//		led = !led;
//	}
//	TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
//}
