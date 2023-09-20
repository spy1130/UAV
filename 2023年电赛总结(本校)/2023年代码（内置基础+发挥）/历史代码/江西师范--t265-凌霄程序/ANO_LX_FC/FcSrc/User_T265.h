/*==========================================================================
 * ����    ��T265���ݴ���
 * ����ʱ�䣺2023��3��23��
 * ����		 ��	LHB
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


//==����
typedef struct
{
//	uint8_t offline;
//	uint8_t mode_sta;
	uint8_t ctrl_mode;
	//ԭʼ����[T265����ϵ]
	int16_t pos_x;
	int16_t pos_y;
	int16_t pos_z;
	//ԭʼ�ٶ�
	int16_t v_x;
	int16_t v_y;
	int16_t v_z;
	//ԭʼŷ����
	int16_t pitch;
	int16_t roll;
	int16_t yaw;
	
	//ת��������[��������ϵ]
	int16_t pos_x_f;
	int16_t pos_y_f;
	int16_t pos_z_f;
	//ת�����ٶ�
	int16_t v_x_f;
	int16_t v_y_f;
	int16_t v_z_f;
	//ת����ŷ����
	int16_t pi_f;
	int16_t ro_f;
	int16_t ya_f;
	
}T265_Data;

extern T265_Data t265;//T265�ṹ�� ȫ�ֱ���
extern uint8_t t265_send[30];//T265�������ݻ���

void t265_data_get(uint8_t data);//T265���ݻ�ȡ
void t265_data_analysis(void);//T265���ݽ���


#endif
