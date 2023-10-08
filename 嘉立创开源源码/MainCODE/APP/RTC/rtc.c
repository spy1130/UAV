#include "led.h" 
#include "delay.h"
#include "usart.h"
#include "rtc.h" 		    

/*
���ܣ�����RTC������1�����жϣ����ڴ�ӡ��ǰʱ��
��̣�
	1������ʱ�ӣ�BKP����backup domain����PWR
	2��RTC CORE BKP ����
	3��RTC���󱸵�Դ�����������һ�ν��й���
	�󱸼Ĵ���1:0x6666
		�����ж�RTC�Ƿ��Ѿ����ù�����û�У�
		
		��λ�������� 
		LSE:32768hz�����ⲿ����ʱ��
		�ȴ�ʱ���ȶ�����
		{
		while(GETFLAG && ʱ��);//��ʱʱ��
			
		}
		if()
		return 
		��1��
		��2��
		����RTC����ʱ��
		ʹ��RTCʱ�� 
		�жϺ͵ȴ����һ�ζ�RTC�Ĵ�����д�������
		ʹ��RTC���ж�
		�ȴ����һ�ζ�RTC�Ĵ�����д�������
		
		��������ģʽ
		���÷���
		�ȴ����
		���ó�ʼʱ��
		�ȴ����
		�˳�����ģʽ
		NVIC RTC�ж�
		��ָ���ĺ󱸼Ĵ���1��д���û��������ݣ�0x6666
	4�����²�����
*/
RTC_VARIABLE rtc;//ʱ�ӽṹ�� 

//ʵʱʱ������
//��ʼ��RTCʱ��,ͬʱ���ʱ���Ƿ�������
//BKP->DR1���ڱ����Ƿ��һ�����õ�����
//����0:����
//����:�������

unsigned char RTC_Init(void)
{
	//����ǲ��ǵ�һ������ʱ��
	unsigned char  temp=0;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��   
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ�������  
	if (BKP_ReadBackupRegister(BKP_DR1) != 0x6666)		//��ָ���ĺ󱸼Ĵ����ж�������:��������д���ָ�����ݲ����
	{	 			
		BKP_DeInit();	//��λ�������� 	
		RCC_LSEConfig(RCC_LSE_ON);	//�����ⲿ���پ���(LSE),ʹ��������پ���
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET&&temp<200)	//���ָ����RCC��־λ�������,�ȴ����پ������
		{
			temp++;
			delay_ms(10);
		}
		if(temp>=200)
			return 1;//��ʼ��ʱ��ʧ��,����������	
		else
		{
			RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);		//����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
			RCC_RTCCLKCmd(ENABLE);	//ʹ��RTCʱ��  
			RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
			RTC_WaitForSynchro();		//�ȴ�RTC�Ĵ���ͬ��  
			RTC_ITConfig(RTC_IT_SEC, ENABLE);		//ʹ��RTC���ж�
			RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
			RTC_EnterConfigMode();/// ��������	
			RTC_SetPrescaler(32768-1); //����RTCԤ��Ƶ��ֵ 32768 1hz 1s
			RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
			RTC_Set(2021,7,15,17,42,55);  //����ʱ��	
			RTC_ExitConfigMode(); //�˳�����ģʽ  
			
			BKP_WriteBackupRegister(BKP_DR1, 0x6666);	//��ָ���ĺ󱸼Ĵ�����д���û���������
		}
	}
	else//ϵͳ������ʱ
	{
		RTC_WaitForSynchro();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_ITConfig(RTC_IT_SEC, ENABLE);	//ʹ��RTC���ж�
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	}

	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;		//RTCȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�1λ,�����ȼ�3λ
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	//��ռ���ȼ�0λ,�����ȼ�4λ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ�ܸ�ͨ���ж�
	NVIC_Init(&NVIC_InitStructure);		//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���    				     
	RTC_Get();//����ʱ��	
	return 0; //ok

}		 				    
//RTCʱ���ж�
//ÿ�봥��һ��  
//extern unsigned int tcnt; 
void RTC_IRQHandler(void)
{		
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//�����ж�
	{							
		RTC_Get();//����ʱ��   
		printf("Time:%d-%d-%d %d:%d:%d\t\n",rtc.w_year,rtc.w_month,rtc.w_date,rtc.hour,rtc.min,rtc.sec);
 	}
			  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//�������ж�
	RTC_WaitForLastTask();	  	    						 	   	 
}

//�ж��Ƿ������꺯��
//�·�   1  2  3  4  5  6  7  8  9  10 11 12
//����   31 29 31 30 31 30 31 31 30 31 30 31
//������ 31 28 31 30 31 30 31 31 30 31 30 31
//����:���
//���:������ǲ�������.1,��.0,����
unsigned char  Is_Leap_Year(unsigned int year)
{			  
	if(year%4==0) //�����ܱ�4���� //for if ���⣺�ж��Ƿ����� 2��ˮ�ɻ�
	{ 
		if(year%100==0) 
		{ 
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400���� 	   
			else return 0;   
		}else return 1;   
	}else return 0;	
}

//����ʱ��
//�������ʱ��ת��Ϊ����
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//����ֵ:0,�ɹ�;����:�������.
//�·����ݱ�											 
unsigned char  const table_week[12]={0,3,3,6,1,4,6,2,5,0,3,5}; //���������ݱ�	  
//ƽ����·����ڱ�
const unsigned char  mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
unsigned char  RTC_Set(unsigned int syear,unsigned char  smon,unsigned char  sday,unsigned char  hour,unsigned char  min,unsigned char  sec)
{
	//��ʱ�Ļ�׼��1970 RTCʱ��ģ��
	//1 �ж�  2 �������� 3��ͬ�����ȴ����
	
	unsigned int t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
    seccount+=(u32)min*60;	 //����������
	seccount+=sec;//�������Ӽ���ȥ

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
	PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 
	RTC_SetCounter(seccount);	//����RTC��������ֵ

	RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
	return 0;	    
}

//��ʼ������		  
//��1970��1��1��Ϊ��׼
//1970~2099��Ϊ�Ϸ����
//syear,smon,sday,hour,min,sec�����ӵ�������ʱ����   
//����ֵ:0,�ɹ�;����:�������.
unsigned char  RTC_Alarm_Set(unsigned int syear,unsigned char  smon,unsigned char  sday,unsigned char  hour,unsigned char  min,unsigned char  sec)
{
	unsigned int t;
	u32 seccount=0;
	if(syear<1970||syear>2099)return 1;	   
	for(t=1970;t<syear;t++)	//��������ݵ��������
	{
		if(Is_Leap_Year(t))seccount+=31622400;//�����������
		else seccount+=31536000;			  //ƽ���������
	}
	smon-=1;
	for(t=0;t<smon;t++)	   //��ǰ���·ݵ����������
	{
		seccount+=(u32)mon_table[t]*86400;//�·����������
		if(Is_Leap_Year(syear)&&t==1)seccount+=86400;//����2�·�����һ���������	   
	}
	seccount+=(u32)(sday-1)*86400;//��ǰ�����ڵ���������� 
	seccount+=(u32)hour*3600;//Сʱ������
    seccount+=(u32)min*60;	 //����������
	seccount+=sec;//�������Ӽ���ȥ 			    
	//����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��   
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ�������  
	//���������Ǳ����!
	
	RTC_SetAlarm(seccount);
 
	RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������  	
	
	return 0;	    
}


//�õ���ǰ��ʱ��
//����ֵ:0,�ɹ�;����:�������.
unsigned char  RTC_Get(void)
{
	static unsigned int daycnt=0;
	u32 timecount=0; 
	u32 temp=0;
	unsigned int temp1=0;	  
    timecount=RTC_GetCounter();	 
 	temp=timecount/86400;   //�õ�����(��������Ӧ��)
	if(daycnt!=temp)//����һ����
	{	  
		daycnt=temp;
		temp1=1970;	//��1970�꿪ʼ
		while(temp>=365)
		{				 
			if(Is_Leap_Year(temp1))//������
			{
				if(temp>=366)temp-=366;//�����������
				else {temp1++;break;}  
			}
			else temp-=365;	  //ƽ�� 
			temp1++;  
		}   
		rtc.w_year=temp1;//�õ����
		temp1=0;
		while(temp>=28)//������һ����
		{
			if(Is_Leap_Year(rtc.w_year)&&temp1==1)//�����ǲ�������/2�·�
			{
				if(temp>=29)temp-=29;//�����������
				else break; 
			}
			else 
			{
				if(temp>=mon_table[temp1])temp-=mon_table[temp1];//ƽ��
				else break;
			}
			temp1++;  
		}
		rtc.w_month=temp1+1;	//�õ��·�
		rtc.w_date=temp+1;  	//�õ����� 
	}
	temp=timecount%86400;     		//�õ�������   	   
	rtc.hour=temp/3600;     	//Сʱ
	rtc.min=(temp%3600)/60; 	//����	
	rtc.sec=(temp%3600)%60; 	//����
	rtc.week=RTC_Get_Week(rtc.w_year,rtc.w_month,rtc.w_date);//��ȡ����   
	return 0;
}	

//������������ڼ�
//��������:���빫�����ڵõ�����(ֻ����1901-2099��)
//������������������� 
//����ֵ�����ں�																						 
unsigned char  RTC_Get_Week(unsigned int year,unsigned char  month,unsigned char  day)
{	
	unsigned int temp2;
	unsigned char yearH,yearL;
	
	yearH=year/100;	yearL=year%100; 
	// ���Ϊ21����,�������100  
	if (yearH>19)yearL+=100;
	// ����������ֻ��1900��֮���  
	temp2=yearL+yearL/4;
	temp2=temp2%7; 
	temp2=temp2+day+table_week[month-1];
	if (yearL%4==0&&month<3)temp2--;
	return(temp2%7);
}			  
















