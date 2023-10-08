#include "temperature.h"
#include "adc.h"
#include "delay.h"

//���òɼ��¶Ⱥ���֮ǰ����Ҫ�ȵ���Adc_Init();
//�ɼ�һ���¶�
unsigned int Adc_Get_Temperature(void)
{
	unsigned int temp;
	
	//�ؼ�������ADC����ͨ���ĵ�ѹ���ù���
	ADC_TempSensorVrefintCmd(ENABLE);//�����ڲ��¶ȴ�����
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);//239.5
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//�������Ϊ1������ͨ����ʼת��
	//Ӳ������Ϊ0���Ѿ���ʼת��
	while(ADC_GetSoftwareStartConvStatus(ADC1) != 0);//0x004 0100  00000
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//EOC 
	temp = ADC_GetConversionValue(ADC1);
	return temp;
}

/*
�ڲ��¶ȼ��㹫ʽ��
	Temperature (in ��C) = {(V25 - VSENSE) / Avg_Slope} + 25.
	Where, 
	V25 = VSENSE value for 25��C and
	Avg_Slope = Average Slope for curve between Temperature vs. VSENSE (given in 
	mV/�� C or ��V/ ��C). 
	Refer to the Electrical characteristics section for the actual values of V25 and 
	Avg_Slope.
*/
//�õ��¶ȵ�ƽ��ֵԭʼֵ����ѹֵV�����ֵ�ѹ��
unsigned int Adc_Filter_Average_Temperature(unsigned char num)
{
	unsigned char i = 0;
	unsigned long sum = 0;
	for(; i < num; i++)
	{
		sum += Adc_Get_Temperature();
		delay_ms(10);
	}
	return sum/10;
}


float Adc_Temperature_Handle(unsigned int dat)
{
	float temp;
	temp = dat*3.3/4096;		//ģ���ѹֵ 
	temp = (1.43 - temp) / (4.3 /1000) + 25;	//ת��Ϊ�¶�ֵ 	
	return temp;
}






