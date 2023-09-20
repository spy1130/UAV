//#include "UART.h"
#include "config.h"

#define USART2_SR 			*(u32 *)0x40004400
#define USART2_SR_RXNE 		(USART2_SR & (1<<5))
#define USART2_SR_TC 		(USART2_SR & (1<<6))
#define USART2_SR_ORE 		(USART2_SR & (1<<3))
#define USART2_SR_LBD 		(USART2_SR & (1<<8))

#define USART1_SR 			*(u32 *)0x40013800
#define USART1_SR_RXNE 		(USART1_SR & (1<<5))
#define USART1_SR_TC 		(USART1_SR & (1<<6))
#define USART1_SR_ORE 		(USART1_SR & (1<<3))
#define USART1_SR_LBD 		(USART1_SR & (1<<8))


extern u8 UART2_busy;
extern u8 UART1_busy;
extern u8 receive[42];
extern u8 flag;
extern u32 flag1s;
extern u32 pack_num;
extern u8 one_pack_flag;

void SysTick_Handler(void)
{
}

//void  USART2_IRQHandler(void)
//{
//    if(USART_SR_RXNE != 0)  //�������жϱ�־λ    
//    {
//		USART2_SR &= ~(1<<5);//��������жϱ�־λ	
//    }
//	if(USART2_SR_TC != 0)//��������ж�
//	{
//		USART2_SR &= ~(1<<6);//��������жϱ�־λ
//		UART2_busy = 0;
//	}
//	
//	if(USART2_SR_ORE != 0)//���ر�־
//	{
//		USART2_SR &= ~(1<<3);//��������ж�
//	}
//}

//void  USART1_IRQHandler(void)
//{
//	static u8 i = 0;
//	u8 buff;
//	
//    if(USART1_SR_RXNE != 0)  //�������жϱ�־λ    
//    {
//		USART1_SR &= ~(1<<5);//��������жϱ�־λ
//		buff = USART_ReceiveData(USART1);
//		if((buff == 0xFA) && (receive[0] != 0xFA))
//		{
//			i = 1;
//			receive[0] = buff;
//			return;
//		}
//		receive[i] = buff;
//		i++;
//		if(i>= 42)
//		{
//			i = 0;
//			pack_num++;
//			//one_pack_flag=1;
//			one_pack_flag=1;
//		}
//    }
//	if(USART1_SR_TC != 0)//��������ж�
//	{
//		USART1_SR &= ~(1<<6);//��������жϱ�־λ
//		UART1_busy = 0;
//	}
//	
//	if(USART1_SR_ORE != 0)//���ر�־
//	{
//		USART1_SR &= ~(1<<3);//��������ж�
//	}
//}














//void TIM2_IRQHandler(void)
//{
//	static u16 ti = 0;
//	
//	if (TIM_GetITStatus(TIM2, TIM_FLAG_Update) == SET) //����Ƿ�Ϊ����ж�
//	{
//		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); //����жϱ�־λ
//		ti++;
//		if(ti >= 20000)//40s��ʱ
//		{
//			ti = 0;
//			flag = 1;
//		}
//	}
//}




void  USART3_IRQHandler(void)
{
//	static u8 i = 0;
	u8 buff;
	
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
	{
//		USART3_SR &= ~(1<<5);//��������жϱ�־λ
		buff = USART_ReceiveData(USART3);
		
    }
	
}

