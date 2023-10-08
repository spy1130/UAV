#ifndef __temperature_H
#define __temperature_H
#include "stm32f10x.h"

unsigned int Adc_Filter_Average_Temperature(unsigned char num);
unsigned int Adc_Get_Temperature(void);
float Adc_Temperature_Handle(unsigned int dat);

#endif 




