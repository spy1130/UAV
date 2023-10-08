/*
	变成步骤：
	1，解锁：向KEY写值
	
	These bits must be written by software at regular intervals with the key value AAAAh, 
	otherwise the watchdog generates a reset when the counter reaches 0.
	
	Writing the key value 5555h to enable access to the IWDG_PR and IWDG_RLR registers 

	Writing the key value CCCCh starts the watchdog (except if the hardware watchdog option is 
	selected)
	
	2，设置分频系数，计数值
	3，喂狗
*/

#include "iwdg.h"

/*
	clk = clk_o / (4*2^pr)
	clk_o:40K

时间计算(大概):Tout=((4*2^pr)*rlr)/40 (ms).

*/
void Iwdg_Init(unsigned int pr,unsigned int rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(pr);    //IWDG->PR = IWDG_Prescaler;[2:0]
    IWDG_SetReload(rlr);      //IWDG->RLR = Reload;[11:0]
	IWDG_ReloadCounter();//IWDG->KR = KR_KEY_Reload; #define KR_KEY_Reload    ((uint16_t)0xAAAA)
	IWDG_Enable();
}


void Iwdg_Feed(void)
{
	IWDG_ReloadCounter();
}

