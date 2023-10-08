/*
PA3:ADC_IN3
*/

/*
编写程序步骤：
1，配置GPIOA相应的引脚
2，配置ADC相应的参数
3，开启ADC和GPIO的时钟
4，复位ADC
5，校准
6，等待校准完成

7，编写AD采集函数（ADC开启）
8，编写滤波函数：多次采集取平均值
9，将数据通过串口发送显示
*/

#include "delay.h"
#include "adc.h"

void Adc_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_InitTypeDef ADC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启GPIOA的时钟
		
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA ,&GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//开启ADC的时钟 72M
	//ADC时钟分频
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//72M/6 = 12M < 14M
	
	//ADC_DeInit(ADC1);
	
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_DataAlign  = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	
	ADC_Cmd(ADC1,ENABLE);
	//软件设置为1：开启复位校准功能
	//硬件设置为0：复位校准完成
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) != 0);
	
	//开始校准
	//软件设置为1：开启校准功能
	//硬件设置为0：校准完成
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) != 0);

}

//采集一次数据的函数
static unsigned int Adc_Start_Conversion(void)
{	
	unsigned int temp;
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,1,ADC_SampleTime_239Cycles5);//239.5
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	//软件设置为1：规则通道开始转换
	//硬件设置为0：已经开始转换
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






