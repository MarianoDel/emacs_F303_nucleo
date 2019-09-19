//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### ADC.H #################################
//---------------------------------------------
#ifndef _ADC_H_
#define _ADC_H_

#include "hard.h"		//por configuracion diferentes en V1_0 y V1_1

//----------- Defines For Configuration --------------//
//----------- Some ADC Configurations ----------------//
#ifdef HARD_TEST_MODE_ADC1_INT
#define ADC_WITH_INT
#endif
// #define ADC_WITH_DMA


#ifdef WITH_TEMP_CONTROL
#define ADC_WITH_TEMP_SENSE
#endif

#ifdef ADC_WITH_TEMP_SENSE
#define SIZEOF_BOARD_TEMP		8
#endif
//----------- End of ADC Configurations --------------//

#define IS1		adc_ch[0]
#define IS2	        adc_ch[1]
#define IS3    	       	adc_ch[2]
#define IS4    	       	adc_ch[3]
#define V200_Sense      adc_ch[4]
#define V40_Sense      	adc_ch[5]
#define ADC_CHANNEL_QUANTITY         6
#define ADC_LAST_CHANNEL_QUANTITY    (ADC_CHANNEL_QUANTITY - 1)


#define RCC_ADC12_CLK 		(RCC->AHBENR & 0x10000000)
#define RCC_ADC12_CLK_ON	RCC->AHBENR |= 0x10000000
#define RCC_ADC12_CLK_OFF 	RCC->AHBENR &= ~0x10000000

#define RCC_ADC34_CLK 		(RCC->AHBENR & 0x20000000)
#define RCC_ADC34_CLK_ON	RCC->AHBENR |= 0x20000000
#define RCC_ADC34_CLK_OFF 	RCC->AHBENR &= ~0x20000000

#define ADC12_CCR_ASYNC_CLK         (ADC12_COMMON->CCR &= ~(ADC12_CCR_CKMODE))
#define ADC12_CCR_SYNC_CLK          (ADC12_COMMON->CCR |= ADC12_CCR_CKMODE_0)
#define ADC12_CCR_SYNC_CLK_DIV_2    (ADC12_COMMON->CCR |= ADC12_CCR_CKMODE_1)
#define ADC12_CCR_SYNC_CLK_DIV_4    (ADC12_COMMON->CCR |= ADC12_CCR_CKMODE_1 | ADC12_CCR_CKMODE_0)

// /* Temperature sensor calibration value address */
// #define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
// #define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
// #define VDD_CALIB ((uint16_t) (330))
// #define VDD_APPLI ((uint16_t) (330))



//--- Exported Module Functions ------------
void AdcConfig (void);

#ifdef ADC_WITH_TEMP_SENSE
void UpdateTemp(void);
unsigned short GetTemp (void);
void FillTempBuffer (void);
short ConvertTemp (unsigned short);
#endif
#endif /* _ADC_H_ */
