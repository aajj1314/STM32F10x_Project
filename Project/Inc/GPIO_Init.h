#ifndef __GPIO_INIT_H__
#define __GPIO_INIT_H__

#include "stm32f10x.h"

// 从标准外设库GPIO_Pin_定义中直接提取后,简化的引脚定义
#define Pin0    GPIO_Pin_0    
#define Pin1    GPIO_Pin_1
#define Pin2    GPIO_Pin_2
#define Pin3    GPIO_Pin_3
#define Pin4    GPIO_Pin_4
#define Pin5    GPIO_Pin_5
#define Pin6    GPIO_Pin_6
#define Pin7    GPIO_Pin_7
#define Pin8    GPIO_Pin_8
#define Pin9    GPIO_Pin_9
#define Pin10   GPIO_Pin_10
#define Pin11   GPIO_Pin_11
#define Pin12   GPIO_Pin_12
#define Pin13   GPIO_Pin_13
#define Pin14   GPIO_Pin_14
#define Pin15   GPIO_Pin_15
#define PinAll  GPIO_Pin_All

// 简化的GPIO模式定义
#define FLOATING   0  // 浮空输入
#define IPU        1  // 上拉输入
#define IPD        2  // 下拉输入
#define PP         3  // 推挽输出
#define OD         4  // 开漏输出

// 简化的GPIO速度定义
#define M2   0  // 2MHz
#define M10  1  // 10MHz
#define M50  2  // 50MHz

// 主要初始化函数
void GPIO_Init_ANAN(GPIO_TypeDef* port, uint16_t pin, uint8_t mode, uint8_t speed);

// 便捷宏定义
#define  GPIO_IN(port, pin, mode)        GPIO_Init_ANAN(port, pin, mode, M50)  
#define GPIO_OUT(port, pin, mode, spd)   GPIO_Init_ANAN(port, pin, mode, spd)

#endif // __GPIO_INIT_H__
