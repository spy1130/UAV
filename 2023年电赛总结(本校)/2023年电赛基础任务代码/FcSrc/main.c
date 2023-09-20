/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * ����    �������ƴ�
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
 * ����    ����ѭ��
**********************************************************************************/
#include "SysConfig.h"
#include "Ano_Scheduler.h"
#include <string.h>

int Send_Count,speak_i;
char DataScope_OutPut_Buffer_xm[20];
int speak_len1=0x00;//(sizeof(buf_xm)/sizeof(buf_xm[0]));
int speak_len,speak_i;
char buf1[100]={"�Լ� "};//\[b1] ��ӭ���٣����

char station_buf1[60]={"����վ"};//\[b1] ��ӭ���٣����

u8 m1_step=0x00,m2_step=0x00,m3_step=0x00,m4_step=0x00;


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
		while((USART3->SR&0X40)==0);  //��ǰ����2����������Դ���ţ��ĵ�����3
		USART3->DR = DataScope_OutPut_Buffer_xm[speak_i]; 
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



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
	while (1)
	{
		//��ϵͳ����󣬻���������ѭ��
	}
}
#endif
//=======================================================================================
//=======================================================================================
int main(void)
{
	//���������豸�ĳ�ʼ����������ʼ���������

	All_Init();
	
	
	
	//��������ʼ����ϵͳΪ�㱼�������˹�����һ��ʱ�ֵ�����
	speaker_test();
	
 
	MyDelayMs(1000);
	MyDelayMs(1000);
	MyDelayMs(1000);
	
	
	
	
	
	Scheduler_Setup();
	while (1)
	{
		//�������������������ϵͳ���ܣ������жϷ�������������������������
		Scheduler_Run();
	}
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
