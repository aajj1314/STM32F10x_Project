#ifndef __MAIN_H__
#define __MAIN_H__
//#include "GPIO_STM32F10x.h"
#include "stm32f10x.h"
#include "Delay.h"
#include "GPIO_Init.h"
#define LED_ON  GPIO_SetBits(GPIOC, Pin13)
#define LED_OFF GPIO_ResetBits(GPIOC, Pin13)



#endif // __MAIN_H__
