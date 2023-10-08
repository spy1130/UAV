#include "usart.h"


/*���ڱ�̲��裺
	1������GPIOʱ�ӣ����ô���1��ʱ��
	2������GPIO��PA9:TXD PA10:RXD
	3��������Ӧ�Ĵ����ж�
	4�������ж����ȼ�
	5��������Ӧ���ж�
	6����д�����жϺ���
*/

void Usart1_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//gpioʱ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//usart1ʱ��
	
	//PA9
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//����
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
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//������Ӧ�Ĵ����ж�
	USART_Cmd(USART1,ENABLE);//����ʹ��
	
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


//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE //�ṹ�����
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR & 0X40) == 0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

















