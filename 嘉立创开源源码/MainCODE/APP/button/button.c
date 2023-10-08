#include "button.h"
#include "led.h"
#include "delay.h"

int button_flag = 0;

//按键设置为上拉输入
void Button_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOB的时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//开启AFIO时钟
	
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin   = BUTTON_PORT_PIN;//设置为上拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUTTON_PORT ,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
	
	EXTI_InitStruct.EXTI_Line=     EXTI_Line10;//GPIOB_10
	EXTI_InitStruct.EXTI_LineCmd=  ENABLE;
	EXTI_InitStruct.EXTI_Mode    =  EXTI_Mode_Interrupt;//中断模式
	EXTI_InitStruct.EXTI_Trigger =  EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority= 2;//0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=  2;      //0-3
	NVIC_Init(&NVIC_InitStruct);
	
}

void doubixiaohanhan_HANDLER(void)
{
	//按键需要消抖
	//EXTI_GetFlagStatus 返回值1 有中断产生
	if(EXTI_GetFlagStatus(EXTI_Line10) == 1)
	{
		delay_ms(20);
		if(EXTI_GetFlagStatus(EXTI_Line10) == 1)
		{
			button_flag = ! button_flag;
		}
	}
	#if 0
	if(button_flag != 0)
	{
		LED_Operation(0);//LED点亮
	}
	else
	{
		LED_Operation(1);//LED熄灭
	}
	#endif
	EXTI_ClearITPendingBit(EXTI_Line10);
}



