//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### GPIO.C ################################
//---------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx.h"
#include "gpio.h"
#include "hard.h"


/* Externals ------------------------------------------------------------------*/


/* Globals ------------------------------------------------------------------*/


/* Module Functions -----------------------------------------------------------*/


//--- Tamper config ---//
// void Tamper_Config(void)
// {
// 	unsigned long temp;

// 	//--- GPIOB ---//
// 	//--- Clock ---//
// 	if (!(RCC->APB2ENR & 0x00000008))
// 		RCC->APB2ENR |= 0x00000008;

// 	//--- Config pines ---//
// 	temp = GPIOB->CRH;
// 	temp &= 0xFF0FFFFF;
// 	temp |= 0x00800000;
// 	GPIOB->CRH = temp;
// 	GPIOB->BSRR = 0x00002000;
// }



//-- GPIO Configuration --------------------
void GpioInit (void)
{
    unsigned long temp;

    //--- MODER ---//
    //00: Input mode (reset state)
    //01: General purpose output mode
    //10: Alternate function mode
    //11: Analog mode

    //--- OTYPER ---//
    //These bits are written by software to configure the I/O output type.
    //0: Output push-pull (reset state)
    //1: Output open-drain

    //--- ORSPEEDR ---//
    //These bits are written by software to configure the I/O output speed.
    //x0: Low speed.
    //01: Medium speed.
    //11: High speed.
    //Note: Refer to the device datasheet for the frequency.

    //--- PUPDR ---//
    //These bits are written by software to configure the I/O pull-up or pull-down
    //00: No pull-up, pull-down
    //01: Pull-up
    //10: Pull-down
    //11: Reserved


    //--- GPIOA Config ------------------//
#ifdef GPIOA_ENABLE
    if (!RCC_GPIOA_CLK)
        RCC_GPIOA_CLKEN;

#ifdef HARD_TEST_MODE_SPI_MASTER
    temp = GPIOA->MODER;	//2 bits por pin
    temp &= 0xFFFF03FF;		//PA5 PA6 PA7 alternative
    temp |= 0x0000A800;        //
    GPIOA->MODER = temp;
#elif defined HARD_TEST_MODE_RC522
    temp = GPIOA->MODER;	//2 bits por pin
    temp &= 0xFFC300F0;		//PA0 PA1 out; PA4 input; PA5 PA6 PA7 alternative
    temp |= 0x0028A805;        //PA9 PA10 alternative
    GPIOA->MODER = temp;    
#else
    temp = GPIOA->MODER;	//2 bits por pin
    temp &= 0xFFC0F3FF;		//PA5 output
    temp |= 0x002A0400;        //PA8 PA9 PA10 alternative
    GPIOA->MODER = temp;
#endif

    temp = GPIOA->OTYPER;	//1 bit por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOA->OTYPER = temp;

    temp = GPIOA->OSPEEDR;	//2 bits por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOA->OSPEEDR = temp;

    temp = GPIOA->PUPDR;	//2 bits por pin
    temp &= 0xFFFFFCFF;        //PA4 pullup
    temp |= 0x00000100;
    GPIOA->PUPDR = temp;

#endif    //GPIOA_ENABLE

    //--- GPIOB Config ------------------//
#ifdef GPIOB_ENABLE
    if (!RCC_GPIOB_CLK)
        RCC_GPIOB_CLKEN;
    
    temp = GPIOB->MODER;	//2 bits por pin
    temp &= 0xFFF0FFFF;		//PB9 - PB8 (alternative)
    temp |= 0x000A0000;		
    GPIOB->MODER = temp;

    temp = GPIOB->OTYPER;	//1 bit por pin
    temp &= 0xFFFFF0FF;         //PB9 - PB8 open drain
    temp |= 0x00000300;
    GPIOB->OTYPER = temp;

    temp = GPIOB->OSPEEDR;	//2 bits por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOB->OSPEEDR = temp;

    temp = GPIOB->PUPDR;	//2 bits por pin
    temp &= 0xFFF0FFFF;        //PB9 - PB8 pullup
    temp |= 0x00050000;
    GPIOB->PUPDR = temp;

#endif    //GPIOB_ENABLE

    //--- GPIOC Config ------------------//
#ifdef GPIOC_ENABLE
    if (!RCC_GPIOC_CLK)
        RCC_GPIOC_CLKEN;
    
    temp = GPIOC->MODER;	//2 bits por pin
    temp &= 0xF3FFFFFF;		//PC13 input
    temp |= 0x00000000;		
    GPIOC->MODER = temp;

    temp = GPIOC->OTYPER;	//1 bit por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOC->OTYPER = temp;

    temp = GPIOC->OSPEEDR;	//2 bits por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOC->OSPEEDR = temp;

    temp = GPIOC->PUPDR;	//2 bits por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOC->PUPDR = temp;

#endif    //GPIOC_ENABLE

    //--- GPIOD Config ------------------//
#ifdef GPIOD_ENABLE
    if (!RCC_GPIOD_CLK)
        RCC_GPIOD_CLKEN;
    
    temp = GPIOD->MODER;	//2 bits por pin
    temp &= 0xFFFFC3C0;		//PA0 - PA2 (analog input); PA5 - PA6 (analog input)
    temp |= 0x00003C3F;		
    GPIOD->MODER = temp;

    temp = GPIOD->OTYPER;	//1 bit por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOD->OTYPER = temp;

    temp = GPIOD->OSPEEDR;	//2 bits por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOD->OSPEEDR = temp;

    temp = GPIOD->PUPDR;	//2 bits por pin
    temp &= 0xFFFFFFFF;
    temp |= 0x00000000;
    GPIOD->PUPDR = temp;

#endif    //GPIOD_ENABLE

    
// #ifdef USE_EXTERNAL_INTS
//     //Interrupt en PA4 y PA5
//     if (!RCC_AFIO_CLK)
//         RCC_AFIO_CLKEN;

//     //Select Port A & Pin0 for external interrupt
//     temp = AFIO->EXTICR[0];
//     temp &= ~AFIO_EXTICR1_EXTI0;
//     temp |= AFIO_EXTICR1_EXTI0_PA;
//     AFIO->EXTICR[0] = (unsigned short) temp;
    
//     // EXTI->IMR |= 0x00000001; 			//Corresponding mask bit for interrupts EXTI0
//     EXTI->EMR |= 0x00000000; 			//Corresponding mask bit for events
//     EXTI->RTSR |= 0x00000001; 			//Interrupt line on rising edge
//     EXTI->FTSR |= 0x00000000; 			//Interrupt line on falling edge

//     NVIC_EnableIRQ(EXTI0_IRQn);
//     NVIC_SetPriority(EXTI0_IRQn, 2);

// #endif
}

#ifdef USE_EXTERNAL_INTS
inline void EXTIOff (void)
{
    EXTI->IMR &= ~0x00000001;
}

inline void EXTIOn (void)
{
    EXTI->IMR |= 0x00000001;
}
#endif

//--- end of file ---//
