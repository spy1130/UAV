#ifndef _system_H
#define _system_H
#include <stm32f10x.h>
/*位带计算公式：
((A & 0xF0000000)+0x02000000+((A &0x000FFFFF)<<5)+(n<<2))
注：左移五位相当于*32，左移两位相当于*4；
A：要操作的位所在寄存器的地址
n：位号，即在寄存器的第几位。*/

#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
//addr：要操作的寄存器的地址；bitnum：要操作的寄存器的某一位。
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))	//此处只有强制转换成指针变量，才能被识别出是地址。
																//volatile：提醒编译器：后面的变量随时都会发生改变。
																//以便编译器直接读取他所在的地址
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) //IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C.为什么要加12？因为ODR—输出寄存器相对于基地址的偏移量为12。
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C.详见中文参考手册8.2.4。
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C.
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C.
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C.
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C.
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C.
#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 
#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 
#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入
#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入
#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
#endif

