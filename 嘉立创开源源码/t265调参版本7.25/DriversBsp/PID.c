#include "PID.h"
#include "ANO_LX.h"
#include "Info.h"
#include <math.h>
#include "T265_Sensor.h"
/*
1.做差求出目标量的误差值（目标值减期望值，注意正负号）
2.将差值投入PID_Calc函数，并将改函数放入固定频率执行的线程中，以高刷新率计算PID输出值
3.将PID的输出out作为控制量，赋值给实时控制帧
*/
/*******************************************************
	函数名：PID_Calc（位置试PID）/PID_Calc_Increment(增量式PID)
	输  入:
	输  出:
	功能说明：变速积分
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

float PID_Calc(PID_Struct_f* pPID,s16 ferror)   //位置式PID
{
	float out;
	
  float derror;//误差微分  
	//微分
	derror = (ferror - pPID->fPreviousError)/pPID->ts;
  //保存微分值
	pPID->fPreviousError =  ferror;
  //微分项
	derror *= pPID->Kd;
	//微分限幅
 	if(derror>pPID->fLimit_Derivat) 	       derror = pPID->fLimit_Derivat;
	else if(derror<-pPID->fLimit_Derivat) 	 derror =-pPID->fLimit_Derivat;

//输出 =  误差  ×  比例   + 误差微分 +        积分    ×   积分衰减系数      +       前馈  ×  目标值       
	out = ferror*pPID->Kp + derror + pPID->fIntegral*pPID->beta_Integral+ pPID->fStab*pPID->Val_obj; // 增加了前馈
	//比例项         					微分
	if(1) //启动积分
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

//积分限幅
	if(pPID->fIntegral<pPID->fLower_Limit_Integral)
	{
		   pPID->fIntegral= pPID->fLower_Limit_Integral ; 
	}
	else if(pPID->fIntegral>pPID->fUpper_Limit_Integral)
	{
		   pPID->fIntegral = pPID->fUpper_Limit_Integral; 
	}

//输出限幅
	if(out>pPID->fUpper_Limit_Output)      out = pPID->fUpper_Limit_Output;
	else if(out<pPID->fLower_Limit_Output) out = pPID->fLower_Limit_Output;

	return out;
}

float PID_Calc_Increment(PID_Struct_f* pPID,float ferror)  //增量式PID
{
	float out;
	float Last_ferror;//上次计算偏差误差
  float derror;//误差微分  
	//微分
	derror = (ferror - pPID->fPreviousError)/pPID->ts;
  //保存微分值
	pPID->fPreviousError =  ferror;
  //微分项
	derror *= pPID->Kd;
	//微分限幅
 	if(derror>pPID->fLimit_Derivat) 	       derror = pPID->fLimit_Derivat;
	else if(derror<-pPID->fLimit_Derivat) 	 derror =-pPID->fLimit_Derivat;

//输出 =   两次误差的偏差值 ×     比例   + 误差微分  +        积分    ×   积分衰减系数
	out += (ferror - Last_ferror)*pPID->Kp    + derror     + pPID->fIntegral*pPID->beta_Integral; 	
	//比例项         					微分
	Last_ferror = ferror; 
	if(1) //启动积分
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

//积分限幅
	if(pPID->fIntegral<pPID->fLower_Limit_Integral)
	{
		   pPID->fIntegral= pPID->fLower_Limit_Integral ; 
	}
	else if(pPID->fIntegral>pPID->fUpper_Limit_Integral)
	{
		   pPID->fIntegral = pPID->fUpper_Limit_Integral; 
	}

//输出限幅
	if(out>pPID->fUpper_Limit_Output)      out = pPID->fUpper_Limit_Output;
	else if(out<pPID->fLower_Limit_Output) out = pPID->fLower_Limit_Output;

	return out;
}

void PID_Init(void)
{
//P控制参数初始化   I控制参数初始化     D控制参数初始化 
  X_PID.Kp=0.55;     X_PID.Ki=0.0;     X_PID.Kd=0.05;
  Y_PID.Kp=0.55;     Y_PID.Ki=0.0;     Y_PID.Kd=0.05;
	X_K_PID.Kp=0.15;     X_K_PID.Ki=0.0;     X_K_PID.Kd=0.05;
  Y_K_PID.Kp=0.15;     X_K_PID.Ki=0.0;     X_K_PID.Kd=0.05;
  Z_PID.Kp=0.45;     Z_PID.Ki=0;     		Z_PID.Kd=0.1;
	Rol_PID.Kp=1.2;      Rol_PID.Ki=0.001;        Rol_PID.Kd=0;
	Pit_PID.Kp=1.2;      Pit_PID.Ki=0.001;        Pit_PID.Kd=0;
	Yaw_PID.Kp=5;      Yaw_PID.Ki=0.0;        Yaw_PID.Kd=0.8;
//误差死区
  X_PID.ferror_death=0.01;   Y_PID.ferror_death=0.01;   Z_PID.ferror_death=0.01; Yaw_PID.ferror_death=0.01;
//微分限制  积分池
  X_PID.fLimit_Derivat=1.5;  Y_PID.fLimit_Derivat=1.5;  Z_PID.fLimit_Derivat=1;  Yaw_PID.fLimit_Derivat=1.5;
//积分衰减系数
  X_PID.beta_Integral=1;     Y_PID.beta_Integral=1;     Z_PID.beta_Integral=1;   Yaw_PID.beta_Integral=1;
//采样周期
  X_PID.ts=0.01;  Y_PID.ts=0.01;  Z_PID.ts=0.01;  Yaw_PID.ts=0.01;
//积分幅值
  X_PID.fLower_Limit_Integral=-1;    X_PID.fUpper_Limit_Integral=1;
  Y_PID.fLower_Limit_Integral=-1;    Y_PID.fUpper_Limit_Integral=1;
  Z_PID.fLower_Limit_Integral=-1;  Z_PID.fUpper_Limit_Integral=1;
	Yaw_PID.fLower_Limit_Integral=-1;  Yaw_PID.fUpper_Limit_Integral=1;
 //输出幅值
  X_PID.fLower_Limit_Output=-45;    X_PID.fUpper_Limit_Output=45;
  Y_PID.fLower_Limit_Output=-45;    Y_PID.fUpper_Limit_Output=45;
  Z_PID.fLower_Limit_Output=-40;     Z_PID.fUpper_Limit_Output=40;
	Yaw_PID.fLower_Limit_Output=-60;     Yaw_PID.fUpper_Limit_Output=60;
}

/*******************************************************
	函数名：OutLoop_Control_height
	输  入:
	输  出:
	功能说明：高度环PID
 
********************************************************/
void OutLoop_Control_height(void)
{
	if(User.Flight.keep_height==1)
	{
		User.Flight.offset_B[2]=User.Flight.target_alt_cm-User.Flight.alt_cm; //期望高度和当前高度差
		
		User.Flight.des_V[2]=PID_Calc(&Z_PID,User.Flight.offset_B[2]);	//获取飞机机体Z方向的PID速度(厘米/秒)
		rt_tar.st_data.vel_z=User.Flight.des_V[2];
	}

}

/*******************************************************
	函数名：OutLoop_Control
	输  入:
	输  出:
	功能说明：外环位置-内环速度控制

********************************************************/

/*******************************************************
	函数名：OutLoop_Control_yaw
	输  入:
	输  出:
	功能说明：外环位置-内环角速度控制
 
********************************************************/
void OutLoop_Control_yaw()
{
		if(User.Flight.keep_yaw==1)
	{
		User.Flight.offset_B[3]=(User.Flight.YAW_Start - User.Flight.YAW +180) %360 -180;	//保持YAW处于开始状态，使用实时控制帧控制坐标
		User.Flight.des_V[3]=PID_Calc(&Yaw_PID,User.Flight.offset_B[3]);	//获取飞机机体YAW的PID角速度(°/s)	
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



