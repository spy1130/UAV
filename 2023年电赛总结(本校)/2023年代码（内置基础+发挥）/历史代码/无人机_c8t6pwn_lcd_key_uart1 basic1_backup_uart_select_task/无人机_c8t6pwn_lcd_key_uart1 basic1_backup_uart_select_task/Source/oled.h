#ifndef  __OLED_H
#define  __OLED_H
#include "sys.h"

//#define OLED_SCL PBout(15)
//#define OLED_SDA PBout(9) 
//#define OLED_SCL PCout(8)
//#define OLED_SDA PCout(9) 

#define OLED_SCL PBout(0)
#define OLED_SDA PBout(1) 

#define high 1
#define low 0
 
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define Brightness 196 //0~255��������

void IIC_Start(void);// -- ����I2C����
void IIC_Stop(void);// -- �ر�I2C����
void Write_IIC_Byte(unsigned char IIC_Byte);// -- ͨ��I2C����дһ��byte������
void OLED_WrDat(unsigned char dat);// -- ��OLED��д����
void OLED_WrCmd(unsigned char cmd);// -- ��OLED��д����
void OLED_Set_Pos(unsigned char x, unsigned char y);// -- ������ʾ����
void OLED_Fill(unsigned char bmp_dat);// -- ȫ����ʾ(��ʾBMPͼƬʱ�Ż��õ��˹���)
void OLED_CLS(void);// -- ��λ/����
void OLED_ON(void);
void OLED_OFF(void);
void OLED_Init(void);// -- OLED����ʼ�����򣬴˺���Ӧ�ڲ�����Ļ֮ǰ���ȵ���
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[],unsigned char against);// -- 6x8������������ʾASCII�����С���У���̫����
void OLED_P8x16Str(unsigned char x,unsigned char y,unsigned char ch[],unsigned char against);// -- 8x16������������ʾASCII�룬�ǳ�����
void OLED_Show6x8(unsigned char x,unsigned char y,unsigned int N,unsigned char against);
void OLED_Show8x16(unsigned char x,unsigned char y,unsigned int N,unsigned char against);
void OLED_Show16x16(unsigned char x,unsigned char y,unsigned int N,unsigned char against);// -- 16x16������������ʾ���ֵ���С���У������ø������塢�Ӵ֡���б���»��ߵ�
void Oled_Printf_U16(unsigned char x,unsigned char y,unsigned int num,unsigned char TextSize);
void Oled_Printf_Float(unsigned char x,unsigned char y,float num,unsigned char TextSize);

#endif
