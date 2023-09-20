#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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
