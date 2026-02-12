#include "Delay.h"
#if 0
static volatile uint32_t TimingDelay;

void Delay_Init(void)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

void Delay_ms(uint16_t ms)
{
  SysTick_Config(SystemCoreClock*9 / 8000);
  TimingDelay = ms;
  while(TimingDelay != 0);
}

void Delay_us(uint32_t us)
{
  uint32_t temp;
  SysTick->LOAD = 9 * us;  
  SysTick->VAL = 0;
  SysTick->CTRL = 5;
  do
  {
    temp = SysTick->CTRL;
  }
  while((temp & 0x01) && !(temp & (1 << 16)));
  SysTick->CTRL = 0;
  SysTick->VAL = 0;
}

void Delay_s(uint32_t s)
{
  while(s--)
  {
    Delay_ms(1000);
  }
}
void SysTick_Handler(void)
{
  if(TimingDelay != 0)
  {
    TimingDelay--;
  }
}
#else

int f_us = 9;
int f_ms = 9000;
void Delay_Init(void) 
{
   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 设置外部源时钟 72MHZ/8=9MHZ
}
void Delay_us(uint32_t us)
{
   u32 temp;
   SysTick->LOAD = us * f_us - 1;
   SysTick->VAL = 0X00;
   SysTick->CTRL |= (0X01 << 0);
   do {
       temp = SysTick->CTRL;
   } while ((temp & (0x01 << 0)) && (!(temp & (0x01 << 16))));
   SysTick->CTRL &= ~(0X01 << 0);
}
void Delay_ms(uint16_t ms) 
{
   u32 temp;
   SysTick->LOAD = ms * f_ms - 1;
   SysTick->VAL = 0X00;
   SysTick->CTRL |= (0X01 << 0);
   do {
       temp = SysTick->CTRL;
   } while ((temp & (0x01 << 0)) && (!(temp & (0x01 << 16))));
   SysTick->CTRL &= ~(0X01 << 0);
}
void Delay_s(uint16_t s) 
{
   int n;
   for (n = 0; n < s; n++) {  
       Delay_ms(1000);
   }
}

#endif
