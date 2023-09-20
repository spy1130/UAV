#include "stm32f10x.h"
#include "sys.h"
#ifndef _CONFIG_H
#define _CONFIG_H

//位带宏定义
//#define BITBAND(addr, bitnum) ((addr&0xF0000000) + 0x2000000 + ((addr&0xFFFFF)<<5) + (bitnum<<2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))
//IO 口地址位带映射
//#define PERIPH_BASE ((unsigned int)0x40000000) /* 声明 片上外设分区基地址 */
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000) /* 声明 APB2 总线基地址 */
#define GPIOA_BASE (APB2PERIPH_BASE + 0x0800) /* 声明 GPIO 端口 A 基地址 */
#define GPIOB_BASE (APB2PERIPH_BASE + 0x0C00) /* 声明 GPIO 端口 B 基地址 */
#define GPIOC_BASE (APB2PERIPH_BASE + 0x1000) /* 声明 GPIO 端口 C 基地址 */
#define GPIOD_BASE (APB2PERIPH_BASE + 0x1400) /* 声明 GPIO 端口 D 基地址 */
#define GPIOE_BASE (APB2PERIPH_BASE + 0x1800) /* 声明 GPIO 端口 E 基地址 */
#define GPIOF_BASE (APB2PERIPH_BASE + 0x1C00) /* 声明 GPIO 端口 F 基地址 */
#define GPIOG_BASE (APB2PERIPH_BASE + 0x2000) /* 声明 GPIO 端口 G 基地址 */
#define GPIOA_ODR_Addr (GPIOA_BASE+12) //GPIOA 输出数据寄存器地址 0x4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE+12) //GPIOB 输出数据寄存器地址 0x40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE+12) //GPIOC 输出数据寄存器地址 0x4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE+12) //GPIOD 输出数据寄存器地址 0x4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE+12) //GPIOE 输出数据寄存器地址 0x4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE+12) //GPIOF 输出数据寄存器地址 0x40011A0C
#define GPIOG_ODR_Addr (GPIOG_BASE+12) //GPIOG 输出数据寄存器地址 0x40011E0C
#define GPIOA_IDR_Addr (GPIOA_BASE+8) //GPIOA 输入数据寄存器地址 0x40010808
#define GPIOB_IDR_Addr (GPIOB_BASE+8) //GPIOB 输入数据寄存器地址 0x40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE+8) //GPIOC 输入数据寄存器地址 0x40011008
#define GPIOD_IDR_Addr (GPIOD_BASE+8) //GPIOD 输入数据寄存器地址 0x40011408
#define GPIOE_IDR_Addr (GPIOE_BASE+8) //GPIOE 输入数据寄存器地址 0x40011808
#define GPIOF_IDR_Addr (GPIOF_BASE+8) //GPIOF 输入数据寄存器地址 0x40011A08
#define GPIOG_IDR_Addr (GPIOG_BASE+8) //GPIOG 输入数据寄存器地址 0x40011E08
//单个 IO 口位带操作
#define PA_OUT(n) BIT_ADDR(GPIOA_ODR_Addr,n) //PAx 输出
#define PA_IN(n) BIT_ADDR(GPIOA_IDR_Addr,n) //PAx 输入
#define PB_OUT(n) BIT_ADDR(GPIOB_ODR_Addr,n) //PBx 输出
#define PB_IN(n) BIT_ADDR(GPIOB_IDR_Addr,n) //PBx 输入
#define PC_OUT(n) BIT_ADDR(GPIOC_ODR_Addr,n) //PCx 输出
#define PC_IN(n) BIT_ADDR(GPIOC_IDR_Addr,n) //PCx 输入
#define PD_OUT(n) BIT_ADDR(GPIOD_ODR_Addr,n) //PDx 输出
#define PD_IN(n) BIT_ADDR(GPIOD_IDR_Addr,n) //PDx 输入
#define PE_OUT(n) BIT_ADDR(GPIOE_ODR_Addr,n) //PEx 输出
#define PE_IN(n) BIT_ADDR(GPIOE_IDR_Addr,n) //PEx 输入
#define PF_OUT(n) BIT_ADDR(GPIOF_ODR_Addr,n) //PFx 输出
#define PF_IN(n) BIT_ADDR(GPIOF_IDR_Addr,n) //PFx 输入
#define PG_OUT(n) BIT_ADDR(GPIOG_ODR_Addr,n) //PGx 输出
#define PG_IN(n) BIT_ADDR(GPIOG_IDR_Addr,n) //PGx 输入

#endif

