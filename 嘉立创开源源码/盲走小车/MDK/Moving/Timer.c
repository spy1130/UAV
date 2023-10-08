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
1,ʱ��ʹ��
2,����Ԥ��Ƶ���Զ���װֵ���ظ�����ֵ
3,����жϱ�־λ��������Ƚ�һ���жϣ�
4,ʹ��TIM�жϣ�ѡ���ж�Դ
5,�����ж����ȼ�
6,ʹ��TIMx����

arr���Զ���װֵ
psc��ʱ��Ԥ��Ƶ��
*/

extern u8 dat;
static u32 dly_cnt_100ms=0;
void Timer1_Init(u16 arr,u16 psc)  

{  

  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  NVIC_InitTypeDef NVIC_InitStructure;  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��  
  
  TIM_TimeBaseStructure.TIM_Period = arr; //�����Զ���װ�ؼĴ�������ֵ  
  TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);//����Ԥ��Ƶֵ 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//�ظ���������  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //������ʼ��  

  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//���жϱ�־λ  

  TIM_ITConfig(      //ʹ�ܻ���ʧ��ָ����TIM�ж�  
    TIM1,            //TIM1  
    TIM_IT_Update  | //TIM �����ж�Դ  
    TIM_IT_Trigger,  //TIM �����ж�Դ   
    ENABLE           //ʹ��  
    );  
    
  //�������ȼ�  

  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�0��  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //�����ȼ�0��  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);   

  TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx����  
}  


void TIM1_UP_IRQHandler(void)   //TIM1�ж�
{	

	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //���ָ����TIM1�жϷ������:TIM1 �ж�Դ 
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
		
		
		
		
	    TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM1 �ж�Դ 

	   /* ����д�ж� */
	
	}
}




