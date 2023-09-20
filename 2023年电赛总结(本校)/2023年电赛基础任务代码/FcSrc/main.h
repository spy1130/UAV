#ifndef __MAIN_H
#define __MAIN_H
#include "ANO_DT_LX.h"
#include "ANO_LX.h"
#include "Drv_RcIn.h"
#include "LX_FC_EXT_Sensor.h"
#include "Drv_led.h"
#include "LX_FC_State.h"
#include "Drv_Uart.h"

void speak_context(u8 buf_xm[],int speak_len);
	
extern int Send_Count,speak_i;
extern char DataScope_OutPut_Buffer_xm[20];
extern int speak_len1;//(sizeof(buf_xm)/sizeof(buf_xm[0]));
extern int speak_len,speak_i;
extern char buf1[30];//\[b1] »¶Ó­¹âÁÙ£¬Çë½ø

extern char station_buf1[60];//\[b1] »¶Ó­¹âÁÙ£¬Çë½ø










#endif

