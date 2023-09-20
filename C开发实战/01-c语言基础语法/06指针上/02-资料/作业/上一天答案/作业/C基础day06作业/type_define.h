#pragma once

/************** 数据类型定义. *************/
#define u8 unsigned char
#define u16 unsigned short int
#define u32 unsigned long int
#define uc8 counst u8
#define uc16 const u16
#define uc32 const u32
#define vu8 volatile u8
#define vu16 volatile u16
#define vu32 volatile u32
#define vuc8 const vu8
#define vuc16 const vu16
#define vuc32 const vu32

/** bool 类型定义 **/
typedef enum
    {
        False = 0,
        True = !False
    } BOOL;