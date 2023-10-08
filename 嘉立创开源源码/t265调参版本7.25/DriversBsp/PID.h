#include "SysConfig.h"
#include <stdlib.h>
#include <Math.h>

typedef struct 
{
 /***************************************************************************************/
  float Val_obj;   // 目标值
  float Val_cur;   // 

  float ts;
  float Kp;		//比例系数因子
  float Ki;  	//积分系数因子  
  float Kd;		//微分系数因子
  float fLower_Limit_Output;     //Lower Limit for Output limitation			总输出下限
  float fUpper_Limit_Output;     //Lower Limit for Output limitation			总输出上限
  float fLower_Limit_Integral;   //Lower Limit for Integral term limitation	积分项下限
  float fUpper_Limit_Integral;   //Lower Limit for Integral term limitation	积分项上限
  float fLimit_Derivat; // 微分项极限
  float fIntegral;			//积分累积和
  float fPreviousError;	//上次误差
  float fStab; // 前馈系数
  float Kd_d; // 二次微分系数
  float fLimit_DDerivate; //二次微分极限
  float ferror_death; // 死区
	
  float beta_Integral;// 积分衰减系数
  float ARange_error_Integral;// 积分误差范围A 不变积分区误差
  float BRange_error_Integral;// 积分误差范围B 可变积分区误差长

} PID_Struct_f;


u8 position_detec(void);

float PID_Calc(PID_Struct_f* pPID,s16 ferror);
float PID_Calc_Increment(PID_Struct_f* pPID,float ferror);
void PID_Init(void);
void OutLoop_Control_height(void); //位置Z
void OutLoop_Control_yaw(void); //位置YAW
void OutLoop_Control_T265(void);

s16 YAW_Calc(s16 Yaw_In,s16 Yaw_Var); //YAW转动量运算


