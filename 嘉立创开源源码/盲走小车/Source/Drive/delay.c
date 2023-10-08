#include "delay.h"
#include "misc.h"

static uint16_t  fac_us=0;
static uint16_t fac_ms=0;

static volatile uint32_t sv_uiDelay = 0;
void SysTick_Init(void)
{	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SystemCoreClock/8000000;
	fac_ms=(uint16_t)fac_us*1000;
}

void delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;	    
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
