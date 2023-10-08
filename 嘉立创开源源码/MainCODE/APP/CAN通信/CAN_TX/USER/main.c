/*
	第二个STM32
*/              
#include "led.h"
#include "delay.h"
#include "button.h"
#include "can.h"
#include "usart.h"

int main(void) 
{
	uint8_t len = 0;
	uint8_t can_sendbuf = 'A';
	uint8_t can_recvbuf = 0;
	//抢占式优先级 2 bit ，响应式优先级:2 bit
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	Usart1_Init(115200);
	delay_init();
	
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN初始化环回模式,波特率500Kbps
	
	Led_Init();
	
	Button_Init();
	
	printf("CAN test\n\r\n");
	
	led1 = 1;//发送成功指示灯
	led2 = 1;//接收成功指示灯
	while(1)
	{
		if(button_flag == 1)
		{
			if(Can_Send_Msg(&can_sendbuf,1) == 0)
				led1 = !led1;
			button_flag = 0;
		}
		
		//len = Can_Receive_Msg(&can_recvbuf,1);
		if(can_flag == 1)//接收到有数据
		{	
			can_flag = 0;
			printf("%d ",buf);
 			if(buf == 'B')
			{
				led2 = !led2;
				buf = 0;
				button_flag = 1;
				delay_ms(1000);	
			}
			
		}
	}
} 


