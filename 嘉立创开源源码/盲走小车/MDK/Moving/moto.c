#include "moto.h"
#include "PWM.h"
#include "delay.h"


//extern float Velcity_Kp,  Velcity_Ki,  Velcity_Kd; //����ٶ�PID����
//extern float Position_KP,Position_KI,Position_KD,Velocity_KP,Velocity_KI;      //PIDϵ��
extern pid_param_t TurnControl;
int encoder_A1,encoder_A2,encoder_B1,encoder_B2;
extern float fAngle[3];
void InitDirection(void)       //���������ܽ�
{
	GPIO_InitTypeDef LASER_Pin;
//	GPIO_InitTypeDef  GPIO_B;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //ʹ��GPIOB�˿ڵ�ʱ��
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  // �л���SWJ���ԣ��ͷ�PA15��PB4, PB3
//	GPIO_B.GPIO_Mode = GPIO_Mode_Out_PP;    //ģʽ���������
//	GPIO_B.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;          //�ܽźţ�13��
//	GPIO_B.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶȣ�50MHZ
//	GPIO_Init(GPIOB,&GPIO_B);   
	LASER_Pin.GPIO_Mode = GPIO_Mode_Out_PP;    //ģʽ���������
	LASER_Pin.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;          //�ܽźţ�13��
	LASER_Pin.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶȣ�50MHZ
	GPIO_Init(GPIOA,&LASER_Pin);   
//	LASER_Pin.GPIO_Mode = GPIO_Mode_Out_PP;    //ģʽ���������
//	LASER_Pin.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;          //�ܽźţ�13��
//	LASER_Pin.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶȣ�50MHZ
//	GPIO_Init(GPIOC,&LASER_Pin);   
	
	
    GPIO_SetBits(GPIOA,GPIO_Pin_1);         //IO��������ߵ�ƽ����ʼ��״̬������
	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_11);         //IO��������ߵ�ƽ����ʼ��״̬������
	GPIO_SetBits(GPIOA,GPIO_Pin_15);         //IO��������ߵ�ƽ����ʼ��״̬������
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_12);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}                                   
/***************************************************************************
�������ܣ�����ıջ�����
��ڲ���������ı�����ֵ
����ֵ  �������PWM
***************************************************************************/
//int Velocity_A(int TargetVelocity, int CurrentVelocity)
//{
//		int Bias;  //������ر���
//		static int ControlVelocity, Last_bias; //��̬�������������ý�������ֵ��Ȼ����
//		
//		Bias=TargetVelocity-CurrentVelocity; //���ٶ�ƫ��
//		
//		ControlVelocity+=Velcity_Kp*(Bias-Last_bias)+Velcity_Ki*Bias;  //����ʽPI������
//                                                                   //Velcity_Kp*(Bias-Last_bias) ����Ϊ���Ƽ��ٶ�
//	                                                                 //Velcity_Ki*Bias             �ٶȿ���ֵ��Bias���ϻ��ֵõ� ƫ��Խ����ٶ�Խ��
//		Last_bias=Bias;	
//		return ControlVelocity; //�����ٶȿ���ֵ 
//	
//}
//int Velocity_B(int TargetVelocity, int CurrentVelocity)
//{  
//    int Bias;  //������ر���
//		static int ControlVelocity, Last_bias; //��̬�������������ý�������ֵ��Ȼ����
//		
//		Bias=TargetVelocity-CurrentVelocity; //���ٶ�ƫ��
//		
//		ControlVelocity+=Velcity_Kp*(Bias-Last_bias)+Velcity_Ki*Bias;  //����ʽPI������
//                                                                   //Velcity_Kp*(Bias-Last_bias) ����Ϊ���Ƽ��ٶ�
//	                                                             //Velcity_Ki*Bias             �ٶȿ���ֵ��Bias���ϻ��ֵõ� ƫ��Խ����ٶ�Խ��
//		Last_bias=Bias;	
//		return ControlVelocity; //�����ٶȿ���ֵ
//}

//void MotorContorl()
//{
//	encoder_B1 = Read_Encoder_TIM4();
//	encoder_B2 = Read_Encoder_TIM2();
//	TIM_SetCompare1(TIM3,Velocity_A(500,encoder_B2));//100~1999
//	TIM_SetCompare2(TIM3,Velocity_A(500,encoder_B1));
//	TIM_SetCompare3(TIM3,Velocity_A(500,encoder_B1));
//	TIM_SetCompare4(TIM3,Velocity_A(500,encoder_B2));
//}

void StraightMove(int Velocity,uint16_t delaytime)
{
	SetMotor(1,Velocity);
	SetMotor(2,Velocity);
	SetMotor(3,Velocity);
	SetMotor(4,Velocity);
	for(int i = 0;i < delaytime;i ++)
		delay_ms(10);
}

void SetMotor(u8 motor,int Velocity)
{
	switch(motor)
	{
		case 1:
			if(Velocity >= 0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_1);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_ResetBits(GPIOA,GPIO_Pin_8);

			TIM_SetCompare1(TIM3,Velocity);//100~1999
		}
			else 
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_SetBits(GPIOA,GPIO_Pin_8);
		
			TIM_SetCompare1(TIM3,-Velocity);//100~1999
		}
			break;
		case 2:
			if(Velocity >= 0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_4);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			
			TIM_SetCompare2(TIM3,Velocity);
		}
			else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			
			TIM_SetCompare2(TIM3,-Velocity);
		}
			break;
		case 3:
			if(Velocity >= 0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_11);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_ResetBits(GPIOA,GPIO_Pin_12);
			
			TIM_SetCompare3(TIM3,Velocity);
		}
			else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_SetBits(GPIOA,GPIO_Pin_12);
			
			TIM_SetCompare3(TIM3,-Velocity);
		}
			break;
		case 4:
			if(Velocity >= 0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_15);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);
			
			TIM_SetCompare4(TIM3,Velocity);
		}
			else
		{
			GPIO_ResetBits(GPIOA,GPIO_Pin_15);         //IO��������ߵ�ƽ����ʼ��״̬������
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
			
			TIM_SetCompare4(TIM3,-Velocity);
		}
			break;
		default:
			break;
	}
}

void TurnAround(int degree)
{
	if(degree > 0)
	{
		SetMotor(1,-1200);
		SetMotor(2,1200);
		SetMotor(3,1200);
		SetMotor(4,-1200);
		delay_ms(750);
	}
	
	else
	{
		SetMotor(1,1200);
		SetMotor(2,-1200);
		SetMotor(3,-1200);
		SetMotor(4,1200);
		delay_ms(850);
	}
	
}

u8 TurnAround_Plus(int degree)
{
	
	int Velocity;
	Velocity = (degree - fAngle[2]) * 14;
	if(Velocity>1400)//�޷�
		Velocity=1400;
	else if(Velocity<-1400)
		Velocity=-1400;
	if(Velocity < 800 && Velocity > -800)
	{
		if(Velocity >= 0) Velocity = 800;
		else if(Velocity < 0) Velocity = -800;
	}

		SetMotor(1,-Velocity);
		SetMotor(2,Velocity);
		SetMotor(3,Velocity);
		SetMotor(4,-Velocity);
		
	if(ABS(degree - fAngle[2]) <= 2)
		return 1;
	else 
		return 0;
}

void Turning_Pid(float error)
{
	float vel = PidLocCtrl(&TurnControl,error) * 100;
	SetMotor(1,-error);
	SetMotor(2,error);
	SetMotor(3,error);
	SetMotor(4,-error);
	
}
