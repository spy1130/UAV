/*==========================================================================
 * 描述    ：T265数据处理
 * 更新时间：2023年3月23日
 * 作者		 ：	LHB
===========================================================================*/

#ifndef __USER_T265_
#define __USER_T265_

#include "Drv_Uart.h"
#include "uart.h"
#include "hw_ints.h"
#include "hw_gpio.h"
#include "hw_types.h"
#include "Ano_DT_LX.h"
#include "Drv_UbloxGPS.h"
#include "Drv_AnoOf.h"


//==定义
typedef struct
{
//	uint8_t offline;
//	uint8_t mode_sta;
	uint8_t ctrl_mode;
	//原始坐标[T265坐标系]
	int16_t pos_x;
	int16_t pos_y;
	int16_t pos_z;
	//原始速度
	int16_t v_x;
	int16_t v_y;
	int16_t v_z;
	//原始欧拉角
	int16_t pitch;
	int16_t roll;
	int16_t yaw;
	
	//转换后坐标[匿名坐标系]
	int16_t pos_x_f;
	int16_t pos_y_f;
	int16_t pos_z_f;
	//转换后速度
	int16_t v_x_f;
	int16_t v_y_f;
	int16_t v_z_f;
	//转换后欧拉角
	int16_t pi_f;
	int16_t ro_f;
	int16_t ya_f;
	
}T265_Data;

extern T265_Data t265;//T265结构体 全局变量
extern uint8_t t265_send[30];//T265发送数据缓冲

void t265_data_get(uint8_t data);//T265数据获取
void t265_data_analysis(void);//T265数据解析


#endif
