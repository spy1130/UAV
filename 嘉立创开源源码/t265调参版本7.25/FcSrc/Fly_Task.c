#include "Fly_Task.h"
#include "info.h"
#include "T265_Sensor.h"
#include "Ano_Math.h"
#include "PID.h"

#define LIMIT_XY_SPEED 25
extern PID_Struct_f X_PID;
extern PID_Struct_f Y_PID;
extern PID_Struct_f X_K_PID;
extern PID_Struct_f Y_K_PID;
static s16 UAV_pos_xy[2],target_speed_xy[2],home_pos_xy[2];

void RecordHome(s16 x,s16 y){
	home_pos_xy[0]=x;
	home_pos_xy[1]=y;
}


s16 Height_Control(){
	if(ABS(User.Flight.alt_cm-User.Flight.target_alt_cm)<4){
	return 1;
	}
	else{
	return 0;
	}
}

u8 PointFly_PID(s16 x,s16 y){
	if(User.Flight.pointfly == 1){
		UAV_pos_xy[0] = T265.pose_x_cm - home_pos_xy[0];
		UAV_pos_xy[1] = T265.pose_y_cm - home_pos_xy[1]; //获取无人机当前位置 
		
		target_speed_xy[0]=PID_Calc(&X_PID,x- UAV_pos_xy[0]);	//获取飞机机体x方向的PID速度(厘米/秒)
		target_speed_xy[1]=PID_Calc(&Y_PID,y- UAV_pos_xy[1]);	//获取飞机机体x方向的PID速度(厘米/秒)
		
		rt_tar.st_data.vel_x = LIMIT(target_speed_xy[0],-LIMIT_XY_SPEED,LIMIT_XY_SPEED);
		rt_tar.st_data.vel_y = LIMIT(target_speed_xy[1],-LIMIT_XY_SPEED,LIMIT_XY_SPEED);
	}
		if(ABS(target_speed_xy[0]) < 10 && ABS(target_speed_xy[1]) < 10 && ABS(T265.pose_x_cm - x)<7 && ABS(T265.pose_y_cm - y)<7)
			{
					return 1;
			}
			return 0;
			
}
/*------------------------------------------
Pole_Find----xy不变，找杆子 Finding--xy可变找杆
------------------------------------------*/


u8 Fire_Finding()
{
	if(User.Flight.FireFinding_Flag==1){
		if(User.Flight.Success_Find == 1){
		if(ABS(320-User.Flight.FireCenter[0]) < 15 && ABS(320-User.Flight.FireCenter[1]) < 15){//--------------需要修改
			return 1;
		}
		else{
			rt_tar.st_data.vel_x = 0.1*(320 - User.Flight.FireCenter[0]) + 0.05*(User.Flight.Last_FireCenter[0] - User.Flight.FireCenter[0]);
			rt_tar.st_data.vel_y = 0.12*(240 - User.Flight.FireCenter[1]) + 0.04*(User.Flight.Last_FireCenter[1] - User.Flight.FireCenter[1]);
			return 0;
		}
	}
 }
	return 0;
}

u8 Fire_Finding_SLOW()
{
	if(User.Flight.FireFinding_Flag==1){
		if(ABS(320-User.Flight.FireCenter[0]) < 10 && ABS(320-User.Flight.FireCenter[1]) < 10){//--------------需要修改
			return 1;
		}
		else{
			rt_tar.st_data.vel_x = 0.3*(320 - User.Flight.FireCenter[0]) + 0.1*(User.Flight.Last_FireCenter[0] - User.Flight.FireCenter[0]);
			rt_tar.st_data.vel_y = 0.3*(240 - User.Flight.FireCenter[1]) + 0.1*(User.Flight.Last_FireCenter[1] - User.Flight.FireCenter[1]);
			return 0;
		}
	}
	return 0;
}

u8 Point_Keep()
{
	static s16 KeepPoint[2];
	static u8 getpoint = 0;

	if(User.Flight.keep_point == 1)
	{
		if(getpoint == 0)
		{
			KeepPoint[0] = T265.pose_x_cm;
			KeepPoint[1] = T265.pose_y_cm;
			getpoint = 1;
		}
		else if(getpoint == 1)
		{
			target_speed_xy[0]=PID_Calc(&X_K_PID,KeepPoint[0] - T265.pose_x_cm);	//获取飞机机体x方向的PID速度(厘米/秒)
			target_speed_xy[1]=PID_Calc(&Y_K_PID,KeepPoint[1] - T265.pose_y_cm);	//获取飞机机体x方向的PID速度(厘米/秒)
		
			rt_tar.st_data.vel_x = LIMIT(target_speed_xy[0],-LIMIT_XY_SPEED,LIMIT_XY_SPEED);
			rt_tar.st_data.vel_y = LIMIT(target_speed_xy[1],-LIMIT_XY_SPEED,LIMIT_XY_SPEED);
		}
	}
	else
	{
		getpoint=0;
	}
	return 1;
}


