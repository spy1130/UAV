/*I2C_Init.h*/
#ifndef I2C_INIT_H
#define I2C_INIT_H

#include "sys.h"
#include "Drv_Sys.h"

#define IIC_SCL_PORT		GPIOB
#define IIC_SCL_PIN			GPIO_Pin_0
#define IIC_SCL_PORT_RCC 	RCC_AHB1Periph_GPIOB

#define IIC_SDA_PORT		GPIOB
#define IIC_SDA_PIN			GPIO_Pin_1
#define IIC_SDA_PORT_RCC	RCC_AHB1Periph_GPIOB

//IO操作函数	 
#define IIC_SCL    PBout(0) //SCL
#define IIC_SDA    PBout(1) //SDA	 
//#define READ_SCL   PBin(8)  //输入SCL
#define READ_SDA   PBin(1)  //输入SDA 


//任务io

#define task_pc6   PCin(6)  //输入SDA 
#define task_pc7   PDin(14)  //输入SDA 

//舵机 io
#define steering_pd12   PDout(12)  //输入SDA 
#define steering_pd13   PDout(13)  //输入SDA 


void SW_I2C_Init(void);

void IIC_Start(void);               //发送IIC开始信号
void IIC_Stop(void);                //发送IIC停止信号
void IIC_Send_Byte(u8 txd);         //IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void);              //IIC等待ACK信号
void IIC_Ack(void);                 //IIC发送ACK信号
void IIC_NAck(void);                //IIC不发送ACK信号

#endif
