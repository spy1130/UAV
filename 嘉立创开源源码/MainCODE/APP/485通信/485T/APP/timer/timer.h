/*定时器定时功能编程步骤：
	
	1,选择时钟（4种），一般选择内部时钟
	2，设置分频系数
	3，设置自动重载寄存器的值
	
	4，开启定时器
	
	5，设置定时器中断
	6，设置优先级
	7，开启中断
	8，编写定时器中断程序
*/

#ifndef __timer_H

#include "stm32f10x.h"

void Timer_Init(unsigned int pre,unsigned int arr);



#endif

