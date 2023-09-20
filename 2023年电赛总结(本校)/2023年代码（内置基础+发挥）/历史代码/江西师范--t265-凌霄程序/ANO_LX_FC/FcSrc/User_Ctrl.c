/*==========================================================================
 * ����    ���û��̿غ���
 * ����ʱ�䣺2023��3��26��
 * ����		 ��	LHB
===========================================================================*/

#include "User_Ctrl.h"

#include "Drv_Uart.h"
#include "uart.h"
#include "hw_ints.h"
#include "hw_gpio.h"
#include "hw_types.h"
#include "Ano_DT_LX.h"
#include "Drv_UbloxGPS.h"
#include "Drv_AnoOf.h"
#include "Drv_AnoOf.h"
#include "User_T265.h"
#include "Ano_Math.h"
#include "User_Task.h"
#include "LX_FC_Fun.h"
#include "LX_FC_State.h"

s16 CMDvalue[4]={0}; //ʵʱ����֡x y z deg��������  
////////////////////////////////

u8 ProgramAutoLand =0;//�̿��Զ�����
///////////////////////////////
u8 LocCtrlEnable =0;
u8 AngCtrlEnable =0;
u8 AttCtrlEnable =0;
/*����ʹ�ܱ�־λ0������ 1 ����*/
///////////////////////////////
/**********************************************************************************************************
*�� �� ��: Program_Ctrl_User_Set_Speed()
*����˵��: �̿ع��ܣ�����ˮƽ����ϵ���ٶ��趨��ʵʱ���ƣ�
*��    ��: X�ٶȣ�����ÿ�룬��Ϊǰ������Ϊ���ˣ�Y�ٶȣ�����ÿ�룬��Ϊ���ƣ���Ϊ���ƣ�
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/
void Program_Ctrl_User_Set_Speed(s16 xpcm, s16 ypcm, s16 zpcm, s16 degpres)
{
		CMDvalue[0] = degpres;  //����ת�����ٶȣ���ÿ�룬��ʱ��Ϊ��
		CMDvalue[1] = xpcm;    //ͷ���ٶȣ�����ÿ��
		CMDvalue[2] = ypcm;    //�����ٶȣ�����ÿ��
		CMDvalue[3] = zpcm;	 //�����ٶȣ�����ÿ��
}

/**********************************************************************************************************
*�� �� ��: User_Loc_Ctrl
*����˵��:	�д��Ľ� ��ֳɶ������ ����߶Ȼ�����
*��    ��:ʵ��λ�� ����λ�� ���ú���Ƶ��
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/
void User_Loc_Ctrl(s16 true_x_cm,s16 true_y_cm,s16 true_z_cm,s16 true_yaw_deg,s16 exp_x_cm,s16 exp_y_cm,s16 exp_z_cm,s16 exp_yaw_deg,u8 freq)
{
	static float err_old_x_cm=0,err_old_y_cm=0,err_old_z_cm=0,err_old_yaw_deg=0;
	static float err_new_x_cm=0,err_new_y_cm=0,err_new_z_cm=0,err_new_yaw_deg=0;
	static float err_add_x_cm=0,err_add_y_cm=0,err_add_z_cm=0,err_add_yaw_deg=0;
	static s16 spd_out_x_cm=0,spd_out_y_cm=0,spd_out_z_cm=0,spd_out_yaw_deg=0;
	
	static s16 LandTime =0;
	///////////////////////////////////////////////////////////////////////////////
	/*PID����*/
	err_new_x_cm=exp_x_cm-true_x_cm;
	err_new_y_cm=exp_y_cm-true_y_cm;
	err_new_z_cm=exp_z_cm-true_z_cm;
	err_new_yaw_deg=exp_yaw_deg-true_yaw_deg;
	
	err_add_x_cm+=err_new_x_cm;
	err_add_y_cm+=err_new_y_cm;
	err_add_z_cm+=err_new_z_cm;
	err_add_yaw_deg+=err_new_yaw_deg;
	
	spd_out_x_cm=(s16)(loc_ctrl_dis_p*err_new_x_cm+LIMIT(loc_ctrl_dis_i*err_add_x_cm,-10,10)+loc_ctrl_dis_d*(err_new_x_cm-err_old_x_cm));
	spd_out_y_cm=(s16)(loc_ctrl_dis_p*err_new_y_cm+LIMIT(loc_ctrl_dis_i*err_add_y_cm,-10,10)+loc_ctrl_dis_d*(err_new_y_cm-err_old_y_cm));
	spd_out_z_cm=(s16)(loc_ctrl_att_p*err_new_z_cm+LIMIT(loc_ctrl_att_i*err_add_z_cm,-10,10)+loc_ctrl_att_d*(err_new_z_cm-err_old_z_cm));
	spd_out_yaw_deg=(s16)(loc_ctrl_ang_p*err_new_yaw_deg+LIMIT(loc_ctrl_ang_i*err_add_yaw_deg,-10,10)+loc_ctrl_ang_d*(err_new_yaw_deg-err_old_yaw_deg));
	
	err_old_x_cm=err_new_x_cm;
	err_old_y_cm=err_new_y_cm;
	err_old_z_cm=err_new_z_cm;
	err_old_yaw_deg=err_new_yaw_deg;
	//////////////////////////////////////////
	/*����*/
	spd_out_x_cm=LIMIT(spd_out_x_cm,-40,40);
	spd_out_y_cm=LIMIT(spd_out_y_cm,-40,40);
	spd_out_z_cm=LIMIT(spd_out_z_cm,-10,10);
	spd_out_yaw_deg=LIMIT(spd_out_yaw_deg,-10,10);
	///////////////////////////////////////////////////////////////////////////////
	/*���������*/
	//Program_Ctrl_User_Set_Speed(spd_out_x_cm,spd_out_y_cm,spd_out_z_cm,spd_out_yaw_deg);
	
	////////////////////////////////////////////////////////////////////////////////////
	if(LocCtrlEnable==0)
	{
		spd_out_x_cm=0;
		spd_out_y_cm=0;
	}
	
	if(AngCtrlEnable==0)
	{
		spd_out_yaw_deg=0;
	}
	
	if(AttCtrlEnable==0)
	{
		spd_out_z_cm=0;
	}
	//////////////////////////////////////////////////////////////////
	if(ProgramAutoLand==1)//ִ���Զ�����
	{
		LandTime+=5;
		
		if(LandTime>=15*1000||true_z_cm<=5)
		{
			spd_out_z_cm=0;
			ProgramAutoLand=0;//�Զ������־λ��λ
			LandTime=0;
			FC_Lock();
		}
		
		if(true_z_cm>=100)
			spd_out_z_cm=-20;
		else if(true_z_cm>=30)
			spd_out_z_cm=-10;
		else 
			spd_out_z_cm=-8;
	}
//////////////////////////////////////////////////////////////////////
	Program_Ctrl_User_Set_Speed(spd_out_x_cm,spd_out_y_cm,spd_out_z_cm,-spd_out_yaw_deg);//Z���ٶ�Ϊ0��Ŀǰ�߶ȿ�������
}

/**********************************************************************************************************
*�� �� ��: ����
*����˵��:	 �߶Ȼ�
*��    ��:
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*�� �� ��: ����
*����˵��:	 �����״��������Ͽ���
*��    ��:
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*�� �� ��: ����
*����˵��:	 �Ӿ�����
*��    ��:
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*�� �� ��: ����
*����˵��:	 λ�û�����
*��    ��:
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*�� �� ��: ����
*����˵��:	 �Ƹ˷��п���
*��    ��:
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*�� �� ��: ����
*����˵��:	 һ����ɶ���
*��    ��:
*�� �� ֵ: ��
*��    ��: LHB
**********************************************************************************************************/

