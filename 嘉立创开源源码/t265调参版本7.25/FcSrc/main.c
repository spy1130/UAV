/******************** (C) COPYRIGHT 2017 ANO Tech ********************************
 * ����    �������ƴ�
 * ����    ��www.anotc.com
 * �Ա�    ��anotc.taobao.com
 * ����QȺ ��190169595
 * ����    ����ѭ��
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
u8 once_flag=1;
	//��������ʼ����ϵͳΪ�㱼�������˹�����һ��ʱ�ֵ�����
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
		//�������������������ϵͳ���ܣ������жϷ�������������������������
		//Scheduler_Run();
	}
}
/******************* (C) COPYRIGHT 2014 ANO TECH *****END OF FILE************/
