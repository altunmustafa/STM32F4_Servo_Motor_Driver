#ifndef MA_TIM_H
#define MA_TIM_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	
#include "stm32f4xx.h"

#define APB1_CLOCK 168000000/4
#define APB2_CLOCK 168000000/2

typedef enum{
    APB1    = 1,
    APB2    = 2,
    APB_ERR = 0
}MA_TIM_APBx_t;

typedef struct{
    MA_TIM_APBx_t	APBx;
    TIM_TypeDef* 	TIMx;       /* TIM1...TIM14 */
    uint16_t 	Prescaler;      /* Between 0x0000 and 0xFFFF so 0-65535. */
    uint32_t	Clock;          /* Spacial parameter! 
                                 * NOTICE: This value should be divisible by "SystemCoreClock" (168.000.000 for STM32F407)
                                 * Between 1-168.000.000 (Hz) for STM32F407 
                                 * If this parameter value is greater than 0, "Prescaler" is calculated according to this value,
                                 * and the "Prescaler" entered is ignored. */
    uint16_t 	CounterMode;    /* TIM_CounterMode_Up - TIM_CounterMode_Down - TIM_CounterMode_CenterAligned1 - TIM_CounterMode_CenterAligned2 - TIM_CounterMode_CenterAligned3*/
    uint32_t 	Period;         /* Between 0x0000 and 0xFFFF so 0 and 65535. */
    uint32_t	Signal_Clock;   /* Spacial parameter! 
                                 * NOTICE: This value should be divisible by "Clock"
                                 * Between 1-"Clock" (Hz) 
                                 * If this parameter value is greater than 0, "Period" is calculated according to this value,
                                 * and the "Period" entered is ignored. */
    uint16_t 	ClockDivision;      /* This parameter can be a value of @ref TIM_Clock_Division_CKD */
    uint8_t  	RepetitionCounter;  /* Between 0x00 and 0xFF so 0-255. Valid only for TIM1 and TIM8 (Advanced Timers). */
}MA_TIM_TimeBase_t;

void MA_TIM_TimeBaseInit(MA_TIM_TimeBase_t* MA_TIM_TimeBase);
void MA_TIM_CompleteParameters(MA_TIM_TimeBase_t* MA_TIM_TimeBase);
uint16_t MA_TIM_CalcPrescaler(MA_TIM_APBx_t APBx, uint32_t DesiredClock);
MA_TIM_APBx_t MA_TIM_ObtainAPBx(TIM_TypeDef* TIMx);
	
#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* MA_TIM_H */
