#include "motor.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
void MiniBalance_Motor_Init(void)
{
	RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ��   
//	GPIOB->CRL&=0XFFFF0FFF;   //PORTB12 13 14 15�������
//	GPIOB->CRL|=0X00002000;   //PORTB12 13 14 15�������
//	GPIOB->CRH&=0XFF00FFFF;   //PORTB12 13 14 15�������
//	GPIOB->CRH|=0X00220000;   //PORTB12 13 14 15�������
//	GPIOB->ODR|=0<<3;  
//		GPIOB->ODR|=0<<12;  
//		GPIOB->ODR|=0<<13;  
}
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
	//MiniBalance_Motor_Init();  //��ʼ�������������IO
	RCC->APB2ENR|=1<<11;       //ʹ��TIM1ʱ��    
	RCC->APB2ENR|=1<<2;        //PORTAʱ��ʹ��     
	GPIOA->CRH&=0XFFFFF000;    //PORTA8 11�������
	GPIOA->CRH|=0X00000BBB;    //PORTA8 11�������
	TIM1->ARR=arr;             //�趨�������Զ���װֵ 
	TIM1->PSC=psc;             //Ԥ��Ƶ������Ƶ
	TIM1->CCMR1|=6<<12;        //CH4 PWM1ģʽ	
	TIM1->CCMR2|=6<<4;         //CH1 PWM1ģʽ	
	TIM1->CCMR1|=6<<4;         //CH1 PWM1ģʽ	
	TIM1->CCMR1|=1<<11;        //CH4Ԥװ��ʹ��	 
	TIM1->CCMR1|=1<<3;         //CH1Ԥװ��ʹ��	  
	TIM1->CCMR2|=1<<3;         //CH1Ԥװ��ʹ��	  
	TIM1->CCER|=1<<8;         //CH4���ʹ��	   
	TIM1->CCER|=1<<4;         //CH4���ʹ��	   
	TIM1->CCER|=1<<0;          //CH1���ʹ��	
	TIM1->BDTR |= 1<<15;       //TIM1����Ҫ��仰�������PWM
	TIM1->CR1=0x8000;          //ARPEʹ�� 
	TIM1->CR1|=0x01;          //ʹ�ܶ�ʱ��1 			
	
	
	RCC->APB1ENR|=1<<1;        //TIM3ʱ��ʹ��
	RCC->APB2ENR|=1<<3;        //PORTBʱ��ʹ��     
	GPIOA->CRL&=0X00FFFFFF;    //PORTA6 7�������
	GPIOA->CRL|=0XBB000000;    //PORTA6 7�������
	
	GPIOB->CRL&=0XFFFFFFF0;    //PORTB0�������
	GPIOB->CRL|=0X0000000B;    //PORTB0�������
	TIM3->ARR=arr;             //�趨�������Զ���װֵ 
	TIM3->PSC=psc;             //Ԥ��Ƶ������Ƶ
	TIM3->CCMR1|=6<<12;        //CH4 PWM1ģʽ	
	TIM3->CCMR2|=6<<4;         //CH1 PWM1ģʽ	
	TIM3->CCMR1|=6<<4;         //CH1 PWM1ģʽ	
	TIM3->CCMR1|=1<<11;        //CH4Ԥװ��ʹ��	 
	TIM3->CCMR1|=1<<3;         //CH1Ԥװ��ʹ��	  
	TIM3->CCMR2|=1<<3;         //CH1Ԥװ��ʹ��	  
	TIM3->CCER|=1<<8;         //CH4���ʹ��	   
	TIM3->CCER|=1<<4;         //CH4���ʹ��	   
	TIM3->CCER|=1<<0;          //CH1���ʹ��	
	TIM3->CR1=0x8000;          //ARPEʹ�� 
	TIM3->CR1|=0x01;          //ʹ�ܶ�ʱ��1 			
} 

