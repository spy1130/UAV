#include <ir.h>
u8 fin;
u32 irdata;
u8 ir_flag;

void irinit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);		//把配置GPIO的放在一起。
	EXTI_ClearITPendingBit(EXTI_Line0);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	//由于此处的外部中断只有一个，因此中断优先级可以任意设置。
	NVIC_Init(&NVIC_InitStructure);
}
u8 dat_recv()	//此函数在中断服务函数中调用，当PG0恢复高电平后，对高电平持续时间进行计时。
{
	u8 t=0;
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
	{
		t++;
		delay_us(20);
		if(t>=250)
		{
			break;
		}
	}
	return t;
}
void EXTI0_IRQHandler()
{
	u8 time=0,valid=0,bit=0,num=0;
	ir_flag = 1;
	while(1)									//使用大循环是为了确保连续地将32位数据全部接收完成。
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
		{
			time=dat_recv();
			if(time>=250)	break;				//无效信号；
			if(time>=200&&time<250)				//4-5ms
			{
				valid=1;						//有效的起始信号，开始接收数据。
			}
			else if(time>=20&&time<=35)			//逻辑0(200-1000ms)；
			{
				bit=0;
			}
			else if(time>=60&&time<=90)			//逻辑1(1200ms-1800ms)；
			{
				bit=1;
			}
			if(valid==1)
			{
				irdata<<=1;
				irdata+=bit;
				if(num>=32)
				{
					fin=1;
					break;
				}
			}
			num++;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}
