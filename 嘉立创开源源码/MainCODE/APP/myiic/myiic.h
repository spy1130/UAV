#ifndef __myiic_H
#define __myiic_H
#include "stm32f10x.h"
#include "bit_operation.h"

//IICʱ����ʱʱ��
#define DELAY_XUS  5

//IIC��һ���ֽ������λ����д��־λ
#define WRITE_FLAG 0
#define READ_FLAG  1

//PB14->SDA  PB15->SCL 
#define  SDA_PIN 	GPIO_Pin_14
#define  SCL_PIN 	GPIO_Pin_15

#define  SDA_OUT   PBout(14)
#define  SCL_OUT   PBout(15)
#define  SDA_IN    PBin(14)

//����PB14(SDA)Ϊ���  27:24  = 0011
#define  SDA_MODE_OUT()  {GPIOB->CRH &= ~(0X0F << 24); GPIOB->CRH |= (0X03 << 24); }

//����PB14(SDA)Ϊ����  27:24  = 1000
#define  SDA_MODE_IN()   {GPIOB->CRH &= ~(0X0F << 24); GPIOB->CRH |= (0X08 << 24); }

//�ɹ��ⲿ�ļ����õĺ���
void myiic_init(void);
void sensor_common_write_byte(unsigned char slave_addr,unsigned char reg_addr,unsigned char dat);
unsigned char sensor_common_read_byte(unsigned char slave_addr,unsigned char reg_addr);

//��̬����
static void myiic_start(void);
static void myiic_stop(void);
static void myiic_ack(void);
static void myiic_noack(void);
static unsigned char myiic_wait_ack(void);
static void myiic_write_byte(unsigned char dat);
static unsigned char myiic_read_byte(void);
static void myiic_delay(unsigned char xus);
#endif



