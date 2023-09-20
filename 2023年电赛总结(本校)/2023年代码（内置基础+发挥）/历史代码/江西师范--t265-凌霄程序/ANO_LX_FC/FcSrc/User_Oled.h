/*==========================================================================
 * 描述    ：OLED屏幕显示
 * 更新时间：2023年3月25日
 * 作者		 ：	LHB
===========================================================================*/
#ifndef __USER_OLED_H
#define __USER_OLED_H

#include "User_RC.h"
#include "Drv_RcIn.h"
#include "Timer.h"
#include "hw_ints.h"
#include "uart.h"
#include "ANO_LX.h"
#include "ANO_DT_LX.h"
#include "LX_FC_Fun.h"
#include "LX_FC_State.h"
#include "ANO_DT_LX.h"
#include "stdlib.h"
#include "stdio.h"



#define OLED_SCL_Clr() ROM_GPIOPinWrite(GPIOB_BASE,GPIO_PIN_0,0)
#define OLED_SCL_Set() ROM_GPIOPinWrite(GPIOB_BASE,GPIO_PIN_0,GPIO_PIN_0)

#define OLED_SDA_Clr() ROM_GPIOPinWrite(GPIOB_BASE,GPIO_PIN_1,0)
#define OLED_SDA_Set() ROM_GPIOPinWrite(GPIOB_BASE,GPIO_PIN_1,GPIO_PIN_1)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_ClearPoint(uint8_t x,uint8_t y);
void OLED_ColorTurn(uint8_t i);
void OLED_DisplayTurn(uint8_t i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(uint8_t dat);
void OLED_WR_Byte(uint8_t dat,uint8_t mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t mode);
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1,uint8_t mode);
void OLED_ShowChar6x8(uint8_t x,uint8_t y,uint8_t chr,uint8_t mode);
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1,uint8_t mode);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1,uint8_t mode);
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1,uint8_t mode);
void OLED_ScrollDisplay(uint8_t num,uint8_t space,uint8_t mode);
void OLED_ShowPicture(uint8_t x,uint8_t y,uint8_t sizex,uint8_t sizey,uint8_t BMP[],uint8_t mode);
void OLED_Init(void);
void heading_printf(void);/*页面标题打印*/
void name_printf(void);
#define OLED_LEN 48
#define TXT_SIZE 8/*这里改字体大小，可选8，12，16，24*/
extern char oled_buf[OLED_LEN];

#define oled_printf(line,fmt,...) {sprintf(oled_buf,fmt,##__VA_ARGS__);\
OLED_ShowString(0,line*12,(uint8_t *)oled_buf,12,1);\
/*OLED_Refresh()*/;}

//#define oled_printf(line,fmt,...) {sprintf(oled_buf,fmt,##__VA_ARGS__);\
//OLED_ShowString(0,line*TXT_SIZE,(uint8_t *)oled_buf,TXT_SIZE,1);\
///*OLED_Refresh()*/;}


#endif

