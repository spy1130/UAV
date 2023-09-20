#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "OLED.h"

float Cx=0,Cy=0;
uint8_t RxFlag1=0;

/*************************************
*函  数  名：	Serial_Init()
*函数功能：初始化串口
*输	入	：无
*输	出	：无
*************************************/
void Serial_Init(void)
{
	//第一步：开启时钟，把USART和GPIO的打开
	//第二步：GPIO初始化，把TX配置成复用输出，RX配置成输入
	//第三步：配置USART
	//第四步：若只用发送功能就直接开启USART；若要有接收功能还需配置中断
	
	//第一步：开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);													//开启USART时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);														//开启ＧＰＩＯ时钟
	
	//第二步：GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	//TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;																	//开启复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//ＲX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;																		//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//第三步：配置USART
	USART_InitTypeDef USART_InitStructure;																					//定义结构体
	USART_InitStructure.USART_BaudRate = 115200;																		//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;									//串口模式，发送和接收模式
	USART_InitStructure.USART_Parity = USART_Parity_No;															//校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;													//停止位，此为１位停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;											//字长
	USART_Init(USART1, &USART_InitStructure);																				//初始化
	
	//第四步：开启中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);																	//开启RXNE标志位到NVIC的输出
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);																	//分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);																											//使能ＵＳＡＲＴ
}

/*************************************
*函  数  名	：USART1_IRQHandler()
*函数功能	：接收openmv识别到目标的xy坐标
*输	入	：无
*输	出	：无
*************************************/
void USART1_IRQHandler(void)																											//中断处理函数
{
		u8 com_data; 
		static u8 RxCounter1=0;
		static float RxBuffer1[10]={0};
		static u8 RxState = 0;	
		//static u8 RxFlag1 = 0;


		if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  	  									 		//接收中断  
		{
				USART_ClearITPendingBit(USART1,USART_IT_RXNE);   													//清除中断标志
				com_data = USART_ReceiveData(USART1);
			
				if(RxState==0&&com_data==0x2C)  																					//0x2c帧头
				{
					
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1>=5||com_data == 0x5B)       															//RxBuffer1接受满了,接收数据结束
					{
						RxState=2;
						RxFlag1=1;
						Cx=RxBuffer1[RxCounter1-3];
						Cy=RxBuffer1[RxCounter1-2];
					}
				}
		
				else if(RxState==2)																												//检测是否接受到结束标志
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{	
									USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);										//关闭DTSABLE中断
									if(RxFlag1)
									{
									//OLED_ShowNum(1, 1,RxCounter1,4);//RxCounter1长度为4
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
						else   //接收错误
						{
									RxState = 0;
									RxFlag1 = 0;
									RxCounter1=0;
								      memset(RxBuffer1,0,sizeof(RxBuffer1));
						}
				} 
	
				else   //接收异常
				{
						RxState = 0;
						RxFlag1 = 0;
						RxCounter1=0;
					      memset(RxBuffer1,0,sizeof(RxBuffer1));
				}

		}
}


/*************************************
*函  数  名	Get_x()
*函数功能	：输出x轴的值
*输	入	：无
*输	出	：x轴坐标
*************************************/
int Get_x(void)
{
	return Cx;
}


/*************************************
*函  数  名	Get_y()
*函数功能	：输出y轴的值
*输	入	：无
*输	出	：y轴坐标
*************************************/
int Get_y(void)
{
	return Cy;
}


/*************************************
*函  数  名	Serial_flag()
*函数功能	：判断是否识别到小球
*输	入	：无
*输	出	：标志位
*************************************/
int Serial_flag()
{
	return RxFlag1;
}

