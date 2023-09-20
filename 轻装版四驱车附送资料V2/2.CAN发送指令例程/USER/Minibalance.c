#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
u8 Way_Angle=1;                             //获取角度的算法，1：四元数  2：卡尔曼  3：互补滤波 
u8 Flag_Qian,Flag_Hou,Flag_Left,Flag_Right,Flag_Direction=0; //蓝牙遥控相关的变量
u8 Flag_Stop=1,Flag_Show=0;                 //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_A,Encoder_B,Encoder_C;             //编码器的脉冲计数
int Encoder_A_EXTI;
int Motor_A,Motor_B,Motor_C;                   //电机PWM变量
int Target_A,Target_B,Target_C;                   //电机目标速度
int Temperature;                            //显示温度
int Voltage;                                //电池电压采样相关的变量
float Angle_Balance,Gyro_Balance,Gyro_Turn; //平衡倾角 平衡陀螺仪 转向陀螺仪
float Show_Data_Mb;                         //全局显示变量，用于显示需要查看的数据
u32 Distance;                               //超声波测距
u8 delay_50,delay_flag;         //默认情况下，不开启避障功能，长按用户按键2s以上可以进入避障模式
int Velocity=30;
u8 Usart3_Receive;
u8 rxbuf[8],Rxbuf[16];
u8 txbuf[8];
int AZ,GZ;
float Pitch,Roll,Yaw; 
u32 count,usart_count;
int temp,temp2,temp3,count_temp,flag;
u8 ON_txbuf[8]={10,12,15,19,24,30,37,1} ;
u8 Velocity_txbuf[8]={11,13,16,20,25,31,38,50} ; 

int main(void)
{ 
	 float i;
	Stm32_Clock_Init(9);            //=====系统时钟设置
	delay_init(72);                 //=====延时初始化
   uart_init(72,128000);           //=====初始化串口1
   uart2_init(36,128000);            //=====串口2初始化
	  Timer1_Init(499,7199);
	CAN1_Mode_Init(1,2,3,6,0);  //CAN初始化
		while(1)
		{    	
	    	if(++count==1)
				{	
        memcpy(txbuf,ON_txbuf,8*sizeof(u8));
				}
				else
				{	
				txbuf[0]=32;
				txbuf[1]=1;
				txbuf[2]=40;	
				txbuf[3]=0;		
			  txbuf[4]=0;
				txbuf[5]=0;	
	  		txbuf[6]=0;
				txbuf[7]=0;							
				}
				CAN1_SEND(0X121,txbuf);//CAN发送
		    
/***********CAN发送数据*********************************/
     
/***********串口打印接收数据*********************************/
//			  Pitch= (float)((Rxbuf[0]*256+Rxbuf[1])-30000)/100;
//        Roll = (float)((Rxbuf[2]*256+Rxbuf[3])-30000)/100;
//			  Yaw  = (float)((Rxbuf[4]*256+Rxbuf[5])-30000)/100;
//		  	GZ   = (float)(Rxbuf[6]*256+Rxbuf[7])-32768;
//			  Encoder_A=(1-Rxbuf[9])*Rxbuf[8];
//				Encoder_B=(1-Rxbuf[11])*Rxbuf[10];
//				Encoder_C=(1-Rxbuf[13])*Rxbuf[12];
//		  	Voltage=Rxbuf[14];
//			
//			  printf("Encoder_A:%d\r\n",Encoder_A);
//			  printf("Encoder_B:%d\r\n",Encoder_B);
//		  	printf("Encoder_C:%d\r\n",Encoder_C);
//			
//				printf("Pitch:%f\r\n",Pitch);
//			  printf("Roll:%f\r\n",Roll);
//			  printf("Yaw:%f\r\n",Yaw);
//			
//			  printf("GZ:%d\r\n",GZ);
//		  	printf("Voltage:%d\r\n",Voltage);
/***********串口发送数据*********************************/


//		   	usart2_send(0xff);
//				usart2_send(0xfe);	
//				usart2_send(1);
//				usart2_send(0);
//				usart2_send(0);
//				usart2_send(0);
//				usart2_send(45);
//				usart2_send(0);
//				usart2_send(0);
//				usart2_send(0x07);
	

		} 
}
