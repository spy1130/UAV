#include "UART.h"

extern u8 UART2_busy;
extern u8 UART1_busy;




u8 rx_buff[20]={0};
u8 rx_end_flag=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx_star_flag=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx_num=0,command_text=0x00;

u8 rx2_buff[20]={0};
u8 rx2_end_flag=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx2_star_flag=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx2_num=0,command_text2=0x00;
void UART3_Init(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); 

	
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;     //tx
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;   //rx 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	NVIC_InitTypeDef NVIC_InitStructure;
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         //ѡ��USART2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //������Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ��ͨ��
    NVIC_Init(&NVIC_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      //ʹ��USART2ʱ��
    USART_InitStructure.USART_BaudRate = baud;                  //���ò�����Ϊbaud
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����Ϊ8λ����λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //����Ϊ1λֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;         //��ʹ����żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //����Ӳ��������
    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //ѡ��USART���ͺͽ���ģʽ
    USART_Init(USART3, &USART_InitStructure);                     //��ʼ��USART1
	
//    USART_ITConfig(USART3,USART_IT_TC, ENABLE); 	//�������ڷ�������ж�	
	USART_ITConfig(USART3,USART_IT_RXNE, ENABLE); 	//�������ڽ����ж�
    USART_Cmd(USART3,ENABLE);                     	//ʹ��USART2
}

void UART2_Init(u32 baud)
{
				GPIO_InitTypeDef GPIO_InitStructure;                         
				USART_InitTypeDef USART_InitStructure;
				NVIC_InitTypeDef NVIC_InitStructure;
				
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE); 
				
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;             
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOA , &GPIO_InitStructure);
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;               
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_Init(GPIOA , &GPIO_InitStructure);
				
				USART_InitStructure.USART_BaudRate = baud;           
				USART_InitStructure.USART_WordLength = USART_WordLength_8b;
				USART_InitStructure.USART_StopBits = USART_StopBits_1;
				USART_InitStructure.USART_Parity = USART_Parity_No;
				USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
				USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
				USART_Init(USART2,&USART_InitStructure);                   
				
				NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;       
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
				NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;       
				NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         
				NVIC_Init(&NVIC_InitStructure);                         
				
				USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);           
				USART_Cmd(USART2,ENABLE);
}




//void UART2_Init(u32 baud)
//{
//		GPIO_InitTypeDef GPIO_InitStructure;
//    
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;             //TXD����-PA2
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //����Ϊ�����������
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //�������50MHz
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;            //RXD����-PA3
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//		NVIC_InitTypeDef NVIC_InitStructure;
//    
//    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;         //ѡ��USART2�ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //������ռ���ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //������Ӧ���ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ��ͨ��
//    NVIC_Init(&NVIC_InitStructure);
//	
//	  USART_InitTypeDef USART_InitStructure;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);      //ʹ��USART2ʱ��
//    USART_InitStructure.USART_BaudRate = baud;                  //���ò�����Ϊbaud
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����Ϊ8λ����λ
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //����Ϊ1λֹͣλ
//    USART_InitStructure.USART_Parity = USART_Parity_No;         //��ʹ����żУ��
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //����Ӳ��������
//    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //ѡ��USART���ͺͽ���ģʽ
//    USART_Init(USART2, &USART_InitStructure);                     //��ʼ��USART1
//	
//    USART_ITConfig(USART2,USART_IT_TC, ENABLE); 	//�������ڷ�������ж�	
//	  USART_ITConfig(USART2,USART_IT_RXNE, ENABLE); 	//�������ڽ����ж�
//    USART_Cmd(USART2,ENABLE);                     	//ʹ��USART2
//}

void UART2_Send(u8 UARTdat)
{
	while(UART2_busy);
	UART2_busy = 1;
	USART_SendData(USART2, UARTdat);
}

void UART2_SendStr(uc8 *dat)
{
	while(*dat != '\0')
	{
		UART2_Send(*dat++);
	}
}




void UART2_SendStr_xm(uc8 *DataToSend, u8 data_num)
{
	
	u8 i;
    for (i = 0; i < data_num; i++)
    {
        UART2_Send(*DataToSend++);
    }

//    if (!(UART5->CR1 & USART_CR1_TXEIE))
//    {
//        USART_ITConfig(UART5, USART_IT_TXE, ENABLE); //�򿪷����ж�
//    }
	
	
}

//void USART2_IRQHandler(void)
//    {
//            uint8_t ucTemp;
//            if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
//            {                
//                    ucTemp = USART_ReceiveData(USART2);
//                   
//            }         
//    }
void clear_tx2_buff(void)
{
		rx2_buff[0]=0x00;
	 rx2_buff[1]=0x00;
	 rx2_buff[2]=0x00;
	 rx2_buff[3]=0x00;
	 rx2_buff[4]=0x00;
	 rx2_buff[5]=0x00;
	 rx2_buff[6]=0x00;
	rx2_buff[7]=0x00;
	 rx2_buff[8]=0x00;
	 rx2_buff[9]=0x00;
	 rx2_buff[10]=0x00;
	 rx2_buff[11]=0x00;
	rx2_buff[12]=0x00;
	 rx2_buff[13]=0x00;
	 rx2_buff[14]=0x00;
	 rx2_buff[15]=0x00;
	 rx2_buff[16]=0x00;
	 
	 rx2_num=0x00;
	 rx2_end_flag=0x00;
	 rx2_star_flag=0x00;
}

//void USART2_IRQHandler(void)                	//����1�жϷ������
//	{
//	u8 res2;
//#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntEnter();    
//#endif

   
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//		{
//            res2 =USART_ReceiveData(USART2);	//��ȡ���յ�������
//            

//             switch(rx2_num)
//             {
//                  case 0://freame star
//                 {
//                     if(0xaa==res2)
//                     {
//                         rx2_buff[0]=res2;
//                         rx2_num=0x01;
//                         rx2_end_flag=0x00;
//                         rx2_star_flag=0x01;
//                     }
//                     else
//                     {
//                         clear_tx2_buff();
//                     }
//                     
//                     
//                     break;
//                 } 
//                 case 1://freame star
//                 {
//                     if(0x29==res2)
//                     {
//                         rx2_buff[1]=res2;
//                         rx2_num=0x02;
//                         rx2_end_flag=0x00;
//                         rx2_star_flag=0x01;
//                     }
//                     else
//                     {
//                        clear_tx2_buff();
//                     }
//                     
//                     break;
//                 }
//								 case 2://freame star
//                 {
//                     if(0X05==res2)
//                     {
//                         rx2_buff[2]=res2;
//                         rx2_num=0x03;
//                         rx2_end_flag=0x00;
//                         rx2_star_flag=0x01;
//                     }
//                     else
//                     {
//                         clear_tx2_buff();
//                     }
//                     
//                     break;
//                 }
//                 case 3:///*�����֣�0X35ŷ���� 0X34λ�� 0X33�ٶ�*/
//                 {
//                    if(res2==0x33 || res2==0x34|| res2==0x35)
//										{
//											 rx2_buff[3]=res2;
//											 rx2_num=0x04;
//											 rx2_end_flag=0x00;
//											 rx2_star_flag=0x01;
//										}
//										else
//										{
//											clear_tx2_buff();
//										}	

//										
//                 }
//                 
//                 case 4://///*0X06*/����������Ϊ6���ֽڣ�2���ֽ��ٶȣ�2���ֽ�λ�ã�2���ֽڽǶ�
//                 {
//                     
//									 rx2_buff[4]=res2;
//									 rx2_num=0x05;
//									 rx2_end_flag=0x00;
//									 rx2_star_flag=0x01;
//                   break;                   
//                 }
//								 case 5://commamd 1
//                 {
//                     
//									 rx2_buff[5]=res2;
//									 rx2_num=0x06;
//									 rx2_end_flag=0x00;
//									 rx2_star_flag=0x01;
//                   break;                   
//                 }
//								 case 6://commamd 1
//                 {
//                     
//									 rx2_buff[6]=res2;
//									 rx2_num=0x07;
//									 rx2_end_flag=0x00;
//									 rx2_star_flag=0x01;
//                   break;                   
//                 }
//								 case 7:
//                 {
//                     
//									 rx2_buff[7]=res2;
//									 rx2_num=0x08;
//									 rx2_end_flag=0x00;
//									 rx2_star_flag=0x01;
//                   break;                   
//                 }
//								 case 8://commamd 1
//                 {
//                     
//									 rx2_buff[8]=res2;
//									 rx2_num=0x09;
//									 rx2_end_flag=0x00;
//									 rx2_star_flag=0x01;
//                   break;                   
//                 }
//								 case 9://
//                 {
//                     
//									 rx2_buff[9]=res2;
//									 rx2_num=0x0a;
//									 rx2_end_flag=0x00;
//									 rx2_star_flag=0x01;
//                   break;                   
//                 }
//								 case 10://commamd 1
//                 {
//                     
//									 rx2_buff[10]=res2;
//									 rx2_num=0x0b;
//									 rx2_end_flag=0x00;
//									 rx2_star_flag=0x01;
//                   break;                   
//                 }
//								
//				 
//								case 11:///*֡β*/
//											 {
//									 if(0x00==res2)
//									 {
//										 rx2_buff[11]=res2;
//										 rx2_num=0x00;
//										 rx2_star_flag=0x00;
//										 command_text2=rx2_buff[2];
//										 rx2_end_flag=0x01;
//										 
//									 }
//									 else
//									 {
//											clear_tx2_buff();
//												 
//												 
//									 }
//													 break;
//											 }
//							 default:
//								{
//								clear_tx2_buff();
//									
//									break;
//									
//								}
//									 }  		 
//     } 
//#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
//	OSIntExit();  											 
//#endif
//} 


void USART2_IRQHandler(void)
{
				uint8_t res2;
				if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
				{                
						res2 =USART_ReceiveData(USART2);	//��ȡ���յ�������
						switch(rx2_num)
             {
                  case 0://freame star
                 {
                     if(0xaa==res2)
                     {
                         rx2_buff[0]=res2;
                         rx2_num=0x01;
                         rx2_end_flag=0x00;
                         rx2_star_flag=0x01;
                     }
                     else
                     {
                         clear_tx2_buff();
                     }
                     
                     
                     break;
                 } 
                 case 1://freame star
                 {
                     if(0x29==res2)
                     {
                         rx2_buff[1]=res2;
                         rx2_num=0x02;
                         rx2_end_flag=0x00;
                         rx2_star_flag=0x01;
                     }
                     else
                     {
                        clear_tx2_buff();
                     }
                     
                     break;
                 }
								 
							 case 2://freame star
                 {
                     if(0X05==res2)
                     {
                         rx2_buff[2]=res2;
                         rx2_num=0x03;
                         rx2_end_flag=0x00;
                         rx2_star_flag=0x01;
                     }
                     else
                     {
                         clear_tx2_buff();
                     }
                     
                     break;
                 }
                 case 3:///*�����֣�0X35ŷ���� 0X34λ�� 0X33�ٶ�*/
                 {
                    if(res2==0x33 || res2==0x34|| res2==0x35)
										{
											 rx2_buff[3]=res2;
											 rx2_num=0x04;
											 rx2_end_flag=0x00;
											 rx2_star_flag=0x01;
										}
										else
										{
											clear_tx2_buff();
										}	
										
										 break;

										
                 }
                 
                 case 4://///*0X06*/����������Ϊ6���ֽڣ�2���ֽ��ٶȣ�2���ֽ�λ�ã�2���ֽڽǶ�
                 {
                     
									 rx2_buff[4]=res2;
									 rx2_num=0x05;
									 rx2_end_flag=0x00;
									 rx2_star_flag=0x01;
                   break;                   
                 }
								 case 5://commamd 1
                 {
                     
									 rx2_buff[5]=res2;
									 rx2_num=0x06;
									 rx2_end_flag=0x00;
									 rx2_star_flag=0x01;
                   break;                   
                 }
								 case 6://commamd 1
                 {
                     
									 rx2_buff[6]=res2;
									 rx2_num=0x07;
									 rx2_end_flag=0x00;
									 rx2_star_flag=0x01;
                   break;                   
                 }
								 case 7:
                 {
                     
									 rx2_buff[7]=res2;
									 rx2_num=0x08;
									 rx2_end_flag=0x00;
									 rx2_star_flag=0x01;
                   break;                   
                 }
								 case 8://commamd 1
                 {
                     
									 rx2_buff[8]=res2;
									 rx2_num=0x09;
									 rx2_end_flag=0x00;
									 rx2_star_flag=0x01;
                   break;                   
                 }
								 case 9://
                 {
                     
									 rx2_buff[9]=res2;
									 rx2_num=0x0a;
									 rx2_end_flag=0x00;
									 rx2_star_flag=0x01;
                   break;                   
                 }
								 case 10://commamd 1
                 {
                     
									 rx2_buff[10]=res2;
									 rx2_num=0x0b;
									 rx2_end_flag=0x00;
									 rx2_star_flag=0x01;
                   break;                   
                 }
								
				 
								case 11:///*֡β*/
											 {
									 if(0x00==res2)
									 {
										 rx2_buff[11]=res2;
										 rx2_num=0x00;
										 rx2_star_flag=0x00;
										 command_text2=rx2_buff[2];
										 rx2_end_flag=0x01;
										 
									 }
									 else
									 {
											clear_tx2_buff();
												 
												 
									 }
													 break;
											 }
							 default:
								{
								clear_tx2_buff();
									
									break;
									
								}
								
				} 
						 
			}
}






void UART1_Init(u32 baud)
{
//	GPIO_InitTypeDef GPIO_InitStructure;
//    
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;             //TXD����-PA9
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //����Ϊ�����������
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //�������50MHz
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            //RXD����-PA10
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	NVIC_InitTypeDef NVIC_InitStructure;
//    
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         //ѡ��USART2�ж�
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //������ռ���ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //������Ӧ���ȼ�
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ��ͨ��
//    NVIC_Init(&NVIC_InitStructure);
//	
//	USART_InitTypeDef USART_InitStructure;
//    
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);      //ʹ��USART2ʱ��
//    USART_InitStructure.USART_BaudRate = baud;                  //���ò�����Ϊbaud
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����Ϊ8λ����λ
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //����Ϊ1λֹͣλ
//    USART_InitStructure.USART_Parity = USART_Parity_No;         //��ʹ����żУ��
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //����Ӳ��������
//    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //ѡ��USART���ͺͽ���ģʽ
//		
//    USART_Init(USART1, &USART_InitStructure);                     //��ʼ��USART1
//	
//    //USART_ITConfig(USART1,USART_IT_TC, ENABLE); 	//�������ڷ�������ж�
//		USART_ITConfig(USART1,USART_IT_RXNE, ENABLE); 	//�������ڽ����ж�
//    USART_Cmd(USART1,ENABLE);                     	//ʹ��USART2

GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = baud;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  
  
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void UART1_Send(u8 UARTdat)
{
	while(UART1_busy);
	UART1_busy = 1;
	USART_SendData(USART1, UARTdat);
}

void UART1_SendStr(uc8 *dat)
{
	while(*dat != '\0')
	{
		UART1_Send(*dat++);
	}
}
void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
            res =USART_ReceiveData(USART1);	//��ȡ���յ�������
            

             switch(rx_num)
             {
                  case 0://freame star
                 {
                     if(0xa5==res)
                     {
                         rx_buff[0]=res;
                         rx_num=0x01;
                         rx_end_flag=0x00;
                         rx_star_flag=0x01;
                     }
                     else
                     {
                         rx_buff[0]=0x00;
                         rx_buff[1]=0x00;
                         rx_buff[2]=0x00;
                         rx_buff[3]=0x00;
                         rx_buff[4]=0x00;
                         rx_buff[5]=0x00;
                         rx_buff[6]=0x00;
													rx_buff[7]=0x00;
                         rx_buff[8]=0x00;
                         rx_buff[9]=0x00;
                         rx_buff[10]=0x00;
                         rx_buff[11]=0x00;
                         
                         rx_num=0x00;
                         rx_end_flag=0x00;
                         rx_star_flag=0x00;
                     }
                     
                     
                     break;
                 } 
                 case 1://freame star
                 {
                     if(0x5a==res)
                     {
                         rx_buff[1]=res;
                         rx_num=0x02;
                         rx_end_flag=0x00;
                         rx_star_flag=0x01;
                     }
                     else
                     {
                         rx_buff[0]=0x00;
                         rx_buff[1]=0x00;
                         rx_buff[2]=0x00;
                         rx_buff[3]=0x00;
                         rx_buff[4]=0x00;
                         rx_buff[5]=0x00;
                         rx_buff[6]=0x00;
												 rx_buff[7]=0x00;
                         rx_buff[8]=0x00;
                         rx_buff[9]=0x00;
                         rx_buff[10]=0x00;
                         rx_buff[11]=0x00;
                         
                         rx_num=0x00;
                         rx_end_flag=0x00;
                         rx_star_flag=0x00;
                     }
                     
                     break;
                 }
                 case 2://commamd 1
                 {
                     rx_buff[2]=res;
                     rx_num=0x03;
                     rx_end_flag=0x00;
                     rx_star_flag=0x01;
                     break;
                 }
                 
                 case 3://commamd 1
                 {
                     
                         rx_buff[3]=res;
                         rx_num=0x04;
                         rx_end_flag=0x00;
                         rx_star_flag=0x01;
                         
                     
                            break;      
                                 
                 }

				 
						case 4://end frame
                 {
										if(0xfd==res)
										 {
//											 rx_buff[4]=res;
//											 rx_num=0x05;
//											 rx_end_flag=0x00;
//											 rx_star_flag=0x01;
											 
											 rx_buff[13]=res;
											 rx_num=0x00;
										   rx_star_flag=0x00;
										   command_text=rx_buff[2];
										   rx_end_flag=0x01;
											 
										 }
										 else
										 {
											 rx_buff[0]=0x00;
											 rx_buff[1]=0x00;
											 rx_buff[2]=0x00;
											 rx_buff[3]=0x00;
											 rx_buff[4]=0x00;
											 rx_buff[5]=0x00;
											 rx_buff[6]=0x00;
											 rx_buff[7]=0x00;
											 rx_buff[8]=0x00;
											 rx_buff[9]=0x00;
											 rx_buff[10]=0x00;
											 rx_buff[11]=0x00;
											 
											 rx_num=0x00;
											 rx_end_flag=0x00;
											 rx_star_flag=0x00;
													 
													 
										 }
														 break;
									 }
				 
				  case 13://length
                 {
						 if(0x0a==res)
						 {
							 rx_buff[13]=res;
							 rx_num=0x00;
							 rx_star_flag=0x00;
							 command_text=rx_buff[2];
							 rx_end_flag=0x01;
							 
						 }
						 else
						 {
							 rx_buff[0]=0x00;
							 rx_buff[1]=0x00;
							 rx_buff[2]=0x00;
							 rx_buff[3]=0x00;
							 rx_buff[4]=0x00;
							 rx_buff[5]=0x00;
							 rx_buff[6]=0x00;
							 rx_buff[7]=0x00;
							 rx_buff[8]=0x00;
							 rx_buff[9]=0x00;
							 rx_buff[10]=0x00;
							 rx_buff[11]=0x00;
							 
							 rx_num=0x00;
							 rx_end_flag=0x00;
							 rx_star_flag=0x00;
									 
									 
						 }
                     break;
                 }
				 default:
				  {
					 rx_buff[0]=0x00;
					 rx_buff[1]=0x00;
					 rx_buff[2]=0x00;
					 rx_buff[3]=0x00;
					 rx_buff[4]=0x00;
					 rx_buff[5]=0x00;
					 rx_buff[6]=0x00;
					 rx_buff[7]=0x00;
					 rx_buff[8]=0x00;
					 rx_buff[9]=0x00;
					 rx_buff[10]=0x00;
					 rx_buff[11]=0x00;
					 
					 rx_num=0x00;
					 rx_end_flag=0x00;
					 rx_star_flag=0x00;
					  
					  break;
					  
				  }
             }  		 
     } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 

