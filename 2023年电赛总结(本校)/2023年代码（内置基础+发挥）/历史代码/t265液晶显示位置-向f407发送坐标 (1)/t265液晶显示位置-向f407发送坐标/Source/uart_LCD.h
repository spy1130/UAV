#ifndef _UART_LCD_H
#define _UART_LCD_H

#include "config.h"

void LED_PS(u16 x, u16 y, u16 c);	//����
void LED_PL(u16 x1, u16 y1, u16 x2, u16 y2, u16 c); //����
void LED_Init(u16 c); //������cΪ����ɫ
void LCD_DS16(u16 x, u16 y, u32 num, u16 c);//16*16������ʾ
void LCD_DS32(u16 x, u16 y, u32 num, u16 c);//32*32������ʾ
void Show_Init(void);

#endif
