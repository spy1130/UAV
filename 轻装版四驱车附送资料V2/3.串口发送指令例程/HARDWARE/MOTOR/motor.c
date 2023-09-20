#include "motor.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
void MiniBalance_Motor_Init(void)
{
	RCC->APB2ENR|=1<<3;       //PORTB时钟使能   
//	GPIOB->CRL&=0XFFFF0FFF;   //PORTB12 13 14 15推挽输出
//	GPIOB->CRL|=0X00002000;   //PORTB12 13 14 15推挽输出
//	GPIOB->CRH&=0XFF00FFFF;   //PORTB12 13 14 15推挽输出
//	GPIOB->CRH|=0X00220000;   //PORTB12 13 14 15推挽输出
//	GPIOB->ODR|=0<<3;  
//		GPIOB->ODR|=0<<12;  
//		GPIOB->ODR|=0<<13;  
}
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	//MiniBalance_Motor_Init();  //初始化电机控制所需IO
	RCC->APB2ENR|=1<<11;       //使能TIM1时钟    
	RCC->APB2ENR|=1<<2;        //PORTA时钟使能     
	GPIOA->CRH&=0XFFFFF000;    //PORTA8 11复用输出
	GPIOA->CRH|=0X00000BBB;    //PORTA8 11复用输出
	TIM1->ARR=arr;             //设定计数器自动重装值 
	TIM1->PSC=psc;             //预分频器不分频
	TIM1->CCMR1|=6<<12;        //CH4 PWM1模式	
	TIM1->CCMR2|=6<<4;         //CH1 PWM1模式	
	TIM1->CCMR1|=6<<4;         //CH1 PWM1模式	
	TIM1->CCMR1|=1<<11;        //CH4预装载使能	 
	TIM1->CCMR1|=1<<3;         //CH1预装载使能	  
	TIM1->CCMR2|=1<<3;         //CH1预装载使能	  
	TIM1->CCER|=1<<8;         //CH4输出使能	   
	TIM1->CCER|=1<<4;         //CH4输出使能	   
	TIM1->CCER|=1<<0;          //CH1输出使能	
	TIM1->BDTR |= 1<<15;       //TIM1必须要这句话才能输出PWM
	TIM1->CR1=0x8000;          //ARPE使能 
	TIM1->CR1|=0x01;          //使能定时器1 			
	
	
	RCC->APB1ENR|=1<<1;        //TIM3时钟使能
	RCC->APB2ENR|=1<<3;        //PORTB时钟使能     
	GPIOA->CRL&=0X00FFFFFF;    //PORTA6 7复用输出
	GPIOA->CRL|=0XBB000000;    //PORTA6 7复用输出
	
	GPIOB->CRL&=0XFFFFFFF0;    //PORTB0复用输出
	GPIOB->CRL|=0X0000000B;    //PORTB0复用输出
	TIM3->ARR=arr;             //设定计数器自动重装值 
	TIM3->PSC=psc;             //预分频器不分频
	TIM3->CCMR1|=6<<12;        //CH4 PWM1模式	
	TIM3->CCMR2|=6<<4;         //CH1 PWM1模式	
	TIM3->CCMR1|=6<<4;         //CH1 PWM1模式	
	TIM3->CCMR1|=1<<11;        //CH4预装载使能	 
	TIM3->CCMR1|=1<<3;         //CH1预装载使能	  
	TIM3->CCMR2|=1<<3;         //CH1预装载使能	  
	TIM3->CCER|=1<<8;         //CH4输出使能	   
	TIM3->CCER|=1<<4;         //CH4输出使能	   
	TIM3->CCER|=1<<0;          //CH1输出使能	
	TIM3->CR1=0x8000;          //ARPE使能 
	TIM3->CR1|=0x01;          //使能定时器1 			
} 

