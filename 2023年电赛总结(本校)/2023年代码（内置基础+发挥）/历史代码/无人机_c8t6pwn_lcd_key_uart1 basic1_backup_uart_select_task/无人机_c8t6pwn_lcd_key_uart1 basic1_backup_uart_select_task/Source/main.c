#include "config.h"
#include "UART.h"
#include "timer.h"
#include <math.h>//调用三角函数
#include "delay.h"
#include "lcd.h"
#include "key.h"
#include "ir.h"
#include <string.h>
#include "oled.h"
#include "led.h"
#include "stdio.h"
#include "mian.h"



#define BYTE0(dwTemp) (*((char *)(&dwTemp)))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))
	
T265_Data t265={0};;

u8 UART2_busy = 0,start_com_flag=1;
u8 UART1_busy = 0;
u8 receive[42*2]={0};
u16 dis_angle[360];

u16 x_old[400]={0};
u16 y_old[400]={0};
u16 x_old_min=0;
u16 y_old_min=0;

u8 uart_flag=0;

u16 x_now=0,y_now=0;

u16 dis_num=0;

//u16 index = 0;//角度递增量

u8 flag = 0;//定时清屏标志位
u8 scale = 10;//扫描图像放大比例系数
u8 color_wall = 0;//背景颜色
u8 color_xy = 1;//xy坐标颜色
u8 color = 15;//扫描颜色
u8 stay = 0;//扫描运行标志位

u8 one_pack_flag=0;

u32 pack_num=0;

u16 min_angle=0,min_angle_last=0,min_dis=0;
u16 min_angle_kalman=0,min_dis_kalman=0;

u16 index_i=0;

u8 loop_point=0;
u16 angle_t_2=0,angle_t_1=0,angle_t_0=0;
u16 dis_t_2=0,dis_t_1=0,dis_t_0=0;

u16 angle_fina=0,chose_success=0,dis_fina=0;

void memorydis(void);//将串口数据转存到dis_angle[360]，并显示图像
float return_y(u16 ang, signed int d);//x坐标转换函数
float return_x(u16 ang, signed int d);//y坐标转换函数
int t=0,t_flag=0;
u8 temp_i=0,check_sum_a=0,temp_b=0;



int led0pwmval=0x00;

int model_run_key=0x00;
char buf1[30]={"自检 "};//\[b1] 欢迎光临，请进

int s_i,Send_Count;

char x1_hunders=3,x1_ten=7,x1_unit=0;
char y1_hunders=1,y1_ten=1,y1_unit=3;

char x2_hunders=2,x2_ten=1,x2_unit=1;
char y2_hunders=2,y2_ten=6,y2_unit=7;
u8 shift_num=0x00,input_end_flag=0x00,shift_num2=0x00;

u16 x1_position,y1_position,x2_position,y2_position;

extern int key_flag;

extern int key_num;
extern int key_true;

struct point_obj
{
	u16 x;
	u16 y;
};

struct point_obj point_arry[13]={{70,67},{370,113},{211,267},{299,344},{48,418},{369,424},{133,348},{134,198},{298,191},{209,119},{59,276},{376,264},{207,417}};
int tempb,tempa;

u8 record_num1,record_num2,done_flag=0x00;
	
char Uart1_OutPut_Buffer[20]={0};
char Uart2_OutPut_Buffer[20]={0};


int stop_time=0x00;

extern u8 rx_end_flag;
extern u8 command_text;

extern u8 rx2_buff[20];
extern u8 rx2_end_flag;


void t265_data_analysis(void)
{		

//    int16_t sum=0;	
				/*坐标基于匿名坐标系*/
	if(rx2_buff[3]==0x34)/*解析位置*/
    {
			t265.pos_x=(int16_t)((rx2_buff[5]<<8)|rx2_buff[6]);
			
			t265.pos_y=(int16_t)((rx2_buff[7]<<8)|rx2_buff[8]);
			
			t265.pos_z=(int16_t)((rx2_buff[9]<<8)|rx2_buff[10]);
		
			t265.pos_y_f=-(int16_t)(1*(float)t265.pos_x);
			t265.pos_z_f=(int16_t)(1*(float)t265.pos_y);
			t265.pos_x_f=(int16_t)(1*(float)t265.pos_z);//这里是我根臼导是情况进行调整，源程序是江西师范大学罗同学提供。谢谢罗同学2023.07.29 22：58
    }

}
	
	
void t265_send()
{
	if(rx2_end_flag==1)
	{
		rx2_end_flag = 0;
		t265_data_analysis();
		
		for(int tempa=0; tempa<19;tempa++)
		{
			Uart1_OutPut_Buffer[tempa]=rx2_buff[tempa];
		}
	
		for( int u1_i = 0 ; u1_i < 12; u1_i++) 
		{
			while((USART1->SR&0X40)==0);  
			USART1->DR = Uart1_OutPut_Buffer[u1_i]; 
		}
	}
}

void position_send()
{
	Uart1_OutPut_Buffer[0]=0xaa;
	Uart1_OutPut_Buffer[1]=0x29;
	Uart1_OutPut_Buffer[2]=0x05;
	Uart1_OutPut_Buffer[3]=0x33;
	Uart1_OutPut_Buffer[4]=0x06;


	Uart1_OutPut_Buffer[5]=record_num1;
	Uart1_OutPut_Buffer[6]=record_num2;
	Uart1_OutPut_Buffer[7]=0x00;//01 gbk //00 gb2312
	Uart1_OutPut_Buffer[8]=0x00;
	Uart1_OutPut_Buffer[9]=0x00;
	Uart1_OutPut_Buffer[10]=0x00;
	Uart1_OutPut_Buffer[11]=0x00;
	for( int u1_i = 0 ; u1_i < 12; u1_i++) 
	{
	while((USART1->SR&0X40)==0);  
	USART1->DR = Uart1_OutPut_Buffer[u1_i]; 
	}
}
		
//void test_uart1_send(void)
//{
//	Uart1_OutPut_Buffer[0]=0xa5;
//	Uart1_OutPut_Buffer[1]=0x5a;
//	Uart1_OutPut_Buffer[2]=02;
//	
//	Uart1_OutPut_Buffer[3]=record_num1;
//	Uart1_OutPut_Buffer[4]=record_num2;//01 gbk //00 gb2312
//	Uart1_OutPut_Buffer[5]=0xfd;//01 gbk //00 gb2312
//	
//	


//	for( int u1_i = 0 ; u1_i < 6; u1_i++) 
//	{
//		while((USART1->SR&0X40)==0);  
//		USART1->DR = Uart1_OutPut_Buffer[u1_i]; 
//	}
//}
	
void show_two_point_xy(void)
{

	 OLED_Show16x16(32+16*0,0,58,0);
	 OLED_Show16x16(32+16*1,0,59,0);
	 OLED_Show16x16(32+16*2,0,60,0);
	 OLED_Show16x16(32+16*3,0,61,0);
	 OLED_Show16x16(32+16*4,0,62,0);
	
	sprintf(buf1,"X1=000cmY1=000cm");
	OLED_P8x16Str(0, 2, (unsigned char*)buf1, 0); //	
	
	sprintf(buf1,"X2=000cmY2=000cm");
	OLED_P8x16Str(0, 5, (unsigned char*)buf1, 0); //	
}

void dis_x1_hunder(char n)
{
	sprintf(buf1,"%d",x1_hunders);	
	OLED_P8x16Str(24+8*0,2, (unsigned char*)buf1, n); //
}


void dis_x1_ten(char n)
{
	sprintf(buf1,"%d",x1_ten);	
	OLED_P8x16Str(24+8*1,2, (unsigned char*)buf1, n); //
}

void dis_x1_unit(char n)
{
	sprintf(buf1,"%d",x1_unit);	
	OLED_P8x16Str(24+8*2,2, (unsigned char*)buf1, n); //
}


void dis_y1_hunder(char n)
{
	sprintf(buf1,"%d",y1_hunders);	
	OLED_P8x16Str(88+8*0,2, (unsigned char*)buf1, n); //
}


void dis_y1_ten(char n)
{
	sprintf(buf1,"%d",y1_ten);	
	OLED_P8x16Str(88+8*1,2, (unsigned char*)buf1, n); //
}

void dis_y1_unit(char n)
{
	sprintf(buf1,"%d",y1_unit);	
	OLED_P8x16Str(88+8*2,2, (unsigned char*)buf1, n); //
}
///////////////////////////////////////
void dis_x2_hunder(char n)
{
	sprintf(buf1,"%d",x2_hunders);	
	OLED_P8x16Str(24+8*0,5, (unsigned char*)buf1, n); //
}


void dis_x2_ten(char n)
{
	sprintf(buf1,"%d",x2_ten);	
	OLED_P8x16Str(24+8*1,5, (unsigned char*)buf1, n); //
}

void dis_x2_unit(char n)
{
	sprintf(buf1,"%d",x2_unit);	
	OLED_P8x16Str(24+8*2,5, (unsigned char*)buf1, n); //
}


void dis_y2_hunder(char n)
{
	sprintf(buf1,"%d",y2_hunders);	
	OLED_P8x16Str(88+8*0,5, (unsigned char*)buf1, n); //
}


void dis_y2_ten(char n)
{
	sprintf(buf1,"%d",y2_ten);	
	OLED_P8x16Str(88+8*1,5, (unsigned char*)buf1, n); //
}

void dis_y2_unit(char n)
{
	sprintf(buf1,"%d",y2_unit);	
	OLED_P8x16Str(88+8*2,5, (unsigned char*)buf1, n); //
}


void show_all_number(void)
{
	
	dis_x1_hunder(0);
	dis_x1_ten(0);
	dis_x1_unit(0);
	
	dis_y1_hunder(0);
	dis_y1_ten(0);
	dis_y1_unit(0);
	
	dis_x2_hunder(0);
	dis_x2_ten(0);
	dis_x2_unit(0);
	
	dis_y2_hunder(0);
	dis_y2_ten(0);
	dis_y2_unit(0);
	
	//OLED_Show8x16(24+8*0,2,x1_hunders+16,0);
//	OLED_Show8x16(24+8*1,2,x1_ten+16,0);
//	OLED_Show8x16(24+8*2,2,x1_unit+16,0);
	
//	OLED_Show8x16(88+8*0,2,y1_hunders+16,0);
//	OLED_Show8x16(88+8*1,2,y1_ten+16,0);	
//	OLED_Show8x16(88+8*2,2,y1_unit+16,0);
//	

//	OLED_Show8x16(24+8*0,5,x2_hunders,0);
//	OLED_Show8x16(24+8*1,5,x2_ten,0);
//	OLED_Show8x16(24+8*2,5,x2_unit,0);
//	
//	OLED_Show8x16(88+8*0,5,y2_hunders,0);
//	OLED_Show8x16(88+8*1,5,y2_ten,0);	
//	OLED_Show8x16(88+8*2,5,y2_unit,0);
}
void show_num_reverse(void)
{
	switch (shift_num)
  {
  	case 0:
				dis_x1_hunder(1);
  		break;
  	case 1:
				dis_x1_ten(1);
  		break;		
		case 2:
			dis_x1_unit(1);
  		break;
		
		
		case 3:
			dis_y1_hunder(1);
  		break;
  	case 4:
					dis_y1_ten(1);
  		break;		
		case 5:
			dis_y1_unit(1);
  		break;
		
		
		case 6:
			dis_x2_hunder(1);
  		break;
  	case 7:
			dis_x2_ten(1);
  		break;		
		case 8:
				dis_x2_unit(1);
  		break;
		
		
		case 9:
			dis_y2_hunder(1);
  		break;
  	case 10:
			dis_y2_ten(1);
  		break;		
		case 11:
			dis_y2_unit(1);
  		break;
		
		
  	default:
  		break;
  }
}

void return_back_dis_num()
{
	switch (shift_num)
  {
  	case 0:
			dis_x1_hunder(0);
  		break;
  	case 1:
				dis_x1_ten(0);
  		break;		
		case 2:
			dis_x1_unit(0);
  		break;
		
		
		case 3:
			dis_y1_hunder(0);
  		break;
  	case 4:
				dis_y1_ten(0);
  		break;		
		case 5:
			dis_y1_unit(0);
  		break;
		
		
		case 6:
			dis_x2_hunder(0);
  		break;
  	case 7:
			dis_x2_ten(0);
  		break;		
		case 8:
				dis_x2_unit(0);
  		break;
		
		
		case 9:
		dis_y2_hunder(0);
  		break;
  	case 10:
			dis_y2_ten(0);
  		break;		
		case 11:
			dis_y2_unit(0);
  		break;
		
		
  	default:
  		break;
  }
}
void show_num_add_one(void)
{
	switch (shift_num)
  {
  	case 0:
			x1_hunders = key_num;
			if(x1_hunders>=10)
			{
				x1_hunders=0;
			}
			dis_x1_hunder(0);
  		break;
  	case 1:
			
			x1_ten=key_num;
			if(x1_ten>=10)
			{
				x1_ten=0;
			}
			dis_x1_ten(0);
  		break;		
		case 2:
			x1_unit = key_num;
			if(x1_unit>=10)
			{
				x1_unit=0;
			}
			dis_x1_unit(0);
  		break;
		
		
		case 3:
			y1_hunders=key_true;
				if(y1_hunders>=10)
				{
					y1_hunders=0;
				}
			dis_y1_hunder(0);
  		break;
  	case 4:
			y1_ten=key_true;
				if(y1_ten>=10)
				{
					y1_ten=0;
				}
		
				dis_y1_ten(0);
  		break;		
		case 5:
				y1_unit=key_true;
				if(y1_unit>=10)
				{
					y1_unit=0;
				}
			dis_y1_unit(0);
  		break;
		
		
		case 6:
			x2_hunders=key_true;
				if(x2_hunders>=10)
				{
					x2_hunders=0;
				}
			
			dis_x2_hunder(0);
  		break;
  	case 7:
			x2_ten=key_true;
				if(x2_ten>=10)
				{
					x2_ten=0;
				}
			dis_x2_ten(0);
  		break;		
		case 8:
			x2_unit=key_true;
				if(x2_unit>=10)
				{
					x2_unit=0;
				}
				dis_x2_unit(0);
  		break;
		
		
		case 9:
			y2_hunders=key_true;
				if(y2_hunders>=10)
				{
					y2_hunders=0;
				}
		dis_y2_hunder(0);
  		break;
  	case 10:
			y2_ten=key_true;
				if(y2_ten>=10)
				{
					y2_ten=0;
				}
			dis_y2_ten(0);
  		break;		
		case 11:
			y2_unit=key_true;
				if(y2_unit>=10)
				{
					y2_unit=0;
				}
			dis_y2_unit(0);
  		break;
		
		
  	default:
  		break;
  }
}

void show_num_sub_one(void)
{
	switch (shift_num)
  {
  	case 0:
			if(x1_hunders<=0)
			{
				x1_hunders=9;
			}
			else
			{
				x1_hunders--;
			}
			
		
			dis_x1_hunder(1);
  		break;
  	case 1:
			
				if(x1_ten<=0)
			{
				x1_ten=9;
			}
			else
			{
				x1_ten--;
			}
				dis_x1_ten(1);
  		break;		
		case 2:
			if(x1_unit<=0)
			{
				x1_unit=9;
			}
			else
			{
				x1_unit--;
			}
		
			dis_x1_unit(1);
  		break;
		
		
		case 3:
			if(y1_hunders<=0)
			{
				y1_hunders=9;
			}
			else
			{
				y1_hunders--;
			}
			dis_y1_hunder(1);
  		break;
  	case 4:
			if(y1_ten<=0)
			{
				y1_ten=9;
			}
			else
			{
				y1_ten--;
			}
		
				dis_y1_ten(1);
  		break;		
		case 5:
			if(y1_unit<=0)
			{
				y1_unit=9;
			}
			else
			{
				y1_unit--;
			}
			dis_y1_unit(1);
  		break;
		
		
		case 6:
			if(x2_hunders<=0)
			{
				x2_hunders=9;
			}
			else
			{
				x2_hunders--;
			}
			
			dis_x2_hunder(1);
  		break;
  	case 7:
			if(x2_ten<=0)
			{
				x2_ten=9;
			}
			else
			{
				x2_ten--;
			}
			dis_x2_ten(1);
  		break;		
		case 8:
			if(x2_unit<=0)
			{
				x2_unit=9;
			}
			else
			{
				x2_unit--;
			}
				dis_x2_unit(1);

  		break;
		
		
		case 9:
			if(y2_hunders<=0)
			{
				y2_hunders=9;
			}
			else
			{
				y2_hunders--;
			}
		dis_y2_hunder(1);
  		break;
  	case 10:
			if(y2_ten<=0)
			{
				y2_ten=9;
			}
			else
			{
				y2_ten--;
			}
			dis_y2_ten(1);
  		break;		
		case 11:
			if(y2_unit<=0)
			{
				y2_unit=9;
			}
			else
			{
				y2_unit--;
			}
			dis_y2_unit(1);
  		break;
		
		
  	default:
  		break;
  }
}

void input_two_point_xy(void)
{
	
	


}








int check_sum_frame(void)
{
	check_sum_a=0;
	
	if(receive[40]==receive[41])
	{
		for(temp_i=0;temp_i<40;temp_i++)
		{
			check_sum_a=check_sum_a+receive[temp_i];
			
		}
		check_sum_a=0xff-check_sum_a;
		
		if(check_sum_a==receive[40])
		{
			return 1 ;
		}
		else
		{
			return 0 ;
		}
		
		
	}
	else
	{
		return 0 ;
	} 
	
	
	
	
	
	
	
}

float Q = 0.02;
float R = 0.104;
float x_last=0;//滤波后输出距离
float p_last=1;//方差

int s_i,Send_Count;

int kalmanfilter_xm(int z_mensure)
{
	float p_mid,p_now,kg,Sm;
	
	float x_mid;
//	x_mid = x_last;
//	p_mid = p_last+Q;
//	kg = 	p_mid/(p_mid+R);
//	Sm = (int)x_mid+kg*(z_mensure-x_mid);
//	p_now = (1-kg)*p_mid;
//	p_last = p_now;
//	x_last = Sm;
	
//	K(i) = P(i-1) / (P(i-1) + R);
	p_mid = p_last;
	kg = p_mid/(p_mid+R);
	
//    X(i) = X(i-1) + K(i) * (data(i) - X(i-1));
	x_mid = x_last;
	Sm = (int)x_mid+kg*(z_mensure-x_mid);
		

//    P(i) = P(i-1) - K(i) * P(i-1) + Q;	
	p_now = (1-kg)*p_mid+Q;
	p_last = p_now;
	
	x_last = Sm;

	return Sm;

}	







void min_dis_angle(void)
{
	min_angle=0;
	min_angle_kalman=0;
	min_dis=3000;
	min_dis_kalman=3000;
	//seek the min
	for(index_i=0;index_i<360;index_i++)
	{
		if(dis_angle[index_i]<min_dis)
		{
			if(dis_angle[index_i]!=0)
			{
				min_dis=dis_angle[index_i];
				min_angle=index_i;
			}
			
		}
	}
	//save the min data into value_t;
	if(loop_point==0)
	{
		angle_t_2=min_angle;
		dis_t_2=min_dis;
	}
	else if(loop_point==1)
	{
		angle_t_1=min_angle;
		dis_t_1=min_dis;
	}
	else
	{
		angle_t_0=min_angle;
		dis_t_0=min_dis;
	}
	
	loop_point++;
	
	if(loop_point==3)
	{
		loop_point=0;
	}
	
	
		
	
	//three_chose_two();
	if(min_angle!=91)
	{
		temp_b++;
		
		
	}
	
	if(abs(angle_t_2-angle_t_1)<=2)
	{
		angle_fina=angle_t_2;
		dis_fina=dis_t_2;
		chose_success=1;
	}
	else if(abs(angle_t_2-angle_t_0)<=2)
	{
		angle_fina=angle_t_2;
		dis_fina=dis_t_2;
		chose_success=1;
	}
	else if(abs(angle_t_1-angle_t_0)<=2)
	{
		angle_fina=angle_t_1;
		dis_fina=dis_t_1;
		chose_success=1;
	}
	else //if(abs(angle_t_2-angle_t_1)>=3||abs(angle_t_2-angle_t_0)>=3||abs(angle_t_1-angle_t_0)>=3)
	{
		chose_success=0;
		
	}
	
	
		
	
	
	
	
	
	
	min_dis_kalman=kalmanfilter_xm(dis_fina);
	
//	if(start_com_flag==1)	
//	{
//		if(min_angle!=0)
//		{
//			min_angle_last=min_angle;
//			start_com_flag=0;
//		}
//		
//		
//		
//	}
//	if(abs(min_angle_last-min_angle)>20)
//	{
//		min_angle=min_angle_last;
//	}
//	else
//	{
//		min_angle_last=min_angle;
//	}
	
	
}
void send_min_dis_angle(void)
{
	u8 str_init[15];
	u8 length=0;
	
	if(chose_success==1)
	{
		chose_success=0;
		
		str_init[0] = 0xa5;//frame head
	
		str_init[1] = 0x04;//length
		
		str_init[2] = BYTE0(min_angle);
		str_init[3] = BYTE1(min_angle);
		
		str_init[4] = BYTE0(min_dis);
		str_init[5] = BYTE1(min_dis);
		
		
		str_init[6] = 0xff;//frame end
		
		length=0x7;
		
		UART2_SendStr_xm(str_init,length);

	}
	
	
	
	
}


void keyaction_xm(void)//按键服务函数
{
	t=KEY_Scan(0);
			
		
	if(t==KEY0_PRES)//KEY0按下
	{
		
		if(t_flag==0)
		{
//					USART_SendData(USART1, 0x0062);//向串口1发送数据
//					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			 //printf("b"); 
			UART1_Send(0x62);//开始时雷达不扫描
			t_flag=1;
			stay = 1;
		}
		else
		{
//					USART_SendData(USART1, 0x0065);//向串口1发送数据
//					while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			//printf("e"); 
			UART1_Send(0x65);//开始时雷达不扫描
			t_flag=0;
			stay = 0;
		}
		
		
	}
}


void extute_task_1(void)
{
	if(model_run_key==0)//显示任务一界面
		{
			//select model
			show_two_point_xy();
			model_run_key=0x01;
		}			
		////////////////////////////////////////////
		//entern mode and then test the function of model
		///////////////////////////////////////////////////
		else if(model_run_key==1)//进行按键操作
		{
			show_all_number();
			show_num_reverse();
			
			while(input_end_flag==0)
			{
				if(key_flag==1)
				{
					key_flag=0;
					
					show_all_number();
					switch (key_num)
					{
						case 15:
							
						return_back_dis_num();
						x1_position=x1_hunders*100+x1_ten*10+x1_unit;
						y1_position=y1_hunders*100+y1_ten*10+y1_unit;
						
						x2_position=x2_hunders*100+x2_ten*10+x2_unit;
						y2_position=y2_hunders*100+y2_ten*10+y2_unit;
						
						input_end_flag=1;
									
						break;
	/*-------------------------------------------------------------------------------------*/
						case 13:  //移位+1
							
							return_back_dis_num();
							
							if(shift_num<11)
							{
								shift_num++;
							}
							
							show_num_reverse();
							
							break;
	/*-------------------------------------------------------------------------------------*/									
						case 12:  //移位-1
							
							return_back_dis_num();
							
							if(shift_num>0)
							{
								shift_num-=1;
							}
							
							show_num_reverse();
							break;
						case 14:
							if(shift_num<6)
							{
								shift_num+=6;
							}
							show_num_reverse();								
							break;
						case 10:
							if(shift_num>=6)
							{
								shift_num-=6;
							}
							show_num_reverse();
							break;
						default:
							show_num_add_one();
							if(shift_num<11)
							{
								shift_num++;
							}
							show_num_reverse();
							break;
						}
					}
				else;
			}
			model_run_key=0x02;
		}
		else  if(model_run_key==2)//验证坐标正确性
		{
			
				OLED_CLS();	
			//输入坐标结束
				OLED_Show16x16(16+16*0,0,59,0);
				OLED_Show16x16(16+16*1,0,60,0);
				OLED_Show16x16(16+16*2,0,61,0);
				OLED_Show16x16(16+16*3,0,62,0);
				OLED_Show16x16(16+16*4,0,63,0);
				OLED_Show16x16(16+16*5,0,64,0);
			//验证坐标正确性
				record_num1=100;
				record_num2=100;
			
			
				for(int i=0; i<12 ;i++)
				{
					if ((x1_position==point_arry[i].x)&&(y1_position==point_arry[i].y))
					{
						record_num1=i;
						break;
					}
					
				}
				
			for(int i=0; i<12 ;i++)
				{
					if ((x2_position==point_arry[i].x)&&(y2_position==point_arry[i].y))
					{
						record_num2=i;
						break;
					}
					
				}
				
				if((record_num1==100)||(record_num2==100))
				{
					//输入坐标错误
					
					OLED_Show16x16(16+16*0,4,59,0);
					OLED_Show16x16(16+16*1,4,60,0);
					OLED_Show16x16(16+16*2,4,61,0);
					OLED_Show16x16(16+16*3,4,62,0);
					OLED_Show16x16(16+16*4,4,65,0);
					OLED_Show16x16(16+16*5,4,66,0);
					
					delay_ms(1500);
					OLED_CLS();
					
					model_run_key=0x00;
					input_end_flag=0;
					
				}
				
				else
				{
					//输入坐标正确
					
					OLED_Show16x16(16+16*0,2,59,0);
					OLED_Show16x16(16+16*1,2,60,0);
					OLED_Show16x16(16+16*2,2,61,0);
					OLED_Show16x16(16+16*3,2,62,0);
					OLED_Show16x16(16+16*4,2,67,0);
					OLED_Show16x16(16+16*5,2,68,0);

					sprintf(buf1,"%d,%d   selected",record_num1,record_num2);
				
					OLED_P8x16Str(0+8*0,6, (unsigned char*)buf1, 1); //
				
					delay_ms(1600);
				
					model_run_key=0x03;
					
				}
			
		}
		else if(model_run_key==3)//串口1发送位置信息
		{
				OLED_CLS();
				//串口1发送位置信息
				OLED_Show16x16(16+16*0,0,69,0);
				OLED_Show16x16(16+16*1,0,70,0);
				OLED_Show16x16(16+16*2,0,71,0);
				OLED_Show16x16(16+16*3,0,72,0);
				OLED_Show16x16(16+16*4,0,73,0);
				OLED_Show16x16(16+16*5,0,74,0);
			
				position_send();
			
				delay_ms(10000);
				model_run_key=0x04;
		}
		

		else if(model_run_key==4)////飞机死等飞控回信，等不到就死在这里
		{
				if(rx_end_flag==1)
				{
					rx_end_flag=0;
					if(command_text==0x03)
					{
							//飞机收到信息
							OLED_Show16x16(16+16*0,0,75,0);
							OLED_Show16x16(16+16*1,0,76,0);
							OLED_Show16x16(16+16*2,0,77,0);
							OLED_Show16x16(16+16*3,0,78,0);
							OLED_Show16x16(16+16*4,0,79,0);
							OLED_Show16x16(16+16*5,0,80,0);
						
							delay_ms(10000);
							model_run_key=0x05;
							OLED_CLS();
							//等待吊篮命令
						//飞机收到信息
							OLED_Show16x16(16+16*0,0,81,0);
							OLED_Show16x16(16+16*1,0,82,0);
							OLED_Show16x16(16+16*2,0,83,0);
							OLED_Show16x16(16+16*3,0,84,0);
							OLED_Show16x16(16+16*4,0,85,0);
							OLED_Show16x16(16+16*5,0,86,0);
					}
				}
		}
		
		
		//飞机处于运行状态，随时可能发送吊篮命令
		else if(model_run_key==5)
		{

		}
}
/////////////////////////////////////////////////////////////
/////////
//////////////////////////////////////////////////////////

void extute_task_2(void)
{
	OLED_CLS();
	OLED_Show16x16(40+16*0,0,93,0);
	OLED_Show16x16(40+16*1,0,94,0);
	OLED_Show16x16(40+16*2,0,95,0);
}
/////////////////////////////////////////////////////////////
/////////
//////////////////////////////////////////////////////////

void extute_task_3(void)
{
	OLED_CLS();
	OLED_Show16x16(40+16*0,0,93,0);
	OLED_Show16x16(40+16*1,0,94,0);
	OLED_Show16x16(40+16*2,0,96,0);
}

void extute_task_4(void)
{
	if(model_run_key==0)//显示任务一界面
	{
		show_two_point_xy();
		model_run_key=0x01;
	}
	else if(model_run_key==1)//进行按键操作
	{
		show_all_number();
		show_num_reverse();
		
		while(input_end_flag==0)
		{
			 if(ir_flag==1)
			{
				ir_flag=0;
				show_all_number();
				switch (irdata)
				{
					case 0X00FF22DD:	//播放/暂停键
						
						return_back_dis_num();
						x1_position=x1_hunders*100+x1_ten*10+x1_unit;
						y1_position=y1_hunders*100+y1_ten*10+y1_unit;
						
						x2_position=x2_hunders*100+x2_ten*10+x2_unit;
						y2_position=y2_hunders*100+y2_ten*10+y2_unit;
						
						input_end_flag=1;
								
						break;
					//移位+1
					case 0X00FFC23D:	//下一曲
					
						return_back_dis_num();
						
						shift_num++;
						
						if(shift_num>=12)
						{
							shift_num=0;
						}
						show_num_reverse();
						break;
					//数字+1
					case 0X00FF906F:	 //vol+
						show_num_add_one();
						break;
					//数字-1
					case 0X00FFA857:	//vol-
						show_num_sub_one();
						break;
					default:
						break;
					}
				}
		}
		model_run_key=0x02;
	}
	else  if(model_run_key==2)//验证坐标正确性
	{
		
			OLED_CLS();	
		//输入坐标结束
			OLED_Show16x16(16+16*0,0,59,0);
			OLED_Show16x16(16+16*1,0,60,0);
			OLED_Show16x16(16+16*2,0,61,0);
			OLED_Show16x16(16+16*3,0,62,0);
			OLED_Show16x16(16+16*4,0,63,0);
			OLED_Show16x16(16+16*5,0,64,0);
		//验证坐标正确性
			record_num1=100;
			record_num2=100;
		
		
			for(int i=0; i<12 ;i++)
			{
				if ((x1_position==point_arry[i].x)&&(y1_position==point_arry[i].y))
				{
					record_num1=i;
					break;
				}
			}
		for(int i=0; i<12 ;i++)
			{
				if ((x2_position==point_arry[i].x)&&(y2_position==point_arry[i].y))
				{
					record_num2=i;
					break;
				}
				
			}
			if((record_num1==100)||(record_num2==100))
			{
				//输入坐标错误
				
				OLED_Show16x16(16+16*0,4,59,0);
				OLED_Show16x16(16+16*1,4,66,0);
				OLED_Show16x16(16+16*2,4,61,0);
				OLED_Show16x16(16+16*3,4,62,0);
				OLED_Show16x16(16+16*4,4,65,0);
				OLED_Show16x16(16+16*5,4,66,0);
				
				delay_ms(1500);
				OLED_CLS();
				
				model_run_key=0x00;
				input_end_flag=0;
				
			}
			else
			{
				//输入坐标正确
				OLED_Show16x16(16+16*0,2,59,0);
				OLED_Show16x16(16+16*1,2,66,0);
				OLED_Show16x16(16+16*2,2,61,0);
				OLED_Show16x16(16+16*3,2,62,0);
				OLED_Show16x16(16+16*4,2,67,0);
				OLED_Show16x16(16+16*5,2,68,0);
				
				sprintf(buf1,"%d,%d   selected",record_num1,record_num2);
				
				OLED_P8x16Str(0+8*0,6, (unsigned char*)buf1, 1); //
				
				delay_ms(1600);
				
				model_run_key=0x03;
			}
	}
	else if(model_run_key==3)//串口1发送位置信息
	{
			OLED_CLS();
			//串口1发送位置信息
			OLED_Show16x16(16+16*0,0,69,0);
			OLED_Show16x16(16+16*1,0,70,0);
			OLED_Show16x16(16+16*2,0,71,0);
			OLED_Show16x16(16+16*3,0,72,0);
			OLED_Show16x16(16+16*4,0,73,0);
			OLED_Show16x16(16+16*5,0,74,0);
			
			Uart1_OutPut_Buffer[0]=0xa5;
			Uart1_OutPut_Buffer[1]=0x5a;
			Uart1_OutPut_Buffer[2]=02;
			
			Uart1_OutPut_Buffer[3]=record_num1;
			Uart1_OutPut_Buffer[4]=record_num2;//01 gbk //00 gb2312
			Uart1_OutPut_Buffer[5]=0xfd;//01 gbk //00 gb2312

			for( int u1_i = 0 ; u1_i < 6; u1_i++) 
			{
				while((USART1->SR&0X40)==0);  
				USART1->DR = Uart1_OutPut_Buffer[u1_i]; 
			}
			delay_ms(10000);
			model_run_key=0x04;
	}
	else if(model_run_key==4)////飞机死等飞控回信，等不到就死在这里
	{
			if(rx_end_flag==1)
			{
				rx_end_flag=0;
				if(command_text==0x03)
				{
						//飞机收到信息
						OLED_Show16x16(16+16*0,0,75,0);
						OLED_Show16x16(16+16*1,0,76,0);
						OLED_Show16x16(16+16*2,0,77,0);
						OLED_Show16x16(16+16*3,0,78,0);
						OLED_Show16x16(16+16*4,0,79,0);
						OLED_Show16x16(16+16*5,0,80,0);
					
						delay_ms(10000);
						model_run_key=0x05;
						OLED_CLS();
						//等待吊篮命令
					//飞机收到信息
						OLED_Show16x16(16+16*0,0,81,0);
						OLED_Show16x16(16+16*1,0,82,0);
						OLED_Show16x16(16+16*2,0,83,0);
						OLED_Show16x16(16+16*3,0,84,0);
						OLED_Show16x16(16+16*4,0,85,0);
						OLED_Show16x16(16+16*5,0,86,0);
				}
			}
	}
	//飞机处于运行状态，随时可能发送吊篮命令
	else if(model_run_key==5)
	{

	}
}

int main(void)
{
	u8 a=0xb8;
	int8_t c;
	c=(int8_t) a;
	a++;
	c++;
	start_com_flag=1;
	
	delay_init();
	delay_ms(500);//等待器件上电准备好
		
	OLED_Init();
	
	OLED_Show16x16(40+16*0,0,40,0);
	OLED_Show16x16(40+16*1,0,41,0);
	OLED_Show16x16(40+16*2,0,42,0);
	OLED_Show16x16(40+16*3,0,43,0);
	
	OLED_P8x16Str(48,2,"2023",0);
	
	//OLED_Show8x16(48,2,2+16,0);
	
	
	OLED_Show16x16(48+16*2,2,44,0);
	
	OLED_Show16x16(24+16*0,4,45,0);
	OLED_Show16x16(24+16*1,4,46,0);
	OLED_Show16x16(24+16*2,4,47,0);
	OLED_Show16x16(24+16*3,4,48,0);
	OLED_Show16x16(24+16*4,4,49,0);
	OLED_Show16x16(24+16*5,4,50,0);
	
	OLED_Show16x16(24+16*0,6,53,0);
	OLED_Show16x16(24+16*1,6,54,0);
	OLED_Show16x16(24+16*2,6,55,0);
	OLED_Show16x16(24+16*3,6,56,0);
	OLED_Show16x16(24+16*4,6,57,0);
	


	TIM2_Int_Init(2000, 72);//定时器2定时2毫秒
	
	TIM3_PWM_Init(20000-1,72-1);
	
	
	
	led0pwmval=1500;//high mean low speed
	TIM_SetCompare1(TIM3,led0pwmval);
	
	delay_ms(1600);//等待器件上电准备好
//	delay_ms(1600);//等待器件上电准备好
	
	UART2_Init(115200);

	UART1_Init(115200);
	
//	test_uart1_send();
	UART3_Init(115200);
	
	irinit();

	key_init_r_c();				//按键初始化		

	backup_uart_io_stop_io_init();

	
	OLED_CLS();
	
	while(1)
	{
		t265_send();
		if((task_pb8==0)&&(task_pb9==0))
		{
		
			extute_task_1();
		
		}
	//	delay_ms(5);
	//	UART1_Send(0x65);//开始时雷达不扫描
		
		if((task_pb8==0)&&(task_pb9==1))
		{
		
			extute_task_2();
		
		}
		
		if((task_pb8==1)&&(task_pb9==0))
		{
		
			extute_task_3();
		
		}
		
		if((task_pb8==1)&&(task_pb9==1))
		{
		
			extute_task_1();
		
		}
	}

	

}


//数据转存为角度和距离,单位毫米,数组元素序号代表角度0~359度，内容为距离。
void memorydis(void)
{
	u16 i,j;
	
	if(one_pack_flag)
	{
		one_pack_flag=0;
		for(i=0; i<60; i++)
		{
			if(receive[1] == (i+0xA0))
			{
				for(j=0; j<6; j++)
				{
					dis_angle[i*6+j] = 0;
					dis_angle[i*6+j] |= receive[7+(j*6)];
					dis_angle[i*6+j] <<= 8;
					dis_angle[i*6+j] |= receive[6+(j*6)];
				}
			}
		}
	}
	

}







