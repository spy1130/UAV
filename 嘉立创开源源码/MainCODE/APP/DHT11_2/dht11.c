#include "dht11.h"
#include "delay.h"
#include "usart.h"

struct DHT11 dht11;

/*
功能：采集温湿度通过串口显示
硬件连线：
	DHT11 VCC-3.3V GND-GND SIGNAL-PB12引脚
	
编程步骤：
	1，开启GPIOB时钟
	2，配置PB12为输出模式 DHT11：MCU 
	3，编写DHT11相关函数
所需要编写的函数：
1，初始化函数
2，开始函数（复位函数）
3，检测函数
4，接收DHT11 1位数据函数
5，接收一个字节数据
6，5节数据，接收一次数据采集的函数：两次数据1秒
*/


unsigned char Dht11_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	DHT11_SIGNAL_OUT = 1;
	return 0;
}

//DHT11开始函数/复位函数
void Dht11_Start(void)
{
	//设置PB12为输出模式
	DHT11_PIN_MODE_OUT()
	
	//DHT11_SIGNAL_OUT = 1;
	DHT11_SIGNAL_OUT = 0;
	delay_ms(20);//至少18ms
	DHT11_SIGNAL_OUT = 1;
	delay_us(40);
}

//DHT11检测函数
//1：代表失败 0:表示成功
unsigned char Dht11_Check(void)
{
	unsigned char counter = 0;
	//设置PB12为输入模式
	DHT11_PIN_MODE_IN()
	
	while( DHT11_SIGNAL_IN && counter < 100)//counter超时时间
	{
		counter++;
		delay_us(1);
	}
	if(counter >= 100)
		return 1;
	counter = 0;
	while( !DHT11_SIGNAL_IN  && counter < 100)//counter超时时间
	{
		counter++;
		delay_us(1);
	}
	if(counter >= 80)
		return 1;
	else
		return 0;//成功
	
}
	

unsigned char Dht11_ReadBit(void)
{
	unsigned char counter = 0;
	//设置PB12为输入模式
	DHT11_PIN_MODE_IN()
	
	while( DHT11_SIGNAL_IN && counter < 60)//counter超时时间
	{
		counter++;
		delay_us(1);
	}
	counter = 0;
	while( !DHT11_SIGNAL_IN  && counter < 60)//counter超时时间
	{
		counter++;
		delay_us(1);
	}
	delay_us(40);
	
	if(DHT11_SIGNAL_IN != 0)
		return 1;
	else
		return 0;
}

unsigned char Dht11_ReadByte(void)
{
	unsigned char counter = 0;
	unsigned char dat = 0,temp = 0;        
	for(counter = 0;counter < 8; counter++)
	{
		dat <<= 1;//为下一次数据移位做准备 8bit 转换一个字节  
		temp = Dht11_ReadBit();
		if(temp != 0)
			dat |= 1;   
		else
			dat |= 0;  
	}
	return dat;
}

unsigned char DHT11_Read_Data(void)//双向
{
	unsigned char counter = 0;
	unsigned char dat[5];
	
	Dht11_Start();//读取DHT11数据的第一步，发送开始信号
	
	//DHT11的数据格式：  0:HH8 HL8 TH8 TL8 CHECK
	if(0 == Dht11_Check())//读取DHT11数据的第二步，检测DHT11，等待DHT11响应
	{
		for(counter = 0;counter < 5; counter++)
		{
			dat[counter] = Dht11_ReadByte();//读取DHT11数据的第三步，读取40bit的数据（5个字节）
		}
		
		if(dat[4] == (dat[0] + dat[1] + dat[2] + dat[3]))
		{
			dht11 = dat[2];
			*humi = dat[0];
			return 0;
		}	
	}
	return 1;	
}











