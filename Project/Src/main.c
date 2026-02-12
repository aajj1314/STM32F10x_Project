#include "main.h"

int main (void)
{
  Delay_Init();
  #if 0
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_SetBits(GPIOA, GPIO_Pin_All);   
  uint16_t i=0xFFFE;
 while(1)
 {
   GPIO_Write(GPIOA,i);
   Delay_ms(500);
   i=(i<<1)|0x0001;
   if(i==0xFFFF)
   {
    i=0xFFFE;
   }
 }
////////////////////////////////////////////

 //GPIO_PortClock(GPIOB, true);
 GPIO_Init_Output(GPIOA);
 GPIO_Init_Output(GPIOC);
 GPIO_PinWrite(GPIOC, 13, 0);
 //GPIO_PinConfigure(GPIOB, 1 , GPIO_OUT_PUSH_PULL ,GPIO_MODE_OUT50MHZ);
 while(1)
 {
 GPIO_PinWrite(GPIOB, 1, 1);
 GPIO_PinWrite(GPIOC, 13, 0);
 Delay_ms(1000);
 GPIO_PinWrite(GPIOB, 1, 0);
 GPIO_PinWrite(GPIOC, 13, 1);
 Delay_ms(1000);
 }
 }
////////////////////////////////////////////

  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  // GPIO_InitTypeDef GPIO_InitStructure;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_Init_ANAN(GPIOA, Pin1, PP, M50);
  GPIO_OUT(GPIOC, Pin13, PP , M50);
  GPIO_IN(GPIOA, Pin1, IPU);
  GPIO_ResetBits(GPIOA, Pin1);
  while(1)
  {
    LED_ON;
    Delay_ms(1000);
    LED_OFF;
    Delay_ms(1000);

  }
#else






#endif
}








