#include "dht11.h"
#include "delay.h"
#include "usart.h"

struct DHT11 dht11;

/*
���ܣ��ɼ���ʪ��ͨ��������ʾ
Ӳ�����ߣ�
	DHT11 VCC-3.3V GND-GND SIGNAL-PB12����
	
��̲��裺
	1������GPIOBʱ��
	2������PB12Ϊ���ģʽ DHT11��MCU 
	3����дDHT11��غ���
����Ҫ��д�ĺ�����
1����ʼ������
2����ʼ��������λ������
3����⺯��
4������DHT11 1λ���ݺ���
5������һ���ֽ�����
6��5�����ݣ�����һ�����ݲɼ��ĺ�������������1��
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

//DHT11��ʼ����/��λ����
void Dht11_Start(void)
{
	//����PB12Ϊ���ģʽ
	DHT11_PIN_MODE_OUT()
	
	//DHT11_SIGNAL_OUT = 1;
	DHT11_SIGNAL_OUT = 0;
	delay_ms(20);//����18ms
	DHT11_SIGNAL_OUT = 1;
	delay_us(40);
}

//DHT11��⺯��
//1������ʧ�� 0:��ʾ�ɹ�
unsigned char Dht11_Check(void)
{
	unsigned char counter = 0;
	//����PB12Ϊ����ģʽ
	DHT11_PIN_MODE_IN()
	
	while( DHT11_SIGNAL_IN && counter < 100)//counter��ʱʱ��
	{
		counter++;
		delay_us(1);
	}
	if(counter >= 100)
		return 1;
	counter = 0;
	while( !DHT11_SIGNAL_IN  && counter < 100)//counter��ʱʱ��
	{
		counter++;
		delay_us(1);
	}
	if(counter >= 80)
		return 1;
	else
		return 0;//�ɹ�
	
}
	

unsigned char Dht11_ReadBit(void)
{
	unsigned char counter = 0;
	//����PB12Ϊ����ģʽ
	DHT11_PIN_MODE_IN()
	
	while( DHT11_SIGNAL_IN && counter < 60)//counter��ʱʱ��
	{
		counter++;
		delay_us(1);
	}
	counter = 0;
	while( !DHT11_SIGNAL_IN  && counter < 60)//counter��ʱʱ��
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
		dat <<= 1;//Ϊ��һ��������λ��׼�� 8bit ת��һ���ֽ�  
		temp = Dht11_ReadBit();
		if(temp != 0)
			dat |= 1;   
		else
			dat |= 0;  
	}
	return dat;
}

unsigned char DHT11_Read_Data(void)//˫��
{
	unsigned char counter = 0;
	unsigned char dat[5];
	
	Dht11_Start();//��ȡDHT11���ݵĵ�һ�������Ϳ�ʼ�ź�
	
	//DHT11�����ݸ�ʽ��  0:HH8 HL8 TH8 TL8 CHECK
	if(0 == Dht11_Check())//��ȡDHT11���ݵĵڶ��������DHT11���ȴ�DHT11��Ӧ
	{
		for(counter = 0;counter < 5; counter++)
		{
			dat[counter] = Dht11_ReadByte();//��ȡDHT11���ݵĵ���������ȡ40bit�����ݣ�5���ֽڣ�
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











