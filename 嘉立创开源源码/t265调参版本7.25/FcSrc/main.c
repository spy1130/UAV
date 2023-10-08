/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * 作者    ：匿名科创
 * 官网    ：www.anotc.com
 * 淘宝    ：anotc.taobao.com
 * 技术Q群 ：190169595
 * 描述    ：主循环
**********************************************************************************/
#include "SysConfig.h"
#include "Ano_Scheduler.h"
#include "Expansion_board_RXSD.h"
#include "info.h"
#include "Openmv_Sensor.h"
#include "T265_Sensor.h"
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
u8 once_flag=1;
	//调度器初始化，系统为裸奔，这里人工做了一个时分调度器
	Scheduler_Setup();
	while (1)
	{
			
		
		
		//	MyDelayMs(3000);
			Expansion_board_LED(1,1);
		if(User.Flight.Page_OK_Flag == 1){
			Expansion_board_LED(1,1);
		
		}
		

		/*
		if(User.Flight.key==1){
			Openmv_sd('1');
			MyDelayMs(300);
		}
		else if(User.Flight.key==0){
			Openmv_sd('0');
			MyDelayMs(300);
		}
*/
		//Laser_On_Off(1);
		//运行任务调度器，所有系统功能，除了中断服务函数，都在任务调度器内完成
		//Scheduler_Run();
	}
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
