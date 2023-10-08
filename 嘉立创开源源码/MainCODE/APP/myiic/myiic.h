#ifndef __myiic_H
#define __myiic_H
#include "stm32f10x.h"
#include "bit_operation.h"

//IIC时序延时时间
#define DELAY_XUS  5

//IIC第一个字节中最低位：读写标志位
#define WRITE_FLAG 0
#define READ_FLAG  1

//PB14->SDA  PB15->SCL 
#define  SDA_PIN 	GPIO_Pin_14
#define  SCL_PIN 	GPIO_Pin_15

#define  SDA_OUT   PBout(14)
#define  SCL_OUT   PBout(15)
#define  SDA_IN    PBin(14)

//定义PB14(SDA)为输出  27:24  = 0011
#define  SDA_MODE_OUT()  {GPIOB->CRH &= ~(0X0F << 24); GPIOB->CRH |= (0X03 << 24); }

//定义PB14(SDA)为输入  27:24  = 1000
#define  SDA_MODE_IN()   {GPIOB->CRH &= ~(0X0F << 24); GPIOB->CRH |= (0X08 << 24); }

//可供外部文件调用的函数
void myiic_init(void);
void sensor_common_write_byte(unsigned char slave_addr,unsigned char reg_addr,unsigned char dat);
unsigned char sensor_common_read_byte(unsigned char slave_addr,unsigned char reg_addr);

//静态函数
static void myiic_start(void);
static void myiic_stop(void);
static void myiic_ack(void);
static void myiic_noack(void);
static unsigned char myiic_wait_ack(void);
static void myiic_write_byte(unsigned char dat);
static unsigned char myiic_read_byte(void);
static void myiic_delay(unsigned char xus);
#endif



