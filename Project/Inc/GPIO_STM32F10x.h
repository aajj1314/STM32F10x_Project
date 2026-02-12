/* ----------------------------------------------------------------------------- * 版权所有 (c) 2013 Arm Limited (或其附属公司)。保留所有
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
 * $Date:        2013年8月26日
 * $Revision:    V1.2
 *
 * 项目：        ST STM32F10x 的 GPIO 驱动定义
 * -------------------------------------------------------------------- */

#ifndef __GPIO_STM32F10X_H
#define __GPIO_STM32F10X_H

#include <stdbool.h>
#include "stm32f10x.h"


#if defined (__CC_ARM)
  #define __FORCE_INLINE  static __forceinline
#else
  #define __FORCE_INLINE  __STATIC_INLINE
#endif

/// GPIO 引脚标识符
typedef struct _GPIO_PIN_ID {
  GPIO_TypeDef *port;
  uint8_t       num;
} GPIO_PIN_ID;

/// 端口模式
typedef enum {
  GPIO_MODE_INPUT     = 0x00,              /// GPIO 为输入
  GPIO_MODE_OUT10MHZ  = 0x01,              /// 最大输出速度 10MHz
  GPIO_MODE_OUT2MHZ   = 0x02,              /// 最大输出速度  2MHz
  GPIO_MODE_OUT50MHZ  = 0x03               /// 最大输出速度 50MHz
} GPIO_MODE;

/// 端口配置
typedef enum {
  GPIO_OUT_PUSH_PULL  = 0x00,               /// 通用推挽输出
  GPIO_OUT_OPENDRAIN  = 0x01,               /// 通用开漏输出
  GPIO_AF_PUSHPULL    = 0x02,               /// 复用功能推挽输出
  GPIO_AF_OPENDRAIN   = 0x03,               /// 复用功能开漏输出
  GPIO_IN_ANALOG      = 0x00,               /// 模拟输入
  GPIO_IN_FLOATING    = 0x01,               /// 浮空输入
  GPIO_IN_PULL_DOWN   = 0x02,               /// 下拉输入
  GPIO_IN_PULL_UP     = 0x03                /// 上拉输入
} GPIO_CONF;

/* 复用功能定义宏 */
#define AFIO_FUNC_DEF(bit, mask, val, reg) ((bit) | (mask << 5) | (val << 8) | (reg << 12))

/// 复用功能 I/O 重映射
typedef enum {
  /* 复用功能重映射和调试 I/O 配置寄存器 */
  AFIO_SPI1_NO_REMAP         = AFIO_FUNC_DEF (0,  1, 0, 0),
  AFIO_SPI1_REMAP            = AFIO_FUNC_DEF (0,  1, 1, 0),
  AFIO_I2C1_NO_REMAP         = AFIO_FUNC_DEF (1,  1, 0, 0),
  AFIO_I2C1_REMAP            = AFIO_FUNC_DEF (1,  1, 1, 0),
  AFIO_USART1_NO_REMAP       = AFIO_FUNC_DEF (2,  1, 0, 0),
  AFIO_USART1_REMAP          = AFIO_FUNC_DEF (2,  1, 1, 0),
  AFIO_USART2_NO_REMAP       = AFIO_FUNC_DEF (3,  1, 0, 0),
  AFIO_USART2_REMAP          = AFIO_FUNC_DEF (3,  1, 1, 0),
  AFIO_USART3_NO_REMAP       = AFIO_FUNC_DEF (4,  3, 0, 0),
  AFIO_USART3_REMAP_PARTIAL  = AFIO_FUNC_DEF (4,  3, 1, 0),
  AFIO_USART3_REMAP_FULL     = AFIO_FUNC_DEF (4,  3, 3, 0),
  AFIO_TIM1_NO_REMAP         = AFIO_FUNC_DEF (6,  3, 0, 0),
  AFIO_TIM1_REMAP_PARTIAL    = AFIO_FUNC_DEF (6,  3, 1, 0),
  AFIO_TIM1_REMAP_FULL       = AFIO_FUNC_DEF (6,  3, 3, 0),
  AFIO_TIM2_NO_REMAP         = AFIO_FUNC_DEF (8,  3, 0, 0),
  AFIO_TIM2_REMAP_PARTIAL_1  = AFIO_FUNC_DEF (8,  3, 1, 0),
  AFIO_TIM2_REMAP_PARTIAL_2  = AFIO_FUNC_DEF (8,  3, 2, 0),
  AFIO_TIM2_REMAP_FULL       = AFIO_FUNC_DEF (8,  3, 3, 0),
  AFIO_TIM3_NO_REMAP         = AFIO_FUNC_DEF (10, 3, 0, 0),
  AFIO_TIM3_REMAP_PARTIAL    = AFIO_FUNC_DEF (10, 3, 2, 0),
  AFIO_TIM3_REMAP_FULL       = AFIO_FUNC_DEF (10, 3, 3, 0),
  AFIO_TIM4_NO_REMAP         = AFIO_FUNC_DEF (12, 1, 0, 0),
  AFIO_TIM4_REMAP            = AFIO_FUNC_DEF (12, 1, 1, 0),
  AFIO_CAN_PA11_PA12         = AFIO_FUNC_DEF (13, 3, 0, 0),
  AFIO_CAN_PB8_PB9           = AFIO_FUNC_DEF (13, 3, 2, 0),
  AFIO_CAN_PD0_PD1           = AFIO_FUNC_DEF (13, 3, 3, 0),
  AFIO_PD01_NO_REMAP         = AFIO_FUNC_DEF (15, 1, 0, 0),
  AFIO_PD01_REMAP            = AFIO_FUNC_DEF (15, 1, 1, 0),
  AFIO_TIM5CH4_NO_REMAP      = AFIO_FUNC_DEF (16, 1, 0, 0),
  AFIO_TIM5CH4_REMAP         = AFIO_FUNC_DEF (16, 1, 1, 0),
  AFIO_ADC1_ETRGINJ_NO_REMAP = AFIO_FUNC_DEF (17, 1, 0, 0),
  AFIO_ADC1_ETRGINJ_REMAP    = AFIO_FUNC_DEF (17, 1, 1, 0),
  AFIO_ADC1_ETRGREG_NO_REMAP = AFIO_FUNC_DEF (18, 1, 0, 0),
  AFIO_ADC1_ETRGREG_REMAP    = AFIO_FUNC_DEF (18, 1, 1, 0),
  AFIO_ADC2_ETRGINJ_NO_REMAP = AFIO_FUNC_DEF (19, 1, 0, 0),
  AFIO_ADC2_ETRGINJ_REMAP    = AFIO_FUNC_DEF (19, 1, 1, 0),
  AFIO_ADC2_ETRGREG_NO_REMAP = AFIO_FUNC_DEF (20, 1, 0, 0),
  AFIO_ADC2_ETRGREG_REMAP    = AFIO_FUNC_DEF (20, 1, 1, 0),
#if defined(STM32F10X_CL)
  AFIO_ETH_NO_REMAP          = AFIO_FUNC_DEF (21, 1, 0, 0),
  AFIO_ETH_REMAP             = AFIO_FUNC_DEF (21, 1, 1, 0),
  AFIO_CAN2_NO_REMAP         = AFIO_FUNC_DEF (22, 1, 0, 0),
  AFIO_CAN2_REMAP            = AFIO_FUNC_DEF (22, 1, 1, 0),
  AFIO_ETH_MII_SEL           = AFIO_FUNC_DEF (23, 1, 0, 0),
  AFIO_ETH_RMII_SEL          = AFIO_FUNC_DEF (23, 1, 1, 0),
#endif
  AFIO_SWJ_FULL              = AFIO_FUNC_DEF (24, 7, 0, 0),
  AFIO_SWJ_FULL_NO_NJTRST    = AFIO_FUNC_DEF (24, 7, 1, 0),
  AFIO_SWJ_JTAG_NO_SW        = AFIO_FUNC_DEF (24, 7, 2, 0),
  AFIO_SWJ_NO_JTAG_NO_SW     = AFIO_FUNC_DEF (24, 7, 4, 0),
#if defined(STM32F10X_CL)
  AFIO_SPI3_NO_REMAP         = AFIO_FUNC_DEF (28, 1, 0, 0), 
  AFIO_SPI3_REMAP            = AFIO_FUNC_DEF (28, 1, 1, 0),
  AFIO_TIM2ITR_NO_REMAP      = AFIO_FUNC_DEF (29, 1, 0, 0),
  AFIO_TIM2ITR_REMAP         = AFIO_FUNC_DEF (29, 1, 1, 0),
  AFIO_PTP_PPS_NO_REMAP      = AFIO_FUNC_DEF (30, 1, 0, 0),
  AFIO_PTP_PPS_REMAP         = AFIO_FUNC_DEF (30, 1, 1, 0),
#endif
  
  /* 复用功能重映射和调试 I/O 配置寄存器 2 */
  AFIO_TIM15_NO_REMAP        = AFIO_FUNC_DEF (0,  1, 0, 1),
  AFIO_TIM15_REMAP           = AFIO_FUNC_DEF (0,  1, 1, 1),
  AFIO_TIM16_NO_REMAP        = AFIO_FUNC_DEF (1,  1, 0, 1),
  AFIO_TIM16_REMAP           = AFIO_FUNC_DEF (1,  1, 1, 1),
  AFIO_TIM17_NO_REMAP        = AFIO_FUNC_DEF (2,  1, 0, 1),
  AFIO_TIM17_REMAP           = AFIO_FUNC_DEF (2,  1, 1, 1),
  AFIO_CEC_NO_REMAP          = AFIO_FUNC_DEF (3,  1, 0, 1),
  AFIO_CEC_REMAP             = AFIO_FUNC_DEF (3,  1, 1, 1),
  AFIO_TIM1_DMA_NO_REMAP     = AFIO_FUNC_DEF (4,  1, 0, 1),
  AFIO_TIM1_DMA_REMAP        = AFIO_FUNC_DEF (4,  1, 1, 1),
  
  AFIO_TIM9_NO_REMAP         = AFIO_FUNC_DEF (5,  1, 0, 1),
  AFIO_TIM9_REMAP            = AFIO_FUNC_DEF (5,  1, 1, 1),
  AFIO_TIM10_NO_REMAP        = AFIO_FUNC_DEF (6,  1, 0, 1),
  AFIO_TIM10_REMAP           = AFIO_FUNC_DEF (6,  1, 1, 1),
  AFIO_TIM11_NO_REMAP        = AFIO_FUNC_DEF (7,  1, 0, 1),
  AFIO_TIM11_REMAP           = AFIO_FUNC_DEF (7,  1, 1, 1),
  AFIO_TIM13_NO_REMAP        = AFIO_FUNC_DEF (8,  1, 0, 1),
  AFIO_TIM13_REMAP           = AFIO_FUNC_DEF (8,  1, 0, 1),
  AFIO_TIM14_NO_REMAP        = AFIO_FUNC_DEF (9,  1, 0, 1),
  AFIO_TIM14_REMAP           = AFIO_FUNC_DEF (9,  1, 1, 1),
  AFIO_FSMC_NADV_NO_REMAP    = AFIO_FUNC_DEF (10, 1, 0, 1),
  AFIO_FSMC_NADV_REMAP       = AFIO_FUNC_DEF (10, 1, 1, 1),

  AFIO_TIM67_DAC_DMA_NO_REMAP = AFIO_FUNC_DEF(11, 1, 0, 1),
  AFIO_TIM67_DAC_DMA_REMAP   = AFIO_FUNC_DEF (11, 1, 1, 1),
  AFIO_TIM12_NO_REMAP        = AFIO_FUNC_DEF (12, 1, 0, 1),
  AFIO_TIM12_REMAP           = AFIO_FUNC_DEF (12, 1, 1, 1),
  AFIO_MISC_NO_REMAP         = AFIO_FUNC_DEF (13, 1, 0, 1),
  AFIO_MISC_REMAP            = AFIO_FUNC_DEF (13, 1, 1, 1),

  /* 保留值 */
  AFIO_UNAVAILABLE_REMAP     = AFIO_FUNC_DEF (0,  0, 0, 0)
} AFIO_REMAP;


/**
  \fn          void GPIO_PortClock (GPIO_TypeDef *GPIOx, bool en)
  \brief       端口时钟控制
  \param[in]   GPIOx  GPIO 外设指针
  \param[in]   enable 使能或禁用时钟
*/
extern void GPIO_PortClock (GPIO_TypeDef *GPIOx, bool enable);// 端口时钟控制

/**
  \fn          bool GPIO_GetPortClockState (GPIO_TypeDef *GPIOx)
  \brief       获取 GPIO 端口时钟状态
  \param[in]   GPIOx  GPIO 外设指针
  \return      true  - 已使能
               false - 已禁用
*/
extern bool GPIO_GetPortClockState (GPIO_TypeDef *GPIOx);// 获取 GPIO 端口时钟状态

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
bool GPIO_PinConfigure(GPIO_TypeDef      *GPIOx,/* GPIO 外设指针 */
                       uint32_t           num,/* 端口引脚编号 */
                       GPIO_CONF          conf,/* 端口引脚配置 */
                       GPIO_MODE          mode);// 配置端口引脚

/**
  \fn          void GPIO_PinWrite (GPIO_TypeDef *GPIOx, uint32_t num, uint32_t val)
  \brief       写入端口引脚
  \param[in]   GPIOx  GPIO 外设指针
  \param[in]   num    端口引脚编号
  \param[in]   val    端口引脚值 (0 或 1)
*/
__FORCE_INLINE void GPIO_PinWrite (GPIO_TypeDef *GPIOx, uint32_t num, uint32_t val) {
  if (val & 1) {
    GPIOx->BSRR = (1UL << num);         // 设置
  } else {
    GPIOx->BSRR = (1UL << (num + 16));  // 清除
  }
}// 写入端口引脚

/**
  \fn          uint32_t GPIO_PinRead (GPIO_TypeDef *GPIOx, uint32_t num)
  \brief       读取端口引脚
  \param[in]   GPIOx  GPIO 外设指针
  \param[in]   num    端口引脚编号
  \return      引脚值 (0 或 1)
*/
__FORCE_INLINE uint32_t GPIO_PinRead (GPIO_TypeDef *GPIOx, uint32_t num) {
  return ((GPIOx->IDR >> num) & 1);
}// 读取端口引脚

/**
  \fn          void GPIO_PortWrite (GPIO_TypeDef *GPIOx, uint16_t mask, uint16_t val)
  \brief       写入端口引脚
  \param[in]   GPIOx  GPIO 外设指针
  \param[in]   mask   选中的引脚
  \param[in]   val    引脚值
*/
__FORCE_INLINE void GPIO_PortWrite (GPIO_TypeDef *GPIOx, uint16_t mask, uint16_t val) {
  GPIOx->ODR = (GPIOx->ODR & ~mask) | val;
}// 写入端口引脚

/**
  \fn          uint16_t GPIO_PortRead (GPIO_TypeDef *GPIOx)
  \brief       读取端口引脚
  \param[in]   GPIOx  GPIO 外设指针
  \return      端口引脚输入
*/
__FORCE_INLINE uint16_t GPIO_PortRead (GPIO_TypeDef *GPIOx) {
  return (GPIOx->IDR);
}// 读取端口引脚

/**
  \fn          void GPIO_AFConfigure (AFIO_REMAP af_type)
  \brief       配置复用功能
  \param[in]   af_type 复用功能重映射类型
*/
void GPIO_AFConfigure (AFIO_REMAP af_type);// 配置复用功能

/**
  \fn          void GPIO_Init_Output(GPIO_TypeDef *GPIOx)
  \brief       初始化 GPIO 端口为输出模式
  \param[in]   GPIOx  GPIO 外设指针
*/
void GPIO_Init_Output(GPIO_TypeDef *GPIOx);// 初始化 GPIO 端口为输出模式



#endif /* __GPIO_STM32F10X_H */

