#include "delay.h"

static unsigned int fac_us;
static unsigned int fac_ms;

void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;				//Ϊϵͳʱ�ӵ�1/8  
	fac_ms=(unsigned int)fac_us*1000;//����ÿ��ms��Ҫ��systickʱ����   
}	

void delay_us(unsigned int xus)  //1.864S  
{		
	unsigned int temp;	
	//���в������ж�
	if((xus<=0) || (xus > 1864135))
		return ;
	SysTick->LOAD=xus*fac_us; 					//ʱ�����	 RELOAD=900  		 
	SysTick->VAL=0x00;        					//��ռ����� CURRENT=0
	
	SysTick->CTRL|=1 ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~1;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	 	
}

void delay_ms(unsigned int xms)
{	 		  	  
	unsigned int temp;	
	//���в������ж�
	if((xms<=0) || (xms > 1864))//���ݲ������ж�
		return ;	
	SysTick->LOAD=(u32)xms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							//��ռ�����
	SysTick->CTRL|=1 ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~1;	//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	  	    
}



