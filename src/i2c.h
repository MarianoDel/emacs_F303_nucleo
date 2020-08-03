//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### I2C.H #################################
//---------------------------------------------
#ifndef _I2C_H_
#define _I2C_H_

// Config Defines --------------------------------------------------------------
#define I2C_ADDRESS_OWN    0x01
#define I2C_ADDRESS_SLV    0x3C
#define I2C_ADDRESS_MSK    0x7F


// #define I2C_WITH_INTS

// Common Defines --------------------------------------------------------------
#define RCC_I2C1_CLK (RCC->APB1ENR & 0x00200000)
#define RCC_I2C1_CLKEN RCC->APB1ENR |= 0x00200000
#define RCC_I2C1_CLKDIS RCC->APB1ENR &= ~0x00200000

#define RCC_I2C2_CLK (RCC->APB1ENR & 0x00400000)
#define RCC_I2C2_CLKEN RCC->APB1ENR |= 0x00400000
#define RCC_I2C2_CLKDIS RCC->APB1ENR &= ~0x00400000

// Module Exported Functions ---------------------------------------------------
void I2C1_Init (void);
void I2C1_SendByte (unsigned char);
void I2C1_SendAddr (unsigned char);
void I2C1_SendMultiByte (unsigned char *, unsigned short);

#endif    /* _I2C_H_ */
