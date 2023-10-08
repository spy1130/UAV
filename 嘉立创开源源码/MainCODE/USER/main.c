#include "delay.h"
#include "usart.h"
#include "stm32f10x.h"
#include "Oled.h"
#include "usart.h"
#include "pwm.h"
#include "Keyboard.h"
#include "Timer.h"
#include "LX_DT.h"


void LaserInit(void)       //���� LED�ܽ�
{
	GPIO_InitTypeDef LASER_Pin;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	LASER_Pin.GPIO_Mode = GPIO_Mode_Out_PP;    //ģʽ���������
	LASER_Pin.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;          //�ܽźţ�13��
	LASER_Pin.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶȣ�50MHZ
	GPIO_Init(GPIOA,&LASER_Pin);   
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    GPIO_ResetBits(GPIOA,GPIO_Pin_0);         //IO��������ߵ�ƽ����ʼ��״̬������
}                                         
extern	u8  LEDFlag;
extern	u8  LaserFlag;
extern	u8  PagFlag;

int main(void) 
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();
	//OLED_Init();
	uart1_init(115200);
	//uart2_init(115200);
	TIM4_PWM_Init(1999,719);
	//Matrix_ssKey_Pin_Init();
	Timer1_Init(499,7199);
	LaserInit();
	TIM_SetCompare1(TIM4,1745);
	//u8 keyval;
	u8 once_flag=1;
	while(1)
	{
		
//		OLED_ShowChinese(0,0,0,16,1);//��
//		OLED_ShowChinese(16,0,1,16,1);//��
//		OLED_ShowChinese(32,0,2,16,1);//��
//		OLED_ShowChar(48,0,':',16,1);//oled��ʾ�ַ�
//		OLED_ShowNum(64,0,444,2,16);//oled��ʾ����
		
		//keyval = Matrix_Key_Scan();
		//KeyBoardSend(keyval);
		/*
		OLED_ShowChar(0,0,'N',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(6,0,'U',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(12,0,'M',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(18,0,':',12,1);//oled��ʾ�ַ�
		OLED_ShowNum(24,0,keyval,2,12);//oled��ʾ��
		
		OLED_ShowChar(0,15,'L',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(6,15,'A',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(12,15,'S',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(18,15,'E',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(24,15,'R',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(30,15,':',12,1);//oled��ʾ�ַ�
		OLED_ShowNum(36,15,LaserFlag,2,12);//oled��ʾ��
		
		OLED_ShowChar(0,30,'S',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(6,30,'O',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(12,30,'U',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(18,30,'N',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(24,30,'D',12,1);//oled��ʾ�ַ�
		OLED_ShowChar(30,30,':',12,1);//oled��ʾ�ַ�
		OLED_ShowNum(36,30,PagFlag,2,12);//oled��ʾ��
		
		
//		OLED_ShowChinese(0,16,3,16,1);//P
//		OLED_ShowChinese(16,16,4,16,1);//H
//		OLED_ShowChinese(32,16,5,16,1);//ֵ
//		OLED_ShowChar(48,16,':',16,1);//oled��ʾ�ַ�
//		OLED_ShowNum(64,16,666,2,16);//oled��ʾ��?
// 

		OLED_Refresh_Gram();
			
		*/
	//	GPIO_SetBits(GPIOA,GPIO_Pin_1);
		if(LEDFlag==1){
			GPIO_SetBits(GPIOA,GPIO_Pin_1);
		}
		else{
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		}
			GPIO_SetBits(GPIOA,GPIO_Pin_0);

	if(PagFlag == 1){


		//д���ת������ըҩ��
		TIM_SetCompare1(TIM4,1870);
		DataSend();
		//----------------------------------------------------------------------------------------------------
		
	}
	
//			
		
		
		//printf("%d",dat);
		
//		TIM_SetCompare1(TIM4,ServoAngle.Data[0] + 1932);	//1845Ϊ��  ��90�㣺1755  ˳90�㣺1935 �Ϸ����  ������ǰˮƽ��1820  ��ֱ��1888  ��ˮƽ��1999
//		TIM_SetCompare2(TIM4,ServoAngle.Data[1] + 1875);	//1875Ϊ��	��ֱ ��1825  ���� ��1925 �·����  ������˳90�㣺1800   ��ֵ��1865  ��90�㣺1935
		
		
	}
} 




	
