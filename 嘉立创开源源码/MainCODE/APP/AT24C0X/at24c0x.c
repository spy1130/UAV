#include "at24c0x.h"
#include "myiic.h"
#include "delay.h"
#include "usart.h"
#include "myiic.h"

void my_at24c0x_init(void)
{
	myiic_init();
}

unsigned char my_at24c0x_read_byte(unsigned char addr)
{
	unsigned char dat;
	dat = sensor_common_read_byte(AT24C0X_SLAVE_ADDR,addr);
	return dat;
}

void my_at24c0x_write_byte(unsigned char addr,unsigned char dat)
{
	sensor_common_write_byte(AT24C0X_SLAVE_ADDR, addr,dat);
}


void my_at24c0x_test(void)
{
	#define OPERATION_ADDR 0
	static unsigned char dat = 0,flag = 1;
	unsigned char temp = 0;
	
	temp = my_at24c0x_read_byte(OPERATION_ADDR);
	
	if(flag == 1)
	{
		flag = 0;
	}
	else
		printf("temp = %d\n",temp);
	
	my_at24c0x_write_byte(OPERATION_ADDR, dat++);
	delay_ms(5);
	temp = my_at24c0x_read_byte(OPERATION_ADDR);
	printf("temp = %d\n",temp);
	
	if(dat == 255)
		dat = 0;
}





