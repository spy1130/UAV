#include "dht11.h"
#include "delay.h"

/*
	���ܣ��ɼ���ʪ��ͨ�����ڽ�����ʾ
	���裺
	1������ʱ��
	2������GPIO���� :out in
	3������
	
	���躯����
	1����ʼ������
	2����⺯��
	3����ȡһλ����
	4����ȡһ���ֽ�
*/

//��ʼ������
//PB12 FT ��һ��DHT11
unsigned char Dht11_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����GPIOBʱ��
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
	DHT11_SIGNAL_OUT = 1;//�Ѿ���ɷ��Ϳ�ʼ�ź�	
	delay_us(30);
}

unsigned char Dht11_Check(void)
{
	unsigned char counter = 0;
	
	
	DHT11_PIN_MODE_IN();//����Ϊ����
	
	while(DHT11_SIGNAL_IN  && counter<100)//DHT11������40~80us
	{
		delay_us(1);
		counter++;
	}
	if(counter >= 100)
		return 1;//û�м�⵽DHT11
	counter = 0;
	while(!DHT11_SIGNAL_IN  && counter<=80)//DHT11���ͺ���ٴ�����40~80us
	{
		delay_us(1);
		counter++;
	}
	if(counter > 80)
		return 1;//û�м�⵽DHT11
	else
		return 0;//��⵽DHT11
	
}

unsigned char Dht11_ReadBit(void)
{
	unsigned char counter = 0;
	
	//����ΪPB12����ģʽ
	//T���յ����ǵ͵�ƽ
	DHT11_PIN_MODE_IN()
	
	while(DHT11_SIGNAL_IN && counter<100)
	{
		delay_us(1);
		counter++;
	}
	counter = 0;
	//ǰ���൱���ǰѵ͵�ƽʱ����˵�
	//D����ߵ�ƽ
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

//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
unsigned char DHT11_Read_Data(u8 *temp,u8 *humi)    
{        
 	unsigned char buf[5];
	unsigned char i;
	
	Dht11_Start();
	if(Dht11_Check()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
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

