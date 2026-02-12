/* -----------------------------------------------------------------------------
 * 版权所有 (c) 2016 Arm Limited (或其附属公司)。保留所有
 * 权利。
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * 根据 Apache License, Version 2.0（许可证）授权；您可以
 * 除非符合许可证的规定，否则不得使用此文件。
 * 您可以在以下位置获取许可证：
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * 除非适用法律要求或书面同意，否则软件
 * 根据许可证分发的软件按“原样”分发，不附带任何
 * 明示或暗示的保证或条件。请参阅许可证中
 * 有关权限和限制的具体规定。
 *
 *
 * $Date:        2016年4月26日
 * $Revision:    V1.3
 *
 * 项目：        ST STM32F10x 的 GPIO 驱动
 * -------------------------------------------------------------------- */

#include "GPIO_STM32F10x.h"

/* 历史记录：
 *  版本 1.3
 *    修正了串行线 JTAG 引脚复用功能配置的损坏问题。
 *  版本 1.2
 *    添加了 GPIO_GetPortClockState 函数
 *    GPIO_PinConfigure 函数在未启用时会启用 GPIO 外设时钟
 *  版本 1.1
 *    重写了 GPIO_PortClock 和 GPIO_PinConfigure 函数
 *    清理并简化了 GPIO_STM32F1xx 头文件
 *    添加了 GPIO_AFConfigure 函数及其相关定义
 *  版本 1.0
 *    初始版本发布
 */

/* 串行线 JTAG 引脚复用功能配置
 * 可由 C 预处理器用户定义：
 *   AFIO_SWJ_FULL, AFIO_SWJ_FULL_NO_NJTRST, AFIO_SWJ_JTAG_NO_SW, AFIO_SWJ_NO_JTAG_NO_SW
 */
#ifndef AFIO_MAPR_SWJ_CFG_VAL
#define AFIO_MAPR_SWJ_CFG_VAL   (AFIO_SWJ_FULL)    // 完整 SWJ (JTAG-DP + SW-DP)
#endif

/**
  \fn          void GPIO_PortClock (GPIO_TypeDef *GPIOx, bool en)
  \brief       端口时钟控制
  \param[in]   GPIOx  GPIO 外设指针
  \param[in]   enable 使能或禁用时钟
*/
void GPIO_PortClock (GPIO_TypeDef *GPIOx, bool enable) {

  if (enable) {
    if      (GPIOx == GPIOA) RCC->APB2ENR |=  (1U << 2);
    else if (GPIOx == GPIOB) RCC->APB2ENR |=  (1U << 3);
    else if (GPIOx == GPIOC) RCC->APB2ENR |=  (1U << 4);
    else if (GPIOx == GPIOD) RCC->APB2ENR |=  (1U << 5);
    else if (GPIOx == GPIOE) RCC->APB2ENR |=  (1U << 6);
    else if (GPIOx == GPIOF) RCC->APB2ENR |=  (1U << 7);
    else if (GPIOx == GPIOG) RCC->APB2ENR |=  (1U << 8);
  } else {
    if      (GPIOx == GPIOA) RCC->APB2ENR &= ~(1U << 2);
    else if (GPIOx == GPIOB) RCC->APB2ENR &= ~(1U << 3);
    else if (GPIOx == GPIOC) RCC->APB2ENR &= ~(1U << 4);
    else if (GPIOx == GPIOD) RCC->APB2ENR &= ~(1U << 5);
    else if (GPIOx == GPIOE) RCC->APB2ENR &= ~(1U << 6);
    else if (GPIOx == GPIOF) RCC->APB2ENR &= ~(1U << 7);
    else if (GPIOx == GPIOG) RCC->APB2ENR &= ~(1U << 8);
  }
}

/**
  \fn          bool GPIO_GetPortClockState (GPIO_TypeDef *GPIOx)
  \brief       获取 GPIO 端口时钟状态
  \param[in]   GPIOx  GPIO 外设指针
  \return      true  - 已使能
               false - 已禁用
*/
bool GPIO_GetPortClockState (GPIO_TypeDef *GPIOx) // 获取 GPIO 端口时钟状态
{

  if      (GPIOx == GPIOA) { return ((RCC->APB2ENR &  (1U << 2)) != 0U); }
  else if (GPIOx == GPIOB) { return ((RCC->APB2ENR &  (1U << 3)) != 0U); }
  else if (GPIOx == GPIOC) { return ((RCC->APB2ENR &  (1U << 4)) != 0U); }
  else if (GPIOx == GPIOD) { return ((RCC->APB2ENR &  (1U << 5)) != 0U); }
  else if (GPIOx == GPIOE) { return ((RCC->APB2ENR &  (1U << 6)) != 0U); }
  else if (GPIOx == GPIOF) { return ((RCC->APB2ENR &  (1U << 7)) != 0U); }
  else if (GPIOx == GPIOG) { return ((RCC->APB2ENR &  (1U << 8)) != 0U); }

  return false; 
}


/**
  \fn          bool GPIO_PinConfigure (GPIO_TypeDef      *GPIOx,
                                       uint32_t           num,
                                       GPIO_CONF          conf,
                                       GPIO_MODE          mode)
  \brief       配置端口引脚
  \param[in]   GPIOx         GPIO 外设指针
  \param[in]   num           端口引脚编号
  \param[in]   mode          \ref GPIO_MODE
  \param[in]   conf          \ref GPIO_CONF
  \return      true  - 成功
               false - 错误
*/
bool GPIO_PinConfigure(GPIO_TypeDef *GPIOx, uint32_t num, GPIO_CONF conf,
                                                          GPIO_MODE mode) // 配置端口引脚
{
  __IO uint32_t *reg;
  if (num > 15) return false;

  if (GPIO_GetPortClockState(GPIOx) == false) {
    /* 使能 GPIOx 外设时钟 */
    GPIO_PortClock (GPIOx, true);
  }

  if (mode == GPIO_MODE_INPUT) {
    if      (conf == GPIO_IN_PULL_DOWN) {
      /* 为选中的输入使能下拉 */
      GPIOx->ODR &= ~(1 << num);
    }
    else if (conf == GPIO_IN_PULL_UP) {
      /* 为选中的输入使能上拉 */
      conf &= ~1;
      GPIOx->ODR |=  (1 << num);
    }
  }

  if (num < 8) {
    reg = &GPIOx->CRL;
  }
  else {
    num -= 8;
    reg = &GPIOx->CRH;
  }
  *reg &= ~(0xF << (num << 2));
  *reg |= ((conf << 2) | mode) << (num << 2);
  return true;
}
/**
  \fn          void GPIO_Init_Output(GPIO_TypeDef *GPIOx)
  \brief       初始化 GPIO 端口为输出模式
  \param[in]   GPIOx  GPIO 外设指针
   作者：       安安
*/
void GPIO_Init_Output(GPIO_TypeDef *GPIOx)
{
  GPIO_PinConfigure(GPIOx, 0, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 1, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 2, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 3, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ); 
  GPIO_PinConfigure(GPIOx, 4, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 5, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 6, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 7, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 8, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 9, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 10, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 11, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 12, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 13, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 14, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
  GPIO_PinConfigure(GPIOx, 15, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);
}



/**
  \fn          void GPIO_AFConfigure (AFIO_REMAP af_type)
  \brief       配置复用功能
  \param[in]   af_type 复用功能重映射类型
*/
void GPIO_AFConfigure (AFIO_REMAP af_type) {
           uint32_t msk, val;
  volatile uint32_t mapr;

  if (af_type != AFIO_UNAVAILABLE_REMAP) {
    msk = (af_type >> 5) & 0x07;
    val = (af_type >> 8) & 0x0F;

    if (!(RCC->APB2ENR & RCC_APB2ENR_AFIOEN)) {
      /* 使能 AFIO 外设时钟 */
      RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    }
    if (af_type & (1 << 12)) {
      /* 复用功能重映射和调试 I/O 配置寄存器 2 */
      mapr  = AFIO->MAPR2;
      mapr &= ~(msk << (af_type & 0x1F));
      mapr |=  (val << (af_type & 0x1F));
      AFIO->MAPR2 = mapr;
    }
    else {
      /* 复用功能重映射和调试 I/O 配置寄存器 */
      mapr  = AFIO->MAPR;
      mapr &= ~(msk << (af_type & 0x1F));
      mapr |=  (val << (af_type & 0x1F));

      /* 串行线 JTAG 配置 */
      msk  =   (AFIO_MAPR_SWJ_CFG_VAL >> 5) & 0x07;
      val  =   (AFIO_MAPR_SWJ_CFG_VAL >> 8) & 0x0F;
      mapr &= ~(msk << (AFIO_MAPR_SWJ_CFG_VAL & 0x1F));
      mapr |=  (val << (AFIO_MAPR_SWJ_CFG_VAL & 0x1F));

      AFIO->MAPR = mapr;
    }
  }
}

