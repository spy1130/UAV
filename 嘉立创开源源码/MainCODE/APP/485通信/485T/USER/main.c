/*
	PC13接led指示灯，led亮灭变化
*/              
#include "led.h"
#include "delay.h"
#include "button.h"
#include "rs485.h"

uint8_t rs485_send_buf[16] = "doubixiaohanhan";

int main(void) 
{
	//抢占式优先级 2 bit ，响应式优先级:2 bit
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	delay_init();
	
	Led_Init();
	
	Button_Init();
	
	RS485_Init(9600);
	
	led1 = 1;
	led2 = 1;
	while(1)
	{
		if(1 == button_flag)//按键按下,发送一次数据
		{
			RS485_Send_Data(rs485_send_buf,16);//发送16个字节 		
			led2 = !led2;	
			button_flag = 0;
		}
		
		if(RS485_RX_CNT >= 2)
		{
			if('K' == RS485_RX_BUF[1])
			{
				led1 = !led1;	
				//button_flag = 1;
				RS485_RX_BUF[1] = 'C';
				delay_ms(1000);
				button_flag = 1;
			}
			RS485_RX_CNT = 0;
		}				
	}
} 


