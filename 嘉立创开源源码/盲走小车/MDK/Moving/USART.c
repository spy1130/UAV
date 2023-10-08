#include "usart.h"
#include "LX_DT.h"

//u8 dat; 
////如果使用ucos,则包括下面的头文件即可.
//#if SYSTEM_SUPPORT_OS
//#include "includes.h"					//ucos 使用	  
//#endif

//#if 1
//#pragma import(__use_no_semihosting)             
////标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//void _sys_exit(int x) 
//{ 
//	x = x; 
//} 
////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 

 
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	  
  
void uart1_init(u32 bound){
	//GPIO端口设置
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

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//	//u8 Res;
//	Flight_DataReceive(USART_ReceiveData(USART1));		
//#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
//	OSIntEnter();    
//#endif
////	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
////	{
//			//读取接收到的数据
//		
//		//USART_SendData(USART2,Res);
////		if((USART1_RX_STA&0x8000)==0)//接收未完成
////		{
////			if(USART1_RX_STA&0x4000)//接收到了0x0d
////			{
////				if(Res!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
////				else USART1_RX_STA|=0x8000;	//接收完成了 
////			}
////			else //还没收到0X0D
////			{	
////				if(Res==0x0d)USART1_RX_STA|=0x4000;
////				else
////					{
////					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
////					USART1_RX_STA++;
////					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
////					}		 
////				}
////			}   		 
////   } 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif


#endif	

#if EN_USART2_RX
u8  USART2_RX_BUF[USART2_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
u16 USART2_RX_STA = 0;         			//接收状态标记	

void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	USART_InitTypeDef USART_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	// 外设使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_DeInit(USART2);  //复位串口2 -> 可以没有
	
	// 初始化 串口对应IO口  TX-PA2  RX-PA3
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	// 初始化 串口模式状态
	USART_InitStrue.USART_BaudRate=bound; // 波特率
	USART_InitStrue.USART_HardwareFlowControl=USART_HardwareFlowControl_None; // 硬件流控制
	USART_InitStrue.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; // 发送 接收 模式都使用
	USART_InitStrue.USART_Parity=USART_Parity_No; // 没有奇偶校验
	USART_InitStrue.USART_StopBits=USART_StopBits_1; // 一位停止位
	USART_InitStrue.USART_WordLength=USART_WordLength_8b; // 每次发送数据宽度为8位
	USART_Init(USART2,&USART_InitStrue);
	
	USART_Cmd(USART2,ENABLE);//使能串口
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启接收中断
	
	// 初始化 中断优先级
	NVIC_InitStrue.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStrue);
}
// 
//void Usart2Init(unsigned int uiBaud)
//{
// 	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure; 
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//	
//	// 485 control pin
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA, GPIO_Pin_1);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);    
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	 
//	USART_InitStructure.USART_BaudRate = uiBaud;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No ;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART2, &USART_InitStructure); 
//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	
//	USART_Cmd(USART2, ENABLE);
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
//void USART2_IRQHandler(void) // 串口2中断服务函数
//{
//	JY62_DataReceive(USART_ReceiveData(USART2));
//	if(USART_GetITStatus(USART2,USART_IT_RXNE)) // 中断标志
//	{
//		  // 串口2 接收
//		
////		USART_SendData(USART2,res);   // 串口2 发送
////		if((USART2_RX_STA&0x8000)==0)//接收未完成
////		{
////		if(USART2_RX_STA&0x4000)//接收到了0x0d
////			{
////			if(res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
////			else USART2_RX_STA|=0x8000;	//接收完成了 
////			}
////		else //还没收到0X0D
////			{	
////			if(res==0x0d)USART2_RX_STA|=0x4000;
////			else
////				{
////				USART2_RX_BUF[USART2_RX_STA&0X3FFF]=res ;
////				USART2_RX_STA++;
////				if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
////				}		 
////			}
////		} 
//	}
//}
#endif

#if EN_USART3_RX
u8  USART3_RX_BUF[USART3_REC_LEN]; 	//接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
u16 USART3_RX_STA = 0;         			//接收状态标记	

void uart3_init(u32 bound)
{

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	// GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); //串口3时钟使能
 
 	USART_DeInit(USART3);  //复位串口3
		 //USART3_TX   PB10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
   
    //USART3_RX	  PB11
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11
	
	USART_InitStructure.USART_BaudRate = bound;//波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
	USART_Init(USART3, &USART_InitStructure); //初始化串口	3
  
 
	USART_Cmd(USART3, ENABLE);                    //使能串口 
	
	//使能接收中断
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断   
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	USART3_RX_STA=0;		//清零
}
 
void USART3_IRQHandler(void) // 串口3中断服务函数
{
	u8 res;
	if(USART_GetITStatus(USART3,USART_IT_RXNE)) // 中断标志
	{
		res= USART_ReceiveData(USART3);  // 串口3 接收
////		USART_SendData(USART2,res);   // 串口3 发送
//		if((USART3_RX_STA&0x8000)==0)//接收未完成
//		{
//		if(USART3_RX_STA&0x4000)//接收到了0x0d
//			{
//			if(res!=0x0a)USART3_RX_STA=0;//接收错误,重新开始
//			else USART3_RX_STA|=0x8000;	//接收完成了 
//			}
//		else //还没收到0X0D
//		{	
//			if(res==0x0d)USART3_RX_STA|=0x4000;
//			else
//				{
//				USART3_RX_BUF[USART2_RX_STA&0X3FFF]=res ;
//				USART3_RX_STA++;
//				if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
//				}		 
//		}
//	} 
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);  //清除RXNE标志位

	}
	
}

#endif

















