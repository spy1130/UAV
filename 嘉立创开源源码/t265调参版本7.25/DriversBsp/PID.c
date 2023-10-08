#include "PID.h"
#include "ANO_LX.h"
#include "Info.h"
#include <math.h>
#include "T265_Sensor.h"
/*
1.�������Ŀ���������ֵ��Ŀ��ֵ������ֵ��ע�������ţ�
2.����ֵͶ��PID_Calc�����������ĺ�������̶�Ƶ��ִ�е��߳��У��Ը�ˢ���ʼ���PID���ֵ
3.��PID�����out��Ϊ����������ֵ��ʵʱ����֡
*/
/*******************************************************
	��������PID_Calc��λ����PID��/PID_Calc_Increment(����ʽPID)
	��  ��:
	��  ��:
	����˵�������ٻ���
********************************************************/
PID_Struct_f X_PID;
PID_Struct_f X_K_PID;
PID_Struct_f Y_PID;
PID_Struct_f Y_K_PID;
PID_Struct_f Z_PID;

PID_Struct_f Rol_PID;

PID_Struct_f Pit_PID;

PID_Struct_f Yaw_PID;



u8 open_keeping_button = 0;

float PID_Calc(PID_Struct_f* pPID,s16 ferror)   //λ��ʽPID
{
	float out;
	
  float derror;//���΢��  
	//΢��
	derror = (ferror - pPID->fPreviousError)/pPID->ts;
  //����΢��ֵ
	pPID->fPreviousError =  ferror;
  //΢����
	derror *= pPID->Kd;
	//΢���޷�
 	if(derror>pPID->fLimit_Derivat) 	       derror = pPID->fLimit_Derivat;
	else if(derror<-pPID->fLimit_Derivat) 	 derror =-pPID->fLimit_Derivat;

//��� =  ���  ��  ����   + ���΢�� +        ����    ��   ����˥��ϵ��      +       ǰ��  ��  Ŀ��ֵ       
	out = ferror*pPID->Kp + derror + pPID->fIntegral*pPID->beta_Integral+ pPID->fStab*pPID->Val_obj; // ������ǰ��
	//������         					΢��
	if(1) //��������
	{
		if((ferror>0)&&(out<pPID->fUpper_Limit_Output))
		{
			pPID->fIntegral += (ferror *pPID->Ki * pPID->ts); 
		}
		else if((ferror<0)&&(out>pPID->fLower_Limit_Output))
    {
      pPID->fIntegral += (ferror *pPID->Ki*pPID->ts); 
    }
	}

//�����޷�
	if(pPID->fIntegral<pPID->fLower_Limit_Integral)
	{
		   pPID->fIntegral= pPID->fLower_Limit_Integral ; 
	}
	else if(pPID->fIntegral>pPID->fUpper_Limit_Integral)
	{
		   pPID->fIntegral = pPID->fUpper_Limit_Integral; 
	}

//����޷�
	if(out>pPID->fUpper_Limit_Output)      out = pPID->fUpper_Limit_Output;
	else if(out<pPID->fLower_Limit_Output) out = pPID->fLower_Limit_Output;

	return out;
}

float PID_Calc_Increment(PID_Struct_f* pPID,float ferror)  //����ʽPID
{
	float out;
	float Last_ferror;//�ϴμ���ƫ�����
  float derror;//���΢��  
	//΢��
	derror = (ferror - pPID->fPreviousError)/pPID->ts;
  //����΢��ֵ
	pPID->fPreviousError =  ferror;
  //΢����
	derror *= pPID->Kd;
	//΢���޷�
 	if(derror>pPID->fLimit_Derivat) 	       derror = pPID->fLimit_Derivat;
	else if(derror<-pPID->fLimit_Derivat) 	 derror =-pPID->fLimit_Derivat;

//��� =   ��������ƫ��ֵ ��     ����   + ���΢��  +        ����    ��   ����˥��ϵ��
	out += (ferror - Last_ferror)*pPID->Kp    + derror     + pPID->fIntegral*pPID->beta_Integral; 	
	//������         					΢��
	Last_ferror = ferror; 
	if(1) //��������
	{
		if((ferror>0)&&(out<pPID->fUpper_Limit_Output))
		{
			pPID->fIntegral += (ferror *pPID->Ki * pPID->ts); 
		}
		else if((ferror<0)&&(out>pPID->fLower_Limit_Output))
    {
      pPID->fIntegral += (ferror *pPID->Ki*pPID->ts); 
    }
	}

//�����޷�
	if(pPID->fIntegral<pPID->fLower_Limit_Integral)
	{
		   pPID->fIntegral= pPID->fLower_Limit_Integral ; 
	}
	else if(pPID->fIntegral>pPID->fUpper_Limit_Integral)
	{
		   pPID->fIntegral = pPID->fUpper_Limit_Integral; 
	}

//����޷�
	if(out>pPID->fUpper_Limit_Output)      out = pPID->fUpper_Limit_Output;
	else if(out<pPID->fLower_Limit_Output) out = pPID->fLower_Limit_Output;

	return out;
}

void PID_Init(void)
{
//P���Ʋ�����ʼ��   I���Ʋ�����ʼ��     D���Ʋ�����ʼ�� 
  X_PID.Kp=0.55;     X_PID.Ki=0.0;     X_PID.Kd=0.05;
  Y_PID.Kp=0.55;     Y_PID.Ki=0.0;     Y_PID.Kd=0.05;
	X_K_PID.Kp=0.15;     X_K_PID.Ki=0.0;     X_K_PID.Kd=0.05;
  Y_K_PID.Kp=0.15;     X_K_PID.Ki=0.0;     X_K_PID.Kd=0.05;
  Z_PID.Kp=0.45;     Z_PID.Ki=0;     		Z_PID.Kd=0.1;
	Rol_PID.Kp=1.2;      Rol_PID.Ki=0.001;        Rol_PID.Kd=0;
	Pit_PID.Kp=1.2;      Pit_PID.Ki=0.001;        Pit_PID.Kd=0;
	Yaw_PID.Kp=5;      Yaw_PID.Ki=0.0;        Yaw_PID.Kd=0.8;
//�������
  X_PID.ferror_death=0.01;   Y_PID.ferror_death=0.01;   Z_PID.ferror_death=0.01; Yaw_PID.ferror_death=0.01;
//΢������  ���ֳ�
  X_PID.fLimit_Derivat=1.5;  Y_PID.fLimit_Derivat=1.5;  Z_PID.fLimit_Derivat=1;  Yaw_PID.fLimit_Derivat=1.5;
//����˥��ϵ��
  X_PID.beta_Integral=1;     Y_PID.beta_Integral=1;     Z_PID.beta_Integral=1;   Yaw_PID.beta_Integral=1;
//��������
  X_PID.ts=0.01;  Y_PID.ts=0.01;  Z_PID.ts=0.01;  Yaw_PID.ts=0.01;
//���ַ�ֵ
  X_PID.fLower_Limit_Integral=-1;    X_PID.fUpper_Limit_Integral=1;
  Y_PID.fLower_Limit_Integral=-1;    Y_PID.fUpper_Limit_Integral=1;
  Z_PID.fLower_Limit_Integral=-1;  Z_PID.fUpper_Limit_Integral=1;
	Yaw_PID.fLower_Limit_Integral=-1;  Yaw_PID.fUpper_Limit_Integral=1;
 //�����ֵ
  X_PID.fLower_Limit_Output=-45;    X_PID.fUpper_Limit_Output=45;
  Y_PID.fLower_Limit_Output=-45;    Y_PID.fUpper_Limit_Output=45;
  Z_PID.fLower_Limit_Output=-40;     Z_PID.fUpper_Limit_Output=40;
	Yaw_PID.fLower_Limit_Output=-60;     Yaw_PID.fUpper_Limit_Output=60;
}

/*******************************************************
	��������OutLoop_Control_height
	��  ��:
	��  ��:
	����˵�����߶Ȼ�PID
 
********************************************************/
void OutLoop_Control_height(void)
{
	if(User.Flight.keep_height==1)
	{
		User.Flight.offset_B[2]=User.Flight.target_alt_cm-User.Flight.alt_cm; //�����߶Ⱥ͵�ǰ�߶Ȳ�
		
		User.Flight.des_V[2]=PID_Calc(&Z_PID,User.Flight.offset_B[2]);	//��ȡ�ɻ�����Z�����PID�ٶ�(����/��)
		rt_tar.st_data.vel_z=User.Flight.des_V[2];
	}

}

/*******************************************************
	��������OutLoop_Control
	��  ��:
	��  ��:
	����˵�����⻷λ��-�ڻ��ٶȿ���

********************************************************/

/*******************************************************
	��������OutLoop_Control_yaw
	��  ��:
	��  ��:
	����˵�����⻷λ��-�ڻ����ٶȿ���
 
********************************************************/
void OutLoop_Control_yaw()
{
		if(User.Flight.keep_yaw==1)
	{
		User.Flight.offset_B[3]=(User.Flight.YAW_Start - User.Flight.YAW +180) %360 -180;	//����YAW���ڿ�ʼ״̬��ʹ��ʵʱ����֡��������
		User.Flight.des_V[3]=PID_Calc(&Yaw_PID,User.Flight.offset_B[3]);	//��ȡ�ɻ�����YAW��PID���ٶ�(��/s)	
		rt_tar.st_data.yaw_dps = User.Flight.des_V[3];
		
	}
		else if(User.Flight.keep_yaw==2)
	{
		rt_tar.st_data.yaw_dps = -30;
	}
		else
	{
		rt_tar.st_data.yaw_dps=0;	
	}
}


s16 YAW_Calc(s16 Yaw_In,s16 Yaw_Var)
{
	s16 Yaw_Out;
	Yaw_Out = Yaw_In + Yaw_Var;
	{
	if(Yaw_Out > 180) 
		Yaw_Out -= 360;
	if(Yaw_Out < -180)
		Yaw_Out += 360;
  }
	return Yaw_Out;
}



