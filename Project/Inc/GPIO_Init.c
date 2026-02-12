#include "GPIO_Init.h"

// 获取GPIO端口的时钟使能宏
static uint32_t get_gpio_clock(GPIO_TypeDef* port)
{
    if(port == GPIOA) return RCC_APB2Periph_GPIOA;
    else if(port == GPIOB) return RCC_APB2Periph_GPIOB;
    else if(port == GPIOC) return RCC_APB2Periph_GPIOC;
    else if(port == GPIOD) return RCC_APB2Periph_GPIOD;
    else if(port == GPIOE) return RCC_APB2Periph_GPIOE;
    else if(port == GPIOF) return RCC_APB2Periph_GPIOF;
    else if(port == GPIOG) return RCC_APB2Periph_GPIOG;
    else return 0;
}

// 主要初始化函数
void GPIO_Init_ANAN(GPIO_TypeDef* port, uint16_t pin, uint8_t mode, uint8_t speed)
{
    uint32_t clock = get_gpio_clock(port);
    if(clock == 0) return;
    
    // 使能GPIO时钟
    RCC_APB2PeriphClockCmd(clock, ENABLE);
    
    // 配置GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    
    // 设置模式
    switch(mode) {
        case FLOATING:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            break;
        case IPU:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
            break;
        case IPD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
            break;
        case PP:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
            break;
        case OD:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
            break;
        default:
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            break;
    }
    
    // 设置速度
    switch(speed) {
        case M2:
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
            break;
        case M10:
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
            break;
        case M50:
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            break;
        default:
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            break;
    }
    
    GPIO_Init(port, &GPIO_InitStructure);
}
