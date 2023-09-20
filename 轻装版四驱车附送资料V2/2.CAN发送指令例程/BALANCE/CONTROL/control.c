#include "control.h"	
#include "filter.h"	
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
u8 Flag_Target;
#define VX_VALUE           (0.5f)
#define VY_VALUE           (sqrt(3)/2.f)      
#define L_value            (20*0.01f)  
#define RADIUS_value       (1.0/12.5*0.01f)
void Speed_Moto_Control(float vx,float vy,float vz)
{
        Target_C   = (-VX_VALUE*vx + VY_VALUE*vy + L_value*vz)-Gyro_Turn*0.04;
        Target_B   = (-VX_VALUE*vx - VY_VALUE*vy + L_value*vz)-Gyro_Turn*0.04;
        Target_A = (vx + L_value*vz)-Gyro_Turn*0.04;
}

/**************************************************************************
函数功能：所有的控制代码都在这里面
         5ms定时中断由MPU6050的INT引脚触发
         严格保证采样和数据处理的时间同步				 
**************************************************************************/
int EXTI9_5_IRQHandler(void) 
{    
	 if(PBin(5)==0)		
	{   
		  EXTI->PR=1<<5;                                                      //清除LINE5上的中断标志位   
		   Flag_Target=!Flag_Target;
		  if(delay_flag==1)
			 {
				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //给主函数提供50ms的精准延时
			 }
		  if(Flag_Target==1)                                                  //5ms读取一次陀螺仪和加速度计的值，更高的采样频率可以改善卡尔曼滤波和互补滤波的效果
			{
			Get_Angle(Way_Angle);                                               //===更新姿态	
			return 0;	                                               
			}                                                                   //10ms控制一次，为了保证M法测速的时间基准，首先读取编码器数据
			Encoder_A=-Read_Encoder(2);                                          //===读取编码器的值
			Encoder_B=-Read_Encoder(3);                                          //===读取编码器的值
			Encoder_C=-Read_Encoder(4);                                          //===读取编码器的值
	  	Get_Angle(Way_Angle);                                               //===更新姿态	
  		Led_Flash(100);                                                     //===LED闪烁;常规模式 1s改变一次指示灯的状态	
  		Voltage=Get_battery_volt();                                         //===获取电池电压	          
			//Key();                                                              //===扫描按键状态 
			
				if(Flag_Left==1)  Speed_Moto_Control(0,0,Velocity*13);
			else if(Flag_Right==1)  Speed_Moto_Control(0,0,-Velocity*13);
			
			else if(Flag_Direction==1) Speed_Moto_Control(0,Velocity,0);
      else   if(Flag_Direction==5) Speed_Moto_Control(0,-Velocity,0);
		  else	if(Flag_Direction==3) Speed_Moto_Control(-Velocity,0,0);
      else   if(Flag_Direction==7) Speed_Moto_Control(Velocity,0,0);
	   	else  if(Flag_Direction==2) Speed_Moto_Control(-Velocity,Velocity,0);
	  	else	if(Flag_Direction==4) Speed_Moto_Control(-Velocity,-Velocity,0);
			else	if(Flag_Direction==6) Speed_Moto_Control(Velocity,-Velocity,0);
			else	if(Flag_Direction==8) Speed_Moto_Control(Velocity,Velocity,0);
			else Speed_Moto_Control(0,0,0);
			if(rxbuf[0]==1)Speed_Moto_Control(rxbuf[1],rxbuf[2],rxbuf[3]);
			if(rxbuf[0]==2)Target_A=rxbuf[1],Target_B=rxbuf[2],Target_C=rxbuf[3];

 		  Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         //===计算电机A最终PWM
 	    Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         //===计算电机B最终PWM
			Motor_C=Incremental_PI_C(Encoder_C,Target_C);                         //===计算电机C最终PWM
   	  //	Xianfu_Pwm();                                                       //===PWM限幅
		
      //if(Turn_Off(Angle_Balance,Voltage)==0)                            //===如果不存在异常
    if(rxbuf[0]==3)Motor_A=rxbuf[1]*256+rxbuf[2],			             Motor_B=rxbuf[3]*256+rxbuf[4],		               Motor_C=rxbuf[5]*256+rxbuf[6];
	    Set_Pwm(Motor_A,Motor_B,-Motor_B);                                   //===赋值给PWM寄存器  	
	    
    			
	 
 }
	 return 0;	 
} 


/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int motor_c)
{
    	if(motor_a>0)			PWMA2=7200,PWMA1=7200-motor_a;
			else 	            PWMA1=7200,PWMA2=7200+motor_a;
		
		  if(motor_b>0)			PWMB2=7200,PWMB1=7200-motor_b;
			else 	            PWMB1=7200,PWMB2=7200+motor_b;
	
	    if(motor_c>0)			PWMC2=7200,PWMC1=7200-motor_c;
			else 	            PWMC1=7200,PWMC2=7200+motor_c;
}

/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM满幅是7200 限制在6900
    if(Motor_A<-Amplitude) Motor_A=-Amplitude;	
		if(Motor_A>Amplitude)  Motor_A=Amplitude;	
	  if(Motor_B<-Amplitude) Motor_B=-Amplitude;	
		if(Motor_B>Amplitude)  Motor_B=Amplitude;		
	  if(Motor_C<-Amplitude) Motor_C=-Amplitude;	
		if(Motor_C>Amplitude)  Motor_C=Amplitude;		
}
/**************************************************************************
函数功能：按键修改小车运行状态 
入口参数：无
返回  值：无
**************************************************************************/
void Key(void)
{	
	u8 tmp;
	tmp=click_N_Double(50); 
	if(tmp==1)Flag_Stop=!Flag_Stop;//单击控制小车的启停
	if(tmp==2)Flag_Show=!Flag_Show;//双击控制小车的显示状态
//	tmp2=Long_Press();                   

}

/**************************************************************************
函数功能：异常关闭电机
入口参数：倾角和电压
返回  值：1：异常  0：正常
**************************************************************************/
u8 Turn_Off(float angle, int voltage)
{
	    u8 temp;
			if(angle<-40||angle>40||1==Flag_Stop||voltage<1110)//电池电压低于11.1V关闭电机
			{	                                                 //===倾角大于40度关闭电机
      temp=1;                                            //===Flag_Stop置1关闭电机
			PWMA1=0;                                            
			PWMB1=0;
			PWMC1=0;
			PWMA2=0;
			PWMB2=0;
			PWMC2=0;
      }
			else
      temp=0;
      return temp;			
}
	
/**************************************************************************
函数功能：获取角度 三种算法经过我们的调校，都非常理想 
入口参数：获取角度的算法 1：DMP  2：卡尔曼 3：互补滤波
返回  值：无
**************************************************************************/
void Get_Angle(u8 way)
{ 
	    float Accel_Y,Accel_X,Accel_Z,Gyro_Y,Gyro_Z;
	   	Temperature=Read_Temperature();      //===读取MPU6050内置温度传感器数据，近似表示主板温度。
	    if(way==1)                           //===DMP的读取在数据采集中断提醒的时候，严格遵循时序要求
			{	
					Read_DMP();                      //===读取加速度、角速度、倾角
			}			
      else
      {
			Gyro_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //读取Y轴陀螺仪
			Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //读取Z轴陀螺仪
		  Accel_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //读取X轴加速度计
	  	Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //读取Z轴加速度计
		  if(Gyro_Y>32768)  Gyro_Y-=65536;                       //数据类型转换  也可通过short强制类型转换
			if(Gyro_Z>32768)  Gyro_Z-=65536;                       //数据类型转换
	  	if(Accel_X>32768) Accel_X-=65536;                      //数据类型转换
		  if(Accel_Z>32768) Accel_Z-=65536;                      //数据类型转换
			Gyro_Balance=-Gyro_Y;                                  //更新平衡角速度
	   	Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //计算倾角	
		  Gyro_Y=Gyro_Y/16.4;                                    //陀螺仪量程转换	
      if(Way_Angle==2)		  	Kalman_Filter(Accel_Y,-Gyro_Y);//卡尔曼滤波	
			else if(Way_Angle==3)   Yijielvbo(Accel_Y,-Gyro_Y);    //互补滤波
	    Angle_Balance=angle;                                   //更新平衡倾角
			Gyro_Turn=Gyro_Z;                                      //更新转向角速度
		}
}
/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
   float Kp=2,Ki=3;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
   float Kp=2,Ki=3;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
   float Kp=2,Ki=3;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
int Position_PID (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 float Position_KP,Position_KI,Position_KD;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}

