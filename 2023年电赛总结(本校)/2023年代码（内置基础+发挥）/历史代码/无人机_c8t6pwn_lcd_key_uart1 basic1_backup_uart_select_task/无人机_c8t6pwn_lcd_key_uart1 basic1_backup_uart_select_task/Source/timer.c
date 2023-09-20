#include "timer.h"
#include "led.h"
#include "delay.h"
extern int stop_time;

int key_count=0x00;
int key_flag=0x00;
int key_last_value=0x00;
int key_num=0x00;
char key_true=0x00;

int steering_pwmval=1500;

int down_count=0x00;
u8 	down_flag=0x00;

int 	up_count=0x00;
u8 	up_flag=0x00;
u8	 	emergence_flag=0x00;







/* TIM2 �ж����ȼ����ú��� */
void NVIC_TIM2Enable(void)
{
	NVIC_InitTypeDef NVIC_initstructure;
	//�ڴ�δ�������ȼ����飬 ʹ��ϵͳĬ�ϵķ���
	NVIC_initstructure.NVIC_IRQChannel = TIM2_IRQn; //ѡ�� TIM2 �ж�ͨ��
	NVIC_initstructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ж�ͨ��
	NVIC_initstructure.NVIC_IRQChannelPreemptionPriority = 3; //�趨��ռ���ȼ�Ϊ 0
	NVIC_initstructure.NVIC_IRQChannelSubPriority = 1; //�趨��Ӧ���ȼ�Ϊ 0
	NVIC_Init(&NVIC_initstructure);
} 

/////////////////////////////////
//judge_key_num();
////////////////////////////////
void judge_key_num()              //������ľ�����̣���ʵ��0-9���룬���������л����
{
	key_num = 0x11;
	c1 = 0;c2 = 1;c3 = 1;c4 = 1;  //������һ��Ϊ0
	if(r1 == 0&&r2 == 1&&r3 == 1&&r4 == 1)
	{
		key_num = 1;
	}
	else if(r1==1&&r2==0&&r3==1&&r4==1)
	{
		key_num = 5;
	}
	else if(r1==1&&r2==1&&r3==0&&r4==1)
	{
		key_num = 9;
	}
	else if(r1==1&&r2==1&&r3==1&&r4==0)
	{
		key_num = 12;
	}
	c1 = 1;c2 = 0;c3 = 1;c4 = 1;  //�����ڶ���Ϊ0
	if(r1 == 0&&r2 == 1&&r3 == 1&&r4 == 1)
	{
		key_num = 2;
	}
	else if(r1==1&&r2==0&&r3==1&&r4==1)
	{
		key_num = 6;
	}
	else if(r1==1&&r2==1&&r3==0&&r4==1)
	{
		key_num = 0;
	}
	else if(r1==1&&r2==1&&r3==1&&r4==0)
	{
		key_num = 13;
	}
	c1 = 1;c2 = 1;c3 = 0;c4 = 1;  //����������Ϊ0
	if(r1 == 0&&r2 == 1&&r3 == 1&&r4 == 1)
	{
		key_num = 3;
	}
	else if(r1==1&&r2==0&&r3==1&&r4==1)
	{
		key_num = 7;
	}
	else if(r1==1&&r2==1&&r3==0&&r4==1)
	{
		key_num = 10;
	}
	else if(r1==1&&r2==1&&r3==1&&r4==0)
	{
		key_num = 14;
	}

	c1 = 1;c2 = 1;c3 = 1;c4 = 0;  //����������Ϊ0
	if(r1 == 0&&r2 == 1&&r3 == 1&&r4 == 1)
	{
		key_num = 4;
	}
	else if(r1==1&&r2==0&&r3==1&&r4==1)
	{
		key_num = 8;
	}	
	else if(r1==1&&r2==1&&r3==0&&r4==1)
	{
		key_num = 11;
	}
	else if(r1==1&&r2==1&&r3==1&&r4==0)
	{
		key_num = 15;
	}
	c1=1;c2=1;c3=1;c4=1;
}


///////////////////////////////////
//
/////////////////////////////////////

void scan_key(void)
{
	switch (key_count)
	{
		case 0:
			c1=0;
			c2=0;
			c3=0;
			c4=0;
		
			if(r1==1&&r2==1&&r3==1&&r4==1)
			{
				key_count=0;
				key_flag=0;
				key_last_value=0;
			}
			else
			{
				key_count=1;
				
			}
			break;
		case 1:   //������  �жϼ�ֵ
			c1=0;
			c2=0;
			c3=0;
			c4=0;
		
			if(r1==1&&r2==1&&r3==1&&r4==1)
			{
				key_count=0;
				key_flag=0;
				key_last_value=0;
				
			}
			else
			{
				key_count=2;
				judge_key_num();//�жϼ�ֵ
				if(key_num==0x11)
				{
					key_count=0;
					key_flag=0;
					key_last_value=0;
				}
				else
				{
					key_last_value=key_num;//�����ֵ
				}
				
				

			}
			break;
		case 2:   //�ٴ�ȷ�ϰ�������
			c1=0;
			c2=0;
			c3=0;
			c4=0;
		
			if(r1==1&&r2==1&&r3==1&&r4==1)
			{
				key_count=0;
				key_flag=0;
				key_last_value=0;
				
			}
			else
			{
				judge_key_num();
				if(key_last_value==key_num)
				{
					
					key_count=3;
					key_flag=1;
					key_last_value=key_num;
					key_true = key_num;
				}
				else
				{
					key_count=0;
					key_flag=0;
					key_last_value=0;
				}
			}
			
		
			break;
		case 3:  //�ȴ������ͷ�
			c1=0;
			c2=0;
			c3=0;
			c4=0;
			
			if(r1==1&&r2==1&&r3==1&&r4==1)
			{
				key_count=0;
				
				key_last_value=key_num;
				
			}
			else
			{
				key_count=3;
			}
			break;
		default:
			break;
	}
	
}
/////////////////////////////
//
//////////////////////////////
























/* ��ʱ�� 2 ��ʼ�������� period-�������ڣ� Prescaler-Ԥ��Ƶֵ */
//��ʱ��2����1#ͨ������ 
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

   //??TIMER3 ����Ϊ������
//   TIM_DeInit(TIM4);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM2�ж�,��������ж�
	//TIM_ETRClockMode2Config(TIM4, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);//this sentense make tim3 work in mode of etr
	TIM_SetCounter(TIM2, 0);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	
	
	
	TIM_Cmd(TIM2, ENABLE);
}

void judge_excute_steering(void)
{
	if(emergenc_io==0)//����Ȩ���
	{
		//down//������ֹͣ�����Ǽ�ͣ�������ˣ�������Ҫ���£��ͷż�ͣ
		steering_pwmval=1500+200;//high mean low speed
		TIM_SetCompare1(TIM3,steering_pwmval);
		emergence_flag=1;
		
		up_flag=0;	
		
		
	
		
	}
	else
	{
		if((string_pb6==1)&&(string_pb7==0))
		{
			//down
			if(down_flag==00)
			{
				down_flag=0x01;
				//down_count=0x00;
				//up
				steering_pwmval=1500+200;//high mean low speed
				TIM_SetCompare1(TIM3,steering_pwmval);
			
				
			}
			else
			{
				if(down_count>=2900)
				{
					//time is up
					//stop
			
					steering_pwmval=1500;//high mean low speed
					TIM_SetCompare1(TIM3,steering_pwmval);
					
					
					
					
				}
			}
			
		}
		else if((string_pb6==0)&&(string_pb7==1))
		{
			//up

			if(up_flag==00)
			{
				up_flag=0x01;
				//up_count=0x00;
				//down
				steering_pwmval=1500-200;//high mean low speed
				TIM_SetCompare1(TIM3,steering_pwmval);
			
				
			}
			else
			{
				if(up_count>=2900)
				{
					//time is up
					//stop
			
					steering_pwmval=1500;//high mean low speed
					TIM_SetCompare1(TIM3,steering_pwmval);
					
					
					
					
				}
			}
		}
		else if((string_pb6==1)&&(string_pb7==1))
		{
			//stop
			steering_pwmval=1500;//high mean low speed
			TIM_SetCompare1(TIM3,steering_pwmval);
			
			up_count=0;
			down_count=0;
			up_flag=0;
			down_flag=0;
		}
		else if((string_pb6==0)&&(string_pb7==0))
		{
			//stop
			
			steering_pwmval=1500;//high mean low speed
			TIM_SetCompare1(TIM3,steering_pwmval);
			
			up_count=0;
			down_count=0;
			up_flag=0;
			down_flag=0;
			
		}
		
		
		
		
	}
	
	
}




//��ʱ��2�����������
void TIM2_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
				//LED0=!LED0;
			
			
				scan_key();
			
				stop_time++;
			
				down_count++;
			
				up_count++;
			
				judge_excute_steering();
			
			
				TIM_SetCounter(TIM2, 0);
				TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
			
				TIM_Cmd(TIM2, ENABLE);
			
			
		}
}



void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO����ʱ�ӣ��ҵ�c8t6��������ӳ�䣬����AFIO���ù���ģ��ʱ��
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3������ӳ�� TIM3_CH1->PB4  TIM3_CH2->PB5  ,��ֻ��tim3ch1    
 
   //���ø�����Ϊ�����������,���TIM3 CH1��PWM���岨��	GPIOC.6->ch1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
//	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOC.7->ch2
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIO
	
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
	
	
	
	//��ʼ��TIM3 Channel 1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse=900;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	
//	//��ʼ��TIM3 Channel 2 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
////	TIM_OCInitStructure.TIM_Pulse=900;
//	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
//	
//	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���,д��ccr��ֵ������Ч�����enable����������ʱ���ccrֵ�����£��Ȳ���������Ч

	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
	

}
//��ʱ��3�����������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
				
				TIM_SetCounter(TIM3, 0);
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
			
				TIM_Cmd(TIM3, ENABLE);
			
//				pwm_num++;
//				
//				room_2_pwm_num++;
			 
			
		}
}


//////////////////////////////////
////
/////////////////////////////////////
//void key_scan(void)
//{
//	
//	
//	
//}




