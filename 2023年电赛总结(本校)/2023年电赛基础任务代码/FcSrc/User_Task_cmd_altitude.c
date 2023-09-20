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
    //һ�����/��������
    //////////////////////////////////////////////////////////////////////
    //�þ�̬������¼һ�����/����ָ���Ѿ�ִ�С�
    static u8 one_key_takeoff_f = 1, one_key_land_f = 1, one_key_mission_f = 0;
    static u8 mission_step, last_switch=0,now_switch=0;
	
    //�ж���ң���źŲ�ִ��
    if (rc_in.no_signal == 0)
    {
        
			
			  //�жϵ�6ͨ������λ�� 800<CH_6<1200 1000  c�ſ��ز�����1��
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
        {
            //��û��ִ��
            if (one_key_land_f == 0)
            {
                //����Ѿ�ִ��
                one_key_land_f =
                    //ִ��һ������
                    OneKey_Land();
            }
						now_switch=1;
					
						if(last_switch!=now_switch)
						{
							last_switch=now_switch;
							sprintf(buf1,"[x1] sound201 ");//\[b1] ��ӭ���٣����
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
        }
        else
        {
            //��λ��ǣ��Ա��ٴ�ִ��
            one_key_land_f = 0;
        }
			
			
			
			
			
			
			
			
			
			
			
			//�жϵ�6ͨ������λ�� 1300<CH_6<1700  1500   c�ſ��ز�����2��
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 1300 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1700)
        {
            //��û��ִ��
//            if (one_key_takeoff_f == 0)
//            {
//                //����Ѿ�ִ��
//                one_key_takeoff_f =
//                    //ִ��һ�����
//                    OneKey_Takeoff(100); //������λ�����ף� 0��Ĭ����λ�����õĸ߶ȡ�
//            }
					
					if (one_key_takeoff_f == 0)
					{	
						
						
//						rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
//						//������ʵʱXYZ-YAW�����ٶ�����		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =0;
//						rt_tar.st_data.vel_y =20;
//						rt_tar.st_data.vel_z = 20;

//							
//					 dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�	
						
						
						
						one_key_mission_f = 0;
						mission_step = 1;
						
						
						now_switch=2;
					
						if(last_switch!=now_switch)
						{
							last_switch=now_switch;
							sprintf(buf1,"[x1] sound203 ");//\[b1] ��ӭ���٣����
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
						
							
						
						
				}
					
					
										
        }
        else
        {
            //��λ��ǣ��Ա��ٴ�ִ��
            one_key_takeoff_f = 0;
        }
        //
    
	//�жϵ�6ͨ������λ�� 1700<CH_6<2200  c�ſ��ز���������
		if(rc_in.rc_ch.st_data.ch_[ch_6_aux2]>1700 && rc_in.rc_ch.st_data.ch_[ch_6_aux2]<2200)
		{
			//��û��ִ��
			if(one_key_mission_f ==0)
			{
				//����Ѿ�ִ��
				one_key_mission_f = 1;
				//��ʼ����
				mission_step = 1;
				//���Բ�������
				
			}
			
			now_switch=3;
			last_switch=3;
			
		}
		else
		{
			//��λ��ǣ��Ա��ٴ�ִ��
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
					//�л��̿�ģʽ
					//mission_step += LX_Change_Mode(3);
					mission_step=mission_step+1;
				}
				break;
				case 2:
				{
					//����
					mission_step += FC_Unlock();
					//buf1[]={"[s9]����sound223 "};//\[b1] ��ӭ���٣����
					
					sprintf(buf1,"[s8]����");//\[b1] ��ӭ���٣����
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
				break;
				case 3:
				{
					//��2��
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
					//���
					mission_step += OneKey_Takeoff(100);//������λ�����ף� 0��Ĭ����λ�����õĸ߶ȡ�
					
					//buf1[]={"[s9]���sound223 "};//\[b1] ��ӭ���٣����
					
					sprintf(buf1,"���");//\[b1] ��ӭ���٣����
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					
				}
				break;
				case 5:
				{
					//��10��
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
					//ǰ��1��
					mission_step += LX_Change_Mode(3);
//					mission_step += 1;
					//buf1[]={"[s9]ģʽ2sound223 "};//\[b1] ��ӭ���٣����
					
					sprintf(buf1,"[s9]ģʽ3");//\[b1] ��ӭ���٣����
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
				}
				break;	
				case 7:
				{
					//��10��
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
					//ǰ��1��
					//ission_step += Horizontal_Move(100,150,0);
						mission_step +=target_altituded(150);
					
					
					
//						rt_tar.st_data.rol = 0;
//						rt_tar.st_data.pit = 0;
//						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
//						//������ʵʱXYZ-YAW�����ٶ�����		
//						rt_tar.st_data.yaw_dps = 0;
//						rt_tar.st_data.vel_x =20;
//						rt_tar.st_data.vel_y =0;
//						rt_tar.st_data.vel_z = 20;

//							
//						dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�	
					
						time_dly_cnt_ms = 0;
//						mission_step += 1;
					
						//buf1[]={"[s9]45��б��sound223 "};//\[b1] ��ӭ���٣����
						
						sprintf(buf1,"[s9]�߶�����");//\[b1] ��ӭ���٣����
		
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
					
					
					
					
					
				}
				break;	
				case 9:
				{
					//��10��
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
					//����1��
					//mission_step += Horizontal_Move(100,150,90);
					//ִ��һ������
					//OneKey_Land();	
				
					
					
					
						rt_tar.st_data.rol = 0;
						rt_tar.st_data.pit = 0;
						rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
						//������ʵʱXYZ-YAW�����ٶ�����		
						rt_tar.st_data.yaw_dps = 0;
						rt_tar.st_data.vel_x =0;
						rt_tar.st_data.vel_y =0;
						rt_tar.st_data.vel_z = 0;

							
						dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�	
					
						time_dly_cnt_ms = 0;
						mission_step += 1;
					
						//buf1[]={"[s9]z������sound223 "};//\[b1] ��ӭ���٣����
						
						sprintf(buf1,"[s9]]z������");//\[b1] ��ӭ���٣����
	
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
					
					
				}
				break;
				
				case 11:
				{
					//��10��
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
					//����1��
					//mission_step += Horizontal_Move(100,150,90);
					//ִ��һ������
					OneKey_Land();

					//buf1[]={"[s9]����sound223 "};//\[b1] ��ӭ���٣����
					
					sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
	
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					mission_step += 1;
					
						
					
					
				}
				break;
				
				
				
				
//				case 9:
//				{
//					//��10��
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
//					//ִ��һ������
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
