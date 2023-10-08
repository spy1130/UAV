#include "Pid.h"

pid_param_t TurnControl;
/*********************************************************
�������ƣ��޷�����
���ܽ��ܣ������޷�
�ӿڶ��壺
amt:����
low:���ֵ
high:���ֵ
return:�޷����ֵ
�汾��2.0
ʱ�䣺2021.09.16
*********************************************************/
float constrain_float(float amt, float low, float high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

/*********************************************************
�������ƣ�pid������ʼ������
���ܽ��ܣ���ʼ��pid����
�ӿڶ��壺
pid:��Ҫ��ʼ����pid����
�汾��2.0
ʱ�䣺2021.09.16
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

float PidLocCtrl(pid_param_t * pid, float error)//P:����;I:����,D:΢��
{
	//�ۻ����
	pid->integrator += error;

	//����޷�
	constrain_float(pid->integrator, -pid->imax, pid->imax);


	pid->out_p = pid->kp * error;
	pid->out_i = pid->ki * pid->integrator;
	pid->out_d = pid->kd * (error - pid->last_error);

	pid->last_error = error;

	pid->out = pid->out_p + pid->out_i + pid->out_d;
	if(pid->out>6000)//�޷�
		pid->out=6000;
	if(pid->out<-6000)
		pid->out=-6000;
	return pid->out;
}

/*********************************************************
�������ƣ�pid����ʽ�������������
���ܽ��ܣ�����pid����ʽ����������
�ӿڶ��壺
pid:���õ�pid����
error:pid�������
return:pid������
�汾��2.0
ʱ�䣺2021.09.16
*********************************************************/
float PidIncCtrl(pid_param_t * pid, float error)//P:����;I:����,D:΢��
{
	pid->out_p = pid->kp * (error - pid->last_error);
	pid->out_i = pid->ki * error;
	//pid->out_d = pid->kd * ((error - pid->last_error) - pid->last_derivative);

	//pid->last_derivative = error - pid->last_error;
	pid->last_error = error;

	pid->out += pid->out_p + pid->out_i;// + pid->out_d;
	if(pid->out>5000)//�޷�
		pid->out=5000;
	if(pid->out<-3000)
		pid->out=-3000;
	return pid->out;
}
