#include "drv_beep.h"

void beep_init()
{
	  GPIO_InitTypeDef GPIO_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能 GPIOA 时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;						//设置GPIO口A9
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//设置GPIO口为推挽输出下拉
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置GPIO口速度50Mhz
		GPIO_Init(GPIOA,&GPIO_InitStructure);					//初始化GPIOB

		GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_SET);	
}

void beep_bsp(unsigned int flag)
{
	if(flag == 1)GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_SET);
	if(flag == 0)GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_RESET);	
}

void beep_delay()
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_SET);
	GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_RESET);	
	MyDelayMs(300);
	GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_SET);
}	
