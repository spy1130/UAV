#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "OLED.h"

float Cx=0,Cy=0;
uint8_t RxFlag1=0;

/*************************************
*��  ��  ����	Serial_Init()
*�������ܣ���ʼ������
*��	��	����
*��	��	����
*************************************/
void Serial_Init(void)
{
	//��һ��������ʱ�ӣ���USART��GPIO�Ĵ�
	//�ڶ�����GPIO��ʼ������TX���óɸ��������RX���ó�����
	//������������USART
	//���Ĳ�����ֻ�÷��͹��ܾ�ֱ�ӿ���USART����Ҫ�н��չ��ܻ��������ж�
	
	//��һ��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);													//����USARTʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);														//�����ǣУɣ�ʱ��
	
	//�ڶ�����GPIO��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;																	//���������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//��X
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;																		//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//������������USART
	USART_InitTypeDef USART_InitStructure;																					//����ṹ��
	USART_InitStructure.USART_BaudRate = 115200;																		//������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;									//����ģʽ�����ͺͽ���ģʽ
	USART_InitStructure.USART_Parity = USART_Parity_No;															//У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;													//ֹͣλ����Ϊ��λֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;											//�ֳ�
	USART_Init(USART1, &USART_InitStructure);																				//��ʼ��
	
	//���Ĳ��������ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);																	//����RXNE��־λ��NVIC�����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);																	//����
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);																											//ʹ�ܣգӣ��ң�
}

/*************************************
*��  ��  ��	��USART1_IRQHandler()
*��������	������openmvʶ��Ŀ���xy����
*��	��	����
*��	��	����
*************************************/
void USART1_IRQHandler(void)																											//�жϴ�����
{
		u8 com_data; 
		static u8 RxCounter1=0;
		static float RxBuffer1[10]={0};
		static u8 RxState = 0;	
		//static u8 RxFlag1 = 0;


		if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  	  									 		//�����ж�  
		{
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);   													//����жϱ�־
				com_data = USART_ReceiveData(USART1);
			
				if(RxState==0&&com_data==0x2C)  																					//0x2c֡ͷ
				{
					
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=5||com_data == 0x5B)       															//RxBuffer1��������,�������ݽ���
					{
						RxState=2;
						RxFlag1=1;
						Cx=RxBuffer1[RxCounter1-3];
						Cy=RxBuffer1[RxCounter1-2];
					}
				}
		
				else if(RxState==2)																												//����Ƿ���ܵ�������־
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{	
									USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);										//�ر�DTSABLE�ж�
									if(RxFlag1)
									{
									//OLED_ShowNum(1, 1,RxCounter1,4);//RxCounter1����Ϊ4
//										OLED_ShowNum(1, 1,RxBuffer1[0],4);
//										OLED_ShowNum(2, 1,RxBuffer1[1],4);
//										OLED_ShowNum(3, 1,RxBuffer1[2],4);
//										OLED_ShowNum(4, 1,RxBuffer1[3],4);
//										OLED_ShowNum(4, 5,RxBuffer1[4],4);
									}
									RxFlag1 = 0;
									RxCounter1 = 0;
									RxState = 0;
									USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
						}
						else   //���մ���
						{
									RxState = 0;
									RxFlag1 = 0;
									RxCounter1=0;
								      memset(RxBuffer1,0,sizeof(RxBuffer1));
						}
				} 
	
				else   //�����쳣
				{
						RxState = 0;
						RxFlag1 = 0;
						RxCounter1=0;
					      memset(RxBuffer1,0,sizeof(RxBuffer1));
				}

		}
}


/*************************************
*��  ��  ��	Get_x()
*��������	�����x���ֵ
*��	��	����
*��	��	��x������
*************************************/
int Get_x(void)
{
	return Cx;
}


/*************************************
*��  ��  ��	Get_y()
*��������	�����y���ֵ
*��	��	����
*��	��	��y������
*************************************/
int Get_y(void)
{
	return Cy;
}


/*************************************
*��  ��  ��	Serial_flag()
*��������	���ж��Ƿ�ʶ��С��
*��	��	����
*��	��	����־λ
*************************************/
int Serial_flag()
{
	return RxFlag1;
}

