#include "Timer.h"
#include "LX_DT.h"
#include "moto.h"
#include "MATH.h"


extern u8 MissionQuality;
extern u8 MissionFlag;
extern S16_Byte FirePosition;
extern s16 angle;
extern 	u16 counttime;

/*
1,时钟使能
2,配置预分频、自动重装值和重复计数值
3,清除中断标志位（否则会先进一次中断）
4,使能TIM中断，选择中断源
5,设置中断优先级
6,使能TIMx外设

arr：自动重装值
psc：时钟预分频数
*/

extern u8 dat;
static u32 dly_cnt_100ms=0;
void Timer1_Init(u16 arr,u16 psc)  

{  

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  NVIC_InitTypeDef NVIC_InitStructure;  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能  
  
  TIM_TimeBaseStructure.TIM_Period = arr; //设置自动重装载寄存器周期值  
  TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);//设置预分频值 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数设置  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //参数初始化  

  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位  

  TIM_ITConfig(      //使能或者失能指定的TIM中断  
    TIM1,            //TIM1  
    TIM_IT_Update  | //TIM 更新中断源  
    TIM_IT_Trigger,  //TIM 触发中断源   
    ENABLE           //使能  
    );  
    
  //设置优先级  

  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级0级  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //从优先级0级  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);   

  TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设  
}  


void TIM1_UP_IRQHandler(void)   //TIM1中断
{	

	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM1中断发生与否:TIM1 中断源 
	{
		dly_cnt_100ms+=100;
		switch(900)
		{
			case 0:
				StraightMove(0,0);
				if(FirePosition.Data[0] != 0 && FirePosition.Data[1] != 0)
				{
					angle = atan2((double)(FirePosition.Data[1]-135),(double)(FirePosition.Data[0]-25))/3.14159265*180.0;
					MissionFlag ++;
				}
				break;
			case 1:
				MissionQuality += TurnAround_Plus(angle);
				if(MissionQuality >= 3)
					MissionFlag ++;
				break;
			case 2:
				StraightMove(0,0);
			if(dly_cnt_100ms == 3000){
					MissionFlag ++;
					dly_cnt_100ms=0;
			}
			
				break;
			case 3:
				StraightMove(1000,0);
				counttime ++;
				if(dly_cnt_100ms == 5000){
					
					dly_cnt_100ms=0;
					MissionFlag =4;
				}
				//StraightMove(1000,200);
				break;
	
			case 4:
				StraightMove(0,100);
				
//					MissionFlag ++;
				break;
			case 200:
				
				if(dly_cnt_100ms == 800){
					StraightMove(0,0);
					dly_cnt_100ms=0;					
				}
				else{
					counttime ++;
				}
				
				
				break;
			case 250:
				
				StraightMove(-1000,0);
					dly_cnt_100ms=0;
				counttime --;
			
				if(counttime <= 0){
					counttime=0;
					MissionFlag ++;
				}
			
				break;
			case 251:
				StraightMove(0,0);

					angle=0;
					MissionFlag ++;
		//		}
				break;
			case 252:
				MissionQuality += TurnAround_Plus(angle);
				if(MissionQuality >= 3)
					MissionFlag ++;
				break;
			break;
			default:
				break;
		}
		
		
		
		
	    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM1 中断源 

	   /* 这里写中断 */
	
	}
}




