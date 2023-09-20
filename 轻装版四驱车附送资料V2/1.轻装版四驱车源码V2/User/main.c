#include "stm32f10x.h"
#include "sys.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
u8 Flag_Left,Flag_Right,Flag_Direction=0,Flag_Way,Flag_Next,Turn_Flag;   //蓝牙遥控相关的变量
u8 Flag_Stop=1; //停止标志位和 显示标志位 默认停止 显示打开
int Encoder_A,Encoder_B,Encoder_C,Encoder_D;  //编码器的脉冲计数
long int Position_A,Position_B,Position_C,Position_D,Rate_A,Rate_B,Rate_C,Rate_D; //PID控制相关变量                     
long int Motor_A,Motor_B,Motor_C,Motor_D; //电机PWM变量
long int Target_A,Target_B,Target_C,Target_D; //电机目标值
int Voltage;//电池电压采样相关的变量                       
u8 delay_50,delay_flag; //延时相关变量
u8 Run_Flag=0;  //速度或者位置模式指示变量
u8 rxbuf[8],Urxbuf[8],CAN_ON_Flag=0,Usart_ON_Flag=0,Usart_Flag,PID_Send;  //CAN和串口控制相关变量
u8 txbuf[8],txbuf2[8];  //CAN发送相关变量
float Pitch,Roll,Yaw,Gryo_Z,Move_X,Move_Y,Move_Z;   //三轴角度 Z轴陀螺仪和XYZ轴目标速度
float	Position_KP=14,Position_KI=0,Position_KD=25;  //位置控制PID参数
float Velocity_KP=10,Velocity_KI=10;	          //速度控制PID参数
int RC_Velocity=30,RC_Position=3000;         //设置遥控的速度和位置值
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY; //PS2相关变量 
u16 CCD_Zhongzhi,CCD_Yuzhi,ADV[128]={0};//CCD相关变量
int Sensor_Left,Sensor_Middle,Sensor_Right,Sensor;//电磁巡线相关
int main(void)
  { 
		delay_init();	    	            //=====延时函数初始化	
	//JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
		JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
		LED_Init();                     //=====初始化与 LED 连接的硬件接口
	  KEY_Init();                     //=====按键初始化
		MY_NVIC_PriorityGroupConfig(2);	//=====设置中断分组
    MiniBalance_PWM_Init(7199,0);   //=====初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口 
		uart2_init(9600);               //=====串口2初始化
		uart3_init(115200);             //=====串口3初始化 
		OLED_Init();                    //=====OLED初始化	    
    Encoder_Init_TIM2();            //=====编码器接口
		Encoder_Init_TIM3();            //=====编码器接口
		Encoder_Init_TIM4();            //=====编码器接口
    Encoder_Init_TIM5();            //=====初始化编码器
		if(Run_Flag==0){ while(select())	{	}	} //=====选择运行模式 
		else Flag_Stop=0;//===位置模式直接使能电机
		delay_ms(500);                  //=====延时
    IIC_Init();                     //=====IIC初始化
    MPU6050_initialize();           //=====MPU6050初始化	
  	DMP_Init();                     //=====初始化DMP   
		CAN1_Mode_Init(1,2,3,6,0);			//=====CAN初始化,波特率1Mbps
		Adc_Init();                     //=====adc初始化		
	 if(Flag_Way==1)
	  {
		PS2_Init();											//=====PS2手柄初始化
		PS2_SetInit();									//=====ps2配置初始化,配置“红绿灯模式”，并选择是否可以修改
	  }
	  else if(Flag_Way==2)ccd_Init();  //=====CCD初始化
	  else if(Flag_Way==3)ele_Init();  //=====电磁传感器初始化	
	  MiniBalance_EXTI_Init();        //=====MPU6050 5ms定时中断初始化
    while(1)
	   {	
			   if(Flag_Way==1)
			   {
					  PS2_LX=PS2_AnologData(PSS_LX);    //PS2数据采集    
						PS2_LY=PS2_AnologData(PSS_LY);
						PS2_RX=PS2_AnologData(PSS_RX);
						PS2_RY=PS2_AnologData(PSS_RY);
						PS2_KEY=PS2_DataKey();	
			   }
				  if(Flag_Way==0)
			   {
				  CAN1_SEND();             //CAN发送		
          USART_TX();               //串口发送
				 }
					APP_Show();	       //APP相关
					oled_show();          //===显示屏打开
	  } 
}

