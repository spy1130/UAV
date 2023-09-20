#include "User_Task.h"
#include "Drv_RcIn.h"
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"                  // Device header

#include "Drv_Uart.h"


#include "stm32f4xx_gpio.h"

#include "LX_FC_Fun.h"
#include "ANO_DT_LX.h"
#include "main.h"

#include "stdio.h"

#include <string.h>
#include <math.h>//�������Ǻ���
#include "main.h"

#include "User_Task.h"
#include <stdlib.h>//�������Ǻ���
#include "Drv_Sys.h"

#include "Drv_Uart.h"
#include "I2C_Init.h"


extern float sum_x_aa;
extern u8 m1_step,m2_step,m3_step,m4_step;
extern u8 rx_buff_com1[20];
char flag=0x00;

struct point
{
	float x;
	float y;
};

struct point sow_piont[12]={{0.6,4.4},{3.6,4.4},{3.6,3.6},{1.2,3.6},{1.2,2.8},{3.6,2.8},{3.6,2},{1.2,2},{1.2,1.2},{3.6,1.2},{3.6,0.4},{0.6,0.6}};

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
	
int steering_pwmval=1500;
	
	
float altitude_set=100,p_altitude=1.0,speed_z_axis=0,speed_x_axis=0,speed_y_axis=0,p_longitude=10.0;//p_longitudeԭ����ֵΪ10
	
float altitude_set_1=100;

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

unsigned char return_flag=0;//��ȡopenmv�ķ���ֵ������ҵ�����Դͷ�򷵻�1���ҵ���ɽ����ͷ���2
unsigned char done_flag=0;//���������ɱ�־λ


u8 position_1_order=0x00;
u8 position_2_order=0x00;
u8 tx1_buf_xm[6]={0};

int box_down_flag=0x00;
int box_count=0,result_target=0;

int down_count=0x00;
u8 	down_flag=0x00;
unsigned char fire_flag=0x00;

int	up_count=0x00;
u8 	up_flag=0x00;

int record_cnt=0x00,record_arry[10]={0},start_iden_flag=0x00,m2_time_cnt=0x00;//;
int time;
int distance_x,distance_y;//����

unsigned char transition=0x00;

void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  //ʹ��GPIO����ʱ�ӣ��ҵ�c8t6��������ӳ�䣬����AFIO���ù���ģ��ʱ��
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
		
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = 20000-1; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =72; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�
	
	//��ʼ��TIM3 Channel 1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OCInitStructure.TIM_Pulse=900;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM3
}


void cmd_send1(int16_t speed_x_axis_16,int16_t speed_y_axis_16,int16_t speed_z_axis_16,int16_t yaw_16)
{
	rt_tar.st_data.rol = 0;
	rt_tar.st_data.pit = 0;
	rt_tar.st_data.thr = 0; //����ģʽ0������ģʽ0ʱʧ�أ����Ź�����ܣ���һ���Ե�����λ������
			//������ʵʱXYZ-YAW�����ٶ�����		
	rt_tar.st_data.yaw_dps=yaw_16;// yaw_16;
	rt_tar.st_data.vel_x =speed_x_axis_16;//speed_x_axis_16;
	rt_tar.st_data.vel_y =speed_y_axis_16;//
	rt_tar.st_data.vel_z =speed_z_axis_16;
	dt.fun[0x41].WTS = 1; //��Ҫ����rt_tar���ݡ�
}

void task1_UserTask_OneKeyCmd(void);

void stop_basket(void)
{
	steering_pwmval=1500;//high mean low speed
	TIM_SetCompare1(TIM4,steering_pwmval);
	
	up_count=0;
	down_count=0;
	up_flag=0;
	down_flag=0;
}

void up_basket(void)
{
	if(up_flag==00)
	{
		up_flag=0x01;
		steering_pwmval=1500-200;//high mean low speed
		TIM_SetCompare1(TIM4,steering_pwmval);
	}
	else
	{
		if(up_count>=2900)
		{
			steering_pwmval=1500;//high mean low speed
			TIM_SetCompare1(TIM4,steering_pwmval);
		}
	}
}


void down_basket(void)
{
	if(down_flag==00)
	{
		down_flag=0x01;
		steering_pwmval=1500+200;//high mean low speed
		TIM_SetCompare1(TIM4,steering_pwmval);
	}
	else
	{
		if(down_count>=2900)
		{
			steering_pwmval=1500;//high mean low speed
			TIM_SetCompare1(TIM4,steering_pwmval);
		}
	}	
}



///////////////////////////////////
void sow_seed(void)//led����˸����
{
	GPIO_SetBits(GPIOD,GPIO_Pin_15);//GPIOF9,F10���øߣ�����
	light_flag=1;
}

/*---------------------uwb������ڴ���---------------------*/

void uwb_adj(float w_x,float w_y,float w_z)//uwb��������
{
	dis_sonic=sum_x_aa;		
	speed_x_axis=p_longitude*(w_x-plant_x);//PIDX�����
	speed_x_axis_16=(int16_t) speed_x_axis;
	if(speed_x_axis_16>20)
	{
		speed_x_axis_16=20;
	}
	if(speed_x_axis_16<-20)
	{
		speed_x_axis_16=-20;
	}
	
	if((speed_x_axis_16<5)&&(speed_x_axis_16>0))
	{
		speed_x_axis_16=10;
	}
	
	if((speed_x_axis_16<0)&&(speed_x_axis_16>-5))
	{
		speed_x_axis_16=-10;
	}
	
	speed_y_axis=p_longitude*(plant_y-w_y);//PIDY�����  act_y-plant_y
	speed_y_axis_16=(int16_t) speed_y_axis;
	if(speed_y_axis_16>20)
	{
		speed_y_axis_16=10;
	}
	if(speed_y_axis_16<-20)
	{
		speed_y_axis_16=-10;
	}
	
	
	if((speed_y_axis_16<5)&&(speed_y_axis_16>0))
	{
		speed_y_axis_16=10;
	}
	
	if((speed_y_axis_16<0)&&(speed_y_axis_16>-5))
	{
		speed_y_axis_16=-10;
	}

	speed_z_axis=p_altitude*(w_z-alt_add_xm);//PID�߶ȿ���
	speed_z_axis_16=(int16_t) speed_z_axis;
	
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
	
	cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
	
	if(time_dly_cnt_ms_xm%300==0)
	{
		if((speed_x_axis_16>0)&&(speed_y_axis_16>0))//���ֶ���
		{
			LxStringSend(1,"ǰ��+1,����+1");
			sprintf(buf1,"[s9]ǰ��");//\[b1] ��ӭ���٣����
			speak_len1=strlen(buf1);
			speak_context((u8*)buf1,speak_len1);
		}
		else if((speed_x_axis_16>0)&&(speed_y_axis_16<0))
		{
			LxStringSend(1,"ǰ��+1,����+1");
			sprintf(buf1,"[s9]ǰ��");//\[b1] ��ӭ���٣����
			speak_len1=strlen(buf1);
			speak_context((u8*)buf1,speak_len1);
		}
		else if((speed_x_axis_16<0)&&(speed_y_axis_16>0))
		{
			LxStringSend(1,"����+1,����+1");
			sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
			speak_len1=strlen(buf1);
			speak_context((u8*)buf1,speak_len1);
		}
		else if((speed_x_axis_16<0)&&(speed_y_axis_16<0))
		{
			LxStringSend(1,"����+1,����+1");
			sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
			speak_len1=strlen(buf1);
			speak_context((u8*)buf1,speak_len1);
		}
	}
}

/*---------------------uwb������ڴ������---------------------*/

/*---------------------openmv������ڴ���---------------------*/
void openmv_adj(float o_x,float o_y,float o_z)
{
	speed_x_axis = (120-o_y);
	speed_x_axis_16 = (int16_t)speed_x_axis;
	if(speed_x_axis_16>10)
	{
		speed_x_axis_16=5;
	}
	if(speed_x_axis_16<-10)
	{
		speed_x_axis_16=-5;
	}
	
	if((speed_x_axis_16<5)&&(speed_x_axis_16>0))
	{
		speed_x_axis_16=2;
	}
	
	if((speed_x_axis_16<0)&&(speed_x_axis_16>-5))
	{
		speed_x_axis_16=-2;
	}
	
	speed_y_axis = (160-o_x);
	speed_y_axis_16 = (int16_t)speed_y_axis;
	
	if(speed_y_axis_16>10)
	{
		speed_y_axis_16=5;
	}
	if(speed_y_axis_16<-10)
	{
		speed_y_axis_16=-5;
	}
	
	if((speed_y_axis_16<5)&&(speed_y_axis_16>0))
	{
		speed_y_axis_16=2;
	}
	
	if((speed_y_axis_16<0)&&(speed_y_axis_16>-5))
	{
		speed_y_axis_16=-2;
	}
	
	speed_z_axis = (o_z-alt_add_xm);
	speed_z_axis_16 = (int16_t)speed_z_axis_16;
	
	cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,0);
	
	if((speed_x_axis_16>0)&&(speed_y_axis_16>0))//���ֶ���
	{
		LxStringSend(1,"ǰ��+1,����+1");
		sprintf(buf1,"[s9]ǰ��");//\[b1] ��ӭ���٣����
		speak_len1=strlen(buf1);
		speak_context((u8*)buf1,speak_len1);
	}
	else if((speed_x_axis_16>0)&&(speed_y_axis_16<0))
	{
		LxStringSend(1,"ǰ��+1,����+1");
		sprintf(buf1,"[s9]ǰ��");//\[b1] ��ӭ���٣����
		speak_len1=strlen(buf1);
		speak_context((u8*)buf1,speak_len1);
	}
	else if((speed_x_axis_16<0)&&(speed_y_axis_16>0))
	{
		LxStringSend(1,"����+1,����+1");
		sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
		speak_len1=strlen(buf1);
		speak_context((u8*)buf1,speak_len1);
	}
	else if((speed_x_axis_16<0)&&(speed_y_axis_16<0))
	{
		LxStringSend(1,"����+1,����+1");
		sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
		speak_len1=strlen(buf1);
		speak_context((u8*)buf1,speak_len1);
	}
}
/*---------------------openmv������ڴ������---------------------*/
	

int find_target(float target_x,float target_y,float target_z)
{
	if(return_flag == 2||return_flag==1)
	{
		if(return_flag ==2)
		{					
			if((plant_x>=(line_x-0.05f))&&(plant_x<=(line_x+0.05f))&&(plant_y>(line_y-0.05f))&&(plant_y<=(line_y+0.05f)))
			{
				mission_step = 16;
				return 1;
			}
			else
			{
				openmv_adj(line_x,line_y,altitude_set);//���˻����½����꣬�߶���1.8m
				return 0;
			}
		}
		else
		{
			if((plant_x>=(pole_x-0.05f))&&(plant_x<=(pole_x+0.05f))&&(plant_y>(pole_y-0.05f))&&(plant_y<=(pole_y+0.05f)))//���˻��ҵ���Դ������1��
			{
				return 1;
			}
			else
			{
				openmv_adj(pole_x,pole_y,altitude_set);//���˻��һ�Դ���߶ȱ�����1.8m
				return 0;
			}
		}
	}	
	else
	{
		if (((plant_x>=(target_x-0.2f))&&(plant_x<=(target_x+0.2f)))&&((plant_y>(target_y-0.2f))&&(plant_y<=(target_y+0.2f))))//uwb��������ԭ����15->20;
		{
				sprintf(buf1,"[s9]�����һ������");//\[b1] ��ӭ���٣����
				speak_len1=strlen(buf1);
				speak_context((u8*)buf1,speak_len1);
				
				LxStringSend(1,"�����һ������׼���½��߶�");
				return 1;
		}
		else
		 {
			uwb_adj(target_x,target_y,target_z);
			return 0;
		 }	
	 }		 
}

/////////////////////////////////////////////////////////////////////////////////////////////
//��������
/////////////////////////////////////////////////////////////////////////////////////////

void uart3_camera_command_analyse(void)
{
	if( rx_end_flag==0x01)
	{
		
		int n2 = sscanf((char*)rx_buff,"$KT%c, %lf,%lf, %lf ", &type,  &plant_x_init, &plant_y_init, &plant_z);

		plant_x =-0.1716*pow(plant_x_init,3)+0.9039*pow(plant_x_init,2)-0.1098*plant_x_init+0.3109;
		
		plant_y =0.01032*pow(plant_y_init,2)+0.9243*plant_y_init+0.07365;
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
			pole_x=(rx_buff[3]<<8|rx_buff[4]);//���ֵ���������x
			pole_y=(rx_buff[5]<<8|rx_buff[6]);//���ֵ���������y
			if(done_flag==0x00)	
			{
				return_flag = 0x01;
			}//����м�⵽���־ͷ���1
			else 
			{
				return_flag = 0;
			}
		}
		else if(rx_buff[1]==0xf1)//line
		{
			line_x=(rx_buff[3]<<8|rx_buff[4]);//��ɵ����������x
			line_y=(rx_buff[5]<<8|rx_buff[6]);//��ɵ����������y
//			if(transition==11) return_flag = 2;
//			else return_flag = 0;
		}
		rx_end_flag=0;
		first_frame_end=0;
	}			
}
/*--------------------------------------------��ҵ1----------------------------------------------------------*/

void UserTask_task_one(void)
{
	if(!flag)
	{
		TIM_SetCompare1(TIM4,1500);
		flag=1;
		m1_step=1;
	}
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
				
				if(position_1_order==1&&position_2_order==1) m1_step=0x01;
				
				sprintf(buf1,"[s8]׼������ɣ������ѽ���");//�ɿؽ���
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

/*--------------------------------------------��ҵ1��ǽ���------------------------------------------------------*/



/*--------------------------------------------��ʼ������ҵ-------------------------------------------------------*/
void task1_UserTask_OneKeyCmd(void)
{
    //һ�����/��������
    //�þ�̬������¼һ�����/����ָ���Ѿ�ִ�С�
    static u8 one_key_takeoff_f = 1, one_key_land_f = 1, one_key_mission_f = 0;//һ����ɣ�һ�������־λ
    static u8 last_switch=0,now_switch=0;

/*-----------------------------ң�����ź������޸ģ�����-----------------------------*/
	
    //�ж���ң���źŲ�ִ��
    if (rc_in.no_signal == 0)//�յ��źű�־λΪ0
    {
			  //�жϵ�6ͨ������λ�� 800<CH_6<1200 1000  c�ſ��ز�����1��
        if (rc_in.rc_ch.st_data.ch_[ch_6_aux2] > 800 && rc_in.rc_ch.st_data.ch_[ch_6_aux2] < 1200)
        {
            //��û��ִ��
            if (one_key_land_f == 0)
            {
                //����Ѿ�ִ��
                one_key_land_f =  OneKey_Land(); //ִ��һ������  
            }
			now_switch=1;
		
			if(last_switch!=now_switch)
			{
				last_switch=now_switch;
				sprintf(buf1,"[x1] sound201 ");//\[b1] ��ӭ���٣����
				speak_len1=strlen(buf1);
				speak_context((u8*)buf1,speak_len1);
				
				LxStringSend(1,"1��");
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
			if (one_key_takeoff_f == 0)
			{	
				one_key_mission_f = 0;
				mission_step = 1;
				
				now_switch=2;
			
				if(last_switch!=now_switch)
				{
					last_switch=now_switch;
					sprintf(buf1,"[x1] sound203 ");//\[b1] ��ӭ���٣����
					speak_len1=strlen(buf1);
					speak_context((u8*)buf1,speak_len1);
					
					LxStringSend(1,"2��");
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
            //��λ��ǣ��Ա��ٴ�ִ��
            one_key_takeoff_f = 0;
        }
    
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
		
/*--------------------------------�����޸ģ�����------------------------------*/
		
/*----------------------------����������뿪ʼ--------------------------------*/
		
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
				case 2://����
					mission_step += FC_Unlock();
					if(first_a0_voice==1)
					{
						sprintf(buf1,"[s8]����");//�ɿؽ���
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						
						LxStringSend(1,"����");
						
						first_a0_voice=0;
					}
					first_a0_voice=1;
					break;
				case 3://��2��
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
				case 4: //ģʽ�л�
					mission_step += LX_Change_Mode(2);
				    time_dly_cnt_ms = 0;
					if(first_a0_voice==1)
					{
						sprintf(buf1,"[s9]ģʽ2��z������");//\[b1] ��ӭ���٣����
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						LxStringSend(1,"ģʽ2��z������");
						first_a0_voice=0;
					}
					first_a0_voice=1;			
					break;
				case 5://��2��
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
				case 6://һ�����		
					mission_step += OneKey_Takeoff(100);
					time_dly_cnt_ms = 0;
					if(first_a0_voice==1)
					{
						sprintf(buf1,"[s9]һ�����");//\[b1] ��ӭ���٣����
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						LxStringSend(1,"һ�����");
					}
					break;
				case 7://���˻���ɳ�ʼ��
					if(time_dly_cnt_ms<2000)
					{
						time_dly_cnt_ms+=20;//ms
						if(time_dly_cnt_ms%100==0)
						{
							speed_y_axis_16=-10;
							speed_x_axis_16=10;

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
							
							speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//PID�߶ȿ���
							speed_z_axis_16=(int16_t) speed_z_axis;
							
							cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
						}
					}
					else
					{
						sprintf(buf1,"[s9]�뿪��ɵ�");//\[b1] ��ӭ���٣����
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						LxStringSend(1,"�뿪��ɵ�");
					
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;		
					}					
				break;
		    case 8://��2��	
				wait_flag+=20;//2s	
				time_dly_cnt_ms_xm+=20;//ms
				if(time_dly_cnt_ms_xm>=1000)
				{
					time_dly_cnt_ms_xm=0;
				}
				
				uart3_camera_command_analyse();
				
				uart2_openmv();
				
				if(return_flag == 0x01) result_target = find_target(pole_x,pole_y,altitude_set);
				else result_target=find_target(sow_piont[transition].x,sow_piont[transition].y,altitude_set);
				
				if(0==result_target)wait_flag=0;
				if(1==result_target&&wait_flag>=800)
				{
					time_dly_cnt_ms = 0;
					first_a0_voice=1;
					time_dly_cnt_ms_xm=0;
					time=0;//��Ϊ���µ�20msѰ��λ�õı�־λ
					
					LxStringSend(1,"�����x������");
				
					if(return_flag==1&&wait_flag>=1600)
					{
						mission_step+=1;
						wait_flag=0;
						LxStringSend(1,"ǰ���Ż��");
						sprintf(buf1,"[s9]ǰ���Ż��");//\[b1] ��ӭ���٣����
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
					}
					if(wait_flag>=1600&&!return_flag)//�ȴ�ʱ��Ϊ1.6s��openmvû�з����κ�������������Ѳ��
					{
						transition+=1;
						if(transition == 11) mission_step = 16;
						LxStringSend(1,"ǰ����һ��ת�۵�");
						wait_flag=0;
					}
				}
				break;	
			
			case 9://ֱ�ӽ��͸߶�
			{
				time_dly_cnt_ms_xm+=20;//ms		
				if(time_dly_cnt_ms_xm%100==0)
				{
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
							if(three_yaw_xm<standard_yaw) yaw_16 = 5;
							else yaw_16 = -5;
						}
						
						speed_z_axis_16=(int16_t) speed_z_axis;
						
						cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
				
						if(altitude_set_1>alt_add_xm)
						{
							LxStringSend(1,"�����߶�");
						}
						else
						{
							LxStringSend(1,"�½��߶�");
						}
					}
					else
					{
						LxStringSend(1,"����ָ���߶ȣ�׼���·�ɳ��");
						
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
						uart2_openmv();
						result_target = find_target(pole_x,pole_y,altitude_set_1);
						if(result_target==0)wait_flag=0;
						if(result_target==1&&wait_flag>=3000)
						{	
							mission_step= mission_step+1;
							wait_flag=0;
							time=0;
						}
					}
			}
			break;		 
			case 10:   //�շŵ���
				{
				box_count++;
				time_dly_cnt_ms_xm++;
				if(box_count%1==0)//ע�����ﲻ�Ǽ�20���룬���Ǽ�һ
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
					uart2_openmv();
					result_target=find_target(pole_x,pole_y,altitude_set_1);
				}
			}
				if(box_down_flag==0x00)
				{
					box_down_flag=1;
					down_basket();
					LxStringSend(1,"�·ŵ�������ʱ��ʼ");
				}
				else
				{
					if(box_count>=290&&box_count<320)//5.���·ŵ���ʱ�䣬Ȼ������ͣ5��
					{
						if(box_count==290)
						{
							stop_basket();
							
							LxStringSend(1,"ֹͣ�·ŵ�����׼����ͣ5��");
							
							sprintf(buf1,"[s9]ֹͣ�·ŵ�����׼����ͣ5��");//\[b1] ��ӭ���٣����
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
						else
						{
							stop_basket();
						}
							
					}
					else if(box_count>=320&&box_count<320+290)//5.8���·ŵ���ʱ�䣬Ȼ������ͣ5��
					{
					
						up_basket();
						done_flag=1;//�����������Ѿ���ɾȻ����񣬾Ȼ�������ɱ�־λ��Ϊ1��
						if(box_count==290+250)
						{
					
							LxStringSend(1,"��ͣ5��ʱ�䵽��׼����������");
							
							sprintf(buf1,"[s9]��ͣ5��ʱ�䵽��׼����������");//\[b1] ��ӭ���٣����
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
						}
					}	
					else if(box_count>=320+100)//5.���·ŵ���ʱ�䣬Ȼ������ͣ5��
					{
					
							stop_basket();
							LxStringSend(1,"����5.8�뵽��׼���ظ��߶�");
								
							sprintf(buf1,"[s9]����5.8�뵽��׼���ظ��߶�");//\[b1] ��ӭ���٣����
							speak_len1=strlen(buf1);
							speak_context((u8*)buf1,speak_len1);
							
							mission_step= mission_step+1;
					//���
							GPIO_ResetBits(GPIOD,GPIO_Pin_15);//GPIOF9,F10���øߣ�����
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
						//�ظ�1.5�߶�
						
						if(time_dly_cnt_ms_xm%100==0)
						{
							//uart2_openmv();
							//ֹͣ��
							
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
							LxStringSend(1,"�����߶�");
							}
							else
							{
								LxStringSend(1,"����1.8�׸߶ȣ�����Ѳ��");
								
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
/*---------------------�ָ��߶�1.8���ָ�ǰһ��Ѳ�ߵص�--------------------*/		
		    case 12:
				wait_flag+=20;
				time_dly_cnt_ms_xm+=20;//ms
				if(time_dly_cnt_ms_xm>=10000)
				{
					time_dly_cnt_ms_xm=0;
				}
				uart3_camera_command_analyse();
				if(transition>0) transition -= 1;
				result_target=find_target(sow_piont[transition].x,sow_piont[transition].y,altitude_set);
				if(0==result_target)wait_flag=0;
				if(1==result_target&&wait_flag>=800)
				{
					time_dly_cnt_ms = 0;
					mission_step = 8;
					first_a0_voice=1;
					time_dly_cnt_ms_xm=0;
					wait_flag=0;
					time=0;
				}
				break;	
				
/*----------------------------------------Ŀǰ�߶�1.8�ף�׼���ؼҽ���---------------------------*/
	
		    case 16:
			{
				//��2��
					time_dly_cnt_ms_xm+=20;//ms
					if(time_dly_cnt_ms_xm>=10000)
					{
						time_dly_cnt_ms_xm=0;
					}
					
					uart3_camera_command_analyse();
					
					if ((plant_x>=sow_piont[transition].x-0.15f)&&(plant_x<=sow_piont[transition].x+0.15f)&&(plant_y>sow_piont[transition].y-0.15f)&&(plant_y<=sow_piont[transition].y+0.15f))
					{
						sow_seed();
						index_sow_i=0;
						
						sprintf(buf1,"[s9]�����𽵵㣬׼��z��0��");//\[b1] ��ӭ���٣����
						speak_len1=strlen(buf1);
						speak_context((u8*)buf1,speak_len1);
						
						
						LxStringSend(1,"�����𽵵㣬׼��z��0��");
						
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;
						time_dly_cnt_ms_xm=0;
					 }
					 else
					 {
						dis_sonic=sum_x_aa;		
						speed_x_axis=p_longitude*(home_x-plant_x);//PIDX�����
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
						
						speed_y_axis=p_longitude*(plant_y-home_y);//PIDY�����  act_y-plant_yΪɶ��pidy�����
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
				
						speed_z_axis=p_altitude*(altitude_set-alt_add_xm);//PID�߶ȿ���
						speed_z_axis_16=(int16_t) speed_z_axis;
					
						cmd_send1(speed_x_axis_16,speed_y_axis_16,speed_z_axis_16,yaw_16);
						
						if(time_dly_cnt_ms_xm%300==0)
						{
							if((speed_x_axis_16>0)&&(speed_y_axis_16>0))//���ֶ���
							{
								LxStringSend(1,"ǰ��+1,����+1");
							}
							else if((speed_x_axis_16>0)&&(speed_y_axis_16<0))
							{
								LxStringSend(1,"ǰ��+1,����+1");
							}
							else if((speed_x_axis_16<0)&&(speed_y_axis_16>0))
							{
								LxStringSend(1,"����+1,����+1");
							}
							else if((speed_x_axis_16<0)&&(speed_y_axis_16<0))
							{
								LxStringSend(1,"����+1,����+1");
							}
							else
							{
								
							}

						}
								
					}			

				}
			
			break;	
			case 17://z��0��
				{
					time_dly_cnt_ms_xm+=20;//ms		
					
					
					if(time_dly_cnt_ms_xm%100==0) //����ÿ20ms����һ�Σ�100/20=5��ʵ��ʱ�䣺5*20=100ms=0.1s
					{
						//uart2_openmv();
						//ֹͣ��
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
						LxStringSend(1,"z��0��,׼��һ������");
					
						time_dly_cnt_ms = 0;
						mission_step += 1;
						first_a0_voice=1;
						time_dly_cnt_ms_xm=0;
					}	
					break;						
				}
			
		case 18://ִ��һ������
			OneKey_Land();
			
			time_dly_cnt_ms = 0;
			mission_step += 1;
					
			if(first_a0_voice==1)
			{
				sprintf(buf1,"[s9]����");//\[b1] ��ӭ���٣����
				speak_len1=strlen(buf1);
				speak_context((u8*)buf1,speak_len1);
				
				LxStringSend(1,"����");
				
				first_a0_voice=0;
			}
			transition = 0;
			break;			
	case 19:
		{
			//ִ��һ������
			
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
