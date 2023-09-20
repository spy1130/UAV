#include "sys.h"
#include "usart.h"	 
#define sec_basis 0


u8 rx_buff[38]={0};
u8 rx_end_flag=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx_star_flag=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx_num=0,command_text=0x00;

u8 rx_buff2[38]={0};
u8 rx_end_flag2=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx_star_flag2=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx_num2=0,command_text2=0x00;


u8 rx3_buff[38]={0};
u8 rx3_end_flag=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx3_star_flag=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx3_num=0,command_text3=0x00;

u8 first_frame_end=0x00,second_frame_end=0x00,find_pole_flag=0;







u8 res;
u8 row_cloumn_all=0;
u8 row_num=0;
u8 cloumn_num=0;



short  YAW=0,PITCH=0,ROLL=0;
u8   gy_5_flag=0;
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
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
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  










void uart4_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART4, ENABLE);	//使能UART4，
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC ,ENABLE);//GPIOA时钟
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
	
	//USART4_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PD.5
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOD.5
   
  //USART4_RX	  GPIOC.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PD6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOD.6  
	
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//要使用进行重映射
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//要使用PA15、PB3、PA2、PA3的端口组合，要进行部分重映射

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
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

  USART_Init(UART4, &USART_InitStructure); //初始化串口1
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(UART4, ENABLE);                    //使能串口1 

}


void UART4_IRQHandler(void)
{
	
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET);//USART_IT_RXNE
	
	
	 res =USART_ReceiveData(UART4);	//读取接收到的数据
            

	 switch(rx_num)
	 {
		  case 0://freame star
		 {
			 if(0xaa==res)
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
				
				 
				 rx_num=0x00;
				 rx_end_flag=0x00;
				 rx_star_flag=0x00;
			 }
			 
			 
			 break;
		 } 
		 case 1://YAWY hige 8 bit
		 {
			 
			 rx_buff[1]=res;
			 rx_num=0x02;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
				 
			 
			 
			 break;
		 }
		 case 2:////YAWY low 8 bit
		 {
			 rx_buff[2]=res;
			 rx_num=0x03;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
		 
		 case 3://PITCH hige 8 bit
		 {
			 
			 rx_buff[3]=res;
			 rx_num=0x04;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 
		 
			 break;      
						 
		  }
		  
		case 4://length
		 {
			 rx_buff[4]=res;
			 rx_num=0x05;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
		 
		  case 5://length
		 {
			 rx_buff[5]=res;
			 rx_num=0x06;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
		  case 6://length
		 {
			 rx_buff[6]=res;
			 rx_num=0x07;
			 rx_end_flag=0x00;
			 rx_star_flag=0x01;
			 break;
		 }
			
		 
		 
		 case 7://PITCH low 8 bit
		 {
			 if(res==0x55)
			 {
				  
				  rx_buff[7]=res;
				 
				 
				  YAW=(rx_buff[1]<<8|rx_buff[2]);//YAW，PITCH,ROLL为真实值的100倍
				  PITCH=(rx_buff[3]<<8|rx_buff[4]);
				  ROLL=(rx_buff[5]<<8|rx_buff[6]);
				  rx_num=0x00;
				  rx_end_flag=0x01;
				  rx_star_flag=0x01;
//				  LED0=!LED0;
//				 
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
			
			 
			 rx_num=0x00;
			 rx_end_flag=0x00;
			 rx_star_flag=0x00;
			  
			  break;
			  
		  }
	 }
		
		
}















void uart3_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
//	

//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
//	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     /*使能SWD 禁用JTAG*/ 
//	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PA.12 端口配置
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		//fukong输入
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

//	
//	
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//要使用PA15、PB3、PA2、PA3的端口组合，要进行部分重映射




	     //GPIO_PartialRemap_USART3
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE);	//使能USART2，
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC ,ENABLE);//GPIOA时钟
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
	
	//USART3_TX   GPIOC.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PD.5
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOD.5
   
  //USART3_RX	  GPIOB.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PD6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOD.6  
	
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//要使用进行重映射
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//要使用PA15、PB3、PA2、PA3的端口组合，要进行部分重映射

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
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

  USART_Init(USART3, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口1 

}


void clear_tx3_buff(void)
{
	rx3_buff[0]=0x00;
	rx3_buff[1]=0x00;
	rx3_buff[2]=0x00;
	rx3_buff[3]=0x00;
	rx3_buff[4]=0x00;
	rx3_buff[5]=0x00;
	rx3_buff[6]=0x00;
	rx3_buff[7]=0x00;
	rx3_buff[8]=0x00;
	rx3_buff[9]=0x00;
	rx3_buff[10]=0x00;
	rx3_buff[10]=0x00;
	rx3_buff[11]=0x00;
	rx3_buff[12]=0x00;
	rx3_buff[13]=0x00;
	rx3_buff[14]=0x00;
	rx3_buff[15]=0x00;
	rx3_buff[16]=0x00;
	rx3_buff[17]=0x00;
	rx3_buff[18]=0x00;
	rx3_buff[19]=0x00;
	rx3_buff[20]=0x00;
	
	rx3_buff[21]=0x00;
	rx3_buff[22]=0x00;
	rx3_buff[23]=0x00;
	rx3_buff[24]=0x00;
	rx3_buff[25]=0x00;
	rx3_buff[26]=0x00;
	rx3_buff[27]=0x00;
	rx3_buff[28]=0x00;
	rx3_buff[29]=0x00;
	rx3_buff[30]=0x00;

	rx3_num=0x00;
	rx3_end_flag=0x00;
	rx3_star_flag=0x00;
	
}


void USART3_IRQHandler(void)
{
				uint8_t res2;
				if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
				{                
						res2 =USART_ReceiveData(USART3);	//读取接收到的数据
						switch(rx3_num)
             {
                  case 0://freame star
                 {
                     if(0xaa==res2)
                     {
                         rx3_buff[0]=res2;
                         rx3_num=0x01;
                         rx3_end_flag=0x00;
                         rx3_star_flag=0x01;
                     }
                     else
                     {
                         clear_tx3_buff();
                     }
                     
                     
                     break;
                 } 
                 case 1://freame star
                 {
                     if(0x29==res2)
                     {
                         rx3_buff[1]=res2;
                         rx3_num=0x02;
                         rx3_end_flag=0x00;
                         rx3_star_flag=0x01;
                     }
                     else
                     {
                        clear_tx3_buff();
                     }
                     
                     break;
                 }
								 
							 case 2://freame star
                 {
                     if(0X05==res2)
                     {
                         rx3_buff[2]=res2;
                         rx3_num=0x03;
                         rx3_end_flag=0x00;
                         rx3_star_flag=0x01;
                     }
                     else
                     {
                         clear_tx3_buff();
                     }
                     
                     break;
                 }
                 case 3:///*功能字：0X35欧拉角 0X34位置 0X33速度*/
                 {
                    if(res2==0x33 || res2==0x34|| res2==0x35)
										{
											 rx3_buff[3]=res2;
											 rx3_num=0x04;
											 rx3_end_flag=0x00;
											 rx3_star_flag=0x01;
										}
										else
										{
											clear_tx3_buff();
										}	
										
										 break;

										
                 }
                 
                 case 4://///*0X06*/数据区长度为6个字节，2个字节速度，2个字节位置，2个字节角度
                 {
                     
									 rx3_buff[4]=res2;
									 rx3_num=0x05;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 5://commamd 1x.h
                 {
                     
									 rx3_buff[5]=res2;
									 rx3_num=0x06;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 6://commamd 1x.l
                 {
                     
									 rx3_buff[6]=res2;
									 rx3_num=0x07;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 7://y.h
                 {
                     
									 rx3_buff[7]=res2;
									 rx3_num=0x08;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 8://commamd 1 y.hl
                 {
                     
									 rx3_buff[8]=res2;
									 rx3_num=0x09;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 9://z.h
                 {
                     
									 rx3_buff[9]=res2;
									 rx3_num=0x0a;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								 case 10://commamd 1 z.l
                 {
                     
									 rx3_buff[10]=res2;
									 rx3_num=0x0b;
									 rx3_end_flag=0x00;
									 rx3_star_flag=0x01;
                   break;                   
                 }
								  case 11://yaw.h
								 {
									 
													 rx3_buff[11]=res2;
													 rx3_num=0x0c;
													 rx3_end_flag=0x00;
													 rx3_star_flag=0x01;
								   break;                   
								 }
												 case 12://commamd 1 yaw.l
								 {
									 
													 rx3_buff[12]=res2;
													 rx3_num=0x0d;
													 rx3_end_flag=0x00;
													 rx3_star_flag=0x01;
								   break;                   
								 }
								
				 
								case 13:///*帧尾*/yaw.h
											 {
									 if(0x00==res2)
									 {
										 rx3_buff[13]=res2;
										 rx3_num=0x00;
										 rx3_star_flag=0x00;
										 command_text3=rx3_buff[2];
										 rx3_end_flag=0x01;
										 
									 }
									 else
									 {
											clear_tx3_buff();
												 
												 
									 }
													 break;
											 }
							 default:
								{
								clear_tx3_buff();
									
									break;
									
								}
								
				} 
						 
			}
}








////////////////////





////////////////////
////////
////////////////////
////////
////////////////
void uart2_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
//	

//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
//	
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);     /*使能SWD 禁用JTAG*/ 
//	
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PA.12 端口配置
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		//fukong输入
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
//	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

//	
//	
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//要使用PA15、PB3、PA2、PA3的端口组合，要进行部分重映射




	     //GPIO_PartialRemap_USART3
	
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE);	//使能USART2，
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO ,ENABLE);//GPIOA时钟
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA| RCC_APB2Periph_GPIOC,ENABLE);
	
	//USART2_TX   GPIOD.5
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PD.5
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOD.5
   
  //USART2_RX	  GPIOD.6初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PD6
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOD.6  
	
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);//要使用进行重映射
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);//要使用PA15、PB3、PA2、PA3的端口组合，要进行部分重映射

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
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

  USART_Init(USART2, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口1 

}


void clc_first_frame2(void)
{
	rx_buff2[0]=0x00;
	rx_buff2[1]=0x00;
	rx_buff2[2]=0x00;
	rx_buff2[3]=0x00;
	rx_buff2[4]=0x00;
	rx_buff2[5]=0x00;
	rx_buff2[6]=0x00;
	rx_buff2[7]=0x00;
	rx_buff2[8]=0x00;
	rx_buff2[9]=0x00;
	rx_buff2[10]=0x00;
	rx_buff2[10]=0x00;
	rx_buff2[11]=0x00;
	rx_buff2[12]=0x00;
	rx_buff2[13]=0x00;
	rx_buff2[14]=0x00;
	rx_buff2[15]=0x00;
	rx_buff2[16]=0x00;
	rx_buff2[17]=0x00;
	rx_buff2[18]=0x00;
	rx_buff2[19]=0x00;
	rx_buff2[20]=0x00;
	
	rx_buff2[21]=0x00;
	rx_buff2[22]=0x00;
	rx_buff2[23]=0x00;
	rx_buff2[24]=0x00;
	rx_buff2[25]=0x00;
	rx_buff2[26]=0x00;
	rx_buff2[27]=0x00;
	rx_buff2[28]=0x00;
	rx_buff2[29]=0x00;
	rx_buff2[30]=0x00;

	rx_num2=0x00;
	rx_end_flag2=0x00;
	rx_star_flag2=0x00;
	
}







void USART2_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 com_data;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			com_data =USART_ReceiveData(USART2);	//读取接收到的数据
			
			switch(rx_num2)
             {
                  case 0://freame star
                 {
                     if(0xaa==com_data)
                     {
                         rx_buff2[0]=com_data;
                         rx_num2=0x01;
                         rx_end_flag2=0x00;
                         rx_star_flag2=0x01;
                     }
                     else
                     {
                         clc_first_frame2();
                     }
                     
                     
                     break;
                 } 
                 case 1://freame star
                 {
                     if(0x29==com_data)
                     {
                         rx_buff2[1]=com_data;
                         rx_num2=0x02;
                         rx_end_flag2=0x00;
                         rx_star_flag2=0x01;
                     }
                     else
                     {
                        clc_first_frame2();
                     }
                     
                     break;
                 }
								 
					case 2://freame star
                 {
                     if(0X05==com_data)
                     {
                         rx_buff2[2]=com_data;
                         rx_num2=0x03;
                         rx_end_flag2=0x00;
                         rx_star_flag2=0x01;
                     }
                     else
                     {
                         clc_first_frame2();
                     }
                     
                     break;
                 }
                 case 3:///*功能字：0X35欧拉角 0X34位置 0X33速度*/
                 {
                    if(com_data==0x33 || com_data==0x34|| com_data==0x35)
										{
											 rx_buff2[3]=com_data;
											 rx_num2=0x04;
											 rx_end_flag2=0x00;
											 rx_star_flag2=0x01;
										}
										else
										{
											clc_first_frame2();
										}	
										
										 break;

										
                 }
                 
                 case 4://///*0X06*/数据区长度为6个字节，2个字节速度，2个字节位置，2个字节角度
                 {
                     
									 rx_buff2[4]=com_data;
									 rx_num2=0x05;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 5://commamd 1x.h
                 {
                     
									 rx_buff2[5]=com_data;
									 rx_num2=0x06;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 6://commamd 1x.l
                 {
                     
									 rx_buff2[6]=com_data;
									 rx_num2=0x07;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 7://y.h
                 {
                     
									 rx_buff2[7]=com_data;
									 rx_num2=0x08;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 8://commamd 1 y.hl
                 {
                     
									 rx_buff2[8]=com_data;
									 rx_num2=0x09;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 9://z.h
                 {
                     
									 rx_buff2[9]=com_data;
									 rx_num2=0x0a;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								 case 10://commamd 1 z.l
                 {
                     
									 rx_buff2[10]=com_data;
									 rx_num2=0x0b;
									 rx_end_flag2=0x00;
									 rx_star_flag2=0x01;
                   break;                   
                 }
								  case 11://yaw.h
								 {
									 
													 rx_buff2[11]=com_data;
													 rx_num2=0x0c;
													 rx_end_flag2=0x00;
													 rx_star_flag2=0x01;
								   break;                   
								 }
												 case 12://commamd 1 yaw.l
								 {
									 
													 rx_buff2[12]=com_data;
													 rx_num2=0x0d;
													 rx_end_flag2=0x00;
													 rx_star_flag2=0x01;
								   break;                   
								 }
								
				 
								case 13:///*帧尾*/yaw.h
											 {
									 if(0x00==com_data)
									 {
										 rx_buff2[13]=com_data;
										 rx_num2=0x00;
										 rx_star_flag2=0x00;
										 command_text3=rx_buff2[2];
										 rx_end_flag2=0x01;
										 
									 }
									 else
									 {
											clc_first_frame2();
												 
												 
									 }
													 break;
											 }
							 default:
								{
								clc_first_frame2();
									
									break;
									
								}
								
				} 
						 
			}

            

//			switch(rx_num2)
//			{
//			  case 0://freame star "$"
//			 {
//				 if(0x24==com_data)
//				 {
//					 rx_buff2[0]=com_data;
//					 rx_num2=0x01;
//					 rx_end_flag2=0x00;
//					 rx_star_flag2=0x01;
//				 }
//				 else
//				 {
//					clc_first_frame2();
//				 }
//				 
//				 
//				 break;
//			 } 
//			 case 1://"K"
//			 {
//				 
//				 rx_buff2[1]=com_data;
//				 rx_num2=0x02;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//					 
//				 
//				 
//				 break;
//			 }
//			 case 2:////"T"
//			 {
//				 rx_buff2[2]=com_data;
//				 rx_num2=0x03;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			 
//			 case 3://"0"
//			 {
//				 
//				 rx_buff2[3]=com_data;
//				 rx_num2=0x04;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 
//			 
//				 break;      
//							 
//			  }
//			  
//				case 4://x1
//			 {
//				 rx_buff2[4]=com_data;
//				 rx_num2=0x05;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			 
//			  case 5:////x2
//			 {
//				 rx_buff2[5]=com_data;
//				 rx_num2=0x06;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 6:////x3
//			 {
//				 rx_buff2[6]=com_data;
//				 rx_num2=0x07;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }



//			 case 7:///x4
//			 {
//				 rx_buff2[7]=com_data;
//				 rx_num2=0x08;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 8:///y1
//			 {
//				 rx_buff2[8]=com_data;
//				 rx_num2=0x09;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }


//			   case 9://y2
//			 {
//				 rx_buff2[9]=com_data;
//				 rx_num2=10;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 10:///y3
//			 {
//				 rx_buff2[10]=com_data;
//				 rx_num2=11;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 11:///y4
//			 {
//				 rx_buff2[11]=com_data;
//				 rx_num2=12;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 12:///z1
//			 {
//				 rx_buff2[12]=com_data;
//				 rx_num2=13;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 13:///z2
//			 {
//				 rx_buff2[13]=com_data;
//				 rx_num2=14;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 14:///z3
//			 {
//				 rx_buff2[14]=com_data;
//				 rx_num2=15;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 15:///z4
//			 {
//				 rx_buff2[15]=com_data;
//				 rx_num2=16;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 16:///check sum1
//			 {
//				 rx_buff2[16]=com_data;
//				 rx_num2=17;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 17:///check sum2
//			 {
//				 rx_buff2[17]=com_data;
//				 rx_num2=18;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 18:///check sum3
//			 {
//				 rx_buff2[18]=com_data;
//				 rx_num2=19;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			  case 19:///check sum4
//			 {
//				 rx_buff2[19]=com_data;
//				 rx_num2=20;
//				 rx_end_flag2=0x00;
//				 rx_star_flag2=0x01;
//				 break;
//			 }
//			 
//			  
//				
//			 
//			 
//			 case 20:////帧尾
//			 {
//				 if(com_data==0xA)
//				 {
//					  
//					  rx_buff2[20]=com_data;
//					 
////					 check_sum=0;
////					 for(tempa=0;tempa<9;tempa++)
////					 {
////						 check_sum=check_sum+rx_buff2[tempa];
////					 }
//					 
//						rx_num2=0x00;
//						rx_end_flag2=0x01;
//						rx_star_flag=0x01;
//						first_frame_end=1;
//					
//	//				 
//				 }

//				 else
//				 {
//					 clc_first_frame2();
//					 
//				 }
//				 
//				 break;
//			 }
//			
//			 

//			 default:
//			  {
//				 clc_first_frame2();
//				  
//				  break;
//				  
//			  }
//		 }

///////////
		
	
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
	

















  
void uart_init(u32 bound){
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

void clc_first_frame(void)
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
	rx_buff[10]=0x00;
	rx_buff[11]=0x00;
	rx_buff[12]=0x00;
	rx_buff[13]=0x00;
	rx_buff[14]=0x00;
	rx_buff[15]=0x00;
	rx_buff[16]=0x00;
	rx_buff[17]=0x00;
	rx_buff[18]=0x00;
	rx_buff[19]=0x00;
	rx_buff[20]=0x00;
	
	rx_buff[21]=0x00;
	rx_buff[22]=0x00;
	rx_buff[23]=0x00;
	rx_buff[24]=0x00;
	rx_buff[25]=0x00;
	rx_buff[26]=0x00;
	rx_buff[27]=0x00;
	rx_buff[28]=0x00;
	rx_buff[29]=0x00;
	rx_buff[30]=0x00;

	rx_num=0x00;
	rx_end_flag=0x00;
	rx_star_flag=0x00;
	first_frame_end=0;
	second_frame_end=0x00;
}

void clc_second_frame(void)
{
	rx_buff[sec_basis+0]=0x00;
	rx_buff[sec_basis+1]=0x00;
	rx_buff[sec_basis+2]=0x00;
	rx_buff[sec_basis+3]=0x00;
	rx_buff[sec_basis+4]=0x00;
	rx_buff[sec_basis+5]=0x00;
	rx_buff[sec_basis+6]=0x00;
	rx_buff[sec_basis+7]=0x00;
	rx_buff[sec_basis+8]=0x00;
	rx_buff[sec_basis+9]=0x00;
	rx_buff[sec_basis+10]=0x00;

	rx_num=0x00;
	rx_star_flag=0x00;
	second_frame_end=0x00;
}




void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 com_data;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			com_data =USART_ReceiveData(USART1);	//读取接收到的数据
            

			switch(rx_num)
			{
			  case 0://freame star "$"
			 {
				 if(0x24==com_data)
				 {
					 rx_buff[0]=com_data;
					 rx_num=0x01;
					 rx_end_flag=0x00;
					 rx_star_flag=0x01;
				 }
				 else
				 {
					clc_first_frame();
				 }
				 
				 
				 break;
			 } 
			 case 1://"K"
			 {
				 
				 rx_buff[1]=com_data;
				 rx_num=0x02;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
					 
				 
				 
				 break;
			 }
			 case 2:////"T"
			 {
				 rx_buff[2]=com_data;
				 rx_num=0x03;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			 case 3://"0"
			 {
				 
				 rx_buff[3]=com_data;
				 rx_num=0x04;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 
			 
				 break;      
							 
			  }
			  
				case 4://x1
			 {
				 rx_buff[4]=com_data;
				 rx_num=0x05;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			  case 5:////x2
			 {
				 rx_buff[5]=com_data;
				 rx_num=0x06;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 6:////x3
			 {
				 rx_buff[6]=com_data;
				 rx_num=0x07;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }



			 case 7:///x4
			 {
				 rx_buff[7]=com_data;
				 rx_num=0x08;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 8:///y1
			 {
				 rx_buff[8]=com_data;
				 rx_num=0x09;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }


			   case 9://y2
			 {
				 rx_buff[9]=com_data;
				 rx_num=10;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 10:///y3
			 {
				 rx_buff[10]=com_data;
				 rx_num=11;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 11:///y4
			 {
				 rx_buff[11]=com_data;
				 rx_num=12;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 12:///z1
			 {
				 rx_buff[12]=com_data;
				 rx_num=13;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 13:///z2
			 {
				 rx_buff[13]=com_data;
				 rx_num=14;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 14:///z3
			 {
				 rx_buff[14]=com_data;
				 rx_num=15;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 15:///z4
			 {
				 rx_buff[15]=com_data;
				 rx_num=16;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 16:///check sum1
			 {
				 rx_buff[16]=com_data;
				 rx_num=17;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 17:///check sum2
			 {
				 rx_buff[17]=com_data;
				 rx_num=18;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 18:///check sum3
			 {
				 rx_buff[18]=com_data;
				 rx_num=19;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 19:///check sum4
			 {
				 rx_buff[19]=com_data;
				 rx_num=20;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			  
				
			 
			 
			 case 20:////帧尾
			 {
				 if(com_data==0xA)
				 {
					  
					  rx_buff[20]=com_data;
					 
//					 check_sum=0;
//					 for(tempa=0;tempa<9;tempa++)
//					 {
//						 check_sum=check_sum+rx_buff[tempa];
//					 }
					 
						rx_num=0x00;
						rx_end_flag=0x01;
						rx_star_flag=0x01;
						first_frame_end=1;
					
	//				 
				 }

				 else
				 {
					 clc_first_frame();
					 
				 }
				 
				 break;
			 }
			
			 

			 default:
			  {
				 clc_first_frame();
				  
				  break;
				  
			  }
		 }

/////////
		
		
		
		
		
		
		
		} 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
	





#endif	

