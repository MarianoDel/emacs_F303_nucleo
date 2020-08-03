//---------------------------------------------
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### I2C.C #################################
//---------------------------------------------

// Includes --------------------------------------------------------------------
#include "i2c.h"
#include "stm32f3xx.h"

// Externals -------------------------------------------------------------------

// Globals ---------------------------------------------------------------------

// Module Funtions -------------------------------------------------------------
void I2C1_Init (void)
{
    // Clock for Peripheral
    if (!RCC_I2C1_CLK)
        RCC_I2C1_CLKEN;

    // Clock switch HSI to SYSCLK
    // RCC->CFGR3 |= RCC_CFGR3_I2C1SW;

    // //---- Acomodo punteros ----
    // ptx1 = tx1buff;
    // ptx1_pckt_index = tx1buff;
    // prx1 = rx1buff;

    // Speed and Port options
    I2C1->TIMINGR = 0x00201D2B;    //for HSI
    I2C1->CR1 = I2C_CR1_PE;
    // I2C1->CR2 = I2C_CR2_AUTOEND | (2 << 16) | (I2C1_OWN_ADDRESS << 1);
    I2C1->CR2 = I2C_CR2_AUTOEND | (I2C_ADDRESS_SLV << 1);    

    // Output current for Fast mode + (Fm+)
    //SYSCFG_CFGR1

    // Override Gpios Alternative functions
    // PB8 SCL/D15; PB9 SDA/D14 -> AF4
    unsigned int temp = 0;
    temp = GPIOB->AFR[1];
    temp &= 0xFFFFFF00;
    temp |= 0x00000044;    //PB9 -> AF4 PA8 -> AF4
    GPIOB->AFR[1] = temp;

#ifdef I2C_WITH_INTS
    // Int and priority
    NVIC_EnableIRQ(I2C1_EV_IRQn);
    NVIC_SetPriority(I2C1_EV_IRQn, 8);
    NVIC_EnableIRQ(I2C1_ER_IRQn);
    NVIC_SetPriority(I2C1_ER_IRQn, 8);
#endif
}


void I2C1_SendByte (unsigned char data)
{
    //check empty
    // while (!(I2C1->ISR & I2C_ISR_TXE));    
    // I2C1->TXDR = data;
    // I2C1->CR2 |= I2C_CR2_START;

    // if ((I2C1->ISR & I2C_ISR_TXE) == I2C_ISR_TXE)
    // {
    //     I2C1->TXDR = data;
    //     I2C1->CR2 |= I2C_CR2_START;
    // }

    if ((I2C1->ISR & I2C_ISR_TXE) == I2C_ISR_TXE)
    {
        // I2C1->TXDR = data;
        I2C1->CR2 |= I2C_CR2_START;
    }
    
    
}

void I2C1_SendAddr (unsigned char addr)
{    
    //check START ready
    if (!(I2C1->CR2 & I2C_CR2_START))
    {
        unsigned int temp;
        temp = I2C1->CR2;
        temp &= (I2C_ADDRESS_MSK << 1);
        temp |= (addr << 1);
        I2C1->CR2 = temp;

        I2C1->CR2 |= I2C_CR2_START;
    }
}


void I2C1_SendMultiByte (unsigned char *pdata, unsigned short size)
{
}


//--- end of file ---//
