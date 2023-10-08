/**
  * @file    can1.c(can回环实验)
  * @author  逗比小憨憨
  * @version V1.1
  * @date    xxxx-xx-xx
  * @brief   CAN驱动
  ******************************************************************************
  * @attention
  *
  * 实验平台:STM32F103C8T6
  * 编程步骤:
		1.初始化CAN外设、波特率，位的组成
		2.配置筛选器，方便接收数据
		3.发送数据，并接收，使用回环模式测试
  * 测试：
	  备注：关于STM32中CAN1_RX0_IRQn和CAN1_RX1_IRQn的使用？
		  有2个3级深度的接收缓冲区：FIFO0和FIFO1，
		  每个FIFO都可以存放3个完整的报文，它们完全由硬件来管理。
		  如果是来自FIFO0的接收中断，则用CAN1_RX0_IRQn中断来处理。
		  如果是来自FIFO1的接收中断，则用CAN1_RX1_IRQn中断来处理。
		  在CAN的初始化配置过程中，用CAN_FilterFIFOAssignment来选择要使用FIFO。
 */

#include "can1.h"
#include "usart.h"


/********************************全局变量定义区 ******************************/
struct CAN_STRUCT my_can_struct;
/****************************************************************************/

/********************************静态函数定义区 ******************************/
#if CAN_MODE_CAN_LOOPBACK
static void can_gpio_config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
 	
	GPIO_PinRemapConfig (GPIO_Remap1_CAN1 ,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = CAN_PIN_TX;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(CAN_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = CAN_PIN_RX;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(CAN_PORT, &GPIO_InitStruct);
}
#endif

static void can_mode_config(uint8_t bs1,uint8_t bs2,uint8_t sjw,uint16_t pre)	
{
	CAN_InitTypeDef CAN_InitTypeStruct;
	
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_CAN1, ENABLE);
	CAN_InitTypeStruct.CAN_ABOM = ENABLE;
	CAN_InitTypeStruct.CAN_AWUM = ENABLE;
	CAN_InitTypeStruct.CAN_Mode = CAN_Mode_LoopBack;
	CAN_InitTypeStruct.CAN_NART = ENABLE; 
	CAN_InitTypeStruct.CAN_RFLM = DISABLE;
	CAN_InitTypeStruct.CAN_TTCM = DISABLE;
	CAN_InitTypeStruct.CAN_TXFP = DISABLE; 
	
	CAN_InitTypeStruct.CAN_BS1 = bs1;
	CAN_InitTypeStruct.CAN_BS2 = bs2;
	CAN_InitTypeStruct.CAN_SJW = sjw;
	CAN_InitTypeStruct.CAN_Prescaler = pre;
	
	CAN_Init(CAN1,&CAN_InitTypeStruct);
}

static void can_filter_config(void)
{
	CAN_FilterInitTypeDef CAN_FilterInitStruct;
	
	CAN_FilterInitStruct.CAN_FilterActivation = ENABLE;
	#if CAN_SELECTION_FIFO_0
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	#else
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;
	#endif
	CAN_FilterInitStruct.CAN_FilterNumber = 6;
	CAN_FilterInitStruct.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStruct.CAN_FilterMode  = CAN_FilterMode_IdMask;
	
	CAN_FilterInitStruct.CAN_FilterIdHigh = ((CAN_ID<<CAN_ID_SHIFT |CAN_ID_MODE |CAN_RTR_Data)&0xFFFF0000)>>16;
	CAN_FilterInitStruct.CAN_FilterIdLow  = ((CAN_ID<<CAN_ID_SHIFT |CAN_ID_MODE |CAN_RTR_Data)&0xFFFF);
	
	CAN_FilterInitStruct.CAN_FilterMaskIdHigh = 0xFFFF;
	CAN_FilterInitStruct.CAN_FilterMaskIdLow  = 0xFFFF;	

	CAN_FilterInit(&CAN_FilterInitStruct);
	#if CAN_SELECTION_FIFO_0
	CAN_ITConfig (CAN1,CAN_IT_FMP0,ENABLE);	
	#else
	CAN_ITConfig (CAN1,CAN_IT_FMP1,ENABLE);	
	#endif
}	

static void can_nvic_config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	#if CAN_SELECTION_FIFO_0
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	#else
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
	#endif
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
/****************************************************************************/

/********************************中断函数编写区 ******************************/
#if CAN_SELECTION_FIFO_0
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    if(CAN_GetITStatus(CAN1, CAN_IT_FMP0)  ==  SET)
    {
		CAN_Receive(CAN1, CAN_FIFO0, &my_can_struct.RxMessage);  		
    }
    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
}
#else
void CAN1_RX1_IRQHandler(void)
{
    if(CAN_GetITStatus(CAN1, CAN_IT_FMP1)  ==  SET)
    {
		CAN_Receive(CAN1, CAN_FIFO1, &my_can_struct.RxMessage);    
    }
    CAN_ClearITPendingBit(CAN1, CAN_IT_FMP1);	
}
#endif

/****************************************************************************/

/********************************外部函数编写区 ******************************/
void my_can_transmit_data(uint8_t *dat,uint8_t length)
{
	uint8_t i = 0;
	CanTxMsg can_transmit_data;
	#if CAN_ID_EXTEND_MODE
	can_transmit_data.StdId = 0;//无影响，任意值
	can_transmit_data.ExtId = CAN_ID;
	can_transmit_data.IDE = CAN_ID_MODE;
	#else
	can_transmit_data.StdId = CAN_ID;
	can_transmit_data.ExtId = 0;//无影响，任意值
	can_transmit_data.IDE = CAN_ID_MODE;
	#endif
	
	can_transmit_data.RTR = CAN_RTR_DATA;
	
	can_transmit_data.DLC = length;
	for(i = 0; i < length; i++)
	{
		can_transmit_data.Data[i] = dat[i];
	}
	CAN_Transmit(CAN1,&can_transmit_data);
}


void my_can_init(void)
{
	#if CAN_MODE_CAN_LOOPBACK
	can_gpio_config();
	#endif
	can_mode_config(CAN_BS1_5tq, CAN_BS2_3tq, CAN_SJW_2tq, 4);
    can_nvic_config();
	can_filter_config();
}

void my_can_receive_test(void)
{
	uint8_t count = 0;
	uint8_t length = my_can_struct.RxMessage.DLC;
	printf("\nreceive data:%dbyte \t\n",length);
	for(count = 0; count < length; count++)
		printf("%d ",my_can_struct.RxMessage.Data[count]);
	printf("\t\n");
}
/****************************************************************************/











