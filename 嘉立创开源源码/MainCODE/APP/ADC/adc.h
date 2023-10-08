#ifndef __adc_H
#define __adc_H

#include "stm32f10x.h"
#include "bit_operation.h"

void Adc_Init(void);
unsigned int Adc_Filter_Average(unsigned char num);
static unsigned int Adc_Start_Conversion(void);

#endif



