/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：主循环
**********************************************************************************/
#include "SysConfig.h"
#include "Ano_Scheduler.h"
#include <string.h>

int Send_Count,speak_i;
char DataScope_OutPut_Buffer_xm[20];
int speak_len1=0x00;//(sizeof(buf_xm)/sizeof(buf_xm[0]));
int speak_len,speak_i;
char buf1[100]={"自检 "};//\[b1] 欢迎光临，请进

char station_buf1[60]={"地面站"};//\[b1] 欢迎光临，请进

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
	
	//说话内容	
	
	for(speak_i=0;speak_i<speak_len;speak_i++)
	{
		DataScope_OutPut_Buffer_xm[speak_i+5]=buf_xm[speak_i];
	}
	for( speak_i = 0 ; speak_i < Send_Count; speak_i++) 
	{
		while((USART3->SR&0X40)==0);  //以前串口2，串口子资源紧张，改到串口3
		USART3->DR = DataScope_OutPut_Buffer_xm[speak_i]; 
	}
}
/////////////////
////
///////////////

void speaker_test(void)
{
	
	
	char buf1[]={"[v9]欢迎参加2023年无人机电赛"};//\[b1] 欢迎光临，请进
	speak_len1=strlen(buf1);
	speak_context((u8*)buf1,speak_len1);

	
		
}



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
	while (1)
	{
		//当系统出错后，会进入这个死循环
	}
}
#endif
//=======================================================================================
//=======================================================================================
int main(void)
{
	//进行所有设备的初始化，并将初始化结果保存

	All_Init();
	
	
	
	//调度器初始化，系统为裸奔，这里人工做了一个时分调度器
	speaker_test();
	
 
	MyDelayMs(1000);
	MyDelayMs(1000);
	MyDelayMs(1000);
	
	
	
	
	
	Scheduler_Setup();
	while (1)
	{
		//运行任务调度器，所有系统功能，除了中断服务函数，都在任务调度器内完成
		Scheduler_Run();
	}
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
