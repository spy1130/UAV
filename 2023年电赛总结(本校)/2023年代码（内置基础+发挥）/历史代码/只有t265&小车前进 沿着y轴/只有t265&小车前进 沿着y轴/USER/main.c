#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "12121.h"
#include "time1.h"
#include <string.h>
#include "main.h"


extern u8 rx_buff[38];
extern u8 rx_end_flag;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;
extern int key_flag;
extern int key_num;

extern u8 rx_buff2[38];
extern u8 rx_end_flag2;//1 is mean that serious port  recieve a good frame,0 mean that is recieving ;

extern u8 rx3_buff[38];
extern u8 rx3_end_flag;


unsigned char Send_Count; //������Ҫ���͵����ݸ���
int speak_i;
char DataScope_OutPut_Buffer_xm[20];
int speak_len1=0x00;//(sizeof(buf_xm)/sizeof(buf_xm[0]));
int speak_len,speak_i;
char buf1[100]={"�Լ� "};//\[b1] ��ӭ���٣����

double plant_x_init,plant_y_init,plant_z,act_x=4.19,act_y=4.46;
double plant_x,plant_y;
float lcd_x_plan=0,lcd_y_plan=0;
char c, type;


double car_x_init,car_y_init,car_z;
double car_x,car_y;
double int_t265=0;

char c, type2;


float lcd_x=0,lcd_y=0,lcd_x_last=1.35/4.8*287,lcd_y_last=(4.0-0.35)/4.0*240;

T265_Data t265={0};

char Uart1_OutPut_Buffer[20]={0};
char Uart2_OutPut_Buffer[20]={0};

int speak_len,speak_i;

char car_buf[20]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
int16_t dis,y_orign;



/************************************************
 ALIENTEK��ӢSTM32������ʵ��13
 TFTLCD��ʾʵ��  
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


void draw_path(double plant_x,double plant_y)
{
	if(plant_y>4.80||plant_y<0.0||plant_x>4||plant_x<0 )
	{
		
	}
	else
	{
		lcd_x_plan=plant_y;//�����˻�x����ת��Ϊlcd  x����
		lcd_y_plan=4.0-plant_x;//�����˻y����ת��Ϊlcd  y����
		lcd_x=lcd_x_plan/4.8*287;//��x����ת��Ϊ��������
		lcd_y=lcd_y_plan/4.0*240;//��y����ת��Ϊ��������
		
		
		//void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
		LCD_DrawLine((u16)lcd_x_last,(u16)lcd_y_last,(u16) lcd_x,(u16) lcd_y);
		lcd_x_last=lcd_x;
		lcd_y_last=lcd_y;
		//lcd_x_last
		
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
//��������t0
/////////////////////////////////////////////////////////////////////////////////////////

void uart1_camera_command_analyse(void)
{
	
	if( rx_end_flag==0x01)
	{
		
		int n2 = sscanf((char*)rx_buff,"$KT%c, %lf,%lf, %lf ", &type,  &plant_x_init, &plant_y_init, &plant_z);
		//int n2 = sscanf((char*)rx_buff,"$KT%c, %f,%f, %f ", &type,  &plant_x_init, &plant_y_init, &plant_z);
		
		plant_x =plant_x_init;
		
		plant_y =plant_y_init;
		
				
		rx_end_flag=0;
		
//		LCD_ShowString(279,0,32,16,16,"X:");	 
//		LCD_ShowString(279,17,32,16,16,"Y:");
		
		//LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
		LCD_ShowNum(279+15,0,(u32)(plant_y*10),3,16);
		LCD_ShowNum(279+15,17,(u32)(plant_x*10),3,16);
		
		draw_path( plant_x, plant_y);
		
		
		

	}
		
}	
////////////////////////////////////////////////////////////////////////////////////////////
//��������t1
/////////////////////////////////////////////////////////////////////////////////////////

void uart2_camera_command_analyse(void)
{
	
	if( rx_end_flag2==0x01)
	{
		rx_end_flag2=0;
//		int n2 = sscanf((char*)rx_buff2,"$KT%c, %lf,%lf, %lf ", &type2,  &car_x_init, &car_y_init, &car_z);
//		//int n2 = sscanf((char*)rx_buff,"$KT%c, %f,%f, %f ", &type,  &plant_x_init, &plant_y_init, &plant_z);
//		
//		car_y =car_x_init;
//		
//		car_x =car_y_init;
//		
//				
//		
//		
////		LCD_ShowString(279,0,32,16,16,"X:");	 
////		LCD_ShowString(279,17,32,16,16,"Y:");
//		
//		//LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
//		LCD_ShowNum(279+15,16*11,(u32)(car_x*10),3,16);
//		LCD_ShowNum(279+15,16*12,(u32)(car_y*10),3,16);
		int_t265=int_t265+1;
		if(rx_buff2[3]==0x35)/*����ŷ����*/
		{
				
				t265.pitch=(int16_t)((rx_buff2[5]<<8)|rx_buff2[6]);
				t265.roll= (int16_t)((rx_buff2[7]<<8)|rx_buff2[8]);
				t265.yaw=  (int16_t)((rx_buff2[9]<<8)|rx_buff2[10]);

				t265.pi_f=(int16_t)(t265.pitch);
				
				t265.ro_f=(int16_t)(t265.roll);
				
				t265.ya_f=(int16_t)(t265.yaw);

				
		}else if(rx_buff2[3]==0x34)/*����λ��*/
		{
				
				t265.pos_x=(int16_t)((rx_buff2[5]<<8)|rx_buff2[6]);
				
				t265.pos_y=(int16_t)((rx_buff2[7]<<8)|rx_buff2[8]);
				
				t265.pos_z=(int16_t)((rx_buff2[9]<<8)|rx_buff2[10]);
				t265.yaw=(int16_t)((rx_buff2[11]<<8)|rx_buff2[12]);
				if(t265.yaw<380&&t265.yaw>=0)
				{
					t265.ya_f=(int16_t)(t265.yaw);
				}
				
				
				if(t265.pos_x<540&&t265.pos_x>=-200)
				{
					t265.pos_x_f=-(int16_t)(1.1*(float)t265.pos_x);
				}
				
				if(t265.pos_y<540&&t265.pos_y>=-40)
				{
					t265.pos_z_f=(int16_t)(1.1*(float)t265.pos_y);
				}
				
				if(t265.pos_z<540&&t265.pos_z>=-80)
				{
					t265.pos_y_f=(int16_t)(1.1*(float)t265.pos_z);//�������Ҹ��ʵ���������е�����Դ�����ǽ���ʦ����ѧ��ͬѧ�ṩ��лл��ͬѧ2023.07.29 22��58
					if(t265.pos_y_f>600)
					{
						t265.pos_y_f=400;
					}
				}
				//t265.pos_y_f=(int16_t)(1.1*(float)t265.pos_z);//�������Ҹ��ʵ���������е�����Դ�����ǽ���ʦ����ѧ��ͬѧ�ṩ��лл��ͬѧ2023.07.29 22��58

		}else if(rx_buff2[3]==0x33)/*�����ٶ�*/
		{
				t265.v_x=(int16_t)((rx_buff2[5]<<8)|rx_buff2[6]);
				t265.v_y=(int16_t)((rx_buff2[7]<<8)|rx_buff2[8]);
				t265.v_z=(int16_t)((rx_buff2[9]<<8)|rx_buff2[10]);

	//			t265.v_x_f=(int16_t)(1.5*(t265.v_x));
	//				
	//			t265.v_y_f=(int16_t)(1.5*(t265.v_y));
	//			t265.v_z_f=(int16_t)(1.5*(t265.v_z));
				
				t265.v_y_f=-(int16_t)(1.5*(t265.v_x));//�����������һ��2023.07.29 23:20
				t265.v_z_f=(int16_t)(1.5*(t265.v_y));
				t265.v_x_f=(int16_t)(1.5*(t265.v_z));
		}
		
		
		
		
		
		
		
		
		
		
		

	}
		
}	


void uart3_camera_command_analyse(void)
{
//	if(rx3_end_flag==1)
//	{
//		rx3_end_flag=0;
//		
//		//    int16_t sum=0;	
///*���������������ϵ*/
//		if(rx3_buff[3]==0x35)/*����ŷ����*/
//		{
//				
//				t265.pitch=(int16_t)((rx3_buff[5]<<8)|rx3_buff[6]);
//				t265.roll= (int16_t)((rx3_buff[7]<<8)|rx3_buff[8]);
//				t265.yaw=  (int16_t)((rx3_buff[9]<<8)|rx3_buff[10]);

//				t265.pi_f=(int16_t)(t265.pitch);
//				
//				t265.ro_f=(int16_t)(t265.roll);
//				
//				t265.ya_f=(int16_t)(t265.yaw);

//				
//		}else if(rx3_buff[3]==0x34)/*����λ��*/
//		{
//				
//				t265.pos_x=(int16_t)((rx3_buff[5]<<8)|rx3_buff[6]);
//				
//				t265.pos_y=(int16_t)((rx3_buff[7]<<8)|rx3_buff[8]);
//				
//				t265.pos_z=(int16_t)((rx3_buff[9]<<8)|rx3_buff[10]);
//				t265.yaw=(int16_t)((rx3_buff[11]<<8)|rx3_buff[12]);
//				t265.ya_f=(int16_t)(t265.yaw);
//				

//				t265.pos_y_f=-(int16_t)(1.1*(float)t265.pos_x);
//				t265.pos_z_f=(int16_t)(1.1*(float)t265.pos_y);
//				t265.pos_x_f=(int16_t)(1.1*(float)t265.pos_z);//�������Ҹ��ʵ���������е�����Դ�����ǽ���ʦ����ѧ��ͬѧ�ṩ��лл��ͬѧ2023.07.29 22��58

//		}else if(rx3_buff[3]==0x33)/*�����ٶ�*/
//		{
//				t265.v_x=(int16_t)((rx3_buff[5]<<8)|rx3_buff[6]);
//				t265.v_y=(int16_t)((rx3_buff[7]<<8)|rx3_buff[8]);
//				t265.v_z=(int16_t)((rx3_buff[9]<<8)|rx3_buff[10]);

//	//			t265.v_x_f=(int16_t)(1.5*(t265.v_x));
//	//				
//	//			t265.v_y_f=(int16_t)(1.5*(t265.v_y));
//	//			t265.v_z_f=(int16_t)(1.5*(t265.v_z));
//				
//				t265.v_y_f=-(int16_t)(1.5*(t265.v_x));//�����������һ��2023.07.29 23:20
//				t265.v_z_f=(int16_t)(1.5*(t265.v_y));
//				t265.v_x_f=(int16_t)(1.5*(t265.v_z));
//		}
//						
//						
//						
//	}
}




//////////////////////
///begin show_mode_6_test_process
////////////////////	



//////////////////////
///begin show_mode_6_test_process
////////////////////	
void speak_context(u8 buf_xm[],int speak_len )
{
	//speak_len=(sizeof(buf_xm)/sizeof(buf_xm[0]));
	Send_Count = speak_len+5;

	DataScope_OutPut_Buffer_xm[0]=0xfd;
	DataScope_OutPut_Buffer_xm[1]=0x00;
	DataScope_OutPut_Buffer_xm[2]=speak_len+2;
	
	DataScope_OutPut_Buffer_xm[3]=0x01;
	DataScope_OutPut_Buffer_xm[4]=0x00;//01 gbk //00 gb2312
	
	//˵������	
	
	for(speak_i=0;speak_i<speak_len;speak_i++)
	{
		DataScope_OutPut_Buffer_xm[speak_i+5]=buf_xm[speak_i];
	}
	for( speak_i = 0 ; speak_i < Send_Count; speak_i++) 
	{
		while((UART4->SR&0X40)==0);  //��ǰ����4����������Դ���ţ��ĵ�����4
		UART4->DR = DataScope_OutPut_Buffer_xm[speak_i]; 
	}
}
/////////////////
////
///////////////

void speaker_test(void)
{
	
	
	char buf1[]={"[v9]��ӭ�μ�2023�����˻�����"};//\[b1] ��ӭ���٣����
	speak_len1=strlen(buf1);
	speak_context((u8*)buf1,speak_len1);

	
		
}
void test_car_forward(void)
{
	car_buf[0]=0xff;
	car_buf[1]=0xfe;
	car_buf[2]=0x05;
	car_buf[3]=0x00;
	car_buf[4]=	0x00;
	car_buf[5]=0x00;
	car_buf[6]=0x00;
	car_buf[7]=	0x00;
	car_buf[8]=0x00;
	car_buf[9]=0x00;
	speak_len1=10;//strlen(car_buf);
	
	for( speak_i = 0 ; speak_i < speak_len1; speak_i++) 
	{
		while((USART2->SR&0X40)==0);  //��ǰ����4����������Դ���ţ��ĵ�����4
		USART2->DR = car_buf[speak_i]; 
	}
}

void test_car_back(void)
{
	car_buf[0]=0xff;
	car_buf[1]=0xfe;
	car_buf[2]=0x05;
	car_buf[3]=0x01;
	car_buf[4]=	0x00;
	car_buf[5]=0x00;
	car_buf[6]=0x00;
	car_buf[7]=	0x00;
	car_buf[8]=0x00;
	car_buf[9]=0x00;
	speak_len1=10;//strlen(car_buf);
	
	for( speak_i = 0 ; speak_i < speak_len1; speak_i++) 
	{
		while((USART2->SR&0X40)==0);  //��ǰ����4����������Դ���ţ��ĵ�����4
		USART2->DR = car_buf[speak_i]; 
	}
}





void test_car_stop(void)
{
	car_buf[0]=0xff;
	car_buf[1]=0xfe;
	car_buf[2]=0x00;
	car_buf[3]=0x01;
	car_buf[4]=	0x00;
	car_buf[5]=0x00;
	car_buf[6]=0x00;
	car_buf[7]=	0x00;
	car_buf[8]=0x00;
	car_buf[9]=0x00;
	speak_len1=10;//strlen(car_buf);
	
	for( speak_i = 0 ; speak_i < speak_len1; speak_i++) 
	{
		while((USART2->SR&0X40)==0);  //��ǰ����4����������Դ���ţ��ĵ�����4
		USART2->DR = car_buf[speak_i]; 
	}
}

void test_car(void)
{
	
	
	for( speak_i = 0 ; speak_i < 13; speak_i++) 
	{
		while((USART2->SR&0X40)==0);  //��ǰ����4����������Դ���ţ��ĵ�����4
		USART2->DR = car_buf[speak_i]; 
	}
	delay_ms(100);
	
	car_buf[0]=0xff;
	car_buf[1]=0xfe;
	car_buf[2]=0x05;
	car_buf[3]=0x00;
	car_buf[4]=	0x00;
	car_buf[5]=0x00;
	car_buf[6]=0x00;
	car_buf[7]=	0x00;
	car_buf[8]=0x00;
	car_buf[9]=0x00;
	speak_len1=10;//strlen(car_buf);
	
	for( speak_i = 0 ; speak_i < speak_len1; speak_i++) 
	{
		while((USART2->SR&0X40)==0);  //��ǰ����4����������Դ���ţ��ĵ�����4
		USART2->DR = car_buf[speak_i]; 
	}
}
///////////////////////////
//
//////////////////////////










void walk_alone_y_axis_forward()//����ĵ�λ ��������
{
	while(1)
	{
		uart2_camera_command_analyse();
		uart1_camera_command_analyse();
		uart3_camera_command_analyse();
		
		if(dis> (t265.pos_y_f-y_orign))
		{
			test_car_forward();
		}
		else
		{
			test_car_stop();
		}
		
		delay_ms(10);
		
		
	}
	
}








 int main(void)
 {	 
 	u8 task_no=0;
	 
//	u8 lcd_id[12];			//���LCD ID�ַ���
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	uart2_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	uart3_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	uart4_init(115200);	 	//���ڳ�ʼ��Ϊ115200//gy25sensor//
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();
	 
	TIM2_Int_Init(2000, 72);//��ʱ��2��ʱ2����
	
	TIM3_PWM_Init(20000-1,72-1);
	 
	 LCD_ShowPicture(0, 0, 287, 240,(u16*)gImage_12121);	 
	 
	 
	 speaker_test();
	 test_car();
	 delay_ms(500);
	 test_car_stop();
	 delay_ms(1000);
	 delay_ms(1000);
	 if(key_up==1)
	 {
		 task_no=1;
	 }

	 
	POINT_COLOR=RED;
//	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣 
	
	 
	 //Chinese_Show_one(90,140,0,16,0);
	 POINT_COLOR=RED;	  
//		LCD_ShowString(30,40,210,24,24,"Elite STM32F1 ^_^"); 
//		LCD_ShowString(30,70,200,16,16,"TFTLCD TEST");
//		LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
//		LCD_ShowString(30,110,200,16,16,lcd_id);		//��ʾLCD ID	      					 
//		LCD_ShowString(30,130,200,12,12,"2015/1/14");	
		
	
	 if(0==task_no)//��������
	 {
		  LCD_ShowString(279-15,0,32,16,16,"X:");	 
			LCD_ShowString(279-15,17,32,16,16,"Y:");
			sprintf(buf1,"��������");//��LCD ID��ӡ��lcd_id���顣 
			speak_len1=strlen(buf1);
			speak_context((u8*)buf1,speak_len1);
		 //��ʾ���꣬�켣
		 while(1) 
		{	
			

			//�ȴ���������
			 if(key_flag==1)
			 {
				 key_flag=0;
				 //����1�����������
				 
				 Uart1_OutPut_Buffer[0]=0xa5;
					Uart1_OutPut_Buffer[1]=0x5a;
					Uart1_OutPut_Buffer[2]=0x01;
					
					Uart1_OutPut_Buffer[3]=0x01;
					Uart1_OutPut_Buffer[4]=0x01;//01 gbk //00 gb2312
					Uart1_OutPut_Buffer[5]=0xfd;//01 gbk //00 gb2312
				 

					for( int u1_i = 0 ; u1_i < 6; u1_i++) 
					{
						while((USART1->SR&0X40)==0);  
						USART1->DR = Uart1_OutPut_Buffer[u1_i]; 
					}
//					if(key_num==0)
//					{
//						//ǰ��
//						test_car_forward();
//					}
//					else if(key_num==1)
//					{
//						//����
//						test_car_back();
//					}
//					else if(key_num==2)
//					{
//						//ֹͣ
//						test_car_stop();
//					}
			 }
				
				
				
				uart1_camera_command_analyse();
				
				delay_ms(10);
		} 
	 }
  	

 
 
	 if(1==task_no)//��������
	 {
		 sprintf(buf1,"��������");//��LCD ID��ӡ��lcd_id���顣 
			speak_len1=strlen(buf1);
			speak_context((u8*)buf1,speak_len1);
		  LCD_ShowString(279-15,16*11,32,16,16,"X:");	 
			 LCD_ShowString(279-15,16*12,32,16,16,"Y:");
		  LCD_ShowString(279-15,0,32,16,16,"X:");	 
			LCD_ShowString(279-15,17,32,16,16,"Y:");
		 //��ʾ���꣬�켣
		 delay_ms(2000);
		 delay_ms(2000);
		 while(1) 
		{	

			//�ȴ���������
			 if(key_flag==1)
			 {
				 key_flag=0;
				 //����1�����������
				 
				 Uart1_OutPut_Buffer[0]=0xa5;
					Uart1_OutPut_Buffer[1]=0x5a;
					Uart1_OutPut_Buffer[2]=0x01;
					
					Uart1_OutPut_Buffer[3]=0x01;
					Uart1_OutPut_Buffer[4]=0x01;//01 gbk //00 gb2312
					Uart1_OutPut_Buffer[5]=0xfd;//01 gbk //00 gb2312
				 

					for( int u1_i = 0 ; u1_i < 6; u1_i++) 
					{
						while((USART1->SR&0X40)==0);  
						USART1->DR = Uart1_OutPut_Buffer[u1_i]; 
					}
					
					dis=30;
					
					
					y_orign=t265.pos_y_f;
					walk_alone_y_axis_forward();
			 }	
				
				
				uart2_camera_command_analyse();
				uart1_camera_command_analyse();
				uart3_camera_command_analyse();
			 
			
				
				delay_ms(10);
		} 
	 }
  	

  
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 }


