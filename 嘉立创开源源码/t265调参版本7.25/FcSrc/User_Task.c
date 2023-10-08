#include "User_Task.h"
#include "Drv_RcIn.h"
#include "LX_FC_Fun.h"
#include "Info.h"
//#include "PID.h"
#include "ANO_DT_LX.h"
#include "ANO_LX.h"
#include "Drv_Led.h"
#include "T265_Sensor.h"
#include "Ano_math.h"
#include "Drv_Uart.h"
#include "Fly_Task.h"
#include "Expansion_board_RXSD.h"


static s16 mission_step;  
static s16 home_pos_xy[2];
static s16 Recover_place[2];
static s16 work_place[12][2]={{320,0},{320,-400},{0,-400},{0,-320},{240,-320},{240,-240},{0,-240},{0,-160},{240,-160},{240,-80},{0,-80},
{0,0}};

void UserTask_OneKeyCmd(void)
{
		
		static u8 once_flag1=1;
		static u8 once_flag2=1;
		static u8 once_flag4=1;
		static u16 time_dly_cnt_ms2=0;
		if(User.Flight.Camera_Flag == 1 && once_flag4 == 1){
//			Expansion_board_LED(1);
			time_dly_cnt_ms2+=20;
			if(time_dly_cnt_ms2== 500){
	//			Expansion_board_LED(0);
				if(User.Flight.T265_Flag == 0){
					once_flag4=0;
				}
				else{
					if(time_dly_cnt_ms2==1000){
			//			Expansion_board_LED(1);
					}
					else if(time_dly_cnt_ms2==1500){
			//			Expansion_board_LED(0);
						once_flag4=0;
					}
				}
			}
		}
    //////////////////////////////////////////////////////////////////////
    //һ�����/��������
    //////////////////////////////////////////////////////////////////////
    //�þ�̬������¼һ�����/����ָ���Ѿ�ִ�С�
    static u8   one_key_land_f = 1, one_key_mission_f = 0;
   
    //�ж���ң���źŲ�ִ��
    if (rc_in.no_signal == 0)
    {
        //�жϵ�6ͨ������λ�� 800<CH_6<1200
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
        {
            //��û��ִ��
            if (one_key_land_f == 0)
            {
							User.Flight.FireFinding_Flag=0;
							User.Flight.keep_yaw = 0;
							rt_tar.st_data.vel_x = 0;								
					    User.Flight.keep_height = 0;
							rt_tar.st_data.vel_y = 0;		
                //����Ѿ�ִ��
              one_key_land_f =
                    //ִ��һ������
                   OneKey_Land();
					
            }
        }
        else
        {
            //��λ��ǣ��Ա��ٴ�ִ��
            one_key_land_f = 0;
        }
      	
        //�жϵ�6ͨ������λ�� 1700<CH_6<2200
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1700 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 2200)
        {
            //��û��ִ��
            if (one_key_mission_f == 0)
            {
                //����Ѿ�ִ��
							one_key_mission_f = 1;
								//��ʼ����
							mission_step = 1;
            }
        }
        else
        {

							one_key_mission_f = 0;				
							//��λ��ǣ��Ա��ٴ�ִ��
        }
				
				//------------------------------------------------
       if(one_key_mission_f==1 && User.Flight.T265_Flag ==1)
		{
			User.Flight.mission_step_test=mission_step;
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
					//�л����̿�ģʽ
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += LX_Change_Mode(2);
					}
				}
				break;
				case 2:
				{
					//����
					mission_step += FC_Unlock();
				}
				break;
				case 3:
				{
					//��2��
					RecordHome(T265.pose_x_cm,T265.pose_y_cm);
					home_pos_xy[0]=T265.pose_x_cm;
					home_pos_xy[1]=T265.pose_y_cm;
					User.Flight.YAW_Start=User.Flight.YAW;
					if(time_dly_cnt_ms<1000)
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
					User.Flight.keep_yaw =0;
					rt_tar.st_data.vel_x = 0 ;      //
					rt_tar.st_data.vel_y = 0 ;
					User.Flight.keep_height = 0; //���� ��ʼ��
					User.Flight.place=0;
					rt_tar.st_data.yaw_dps=0;
					User.Flight.target_point[0]=home_pos_xy[0];
					User.Flight.target_point[1]=home_pos_xy[1];
					User.Flight.pointfly=0;
					User.Flight.keep_yaw=1;
					//���
					mission_step += OneKey_Takeoff(180);
				}
				break;
				case 5:
				{
					//��ʱ1s
					if(time_dly_cnt_ms<1500)
					{
						
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						//User.Flight.keep_yaw=1;
						time_dly_cnt_ms  = 0;
						mission_step++;
					}
				}
				break;
				case 6:
				{
					User.Flight.target_alt_cm=180;
					User.Flight.keep_height=1;
					mission_step+=Height_Control();
					//Height_Control();
					//mission_step++;
				}
				break;
				
				case 7:
				{	
					User.Flight.FireFinding_Flag=1;
					if(User.Flight.Success_Find == 0){
						User.Flight.pointfly=1;
						if(PointFly_PID(work_place[User.Flight.place][0],work_place[User.Flight.place][1])){
							
							User.Flight.place++;
							if(User.Flight.place==11){
								mission_step=200;
						}
						}
						else{
							User.Flight.Fly_x=work_place[User.Flight.place][0];
							User.Flight.Fly_y=work_place[User.Flight.place][1];
						
						}
					}
					else{
			//			Expansion_board_LED(1);
						Recover_place[0]=T265.pose_x_cm;
						Recover_place[1]=T265.pose_y_cm;
						mission_step++;
					}
				}
				break;
				case 8:
				{
					if(Fire_Finding()){
						User.Flight.keep_point=1;//-----------------���ǰѱ��ֵ㺯������һֱ�����ģ�
					}
					if(User.Flight.keep_point == 1){
						time_dly_cnt_ms+=20;
						if(time_dly_cnt_ms >= 500){
							User.Flight.target_alt_cm=100;
							if(Height_Control() == 1){
								mission_step+=1;
								time_dly_cnt_ms=0;
							}
						}
					}
				}
				break;
				case 9:
				{
					if(once_flag1){
						once_flag1=0;;
					}
					if(time_dly_cnt_ms<3000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						if(once_flag2--){
							Expansion_board_Page(1);
						}
						//User.Flight.keep_yaw=1;
						if(User.Flight.Page_OK_Flag == 1){
							User.Flight.Send_Fire_Location = 1;
							time_dly_cnt_ms  = 0;
							mission_step++;
						}
					}
				}
				break;
				case 10:
				{
					User.Flight.target_alt_cm=180;
					mission_step+=Height_Control();
					User.Flight.FireFinding_Flag=0;
				}
				break;
				
				case 11:
				{
					User.Flight.keep_point=0;
					//Pole_Find();
	//				Expansion_board_LED(0);
					if(PointFly_PID(Recover_place[0],Recover_place[1])){
						mission_step++;
					}
				}
				break;
				case 12:
				{
					if(PointFly_PID(work_place[User.Flight.place][0],work_place[User.Flight.place][1])){
							User.Flight.place++;
						if(User.Flight.place== 11 ){
							mission_step=200;
						}
					}
				}
				break;
				case 13:
				{
					
					
				}
				break;
				case 14:
				{
				
				}
				break;
				case 17:
				{
				//	User.Flight.keep_yaw =1;
			//		if(ABS(User.Flight.YAW-User.Flight.YAW_Start)<5){
						mission_step+=PointFly_PID(home_pos_xy[0],home_pos_xy[1]);
				//	}
				}
					
				break;
        case 18:
				{
					
					
					
				}
				break;
				
				case 200:
				{ 
					
					mission_step += PointFly_PID(home_pos_xy[0],home_pos_xy[1]);
				}
				break;
				case 201:
				{
					User.Flight.keep_height = 0;
					mission_step+=OneKey_Land();
				}
				break;
				default:{
				
				}
					break;
			}
	}

		else
		{
			mission_step = 0;
		}
	}
    }
    ////////////////////////////////////////////////////////////////////////
		
		
		
		
		
		
		
		
void UserTask_OneKeyCmd_Key(void)
{
		
		static u8 once_flag1=1;
		static u8 once_flag2=1;
		static u8 once_flag3=1;
    //////////////////////////////////////////////////////////////////////
    //һ�����/��������
    //////////////////////////////////////////////////////////////////////
    //�þ�̬������¼һ�����/����ָ���Ѿ�ִ�С�
   static u8 once_flag4=1;
		static u16 time_dly_cnt_ms2=0;
		if(User.Flight.Camera_Flag == 1 && once_flag4 == 1){
			//Expansion_board_LED(1);
			time_dly_cnt_ms2+=20;
			if(time_dly_cnt_ms2== 500){
			//	Expansion_board_LED(0);
				if(User.Flight.T265_Flag == 0){
					once_flag4=0;
				}
				else{
					if(time_dly_cnt_ms2==1000){
			//			Expansion_board_LED(1);
					}
					else if(time_dly_cnt_ms2==1500){
			//			Expansion_board_LED(0);
						once_flag4=0;
					}
				}
			}
		}
    if(once_flag3){
			once_flag3=0;
			mission_step=1;
			User.Flight.FireFinding_Flag=0;
			User.Flight.keep_yaw = 0;
			rt_tar.st_data.vel_x = 0;
			User.Flight.keep_height = 0;
			rt_tar.st_data.vel_y = 0;	
		}
      	
       
				//------------------------------------------------
       if( User.Flight.T265_Flag ==1 && User.Flight.key ==1)
		{
			User.Flight.mission_step_test=mission_step;
			static u16 time_dly_cnt_ms = 0;
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
					//�л����̿�ģʽ
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						time_dly_cnt_ms = 0;
						mission_step += LX_Change_Mode(2);
					}
				}
				break;
				case 2:
				{
					//����
					mission_step += FC_Unlock();
				}
				break;
				case 3:
				{
					//��2��
					RecordHome(T265.pose_x_cm,T265.pose_y_cm);
					home_pos_xy[0]=T265.pose_x_cm;
					home_pos_xy[1]=T265.pose_y_cm;
					User.Flight.YAW_Start=User.Flight.YAW;
					if(time_dly_cnt_ms<1000)
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
					User.Flight.keep_yaw =0;
					rt_tar.st_data.vel_x = 0 ;      //
					rt_tar.st_data.vel_y = 0 ;
					User.Flight.keep_height = 0; //���� ��ʼ��
					User.Flight.place=0;
					rt_tar.st_data.yaw_dps=0;
					User.Flight.target_point[0]=home_pos_xy[0];
					User.Flight.target_point[1]=home_pos_xy[1];
					User.Flight.pointfly=0;
					User.Flight.keep_yaw=1;
					//���
					mission_step += OneKey_Takeoff(180);
				}
				break;
				case 5:
				{
					//��ʱ1s
					if(time_dly_cnt_ms<1500)
					{
						
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						//User.Flight.keep_yaw=1;
						time_dly_cnt_ms  = 0;
						mission_step++;
					}
				}
				break;
				case 6:
				{
					User.Flight.target_alt_cm=180;
					User.Flight.keep_height=1;
					mission_step+=Height_Control();
					//Height_Control();
					//mission_step++;
				}
				break;
				
				case 7:
				{	
					User.Flight.FireFinding_Flag=1;
					if(User.Flight.Success_Find == 0){
						User.Flight.pointfly=1;
						if(PointFly_PID(work_place[User.Flight.place][0],work_place[User.Flight.place][1])){
							
							User.Flight.place++;
							if(User.Flight.place==11){
								mission_step=200;
						}
						}
						else{
							User.Flight.Fly_x=work_place[User.Flight.place][0];
							User.Flight.Fly_y=work_place[User.Flight.place][1];
						
						}
					}
					else{
				//		Expansion_board_LED(1);
						Recover_place[0]=T265.pose_x_cm;
						Recover_place[1]=T265.pose_y_cm;
						mission_step++;
					}
				}
				break;
				case 8:
				{
					if(Fire_Finding()){
						User.Flight.keep_point=1;//-----------------���ǰѱ��ֵ㺯������һֱ�����ģ�
					}
					if(User.Flight.keep_point == 1){
						time_dly_cnt_ms+=20;
						if(time_dly_cnt_ms >= 500){
							User.Flight.target_alt_cm=100;
							if(Height_Control() == 1){
								mission_step+=1;
								time_dly_cnt_ms=0;
							}
						}
					}
				}
				break;
				case 9:
				{
					if(once_flag1){
						once_flag1=0;;
					}
					if(time_dly_cnt_ms<3000)
					{
						time_dly_cnt_ms+=20;//ms
					}
					else
					{
						if(once_flag2--){
							Expansion_board_Page(1);
						}
						//User.Flight.keep_yaw=1;
						if(User.Flight.Page_OK_Flag == 1){
							User.Flight.Send_Fire_Location = 1;
							time_dly_cnt_ms  = 0;
							mission_step++;
						}
					}
				}
				break;
				case 10:
				{
					if(time_dly_cnt_ms<500){
						time_dly_cnt_ms+=20;
					}
					else{
						time_dly_cnt_ms=0;
						mission_step++;
					}
				}
					break;
				case 11:
				{
					User.Flight.target_alt_cm=180;
					mission_step+=Height_Control();
					User.Flight.FireFinding_Flag=0;
				}
				break;
				
				case 12:
				{
					User.Flight.keep_point=0;
					//Pole_Find();
			//		Expansion_board_LED(0);
					if(PointFly_PID(Recover_place[0],Recover_place[1])){
						mission_step++;
					}
				}
				break;
				case 13:
				{
					if(PointFly_PID(work_place[User.Flight.place][0],work_place[User.Flight.place][1])){
							User.Flight.place++;
						if(User.Flight.place== 11 ){
							mission_step=200;
						}
					}
				}
				break;
				case 14:
				{
					
					
				}
				break;
				case 15:
				{
				
				}
				break;
				case 17:
				{
				//	User.Flight.keep_yaw =1;
			//		if(ABS(User.Flight.YAW-User.Flight.YAW_Start)<5){
						mission_step+=PointFly_PID(home_pos_xy[0],home_pos_xy[1]);
				//	}
				}
					
				break;
        case 18:
				{
					
					
					
				}
				break;
				
				case 200:
				{ 
					
					mission_step += PointFly_PID(home_pos_xy[0],home_pos_xy[1]);
				}
				break;
				case 201:
				{
					User.Flight.keep_height = 0;
					mission_step+=OneKey_Land();
				}
				break;
				default:{
				
				}
					break;
			}
	}

		else
		{
			mission_step = 0;
		}
	}
    
		
		
		
		
		
		
		

		
		

