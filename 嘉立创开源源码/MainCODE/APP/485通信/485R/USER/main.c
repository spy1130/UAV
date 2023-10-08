/*
	PC13接led指示灯，led亮灭变化
*/              
#include "led.h"
#include "delay.h"
#include "button.h"
#include "rs485.h"

uint8_t rs485_send_buf[16];
uint8_t rs485_recv_buf[2] = "OK";

int main(void) 
{
	uint8_t len = 0;
	uint8_t t=0;
	
	//抢占式优先级 2 bit ，响应式优先级:2 bit
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	delay_init();
	
	Led_Init();
	
	//Button_Init();
	
	RS485_Init(9600);
	
	led1 = 1;
	led2 = 0;
	RS485_TX_EN=0;	
	while(1)
	{

		if(RS485_RX_CNT >= 16)
		{
			if(RS485_RX_BUF[1] == 'o')
			{
				led1 = !led1;
				RS485_Send_Data(rs485_recv_buf,2);
			}
			RS485_RX_CNT = 0;
			RS485_RX_BUF[1] = 'C';
		}	
		else
			t++;
		if(t >= 100)
		{
			led2 = !led2;
			t=0;
		}
		delay_ms(5);
		
	}
} 


