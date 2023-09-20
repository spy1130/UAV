#ifndef _UART_LCD_H
#define _UART_LCD_H

#include "config.h"

void LED_PS(u16 x, u16 y, u16 c);	//画点
void LED_PL(u16 x1, u16 y1, u16 x2, u16 y2, u16 c); //画线
void LED_Init(u16 c); //清屏，c为背景色
void LCD_DS16(u16 x, u16 y, u32 num, u16 c);//16*16数字显示
void LCD_DS32(u16 x, u16 y, u32 num, u16 c);//32*32数字显示
void Show_Init(void);

#endif
