#include "Pid.h"

pid_param_t TurnControl;
/*********************************************************
函数名称：限幅函数
功能介绍：数据限幅
接口定义：
amt:参数
low:最低值
high:最高值
return:限幅后的值
版本：2.0
时间：2021.09.16
*********************************************************/
float constrain_float(float amt, float low, float high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

/*********************************************************
函数名称：pid参数初始化函数
功能介绍：初始化pid参数
接口定义：
pid:需要初始化的pid变量
版本：2.0
时间：2021.09.16
*********************************************************/
void PidInit(pid_param_t * pid)
{
	pid->kp        = 0;
	pid->ki        = 0;
	pid->kd        = 0;
	pid->imax      = 0;
	pid->out_p     = 0;
	pid->out_i     = 0;
	pid->out_d     = 0;
	pid->out       = 0;
	pid->integrator= 0;
	pid->last_error= 0;
	pid->last_derivative   = 0;
	pid->last_t    = 0;
}

float PidLocCtrl(pid_param_t * pid, float error)//P:比例;I:积分,D:微分
{
	//累积误差
	pid->integrator += error;

	//误差限幅
	constrain_float(pid->integrator, -pid->imax, pid->imax);


	pid->out_p = pid->kp * error;
	pid->out_i = pid->ki * pid->integrator;
	pid->out_d = pid->kd * (error - pid->last_error);

	pid->last_error = error;

	pid->out = pid->out_p + pid->out_i + pid->out_d;
	if(pid->out>6000)//限幅
		pid->out=6000;
	if(pid->out<-6000)
		pid->out=-6000;
	return pid->out;
}

/*********************************************************
函数名称：pid增量式控制器输出函数
功能介绍：计算pid增量式控制输出结果
接口定义：
pid:调用的pid变量
error:pid输入误差
return:pid输出结果
版本：2.0
时间：2021.09.16
*********************************************************/
float PidIncCtrl(pid_param_t * pid, float error)//P:比例;I:积分,D:微分
{
	pid->out_p = pid->kp * (error - pid->last_error);
	pid->out_i = pid->ki * error;
	//pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

	//pid->last_derivative = error - pid->last_error;
	pid->last_error = error;

	pid->out += pid->out_p + pid->out_i;// + pid->out_d;
	if(pid->out>5000)//限幅
		pid->out=5000;
	if(pid->out<-3000)
		pid->out=-3000;
	return pid->out;
}
