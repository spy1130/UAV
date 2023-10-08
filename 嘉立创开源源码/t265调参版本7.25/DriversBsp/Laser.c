#include "Laser.h"

void DvrLaserInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOD, GPIO_Pin_12);

}

void Laser_On_Off(u8 on)
{
	if(on==1){
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	}
	else{
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}
}
