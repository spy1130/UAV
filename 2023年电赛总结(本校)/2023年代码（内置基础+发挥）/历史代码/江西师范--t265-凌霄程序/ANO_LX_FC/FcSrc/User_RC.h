/*==========================================================================
 * ����    ��ң�������ݴ���һ��ͣ��������ѡ���
 * ����ʱ�䣺2023��3��23��
 * ����		 ��	LHB
===========================================================================*/

#ifndef __USER_RC_H
#define __USER_RC_H

#include "Drv_RcIn.h"
#include "Timer.h"
#include "hw_ints.h"
#include "uart.h"

void User_RC_Check(void);//ң�����û����ݴ���
void RC_LOCK_Check(void);//�ɿؽ�������
void RC_LAND_Check(void);//�ɿ�һ������
void RC_Change_mode(void);//ѡ���ٶȴ�������Դ

#endif
