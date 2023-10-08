#include "SysConfig.h"

typedef struct
{
	s16 target_point[2];
	int32_t alt_cm;
	int32_t target_alt_cm;
	u8 keep_height;
	u8 keep_yaw;
	u8 pointfly;
	s16 yaw_cm;
	s16 YAW;
	s16 YAW_Start;
	//PID位置环参数
	float offset_N[4];			//北  西  天  
	float offset_B[4];			//X    Y    Z    YAW  
	float des_V[4];					//X    Y    Z    YAW
	u8 test_button;
	int16_t target_speed_x;
	int16_t target_speed_y;
	int16_t target_speed_z;
	s16 mission_step_test;
	s16 X_Control;
	s16 Y_Control;
	u8 Camera_error;
	u8 keep_point;
	u8 key;
	u8 Camera_Flag;
	u8 T265_Flag;
	s16 FireCenter[2];
	s16 Last_FireCenter[2];
	u8 FireFinding_Flag;
	u8 Success_Find;
	u8 Page_OK_Flag;
	u8 place;
	s16 Fly_x;
	s16 Fly_y;
	u8 Send_Fire_Location;
}Flight_info;


typedef struct
{
	Flight_info Flight;
} User_Info;

extern User_Info User;


