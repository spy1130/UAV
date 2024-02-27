#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "my_code.h"

u16 Task_time_dly_cnt_ms;
u8 mission_step;

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
					mission_step += FC_Unlock();
				}break;
				
				
				
				case 3:
				{
					User_Task_Delay(2000);
					yaw_record = yaw;
					dis_x_target=dis_x;
					dis_y_target=dis_y;
				}break;
				
				
				
				case 4:
				{
					//起飞
					keep_hight_flag=1;
					hight_target=100;
					mission_step++;
				}break;
				
				
				case 5:
				{
					if(((hight_target-hight)>-3)&&((hight_target-hight)<3)) mission_step++;
				}break;
				
				case 6:
				{
					//起飞
					dis_x_target+=50;
					mission_step++;
				}break;
				
				
				case 7:
				{
					if(((dis_x_target-dis_x)>-3)&&((dis_x_target-dis_x)<3)) mission_step++;
				}break;
				
				
				case 8:
				{
					dis_y_target+=50;
					mission_step++;
				}break;
				
				
				case 9:
				{
					if(((dis_y_target-dis_y)>-3)&&((dis_y_target-dis_y)<3)) mission_step++;
				}break;
				
				
				case 10:
				{
					keep_hight_flag=0;
					OneKey_Land();					
				}
				break;	
				
				

				
//				case 5:{User_Task_Delay(5000);}break;
//				
//				
//				
//				case 6:
//				{
//					if((yaw-yaw_record)>=0)mission_step+=right_Move(yaw-yaw_record,yaw-yaw_record);
//					if((yaw_record-yaw)>0) mission_step+=left_Move(yaw_record-yaw,yaw_record-yaw);
//				}
//				break;
//				
//				case 7:{User_Task_Delay(2000);}break;

//				
//				case 8:
//				{
////					keep_dis_z_flag=1;
//					mission_step += Horizontal_Move(50,15,90);
//				}
//				break;
//				
//				case 9:{User_Task_Delay(5000);}break;
//				
//				
//				case 10:
//				{
//					mission_step += Horizontal_Move(50,15,270);
//				}
//				break;
//				case 11:{User_Task_Delay(5000);}break;
//				
//				
//				
//				case 12:
//				{
//					mission_step += Horizontal_Move(50,15,90);
//				}
//				break;
//				case 13:{User_Task_Delay(5000);}break;
//				
//				
//				
//				case 14:
//				{
//					mission_step += Horizontal_Move(50,15,270);
//				}
//				break;
//				case 15:{User_Task_Delay(5000);}break;
//				
//				
//				
//				case 16:
//				{
//					mission_step += Horizontal_Move(50,15,90);
//				}
//				break;
//				case 17:{User_Task_Delay(5000);}break;
//				
//				
//				
//				case 18:
//				{
//					mission_step += Horizontal_Move(50,15,270);
//				}
//				break;
//				case 19:{User_Task_Delay(5000);}break;
//				

//				case 20:
//				{
//					//执行一键降落
//					OneKey_Land();					
//				}
//				break;	
//				
				
				
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
