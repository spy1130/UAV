//T265头文件。
#include "SysConfig.h"
typedef struct
{
	//
	u8 of_t265_update_cnt;  //T265速度等数据更新计数。
	u8 alt_t265_update_cnt; //高度数据更新计数。
	u8 pos_t265_update_cnt;
	//
	u8 t265_link_sta; //连接状态：0，未连接。1，已连接。
	u8 t265_work_sta; //工作状态：0，异常。1，正常
	//
	u8 t265_of_quality;
	//t65的速度信息，单位cm
	s16 speed_x_cms;
	s16 speed_y_cms;
	s16 speed_z_cms;
	
	/*
	s16 of2_dx_fix;
	s16 of2_dy_fix;
	s16 intergral_x;
	s16 intergral_y;
	*/
	//高度信息，单位cm，传过来时注意处理
	//里程计信息
	s16 pose_x_cm;
	s16 pose_y_cm;
	s16 pose_z_cm;
	
	//
	float quaternion[4];
	//
	s16 t265_acc_data_x;
	s16 t265_acc_data_y;
	s16 t265_acc_data_z;
	s16 t265_gyr_data_x;
	s16 t265_gyr_data_y;
	s16 t265_gyr_data_z;

}T265_info;

typedef union
{
	float Data[6];
	u8 byet[24];
}float_u8;

typedef union
{
	float Data[1];
	u8 byet[4];
}float2_u8;


typedef union
{
	s16 Data[2];
	u8 byet[4];
}s16_u8;

extern T265_info T265;
void T265_GetOneByte(uint8_t data);
void T265_Restart(u8 data);
void T265_text(s16 x,s16 y);
