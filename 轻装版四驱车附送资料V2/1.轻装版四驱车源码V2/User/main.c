#include "stm32f10x.h"
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
u8 Flag_Left,Flag_Right,Flag_Direction=0,Flag_Way,Flag_Next,Turn_Flag;   //����ң����صı���
u8 Flag_Stop=1; //ֹͣ��־λ�� ��ʾ��־λ Ĭ��ֹͣ ��ʾ��
int Encoder_A,Encoder_B,Encoder_C,Encoder_D;  //���������������
long int Position_A,Position_B,Position_C,Position_D,Rate_A,Rate_B,Rate_C,Rate_D; //PID������ر���                     
long int Motor_A,Motor_B,Motor_C,Motor_D; //���PWM����
long int Target_A,Target_B,Target_C,Target_D; //���Ŀ��ֵ
int Voltage;//��ص�ѹ������صı���                       
u8 delay_50,delay_flag; //��ʱ��ر���
u8 Run_Flag=0;  //�ٶȻ���λ��ģʽָʾ����
u8 rxbuf[8],Urxbuf[8],CAN_ON_Flag=0,Usart_ON_Flag=0,Usart_Flag,PID_Send;  //CAN�ʹ��ڿ�����ر���
u8 txbuf[8],txbuf2[8];  //CAN������ر���
float Pitch,Roll,Yaw,Gryo_Z,Move_X,Move_Y,Move_Z;   //����Ƕ� Z�������Ǻ�XYZ��Ŀ���ٶ�
float	Position_KP=14,Position_KI=0,Position_KD=25;  //λ�ÿ���PID����
float Velocity_KP=10,Velocity_KI=10;	          //�ٶȿ���PID����
int RC_Velocity=30,RC_Position=3000;         //����ң�ص��ٶȺ�λ��ֵ
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY; //PS2��ر��� 
u16 CCD_Zhongzhi,CCD_Yuzhi,ADV[128]={0};//CCD��ر���
int Sensor_Left,Sensor_Middle,Sensor_Right,Sensor;//���Ѳ�����
int main(void)
  { 
		delay_init();	    	            //=====��ʱ������ʼ��	
	//JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
		JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
		LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	  KEY_Init();                     //=====������ʼ��
		MY_NVIC_PriorityGroupConfig(2);	//=====�����жϷ���
    MiniBalance_PWM_Init(7199,0);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� 
		uart2_init(9600);               //=====����2��ʼ��
		uart3_init(115200);             //=====����3��ʼ�� 
		OLED_Init();                    //=====OLED��ʼ��	    
    Encoder_Init_TIM2();            //=====�������ӿ�
		Encoder_Init_TIM3();            //=====�������ӿ�
		Encoder_Init_TIM4();            //=====�������ӿ�
    Encoder_Init_TIM5();            //=====��ʼ��������
		if(Run_Flag==0){ while(select())	{	}	} //=====ѡ������ģʽ 
		else Flag_Stop=0;//===λ��ģʽֱ��ʹ�ܵ��
		delay_ms(500);                  //=====��ʱ
    IIC_Init();                     //=====IIC��ʼ��
    MPU6050_initialize();           //=====MPU6050��ʼ��	
  	DMP_Init();                     //=====��ʼ��DMP   
		CAN1_Mode_Init(1,2,3,6,0);			//=====CAN��ʼ��,������1Mbps
		Adc_Init();                     //=====adc��ʼ��		
	 if(Flag_Way==1)
	  {
		PS2_Init();											//=====PS2�ֱ���ʼ��
		PS2_SetInit();									//=====ps2���ó�ʼ��,���á����̵�ģʽ������ѡ���Ƿ�����޸�
	  }
	  else if(Flag_Way==2)ccd_Init();  //=====CCD��ʼ��
	  else if(Flag_Way==3)ele_Init();  //=====��Ŵ�������ʼ��	
	  MiniBalance_EXTI_Init();        //=====MPU6050 5ms��ʱ�жϳ�ʼ��
    while(1)
	   {	
			   if(Flag_Way==1)
			   {
					  PS2_LX=PS2_AnologData(PSS_LX);    //PS2���ݲɼ�    
						PS2_LY=PS2_AnologData(PSS_LY);
						PS2_RX=PS2_AnologData(PSS_RX);
						PS2_RY=PS2_AnologData(PSS_RY);
						PS2_KEY=PS2_DataKey();	
			   }
				  if(Flag_Way==0)
			   {
				  CAN1_SEND();             //CAN����		
          USART_TX();               //���ڷ���
				 }
					APP_Show();	       //APP���
					oled_show();          //===��ʾ����
	  } 
}

