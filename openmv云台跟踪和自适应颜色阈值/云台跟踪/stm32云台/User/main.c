#include "stm32f10x.h"                  				// Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"
#include "PID.h"
#include "PWM.h"

uint8_t KeyNum;
float Angle_x = 0.0, Angle_y = 0.0;
uint8_t x,y;																		//当前坐标

float sp_x, sp_y;																//xy舵机的驱动值

float target_x = 120.0;													//位置目标值
float target_y = 120.0;

float servo_x = 1500.0;													//舵机目标值
float servo_y = 1000.0;

float kp_x = 1.35,  ki_x = 0.34,  kd_x = 0.25;	//PID参数
float kp_y = 1.35,  ki_y = 0.34,  kd_y = 0.25;

int main(void)
{
	float sx,sy;
	
	HSE_sysclock_config();
	OLED_Init();
	Key_Init();
	Serial_Init();
	PWM_Init();
	
	PWM_SetCompare_x(servo_x);
	PWM_SetCompare_y(servo_y);
	
	//OLED_ShowString(1, 1, "Angle:");
	
	while (1)
	{
		/*串口获取x轴与y轴坐标*/
		x = Get_x();
		y = Get_y();
		
		/*OLED显示当前xy轴坐标*/
		OLED_ShowNum(1, 1,x,4);
		OLED_ShowNum(2, 1,y,4);
		OLED_ShowNum(1, 7,Serial_flag(),1);
		if(Serial_flag() == 1)
		{
			/*将当前的xy轴坐标带入PID中*/
			sp_x = PID_x(target_x, x, kp_x, ki_x, kd_x);
			sp_y = PID_y(target_y, y, kp_y, ki_y, kd_y);

			sx = servo_x + sp_x;
			sy = servo_y + sp_y;
		}
		/*输出xy舵机的驱动值*/
			PWM_SetCompare_x(sx);
			PWM_SetCompare_y(sy);
		
		/*OLED显示当前xy的pid后的值*/
		OLED_ShowNum(3, 1,servo_x + sp_x,4);
		OLED_ShowNum(4, 1,servo_y + sp_y,4);
		
		OLED_ShowSignedNum(3, 7,sp_x,4);
		OLED_ShowSignedNum(4, 7,sp_y,4);
		

		
/******************舵机调试****************************/
//		KeyNum = Key_GetNum();
//		if (KeyNum == 1)
//		{
//			Angle_x += 5;
//			if (Angle_x > 190)
//			{
//				Angle_x = 0;
//			}
//		}
//		else if(KeyNum == 2)
//		{
//			Angle_y += 5;
//			if (Angle_y > 200)
//			{
//				Angle_y = 0;
//			}
//		}

//		//PWM_SetCompare_x(2500);
//		//PWM_SetCompare_y(500);
//		Servo_SetAngle_x(Angle_x);
//		Servo_SetAngle_y(Angle_y);
//		OLED_ShowNum(1, 1, Angle_x, 4);
//		OLED_ShowNum(2, 1, Angle_y, 4);
	}
}
