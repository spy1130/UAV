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
//					keep_openmv_dis_xy_flag=1;
					keep_yaw_flag=1;
					dis_x_target=dis_x;
					dis_y_target=dis_y;
					keep_x_flag=1;
					keep_y_flag=1;
					hight_target=120;
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
					User_Task_Delay(15000);
				}break;
				
				
				case 9:
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
