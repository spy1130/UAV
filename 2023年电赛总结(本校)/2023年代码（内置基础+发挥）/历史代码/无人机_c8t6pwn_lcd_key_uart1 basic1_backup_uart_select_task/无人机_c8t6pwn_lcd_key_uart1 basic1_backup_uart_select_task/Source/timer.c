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







/* TIM2 中断优先级配置函数 */
void NVIC_TIM2Enable(void)
{
	NVIC_InitTypeDef NVIC_initstructure;
	//在此未设置优先级分组， 使用系统默认的分组
	NVIC_initstructure.NVIC_IRQChannel = TIM2_IRQn; //选择 TIM2 中断通道
	NVIC_initstructure.NVIC_IRQChannelCmd = ENABLE; //使能中断通道
	NVIC_initstructure.NVIC_IRQChannelPreemptionPriority = 3; //设定抢占优先级为 0
	NVIC_initstructure.NVIC_IRQChannelSubPriority = 1; //设定响应优先级为 0
	NVIC_Init(&NVIC_initstructure);
} 

/////////////////////////////////
//judge_key_num();
////////////////////////////////
void judge_key_num()              //修正后的矩阵键盘，可实现0-9输入，上下左右切换光标
{
	key_num = 0x11;
	c1 = 0;c2 = 1;c3 = 1;c4 = 1;  //按键第一列为0
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
	c1 = 1;c2 = 0;c3 = 1;c4 = 1;  //按键第二列为0
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
	c1 = 1;c2 = 1;c3 = 0;c4 = 1;  //按键第三列为0
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

	c1 = 1;c2 = 1;c3 = 1;c4 = 0;  //按键第四列为0
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
		case 1:   //防抖动  判断键值
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
				judge_key_num();//判断键值
				if(key_num==0x11)
				{
					key_count=0;
					key_flag=0;
					key_last_value=0;
				}
				else
				{
					key_last_value=key_num;//保存键值
				}
				
				

			}
			break;
		case 2:   //再次确认按键按下
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
		case 3:  //等待按键释放
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
























/* 定时器 2 初始化函数， period-计数周期， Prescaler-预分频值 */
//定时器2负责1#通道计数 
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

   //??TIMER3 配置为计数器
//   TIM_DeInit(TIM4);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM2中断,允许更新中断
	//TIM_ETRClockMode2Config(TIM4, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);//this sentense make tim3 work in mode of etr
	TIM_SetCounter(TIM2, 0);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	
	
	
	TIM_Cmd(TIM2, ENABLE);
}

void judge_excute_steering(void)
{
	if(emergenc_io==0)//优先权最高
	{
		//down//本来是停止，但是急停被按死了，所以需要向下，释放急停
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




//定时器2溢出计数处理
void TIM2_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
				TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
				//LED0=!LED0;
			
			
				scan_key();
			
				stop_time++;
			
				down_count++;
			
				up_count++;
			
				judge_excute_steering();
			
			
				TIM_SetCounter(TIM2, 0);
				TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
			
				TIM_Cmd(TIM2, ENABLE);
			
			
		}
}



void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设时钟，我的c8t6，不用重映射，不打开AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射 TIM3_CH1->PB4  TIM3_CH2->PB5  ,我只用tim3ch1    
 
   //设置该引脚为复用输出功能,输出TIM3 CH1的PWM脉冲波形	GPIOC.6->ch1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
//	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOC.7->ch2
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
	
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
	
	
	
	//初始化TIM3 Channel 1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_Pulse=900;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);  //使能TIM3在CCR2上的预装载寄存器
	
//	//初始化TIM3 Channel 2 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
// 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
////	TIM_OCInitStructure.TIM_Pulse=900;
//	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
//	
//	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);  //使能TIM3在CCR2上的预装载寄存器,写入ccr的值立刻生效，如果enable，则发生更新时间后，ccr值被更新，既不能立刻生效

	
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
	

}
//定时器3计数溢出处理
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
				TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
				
				TIM_SetCounter(TIM3, 0);
				TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断
			
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




