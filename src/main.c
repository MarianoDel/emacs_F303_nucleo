//------------------------------------------------
// #### PROYECTO PLACA NUCLEO-F303RE STM32 -  ####
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### MAIN.C ###################################
//------------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx.h"
#include "hard.h"
#include "gpio.h"
#include "timer.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"



/* Externals ------------------------------------------------------------------*/
//--- Externals para avisar data ready en usart
volatile unsigned char usart1_have_data = 0;
// volatile unsigned char usart2_have_data = 0;
// volatile unsigned char usart3_have_data = 0;
// volatile unsigned char usart4_have_data = 0;
// volatile unsigned char usart5_have_data = 0;

//--- Externals del ADC
volatile unsigned short adc_ch [ADC_CHANNEL_QUANTITY] = { 0 };
#ifdef HARD_TEST_MODE_ADC1_INT
volatile unsigned char seq_ready = 0;
#endif
//--- Externals de los timers
volatile unsigned short wait_ms_var = 0;
volatile unsigned short timer_standby = 0;


/* Globals ------------------------------------------------------------------*/

//--- Module Functions Declarations ----------
void TimingDelay_Decrement(void);
static void Error_Handler(void);
// extern void EXTI0_IRQHandler (void);

//--- Module Function Definitions ----------------------------------------------
int main (void)
{
    //Configuracion systick    
    if (SysTick_Config(72000))
    {
        /* Capture error */
        Error_Handler();
    }

    // Configuracion led. & Enabled Channels
    GpioInit();


#ifdef HARD_TEST_MODE_LED_SWITCH
    while(1)
    {
        // if (USER_BLUE)
        //     LED_ON;
        // else
        //     LED_OFF;

        // Wait_ms(10);
        if (USER_BLUE)
        {
            LED_TOGGLE;
            Wait_ms(500);
        }
    }    
#endif

#ifdef HARD_TEST_MODE_USART1_TX
    //enciendo usart1
    Usart1Config();

    while(1)
    {
        if (USER_BLUE)
        {
            LED_ON;
            Usart1Send("User Blue Switch\n");
            Wait_ms(100);
        }
        else
            LED_OFF;

        if (!timer_standby)
        {
            timer_standby = 1000;
            Usart1Send("M");
        }
    }    
#endif

#ifdef HARD_TEST_MODE_USART1_RX
    //enciendo usart1
    Usart1Config();
    char buff_local [128] = { 0 };
    unsigned char readed = 0;

    while(1)
    {
        Wait_ms(3000);
        if (usart1_have_data)
        {
            readed = ReadUsart1Buffer(buff_local, 127);
            *(buff_local + readed) = '\n';    //cambio el '\0' por '\n' antes de enviar
            *(buff_local + readed + 1) = '\0';    //ajusto el '\0'
            Usart1Send(buff_local);
        }
    }    
#endif

#ifdef HARD_TEST_MODE_TIMER1
    unsigned short pwm = 0;
    TIM_1_Init();
    
    while(1)
    {
        for (pwm = 0; pwm < DUTY_100_PERCENT; pwm++)
            Update_TIM1_CH1(pwm);

        Wait_ms(2);
    }    
#endif

#ifdef HARD_TEST_MODE_ADC1
    //undef the dma conf on adc.h
    AdcConfig();

    //Start convertions
    ADC1->CR |= ADC_CR_ADSTART;
    
    while(1)
    {
        if (ADC1->ISR & ADC_ISR_EOS)
        {
            ADC1->ISR |= ADC_ISR_EOS;
            if (LED)
                LED_OFF;
            else
                LED_ON;
        }
    }    
#endif

#ifdef HARD_TEST_MODE_ADC1_EOS
    //undef the dma conf on adc.h
    AdcConfig();

    //Start convertions
    ADC1->CR |= ADC_CR_ADSTART;
    
    while(1)
    {
        //eoc & eos funciona ok
        unsigned int temp = ADC1->ISR;
        if ((temp & ADC_ISR_EOC) && (temp & ADC_ISR_EOS))
        {
            ADC1->ISR |= ADC_ISR_EOS;
            LED_OFF;
            Wait_ms(100);
            ADC1->CR |= ADC_CR_ADSTART;
            LED_ON;
        }
        //fin eoc & eos funciona ok
    }    
#endif
    
#ifdef HARD_TEST_MODE_ADC1_INT
    //ADC with ints
    AdcConfig();

    while(1)
    {
        Wait_ms(100);
        ADC1->CR |= ADC_CR_ADSTART;
        LED_ON;
    }    
#endif

#ifdef HARD_TEST_MODE_ADC1_DMA
    //ADC & DMA
    AdcConfig();
    DMAConfig();
    DMA1_Channel1->CCR |= DMA_CCR_EN;
    ADC1->CR |= ADC_CR_ADSTART;
    //end of ADC & DMA
    
    while(1)
    {
        if (sequence_ready)
        {
            sequence_ready_reset;
            
            if (LED)
                LED_OFF;
            else
                LED_ON;
        }
    }    
#endif


#ifdef HARD_TEST_MODE_I2C1_MASTER
    I2C1_Init();

    while (1)
    {
        Wait_ms(300);
        I2C1_SendByte(0);
        if (LED)
            LED_OFF;
        else
            LED_ON;
    }
    
#endif

#ifdef HARD_TEST_MODE_SPI_MASTER
    // SPI_Config();

    while (1)
    {
        Wait_ms(300);
        // SPI_Send_Single('A');
        if (LED)
            LED_OFF;
        else
            LED_ON;
    }
    
#endif



    //-- Welcome Messages --------------------
// #ifdef HARD
//     Usart1Send(HARD);
//     Wait_ms(100);    
// #else
// #error	"No Hardware defined in hard.h file"
// #endif

// #ifdef SOFT
//     Usart1Send(SOFT);
//     Wait_ms(100);    
// #else
// #error	"No Soft Version defined in hard.h file"
// #endif
// #ifdef FEATURES
//     Usart1Send((const char *) FEATURES);
//     Wait_ms(100);
// #endif


    // TIM_4_Init();
}
//--- End of Main ---//

//--- Module Functions Definitions ----------------------
void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

    // if (timer_filters)
    //     timer_filters--;
    
    // if (timer_led)
    //     timer_led--;

    // if (timer_led_pwm < 0xFFFF)
    //     timer_led_pwm ++;
    
}

// void EXTI0_IRQHandler (void)
// {
//     if(EXTI->PR & 0x00000001)	//Line0
//     {
//         if (LED)
//             LED_OFF;
//         else
//             LED_ON;

//         if (SENSE_MOSFET_A)
//         {
//             DisablePreload_MosfetA();
//             UpdateTIM_MosfetA(0);
//             EnablePreload_MosfetA();
//             UpdateTIM_MosfetA(DUTY_FOR_DMAX);            
//         }
//         else if (SENSE_MOSFET_B)
//         {
//             DisablePreload_MosfetB();
//             UpdateTIM_MosfetB(0);
//             EnablePreload_MosfetB();
//             UpdateTIM_MosfetB(DUTY_FOR_DMAX);
//         }
//         else
//         {
//             //llegue tarde
//         }
        
//         EXTI->PR |= 0x00000001;
//     }
// }

void Error_Handler(void)
{
    if (LED)
        LED_OFF;
    else
        LED_ON;

    for (unsigned char i = 0; i < 255; i++)
    {
        asm (	"nop \n\t"
                "nop \n\t"
                "nop \n\t" );
    }
}
//--- end of file ---//

