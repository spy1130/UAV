#ifndef __ANO_LX_H
#define __ANO_LX_H
//==引用
#include "McuConfig.h"

//==定义/声明

	
enum 
{
	ch_1_rol=0,
	ch_2_pit,
	ch_3_thr,
	ch_4_yaw,
	ch_5_aux1,
	ch_6_aux2,
	ch_7_aux3,
	ch_8_aux4,
	ch_9_aux5,	
	ch_10_aux6,	
};

//0x40
typedef struct
{
	s16 ch_[10]; //	

}__attribute__ ((__packed__)) _rc_ch_st;

typedef union 
{
	u8 byte_data[20];
	_rc_ch_st st_data;
}_rc_ch_un;

//0x41
typedef struct
{
	s16 rol;
	s16 pit;
	s16 thr;
	s16 yaw_dps;
	s16 vel_x;
	s16 vel_y;
	s16 vel_z;

}__attribute__ ((__packed__)) _rt_tar_st;

typedef union 
{
	u8 byte_data[14];
	_rt_tar_st st_data;
}_rt_tar_un;

//0x0D
typedef struct
{
	u16 voltage_100;
	u16 current_100;

}__attribute__ ((__packed__)) _fc_bat_st;

typedef union 
{
	u8 byte_data[4];
	_fc_bat_st st_data;
}_fc_bat_un;


//
typedef struct
{
	u16 pwm_m1;
	u16 pwm_m2;
	u16 pwm_m3;
	u16 pwm_m4;
	u16 pwm_m5;
	u16 pwm_m6;
	u16 pwm_m7;
	u16 pwm_m8;
}_pwm_st;

//==数据声明
extern _rt_tar_un rt_tar;
extern _fc_bat_un fc_bat;
extern _pwm_st pwm_to_esc;
//==函数声明
//static


//public
void ANO_LX_Task(void);

#endif

