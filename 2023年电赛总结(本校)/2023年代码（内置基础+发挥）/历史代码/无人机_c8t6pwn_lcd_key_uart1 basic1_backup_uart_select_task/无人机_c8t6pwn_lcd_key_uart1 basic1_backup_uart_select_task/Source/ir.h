#ifndef _ir_H
#define _ir_H

#include <system.h>
#include "delay.h"

extern u8 fin;
extern u8 ir_flag;

extern u32 irdata;

void irinit(void);

#endif
//��������룺00FFA25D	��Դ
//��������룺00FF629D	mode
//��������룺00FFE21D	����
//��������룺00FF22DD	����/��ͣ
//��������룺00FF02FD	��һ��
//��������룺00FFC23D	��һ��
//��������룺00FFE01F	EQ
//��������룺00FFA857	vol+
//��������룺00FF906F	vol-
//��������룺00FF6897	0
//��������룺00FF9867	RPT
//��������룺00FFB04F	U/SD
//��������룺00FF30CF	1
//��������룺00FF18E7	2
//��������룺00FF7A85	3
//��������룺00FF10EF	4
//��������룺00FF38C7	5
//��������룺00FF5AA5	6
//��������룺00FF42BD	7
//��������룺00FF4AB5	8
//��������룺00FF52AD	9
