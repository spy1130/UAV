#include "key.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
/**************************************************************************
�������ܣ�������ʼ��
��ڲ�������
����  ֵ���� 
**************************************************************************/
void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ�ܶ˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_12; //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIO
} 
/**************************************************************************
�������ܣ�����ɨ��
��ڲ�����˫���ȴ�ʱ��
����  ֵ������״̬ 0���޶��� 1������ 2��˫�� 
**************************************************************************/
u8 click_N_Double (u8 time)
{
		static	u8 flag_key,count_key,double_key;	
		static	u16 count_single,Forever_count;
	  if(KEY==0)  Forever_count++;   //������־λδ��1
     else        Forever_count=0;
		if(0==KEY&&0==flag_key)		flag_key=1;	
	  if(0==count_key)
		{
				if(flag_key==1) 
				{
					double_key++;
					count_key=1;	
				}
				if(double_key==2) 
				{
					double_key=0;
					count_single=0;
					return 2;//˫��ִ�е�ָ��
				}
		}
		if(1==KEY)			flag_key=0,count_key=0;
		
		if(1==double_key)
		{
			count_single++;
			if(count_single>time&&Forever_count<time)
			{
			double_key=0;
			count_single=0;	
			return 1;//����ִ�е�ָ��
			}
			if(Forever_count>time)
			{
			double_key=0;
			count_single=0;	
			}
		}	
		return 0;
}
/**************************************************************************
�������ܣ�����ɨ��
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������ 
**************************************************************************/
u8 click(void)
{
			static u8 flag_key=1;//�������ɿ���־
			if(flag_key&&KEY==0)
			{
			flag_key=0;
			return 1;	// ��������
			}
			else if(1==KEY)			flag_key=1;
			return 0;//�ް�������
}
/**************************************************************************
�������ܣ��������
��ڲ�������
����  ֵ������״̬ 0���޶��� 1������2s
**************************************************************************/
u8 Long_Press(void)
{
			static u16 Long_Press_count,Long_Press;
	    if(Long_Press==0&&KEY==0)  Long_Press_count++;   //������־λδ��1
      else                       Long_Press_count=0; 
		  if(Long_Press_count>200)		
			{
				Long_Press=1;	
				Long_Press_count=0;
				return 1;
			}				
			 if(Long_Press==1)     //������־λ��1
			{
				  Long_Press=0;
			}
			return 0;
}
/**************************************************************************
�������ܣ�ѡ�����е�ģʽ
��ڲ�������
����  ֵ����
**************************************************************************/
u8  select(void)
{
	  int Angle=260,Encoder_Temp;
	  static u8 flag=1;
	  int count;
	  static int Last_Encoder_Temp,Start_Count;
	  oled_show_once();  //OLED��ʾ
		Encoder_Temp=abs((short)TIM5->CNT);
    count=Encoder_Temp;
	  if(abs(Encoder_Temp-Last_Encoder_Temp)==0)Start_Count++; else Start_Count=0;
	  if(count<=Angle)								       Flag_Way=0,Flag_Stop=0;  //APPң��ģʽ
		else if(count>Angle&&count<=2*Angle)	 Flag_Way=1,Flag_Stop=1;  //PS2ң��ģʽ
		else if(count>2*Angle&&count<=3*Angle) Flag_Way=2,Flag_Stop=1;	//CCDѲ��ģʽ
		else if(count>3*Angle&&count<=4*Angle) Flag_Way=3,Flag_Stop=1;	//���Ѳ��ģʽ
	  else TIM5->CNT=0;
    if(KEY==0||Start_Count>600)Flag_Next=1;//����������»��߳������8��û��ת������
	  if(Flag_Next==1)OLED_Clear(),flag=0;  //���OLED��Ļ ������������
	  Last_Encoder_Temp=Encoder_Temp;
	  return flag;	  
}
