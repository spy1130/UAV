/*KS10X.h*/


#ifndef Mpu6050_H
#define Mpu6050_H

//****************************************
// 定义KS10X内部地址
//****************************************

#define SlaveAddress1   0xe8    //IIC写入时的地址字节数据，+1为读取
#define SlaveAddress2   0xd0
#define SlaveAddress3   0xd2
#define SlaveAddress4   0xd4
#define SlaveAddress5   0xd6
#define SlaveAddress6   0xd8
#define SlaveAddress7   0xda
#define SlaveAddress8   0xdc
#define SlaveAddress9   0xde
#define SlaveAddress10  0xe0
#define SlaveAddress11  0xe2
#define SlaveAddress12  0xe4
#define SlaveAddress13  0xe6
#define SlaveAddress14  0xea
#define SlaveAddress15  0xec
#define SlaveAddress16  0xee
#define SlaveAddress17  0xf8
#define SlaveAddress18  0xfa
#define SlaveAddress19  0xfc
#define SlaveAddress20  0xfe

#define Command_5_NT_MM        0xb0       // 0-5m  普通无温补 mm    33ms
#define Command_5_NT_US        0xb2       // 0-5m  普通无温补 us    32ms
#define Command_5_YT_MM        0xb4       // 0-5m  普通有温补 mm    87ms
#define Command_11_NT_MM       0xb8       // 0-11m 普通无温补 mm    68ms
#define Command_11_NT_US       0xba       // 0-11m 普通无温补 us    66ms
#define Command_11_YT_MM       0xbc       // 0-11m 普通有温补 mm    87ms
#define Command_11_NT_MM_D     0xbd       // 12cm-11m 普通无温补 mm 68ms
#define Command_11_NT_US_D     0xbe       // 12cm-11m 普通无温补 us 66ms
#define Command_11_YT_MM_D     0xbf       // 12cm-11m 普通有温补 mm 87ms

#include "sys.h"

u8 Single_ReadI2C(u8 SlaveAddress, u8 REG_Address);
void Single_WriteI2C(u8 SlaveAddress, u8 REG_Address, u8 REG_data);
void Change_Addr(u8 OldAdddr, u8 NewAddr);
float Read_KS10X_Data(u8 SlaveAddress, u8 command);
void KS10X_Change_Addr_Init(u8 OldAddr, u8 NewAddr);
u32 Detect_KS10X(u8 SlaveAddress, u8 command);
void Read_KS10X_Data_delay(u8 SlaveAddress, u8 command);
#endif
