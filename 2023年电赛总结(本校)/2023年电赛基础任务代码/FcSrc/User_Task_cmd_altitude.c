#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "ANO_DT_LX.h"
#include "main.h"
#include <string.h>
#include "stdio.h"




int i;

void UserTask_OneKeyCmd(void)
{
    //////////////////////////////////////////////////////////////////////
    //一键起飞/降落例程
    //////////////////////////////////////////////////////////////////////
    //用静态变量记录一键起飞/降落指令已经执行。
    static u8 one_key_takeoff_f = 1, one_key_land_f = 1, one_key_mission_f = 0;
    static u8 mission_step, last_switch=0,now_switch=0;
	
    //判断有遥控信号才执行
    if (rc_in.no_signal == 0)
    {
        
			
			  //判断第6通道拨杆位置 800<CH_6<1200 1000  c号开关拨到了1挡
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
        {
            //还没有执行
            if (one_key_land_f == 0)
            {
                //标记已经执行
                one_key_land_f =
                    //执行一键降落
                    OneKey_Land();
            }
						now_switch=1;
					
						if(last_switch!=now_switch)
						{
							last_switch=now_switch;
							sprintf(buf1,"[x1] sound201 ");//\[b1] 欢迎光临，请进
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
        }
        else
        {
            //复位标记，以便再次执行
            one_key_land_f = 0;
        }
			
			
			
			
			
			
			
			
			
			
			
			//判断第6通道拨杆位置 1300<CH_6<1700  1500   c号开关拨到了2挡
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1300 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1700)
        {
            //还没有执行
//            if (one_key_takeoff_f == 0)
//            {
//                //标记已经执行
//                one_key_takeoff_f =
//                    //执行一键起飞
//                    OneKey_Takeoff(100); //参数单位：厘米； 0：默认上位机设置的高度。
//            }
					
					if (one_key_takeoff_f == 0)
					{	
						
						
//						rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
//						//这里会把实时XYZ-YAW期望速度置零		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =0;
//						rt_tar.st_data.vel_y =20;
//						rt_tar.st_data.vel_z = 20;

//							
//					 dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。	
						
						
						
						one_key_mission_f = 0;
						mission_step = 1;
						
						
						now_switch=2;
					
						if(last_switch!=now_switch)
						{
							last_switch=now_switch;
							sprintf(buf1,"[x1] sound203 ");//\[b1] 欢迎光临，请进
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
						
							
						
						
				}
					
					
										
        }
        else
        {
            //复位标记，以便再次执行
            one_key_takeoff_f = 0;
        }
        //
    
	//判断第6通道拨杆位置 1700<CH_6<2200  c号开关拨到了三挡
		if(rc_in.rc_ch.st_data.ch_[ch_6_aux2]>1700 && rc_in.rc_ch.st_data.ch_[ch_6_aux2]<2200)
		{
			//还没有执行
			if(one_key_mission_f ==0)
			{
				//标记已经执行
				one_key_mission_f = 1;
				//开始流程
				mission_step = 1;
				//可以播放语音
				
			}
			
			now_switch=3;
			last_switch=3;
			
		}
		else
		{
			//复位标记，以便再次执行
			one_key_mission_f = 0;		
		}
		//
		if(one_key_mission_f==1)
		{
			static u16 time_dly_cnt_ms;
			//
			switch(mission_step)
			{
				case 0:
				{
					//reset
					time_dly_cnt_ms = 0;
				}
				break;
				case 1:
				{
					//切换程控模式
					//mission_step += LX_Change_Mode(3);
					mission_step=mission_step+1;
				}
				break;
				case 2:
				{
					//解锁
					mission_step += FC_Unlock();
					//buf1[]={"[s9]解锁sound223 "};//\[b1] 欢迎光临，请进
					
					sprintf(buf1,"[s8]解锁");//\[b1] 欢迎光临，请进
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
				break;
				case 3:
				{
					//等2秒
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}
				}
				break;
				case 4:
				{
					//起飞
					mission_step += OneKey_Takeoff(100);//参数单位：厘米； 0：默认上位机设置的高度。
					
					//buf1[]={"[s9]起飞sound223 "};//\[b1] 欢迎光临，请进
					
					sprintf(buf1,"起飞");//\[b1] 欢迎光临，请进
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					
				}
				break;
				case 5:
				{
					//等10秒
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}					
				}
				break;
				
				
				case 6:
				{
					//前进1米
					mission_step += LX_Change_Mode(3);
//					mission_step += 1;
					//buf1[]={"[s9]模式2sound223 "};//\[b1] 欢迎光临，请进
					
					sprintf(buf1,"[s9]模式3");//\[b1] 欢迎光临，请进
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
				break;	
				case 7:
				{
					//等10秒
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}	
				}
				

				
				
				case 8:
				{
					//前进1米
					//ission_step += Horizontal_Move(100,150,0);
						mission_step +=target_altituded(150);
					
					
					
//						rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
//						//这里会把实时XYZ-YAW期望速度置零		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =20;
//						rt_tar.st_data.vel_y =0;
//						rt_tar.st_data.vel_z = 20;

//							
//						dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。	
					
						time_dly_cnt_ms = 0;
//						mission_step += 1;
					
						//buf1[]={"[s9]45度斜飞sound223 "};//\[b1] 欢迎光临，请进
						
						sprintf(buf1,"[s9]高度命令");//\[b1] 欢迎光临，请进
		
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
					
					
					
					
					
				}
				break;	
				case 9:
				{
					//等10秒
					if(time_dly_cnt_ms<5000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}	
				}
				break;
				case 10:
				{
					//右移1米
					//mission_step += Horizontal_Move(100,150,90);
					//执行一键降落
					//OneKey_Land();	
				
					
					
					
						rt_tar.st_data.rol = 0;
						rt_tar.st_data.pit = 0;
						rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
						//这里会把实时XYZ-YAW期望速度置零		
						rt_tar.st_data.yaw_dps = 0;
						rt_tar.st_data.vel_x =0;
						rt_tar.st_data.vel_y =0;
						rt_tar.st_data.vel_z = 0;

							
						dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。	
					
						time_dly_cnt_ms = 0;
						mission_step += 1;
					
						//buf1[]={"[s9]z轴零速sound223 "};//\[b1] 欢迎光临，请进
						
						sprintf(buf1,"[s9]]z轴零速");//\[b1] 欢迎光临，请进
	
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
					
					
				}
				break;
				
				case 11:
				{
					//等10秒
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
					}	
				}
				break;
				
				
				case 12:
				{
					//右移1米
					//mission_step += Horizontal_Move(100,150,90);
					//执行一键降落
					OneKey_Land();

					//buf1[]={"[s9]降落sound223 "};//\[b1] 欢迎光临，请进
					
					sprintf(buf1,"[s9]降落");//\[b1] 欢迎光临，请进
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					mission_step += 1;
					
						
					
					
				}
				break;
				
				
				
				
//				case 9:
//				{
//					//等10秒
//					if(time_dly_cnt_ms<10000)
//					{
//						time_dly_cnt_ms+=20;//ms
//					}
//					else
//					{
//						time_dly_cnt_ms = 0;
//						mission_step += 1;
//					}						
//				}
//				break;
//				case 10:
//				{
//					//执行一键降落
//					OneKey_Land();					
//				}
//				break;	
//				case 11:
//				{
//					
//				}
//				break;
//				case 12:
//				{
//				
//				}
//				break;
				case 13:
				{
					
				}
				break;
				case 14:
				{
					
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
