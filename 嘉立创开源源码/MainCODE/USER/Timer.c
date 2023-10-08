#include "Timer.h"
#include "LX_DT.h"

/*
1,时钟使能
2,配置预分频、自动重装值和重复计数值
3,清除中断标志位（否则会先进一次中断）
4,使能TIM中断，选择中断源
5,设置中断优先级
6,使能TIMx外设

arr：自动重装值  
psc：时钟预分频数  
*/

extern u8 dat;

void Timer1_Init(u16 arr,u16 psc)  

{  

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  NVIC_InitTypeDef NVIC_InitStructure;  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能  
  
  TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器周期值  
  TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);//设置预分频值 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数设置  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //参数初始化  

  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位  

  TIM_ITConfig(      //使能或者失能指定的TIM中断  
    TIM1,            //TIM1  
    TIM_IT_Update  | //TIM 更新中断源  
    TIM_IT_Trigger,  //TIM 触发中断源   
    ENABLE           //使能  
    );  
    
  //设置优先级  

  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级0级  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //从优先级0级  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);   

  TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设  
}  


void TIM1_UP_IRQHandler(void)   //TIM1中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM1中断发生与否:TIM1 中断源 
	{
	   TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM1 中断源 
	   
		//USART_SendData(USART1,dat);
		//DataSend();
		//USART_SendData(USART2,i ++);
		
	   /* 这里写中断 */
	
	}
}




