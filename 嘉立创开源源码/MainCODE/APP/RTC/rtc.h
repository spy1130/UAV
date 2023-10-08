#ifndef __RTC_H
#define __RTC_H	    

#include "stm32f10x.h"

//ʱ��ṹ��
typedef struct 
{
	volatile unsigned char hour;
	volatile unsigned char min;//��ֹ�Ż�
	volatile unsigned char sec;			
	volatile unsigned int w_year;
	volatile unsigned char w_month;
	volatile unsigned char w_date;
	volatile unsigned char week;		 
}RTC_VARIABLE;	

extern RTC_VARIABLE rtc;	//�����ṹ��

extern unsigned char  const mon_table[12];	//�·��������ݱ�
void Disp_Time(unsigned char x,unsigned char y,unsigned char size);//���ƶ�λ�ÿ�ʼ��ʾʱ��
void Disp_Week(unsigned char x,unsigned char y,unsigned char size,unsigned char lang);//��ָ��λ����ʾ����
unsigned char RTC_Init(void);        //��ʼ��RTC,����0,ʧ��;1,�ɹ�;
unsigned char Is_Leap_Year(unsigned int year);//ƽ��,�����ж�
unsigned char RTC_Alarm_Set(unsigned int syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec);
unsigned char RTC_Get(void);         //����ʱ��   
unsigned char RTC_Get_Week(unsigned int year,unsigned char month,unsigned char day);
unsigned char RTC_Set(unsigned int syear,unsigned char smon,unsigned char sday,unsigned char hour,unsigned char min,unsigned char sec);//����ʱ��			 
#endif


