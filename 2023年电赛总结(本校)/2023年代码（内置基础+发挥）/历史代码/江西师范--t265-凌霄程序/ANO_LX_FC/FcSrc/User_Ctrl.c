/*==========================================================================
 * 描述    ：用户程控函数
 * 更新时间：2023年3月26日
 * 作者		 ：	LHB
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

s16 CMDvalue[4]={0}; //实时控制帧x y z deg发送数据  
////////////////////////////////

u8 ProgramAutoLand =0;//程控自动降落
///////////////////////////////
u8 LocCtrlEnable =0;
u8 AngCtrlEnable =0;
u8 AttCtrlEnable =0;
/*控制使能标志位0不控制 1 控制*/
///////////////////////////////
/**********************************************************************************************************
*函 数 名: Program_Ctrl_User_Set_Speed()
*功能说明: 程控功能，航向水平坐标系下速度设定（实时控制）
*参    数: X速度（厘米每秒，正为前进，负为后退，Y速度（厘米每秒，正为左移，负为右移）
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/
void Program_Ctrl_User_Set_Speed(s16 xpcm, s16 ypcm, s16 zpcm, s16 degpres)
{
		CMDvalue[0] = degpres;  //航向转动角速度，度每秒，逆时针为正
		CMDvalue[1] = xpcm;    //头向速度，厘米每秒
		CMDvalue[2] = ypcm;    //左向速度，厘米每秒
		CMDvalue[3] = zpcm;	 //天向速度，厘米每秒
}

/**********************************************************************************************************
*函 数 名: User_Loc_Ctrl
*功能说明:	有待改进 拆分成多个函数 加入高度环控制
*参    数:实际位置 期望位置 调用函数频率
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/
void User_Loc_Ctrl(s16 true_x_cm,s16 true_y_cm,s16 true_z_cm,s16 true_yaw_deg,s16 exp_x_cm,s16 exp_y_cm,s16 exp_z_cm,s16 exp_yaw_deg,u8 freq)
{
	static float err_old_x_cm=0,err_old_y_cm=0,err_old_z_cm=0,err_old_yaw_deg=0;
	static float err_new_x_cm=0,err_new_y_cm=0,err_new_z_cm=0,err_new_yaw_deg=0;
	static float err_add_x_cm=0,err_add_y_cm=0,err_add_z_cm=0,err_add_yaw_deg=0;
	static s16 spd_out_x_cm=0,spd_out_y_cm=0,spd_out_z_cm=0,spd_out_yaw_deg=0;
	
	static s16 LandTime =0;
	///////////////////////////////////////////////////////////////////////////////
	/*PID计算*/
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
	/*限速*/
	spd_out_x_cm=LIMIT(spd_out_x_cm,-40,40);
	spd_out_y_cm=LIMIT(spd_out_y_cm,-40,40);
	spd_out_z_cm=LIMIT(spd_out_z_cm,-10,10);
	spd_out_yaw_deg=LIMIT(spd_out_yaw_deg,-10,10);
	///////////////////////////////////////////////////////////////////////////////
	/*控制量输出*/
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
	if(ProgramAutoLand==1)//执行自动降落
	{
		LandTime+=5;
		
		if(LandTime>=15*1000||true_z_cm<=5)
		{
			spd_out_z_cm=0;
			ProgramAutoLand=0;//自动降落标志位复位
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
	Program_Ctrl_User_Set_Speed(spd_out_x_cm,spd_out_y_cm,spd_out_z_cm,-spd_out_yaw_deg);//Z轴速度为0，目前高度开环控制
}

/**********************************************************************************************************
*函 数 名: 待定
*功能说明:	 高度环
*参    数:
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*函 数 名: 待定
*功能说明:	 激光雷达自主避障控制
*参    数:
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*函 数 名: 待定
*功能说明:	 视觉降落
*参    数:
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*函 数 名: 待定
*功能说明:	 位置环降落
*参    数:
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*函 数 名: 待定
*功能说明:	 绕杆飞行控制
*参    数:
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/

/**********************************************************************************************************
*函 数 名: 待定
*功能说明:	 一键起飞定高
*参    数:
*返 回 值: 无
*作    者: LHB
**********************************************************************************************************/

