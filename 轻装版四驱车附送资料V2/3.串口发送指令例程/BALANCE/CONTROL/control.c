#include "control.h"	
#include "filter.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
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
�������ܣ����еĿ��ƴ��붼��������
         5ms��ʱ�ж���MPU6050��INT���Ŵ���
         �ϸ�֤���������ݴ����ʱ��ͬ��				 
**************************************************************************/
int EXTI9_5_IRQHandler(void) 
{    
	 if(PBin(5)==0)		
	{   
		  EXTI->PR=1<<5;                                                      //���LINE5�ϵ��жϱ�־λ   
		   Flag_Target=!Flag_Target;
		  if(delay_flag==1)
			 {
				 if(++delay_50==10)	 delay_50=0,delay_flag=0;                     //���������ṩ50ms�ľ�׼��ʱ
			 }
		  if(Flag_Target==1)                                                  //5ms��ȡһ�������Ǻͼ��ٶȼƵ�ֵ�����ߵĲ���Ƶ�ʿ��Ը��ƿ������˲��ͻ����˲���Ч��
			{
			Get_Angle(Way_Angle);                                               //===������̬	
			return 0;	                                               
			}                                                                   //10ms����һ�Σ�Ϊ�˱�֤M�����ٵ�ʱ���׼�����ȶ�ȡ����������
			Encoder_A=-Read_Encoder(2);                                          //===��ȡ��������ֵ
			Encoder_B=-Read_Encoder(3);                                          //===��ȡ��������ֵ
			Encoder_C=-Read_Encoder(4);                                          //===��ȡ��������ֵ
	  	Get_Angle(Way_Angle);                                               //===������̬	
  		Led_Flash(100);                                                     //===LED��˸;����ģʽ 1s�ı�һ��ָʾ�Ƶ�״̬	
  		Voltage=Get_battery_volt();                                         //===��ȡ��ص�ѹ	          
			//Key();                                                              //===ɨ�谴��״̬ 
			
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

 		  Motor_A=Incremental_PI_A(Encoder_A,Target_A);                         //===������A����PWM
 	    Motor_B=Incremental_PI_B(Encoder_B,Target_B);                         //===������B����PWM
			Motor_C=Incremental_PI_C(Encoder_C,Target_C);                         //===������C����PWM
   	  //	Xianfu_Pwm();                                                       //===PWM�޷�
		
      //if(Turn_Off(Angle_Balance,Voltage)==0)                            //===����������쳣
    if(rxbuf[0]==3)Motor_A=rxbuf[1]*256+rxbuf[2],			             Motor_B=rxbuf[3]*256+rxbuf[4],		               Motor_C=rxbuf[5]*256+rxbuf[6];
	    Set_Pwm(Motor_A,Motor_B,-Motor_B);                                   //===��ֵ��PWM�Ĵ���  	
	    
    			
	 
 }
	 return 0;	 
} 


/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
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
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	  int Amplitude=6900;    //===PWM������7200 ������6900
    if(Motor_A<-Amplitude) Motor_A=-Amplitude;	
		if(Motor_A>Amplitude)  Motor_A=Amplitude;	
	  if(Motor_B<-Amplitude) Motor_B=-Amplitude;	
		if(Motor_B>Amplitude)  Motor_B=Amplitude;		
	  if(Motor_C<-Amplitude) Motor_C=-Amplitude;	
		if(Motor_C>Amplitude)  Motor_C=Amplitude;		
}
/**************************************************************************
�������ܣ������޸�С������״̬ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Key(void)
{	
	u8 tmp;
	tmp=click_N_Double(50); 
	if(tmp==1)Flag_Stop=!Flag_Stop;//��������С������ͣ
	if(tmp==2)Flag_Show=!Flag_Show;//˫������С������ʾ״̬
//	tmp2=Long_Press();                   

}

/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������Ǻ͵�ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
u8 Turn_Off(float angle, int voltage)
{
	    u8 temp;
			if(angle<-40||angle>40||1==Flag_Stop||voltage<1110)//��ص�ѹ����11.1V�رյ��
			{	                                                 //===��Ǵ���40�ȹرյ��
      temp=1;                                            //===Flag_Stop��1�رյ��
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
�������ܣ���ȡ�Ƕ� �����㷨�������ǵĵ�У�����ǳ����� 
��ڲ�������ȡ�Ƕȵ��㷨 1��DMP  2�������� 3�������˲�
����  ֵ����
**************************************************************************/
void Get_Angle(u8 way)
{ 
	    float Accel_Y,Accel_X,Accel_Z,Gyro_Y,Gyro_Z;
	   	Temperature=Read_Temperature();      //===��ȡMPU6050�����¶ȴ��������ݣ����Ʊ�ʾ�����¶ȡ�
	    if(way==1)                           //===DMP�Ķ�ȡ�����ݲɼ��ж����ѵ�ʱ���ϸ���ѭʱ��Ҫ��
			{	
					Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
			}			
      else
      {
			Gyro_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //��ȡY��������
			Gyro_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_ZOUT_L);    //��ȡZ��������
		  Accel_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //��ȡX����ٶȼ�
	  	Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
		  if(Gyro_Y>32768)  Gyro_Y-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
			if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
	  	if(Accel_X>32768) Accel_X-=65536;                      //��������ת��
		  if(Accel_Z>32768) Accel_Z-=65536;                      //��������ת��
			Gyro_Balance=-Gyro_Y;                                  //����ƽ����ٶ�
	   	Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //�������	
		  Gyro_Y=Gyro_Y/16.4;                                    //����������ת��	
      if(Way_Angle==2)		  	Kalman_Filter(Accel_Y,-Gyro_Y);//�������˲�	
			else if(Way_Angle==3)   Yijielvbo(Accel_Y,-Gyro_Y);    //�����˲�
	    Angle_Balance=angle;                                   //����ƽ�����
			Gyro_Turn=Gyro_Z;                                      //����ת����ٶ�
		}
}
/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
   float Kp=2,Ki=3;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
   float Kp=2,Ki=3;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
   float Kp=2,Ki=3;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
/**************************************************************************
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
int Position_PID (int Encoder,int Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 float Position_KP,Position_KI,Position_KD;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
}

