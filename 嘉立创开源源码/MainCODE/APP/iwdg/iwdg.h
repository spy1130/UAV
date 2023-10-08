#ifndef __iwdg_H
#define __iwdg_H

#include "stm32f10x.h"

void Iwdg_Init(unsigned int pre,unsigned int lrl);
void Iwdg_Feed(void);

#endif


