#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"
 
/*引脚配置*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_6, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)(x))
 
void OLED_Init(void);//OLED初始化
void OLED_Clear(void);//清屏
void OLED_Refresh_Gram(void);//更新显存到OLED
void OLED_WriteData(uint8_t Data);//OLED写数据
void OLED_WriteCommand(uint8_t Command);//OLED写命令
void OLED_DrawPoint(u8 x,u8 y,u8 t);//画点
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode);//oled显示字符
void OLED_ShowString(u8 x,u8 y,const u8 *p,u8 size);//oled显示字符串
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);//oled显示数字
u32 mypow(u8 m,u8 n);//m^n函数
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size,u8 mode);//oled显示中文

#endif
