/**
 * @author  Mustafa Altun
 * @website http://altunmustafa.com
 * @link    https://github.com/altunmustafa/stm32f4-bacis-projects
 * @version 0.1
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   Customized Timer Library for STM32F4xx devices
 */	
 
#ifndef MA_TIM_H
#define MA_TIM_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	
#include "stm32f4xx.h"

#define APB1_CLOCK 168000000/4
#define APB2_CLOCK 168000000/2

#define MA_TIM_Enable(TIMx) TIM_Cmd(TIMx, ENABLE)
#define MA_TIM_Disable(TIMx) TIM_Cmd(TIMx, DISABLE)

#define MA_TIM_ARRPreloadEnable(TIMx) TIM_ARRPreloadConfig(TIMx, ENABLE)
#define MA_TIM_ARRPreloadDisable(TIMx) TIM_ARRPreloadConfig(TIMx, DISABLE)

#define MA_TIM_OC1PreloadEnable(TIMx) TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable)
#define MA_TIM_OC2PreloadEnable(TIMx) TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable)
#define MA_TIM_OC3PreloadEnable(TIMx) TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable)
#define MA_TIM_OC4PreloadEnable(TIMx) TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable)

#define MA_TIM_OC1PreloadDisable(TIMx) TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Disable)
#define MA_TIM_OC2PreloadDisable(TIMx) TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Disable)
#define MA_TIM_OC3PreloadDisable(TIMx) TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Disable)
#define MA_TIM_OC4PreloadDisable(TIMx) TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Disable)

typedef enum{
    APB1    = 1,
    APB2    = 2,
    APB_ERR = 0
}MA_TIM_APBx_t;

typedef enum{
    CH1 = 1,
    CH2 = 2,
    CH3 = 3,
    CH4 = 4
}MA_TIM_CHx_t;

typedef struct{
    MA_TIM_APBx_t   APBx;
    TIM_TypeDef*    TIMx;       /* TIM1...TIM14 */
    uint16_t 	Prescaler;      /* Between 0x0000 and 0xFFFF so 0-65535. */
    uint32_t	TimerClock;     /* Spacial parameter! 
                                 * NOTICE: This value should be divisible by "SystemCoreClock" (168.000.000 for STM32F407)
                                 * Between 1-168.000.000 (Hz) for STM32F407 
                                 * If this parameter value is greater than 0, "Prescaler" is calculated according to this value,
                                 * and the "Prescaler" entered is ignored. */
    uint16_t 	CounterMode;    /* TIM_CounterMode_Up
                                   TIM_CounterMode_Down - TIM_CounterMode_CenterAligned1 - TIM_CounterMode_CenterAligned2 - TIM_CounterMode_CenterAligned3*/
    uint32_t 	Period;         /* Between 0x0000 and 0xFFFF so 0 and 65535. */
    uint32_t	SignalClock;    /* Spacial parameter! 
                                 * NOTICE: This value should be divisible by "Clock"
                                 * Between 1-"Clock" (Hz) 
                                 * If this parameter value is greater than 0, "Period" is calculated according to this value,
                                 * and the "Period" entered is ignored. */
    uint16_t 	ClockDivision;      /* This parameter can be a value of @ref TIM_Clock_Division_CKD */
    uint8_t  	RepetitionCounter;  /* Between 0x00 and 0xFF so 0-255. Valid only for TIM1 and TIM8 (Advanced Timers). */
}MA_TIM_TimeBaseInitStructure_t;

typedef struct{
    TIM_TypeDef*    TIMx;   /*  -TIM1...TIM14 */
    
    MA_TIM_CHx_t CHx;       /*  -CH1...CH4 */
    
    uint16_t OCMode;        /*  Specifies the TIM mode.
                                -TIM_OCMode_Timing
                                -TIM_OCMode_Active
                                -TIM_OCMode_Inactive
                                -TIM_OCMode_Toggle
                                -TIM_OCMode_PWM1
                                -TIM_OCMode_PWM2 */
    
    uint16_t OutputState;   /*  Specifies the TIM Output Compare state.
                                -TIM_OutputState_Disable
                                -TIM_OutputState_Enable */

    uint16_t OutputNState;  /*  Specifies the TIM complementary Output Compare state.
                                -TIM_OutputNState_Disable
                                -TIM_OutputNState_Enable
                                @note This parameter is valid only for TIM1 and TIM8. */

    uint32_t Pulse;         /*  Specifies the pulse value to be loaded into the Capture Compare Register.
                                -A number between 0x0000 and 0xFFFF (65.535) */
                                
    uint16_t OCPolarity;    /*  Specifies the output polarity.
                                -TIM_OCPolarity_High
                                -TIM_OCPolarity_Low */

    uint16_t OCNPolarity;   /*  Specifies the complementary output polarity.
                                -TIM_OCNPolarity_High
                                -TIM_OCNPolarity_Low
                                @note This parameter is valid only for TIM1 and TIM8. */

    uint16_t OCIdleState;   /*  Specifies the TIM Output Compare pin state during Idle state.
                                -TIM_OCIdleState_Set
                                -TIM_OCIdleState_Reset
                                @note This parameter is valid only for TIM1 and TIM8. */

    uint16_t OCNIdleState;  /*  Specifies the TIM Output Compare pin state during Idle state.
                                -TIM_OCNIdleState_Set
                                -TIM_OCNIdleState_Reset
                                @note This parameter is valid only for TIM1 and TIM8. */
}MA_TIM_OCInitStructure_t;

void MA_TIM_TimeBaseInit(MA_TIM_TimeBaseInitStructure_t* MA_TIM_TimeBase);
void MA_TIM_CompleteParameters(MA_TIM_TimeBaseInitStructure_t* MA_TIM_TimeBase);
uint16_t MA_TIM_CalcPrescaler(MA_TIM_APBx_t APBx, uint32_t DesiredClock);
MA_TIM_APBx_t MA_TIM_ObtainAPBx(TIM_TypeDef* TIMx);
void MA_TIM_OCInit(MA_TIM_OCInitStructure_t *MA_TIM_OCInit);
	
#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* MA_TIM_H */
