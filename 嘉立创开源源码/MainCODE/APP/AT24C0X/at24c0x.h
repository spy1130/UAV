#ifndef __at24c0x_H
#define __at24c0x_H
#include "stm32f10x.h"

#define AT24C0X_SLAVE_ADDR 0XA0

void my_at24c0x_init(void);
unsigned char my_at24c0x_read_byte(unsigned char addr);
void my_at24c0x_write_byte(unsigned char addr,unsigned char dat);



void my_at24c0x_test(void);

#endif
