/*I2C_Init.c*/
#include "I2C_Init.h"
//#include "usart.h"
//#include "delay.h"
#include "math.h"


extern u8 light_flag;

void SDA_IN()	//上拉输入
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(IIC_SDA_PORT,&GPIO_InitStructure);
}
void SDA_OUT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
}

void SW_I2C_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(IIC_SCL_PORT_RCC, ENABLE);
	RCC_AHB1PeriphClockCmd(IIC_SDA_PORT_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(IIC_SCL_PORT, &GPIO_InitStructure);
	GPIO_SetBits(IIC_SCL_PORT, IIC_SCL_PIN);

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
	GPIO_SetBits(IIC_SDA_PORT,IIC_SDA_PIN);
	
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC| RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOF时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;//| GPIO_Pin_7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
	
	
	
}

//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();   //sda线输出
	IIC_SDA = 1;
	IIC_SCL = 1;
	
	MyDelayUs(8);
	
 	IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
	
	MyDelayUs(8);
	
	IIC_SCL = 0; //钳住I2C总线，准备发送或接收数据
}

//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();   //sda线输出
	IIC_SCL = 0;
	IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
	
 	MyDelayUs(8);
	
	IIC_SCL = 1;
	IIC_SDA = 1; //发送I2C总线结束信号
	
	MyDelayUs(8);
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;

	SDA_IN();     //SDA设置为输入
	IIC_SDA = 1;
	
	MyDelayUs(6);
	
	IIC_SCL = 1;
	
	MyDelayUs(6);

	while(READ_SDA)
	{
		ucErrTime++;

		if(ucErrTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}

	IIC_SCL = 0;  //时钟输出0
	return 0;
}

//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 0;
	
	MyDelayUs(6);
	
	IIC_SCL = 1;
	
	MyDelayUs(6);
	
	IIC_SCL = 0;
}

//不产生ACK应答
void IIC_NAck(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 1;
	
	MyDelayUs(6);
	
	IIC_SCL = 1;
	
	MyDelayUs(6);
	
	IIC_SCL = 0;
}

//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(u8 txd)
{
  u8 t;
	SDA_OUT();
  IIC_SCL = 0;     //拉低时钟开始数据传输

	for(t = 0; t < 8; t++)
  {
		if((txd & 0x80) >> 7)
			IIC_SDA = 1;
		else
			IIC_SDA = 0;

		txd <<= 1;
		
		MyDelayUs(6); 
		
		IIC_SCL = 1;
		
		MyDelayUs(6);
		
		IIC_SCL = 0;
		
		MyDelayUs(6);
  }
}

//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC_Read_Byte(u8 ack)
{
	u8 i, receive = 0;
	SDA_IN();     //SDA设置为输入

	for(i = 0; i < 8; i++ )
	{
    IIC_SCL = 0;
		
    MyDelayUs(80);        //读出数据错误关键在这个延时，与从器件的I2C通讯速率有关
		
		IIC_SCL = 1;
    receive <<= 1;
    if(READ_SDA)
			receive++;
		
		MyDelayUs(80);        //读出数据错误关键在这个延时，与从器件的I2C通讯速率有关
  }

  if (!ack)
    IIC_NAck(); //发送nACK
  else
    IIC_Ack();  //发送ACK

	return receive;
}
