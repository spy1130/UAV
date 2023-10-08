/*
1，巩固第一阶段学习的相应知识点，LCD1602,GPIO的操作
2，讲解芯片时序手册怎么解读，以及怎么转换程序
备注：按照芯片手册上的时序图进行编程
3，基于STM32的LCD1602驱动程序

*/

#ifndef __lcd1602_H
#define __lcd1602_H
#include "stm32f10x.h"
#include "bit_operation.h"

#define LCD_PORT_PIN GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
#define LCD_RS_PIN GPIO_Pin_12
#define LCD_RW_PIN GPIO_Pin_13
#define LCD_EN_PIN GPIO_Pin_14

#define LCD_RS PBout(12)
#define LCD_RW PBout(13)
#define LCD_EN PBout(14)

//函数声明
void LCD_GPIO_Init(void);//LCD连接GPIO，初始化GPIO
void LCD_Init(void);//LCD初始化相关参数函数
void LCD_Clear(void);//LCD清屏函数
void LCD_Write_Command(unsigned char com);//LCD写命令函数
void LCD_Write_Data(unsigned char dat);//LCD写数据函数
void LCD_Read_State(void);//LCD读状态函数
void LCD_Set_Position(unsigned char x,unsigned char y);//LCD设置坐标函数
void LCD_Display_Char(unsigned char dat,unsigned char x,unsigned char y);//LCD显示一个字符函数
void LCD_Display_String(unsigned char x,unsigned char y,unsigned char *str);//LCD显示一个字符串函数

#endif


