#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 



#define charge_switch PDout(4)// PE5	
#define fire_switch PDout(5)// PE5	


#define front_echo GPIO_Pin_1
#define front_trig GPIO_Pin_4


#define m1_dir PAout(4)// PE5	
#define m2_dir PAout(5)// PE5	

#define c1 PBout(12)// PF0
#define c2 PBout(13)// PF0
#define c3 PBout(14)// PF0
#define c4 PBout(15)// PF0

#define r1 PAin(4)// PF0
#define r2 PAin(5)// PF0
#define r3 PAin(7)// PF0//pa6 is pwm output,so it can't be set here
#define r4 PAin(8)// PF0

#define string_pb6 PBin(6)// PB5

#define string_pb7 PBin(7)// PB5

#define emergenc_io PAin(1)// PE5	

#define task_pb8 PBin(8)// PB5
#define task_pb9 PBin(9)// PB5


void key_init_r_c(void);

void backup_uart_io_stop_io_init(void);



#endif
