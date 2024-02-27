#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "my_code.h"

u16 Task_time_dly_cnt_ms;
u8 mission_step;
int cnt;
void UserTask_OneKeyCmd(void)
{
    //////////////////////////////////////////////////////////////////////
    //一键起飞/降落例程
    //////////////////////////////////////////////////////////////////////
    //用静态变量记录一键起飞/降落指令已经执行。
    static u8 one_key_land_f = 1, one_key_mission_f = 0;
    //判断有遥控信号才执行
    if (rc_in.no_signal == 0)
    {
//        //判断第6通道拨杆位置 1300<CH_6<1700
//        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1300 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1700)
//        {
//            //还没有执行
//            if (one_key_takeoff_f == 0)
//            {
//                //标记已经执行
//                one_key_takeoff_f =
//                    //执行一键起飞
//                    OneKey_Takeoff(100); //参数单位：厘米； 0：默认上位机设置的高度。
//            }
//        }
//        else
//        {
//            //复位标记，以便再次执行
//            one_key_takeoff_f = 0;
//        }
        //
        //判断第6通道拨杆位置 800<CH_6<1200
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
        {
            //还没有执行
            if (one_key_land_f == 0)
            {
                //标记已经执行
                one_key_land_f =
                    //执行一键降落
                    OneKey_Land();
							keep_hight_flag=0;

//							my_one_key_land();
//							one_key_land_f=1;
            }
        }
        else
        {
            //复位标记，以便再次执行
            one_key_land_f = 0;
        }
	//判断第6通道拨杆位置 1700<CH_6<2200 
		if(rc_in.rc_ch.st_data.ch_[ch_6_aux2]>1700 && rc_in.rc_ch.st_data.ch_[ch_6_aux2]<2200)
		{
			//还没有执行
			if(one_key_mission_f ==0)
			{
				//标记已经执行
				one_key_mission_f = 1;
				//开始流程
				mission_step = 1;
			}
		}
		else
		{
			//复位标记，以便再次执行
			one_key_mission_f = 0;		
		}
		//
		if(one_key_mission_f==1)
		{
			//
			switch(mission_step)
			{
				
				case 0:{Task_time_dly_cnt_ms = 0;}break;
				
				
				
				case 1:{//切换程控模式
					mission_step += LX_Change_Mode(2);
				}break;
				
				
				
				case 2:
				{
					//解锁
					around_pole_flag=0;
					keep_hight_flag=0;
					line_patro_flag=0;
					keep_x_flag=0;
					keep_line_dis_flag=0;
					keep_y_flag=0;
					keep_pole_flag=0;
					keep_yaw_flag=0;
					mission_step += FC_Unlock();
				}break;
				
				
				
				case 3:
				{
					User_Task_Delay(2000);
					dis_yaw_target = yaw;
				}break;
				
				
				
				case 4:
				{
					//起飞
					keep_yaw_flag=1;
					dis_x_target=dis_x;
					dis_y_target=dis_y;
					keep_x_flag=1;
					keep_y_flag=1;
					hight_target=135;
					keep_hight_flag=1;
					mission_step++;
				}break;
				
				
				case 5:
				{
					if(((hight_target-hight)>-3)&&((hight_target-hight)<3)) {mission_step++;keep_hight_flag=0;}
				}break;
				
				case 6:
				{
					mission_step++;
				}break;
				
				
				case 7://回正完成
				{
					if(((dis_yaw_target-yaw)>-3)&&((dis_yaw_target-yaw)<3)) {mission_step++;}
				}break;
				
				
				case 8:
				{
					mission_step++;
				}break;
				
				
				case 9:
				{
					dis_x_target+=0;
					mission_step++;
				}break;
				
				case 10://靠近杆完成
				{
					if(((dis_x_target-dis_x)>-3)&&((dis_x_target-dis_x)<3)) mission_step++;
				}break;

				
				case 11:
				{
					OpenMV_mode=1;
					keep_pole_flag=1;
					keep_line_dis_flag=1;
					mission_step++;
				}break;
				
				
				case 12://超声波靠杆
				{
					if((line_dis-line_dis_target>-30)&&(line_dis-line_dis_target<30)) cnt++; else cnt=0;
					if(cnt>5){cnt=0;mission_step++;keep_pole_flag=0;keep_line_dis_flag=0;}
				}break;
				
				
				
				
				
////////////////////////////////////////////检测条形码拍照/////////////////////////////////////////////////////////		
//				case 13:
//				{
//					OpenMV_mode=2;
//					line_patro_flag=1;
//					dis_y_target=dis_y;
//					dis_y_target-=300;
//					keep_y_flag=1;
//					dis_x_target=dis_x;
//					keep_x_flag=1;
////					keep_line_dis_flag=1;
//					mission_step++;
//				}break;
//				
//				case 14:
//				{
//					User_Task_Delay(1000);
//				}break;
//				

//				case 15://检测条形码
//				{
//					if(receive_OpenMV_mode==2) {mission_step++;dis_y_target=dis_y-10;dis_x_target=dis_x;keep_x_flag=0;}
//				}break;
//				
//				
//				case 16:
//				{
//					User_Task_Delay(3000);
//				}break;
//				

//				case 17:
//				{
//					OpenMV_mode=3;
//					if(receive_OpenMV_mode==4) {mission_step++;dis_y_target-=15;OpenMV_mode=1;}
//				}break;
//				
//				
//				
//				case 18:
//				{
//					User_Task_Delay(3000);
//				}break;
//				

//				
//				
//				case 19:
//				{
//					//执行一键降落
//					OneKey_Land();					
//				}
//				break;	
///////////////////////////////////////////////////////////////////////////////////////////////////
				
				
				
				
				
				
				case 13:
				{
					OpenMV_mode=1;
					line_patro_flag=1;
					dis_y_target=dis_y;
					dis_y_target-=300;
					keep_y_flag=1;
					dis_x_target=dis_x;
					keep_x_flag=1;
					keep_line_dis_flag=1;//////////////////
					mission_step++;
				}break;
				
				case 14:
				{
					User_Task_Delay(8000);
				}break;
				

				case 15:
				{
					if(receive_OpenMV_mode==1) {mission_step++;dis_y_target=dis_y;dis_x_target=dis_x;keep_x_flag=0;}
				}break;
				
				
				

				case 16:
				{
					OpenMV_mode=1;
					keep_pole_flag=1;
					keep_line_dis_flag=1;
					User_Task_Delay(3000);
				}break;
				
				
				case 17:
				{
					if((line_dis-line_dis_target>-30)&&(line_dis-line_dis_target<30)) cnt++; else cnt=0;
					if(cnt>5){cnt=0;mission_step++;keep_pole_flag=0;keep_line_dis_flag=0;}
				}break;
				
				

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
				case 18://
				{
					OpenMV_mode=1;
					keep_line_dis_flag=1;
					mission_step++;
				}break;


				case 19://绕杆开始
				{
					around_pole_flag=1;
					mission_step++;
				}break;
				
				
				case 20://绕杆目标
				{
					dis_yaw_target-=180;
					mission_step++;
				}break;
				
				
				case 21://预绕杆结束
				{
					if(((dis_yaw_target-yaw)>-30)&&((dis_yaw_target-yaw)<30)) {mission_step++;}
				}break;
				
				
				case 22://回正
				{
					around_pole_flag=0;
					keep_pole_flag=1;
					mission_step++;
				}break;
				
				case 23://回正完成
				{
					if((line_dis-line_dis_target>-30)&&(line_dis-line_dis_target<30)) cnt++; else cnt=0;
					if(cnt>5){cnt=0;mission_step++;keep_pole_flag=0;keep_line_dis_flag=0;}
				}break;
				
				
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////						
				case 24:
				{
					OpenMV_mode=1;
					line_patro_flag=1;
					dis_y_target=dis_y;
					dis_y_target-=300;
					keep_y_flag=1;
					dis_x_target=dis_x;
					keep_x_flag=1;
//					keep_line_dis_flag=1;
					mission_step++;
				}break;
				
				case 25:
				{
					User_Task_Delay(5000);
				}break;
				

				case 26:
				{
					if(receive_OpenMV_mode==1) cnt++; else cnt=0;
          if(cnt>10){cnt=0;mission_step++;dis_y_target=dis_y;dis_x_target=dis_x;keep_x_flag=0;}
				}break;
								
				
				case 27:
				{
					dis_x_target=dis_x-10;
					keep_x_flag=1;
					if((dis_x-dis_x_target>-30)&&(dis_x-dis_x_target<30)){mission_step++;}
				}break;
				
				
				case 28:
				{
					//执行一键降落
					OneKey_Land();					
				}
				break;	
				default:break;
			}
		}
		else
		{
			mission_step = 0;
		}
	}
    ////////////////////////////////////////////////////////////////////////
}
