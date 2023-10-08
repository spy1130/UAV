#include "led.h"
#include "bit_operation.h"

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//开启GPIOA的时钟
		
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC ,&GPIO_InitStruct);
	
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);
	led = 1;
}
 

#if 0
void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA的时钟
		
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin   = LED_PORT_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_PORT ,&GPIO_InitStruct);
	
	GPIO_SetBits(LED_PORT,LED_PORT_PIN);	  
}

//button.c button.o obj
void LED_Operation(unsigned int flag)
{
	switch(flag)
	{
		case 0:
			PAout(7)= 0;
			break;
		case 1:
			PAout(7)= 1;
			break;
	
		default:
			break;
	}
}
#endif
