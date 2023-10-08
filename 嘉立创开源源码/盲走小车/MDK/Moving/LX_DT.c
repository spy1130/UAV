#include "LX_DT.h"
#include "delay.h"
u8 receive_buffer[50]; //发送数据缓存
u8 Nano_send_buffer[50]; //发送数据缓存
u8 send_buffer[50]; //发送数据缓存
u8 StopFlag = 0;

//extern u8 MissionFlag;
//extern float fAngle[3];
S16_Byte FirePosition;


/*
通信协议规定(接收)
起始位：		0x67
				0x93
PIC：			0xXX
				0xXX
				0xXX
				0xXX
RT:				0xXX
				0xXX
				0xXX
				0xXX
Fire:			0xXX
				0xXX
				0xXX
				0xXX
终止位：		0xE2
*/
void Flight_DataReceive(u8 data)
{
	static u8 my_flag = 0;
	static u8 len = 0;		//数据长度
	switch (my_flag)
	{
		case 0:
		{
			if(data == 0x67)
			{
				my_flag ++;
				Nano_send_buffer[len ++] = data;
				USART_SendData(USART3,data);
				delay_us(20);
			}
		}
		break;
		case 1:
		{
			if(data == 0x93)
			{
				my_flag ++;
				Nano_send_buffer[len ++] = data;
				USART_SendData(USART3,data);
				delay_us(20);
			}
		}
		break;
		case 2:
		{	
			Nano_send_buffer[len ++] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 3:
		{	
			Nano_send_buffer[len ++] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 4:
		{
			Nano_send_buffer[len ++] = data;
			my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 5:
		{	
			Nano_send_buffer[len ++] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 6:
		{
			Nano_send_buffer[len ++] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		break;
		case 7:
		{	
			Nano_send_buffer[len ++] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 8:
		{	
			Nano_send_buffer[len ++] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 9:
		{	
			Nano_send_buffer[len ++] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 10:
		{	
			Nano_send_buffer[len ++] = data;
			FirePosition.byet[0] = data;//(0,0)为无效
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 11:
		{	
			Nano_send_buffer[len ++] = data;
			FirePosition.byet[1] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 12:
		{	
			Nano_send_buffer[len ++] = data;
			FirePosition.byet[2] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 13:
		{	
			Nano_send_buffer[len ++] = data;
			FirePosition.byet[3] = data;
				my_flag ++;
			USART_SendData(USART3,data);
			delay_us(20);
		}
		break;
		case 14:
		{
			if(data == 0xe2)
			{
				my_flag = 0;
				Nano_send_buffer[len ++] = data;
				USART_SendData(USART3,data);
				//Nano_DataSend();
				len = 0;
				delay_us(20);
			}
		}
		break;
		default:break;
		}	
	}	
}

void Nano_DataSend(void)
{
	
	for(u8 i = 0;i < 15;i ++)
	{
		USART_SendData(USART3,Nano_send_buffer[i]);
		delay_us(60);
	}
		
}
void OpenMV_DataSend(void)
{
	u8 count = 0;
	send_buffer[count ++] = 0x67;
	send_buffer[count ++] = 0x94;
	send_buffer[count ++] = StopFlag;
	send_buffer[count ++] = 0xE3;
	
	for(int i = 0;i < count;i ++)
	{
		USART_SendData(USART3,send_buffer[i]);
		delay_us(15 * (count - 1));
	}
}

/*
通信协议规定(发送)
起始位：		0x67
				0x94
任务Flag：		u8
坐标：			S16_x
				S16_y
终止位：		0xEE
*/
u8 DataSend(u8 data)
{
	
	u8 count = 0;
	send_buffer[count ++] = 0x67;
	send_buffer[count ++] = 0x94;
	send_buffer[count ++] = data;
	send_buffer[count ++] = 0xe2;
	
	for(int i = 0;i < count;i ++)
	{
		USART_SendData(USART1,send_buffer[i]);
		delay_us(100);
	}
	return 1;
}
