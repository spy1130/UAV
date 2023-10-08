/*
1�����̵�һ�׶�ѧϰ����Ӧ֪ʶ�㣬LCD1602,GPIO�Ĳ���
2������оƬʱ���ֲ���ô������Լ���ôת������
��ע������оƬ�ֲ��ϵ�ʱ��ͼ���б��
3������STM32��LCD1602��������

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

//��������
void LCD_GPIO_Init(void);//LCD����GPIO����ʼ��GPIO
void LCD_Init(void);//LCD��ʼ����ز�������
void LCD_Clear(void);//LCD��������
void LCD_Write_Command(unsigned char com);//LCDд�����
void LCD_Write_Data(unsigned char dat);//LCDд���ݺ���
void LCD_Read_State(void);//LCD��״̬����
void LCD_Set_Position(unsigned char x,unsigned char y);//LCD�������꺯��
void LCD_Display_Char(unsigned char dat,unsigned char x,unsigned char y);//LCD��ʾһ���ַ�����
void LCD_Display_String(unsigned char x,unsigned char y,unsigned char *str);//LCD��ʾһ���ַ�������

#endif


