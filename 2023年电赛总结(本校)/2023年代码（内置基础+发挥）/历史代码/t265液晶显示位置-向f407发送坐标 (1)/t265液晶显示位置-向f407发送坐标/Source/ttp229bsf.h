
#ifndef _TTP229BSF_H
#define _TTP229BSF_H

#include "config.h"

#define TTP229_SCL PB_OUT(7)
#define TTP229_SDO PB_IN(6)

u16 TTP229_Readkey(void);
void TTP229_GPIO_Init(void);
void keyplay(u8 keycode);
void keyaction(void);

#endif

