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

//IO��������	 
#define IIC_SCL    PBout(0) //SCL
#define IIC_SDA    PBout(1) //SDA	 
//#define READ_SCL   PBin(8)  //����SCL
#define READ_SDA   PBin(1)  //����SDA 


//����io

#define task_pc6   PCin(6)  //����SDA 
#define task_pc7   PDin(14)  //����SDA 

//��� io
#define steering_pd12   PDout(12)  //����SDA 
#define steering_pd13   PDout(13)  //����SDA 


void SW_I2C_Init(void);

void IIC_Start(void);               //����IIC��ʼ�ź�
void IIC_Stop(void);                //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);         //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void);              //IIC�ȴ�ACK�ź�
void IIC_Ack(void);                 //IIC����ACK�ź�
void IIC_NAck(void);                //IIC������ACK�ź�

#endif
