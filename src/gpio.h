//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### GPIO.H ################################
//---------------------------------------------

#ifndef __GPIO_H_
#define __GPIO_H_

//-- Configurations
#define GPIOA_ENABLE
// #define GPIOB_ENABLE
#define GPIOC_ENABLE
// #define GPIOD_ENABLE

// #define USE_EXTERNAL_INTS

//-- Exported Macros --------------------

//--- RCC clkEnable ---//
#define RCC_GPIOA_CLK (RCC->AHBENR & 0x00020000)
#define RCC_GPIOA_CLKEN RCC->AHBENR |= 0x00020000
#define RCC_GPIOA_CLKDIS RCC->AHBENR &= ~0x00020000

#define RCC_GPIOB_CLK (RCC->AHBENR & 0x00040000)
#define RCC_GPIOB_CLKEN RCC->AHBENR |= 0x00040000
#define RCC_GPIOB_CLKDIS RCC->AHBENR &= ~0x00040000

#define RCC_GPIOC_CLK (RCC->AHBENR & 0x00080000)
#define RCC_GPIOC_CLKEN RCC->AHBENR |= 0x00080000
#define RCC_GPIOC_CLKDIS RCC->AHBENR &= ~0x00080000

#define RCC_GPIOD_CLK (RCC->AHBENR & 0x00100000)
#define RCC_GPIOD_CLKEN RCC->AHBENR |= 0x00100000
#define RCC_GPIOD_CLKDIS RCC->AHBENR &= ~0x00100000

#define RCC_GPIOE_CLK (RCC->AHBENR & 0x00200000)
#define RCC_GPIOE_CLKEN RCC->AHBENR |= 0x00200000
#define RCC_GPIOE_CLKDIS RCC->AHBENR &= ~0x00200000

#define RCC_GPIOF_CLK (RCC->AHBENR & 0x00400000)
#define RCC_GPIOF_CLKEN RCC->AHBENR |= 0x00400000
#define RCC_GPIOF_CLKDIS RCC->AHBENR &= ~0x00400000



/* Includes ------------------------------------------------------------------*/

//--- Exported Functions ------------------------------
void GpioInit(void);
void EXTIOn (void);
void EXTIOff (void);

#endif
