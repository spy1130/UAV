/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：串口驱动
**********************************************************************************/
#include "User_Task.h"
#include "Ano_DT_LX.h"
#include "Drv_UbloxGPS.h"
#include "Drv_AnoOf.h"

#define sec_basis 20

u8 rx_buff[44]={0};
u8 rx_end_flag=0x00;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
u8 rx_star_flag=0x00;//1 mean the 0xa5 has already recieved,0 mean that we are waiting for the beginning of series port
u8 rx_num=0;
u8 tempa=0,cnt_no_find_pole_flag=0x00;
u8 check_sum=0,cnt_find_pole_flag=0;
u8 first_frame_end=0x00,second_frame_end=0x00,find_pole_flag=0;

u8 rx_buff_com1[20]={0};
u8 rx_end_flag_com1=0x00;
u8 rx_star_flag_com1=0x00;
u8 rx_num_com1=0x00;
u8 first_frame_end_com1=0;
u8 second_frame_end_com1=0x00;


int16_t cnt_com1=0x00;

union MyUnion1
{
	float b;
	char a[4];

}b2float;

float angle_min=0;
float dis_min=0;
float dis_min_kalman=0;






void NoUse(u8 data){}
//串口接收发送快速定义，直接修改此处的函数名称宏，修改成自己的串口解析和发送函数名称即可，注意函数参数格式需统一
#define U1GetOneByte	UBLOX_M8_GPS_Data_Receive
#define U2GetOneByte	NoUse
#define U3GetOneByte	NoUse
#define U4GetOneByte	AnoOF_GetOneByte
#define U5GetOneByte	ANO_DT_LX_Data_Receive_Prepare	
	
//====uart1
void DrvUart1Init(u32 br_num)
{
    USART_InitTypeDef USART_InitStructure;
//    USART_ClockInitTypeDef USART_ClockInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    USART_StructInit(&USART_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //开启USART1时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    //串口中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_UART1_P;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_UART1_S;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    //配置PA9作为USART1　Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //配置PA10作为USART1　Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //
    USART_DeInit(USART1);
    //配置USART1
    //中断被屏蔽了
    USART_InitStructure.USART_BaudRate = br_num;                                    //波特率可以通过地面站配置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //在帧结尾传输1个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //禁用奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 //发送、接收使能
    //配置USART1时钟
//    USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;     //时钟低电平活动
//    USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;           //SLCK引脚上时钟输出的极性->低电平
//    USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;         //时钟第二个边沿进行数据捕获
//    USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //最后一位数据的时钟脉冲不从SCLK输出

    USART_Init(USART1, &USART_InitStructure);
//    USART_ClockInit(USART1, &USART_ClockInitStruct);

    //使能USART1接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//    //使能USART1
    USART_Cmd(USART1, ENABLE);
}





void clc_first_frame_com1(void)
{
	rx_buff_com1[0]=0x00;
	rx_buff_com1[1]=0x00;
	rx_buff_com1[2]=0x00;
	rx_buff_com1[3]=0x00;
	rx_buff_com1[4]=0x00;
	rx_buff_com1[5]=0x00;
	rx_buff_com1[6]=0x00;
	rx_buff_com1[7]=0x00;
	rx_buff_com1[8]=0x00;
	rx_buff_com1[9]=0x00;
	rx_buff_com1[10]=0x00;
	rx_buff_com1[11]=0x00;
	rx_buff_com1[12]=0x00;
	rx_buff_com1[13]=0x00;
	rx_buff_com1[14]=0x00;

	rx_num_com1=0x00;
	rx_end_flag_com1=0x00;
	rx_star_flag_com1=0x00;
//	first_frame_end_com1=0;
//	second_frame_end_com1=0x00;
}



u8 Tx1Buffer[256];
u8 Tx1Counter = 0;
u8 count1 = 0;
void DrvUart1SendBuf(unsigned char *DataToSend, u8 data_num)
{
    u8 i;
    for (i = 0; i < data_num; i++)
    {
        Tx1Buffer[count1++] = *(DataToSend + i);
    }

    if (!(USART1->CR1 & USART_CR1_TXEIE))
    {
        USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //打开发送中断
    }
}
u8 U1RxDataTmp[100];
u8 U1RxInCnt = 0;
u8 U1RxoutCnt = 0;
void drvU1GetByte(u8 data)
{
	U1RxDataTmp[U1RxInCnt++] = data;
	if(U1RxInCnt >= 100)
		U1RxInCnt = 0;
}
void drvU1DataCheck(void)
{
	while(U1RxInCnt!=U1RxoutCnt)
	{
		U1GetOneByte(U1RxDataTmp[U1RxoutCnt++]);
		if(U1RxoutCnt >= 100)
			U1RxoutCnt = 0;
	}
}
void Usart1_IRQ(void)
{
    u8 com_data;

    if (USART1->SR & USART_SR_ORE) //ORE中断
    {
        com_data = USART1->DR;
    }
    //接收中断
    if (USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE); //清除中断标志
        com_data = USART1->DR;
        drvU1GetByte(com_data);

			//save the firsr frame

		switch(rx_num_com1)
		{
		  case 0://freame star
		 {
			 if(0xa5==com_data)
			 {
				 rx_buff_com1[0]=com_data;
				 rx_num_com1=0x01;
				 rx_end_flag_com1=0x00;
				 rx_star_flag_com1=0x01;
			 }
			 else
			 {
				clc_first_frame_com1();
			 }
			 
			 
			 break;
		 } 
		 case 1://data1_1
		 {
			 
			if(0x5a==com_data)
			 {
				 rx_buff_com1[1]=com_data;
				 rx_num_com1=0x02;
				 rx_end_flag_com1=0x00;
				 rx_star_flag_com1=0x01;
			 }
			 else
			 {
				clc_first_frame_com1();
			 }
				 
			 
			 
			 break;
		 }
		 case 2://data1_2//command type
		 {
			 rx_buff_com1[2]=com_data;
			 rx_num_com1=0x03;
			 rx_end_flag_com1=0x00;
			 rx_star_flag_com1=0x01;
			 break;
		 }
		 
		 case 3://data1_3//no_1 order
		 {
			 
			 rx_buff_com1[3]=com_data;
			 rx_num_com1=0x04;
			 rx_end_flag_com1=0x00;
			 rx_star_flag_com1=0x01;
			 
		 
			 break;      
						 
		  }
		  
			case 4:////no_2 order
		 {
			 rx_buff_com1[4]=com_data;
			 rx_num_com1=0x05;
			 rx_end_flag_com1=0x00;
			 rx_star_flag_com1=0x01;
			 break;
		 }
		 //帧尾巴 fd
		  case 5://data2_1
		 {
			 if(com_data==0xfd)
			 {
				  
				  rx_buff_com1[5]=com_data;
				 
				  rx_end_flag_com1=0x01;
				 
				  rx_num_com1=0x00;
				
				  rx_star_flag_com1=0x00;
				 
				  cnt_com1++;
				 			 
			 }

			 else
			 {
				 clc_first_frame_com1();
				 
			 }
			 
			 break;
		 }
		 
		

		 default:
		  {
			 clc_first_frame_com1();
			  
			  break;
			  
		  }
		}

		/////////////////////////////////////////////////
		///////////////////////////////////////////////


	
		
    }
    //发送（进入移位）中断
    if (USART_GetITStatus(USART1, USART_IT_TXE))
    {
        USART1->DR = Tx1Buffer[Tx1Counter++]; //写DR清除中断标志
        if (Tx1Counter == count1)
        {
            USART1->CR1 &= ~USART_CR1_TXEIE; //关闭TXE（发送中断）中断
        }
    }
}



//====uart2
void DrvUart2Init(u32 br_num)
{
    USART_InitTypeDef USART_InitStructure;
    //USART_ClockInitTypeDef USART_ClockInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    USART_StructInit(&USART_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //开启USART2时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    //串口中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_UART2_P;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_UART2_S;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

    //配置PD5作为USART2　Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    //配置PD6作为USART2　Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //配置USART2
    //中断被屏蔽了
    USART_InitStructure.USART_BaudRate = br_num;                                    //波特率可以通过地面站配置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //在帧结尾传输1个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //禁用奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 //发送、接收使能
    //配置USART2时钟
//    USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;     //时钟低电平活动
//    USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;           //SLCK引脚上时钟输出的极性->低电平
//    USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;         //时钟第二个边沿进行数据捕获
//    USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //最后一位数据的时钟脉冲不从SCLK输出

    USART_Init(USART2, &USART_InitStructure);
    //USART_ClockInit(USART2, &USART_ClockInitStruct);

    //使能USART2接收中断
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //使能USART2
    USART_Cmd(USART2, ENABLE);
}

u8 TxBuffer[256];
u8 TxCounter = 0;
u8 count = 0;
void DrvUart2SendBuf(unsigned char *DataToSend, u8 data_num)
{
    u8 i;
    for (i = 0; i < data_num; i++)
    {
        TxBuffer[count++] = *(DataToSend + i);
    }

    if (!(USART2->CR1 & USART_CR1_TXEIE))
    {
        USART_ITConfig(USART2, USART_IT_TXE, ENABLE); //打开发送中断
    }
}
u8 U2RxDataTmp[100];
u8 U2RxInCnt = 0;
u8 U2RxoutCnt = 0;
void drvU2GetByte(u8 data)
{
	U2RxDataTmp[U2RxInCnt++] = data;
	if(U2RxInCnt >= 100)
		U2RxInCnt = 0;
}
void drvU2DataCheck(void)
{
	while(U2RxInCnt!=U2RxoutCnt)
	{
		U2GetOneByte(U2RxDataTmp[U2RxoutCnt++]);
		if(U2RxoutCnt >= 100)
			U2RxoutCnt = 0;
	}
}

void clc_first_frame_xm(void)
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

	rx_num=0x00;
	rx_end_flag=0x00;
	rx_star_flag=0x00;
	first_frame_end=0;
	second_frame_end=0x00;
}


void clc_second_frame_xm(void)
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






void Usart2_IRQ(void)
{
    
	
	u8 com_data;

    if (USART2->SR & USART_SR_ORE) //ORE中断
    {
        com_data = USART2->DR;
    }

    //接收中断
    if (USART_GetITStatus(USART2, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART2, USART_IT_RXNE); //清除中断标志
        com_data = USART2->DR;
		drvU2GetByte(com_data);
    
		
				
		
		
		
		
		
		///1:判断是不是数据头，依次存入数据，判断帧尾巴，置标志位
		//////////////////////////////
		if(first_frame_end==0)
		{
			//save the firsr frame

			switch(rx_num)
			{
			  case 0://freame star
			 {
				 if(0xaa==com_data)
				 {
					 rx_buff[0]=com_data;
					 rx_num=0x01;
					 rx_end_flag=0x00;
					 rx_star_flag=0x01;
				 }
				 else
				 {
					clc_first_frame_xm();
				 }
				 
				 
				 break;
			 } 
			 case 1://line or pole
			 {
				 
				 rx_buff[1]=com_data;
				 rx_num=0x02;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
					 
				 
				 
				 break;
			 }
			 case 2:////length
			 {
				 rx_buff[2]=com_data;
				 rx_num=0x03;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			 case 3://pole x hige byte or line delta y hige byte
			 {
				 
				 rx_buff[3]=com_data;
				 rx_num=0x04;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 
			 
				 break;      
							 
			  }
			  
				case 4://pole x low byte or line delta y low byte
			 {
				 rx_buff[4]=com_data;
				 rx_num=0x05;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			  case 5:////pole y hige byte or line sita hige byte
			 {
				 rx_buff[5]=com_data;
				 rx_num=0x06;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 6:////pole y low byte or line sita low byte
			 {
				 rx_buff[6]=com_data;
				 rx_num=0x07;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }



			 case 7:///00
			 {
				 rx_buff[7]=com_data;
				 rx_num=0x08;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 8:///00
			 {
				 rx_buff[8]=com_data;
				 rx_num=0x09;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }


			   case 9:///check sum
			 {
				 rx_buff[9]=com_data;
				 rx_num=10;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
				
			 
			 
			 case 10:////00
			 {
				 if(com_data==0xaf)
				 {
					  
					  rx_buff[10]=com_data;
					 
					 check_sum=0;
					 for(tempa=0;tempa<9;tempa++)
					 {
						 check_sum=check_sum+rx_buff[tempa];
					 }
					 
					 if (check_sum==rx_buff[9])
					 {
						  rx_num=0x00;
						  rx_end_flag=0x01;
						  rx_star_flag=0x01;
						  first_frame_end=1;
						 
						 
						 if(rx_buff[1]==0xf0)
						 {
							  cnt_find_pole_flag++;
							 
							 if (cnt_find_pole_flag>=10)
							 {
								 find_pole_flag=1;
								 cnt_find_pole_flag=0x00;
							 
							 }
							 
						 }
						 else
						 {
							  cnt_no_find_pole_flag++;
							 
							 if (cnt_no_find_pole_flag>=10)
							 {
								 find_pole_flag=0;
								 cnt_no_find_pole_flag=0x00;
							 
							 }
						 }
						 
					 }
					 else
					 {
						 clc_first_frame_xm();
					 }

					 
	//				  YAW=(rx_buff[1]<<8|rx_buff[2]);//YAW，PITCH,ROLL为真实值的100倍
	//				  PITCH=(rx_buff[3]<<8|rx_buff[4]);
	//				  ROLL=(rx_buff[5]<<8|rx_buff[6]);
					 
					 
					 
					  
	//				  LED0=!LED0;
	//				 
				 }

				 else
				 {
					 clc_first_frame_xm();
					 
				 }
				 
				 break;
			 }
			
			 

			 default:
			  {
				 clc_first_frame_xm();
				  
				  break;
				  
			  }
		 }

/////////////////////////////////////////////////
///////////////////////////////////////////////


		}
		else
		{
			//save the second frame

			switch(rx_num)
			{
			  case 0://freame star
			 {
				 if(0xaa==com_data)
				 {
					 rx_buff[sec_basis+0]=com_data;
					 rx_num=0x01;

					 second_frame_end=0x00;
					 rx_star_flag=0x01;
				 }
				 else
				 {
					clc_second_frame_xm();
				 }
				 
				 
				 break;
			 } 
			 case 1://line or pole
			 {
				 
				 rx_buff[sec_basis+1]=com_data;
				 rx_num=0x02;
				
				 second_frame_end=0x00;
				 break;
			 }
			 case 2:////length
			 {
				 rx_buff[sec_basis+2]=com_data;
				 rx_num=0x03;
				 second_frame_end=0x00;
				
				 break;
			 }
			 
			 case 3://pole x hige byte or line delta y hige byte
			 {
				 
				 rx_buff[sec_basis+3]=com_data;
				 rx_num=0x04;
				 second_frame_end=0x00;
				 
				 
			 
				 break;      
							 
			  }
			  
				case 4://pole x low byte or line delta y low byte
			 {
				 rx_buff[sec_basis+4]=com_data;
				 rx_num=0x05;
				 second_frame_end=0x00;
				
				 break;
			 }
			 
			  case 5:////pole y hige byte or line sita hige byte
			 {
				 rx_buff[sec_basis+5]=com_data;
				 rx_num=0x06;
				 second_frame_end=0x00;

				  
				 
				 break;
			 }
			  case 6:////pole y low byte or line sita low byte
			 {
				 rx_buff[sec_basis+6]=com_data;
				 rx_num=0x07;
				 second_frame_end=0x00;
				


				 break;
			 }



			 case 7:///00
			 {
				 rx_buff[sec_basis+7]=com_data;
				 rx_num=0x08;
				 second_frame_end=0x00;
				

				 break;
			 }
			  case 8:///00
			 {
				 rx_buff[sec_basis+8]=com_data;
				 rx_num=0x09;
				 second_frame_end=0x00;
				

				 break;
			 }


			   case 9:///check sum
			 {
				 rx_buff[sec_basis+9]=com_data;
				 rx_num=10;
				 second_frame_end=0x00;
				
				 break;
			 }
				
			 
			 
			 case 10:////00
			 {
				 if(com_data==0xaf)
				 {
					  
					  rx_buff[sec_basis+10]=com_data;
					 
					 check_sum=0;
					 for(tempa=0;tempa<9;tempa++)
					 {
						 check_sum=check_sum+rx_buff[sec_basis+tempa];
					 }
					 
					 if (check_sum==rx_buff[sec_basis+9])
					 {
						  rx_num=0x00;
						  rx_end_flag=0x01;
						  rx_star_flag=0x01;
						  second_frame_end=1;
						  first_frame_end=1;
						 
						 
						 if(rx_buff[sec_basis+1]==0xf0)
						 {

							 cnt_find_pole_flag++;
							 
							 if (cnt_find_pole_flag>=10)
							 {
								 find_pole_flag=1;
								 cnt_find_pole_flag=0x00;
							 
							 }
							 else
							 {
								  find_pole_flag=0;
							 }
							 
						 }
						  else
						 {
							  cnt_no_find_pole_flag++;
							 
							 if (cnt_no_find_pole_flag>=10)
							 {
								 find_pole_flag=0;
								 cnt_no_find_pole_flag=0x00;
							 
							 }
						 }
						
						 
					 }
					 else
					 {
						 clc_first_frame_xm();
					 }

					 
	//				  YAW=(rx_buff[1]<<8|rx_buff[2]);//YAW，PITCH,ROLL为真实值的100倍
	//				  PITCH=(rx_buff[3]<<8|rx_buff[4]);
	//				  ROLL=(rx_buff[5]<<8|rx_buff[6]);
					 
					 
					 
					  
	//				  LED0=!LED0;
	//				 
				 }

				 else
				 {
					 clc_first_frame_xm();
					 
				 }
				 
				 break;
			 }
			
			 

			 default:
			  {
				 clc_first_frame_xm();
				  
				  break;
				  
			  }
		 }

		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	
	}
    //发送（进入移位）中断
    if (USART_GetITStatus(USART2, USART_IT_TXE))
    {
        USART2->DR = TxBuffer[TxCounter++]; //写DR清除中断标志
        if (TxCounter == count)
        {
            USART2->CR1 &= ~USART_CR1_TXEIE; //关闭TXE（发送中断）中断
        }
    }
	
	
	
	
	
	
	
	
	
}

//====uart3
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrvUart3Init(u32 br_num)
{
    USART_InitTypeDef USART_InitStructure;
//    USART_ClockInitTypeDef USART_ClockInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    USART_StructInit(&USART_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //开启USART2时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    //串口中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    //配置PD5作为USART2　Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //配置PD6作为USART2　Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //配置USART2
    //中断被屏蔽了
    USART_InitStructure.USART_BaudRate = br_num;                                    //波特率可以通过地面站配置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //在帧结尾传输1个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //禁用奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 //发送、接收使能
    //配置USART3时钟
////    USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;     //时钟低电平活动
////    USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;           //SLCK引脚上时钟输出的极性->低电平
////    USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;         //时钟第二个边沿进行数据捕获
////    USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //最后一位数据的时钟脉冲不从SCLK输出

    USART_Init(USART3, &USART_InitStructure);
	
	
//    USART_ClockInit(USART3, &USART_ClockInitStruct);

    //使能USART2接收中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		//发送中断不要打开，发送数据，不用串口发送数据
    //使能USART2
    USART_Cmd(USART3, ENABLE);
}

u8 Tx3Buffer[256];
u8 Tx3Counter = 0;
u8 count3 = 0;
void DrvUart3SendBuf(unsigned char *DataToSend, u8 data_num)
{
    u8 i;
    for (i = 0; i < data_num; i++)
    {
        Tx3Buffer[count3++] = *(DataToSend + i);
    }
    if (!(USART3->CR1 & USART_CR1_TXEIE))
    {
        USART_ITConfig(USART3, USART_IT_TXE, ENABLE); //打开发送中断
    }
}
u8 U3RxDataTmp[100];
u8 U3RxInCnt = 0;
u8 U3RxoutCnt = 0;
void drvU3GetByte(u8 data)
{
	U3RxDataTmp[U3RxInCnt++] = data;
	if(U3RxInCnt >= 100)
		U3RxInCnt = 0;
}
void drvU3DataCheck(void)
{
	while(U3RxInCnt!=U3RxoutCnt)
	{
		U3GetOneByte(U3RxDataTmp[U3RxoutCnt++]);
		if(U3RxoutCnt >= 100)
			U3RxoutCnt = 0;
	}
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





void Usart3_IRQ(void)
{
    u8 com_data;

    if (USART3->SR & USART_SR_ORE) //ORE中断
        com_data = USART3->DR;

    //接收中断
    if (USART_GetITStatus(USART3, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART3, USART_IT_RXNE); //清除中断标志
        com_data = USART3->DR;
				drvU3GetByte(com_data);
		////////////////////////////////
		///1:判断是不是数据头，依次存入数据，判断帧尾巴，置标志位
		//////////////////////////////
		
		
		
		
		
		
		
		///1:判断是不是数据头，依次存入数据，判断帧尾巴，置标志位
		//////////////////////////////
		if(first_frame_end==0)
		{
			//save the firsr frame

			switch(rx_num)
			{
			  case 0://freame star
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
			 case 1://line or pole
			 {
				 
				 rx_buff[1]=com_data;
				 rx_num=0x02;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
					 
				 
				 
				 break;
			 }
			 case 2:////length
			 {
				 rx_buff[2]=com_data;
				 rx_num=0x03;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			 case 3://pole x hige byte or line delta y hige byte
			 {
				 
				 rx_buff[3]=com_data;
				 rx_num=0x04;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 
			 
				 break;      
							 
			  }
			  
				case 4://pole x low byte or line delta y low byte
			 {
				 rx_buff[4]=com_data;
				 rx_num=0x05;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			 
			  case 5:////pole y hige byte or line sita hige byte
			 {
				 rx_buff[5]=com_data;
				 rx_num=0x06;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 6:////pole y low byte or line sita low byte
			 {
				 rx_buff[6]=com_data;
				 rx_num=0x07;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }



			 case 7:///00
			 {
				 rx_buff[7]=com_data;
				 rx_num=0x08;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 8:///00
			 {
				 rx_buff[8]=com_data;
				 rx_num=0x09;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }


			   case 9:///check sum
			 {
				 rx_buff[9]=com_data;
				 rx_num=10;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 10:///check sum
			 {
				 rx_buff[10]=com_data;
				 rx_num=11;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 11:///check sum
			 {
				 rx_buff[11]=com_data;
				 rx_num=12;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 12:///check sum
			 {
				 rx_buff[12]=com_data;
				 rx_num=13;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 13:///check sum
			 {
				 rx_buff[13]=com_data;
				 rx_num=14;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 14:///check sum
			 {
				 rx_buff[14]=com_data;
				 rx_num=15;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 15:///check sum
			 {
				 rx_buff[15]=com_data;
				 rx_num=16;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 16:///check sum
			 {
				 rx_buff[16]=com_data;
				 rx_num=17;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 17:///check sum
			 {
				 rx_buff[17]=com_data;
				 rx_num=18;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 18:///check sum
			 {
				 rx_buff[18]=com_data;
				 rx_num=19;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  case 19:///check sum
			 {
				 rx_buff[19]=com_data;
				 rx_num=20;
				 rx_end_flag=0x00;
				 rx_star_flag=0x01;
				 break;
			 }
			  
				
			 
			 
			 case 20:////00
			 {
				 if(com_data==0x0a)
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

/////////////////////////////////////////////////
///////////////////////////////////////////////


		}
		else
		{
			//save the second frame

			switch(rx_num)
			{
			  case 0://freame star
			 {
				 if(0xaa==com_data)
				 {
					 rx_buff[sec_basis+0]=com_data;
					 rx_num=0x01;

					 second_frame_end=0x00;
					 rx_star_flag=0x01;
				 }
				 else
				 {
					clc_second_frame();
				 }
				 
				 
				 break;
			 } 
			 case 1://line or pole
			 {
				 
				 rx_buff[sec_basis+1]=com_data;
				 rx_num=0x02;
				
				 second_frame_end=0x00;
				 break;
			 }
			 case 2:////length
			 {
				 rx_buff[sec_basis+2]=com_data;
				 rx_num=0x03;
				 second_frame_end=0x00;
				
				 break;
			 }
			 
			 case 3://pole x hige byte or line delta y hige byte
			 {
				 
				 rx_buff[sec_basis+3]=com_data;
				 rx_num=0x04;
				 second_frame_end=0x00;
				 
				 
			 
				 break;      
							 
			  }
			  
				case 4://pole x low byte or line delta y low byte
			 {
				 rx_buff[sec_basis+4]=com_data;
				 rx_num=0x05;
				 second_frame_end=0x00;
				
				 break;
			 }
			 
			  case 5:////pole y hige byte or line sita hige byte
			 {
				 rx_buff[sec_basis+5]=com_data;
				 rx_num=0x06;
				 second_frame_end=0x00;

				  
				 
				 break;
			 }
			  case 6:////pole y low byte or line sita low byte
			 {
				 rx_buff[sec_basis+6]=com_data;
				 rx_num=0x07;
				 second_frame_end=0x00;
				


				 break;
			 }



			 case 7:///00
			 {
				 rx_buff[sec_basis+7]=com_data;
				 rx_num=0x08;
				 second_frame_end=0x00;
				

				 break;
			 }
			  case 8:///00
			 {
				 rx_buff[sec_basis+8]=com_data;
				 rx_num=0x09;
				 second_frame_end=0x00;
				

				 break;
			 }


			   case 9:///check sum
			 {
				 rx_buff[sec_basis+9]=com_data;
				 rx_num=10;
				 second_frame_end=0x00;
				
				 break;
			 }
				
			 
			 
			 case 10:////00
			 {
				 if(com_data==0xaf)
				 {
					  
					  rx_buff[sec_basis+10]=com_data;
					 
					 check_sum=0;
					 for(tempa=0;tempa<9;tempa++)
					 {
						 check_sum=check_sum+rx_buff[sec_basis+tempa];
					 }
					 
					 if (check_sum==rx_buff[sec_basis+9])
					 {
						  rx_num=0x00;
						  rx_end_flag=0x01;
						  rx_star_flag=0x01;
						  second_frame_end=1;
						  first_frame_end=1;
						 
						 
						 if(rx_buff[sec_basis+1]==0xf0)
						 {

							 cnt_find_pole_flag++;
							 
							 if (cnt_find_pole_flag>=10)
							 {
								 find_pole_flag=1;
								 cnt_find_pole_flag=0x00;
							 
							 }
							 else
							 {
								  find_pole_flag=0;
							 }
							 
						 }
						  else
						 {
							  cnt_no_find_pole_flag++;
							 
							 if (cnt_no_find_pole_flag>=10)
							 {
								 find_pole_flag=0;
								 cnt_no_find_pole_flag=0x00;
							 
							 }
						 }
						
						 
					 }
					 else
					 {
						 clc_first_frame();
					 }

					 
	//				  YAW=(rx_buff[1]<<8|rx_buff[2]);//YAW，PITCH,ROLL为真实值的100倍
	//				  PITCH=(rx_buff[3]<<8|rx_buff[4]);
	//				  ROLL=(rx_buff[5]<<8|rx_buff[6]);
					 
					 
					 
					  
	//				  LED0=!LED0;
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

		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
    }
    //发送（进入移位）中断
    if (USART_GetITStatus(USART3, USART_IT_TXE))
    {
        USART3->DR = Tx3Buffer[Tx3Counter++]; //写DR清除中断标志
        if (Tx3Counter == count3)
        {
            USART3->CR1 &= ~USART_CR1_TXEIE; //关闭TXE（发送中断）中断
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//====uart4
void DrvUart4Init(u32 br_num)
{
    USART_InitTypeDef USART_InitStructure;
    //USART_ClockInitTypeDef USART_ClockInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    USART_StructInit(&USART_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE); //开启USART2时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    //串口中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_UART4_P;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_UART4_S;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

    //配置PC12作为UART5　Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //配置PD2作为UART5　Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //配置UART5
    //中断被屏蔽了
    USART_InitStructure.USART_BaudRate = br_num;                                    //波特率可以通过地面站配置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //在帧结尾传输1个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //禁用奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 //发送、接收使能
    USART_Init(UART4, &USART_InitStructure);

    //使能UART5接收中断
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    //使能USART5
    USART_Cmd(UART4, ENABLE);
}
u8 Tx4Buffer[256];
u8 Tx4Counter = 0;
u8 count4 = 0;
void DrvUart4SendBuf(unsigned char *DataToSend, u8 data_num)
{
    u8 i;
    for (i = 0; i < data_num; i++)
    {
        Tx4Buffer[count4++] = *(DataToSend + i);
    }

    if (!(UART4->CR1 & USART_CR1_TXEIE))
    {
        USART_ITConfig(UART4, USART_IT_TXE, ENABLE); //打开发送中断
    }
}
u8 U4RxDataTmp[100];
u8 U4RxInCnt = 0;
u8 U4RxoutCnt = 0;
void drvU4GetByte(u8 data)
{
	U4RxDataTmp[U4RxInCnt++] = data;
	if(U4RxInCnt >= 100)
		U4RxInCnt = 0;
}
void drvU4DataCheck(void)
{
	while(U4RxInCnt!=U4RxoutCnt)
	{
		U4GetOneByte(U4RxDataTmp[U4RxoutCnt++]);
		if(U4RxoutCnt >= 100)
			U4RxoutCnt = 0;
	}
}
void Uart4_IRQ(void)
{
    u8 com_data;

    if (UART4->SR & USART_SR_ORE) //ORE中断
    {
        com_data = UART4->DR;
    }
    //接收中断
    if (USART_GetITStatus(UART4, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(UART4, USART_IT_RXNE); //清除中断标志
        com_data = UART4->DR;
        drvU4GetByte(com_data);
    }

    //发送（进入移位）中断
    if (USART_GetITStatus(UART4, USART_IT_TXE))
    {
        UART4->DR = Tx4Buffer[Tx4Counter++]; //写DR清除中断标志
        if (Tx4Counter == count4)
        {
            UART4->CR1 &= ~USART_CR1_TXEIE; //关闭TXE（发送中断）中断
        }
    }
}

//====uart5
void DrvUart5Init(u32 br_num)
{
    USART_InitTypeDef USART_InitStructure;
    //USART_ClockInitTypeDef USART_ClockInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    USART_StructInit(&USART_InitStructure);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE); //开启USART2时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    //串口中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_UART5_P;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_UART5_S;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

    //配置PC12作为UART5　Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    //配置PD2作为UART5　Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    //配置UART5
    //中断被屏蔽了
    USART_InitStructure.USART_BaudRate = br_num;                                    //波特率可以通过地面站配置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8位数据
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //在帧结尾传输1个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //禁用奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //硬件流控制失能
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 //发送、接收使能
    USART_Init(UART5, &USART_InitStructure);

    //使能UART5接收中断
    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    //使能USART5
    USART_Cmd(UART5, ENABLE);
}
u8 Tx5Buffer[256];
u8 Tx5Counter = 0;
u8 count5 = 0;
void DrvUart5SendBuf(unsigned char *DataToSend, u8 data_num)
{
    u8 i;
    for (i = 0; i < data_num; i++)
    {
        Tx5Buffer[count5++] = *(DataToSend + i);
    }

    if (!(UART5->CR1 & USART_CR1_TXEIE))
    {
        USART_ITConfig(UART5, USART_IT_TXE, ENABLE); //打开发送中断
    }
}
u8 U5RxDataTmp[100];
u8 U5RxInCnt = 0;
u8 U5RxoutCnt = 0;
void drvU5GetByte(u8 data)
{
	U5RxDataTmp[U5RxInCnt++] = data;
	if(U5RxInCnt >= 100)
		U5RxInCnt = 0;
}
void drvU5DataCheck(void)
{
	while(U5RxInCnt!=U5RxoutCnt)
	{
		U5GetOneByte(U5RxDataTmp[U5RxoutCnt++]);
		if(U5RxoutCnt >= 100)
			U5RxoutCnt = 0;
	}
}
void Uart5_IRQ(void)
{
    u8 com_data;
	
    if (UART5->SR & USART_SR_ORE) //ORE中断
    {
        com_data = UART5->DR;
    }
    //接收中断
    if (USART_GetITStatus(UART5, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(UART5, USART_IT_RXNE); //清除中断标志   
        com_data = UART5->DR;
        drvU5GetByte(com_data);
    }

    //发送（进入移位）中断
    if (USART_GetITStatus(UART5, USART_IT_TXE))
    {
        UART5->DR = Tx5Buffer[Tx5Counter++]; //写DR清除中断标志
        if (Tx5Counter == count5)
        {
            UART5->CR1 &= ~USART_CR1_TXEIE; //关闭TXE（发送中断）中断
        }
    }
}



void DrvUartDataCheck(void)
{
	drvU1DataCheck();
	drvU2DataCheck();
	drvU3DataCheck();
	drvU4DataCheck();
	drvU5DataCheck();
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
