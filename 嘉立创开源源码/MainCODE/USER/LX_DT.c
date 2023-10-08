#include "LX_DT.h"

u8 receive_buffer[50]; //发送数据缓存
u8 send_buffer[50]; //发送数据缓存

s16 TargetPoint[2];
u8  MissionFlag = 0;

u8  LEDFlag = 0;
u8  LaserFlag = 0;
u8  PagFlag = 0;

S16_Byte Fire_Location;
S16_Byte RT_Location;
S16_Byte RT_Location_PIC;
u8 Page_OK_Flag;

/*
通信协议规定(接收)
起始位：		0x66
				0x98
激光笔,语音：	0x00
舵机：			S16
终止位：		0xEE
*/
/*
void DataReceive(u8 data)
{
	static u8 my_flag = 0;
	//static u8 _datalen = 0;		//数据长度
	static u8 servonum = 0;
	switch (my_flag)
	{
		case 0:
		{
			if(data == 0x66)
			my_flag++;
			//_datalen = 0;
		}
		break;
		case 1:
		{
			if(data == 0x01)//开关LED指示火情
				my_flag = 2;
			
			
		}
		break;		
		case 2:
		{	
			LEDFlag = data;
				my_flag ++;
		}
		break;
		case 3:
		{	
			PagFlag = data;
			//LEDFlag=PagFlag;
				my_flag = 6;
		}
		break;
		case 4:
		{	
			Fire_Location.byet[servonum ++] = data;
			if(servonum == 4){
				my_flag = 6;
				Fire_Location_Send(Fire_Location.Data[0],Fire_Location.Data[1]);
			}
			
		}
		break;
		case 5:
		{	
			RT_Location.byet[servonum ++] = data;
			if(servonum == 4){
				my_flag = 6;
				RT_Location_Send(RT_Location.Data[0],RT_Location.Data[1]);
			}
		}
		break;
		case 10:
		{
			RT_Location_PIC.byet[servonum ++] = data;
			if(servonum == 4){
				my_flag = 6;
				RT_Location_Send_PIC(RT_Location_PIC.Data[0],RT_Location_PIC.Data[1]);
			}
		}
		break;
		case 6:
		{
			if(data == 0xee )
			{
				
//				LaserFlag = receive_buffer[0];
//				PagFlag = receive_buffer[1];
//				ServoAngle[0].byet[0] = receive_buffer[2];
//				ServoAngle[0].byet[1] = receive_buffer[3];
//				ServoAngle[1].byet[0] = receive_buffer[4];
//				ServoAngle[1].byet[1] = receive_buffer[5];
				my_flag = 0;
			}
		break;
		default:break;
		}
	}
}
*/
void DataReceive(u8 data)
{
	LEDFlag=data;
}

/*
通信协议规定(发送)
起始位：		0x66
				0x98
任务Flag：		u8
坐标：			S16_x
				S16_y
终止位：		0xEE
*/
void DataSend(void)
{
	u8 count = 0;
	//s16 tmpdata;
	send_buffer[count ++] = 0x66;
	send_buffer[count ++] = 0x98;
	send_buffer[count ++] = 0x01;
//	tmpdata = TargetPoint[0];
//	send_buffer[count ++] = BYTE0(tmpdata);
//	send_buffer[count ++] = BYTE1(tmpdata);
//	tmpdata = TargetPoint[1];
//	send_buffer[count ++] = BYTE0(tmpdata);
//	send_buffer[count ++] = BYTE1(tmpdata);
	send_buffer[count ++] = 0xEE;
	
	for(int i = 0;i < count;i ++)
	{
		USART_SendData(USART1,send_buffer[i]);
		delay_us(15 * (count - 1));
	}
}

void RT_Location_Send(s16 x,s16 y){
	u8 count =0;
	send_buffer[count ++]=0x77;
	send_buffer[count ++]=0xAA;
	send_buffer[count ++]=BYTE0(x);
	send_buffer[count ++]=BYTE1(x);
	send_buffer[count ++]=BYTE0(y);
	send_buffer[count ++]=BYTE1(y);
	send_buffer[count ++]=0xEE;
	
	for(int i = 0;i < count;i ++)
	{
		USART_SendData(USART2,send_buffer[i]);
		delay_us(15 * (count - 1));
	}

}

void RT_Location_Send_PIC (s16 x,s16 y){
	u8 count =0;
	send_buffer[count ++]=0x77;
	send_buffer[count ++]=0x54;
	send_buffer[count ++]=BYTE0(x);
	send_buffer[count ++]=BYTE1(x);
	send_buffer[count ++]=BYTE0(y);
	send_buffer[count ++]=BYTE1(y);
	send_buffer[count ++]=0xEE;
	
	for(int i = 0;i < count;i ++)
	{
		USART_SendData(USART2,send_buffer[i]);
		delay_us(15 * (count - 1));
	}

}



void Fire_Location_Send(s16 x,s16 y){
	u8 count =0;
	send_buffer[count ++]=0x77;
	send_buffer[count ++]=0xBB;
	send_buffer[count ++]=BYTE0(x);
	send_buffer[count ++]=BYTE1(x);
	send_buffer[count ++]=BYTE0(y);
	send_buffer[count ++]=BYTE1(y);
	send_buffer[count ++]=0xEE;
	
	for(int i = 0;i < count;i ++)
	{
		USART_SendData(USART2,send_buffer[i]);
		delay_us(15 * (count - 1));
	}

}


void Takeoff(u8 data)
{
	u8 count = 0;
	//s16 tmpdata;
	send_buffer[count ++] = 0x66;
	send_buffer[count ++] = 0x01;
	send_buffer[count ++] = data;
	send_buffer[count ++] = 0xEE;
	
	for(int i = 0;i < count;i ++)
	{
		USART_SendData(USART1,send_buffer[i]);
		delay_us(15 * (count - 1));
	}
}




//串口2
void DataReceive2(u8 data)
{
	static u8 my_flag2 = 0;
	//static u8 _datalen = 0;		//数据长度

	switch (my_flag2)
	{
		case 0:
		{
			if(data == 0x77)
			my_flag2++;
			//_datalen = 0;
		}
		break;
		case 1:
		{
			if(data == 0x99)//开关LED指示火情
				my_flag2 ++;
		}
		break;
		case 2:
		{	
			Takeoff(data);
				my_flag2 = 6;
		}
		break;
		case 6:
		{
			if(data == 0xEE )
			{
//				LaserFlag = receive_buffer[0];
//				PagFlag = receive_buffer[1];
//				ServoAngle[0].byet[0] = receive_buffer[2];
//				ServoAngle[0].byet[1] = receive_buffer[3];
//				ServoAngle[1].byet[0] = receive_buffer[4];
//				ServoAngle[1].byet[1] = receive_buffer[5];
				my_flag2 = 0;
			}
		break;
		default:break;
		}	
	}	
}

