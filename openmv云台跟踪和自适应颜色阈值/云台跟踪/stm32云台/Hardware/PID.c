#include "stm32f10x.h"                  // Device header

float err_x = 0.0;											//x误差
float err_y = 0.0;											//y误差
float integral_x = 0.0;									//x积分
float integral_y = 0.0;									//y积分
float err_last_x = 0.0;									//x上一误差值
float err_last_y = 0.0;									//y上一误差值
float actual_value = 0.0;								//驱动值


/*************************************
*函  数  名	：PID_x()
*函数功能	：将X轴的各个参数进行PID运算
*输	入	：目标值，实际值 ,kp_x ,ki_x ,kd_x
*输	出	：PID运算后的驱动值
*************************************/
float PID_x(float target_value, float temp_val, float kp_x, float ki_x, float kd_x)
{
	/*位置式PID*/
	/*误差 = 目标值 - 输入的实际值*/
	err_x = target_value - temp_val;
	
	/*误差累计*/
	integral_x += err_x;
	
	
	/*积分限幅*/
	if(integral_x > 3000)
		integral_x = 3000;
	else if(integral_x < -3000)
		integral_x = -3000;
	
	/*PID算法实现*/
	actual_value = kp_x*err_x + ki_x*integral_x + kd_x*(err_x - err_last_x);
	
	/*记录上一误差值*/
	err_last_x = err_x;
	
	
	/*返回当前实际值*/
	return actual_value;
}

/*************************************
*函  数  名	：PID_y()
*函数功能	：将Y轴的各个参数进行PID运算
*输	入	：目标值，实际值 ,kp_y ,ki_y ,kd_y
*输	出	：PID运算后的驱动值
*************************************/
float PID_y(float target_value, float temp_val, float kp_y, float ki_y, float kd_y)
{
	/*位置式PID*/
	/*误差 = 目标值 - 输入的实际值*/
	err_y = target_value - temp_val;
	
	/*误差累计*/
	integral_y += err_y;
	
	
	/*积分限幅*/
	if(integral_y > 3000)
		integral_y = 3000;
	else if(integral_y < -3000)
		integral_y = -3000;
	
	/*PID算法实现*/
	actual_value = kp_y*err_y + ki_y*integral_y + kd_y*(err_y - err_last_y);
	
	/*记录上一误差值*/
	err_last_y = err_y;
	
	
	/*返回当前实际值*/
	return actual_value;
}

