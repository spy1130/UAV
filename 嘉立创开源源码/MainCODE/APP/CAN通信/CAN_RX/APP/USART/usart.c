#include "usart.h"


/*串口编程步骤：
	1，设置GPIO时钟，设置串口1的时钟
	2，设置GPIO：PA9:TXD PA10:RXD
	3，设置相应的串口中断
	4，设置中断优先级
	5，开启相应的中断
	6，编写串口中断函数
*/

void Usart1_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//gpio时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//usart1时钟
	
	//PA9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//PA10
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority= 2;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_InitStruct.USART_BaudRate = baud;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruct);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//开启相应的串口中断
	USART_Cmd(USART1,ENABLE);//串口使能
	
}



//0X0D 0X0A
void USART1_IRQHandler(void)
{
	unsigned char dat;
	if(RESET != USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		dat = USART_ReceiveData(USART1);

		if((sta & 0x8000)==0)
		{
			if(sta & 0x4000)
			{
				if(dat !=0x0a )
					sta = 0;
				else 
					sta |= 0x8000;	
			}
			else 
			{	
				if(dat == 0x0d)
					sta |= 0x4000;
				else
				{
					usart1_data[sta & 0X3FFF] = dat ;
					sta++;
					if(sta == LEN)
						sta=0;	  
				}		 
			}
			USART_SendData(USART1,dat);
		} 
			
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE //结构体变量
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR & 0X40) == 0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

















