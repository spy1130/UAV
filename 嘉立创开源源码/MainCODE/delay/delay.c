#include "delay.h"

static unsigned int fac_us;
static unsigned int fac_ms;

void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;				//为系统时钟的1/8  
	fac_ms=(unsigned int)fac_us*1000;//代表每个ms需要的systick时钟数   
}	

void delay_us(unsigned int xus)  //1.864S  
{		
	unsigned int temp;	
	//进行参数的判定
	if((xus<=0) || (xus > 1864135))
		return ;
	SysTick->LOAD=xus*fac_us; 					//时间加载	 RELOAD=900  		 
	SysTick->VAL=0x00;        					//清空计数器 CURRENT=0
	
	SysTick->CTRL|=1 ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~1;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 	
}

void delay_ms(unsigned int xms)
{	 		  	  
	unsigned int temp;	
	//进行参数的判定
	if((xms<=0) || (xms > 1864))//传递参数的判断
		return ;	
	SysTick->LOAD=(u32)xms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=1 ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~1;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  	    
}



