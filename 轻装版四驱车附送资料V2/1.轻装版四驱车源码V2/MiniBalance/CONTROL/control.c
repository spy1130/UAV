#include "control.h"	
#include "filter.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/

u8 Flag_Target,Flag_Change;  //��ر�־λ
float Voltage_Count,Voltage_All;  //��ѹ������ر���
float Gyro_K=0.004;       //�����Ǳ���ϵ��
int j,sum;
//#define a_PARAMETER          (0.079f)   
#define a_PARAMETER          (0.5f)  
/**************************************************************************
�������ܣ�С���˶���ѧģ��
��ڲ�����X Y Z �����ٶȻ���λ��
����  ֵ����
**************************************************************************/
void Kinematic_Analysis(float Vy,float Vz)
{
        Target_A   = Vy-Vz*(a_PARAMETER);
        Target_B   = Vy-Vz*(a_PARAMETER);
	      Target_C   = Vy+Vz*(a_PARAMETER);
				Target_D   = Vy+Vz*(a_PARAMETER);  
}
/**************************************************************************
�������ܣ���ȡλ�ÿ��ƹ����ٶ�ֵ
��ڲ�����X Y Z ����λ�ñ仯��
����  ֵ����
**************************************************************************/
void Kinematic_Analysis2(float Vy,float Vz)
{
	      Rate_A   = Vy-Vz*(a_PARAMETER)*10;
        Rate_B   = Vy-Vz*(a_PARAMETER)*10;
	      Rate_C   = Vy+Vz*(a_PARAMETER)*10;
				Rate_D   = Vy+Vz*(a_PARAMETER)*10;
}
/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
         5ms��ʱ�ж���MPU6050��INT���Ŵ���
         �ϸ�֤���������ݴ����ʱ��ͬ��				 
**************************************************************************/
int EXTI9_5_IRQHandler(void) 
{    
	 if(INT==0)		
	{     
		   EXTI->PR=1<<5;   //���LINE5�ϵ��жϱ�־λ  		
		   Flag_Target=!Flag_Target;
		  if(Flag_Target==1)   //5ms��ȡһ�������Ǻͼ��ٶȼƵ�ֵ
			{
					if(Usart_Flag==0&&Usart_ON_Flag==1)  memcpy(rxbuf,Urxbuf,8*sizeof(u8));	//��������˴��ڿ��Ʊ�־λ�����봮�ڿ���ģʽ
					Read_DMP();   //===������̬		
					 if(Flag_Way==2)
					 {	 
								RD_TSL();  //===��ȡ����CCD���� 
						 	  Find_CCD_Zhongzhi(); //===��ȡ���� 
					 }
					 if(Flag_Way==3)		
					 {
					 			Sensor_Left=Get_Adc(11);                //�ɼ���ߵ�е�����
								Sensor_Right=Get_Adc(13);               //�ɼ��ұߵ�е�����
								Sensor_Middle=Get_Adc(12);              //�ɼ��м��е�����
					  	  sum=Sensor_Left*1+Sensor_Middle*100+Sensor_Right*199;  //��һ������
								Sensor=sum/(Sensor_Left+Sensor_Middle+Sensor_Right);   //��ƫ��
					 }						 
			  	Key();//ɨ�谴���仯	
			return 0;	                                               
			}     //===10ms����һ�Σ�Ϊ�˱�֤M�����ٵ�ʱ���׼�����ȶ�ȡ����������
			Encoder_A=-Read_Encoder(2);  //===��ȡ��������ֵ
			Position_A+=Encoder_A;      //===���ֵõ��ٶ�   
			Encoder_B=-Read_Encoder(3);  //===��ȡ��������ֵ
			Position_B+=Encoder_B;      //===���ֵõ��ٶ�   
			Encoder_C=Read_Encoder(4);  //===��ȡ��������ֵ
			Position_C+=Encoder_C;      //===���ֵõ��ٶ�   
			Encoder_D=Read_Encoder(5);  //===��ȡ��������ֵ
			Position_D+=Encoder_D;      //===���ֵõ��ٶ�   
	  	Read_DMP();  //===������̬	
  		Led_Flash(100);  //===LED��˸;����ģʽ 1s�ı�һ��ָʾ�Ƶ�״̬	
			Voltage_All+=Get_battery_volt(); //��β����ۻ�
			if(++Voltage_Count==100) Voltage=Voltage_All/100,Voltage_All=0,Voltage_Count=0;//��ƽ��ֵ ��ȡ��ص�ѹ	   
		 if(Turn_Off(Voltage)==0)   //===�����ص�ѹ�������쳣
		 { 			 
		  if(Run_Flag==0)//�ٶ�ģʽ
			{		
			  Get_RC();   //===���ں�CAN���ƶ�δʹ�ܣ����������ң��ָ
				Motor_A=Incremental_PI_A(Encoder_A,Target_A);  //===�ٶȱջ����Ƽ�����A����PWM
				Motor_B=Incremental_PI_B(Encoder_B,Target_B);  //===�ٶȱջ����Ƽ�����B����PWM
				Motor_C=Incremental_PI_C(Encoder_C,Target_C);  //===�ٶȱջ����Ƽ�����C����PWM
		    Motor_D=Incremental_PI_D(Encoder_D,Target_D);  //===�ٶȱջ����Ƽ�����C����PWM
			}
		 Xianfu_Pwm(6900);                     //===PWM�޷�
		 Set_Pwm(Motor_A,Motor_B,Motor_C,Motor_D);     //===��ֵ��PWM�Ĵ���  
		 }
 }
	 return 0;	 
} 
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
**************************************************************************/
void Set_Pwm(int motor_a,int motor_b,int motor_c,int motor_d)
{
	  	if(motor_a>0)			PWMA1=7200,PWMA2=7200-motor_a;
			else 	            PWMA2=7200,PWMA1=7200+motor_a;
		
		  if(motor_b>0)			PWMB1=7200,PWMB2=7200-motor_b;
			else 	            PWMB2=7200,PWMB1=7200+motor_b;
	
	    if(motor_c>0)			PWMC1=7200,PWMC2=7200-motor_c;
			else 	            PWMC2=7200,PWMC1=7200+motor_c;
		
	    if(motor_d>0)			PWMD1=7200,PWMD2=7200-motor_d;
			else 	            PWMD2=7200,PWMD1=7200+motor_d;
}
/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������ֵ
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(int amplitude)
{	
    if(Motor_A<-amplitude) Motor_A=-amplitude;	
		if(Motor_A>amplitude)  Motor_A=amplitude;	
	  if(Motor_B<-amplitude) Motor_B=-amplitude;	
		if(Motor_B>amplitude)  Motor_B=amplitude;		
	  if(Motor_C<-amplitude) Motor_C=-amplitude;	
		if(Motor_C>amplitude)  Motor_C=amplitude;		
	  if(Motor_D<-amplitude) Motor_D=-amplitude;	
	  if(Motor_D>amplitude)  Motor_D=amplitude;		
}
/**************************************************************************
�������ܣ�λ��PID���ƹ������ٶȵ�����
��ڲ������ޡ���ֵ
����  ֵ����
**************************************************************************/
void Xianfu_Velocity(int amplitude_A,int amplitude_B,int amplitude_C,int amplitude_D)
{	
    if(Motor_A<-amplitude_A) Motor_A=-amplitude_A;	//λ�ÿ���ģʽ�У�A����������ٶ�
		if(Motor_A>amplitude_A)  Motor_A=amplitude_A;	  //λ�ÿ���ģʽ�У�A����������ٶ�
	  if(Motor_B<-amplitude_B) Motor_B=-amplitude_B;	//λ�ÿ���ģʽ�У�B����������ٶ�
		if(Motor_B>amplitude_B)  Motor_B=amplitude_B;		//λ�ÿ���ģʽ�У�B����������ٶ�
	  if(Motor_C<-amplitude_C) Motor_C=-amplitude_C;	//λ�ÿ���ģʽ�У�C����������ٶ�
		if(Motor_C>amplitude_C)  Motor_C=amplitude_C;		//λ�ÿ���ģʽ�У�C����������ٶ�
		if(Motor_D<-amplitude_D) Motor_D=-amplitude_D;	//λ�ÿ���ģʽ�У�C����������ٶ�
		if(Motor_D>amplitude_D)  Motor_D=amplitude_D;		//λ�ÿ���ģʽ�У�C����������ٶ�
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
	if(tmp==1)Flag_Stop=!Flag_Stop;//�������Ƶ����ͣ                  
}
/**************************************************************************
�������ܣ��쳣�رյ��
��ڲ�������ѹ
����  ֵ��1���쳣  0������
**************************************************************************/
u8 Turn_Off( int voltage)
{
	    u8 temp;
			if(voltage<1110||Flag_Stop==1)//��ص�ѹ����11.1V�رյ��
			{	                                                
      temp=1;      
     	PWMA1=0; //�������λ����                                           
			PWMB1=0; //�������λ����
			PWMC1=0; //�������λ����
			PWMD1=0; //�������λ����
			PWMA2=0; //�������λ����
			PWMB2=0; //�������λ����
			PWMC2=0; //�������λ����	
      PWMD2=0; //�������λ����						
      }
			else
      temp=0;
      return temp;			
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����long int
����  ֵ��unsigned int
**************************************************************************/
u32 myabs(long int a)
{ 		   
	  u32 temp;
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
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_C (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_D (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Pwm+=Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;   //����ʽPI������
	 if(Pwm>7200)Pwm=7200;
	 if(Pwm<-7200)Pwm=-7200;
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}

/**************************************************************************
�������ܣ�ͨ��ָ���С������ң��
��ڲ���������ָ��
����  ֵ����
**************************************************************************/
void Get_RC(void)
{
	float step=0.5;   //�����ٶȿ��Ʋ���ֵ��
	int Yuzhi=2;  		//PS2���Ʒ�����ֵ
	float LY,RX,RY;  //PS2�ֱ����Ʊ���
	static float Bias,Last_Bias;  //ƫ�����ʷֵ
	int flag_Y,flag_Z;
	if(Flag_Way==0)//���ڵȿ��Ʒ�ʽ
	{
					 if(CAN_ON_Flag==0&&Usart_ON_Flag==0) 
					 {
						 switch(Flag_Direction)   //�������
						 {
						 case 0:      Move_Y=0; 			 			 	 Move_Z=0;        	 break;	 
						 case 1:      Move_Y+=step;  	 				 Move_Z=0;       		 break;
						 case 2:      Move_Y+=step;  	 	 			 Move_Z-=step;   	 	 break;
						 case 3:      Move_Y=0;      				 	 Move_Z-=step;   		 break;
						 case 4:      Move_Y-=step;  					 Move_Z+=step; 			 break;
						 case 5:      Move_Y-=step;  					 Move_Z=0;       		 break;
						 case 6:      Move_Y-=step;  					 Move_Z-=step;   		 break;
						 case 7:      Move_Y=0;     	 			 	 Move_Z+=step;			 break;
						 case 8:      Move_Y+=step; 	 				 Move_Z+=step;			 break; 
						 default:     break;	 
					 }
						if(Move_Y<-RC_Velocity) Move_Y=-RC_Velocity;	
						if(Move_Y>RC_Velocity)  Move_Y=RC_Velocity;	 
						if(Move_Z<-RC_Velocity) Move_Z=-RC_Velocity;	
						if(Move_Z>RC_Velocity)  Move_Z=RC_Velocity;	 
					}		
					else
				 {
					   if(rxbuf[1]==0)Move_Y=rxbuf[0]; //ʶ���˶�����
						 else           Move_Y=-rxbuf[0]; //�ٶ�
					   if(rxbuf[3]==0)Move_Z=rxbuf[2]; //ʶ���˶�����
						 else           Move_Z=-rxbuf[2]; //�ٶ�			 
				 }
	}
	else	if(Flag_Way==1)//PS2����
		{
			RY=PS2_RY-128; //��ȡƫ��
			LY=PS2_LY-128; //��ȡƫ��
			RX=PS2_RX-128; //��ȡƫ��
			if(RY>-Yuzhi&&RY<Yuzhi)RY=0; //����С�Ƕȵ�����
			if(LY>-Yuzhi&&LY<Yuzhi)LY=0; //����С�Ƕȵ�����
			if(RX>-Yuzhi&&RX<Yuzhi)RX=0; //����С�Ƕȵ�����
			 Move_Y=-LY*RC_Velocity/200-RY/4;	//�ٶȺ�����
			 Move_Z=-RX*RC_Velocity/200;		
		}
			else	if(Flag_Way==2)//CCDѲ��
		{
			 RC_Velocity=45;//Ѳ���ٶ�
	   	 Move_Y=RC_Velocity;
			 Bias=CCD_Zhongzhi-64;   //��ȡƫ��
			 Move_Z=-Bias*0.8-(Bias-Last_Bias)*5; //PD����
			 Last_Bias=Bias;   //������һ�ε�ƫ��
		}
			else	if(Flag_Way==3)//���Ѳ��
		{
			 RC_Velocity=45;//Ѳ���ٶ�
			 Move_Y=RC_Velocity;
			 Bias=100-Sensor;  //��ȡƫ��
			 Move_Z=abs(Bias)*Bias*0.01+Bias*0.1+(Bias-Last_Bias)*9; //
			 Last_Bias=Bias;   //��һ�ε�ƫ��
		}	
		 Kinematic_Analysis(Move_Y,Move_Z);//�õ�����Ŀ��ֵ�������˶�ѧ����
}

/**************************************************************************
�������ܣ�����CCDȡ��ֵ
��ڲ�������
����  ֵ����
**************************************************************************/
void  Find_CCD_Zhongzhi(void)
{ 
	 static u16 i,j,Left,Right,Last_CCD_Zhongzhi;
	 static u16 value1_max,value1_min;
	
	   value1_max=ADV[0];  //��̬��ֵ�㷨����ȡ������Сֵ
     for(i=5;i<123;i++)   //���߸�ȥ��5����
     {
        if(value1_max<=ADV[i])
        value1_max=ADV[i];
     }
	   value1_min=ADV[0];  //��Сֵ
     for(i=5;i<123;i++) 
     {
        if(value1_min>=ADV[i])
        value1_min=ADV[i];
     }
   CCD_Yuzhi=(value1_max+value1_min)/2;	  //���������������ȡ����ֵ
	 for(i = 5;i<118; i++)   //Ѱ�����������
	{
		if(ADV[i]>CCD_Yuzhi&&ADV[i+1]>CCD_Yuzhi&&ADV[i+2]>CCD_Yuzhi&&ADV[i+3]<CCD_Yuzhi&&ADV[i+4]<CCD_Yuzhi&&ADV[i+5]<CCD_Yuzhi)
		{	
			Left=i;
			break;	
		}
	}
	 for(j = 118;j>5; j--)//Ѱ���ұ�������
  {
		if(ADV[j]<CCD_Yuzhi&&ADV[j+1]<CCD_Yuzhi&&ADV[j+2]<CCD_Yuzhi&&ADV[j+3]>CCD_Yuzhi&&ADV[j+4]>CCD_Yuzhi&&ADV[j+5]>CCD_Yuzhi)
		{	
		  Right=j;
		  break;	
		}
  }
	CCD_Zhongzhi=(Right+Left)/2;//��������λ��
	if(myabs(CCD_Zhongzhi-Last_CCD_Zhongzhi)>90)   //�������ߵ�ƫ����̫��
	CCD_Zhongzhi=Last_CCD_Zhongzhi;    //��ȡ��һ�ε�ֵ
	Last_CCD_Zhongzhi=CCD_Zhongzhi;  //������һ�ε�ƫ��
}
