/*
PA3:ADC_IN3
*/

/*
��д�����裺
1������GPIOA��Ӧ������
2������ADC��Ӧ�Ĳ���
3������ADC��GPIO��ʱ��
4����λADC
5��У׼
6���ȴ�У׼���

7����дAD�ɼ�������ADC������
8����д�˲���������βɼ�ȡƽ��ֵ
9��������ͨ�����ڷ�����ʾ
*/

#include "delay.h"
#include "adc.h"

void Adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//����GPIOA��ʱ��
		
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//����ADC��ʱ�� 72M
	//ADCʱ�ӷ�Ƶ
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72M/6 = 12M < 14M
	
	//ADC_DeInit(ADC1);
	
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_DataAlign  = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	
	ADC_Cmd(ADC1,ENABLE);
	//�������Ϊ1��������λУ׼����
	//Ӳ������Ϊ0����λУ׼���
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) != 0);
	
	//��ʼУ׼
	//�������Ϊ1������У׼����
	//Ӳ������Ϊ0��У׼���
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) != 0);

}

//�ɼ�һ�����ݵĺ���
static unsigned int Adc_Start_Conversion(void)
{	
	unsigned int temp;
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,1,ADC_SampleTime_239Cycles5);//239.5
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//�������Ϊ1������ͨ����ʼת��
	//Ӳ������Ϊ0���Ѿ���ʼת��
	while(ADC_GetSoftwareStartConvStatus(ADC1) != 0);//0x004 0100  00000
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//EOC 
	temp = ADC_GetConversionValue(ADC1);
	return temp;
	//return ADC_GetConversionValue(ADC1);
}

unsigned int Adc_Filter_Average(unsigned char num)
{
	unsigned char i = 0;
	unsigned long sum = 0;
	for(; i < num; i++)
	{
		sum += Adc_Start_Conversion();
		delay_ms(10);
	}
	return sum/10;
}






