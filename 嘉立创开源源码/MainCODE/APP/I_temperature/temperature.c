#include "temperature.h"
#include "adc.h"
#include "delay.h"

//调用采集温度函数之前，需要先调用Adc_Init();
//采集一次温度
unsigned int Adc_Get_Temperature(void)
{
	unsigned int temp;
	
	//关键，区别ADC其它通道的电压配置过程
	ADC_TempSensorVrefintCmd(ENABLE);//开启内部温度传感器
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);//239.5
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//软件设置为1：规则通道开始转换
	//硬件设置为0：已经开始转换
	while(ADC_GetSoftwareStartConvStatus(ADC1) != 0);//0x004 0100  00000
	
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//EOC 
	temp = ADC_GetConversionValue(ADC1);
	return temp;
}

/*
内部温度计算公式：
	Temperature (in °C) = {(V25 - VSENSE) / Avg_Slope} + 25.
	Where, 
	V25 = VSENSE value for 25°C and
	Avg_Slope = Average Slope for curve between Temperature vs. VSENSE (given in 
	mV/° C or μV/ °C). 
	Refer to the Electrical characteristics section for the actual values of V25 and 
	Avg_Slope.
*/
//得到温度的平均值原始值（电压值V）数字电压量
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
	temp = dat*3.3/4096;		//模拟电压值 
	temp = (1.43 - temp) / (4.3 /1000) + 25;	//转换为温度值 	
	return temp;
}






