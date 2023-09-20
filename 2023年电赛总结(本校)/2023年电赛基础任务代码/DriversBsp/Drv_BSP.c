/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * ����    �������ƴ�
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
 * ����    ���ɿس�ʼ��
**********************************************************************************/
#include "Drv_BSP.h"
#include "Drv_PwmOut.h"
#include "Drv_led.h"
#include "Drv_adc.h"
#include "Drv_RcIn.h"
#include "Drv_Timer.h"
#include "ANO_DT_LX.h"
#include "Drv_UbloxGPS.h"
#include "Drv_Uart.h"
#include "Drv_Timer.h"
#include "LX_FC_Fun.h"
#include "I2C_Init.h"
#include "ks103.h"

u8 task_no=0x00;

u8 All_Init()
{
	DrvSysInit();
	//��ʱ
	MyDelayMs(100);
	//LED���ܳ�ʼ��
	DvrLedInit();
	//��ʼ������������
	DrvPwmOutInit();
	MyDelayMs(100);
	
	SW_I2C_Init();
	//stop steering
	//������ƴ���
	steering_pd12=0;
	steering_pd13=0;
	
	
	
	Single_WriteI2C(SlaveAddress1, 2, 0x75);
	
	//��1��ʼ������������Ϊ������
	DrvUart1Init(115200);
	
	//����2��ʼ������������Ϊ������
	DrvUart2Init(115200);
	//����3��ʼ�� tx ������ģ�� rx��uwb
	DrvUart3Init(115200);
	//����������
	DrvUart4Init(500000);
	//����5��imu
	DrvUart5Init(500000);
	MyDelayMs(100);
	//SBUS����ɼ���ʼ��
	DrvRcInputInit();
	//��ص�ѹ�ɼ���ʼ��
	DrvAdcInit();
	MyDelayMs(100);
	
	//read pc6 pc7 judge run mode
//	if((task_pc6==0)&&(task_pc7==0))
//	{
//		task_no=0;
//	}
//	else if((task_pc6==0)&&(task_pc7==1))
//	{
//		task_no=1;
//	}
//	else if((task_pc6==1)&&(task_pc7==0))
//	{
//		task_no=2;
//	}
//	else if((task_pc6==1)&&(task_pc7==1))
//	{
//		task_no=3;
//	}
//	
//	
//	
//	
//	
//	
	//����ģ���ʼ��
	ANO_DT_Init();
	MyDelayMs(800);
//	//GPS�ӿڳ�ʼ��
//	Init_GPS();
	//��ʼ����ʱ�ж�
	DrvTimerFcInit();
	//��ʼ����ɣ�����1
	FC_Lock();
	return (1);
}

_rc_input_st rc_in;
void DrvRcInputInit(void)
{
	//�����ʼ��һ��ģʽ
	DrvRcPpmInit();
	//DrvRcSbusInit();

	//�ȱ��λ��ʧ
	rc_in.no_signal = 1;
}
void DrvPpmGetOneCh(u16 data)
{
	static u8 ch_sta = 0;
	if ((data > 2500 && ch_sta > 3) || ch_sta == 10)
	{
		ch_sta = 0;
		rc_in.signal_cnt_tmp++;
		rc_in.rc_in_mode_tmp = 1; //�л�ģʽ���Ϊppm
	}
	else if (data > 300 && data < 3000) //�쳣��������˵�
	{
		//
		rc_in.ppm_ch[ch_sta] = data;
		ch_sta++;
	}
}
void DrvSbusGetOneByte(u8 data)
{
/*
sbus flags�Ľṹ������ʾ��
flags��
bit7 = ch17 = digital channel (0x80)
bit6 = ch18 = digital channel (0x40)
bit5 = Frame lost, equivalent red LED on receiver (0x20)
bit4 = failsafe activated (0x10) b: 0001 0000
bit3 = n/a
bit2 = n/a
bit1 = n/a
bit0 = n/a
*/
	const u8 frame_end[4] = {0x04, 0x14, 0x24, 0x34};
	static u32 sbus_time[2];
	static u8 datatmp[25];
	static u8 cnt = 0;
	static u8 frame_cnt;
	//
	sbus_time[0] = sbus_time[1];
	sbus_time[1] = GetSysRunTimeUs();
	if ((u32)(sbus_time[1] - sbus_time[0]) > 2500)
	{
		cnt = 0;
	}
	//
	datatmp[cnt++] = data;
	//
	if (cnt == 25)
	{
		cnt = 24;
		//
		//if(datatmp[0] == 0x0F && (datatmp[24] == 0x00))
		//if(datatmp[0] == 0x0F && ((datatmp[24] == 0x00)||(datatmp[24] == 0x04)||(datatmp[24] == 0x14)||(datatmp[24] == 0x24)||(datatmp[24] == 0x34)))
		if ((datatmp[0] == 0x0F && (datatmp[24] == 0x00 || datatmp[24] == frame_end[frame_cnt])))
		{
			cnt = 0;
			rc_in.sbus_ch[0] = (s16)(datatmp[2] & 0x07) << 8 | datatmp[1];
			rc_in.sbus_ch[1] = (s16)(datatmp[3] & 0x3f) << 5 | (datatmp[2] >> 3);
			rc_in.sbus_ch[2] = (s16)(datatmp[5] & 0x01) << 10 | ((s16)datatmp[4] << 2) | (datatmp[3] >> 6);
			rc_in.sbus_ch[3] = (s16)(datatmp[6] & 0x0F) << 7 | (datatmp[5] >> 1);
			rc_in.sbus_ch[4] = (s16)(datatmp[7] & 0x7F) << 4 | (datatmp[6] >> 4);
			rc_in.sbus_ch[5] = (s16)(datatmp[9] & 0x03) << 9 | ((s16)datatmp[8] << 1) | (datatmp[7] >> 7);
			rc_in.sbus_ch[6] = (s16)(datatmp[10] & 0x1F) << 6 | (datatmp[9] >> 2);
			rc_in.sbus_ch[7] = (s16)datatmp[11] << 3 | (datatmp[10] >> 5);

			rc_in.sbus_ch[8] = (s16)(datatmp[13] & 0x07) << 8 | datatmp[12];
			rc_in.sbus_ch[9] = (s16)(datatmp[14] & 0x3f) << 5 | (datatmp[13] >> 3);
			rc_in.sbus_ch[10] = (s16)(datatmp[16] & 0x01) << 10 | ((s16)datatmp[15] << 2) | (datatmp[14] >> 6);
			rc_in.sbus_ch[11] = (s16)(datatmp[17] & 0x0F) << 7 | (datatmp[16] >> 1);
			rc_in.sbus_ch[12] = (s16)(datatmp[18] & 0x7F) << 4 | (datatmp[17] >> 4);
			rc_in.sbus_ch[13] = (s16)(datatmp[20] & 0x03) << 9 | ((s16)datatmp[19] << 1) | (datatmp[18] >> 7);
			rc_in.sbus_ch[14] = (s16)(datatmp[21] & 0x1F) << 6 | (datatmp[20] >> 2);
			rc_in.sbus_ch[15] = (s16)datatmp[22] << 3 | (datatmp[21] >> 5);
			rc_in.sbus_flag = datatmp[23];

			//user
			//
			if (rc_in.sbus_flag & 0x08)
			{
				//������������ܽ��յ���ʧ�ر�ǣ��򲻴���ת�޳�������ʧ�ء�
			}
			else
			{
				rc_in.signal_cnt_tmp++;
				rc_in.rc_in_mode_tmp = 2; //�л�ģʽ���Ϊsbus
			}
			//֡β����
			frame_cnt++;
			frame_cnt %= 4;
		}
		else
		{
			for (u8 i = 0; i < 24; i++)
			{
				datatmp[i] = datatmp[i + 1];
			}
		}
	}
}
static void rcSignalCheck(float *dT_s)
{
	//
	static u8 cnt_tmp;
	static u16 time_dly;
	time_dly += (*dT_s) * 1e3f;
	//==1000ms==
	if (time_dly > 1000)
	{
		time_dly = 0;
		//
		rc_in.signal_fre = rc_in.signal_cnt_tmp;

		//==�ж��ź��Ƿ�ʧ
		if (rc_in.signal_fre < 5)
		{
			rc_in.no_signal = 1;
		}
		else
		{
			rc_in.no_signal = 0;
		}
		//==�ж��Ƿ��л����뷽ʽ
		if (rc_in.no_signal)
		{
			//��ʼ0
			if (rc_in.sig_mode == 0)
			{
				cnt_tmp++;
				cnt_tmp %= 2;
				if (cnt_tmp == 1)
				{
					DrvRcSbusInit();
				}
				else
				{
					DrvRcPpmInit();
				}
			}
		}
		else
		{
			rc_in.sig_mode = rc_in.rc_in_mode_tmp;
		}
		//==
		rc_in.signal_cnt_tmp = 0;
	}
}

void DrvRcInputTask(float dT_s)
{
	//�źż��
	rcSignalCheck(&dT_s);
	//���ź�
	if (rc_in.no_signal == 0)
	{
		//ppm
		if (rc_in.sig_mode == 1)
		{
			for (u8 i = 0; i < 10; i++) //ע��ֻ��10��ͨ��
			{
				rc_in.rc_ch.st_data.ch_[i] = rc_in.ppm_ch[i]; 
			}
		}
		//sbus
		else if (rc_in.sig_mode == 2)
		{
			for (u8 i = 0; i < 10; i++) //ע��ֻ��10��ͨ��
			{
				rc_in.rc_ch.st_data.ch_[i] = 0.644f * (rc_in.sbus_ch[i] - 1024) + 1500; //248 --1024 --1800ת����1000-2000
			}
		}
		//���ʧ�ر�������
		if (
			(rc_in.rc_ch.st_data.ch_[ch_5_aux1] > 1200 && rc_in.rc_ch.st_data.ch_[ch_5_aux1] < 1400) || (rc_in.rc_ch.st_data.ch_[ch_5_aux1] > 1600 && rc_in.rc_ch.st_data.ch_[ch_5_aux1] < 1800))
		{
			//�������ã����Ϊʧ��
			rc_in.fail_safe = 1;
		}
		else
		{
			rc_in.fail_safe = 0;
		}
	}
	//���ź�
	else
	{
		//ʧ�ر����λ
		rc_in.fail_safe = 1;
		//
		for (u8 i = 0; i < 10; i++) //ע��ֻ��10��ͨ��
		{
			rc_in.rc_ch.st_data.ch_[i] = 0; //
		}
	}
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
