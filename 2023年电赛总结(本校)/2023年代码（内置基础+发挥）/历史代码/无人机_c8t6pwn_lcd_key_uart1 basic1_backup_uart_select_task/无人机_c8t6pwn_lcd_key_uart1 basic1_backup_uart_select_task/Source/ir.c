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
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);		//������GPIO�ķ���һ��
	EXTI_ClearITPendingBit(EXTI_Line0);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	//���ڴ˴����ⲿ�ж�ֻ��һ��������ж����ȼ������������á�
	NVIC_Init(&NVIC_InitStructure);
}
u8 dat_recv()	//�˺������жϷ������е��ã���PG0�ָ��ߵ�ƽ�󣬶Ըߵ�ƽ����ʱ����м�ʱ��
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
	while(1)									//ʹ�ô�ѭ����Ϊ��ȷ�������ؽ�32λ����ȫ��������ɡ�
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
		{
			time=dat_recv();
			if(time>=250)	break;				//��Ч�źţ�
			if(time>=200&&time<250)				//4-5ms
			{
				valid=1;						//��Ч����ʼ�źţ���ʼ�������ݡ�
			}
			else if(time>=20&&time<=35)			//�߼�0(200-1000ms)��
			{
				bit=0;
			}
			else if(time>=60&&time<=90)			//�߼�1(1200ms-1800ms)��
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
