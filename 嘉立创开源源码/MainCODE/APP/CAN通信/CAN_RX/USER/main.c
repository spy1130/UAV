/*
	�ڶ���STM32
*/              
#include "led.h"
#include "delay.h"
#include "button.h"
#include "can.h"

int main(void) 
{
	uint8_t len = 0;
	uint8_t can_sendbuf = 'B';
	uint8_t can_recvbuf = 0;
	
	//��ռʽ���ȼ� 2 bit ����Ӧʽ���ȼ�:2 bit
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	delay_init();
	
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN��ʼ������ģʽ,������500Kbps
	
	Led_Init();
		
	led1 = 1;//���ͳɹ�ָʾ��
	led2 = 0;//���ճɹ�ָʾ��
	while(1)
	{
		//len = Can_Receive_Msg(&can_recvbuf,1);
		if(can_flag == 1)//���յ�������
		{	
			//len = 0;
			led1 = !led1;
			can_flag = 0;
 			if(buf == 'A')
			{
				if(Can_Send_Msg(&can_sendbuf,1) == 0)
					led2 = !led2;
				buf = 0;
			}
		}		
	}
} 


