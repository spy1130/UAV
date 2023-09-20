//#include "led.h"

////////////////////////////////////////////////////////////////////////////////////	 
////本程序只供学习使用，未经作者许可，不得用于其它任何用途
////ALIENTEK 精英STM32开发板
////LED驱动代码	   
////正点原子@ALIENTEK
////技术论坛:www.openedv.com
////修改日期:2012/9/2
////版本：V1.0
////版权所有，盗版必究。
////Copyright(C) 广州市星翼电子科技有限公司 2009-2019
////All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////// 	   

#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK 精英STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   
/////////////////////////////////////////


void key_init_r_c(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;		  
	 
	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE); 
	  
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14| GPIO_Pin_15;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		    
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7| GPIO_Pin_8;//pa6 is pwm so here i can't be set
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		    
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//	GPIO_SetBits(GPIOB,GPIO_Pin_4 | GPIO_Pin_5|GPIO_Pin_6 | GPIO_Pin_8);//resetBits means pull down ;setBits means pull up
//	
	
}

void backup_uart_io_stop_io_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;		  
	 
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE); 
	  
	 GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//GPIO_Mode_Out_PP;		    
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//| GPIO_Pin_5 | GPIO_Pin_7| GPIO_Pin_8;//pa6 is pwm so here i can't be set
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		    
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
}


