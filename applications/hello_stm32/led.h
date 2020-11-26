/*
 *  LED -- simple LED support
 */

#ifndef __LED_h
#define __LED_h

#if defined(STM32H743xx)
/* These settings are for the STM32H743ZI NUCLEO board */

#include "stm32h7xx_hal.h"

/* Configure GPIO pin : PB14 (LD3) */   
GPIO_InitTypeDef GPIO_InitStruct =
{
  .Pin = GPIO_PIN_14,  
  .Mode = GPIO_MODE_OUTPUT_PP,
  .Speed = GPIO_SPEED_LOW 
};
  
#define LED_INIT() ({\
   __HAL_RCC_GPIOB_CLK_ENABLE();\
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);\
})

#define LED_ON() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
#define LED_OFF() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

#else
/* default case is to print */

#define __LED_PRINTING 1
#define LED_ON()  fputs( "LED ON\n", stderr )
#define LED_OFF() fputs( "LED OFF\n", stderr )
#endif

#ifndef LED_INIT
#define LED_INIT() 
#endif

#endif
