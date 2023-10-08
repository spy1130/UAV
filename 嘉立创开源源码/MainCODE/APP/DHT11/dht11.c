#include "dht11.h"
#include "delay.h"

/*
	功能：采集温湿度通过串口进行显示
	步骤：
	1，开启时钟
	2，设置GPIO引脚 :out in
	3，操作
	
	所需函数：
	1，初始化函数
	2，检测函数
	3，读取一位数据
	4，读取一个字节
*/

//初始化函数
//PB12 FT 接一个DHT11
unsigned char Dht11_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOB时钟
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	return 0;
}

void Dht11_Start(void)//DHT11
{
	DHT11_PIN_MODE_OUT() 
	//DHT11_SIGNAL_OUT = 1;
	DHT11_SIGNAL_OUT = 0;
	delay_ms(20);
	DHT11_SIGNAL_OUT = 1;//已经完成发送开始信号	
	delay_us(30);
}

unsigned char Dht11_Check(void)
{
	unsigned char counter = 0;
	
	
	DHT11_PIN_MODE_IN();//设置为输入
	
	while(DHT11_SIGNAL_IN  && counter<100)//DHT11会拉低40~80us
	{
		delay_us(1);
		counter++;
	}
	if(counter >= 100)
		return 1;//没有检测到DHT11
	counter = 0;
	while(!DHT11_SIGNAL_IN  && counter<=80)//DHT11拉低后会再次拉高40~80us
	{
		delay_us(1);
		counter++;
	}
	if(counter > 80)
		return 1;//没有检测到DHT11
	else
		return 0;//检测到DHT11
	
}

unsigned char Dht11_ReadBit(void)
{
	unsigned char counter = 0;
	
	//设置为PB12输入模式
	//T接收到的是低电平
	DHT11_PIN_MODE_IN()
	
	while(DHT11_SIGNAL_IN && counter<100)
	{
		delay_us(1);
		counter++;
	}
	counter = 0;
	//前面相当于是把低电平时间过滤掉
	//D代表高电平
	while(!DHT11_SIGNAL_IN  && counter<100)
	{
		delay_us(1);
		counter++;
	}
	delay_us(40);
	if(DHT11_SIGNAL_IN)
		return 1;
	else
		return 0;
}

unsigned char Dht11_ReadByte(void)
{
	unsigned char counter = 0;
	unsigned char temp = 0 , dat = 0;
	for(counter = 0; counter < 8; counter++)
	{
		dat <<= 1;
		dat |= Dht11_ReadBit();
	}
	return dat;
}

//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
unsigned char DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	unsigned char buf[5];
	unsigned char i;
	
	Dht11_Start();
	if(Dht11_Check()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=Dht11_ReadByte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}

