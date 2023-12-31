#include "SysConfig.h"

void NMI_Handler(void)
{
}

void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
}

#include "Drv_RcIn.h"
void TIM3_IRQHandler(void)
{
	PPM_IRQH();
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
		
		TIM_SetCounter(TIM4,0);
		TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
	
		TIM_Cmd(TIM4,ENABLE);
	}
}

#include "ANO_LX.h"
void TIM7_IRQHandler(void)
{
	//
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_FLAG_Update);
		//==user code==
		ANO_LX_Task();
	}
}
#include "Drv_Uart.h"
void USART1_IRQHandler(void)
{
	Usart1_IRQ();
}

void USART2_IRQHandler(void)
{
	Usart2_IRQ();
}

void USART3_IRQHandler(void)
{
	Usart3_IRQ();
}

void UART4_IRQHandler(void)
{
	Uart4_IRQ();
}

void UART5_IRQHandler(void)
{
	Uart5_IRQ();
}
void USART6_IRQHandler(void)
{
	Sbus_IRQH();
}
