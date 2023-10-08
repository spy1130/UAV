#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"
 
/*��������*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)(x))
 
void OLED_Init(void);//OLED��ʼ��
void OLED_Clear(void);//����
void OLED_Refresh_Gram(void);//�����Դ浽OLED
void OLED_WriteData(uint8_t Data);//OLEDд����
void OLED_WriteCommand(uint8_t Command);//OLEDд����
void OLED_DrawPoint(u8 x,u8 y,u8 t);//����
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//oled��ʾ�ַ�
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//oled��ʾ�ַ���
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//oled��ʾ����
u32 mypow(u8 m,u8 n);//m^n����
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size,u8 mode);//oled��ʾ����

#endif
