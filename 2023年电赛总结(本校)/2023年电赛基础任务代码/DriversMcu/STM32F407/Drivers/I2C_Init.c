/*I2C_Init.c*/
#include "I2C_Init.h"
//#include "usart.h"
//#include "delay.h"
#include "math.h"


extern u8 light_flag;

void SDA_IN()	//��������
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(IIC_SCL_PORT, &GPIO_InitStructure);
	GPIO_SetBits(IIC_SCL_PORT, IIC_SCL_PIN);

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //��©���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
	GPIO_SetBits(IIC_SDA_PORT,IIC_SDA_PIN);
	
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC| RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOFʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;//| GPIO_Pin_7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN ;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	
	
	
	
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();   //sda�����
	IIC_SDA = 1;
	IIC_SCL = 1;
	
	MyDelayUs(8);
	
 	IIC_SDA = 0; //START:when CLK is high,DATA change form high to low
	
	MyDelayUs(8);
	
	IIC_SCL = 0; //ǯסI2C���ߣ�׼�����ͻ��������
}

//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();   //sda�����
	IIC_SCL = 0;
	IIC_SDA = 0; //STOP:when CLK is high DATA change form low to high
	
 	MyDelayUs(8);
	
	IIC_SCL = 1;
	IIC_SDA = 1; //����I2C���߽����ź�
	
	MyDelayUs(8);
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime = 0;

	SDA_IN();     //SDA����Ϊ����
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

	IIC_SCL = 0;  //ʱ�����0
	return 0;
}

//����ACKӦ��
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

//������ACKӦ��
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

//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void IIC_Send_Byte(u8 txd)
{
  u8 t;
	SDA_OUT();
  IIC_SCL = 0;     //����ʱ�ӿ�ʼ���ݴ���

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

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 IIC_Read_Byte(u8 ack)
{
	u8 i, receive = 0;
	SDA_IN();     //SDA����Ϊ����

	for(i = 0; i < 8; i++ )
	{
    IIC_SCL = 0;
		
    MyDelayUs(80);        //�������ݴ���ؼ��������ʱ�����������I2CͨѶ�����й�
		
		IIC_SCL = 1;
    receive <<= 1;
    if(READ_SDA)
			receive++;
		
		MyDelayUs(80);        //�������ݴ���ؼ��������ʱ�����������I2CͨѶ�����й�
  }

  if (!ack)
    IIC_NAck(); //����nACK
  else
    IIC_Ack();  //����ACK

	return receive;
}
