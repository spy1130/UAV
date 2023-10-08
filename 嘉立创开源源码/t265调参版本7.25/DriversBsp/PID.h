#include "SysConfig.h"
#include <stdlib.h>
#include <Math.h>

typedef struct 
{
 /***************************************************************************************/
  float Val_obj;   // Ŀ��ֵ
  float Val_cur;   // 

  float ts;
  float Kp;		//����ϵ������
  float Ki;  	//����ϵ������  
  float Kd;		//΢��ϵ������
  float fLower_Limit_Output;     //Lower Limit for Output limitation			���������
  float fUpper_Limit_Output;     //Lower Limit for Output limitation			���������
  float fLower_Limit_Integral;   //Lower Limit for Integral term limitation	����������
  float fUpper_Limit_Integral;   //Lower Limit for Integral term limitation	����������
  float fLimit_Derivat; // ΢�����
  float fIntegral;			//�����ۻ���
  float fPreviousError;	//�ϴ����
  float fStab; // ǰ��ϵ��
  float Kd_d; // ����΢��ϵ��
  float fLimit_DDerivate; //����΢�ּ���
  float ferror_death; // ����
	
  float beta_Integral;// ����˥��ϵ��
  float ARange_error_Integral;// ������ΧA ������������
  float BRange_error_Integral;// ������ΧB �ɱ��������

} PID_Struct_f;


u8 position_detec(void);

float PID_Calc(PID_Struct_f* pPID,s16 ferror);
float PID_Calc_Increment(PID_Struct_f* pPID,float ferror);
void PID_Init(void);
void OutLoop_Control_height(void); //λ��Z
void OutLoop_Control_yaw(void); //λ��YAW
void OutLoop_Control_T265(void);

s16 YAW_Calc(s16 Yaw_In,s16 Yaw_Var); //YAWת��������


