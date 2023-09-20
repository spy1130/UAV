/*KS10X.c*/
#include "I2C_Init.h"
#include "sys.h"
//#include "delay.h"
//#include "usart.h"
#include "math.h"
#include "ks103.h"

#include "DataScope_DP.h"

#define uchar unsigned char
#define uint unsigned int
int state_read;
u16	sumx_aa;

float		sum_x_aa;


void Single_WriteI2C(u8 SlaveAddress, u8 REG_Address, u8 REG_data)
{
	IIC_Start();                    //起始信号

	IIC_Send_Byte(SlaveAddress);   //发送设备地址+写信号
	//while(IIC_Wait_Ack());       //有问题，不能用while等待
	IIC_Wait_Ack();

	IIC_Send_Byte(REG_Address);    //内部寄存器地址
	//while(IIC_Wait_Ack());       //有问题，不能用while等待
	IIC_Wait_Ack();

	IIC_Send_Byte(REG_data);       //内部寄存器数据
	//while(IIC_Wait_Ack());       //有问题，不能用while等待
	IIC_Wait_Ack();

	IIC_Stop();                     //发送停止信号
}

//**************************************
//从I2C设备读取一个字节数据
//**************************************
u8 Single_ReadI2C(u8 SlaveAddress, u8 REG_Address)
{
	u8 REG_data = 0;

	IIC_Start();

	IIC_Send_Byte(SlaveAddress);
	//while(IIC_Wait_Ack());       //有问题，不能用while等待
	IIC_Wait_Ack();
	
	IIC_Send_Byte(REG_Address);
	//while(IIC_Wait_Ack());      //有问题，不能用while等待
	IIC_Wait_Ack();

	IIC_Start();

	IIC_Send_Byte(SlaveAddress + 1);
	//while(IIC_Wait_Ack());      //有问题，不能用while等待
	IIC_Wait_Ack();

	MyDelayUs(100);
	
	REG_data = IIC_Read_Byte(0);

	IIC_Stop();

	return REG_data;
}

float Read_KS10X_Data(u8 SlaveAddress, u8 command)
{
	u16 sumx = 0.0;
	float sum_x = 0.0;

	Single_WriteI2C(SlaveAddress, 0x02, command);

	if (command == 0xb4 || command == 0xbc || command == 0xbf)
		MyDelayMs(90);
	else if (command == 0xb8 || command == 0xba || command == 0xbd || command == 0xbe)
		MyDelayMs(70);
	else if (command == 0xb0 || command == 0xb2)
		MyDelayMs(80);
	else if (command == 0xa0)
		MyDelayMs(1);

	sumx = Single_ReadI2C(SlaveAddress, 0x02);        //高8位
	sumx <<= 8;
	sumx += Single_ReadI2C(SlaveAddress, 0x03);       //低8位

	sum_x = (float)sumx / 10;          //mm转换为cm

	return sum_x;
}

void Read_KS10X_Data_delay(u8 SlaveAddress, u8 command)
{
	static int Send_Count_a=0,s_i_a=0;
	
	if(state_read==0)
	{
		//????????
		Single_WriteI2C(SlaveAddress, 0x02, command);
		
		state_read=0x01;
	}
	
	else if(state_read==1)
	{
		//?????20??,???????40??
		
		state_read=0x02;
	}
	else if(state_read==2)
	{
		//?????20??,???????40??
		
		state_read=0x03;
	}
	else
	{
		//???????,?????40??,?????????
		sumx_aa = Single_ReadI2C(SlaveAddress, 0x02);        //?8?
		sumx_aa <<= 8;
		sumx_aa += Single_ReadI2C(SlaveAddress, 0x03);       //?8?

		sum_x_aa = (float)sumx_aa / 10;          //mm???cm
		state_read=0x00;
		
		
		DataScope_Get_Channel_Data((float)sum_x_aa, 1 );
//		DataScope_Get_Channel_Data((float)piston_ad_kalman, 2 );
//		DataScope_Get_Channel_Data((float)piston_ad_av, 3 );
//		DataScope_Get_Channel_Data((float)piston_f, 4 );
//		DataScope_Get_Channel_Data((float)piston_f_kalman, 5 );
//		DataScope_Get_Channel_Data((float)piston_f_av, 6 );


		Send_Count_a = DataScope_Data_Generate(1);
		for( s_i_a = 0 ; s_i_a < Send_Count_a; s_i_a++) 
		{
			while((USART2->SR&0X40)==0);  
			USART2->DR = DataScope_OutPut_Buffer[s_i_a]; 
		}

	}
}	
//

void KS10X_Change_Addr_Init(u8 OldAddr, u8 NewAddr)  	//此函数用来实现选择超声波的地址
{
	Change_Addr(OldAddr, NewAddr);
	MyDelayMs(80);
}

void Change_Addr(u8 OldAdddr, u8 NewAddr)
{
	Single_WriteI2C(OldAdddr, 0x02, 0x9a);             //默认原地址是0x00;
	MyDelayMs(1);

	Single_WriteI2C(OldAdddr, 0x02, 0x92);
	MyDelayMs(1);

	Single_WriteI2C(OldAdddr, 0x02, 0x9e);
	MyDelayMs(1);

	Single_WriteI2C(OldAdddr, 0x02, NewAddr);
	MyDelayMs(100);

	Single_WriteI2C(NewAddr, 0x02, 0xb0);
	MyDelayMs(80);
}

	/*
	MyDelayMs(1);
	SCL_IN();
	for (i = 0; i < 100; i++)
	{
		SCL_IN();
		if (READ_SCL == 0)
			printf("wait %d for detect finish.\r\n", i);
		else
		{
			printf("detect finish\r\n");
			break;
		}
		MyDelayMs(1);
	}
	SCL_OUT();
	*/
