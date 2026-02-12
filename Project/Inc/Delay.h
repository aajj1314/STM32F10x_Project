#ifndef __DELAY_H__
#define __DELAY_H__

#include "stm32f10x.h"

void Delay_Init(void);
void Delay_ms(uint16_t ms);
void Delay_us(uint32_t us);
void Delay_s(uint16_t s);

#endif