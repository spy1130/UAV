#ifndef __MY_CODE_H
#define __MY_CODE_H

#include "stdint.h"

extern int16_t rol,pit,yaw;//imu输出的欧拉角，单位0.01度
extern int16_t vel_x,vel_y,vel_z;//速度，单位cm/s
extern int32_t dis_z;//高度,单位cm

void get_data(void);

#endif
