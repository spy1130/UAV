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
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;         //选择USART2中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //设置响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能通道
    NVIC_Init(&NVIC_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);      //使能USART2时钟
    USART_InitStructure.USART_BaudRate = baud;                  //设置波特率为baud
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //设置为8位数据位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //设置为1位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;         //不使用奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //禁用硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //选择USART发送和接收模式
    USART_Init(USART3, &USART_InitStructure);                     //初始化USART1
	
//    USART_ITConfig(USART3,USART_IT_TC, ENABLE); 	//开启串口发送完成中断	
	USART_ITConfig(USART3,USART_IT_RXNE, ENABLE); 	//开启串口接受中断
    USART_Cmd(USART3,ENABLE);                     	//使能USART2
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
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能GPIOA时钟
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;             //TXD引脚-PA2
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //设置为复用推挽输出
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //输出速率50MHz
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;            //RXD引脚-PA3
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//		NVIC_InitTypeDef NVIC_InitStructure;
//    
//    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;         //选择USART2中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //设置抢占优先级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //设置响应优先级
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能通道
//    NVIC_Init(&NVIC_InitStructure);
//	
//	  USART_InitTypeDef USART_InitStructure;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);      //使能USART2时钟
//    USART_InitStructure.USART_BaudRate = baud;                  //设置波特率为baud
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //设置为8位数据位
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //设置为1位停止位
//    USART_InitStructure.USART_Parity = USART_Parity_No;         //不使用奇偶校验
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //禁用硬件流控制
//    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //选择USART发送和接收模式
//    USART_Init(USART2, &USART_InitStructure);                     //初始化USART1
//	
//    USART_ITConfig(USART2,USART_IT_TC, ENABLE); 	//开启串口发送完成中断	
//	  USART_ITConfig(USART2,USART_IT_RXNE, ENABLE); 	//开启串口接受中断
//    USART_Cmd(USART2,ENABLE);                     	//使能USART2
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
//        USART_ITConfig(UART5, USART_IT_TXE, ENABLE); //打开发送中断
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

//void USART2_IRQHandler(void)                	//串口1中断服务程序
//	{
//	u8 res2;
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif

   
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//            res2 =USART_ReceiveData(USART2);	//读取接收到的数据
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
//                 case 3:///*功能字：0X35欧拉角 0X34位置 0X33速度*/
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
//                 case 4://///*0X06*/数据区长度为6个字节，2个字节速度，2个字节位置，2个字节角度
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
//								case 11:///*帧尾*/
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
//#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntExit();  											 
//#endif
//} 


void USART2_IRQHandler(void)
{
				uint8_t res2;
				if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
				{                
						res2 =USART_ReceiveData(USART2);	//读取接收到的数据
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
                 case 3:///*功能字：0X35欧拉角 0X34位置 0X33速度*/
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
                 
                 case 4://///*0X06*/数据区长度为6个字节，2个字节速度，2个字节位置，2个字节角度
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
								
				 
								case 11:///*帧尾*/
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
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能GPIOA时钟
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;             //TXD引脚-PA9
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;       //设置为复用推挽输出
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //输出速率50MHz
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            //RXD引脚-PA10
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	NVIC_InitTypeDef NVIC_InitStructure;
//    
//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;         //选择USART2中断
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //设置抢占优先级
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //设置响应优先级
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //使能通道
//    NVIC_Init(&NVIC_InitStructure);
//	
//	USART_InitTypeDef USART_InitStructure;
//    
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);      //使能USART2时钟
//    USART_InitStructure.USART_BaudRate = baud;                  //设置波特率为baud
//    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //设置为8位数据位
//    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //设置为1位停止位
//    USART_InitStructure.USART_Parity = USART_Parity_No;         //不使用奇偶校验
//    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //禁用硬件流控制
//    USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx; //选择USART发送和接收模式
//		
//    USART_Init(USART1, &USART_InitStructure);                     //初始化USART1
//	
//    //USART_ITConfig(USART1,USART_IT_TC, ENABLE); 	//开启串口发送完成中断
//		USART_ITConfig(USART1,USART_IT_RXNE, ENABLE); 	//开启串口接受中断
//    USART_Cmd(USART1,ENABLE);                     	//使能USART2

GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = baud;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  
  
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

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
void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
            res =USART_ReceiveData(USART1);	//读取接收到的数据
            

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
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 

