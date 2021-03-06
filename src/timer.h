//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F303
// ##
// #### TIMER.H ################################
//---------------------------------------------

#ifndef _TIMER_H_
#define _TIMER_H_

//-- Exported Macros ------------------------------
#define DUTY_10_PERCENT		100
#define DUTY_50_PERCENT		500
#define DUTY_100_PERCENT        1000
#define DUTY_FOR_DMAX           450

#define DUTY_ALWAYS    (DUTY_100_PERCENT + 1)
#define DUTY_NONE    0

//-- Exported Hardware Macros ---------------------
#define ENABLE_TIM1			TIM1->CR1 |= TIM_CR1_CEN;
#define DISABLE_TIM1			TIM1->CR1 &= ~TIM_CR1_CEN;

#define ENABLE_TIM3			TIM3->CR1 |= TIM_CR1_CEN;
#define DISABLE_TIM3			TIM3->CR1 &= ~TIM_CR1_CEN;

#define EnableTimer6 TIM6->CR1 |= TIM_CR1_CEN
#define DisableTimer6 TIM6->CR1 &= ~TIM_CR1_CEN

#define EnableTimer7 TIM7->CR1 |= TIM_CR1_CEN
#define DisableTimer7 TIM7->CR1 &= ~TIM_CR1_CEN

#define RCC_TIM1_CLK 		(RCC->APB2ENR & 0x00000800)
#define RCC_TIM1_CLKEN     	RCC->APB2ENR |= 0x00000800
#define RCC_TIM1_CLKDIS 	RCC->APB2ENR &= ~0x00000800

#define RCC_TIM2_CLK            (RCC->APB1ENR & 0x00000001)
#define RCC_TIM2_CLKEN          RCC->APB1ENR |= 0x00000001
#define RCC_TIM2_CLKDIS         RCC->APB1ENR &= ~0x00000001

#define RCC_TIM3_CLK 		(RCC->APB1ENR & 0x00000002)
#define RCC_TIM3_CLKEN     	RCC->APB1ENR |= 0x00000002
#define RCC_TIM3_CLKDIS    	RCC->APB1ENR &= ~0x00000002

#define RCC_TIM4_CLK            (RCC->APB1ENR & 0x00000004)
#define RCC_TIM4_CLKEN          RCC->APB1ENR |= 0x00000004
#define RCC_TIM4_CLKDIS         RCC->APB1ENR &= ~0x00000004

#define RCC_TIM6_CLK            (RCC->APB1ENR & 0x00000010)
#define RCC_TIM6_CLKEN          RCC->APB1ENR |= 0x00000010;
#define RCC_TIM6_CLKDIS         RCC->APB1ENR &= ~0x00000010;

#define RCC_TIM7_CLK            (RCC->APB1ENR & 0x00000020)
#define RCC_TIM7_CLKEN          RCC->APB1ENR |= 0x00000020;
#define RCC_TIM7_CLKDIS         RCC->APB1ENR &= ~0x00000020;

#define RCC_TIM15_CLK 		(RCC->APB2ENR & 0x00010000)
#define RCC_TIM15_CLKEN     	RCC->APB2ENR |= 0x00010000
#define RCC_TIM15_CLKDIS 	RCC->APB2ENR &= ~0x00010000

#define RCC_TIM16_CLK 		(RCC->APB2ENR & 0x00020000)
#define RCC_TIM16_CLKEN     	RCC->APB2ENR |= 0x00020000
#define RCC_TIM16_CLKDIS 	RCC->APB2ENR &= ~0x00020000

#define RCC_TIM17_CLK 		(RCC->APB2ENR & 0x00040000)
#define RCC_TIM17_CLKEN     	RCC->APB2ENR |= 0x00040000
#define RCC_TIM17_CLKDIS 	RCC->APB2ENR &= ~0x00040000

#define RCC_TIM20_CLK 		(RCC->APB2ENR & 0x00100000)
#define RCC_TIM20_CLKEN     	RCC->APB2ENR |= 0x00100000
#define RCC_TIM20_CLKDIS 	RCC->APB2ENR &= ~0x00100000


//--- Exported Functions ------------------------------
void Wait_ms (unsigned short);

// void TIM2_Init(void);
void TIM_1_Init (void);
void TIM_3_Init (void);

void UpdateTIMSync (unsigned short);
void UpdateTIM_MosfetA (unsigned short);
void UpdateTIM_MosfetB (unsigned short);
void EnablePreload_MosfetA (void);
void DisablePreload_MosfetA (void);
void EnablePreload_MosfetB (void);
void DisablePreload_MosfetB (void);

void Update_TIM1_CH1 (unsigned short);
void Update_TIM1_CH2 (unsigned short);

void Update_TIM3_CH2 (unsigned short);
void Update_TIM3_CH3 (unsigned short);
void Update_TIM3_CH4 (unsigned short);

void TIM_4_Init (void);
void TIM6_Init(void);
void TIM6_IRQHandler (void);
void TIM7_Init(void);
void TIM7_IRQHandler (void);


#endif /* _TIMER_H_ */
