//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### ADC.C #################################
//---------------------------------------------

/* Includes ------------------------------------------------------------------*/
#include "adc.h"
#include "stm32f3xx.h"
#include "hard.h"


/* Externals ------------------------------------------------------------------*/
extern volatile unsigned short adc_ch [];


#ifdef ADC_WITH_INT
extern volatile unsigned char seq_ready;
#endif

#ifdef ADC_WITH_TEMP_SENSE
extern volatile unsigned short tt_take_temp_sample;
#endif

/* Globals ------------------------------------------------------------------*/
#ifdef ADC_WITH_INT
volatile unsigned short * p_channel;
#endif

#ifdef ADC_WITH_TEMP_SENSE
// ------- del sensor de Temperatura -------
unsigned short board_temp [SIZEOF_BOARD_TEMP];
unsigned short last_temp = 0;
unsigned char board_temp_index = 0;
unsigned char new_temp_sample = 0;
#endif

/* Module Private Functions ---------------------------------------------------*/
void ADC_Delay (void);

/* Module Functions -----------------------------------------------------------*/
//Single conversion mode (CONT=0)
//In Single conversion mode, the ADC performs a single sequence of conversions,
//converting all the channels once.

//Continuous conversion mode (CONT=1)
//In continuous conversion mode, when a software or hardware trigger event occurs,
//the ADC performs a sequence of conversions, converting all the channels once and then
//automatically re-starts and continuously performs the same sequence of conversions

//Discontinuous mode (DISCEN)
//In this mode (DISCEN=1), a hardware or software trigger event is required to start
//each conversion defined in the sequence. Only with (CONT=0)

void AdcConfig (void)
{
    //ADC clk source and dividers    PLL / 6 => 72MHz / 6 = 12MHz
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_4 | RCC_CFGR2_ADCPRE12_1 | RCC_CFGR2_ADCPRE12_0;
    ADC12_CCR_ASYNC_CLK;   
    
    if (!RCC_ADC12_CLK)
        RCC_ADC12_CLK_ON;

    // preseteo los registros a default, la mayoria necesita tener ADC apagado
    ADC1->CR = 0x20000000;
    ADC1->SMPR1 = 0x00000000;
    ADC1->SMPR2 = 0x00000000;
    ADC1->SQR1 = 0x00000000;
    ADC1->SQR2 = 0x00000000;    
    ADC1->SQR3 = 0x00000000;
    ADC1->SQR4 = 0x00000000;
    ADC1->CFGR = 0x00000000;
    
    //set Continuos or Discontinuous
    // ADC1->CFGR |= ADC_CFGR_CONT;
    
    //set sampling time for each channel
    // SMPR1 CH1 - CH9
    ADC1->SMPR1 |= ADC_SMPR1_SMP2_2 | ADC_SMPR1_SMP2_1 | ADC_SMPR1_SMP2_0;    //sample time Channel 2
    ADC1->SMPR1 |= ADC_SMPR1_SMP3_2 | ADC_SMPR1_SMP3_1 | ADC_SMPR1_SMP3_0;    //sample time Channel 3
    ADC1->SMPR1 |= ADC_SMPR1_SMP4_2 | ADC_SMPR1_SMP4_1 | ADC_SMPR1_SMP4_0;    //sample time Channel 4
    ADC1->SMPR1 |= ADC_SMPR1_SMP5_2 | ADC_SMPR1_SMP5_1 | ADC_SMPR1_SMP5_0;    //sample time Channel 5
    ADC1->SMPR1 |= ADC_SMPR1_SMP6_2 | ADC_SMPR1_SMP6_1 | ADC_SMPR1_SMP6_0;    //sample time Channel 6
    ADC1->SMPR1 |= ADC_SMPR1_SMP7_2 | ADC_SMPR1_SMP7_1 | ADC_SMPR1_SMP7_0;    //sample time Channel 7
    // SMPR2 CH10 - CH18

    //set regular channel selection
    // SQR1 set from first to four conversion (4 regular channels)
    ADC1->SQR1 |= ADC_SQR1_SQ1_1;                     //Channel 2
    ADC1->SQR1 |= ADC_SQR1_SQ2_1 | ADC_SQR1_SQ2_0;    //Channel 3
    ADC1->SQR1 |= ADC_SQR1_SQ3_2;                     //Channel 4
    ADC1->SQR1 |= ADC_SQR1_SQ4_2 | ADC_SQR1_SQ4_0;    //Channel 5
    // SQR2 five to nine conversion (5 regular channels)
    ADC1->SQR2 |= ADC_SQR2_SQ5_2 | ADC_SQR2_SQ5_1;    //Channel 6
    ADC1->SQR2 |= ADC_SQR2_SQ6_2 | ADC_SQR2_SQ6_1 | ADC_SQR2_SQ6_0;    //Channel 7
    // SQR3 ten to fourteen conversion  (5 regular channels)
    // SQR4 fifteen to sixteen conversion  (2 regular channels)

    //set channels quantity to convert
    ADC1->SQR1 |= ADC_SQR1_L_2 | ADC_SQR1_L_1;    //convert 6 channels
    // ADC1->SQR1 |= ADC_SQR1_L_2 | ADC_SQR1_L_0;    //convert 5 channels
    // ADC1->SQR1 |= ADC_SQR1_L_2;    //convert 4 channels    


    
#ifdef ADC_WITH_INT        
    //set interrupts
    ADC1->IER |= ADC_IER_EOCIE;

    //set pointer
    p_channel = &adc_ch[0];

    NVIC_EnableIRQ(ADC1_IRQn);
    NVIC_SetPriority(ADC1_IRQn, 3);
#endif

#ifdef ADC_WITH_TEMP_SENSE
    ADC->CCR |= ADC_CCR_TSEN;
#endif

    //ADC Calibration
    //Set Voltage Regulator
    ADC1->CR &= ~(ADC_CR_ADVREGEN_1 | ADC_CR_ADVREGEN_0);    //to reset
    ADC1->CR |= ADC_CR_ADVREGEN_0;    //to enable

    ADC_Delay();    

    //ADC calibration, ADEN = 0, ADENCALIF = 0,
    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);
    
    //Enable the ADC
    ADC1->CR |= ADC_CR_ADEN;
    while (!(ADC1->ISR & ADC_ISR_ADRDY));

#ifdef ADC_WITH_DMA
    ADC1->CFGR |= ADC_CFGR_DMAEN;
    ADC1->CFGR |= ADC_CFGR_DMACFG;    //circular mode
#endif
}

#ifdef ADC_WITH_INT
void ADC1_2_IRQHandler (void)
{
    if (ADC1->ISR & ADC_ISR_EOS)
    {
        if (LED)
            LED_OFF;
        else
            LED_ON;
    }

    if (ADC1->ISR & ADC_ISR_EOC)
    {
        // if (ADC1->ISR & ADC_ISR_EOS)
        if (ADC1->ISR & 0x0008)
        {
            p_channel = &adc_ch[ADC_LAST_CHANNEL_QUANTITY];
            *p_channel = ADC1->DR;
            p_channel = &adc_ch[0];
            seq_ready = 1;


        }
        else
        {
            *p_channel = ADC1->DR;		//
            if (p_channel < &adc_ch[ADC_LAST_CHANNEL_QUANTITY])
                p_channel++;

            // if (ADC1->ISR & ADC_ISR_EOC)
            // if (ADC1->ISR & 0x0004)                
            // {
            //     ADC1->ISR |= ADC_ISR_EOC;
            // }
        }
        //clear pending
        ADC1->ISR |= ADC_ISR_EOC | ADC_ISR_EOS;

    }



}
#endif



#ifdef ADC_WITH_TEMP_SENSE
void UpdateTemp(void)
{
    //hago update cada 1 seg
    if (!tt_take_temp_sample)
    {
        tt_take_temp_sample = 1000;

        board_temp [board_temp_index] = ReadADC1_SameSampleTime(ADC_CH16);
        //board_temp [0] = ReadADC1_SameSampleTime(ADC_CH16);

        if (board_temp_index < (SIZEOF_BOARD_TEMP - 1))
            board_temp_index++;
        else
            board_temp_index = 0;

        new_temp_sample = 1;
    }
}

//devuelve el valor promedio de la temperatura
//si existen nuevas muestras hace la cuenta, sino contesta el ultimo valor calculado
unsigned short GetTemp (void)
{
    unsigned char i;
    unsigned int t = 0;

    if (new_temp_sample)
    {
        for (i = 0; i < SIZEOF_BOARD_TEMP; i++)
            t += board_temp[i];

        last_temp = t >> 3;
        new_temp_sample = 0;
    }

    return ConvertTemp(last_temp);
}

void FillTempBuffer (void)
{
    unsigned char i;
    unsigned short dummy;

    dummy = ReadADC1_SameSampleTime(ADC_CH16);

    for (i = 0; i < SIZEOF_BOARD_TEMP; i++)
        board_temp[i] = dummy;

}

short ConvertTemp (unsigned short adc_temp)
{
    int32_t temperature; /* will contain the temperature in degree Celsius */
    //temperature = (((int32_t) ADC1->DR * VDD_APPLI / VDD_CALIB) - (int32_t) *TEMP30_CAL_ADDR );
    temperature = (int32_t) *TEMP30_CAL_ADDR - adc_temp;
    temperature *= 1000;
    temperature = temperature / 5336;	//4.3mV / °C
    temperature = temperature + 30;

    return (short) temperature;
}
#endif //ADC_WITH_TEMP_SENSE

void ADC_Delay (void)
{
    for (unsigned char i = 0; i < 255; i++)
    {
        asm (	"nop \n\t"
                "nop \n\t"
                "nop \n\t" );
    }
}
//--- end of file ---//


