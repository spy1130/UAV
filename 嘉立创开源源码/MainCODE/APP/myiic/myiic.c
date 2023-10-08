#include "myiic.h"
#include "delay.h"
#include "usart.h"

void myiic_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//SDA PB14输出模式
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  = SDA_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  = SCL_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOB,SDA_PIN|SCL_PIN);//PB14,PB15初始化高电平
	
}


static void myiic_delay(unsigned char xus)
{
	delay_us(xus);
}

//SDA_OUT   PBout(14)  SCL_OUT   PBout(15)
static void myiic_start(void)
{
	SDA_MODE_OUT();//SDA输出模式
	
	SDA_OUT = 1;
	SCL_OUT = 1;
	myiic_delay(DELAY_XUS);
	SDA_OUT = 0;
	myiic_delay(DELAY_XUS);
	SCL_OUT = 0;
}

static void myiic_stop(void)
{
	SDA_MODE_OUT();//SDA输出模式
	
	SCL_OUT = 0;	
	SDA_OUT = 0;
	myiic_delay(DELAY_XUS);	
	SCL_OUT = 1;
	SDA_OUT = 1;
	myiic_delay(DELAY_XUS);	
}

static void myiic_ack(void)
{
	SCL_OUT = 0;
	SDA_MODE_OUT();
	SDA_OUT = 0;
	myiic_delay(DELAY_XUS);	
	SCL_OUT = 1;
	myiic_delay(DELAY_XUS);
	SCL_OUT = 0;	
}

static void myiic_noack(void)
{
	SCL_OUT = 0;
	SDA_MODE_OUT();
	SDA_OUT = 1;
	myiic_delay(DELAY_XUS);	
	SCL_OUT = 1;
	myiic_delay(DELAY_XUS);
	SCL_OUT = 0;	
}

static unsigned char myiic_wait_ack(void)
{
	unsigned char timeout = 0;
	
	SDA_MODE_IN();
	SCL_OUT = 1;
	SDA_OUT = 1;
	myiic_delay(DELAY_XUS);
	while(SDA_IN && timeout >= 200)//有致命bug 超时时间
	{
		delay_ms(1);
		timeout++;
	}
	if(timeout == 200)
	{
		printf("Timeout and Noack\n");
		return 1;
	}
	
	//应答成功
	SCL_OUT = 0;
	return 0;
}

static void myiic_write_byte(unsigned char dat)
{
	unsigned char count = 0;
	SDA_MODE_OUT();
	for(count = 0; count < 8; count++)
	{
		//每次发送一个位（bit） MSB
		SDA_OUT = (dat & 0x80) >> 7;
		dat <<= 1;
		SCL_OUT = 1;
		myiic_delay(DELAY_XUS);
		SCL_OUT = 0;
		myiic_delay(DELAY_XUS);
	}
}
	
static unsigned char myiic_read_byte(void)
{
	unsigned char temp = 0;
	unsigned char count = 0;
	
	SDA_MODE_IN();
	
	for(count = 0; count < 8; count++)
	{
		SCL_OUT = 0;
		myiic_delay(DELAY_XUS);
		SCL_OUT = 1;
		temp <<= 1;
		if(SDA_IN)
			temp++;
		else
			temp = temp;
		myiic_delay(DELAY_XUS);
	}
	
	return temp;
}

//给外部函数/文件调用
void sensor_common_write_byte(unsigned char slave_addr, unsigned char reg_addr,unsigned char dat)
{
	//1,发送开始信号
    myiic_start();
	
	myiic_write_byte(slave_addr | WRITE_FLAG);
	
	myiic_wait_ack();
	
	myiic_write_byte(reg_addr);
	
	myiic_wait_ack();
	
	myiic_write_byte(dat);
	
	myiic_wait_ack();
	
    myiic_stop();
}


//给外部函数/文件调用
unsigned char sensor_common_read_byte(unsigned char slave_addr,unsigned char reg_addr)
{
	unsigned char dat = 0;
	
	myiic_start();
	
	myiic_write_byte(slave_addr | WRITE_FLAG);
	
	myiic_wait_ack();
	
	myiic_write_byte(reg_addr);
	
	myiic_wait_ack();
	
	myiic_start();
	
	myiic_write_byte(slave_addr | READ_FLAG);
	
	myiic_wait_ack();
	
	dat = myiic_read_byte();
	
	myiic_noack();
	
	myiic_stop();
	return dat;
}


