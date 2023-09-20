#include "task_call.h"

 void task_read_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC| RCC_AHB1Periph_GPIOD, ENABLE);//Ê¹ÄÜGPIOFÊ±ÖÓ
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}



u8 task_read(void)
{
	u8 bit1,bit2;
	
	task_read_gpio_config();
	
	bit1 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6);
	bit2 = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7);
	
	if(bit1 == 0 && bit2 == 0)
		return 1;
	else if(bit1 == 1 && bit2 == 0)
		return 2;
	else if(bit1 == 0 && bit2 == 1)
		return 3;
	else
		return 4;
}
