#include "stm32f10x.h"                  // Device header

float err_x = 0.0;											//x���
float err_y = 0.0;											//y���
float integral_x = 0.0;									//x����
float integral_y = 0.0;									//y����
float err_last_x = 0.0;									//x��һ���ֵ
float err_last_y = 0.0;									//y��һ���ֵ
float actual_value = 0.0;								//����ֵ


/*************************************
*��  ��  ��	��PID_x()
*��������	����X��ĸ�����������PID����
*��	��	��Ŀ��ֵ��ʵ��ֵ ,kp_x ,ki_x ,kd_x
*��	��	��PID����������ֵ
*************************************/
float PID_x(float target_value, float temp_val, float kp_x, float ki_x, float kd_x)
{
	/*λ��ʽPID*/
	/*��� = Ŀ��ֵ - �����ʵ��ֵ*/
	err_x = target_value - temp_val;
	
	/*����ۼ�*/
	integral_x += err_x;
	
	
	/*�����޷�*/
	if(integral_x > 3000)
		integral_x = 3000;
	else if(integral_x < -3000)
		integral_x = -3000;
	
	/*PID�㷨ʵ��*/
	actual_value = kp_x*err_x + ki_x*integral_x + kd_x*(err_x - err_last_x);
	
	/*��¼��һ���ֵ*/
	err_last_x = err_x;
	
	
	/*���ص�ǰʵ��ֵ*/
	return actual_value;
}

/*************************************
*��  ��  ��	��PID_y()
*��������	����Y��ĸ�����������PID����
*��	��	��Ŀ��ֵ��ʵ��ֵ ,kp_y ,ki_y ,kd_y
*��	��	��PID����������ֵ
*************************************/
float PID_y(float target_value, float temp_val, float kp_y, float ki_y, float kd_y)
{
	/*λ��ʽPID*/
	/*��� = Ŀ��ֵ - �����ʵ��ֵ*/
	err_y = target_value - temp_val;
	
	/*����ۼ�*/
	integral_y += err_y;
	
	
	/*�����޷�*/
	if(integral_y > 3000)
		integral_y = 3000;
	else if(integral_y < -3000)
		integral_y = -3000;
	
	/*PID�㷨ʵ��*/
	actual_value = kp_y*err_y + ki_y*integral_y + kd_y*(err_y - err_last_y);
	
	/*��¼��һ���ֵ*/
	err_last_y = err_y;
	
	
	/*���ص�ǰʵ��ֵ*/
	return actual_value;
}

