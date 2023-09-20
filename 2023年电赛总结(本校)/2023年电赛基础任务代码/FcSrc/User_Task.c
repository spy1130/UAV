#include "User_Task.h"
#include "Drv_RcIn.h"


#include "Drv_Uart.h"


#include "LX_FC_Fun.h"
#include "ANO_DT_LX.h"
#include "main.h"

#include "stdio.h"

#include <string.h>
#include <math.h>//调用三角函数
#include "main.h"

#include "User_Task.h"
#include <stdlib.h>//调用三角函数
#include "Drv_Sys.h"

#include "Drv_Uart.h"
#include "I2C_Init.h"

extern float		sum_x_aa;
extern u8 m1_step,m2_step,m3_step,m4_step;
extern u8 rx_buff_com1[20];
struct point
{
	float x;
	float y;
};

struct point sow_piont[12]={{0.4,4.4},{3.6,4.4},{3.6,3.6},{1.2,3.6},{1.2,2.8},{3.6,2.8},{3.6,2},{1.2,2},{1.2,1.2},{3.6,1.2},{3.6,0.4},{0.4,0.4}};

int sow_add[27]={28,27,20,19,26,25,18,14,10,8,4,3,7,9,3,7,24,23,16,6,2,1,5,11,15,22};
#define state_num 18
	
float home_x=0.7;
float home_y=0.67;
	
int wait_flag;
int standard_yaw,change_yaw;

//////////////////////////////////////////////////////////////////////////////////////////////
//follow_line()
//////////////////////////////////////////////////////////////////////////////////////////
int16_t pole_x=0,pole_y=0,pole_w=0,pole_w_middle=0;
int16_t line_x=0,line_y=0,line_sita=0;
int time_dly_cnt_ms_xm=0,time_dly_cnt_ms=0;
int16_t x_position=0,y_position=0,y_position_last=0;
char c, type;
double plant_x_init,plant_y_init,plant_z,act_x=4.19,act_y=4.46;
double plant_x,plant_y;
float error_x=0,error_y=0;
int add_n=0;
	
	
float altitude_set=170,p_altitude=1.0,speed_z_axis=0,speed_x_axis=0,speed_y_axis=0,p_longitude=10.0;//p_longitude原先数值为10
	
float altitude_set_1=80	;

int16_t speed_x_axis_16=0,speed_y_axis_16=0,speed_z_axis_16=0,yaw_16=0,p_speed_y_axis_16=0,d_speed_y_axis_16=0,speed_yaw_axis_16=0;										

u8 mission_step=0,near_alarm_flag=0,far_alarm_flag=0,near_alarm_count=0;

u8 far_alarm_count=0,first_a0_voice=1,cnt_20ms_no_signal=0,flag_45=0;

float cons_kp=0.08,cons_kd=0.2;

int i,cnt_20=0,trun_on_time=0;

u8 period_dis=0,basic_step=0,light_flag=0,s_i_xm=0,Send_Count_xm=0;

u8 DataScope_OutPut_Buffer_xm11[10]={0};

u8 index_sow_i=0;
float tar_temp_x,tar_temp_x,tar_temp_x;
float dis_sonic=0;


u8 position_1_order=0x00;
u8 position_2_order=0x00;
u8 tx1_buf_xm[6]={0};

int box_down_flag=0x00;
int box_count=0,result_target=0;

int record_cnt=0x00,record_arry[10]={0},start_iden_flag=0x00,m2_time_cnt=0x00;//;

int time;

unsigned char transition;



void cmd_send1(int16_t speed_x_axis_16,int16_t speed_y_axis_16,int16_t speed_z_axis_16,int16_t yaw_16)
{
	rt_tar.st_data.rol = 0;
	rt_tar.st_data.pit = 0;
	rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
			//这里会把实时XYZ-YAW期望速度置零		
	rt_tar.st_data.yaw_dps=yaw_16;// yaw_16;
	rt_tar.st_data.vel_x =speed_x_axis_16;//speed_x_axis_16;
	rt_tar.st_data.vel_y =speed_y_axis_16;//
	rt_tar.st_data.vel_z =speed_z_axis_16;
	dt.fun[0x41].WTS = 1; //将要发送rt_tar数据。
}





void task1_UserTask_OneKeyCmd(void);
void stop_basket(void)
{
	steering_pd12=0;
	steering_pd13=0;
	
}

void up_basket(void)
{
	steering_pd12=1;
	steering_pd13=0;
}


void down_basket(void)
{
	steering_pd12=0;
	steering_pd13=1;
}



///////////////////////////////////
void sow_seed(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_15);//GPIOF9,F10设置高，灯灭
	light_flag=1;
	
//	MyDelayMs(500);
//	
//	GPIO_ResetBits(GPIOD,GPIO_Pin_15);//GPIOF9,F10设置高，灯灭
//	light_flag=0;
}

int find_target(float target_x,float target_y,float target_z)
{

	if (((plant_x>=(target_x-0.2f))&&(plant_x<=(target_x+0.2f)))&&((plant_y>(target_y-0.2f))&&(plant_y<=(target_y+0.2f))))//uwb的误差带由原来的15->20;
		{
			sow_seed();
			index_sow_i=0;
			
			uart2_openmv();
			if(pole_x!=0&&pole_y!=0)
			{
				if(155<=pole_x&&pole_x<=165&&115<=pole_y&&pole_y<=125)
				{
					sprintf(buf1,"[s9]到达第一个区域");//\[b1] 欢迎光临，请进
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					
					LxStringSend(1,"到达第一个区域，准备下降高度");
					return 1;
				}
				else
				{
					/*
						用openmv做视觉判断，如果目标点位置在图像中心的前方，那么x轴正速度，如果目标点在x轴后方，给x轴负速度
						y轴同理。
					*/
					speed_x_axis = pole_y-120;
					if(speed_x_axis>=10) speed_x_axis = 5;
					else if(5<speed_x_axis&&speed_x_axis<10) speed_x_axis = 1;
					else speed_x_axis = 1;
					if(speed_x_axis<=-10) speed_x_axis = -5;
					else if(-10<speed_x_axis&&speed_x_axis<=-5)speed_x_axis = -1;
					else speed_x_axis = -1;
					speed_x_axis_16 = (int16_t)speed_x_axis;
					
					speed_y_axis = 160-pole_x;
					if(speed_y_axis>=10) speed_y_axis = 5;
					else if(5<speed_y_axis&&speed_y_axis<10) speed_y_axis = 2;
					else speed_y_axis = 1;
					if(speed_y_axis<=-10) speed_y_axis = -5;
					else if(-10<speed_y_axis&&speed_y_axis<=-5)speed_y_axis = -2;
					else speed_y_axis = -1;
					speed_y_axis_16 = (int16_t)speed_y_axis;
					
					if(three_yaw_xm*standard_yaw>0) 
					{
						change_yaw = three_yaw_xm-standard_yaw;
						yaw_16 = (int16_t)change_yaw;
					}
					else
					{
						if(three_yaw_xm<standard_yaw)
						{
							yaw_16 = 5;
						}
						else
						{
							yaw_16 = -5;
						}
					}
					
					speed_z_axis=p_altitude*(target_z-alt_add_xm);//PID高度控制
					speed_z_axis_16=(int16_t) speed_z_axis;
					
					cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
					return 0;
				}		
		 }
	 }
		 else
		 {
			dis_sonic=sum_x_aa;		
			speed_x_axis=p_longitude*(target_x-plant_x);//PIDX轴控制
			speed_x_axis_16=(int16_t) speed_x_axis;
			if(speed_x_axis_16>20)
			{
				speed_x_axis_16=10;
			}
			if(speed_x_axis_16<-20)
			{
				speed_x_axis_16=-15;
			}
			
			if((speed_x_axis_16<5)&&(speed_x_axis_16>0))
			{
				speed_x_axis_16=4;
			}
			
			if((speed_x_axis_16<0)&&(speed_x_axis_16>-5))
			{
				speed_x_axis_16=-4;
			}
			
			speed_y_axis=p_longitude*(plant_y-target_y);//PIDY轴控制  act_y-plant_y
			speed_y_axis_16=(int16_t) speed_y_axis;
			if(speed_y_axis_16>20)
			{
				speed_y_axis_16=10;
			}
			if(speed_y_axis_16<-20)
			{
				speed_y_axis_16=-15;
			}
			
			
			if((speed_y_axis_16<5)&&(speed_y_axis_16>0))
			{
				speed_y_axis_16=4;
			}
			
			if((speed_y_axis_16<0)&&(speed_y_axis_16>-5))
			{
				speed_y_axis_16=-4;
			}
	
			speed_z_axis=p_altitude*(target_z-alt_add_xm);//PID高度控制
			speed_z_axis_16=(int16_t) speed_z_axis;
			
			if(three_yaw_xm*standard_yaw>0) 
			{
				change_yaw = three_yaw_xm-standard_yaw;
				yaw_16 = (int16_t)change_yaw;
			}
			else
			{
				if(three_yaw_xm<standard_yaw)
				{
					yaw_16 = 5;
				}
				else
				{
					yaw_16 = -5;
				}
			}
			
			cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
			
			if(time_dly_cnt_ms_xm%300==0)
			{
				if((speed_x_axis_16>0)&&(speed_y_axis_16>0))//右手定理
				{
					LxStringSend(1,"前进+1,向左+1");
					sprintf(buf1,"[s9]前左");//\[b1] 欢迎光临，请进
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
				else if((speed_x_axis_16>0)&&(speed_y_axis_16<0))
				{
					LxStringSend(1,"前进+1,向右+1");
					sprintf(buf1,"[s9]前右");//\[b1] 欢迎光临，请进
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
				else if((speed_x_axis_16<0)&&(speed_y_axis_16>0))
				{
					LxStringSend(1,"后退+1,向左+1");
					sprintf(buf1,"[s9]后左");//\[b1] 欢迎光临，请进
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
				else if((speed_x_axis_16<0)&&(speed_y_axis_16<0))
				{
					LxStringSend(1,"后退+1,向右+1");
					sprintf(buf1,"[s9]后右");//\[b1] 欢迎光临，请进
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
			}
			return 0;
		}				
}

/////////////////////////////////////////////////////////////////////////////////////////////
//解析数据
/////////////////////////////////////////////////////////////////////////////////////////

void uart3_camera_command_analyse(void)
{
	
	if( rx_end_flag==0x01)
	{
		
		int n2 = sscanf((char*)rx_buff,"$KT%c, %lf,%lf, %lf ", &type,  &plant_x_init, &plant_y_init, &plant_z);
/*		
		uwb拟合曲线在此处修正：
		plant_x =pow(plant_x_init,4)*pow(plant_x_init,3);
		
		plant_y =plant_y_init;
*/
		rx_end_flag=0;
		first_frame_end=0;
	}
		
}	

void uart2_openmv(void)
{
	if(rx_end_flag==0x01)
	{		
		if(rx_buff[1]==0xf0)//ploe
		{
			pole_x=(rx_buff[3]<<8|rx_buff[4]);//YAW，PITCH,ROLL为真实值的100倍
			pole_y=(rx_buff[5]<<8|rx_buff[6]);
			pole_w=(rx_buff[7]<<8|rx_buff[8]);
		}
		
		if(rx_buff[1]==0xf1)//line
		{
			line_x=(rx_buff[3]<<8|rx_buff[4]);//YAW，PITCH,ROLL为真实值的100倍
			line_y=(rx_buff[5]<<8|rx_buff[6]);//YAW，PITCH,ROLL为真实值的100倍
			line_sita=(rx_buff[7]<<8|rx_buff[8]);
		}
		
		rx_end_flag=0;
		first_frame_end=0;
	}			
}
/*--------------------------------------------作业1----------------------------------------------------------*/

void UserTask_task_one(void)
{
	m1_step =0x01;//在没有按键信号的时候直接跳转到起飞界面
	switch(m1_step)
	{
		case 0:
			//reset
			if(rx_end_flag_com1)
			{
				rx_end_flag_com1=0;
				position_1_order= rx_buff_com1[3];
				position_2_order= rx_buff_com1[4];
				
				tx1_buf_xm[0]=0xa5;
				tx1_buf_xm[1]=0x5a;
				tx1_buf_xm[2]=0x03;
				tx1_buf_xm[3]=0x00;
				tx1_buf_xm[4]=0xfd;
				
				DrvUart1SendBuf(tx1_buf_xm,5);
				
				m1_step=0x01;
				
				sprintf(buf1,"[s8]收到数据，准备前往%d和%d送货点",position_1_order,position_2_order);//飞控解锁
				speak_len1=strlen(buf1);
				speak_context((u8*)buf1,speak_len1);
			}
			break;
		case 1:
			//reset
			task1_UserTask_OneKeyCmd();
			break;
		default:
			break;
     }
}

/*--------------------------------------------作业1标记结束------------------------------------------------------*/



/*--------------------------------------------开始飞行作业-------------------------------------------------------*/
void task1_UserTask_OneKeyCmd(void)
{
    //一键起飞/降落例程
    //用静态变量记录一键起飞/降落指令已经执行。
    static u8 one_key_takeoff_f = 1, one_key_land_f = 1, one_key_mission_f = 0;//一键起飞，一键降落标志位
    static u8 last_switch=0,now_switch=0;

/*-----------------------------遥控器信号无需修改！！！-----------------------------*/
	
    //判断有遥控信号才执行
    if (rc_in.no_signal == 0)//收到信号标志位为0
    {
			  //判断第6通道拨杆位置 800<CH_6<1200 1000  c号开关拨到了1挡
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
        {
            //还没有执行
            if (one_key_land_f == 0)
            {
                //标记已经执行
                one_key_land_f =  OneKey_Land(); //执行一键降落
                 
            }
			now_switch=1;
		
			if(last_switch!=now_switch)
			{
				last_switch=now_switch;
				sprintf(buf1,"[x1] sound201 ");//\[b1] 欢迎光临，请进
				speak_len1=strlen(buf1);
				speak_context((u8*)buf1,speak_len1);
				
				LxStringSend(1,"1档");
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
			if (one_key_takeoff_f == 0)
			{	
				one_key_mission_f = 0;
				mission_step = 1;
				
				now_switch=2;
			
				if(last_switch!=now_switch)
				{
					last_switch=now_switch;
					sprintf(buf1,"[x1] sound203 ");//\[b1] 欢迎光临，请进
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					
					LxStringSend(1,"2档");
					first_a0_voice=1;
					
					find_pole_flag=0;
					first_frame_end=0;
					second_frame_end=0;
			
					cmd_send1(0,0,0,0);
				}	
			}						
        }
        else
        {
            //复位标记，以便再次执行
            one_key_takeoff_f = 0;
        }
    
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
		
/*--------------------------------无需修改！！！------------------------------*/
		
/*----------------------------飞行任务代码开始--------------------------------*/
		
		if(one_key_mission_f==1)
		{
			static int time_dly_cnt_ms;
			switch(mission_step)
			{
				case 0:
				{
					time_dly_cnt_ms = 0;
					first_a0_voice=1;
				}
				break;
				case 1:
				{
					mission_step=mission_step+1;
					first_a0_voice=1;
					cmd_send1(0,0,0,0);
				}
				break;
				case 2://解锁
					mission_step += FC_Unlock();
					if(first_a0_voice==1)
					{
						sprintf(buf1,"[s8]解锁");//飞控解锁
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						
						LxStringSend(1,"解锁");
						
						first_a0_voice=0;
					}
					first_a0_voice=1;
					break;
				case 3://等2秒
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
						if (time_dly_cnt_ms<1000&&time_dly_cnt_ms>100)
						{
							cmd_send1(0,0,0,0);
						}
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;
					}
					break;
				case 4: //模式切换
					mission_step += LX_Change_Mode(2);
				    time_dly_cnt_ms = 0;
					if(first_a0_voice==1)
					{
						sprintf(buf1,"[s9]模式2，z轴零速");//\[b1] 欢迎光临，请进
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						LxStringSend(1,"模式2，z轴零速");
						first_a0_voice=0;
					}
					first_a0_voice=1;			
					break;
				case 5://等2秒
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
						
						if (time_dly_cnt_ms<1000&&time_dly_cnt_ms>100)
						{
							cmd_send1(0,0,0,0);
						}
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;
					}					
					break;
				case 6://一键起飞		
					mission_step += OneKey_Takeoff(100);
					time_dly_cnt_ms = 0;
					if(first_a0_voice==1)
					{
						sprintf(buf1,"[s9]一键起飞");//\[b1] 欢迎光临，请进
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						LxStringSend(1,"一键起飞");
					}
					break;
				case 7://无人机起飞初始化
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
						if(time_dly_cnt_ms%100==0)
						{
							speed_y_axis_16=-10;
							speed_x_axis_16=0;

							standard_yaw = three_yaw_xm;
							
							if(three_yaw_xm*standard_yaw>0) 
							{
								change_yaw = three_yaw_xm-standard_yaw;
								yaw_16 = (int16_t)change_yaw;
							}
							else
							{
								if(three_yaw_xm<standard_yaw) yaw_16 = 5;
								else yaw_16 = -5;
							}
							
							speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//PID高度控制
							speed_z_axis_16=(int16_t) speed_z_axis;
							
							cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
						}
					}
					else
					{
						sprintf(buf1,"[s9]离开起飞点");//\[b1] 欢迎光临，请进
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						LxStringSend(1,"离开起飞点");
					
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;		
					}					
				break;
		    case 8://等2秒	
				wait_flag+=20;//2s	
				time_dly_cnt_ms_xm+=20;//ms
				if(time_dly_cnt_ms_xm>=10000)
				{
					time_dly_cnt_ms_xm=0;
				}
				
				uart3_camera_command_analyse();
				
				result_target=find_target(sow_piont[position_1_order].x,sow_piont[position_1_order].y,altitude_set);
				
				if(0==result_target)wait_flag=0;
				if(1==result_target&&wait_flag>=1000)
				{
					time_dly_cnt_ms = 0;
					mission_step += 1;
					first_a0_voice=1;
					time_dly_cnt_ms_xm=0;
					wait_flag=0;
					time=0;
				}
				break;	
			
			case 9://直接降低高度
			{
						time_dly_cnt_ms_xm+=20;//ms		
						if(time_dly_cnt_ms_xm%100==0)
						{
							//uart2_openmv();
							//停止区
							
							if(fabs(altitude_set_1-alt_add_xm)>=10)
							{
								speed_x_axis_16=0;
								speed_y_axis_16=0;
									
								speed_z_axis=p_altitude*(altitude_set_1-alt_add_xm);//int16_t
								
								if(three_yaw_xm*standard_yaw>0) 
								{
									change_yaw = three_yaw_xm-standard_yaw;
									yaw_16 = (int16_t)change_yaw;
								}
								else
								{
									if(three_yaw_xm<standard_yaw)
									{
										yaw_16 = 5;
									}
									else
									{
										yaw_16 = -5;
									}
								}
								
								speed_z_axis_16=(int16_t) speed_z_axis;
								
								cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
						
								if(altitude_set_1>alt_add_xm)
								{
									LxStringSend(1,"上升高度");
								}
								else
								{
									LxStringSend(1,"下降高度");
								}
							}
							else
							{
								LxStringSend(1,"到达指定高度，准备下放吊篮");
								
								time_dly_cnt_ms = 0;
								basic_step=0;
								time_dly_cnt_ms_xm=0;
								
								box_down_flag=0x00;
								box_count=0;
								time = 1;
							}
						}
							if(time)
							{
								wait_flag+=20;
								uart3_camera_command_analyse();
								result_target = find_target(sow_piont[position_1_order].x,sow_piont[position_1_order].y,altitude_set_1);
								if(result_target==0)wait_flag=0;
								if(result_target==1&&wait_flag>=1000)
								{	
									mission_step= mission_step+1;
									wait_flag=0;
									time=0;
								}
							}
					}
					break;		 
			case 10:   //收放吊篮
				{
				box_count++;
				time_dly_cnt_ms_xm++;
				if(box_count%1==0)//注意这里不是加20毫秒，而是加一
				{
					speed_x_axis_16=0;
					speed_y_axis_16=0;
					
					speed_z_axis=p_altitude*(altitude_set_1-alt_add_xm);//int16_t
				
					speed_z_axis_16=(int16_t) speed_z_axis;
					
					if(three_yaw_xm*standard_yaw>0) 
					{
						change_yaw = three_yaw_xm-standard_yaw;
						yaw_16 = (int16_t)change_yaw;
					}
					else
					{
						if(three_yaw_xm<standard_yaw)
						{
							yaw_16 = 5;
						}
						else
						{
							yaw_16 = -5;
						}
					}
					cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);	
					
					uart3_camera_command_analyse();
					
	
					result_target=find_target(sow_piont[position_1_order].x,sow_piont[position_1_order].y,altitude_set_1);
					if(1==result_target)
					{
						
					}
				}
			}
				if(box_down_flag==0x00)
				{
					box_down_flag=1;
					down_basket();
					LxStringSend(1,"下放吊篮，计时开始");
				}
				else
				{
					if(box_count>=290&&box_count<290+250)//5.秒下放吊篮时间，然后再悬停5秒
					{
						if(box_count==290)
						{
							stop_basket();
							
							LxStringSend(1,"停止下放吊篮，准备悬停5秒");
							
							sprintf(buf1,"[s9]停止下放吊篮，准备悬停5秒");//\[b1] 欢迎光临，请进
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
						else
						{
							stop_basket();
						}
							
					}
					else if(box_count>=290+250&&box_count<290+250+290)//5.8秒下放吊篮时间，然后再悬停5秒
					{
					
						up_basket();
						
						if(box_count==290+250)
						{
					
							LxStringSend(1,"悬停5秒时间到，准备上升吊篮");
							
							sprintf(buf1,"[s9]悬停5秒时间到，准备上升吊篮");//\[b1] 欢迎光临，请进
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
					}	
					else if(box_count>=290+250+290)//5.秒下放吊篮时间，然后再悬停5秒
					{
					
							stop_basket();
							LxStringSend(1,"上升5.8秒到，准备回复高度");
								
							sprintf(buf1,"[s9]上升5.8秒到，准备回复高度");//\[b1] 欢迎光临，请进
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
							
							mission_step= mission_step+1;
					//灭灯
							GPIO_ResetBits(GPIOD,GPIO_Pin_15);//GPIOF9,F10设置高，灯灭
							light_flag=0;
					//
							box_count=0;
							
							time_dly_cnt_ms = 0;
							mission_step= mission_step+1;
							basic_step=0;
							time_dly_cnt_ms_xm=0;
							
							box_down_flag=0x00;
							box_count=0;
					}
				}
		   break;
			
			
				case 11:
				{
						time_dly_cnt_ms_xm+=20;//ms		
						//回复1.5高度
						
						if(time_dly_cnt_ms_xm%100==0)
						{
							//uart2_openmv();
							//停止区
							
							if(fabs(altitude_set-alt_add_xm)>=10)
							{
									speed_x_axis_16=0;
									speed_y_axis_16=0;
									
									speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//int16_t
								
									speed_z_axis_16=(int16_t) speed_z_axis;
								
							if(three_yaw_xm*standard_yaw>0) 
							{
								change_yaw = three_yaw_xm-standard_yaw;
								yaw_16 = (int16_t)change_yaw;
							}
							else
							{
								if(three_yaw_xm<standard_yaw)
								{
									yaw_16 = 5;
								}
								else
								{
									yaw_16 = -5;
								}
							}
									cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
									LxStringSend(1,"上升高度");
							}
							else
							{
								LxStringSend(1,"到达1.5米高度，准备去下一个快递点");
								
								time_dly_cnt_ms = 0;
								mission_step= mission_step+1;
								basic_step=0;
								time_dly_cnt_ms_xm=0;
								
								box_down_flag=0x00;
								box_count=0;
								
								
								
								speed_x_axis_16=0;
								speed_y_axis_16=0;
								
								speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//int16_t
							
								speed_z_axis_16=(int16_t) speed_z_axis;
								
							if(three_yaw_xm*standard_yaw>0) 
							{
								change_yaw = three_yaw_xm-standard_yaw;
								yaw_16 = (int16_t)change_yaw;
							}
							else
							{
								if(three_yaw_xm<standard_yaw)
								{
									yaw_16 = 5;
								}
								else
								{
									yaw_16 = -5;
								}
							}							
								
							cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
							}
						}
					}
					break;			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
///////////              目前高度1.5米，执行下一个快递点                                  //////////////			
//////////////////////////case 从12开始////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
		    case 12:
				wait_flag+=20;
				time_dly_cnt_ms_xm+=20;//ms
				if(time_dly_cnt_ms_xm>=10000)
				{
					time_dly_cnt_ms_xm=0;
				}

				uart3_camera_command_analyse();
				
				result_target=find_target(sow_piont[position_2_order].x,sow_piont[position_2_order].y,altitude_set);
				if(0==result_target)wait_flag=0;
				if(1==result_target&&wait_flag>=2000)
				{
					time_dly_cnt_ms = 0;
					mission_step += 1;
					first_a0_voice=1;
					time_dly_cnt_ms_xm=0;
					wait_flag=0;
					time=0;
				}
				break;	
			case 13:
				{
						time_dly_cnt_ms_xm+=20;//ms		
						//直接降低高度
						if(time_dly_cnt_ms_xm%200==0)//每0.1s执行一次该程序
						{
							if(fabs(altitude_set_1-alt_add_xm)>=10)
							{
								speed_x_axis_16=0;
								speed_y_axis_16=0;
								speed_z_axis=p_altitude*(altitude_set_1-alt_add_xm);//int16_t							
								speed_z_axis_16=(int16_t) speed_z_axis;		
							if(three_yaw_xm*standard_yaw>0) 
							{
								change_yaw = three_yaw_xm-standard_yaw;
								yaw_16 = (int16_t)change_yaw;
							}
							else
							{
								if(three_yaw_xm<standard_yaw)
								{
									yaw_16 = 5;
								}
								else
								{
									yaw_16 = -5;
								}
							}						
								cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
								if(altitude_set_1>alt_add_xm)
								{
									LxStringSend(1,"上升高度");
								}
								else
								{
									LxStringSend(1,"下降高度");
								}
							}
							else
							{
								LxStringSend(1,"到达指定高度，准备下放吊篮");
								
								time_dly_cnt_ms = 0;
								basic_step=0;
								time_dly_cnt_ms_xm=0;
								
								box_down_flag=0x00;
								box_count=0;
								time=1;
							}
						}
						if(time)
						{
							wait_flag+=20;
							uart3_camera_command_analyse();
							result_target = find_target(sow_piont[position_1_order].x,sow_piont[position_1_order].y,altitude_set_1);
							if(result_target==0)wait_flag=0;
							if(result_target==1&&wait_flag>=1000)
							{
								mission_step= mission_step+1;
								wait_flag=0;
								time = 0;
							}
						}
				}
				break;	
					
			case 14://收放吊篮
			{
				box_count++;
				time_dly_cnt_ms_xm++;
				if(box_count%1==0)//注意这里不是加20毫秒，而是加一
				{
					speed_x_axis_16=0;
					speed_y_axis_16=0;
					
					speed_z_axis=p_altitude*(altitude_set_1-alt_add_xm);//int16_t
				
					speed_z_axis_16=(int16_t) speed_z_axis;
					
					if(three_yaw_xm*standard_yaw>0) 
					{
						change_yaw = three_yaw_xm-standard_yaw;
						yaw_16 = (int16_t)change_yaw;
					}
					else
					{
						if(three_yaw_xm<standard_yaw)
						{
							yaw_16 = 5;
						}
						else
						{
							yaw_16 = -5;
						}
					}	
					
					cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
					
					uart3_camera_command_analyse();

					result_target=find_target(sow_piont[position_2_order].x,sow_piont[position_2_order].y,altitude_set_1);
				}
				
				if(box_down_flag==0x00)
				{
					box_down_flag=1;
					down_basket();
					LxStringSend(1,"下放吊篮，计时开始");
				}
				else
				{
				if(box_count>=290&&box_count<290+250)//5.秒下放吊篮时间，然后再悬停5秒
				{
					if(box_count==290)
					{
						stop_basket();
						
						LxStringSend(1,"停止下放吊篮，准备悬停5秒");
						
						sprintf(buf1,"[s9]停止下放吊篮，准备悬停5秒");//\[b1] 欢迎光临，请进
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						
					}
					else
					{
						stop_basket();
					}
					
				}
				else if(box_count>=290+250&&box_count<290+250+290)//5.8秒下放吊篮时间，然后再悬停5秒
				{
					
					up_basket();//放下吊篮
					
					if(box_count==290+250)
					{
				
						LxStringSend(1,"悬停5秒时间到，准备上升吊篮");
						
						sprintf(buf1,"[s9]悬停5秒时间到，准备上升吊篮");//\[b1] 欢迎光临，请进
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
					}
				}	
				else if(box_count>=290+250+290)//5.秒下放吊篮时间，然后再悬停5秒
				{
				
						stop_basket();
						LxStringSend(1,"上升5.8秒到，准备回复高度");
							
						sprintf(buf1,"[s9]上升5.8秒到，准备回复高度");//\[b1] 欢迎光临，请进
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						
						mission_step= mission_step+1;
				//灭灯
						GPIO_ResetBits(GPIOD,GPIO_Pin_15);//GPIOF9,F10设置高，灯灭
						light_flag=0;
				//
						box_count=0;
						
						time_dly_cnt_ms = 0;
						mission_step= mission_step+1;
						basic_step=0;
						time_dly_cnt_ms_xm=0;
						
						box_down_flag=0x00;
						box_count=0;
					}
				}
			}
			
			
		   break;
			
			
				case 15://回复1.5高度
				{
						time_dly_cnt_ms_xm+=20;//ms		
						
						
						if(time_dly_cnt_ms_xm%100==0)
						{
							//uart2_openmv();
							//停止区
							
							if(fabs(altitude_set-alt_add_xm)>=10)
							{
								speed_x_axis_16=0;
								speed_y_axis_16=0;
								
								speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//int16_t
							
								speed_z_axis_16=(int16_t) speed_z_axis;
									
								if(three_yaw_xm*standard_yaw>0) 
								{
									change_yaw = three_yaw_xm-standard_yaw;
									yaw_16 = (int16_t)change_yaw;
								}
								else
								{
									if(three_yaw_xm<standard_yaw)
									{
										yaw_16 = 5;
									}
									else
									{
										yaw_16 = -5;
									}
								}
								cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
								if(altitude_set_1>alt_add_xm)
								{
									LxStringSend(1,"上升高度");
								}
								else
								{
									LxStringSend(1,"下降高度");
								}
							}
							else
							{
								LxStringSend(1,"到达1.5米高度，准备回家降落");
								
								time_dly_cnt_ms = 0;
								mission_step= mission_step+1;

								//	灭灯
								GPIO_ResetBits(GPIOD,GPIO_Pin_15);//GPIOF9,F10设置高，灯灭
								light_flag=0;
								basic_step=0;
								time_dly_cnt_ms_xm=0;
								
								box_down_flag=0x00;
								box_count=0;
								
								
								
								speed_x_axis_16=0;
								speed_y_axis_16=0;
								
								speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//int16_t
							
								speed_z_axis_16=(int16_t) speed_z_axis;
								
								if(three_yaw_xm*standard_yaw>0) 
								{
									change_yaw = three_yaw_xm-standard_yaw;
									yaw_16 = (int16_t)change_yaw;
								}
								else
								{
									if(three_yaw_xm<standard_yaw)
									{
										yaw_16 = 5;
									}
									else
									{
										yaw_16 = -5;
									}
								}
								cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
							}
						}
					}
				break;						
	/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
/////////////////////////////////////////////////////////////////////////////////////			
///////////              目前高度1.5米，准备回家降落                                  //////////////			
//////////////////////////case 从17开始////////////////////////////////////////			
		    case 16:
			{
				//等2秒
				/*以下的代码有问题，需要修正*/
					time_dly_cnt_ms_xm+=20;//ms
					if(time_dly_cnt_ms_xm>=10000)
					{
						time_dly_cnt_ms_xm=0;
					}
				/*---------------------------*/
					
					uart3_camera_command_analyse();
					
					if ((plant_x>=home_x-0.15f)&&(plant_x<=home_x+0.15f)&&(plant_y>home_y-0.15f)&&(plant_y<=home_y+0.15f))
					{
						sow_seed();
						index_sow_i=0;
						
						sprintf(buf1,"[s9]到达起降点，准备z轴0速");//\[b1] 欢迎光临，请进
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						
						
						LxStringSend(1,"到达起降点，准备z轴0速");
						
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;
						time_dly_cnt_ms_xm=0;
					 }
					 else
					 {
						dis_sonic=sum_x_aa;		
						speed_x_axis=p_longitude*(home_x-plant_x);//PIDX轴控制
						speed_x_axis_16=(int16_t) speed_x_axis;
						if(speed_x_axis_16>20)
						{
							speed_x_axis_16=15;
						}
						if(speed_x_axis_16<-20)
						{
							speed_x_axis_16=-15;
						}
						
						if((speed_x_axis_16<5)&&(speed_x_axis_16>0))
						{
							speed_x_axis_16=5;
						}
						
						if((speed_x_axis_16<0)&&(speed_x_axis_16>-5))
						{
							speed_x_axis_16=-5;
						}
						
						speed_y_axis=p_longitude*(plant_y-home_y);//PIDY轴控制  act_y-plant_y为啥是pidy轴控制
						speed_y_axis_16=(int16_t) speed_y_axis;
						if(speed_y_axis_16>20)
						{
							speed_y_axis_16=15;
						}
						if(speed_y_axis_16<-20)
						{
							speed_y_axis_16=-15;
						}
						
						
						if((speed_y_axis_16<5)&&(speed_y_axis_16>0))
						{
							speed_y_axis_16=5;
						}
						
						if((speed_y_axis_16<0)&&(speed_y_axis_16>-5))
						{
							speed_y_axis_16=-5;
						}
						
						if(three_yaw_xm*standard_yaw>0) 
						{
							change_yaw = three_yaw_xm-standard_yaw;
							yaw_16 = (int16_t)change_yaw;
						}
						else
						{
							if(three_yaw_xm<standard_yaw)
							{
								yaw_16 = 5;
							}
							else
							{
								yaw_16 = -5;
							}
						}
				
						speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//PID高度控制
						speed_z_axis_16=(int16_t) speed_z_axis;
					
						cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
						
						if(time_dly_cnt_ms_xm%300==0)
						{
							if((speed_x_axis_16>0)&&(speed_y_axis_16>0))//右手定理
							{
								LxStringSend(1,"前进+1,向左+1");
							}
							else if((speed_x_axis_16>0)&&(speed_y_axis_16<0))
							{
								LxStringSend(1,"前进+1,向右+1");
							}
							else if((speed_x_axis_16<0)&&(speed_y_axis_16>0))
							{
								LxStringSend(1,"后退+1,向左+1");
							}
							else if((speed_x_axis_16<0)&&(speed_y_axis_16<0))
							{
								LxStringSend(1,"后退+1,向右+1");
							}
							else
							{
								
							}

						}
								
					}			

				}
			
		   break;	
			case 17://z轴0速
				{
					time_dly_cnt_ms_xm+=20;//ms		
					
					
					if(time_dly_cnt_ms_xm%100==0) //任务每20ms进入一次，100/20=5；实际时间：5*20=100ms=0.1s
					{
						//uart2_openmv();
						//停止区
						speed_x_axis_16=0;
						speed_y_axis_16=0;
						
						speed_z_axis=0;//int16_t
					
						speed_z_axis_16=(int16_t) speed_z_axis;
						
							if(three_yaw_xm*standard_yaw>0) 
							{
								change_yaw = three_yaw_xm-standard_yaw;
								yaw_16 = (int16_t)change_yaw;
							}
							else
							{
								if(three_yaw_xm<standard_yaw)
								{
									yaw_16 = 5;
								}
								else
								{
									yaw_16 = -5;
								}
							}
						cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
					}

					if(time_dly_cnt_ms_xm>=1000)
					{
						LxStringSend(1,"z轴0速,准备一键降落");
					
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;
						time_dly_cnt_ms_xm=0;
					}	
					break;						
				}
			
	case 18://恢复1.5米高度
		{
			//执行一键降落
			OneKey_Land();
			
			time_dly_cnt_ms = 0;
			mission_step += 1;
//			uart3_camera_command_analyse();
//			if(plant_x >= 0.6f&&plant_x<=0.9f&&plant_y >= 0.6f&&plant_y<=0.9f)
//			{
//				if(
//				speed_x_axis_16 = 0;
//				speed_x_axis_16 =0;
//				speed_z_axis=-5;//int16_t
//			
//				speed_z_axis_16=(int16_t) speed_z_axis;
//				
//				rt_tar.st_data.rol = 0;
//				rt_tar.st_data.pit = 0;
//				rt_tar.st_data.thr = 0; //用于模式0，避免模式0时失控，油门过大飞跑，给一个稍低于中位的油门
//				//这里会把实时XYZ-YAW期望速度置零		
//				rt_tar.st_data.yaw_dps = 0;
//				rt_tar.st_data.vel_x =speed_x_axis_16;
//				rt_tar.st_data.vel_y =speed_y_axis_16;
//				rt_tar.st_data.vel_z = speed_z_axis_16;
//			}
					
			if(first_a0_voice==1)
			{
				sprintf(buf1,"[s9]降落");//\[b1] 欢迎光临，请进
				speak_len1=strlen(buf1);
				speak_context((u8*)buf1,speak_len1);
				
				LxStringSend(1,"降落");
				
				first_a0_voice=0;
			}
			
		}
		break;			
	case 19:
		{
			//执行一键降落
			
				time_dly_cnt_ms+=20;//ms
				first_a0_voice=0;
		}
		break;
		case 20:
		{
			time_dly_cnt_ms+=20;//ms
		}
		break;				
		default:
			break;
	}
		}
	}
	else
	{
		mission_step = 0;
	}
		
}
    ////////////////////////////////////////////////////////////////////////



