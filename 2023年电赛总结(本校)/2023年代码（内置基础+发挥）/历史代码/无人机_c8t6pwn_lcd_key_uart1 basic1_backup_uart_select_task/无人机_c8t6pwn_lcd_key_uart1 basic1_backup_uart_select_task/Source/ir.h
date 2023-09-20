#ifndef _ir_H
#define _ir_H

#include <system.h>
#include "delay.h"

extern u8 fin;
extern u8 ir_flag;

extern u32 irdata;

void irinit(void);

#endif
//红外接收码：00FFA25D	电源
//红外接收码：00FF629D	mode
//红外接收码：00FFE21D	静音
//红外接收码：00FF22DD	播放/暂停
//红外接收码：00FF02FD	上一曲
//红外接收码：00FFC23D	下一曲
//红外接收码：00FFE01F	EQ
//红外接收码：00FFA857	vol+
//红外接收码：00FF906F	vol-
//红外接收码：00FF6897	0
//红外接收码：00FF9867	RPT
//红外接收码：00FFB04F	U/SD
//红外接收码：00FF30CF	1
//红外接收码：00FF18E7	2
//红外接收码：00FF7A85	3
//红外接收码：00FF10EF	4
//红外接收码：00FF38C7	5
//红外接收码：00FF5AA5	6
//红外接收码：00FF42BD	7
//红外接收码：00FF4AB5	8
//红外接收码：00FF52AD	9
