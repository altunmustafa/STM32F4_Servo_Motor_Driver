#include "ma_tim.h"

void MA_TIM_TimeBaseInit(MA_TIM_TimeBase_t* pTimeBase)
{
    TIM_DeInit(pTimeBase->TIMx);

    MA_TIM_CompleteParameters(pTimeBase);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_ClockDivision = pTimeBase->ClockDivision;
    TIM_TimeBaseStructure.TIM_CounterMode   = pTimeBase->CounterMode;
    TIM_TimeBaseStructure.TIM_Period        = pTimeBase->Period;
    TIM_TimeBaseStructure.TIM_Prescaler	    = pTimeBase->Prescaler;

    TIM_TimeBaseInit(pTimeBase->TIMx, &TIM_TimeBaseStructure);
}

void MA_TIM_CompleteParameters(MA_TIM_TimeBase_t* pTimeBase)
{
    pTimeBase->APBx = MA_TIM_ObtainAPBx(pTimeBase->TIMx);   /* Set APBx */

    if( pTimeBase->Clock > 0 )
    {
        pTimeBase->Prescaler = MA_TIM_CalcPrescaler(pTimeBase->APBx, pTimeBase->Clock);     /* Set Prescaler by target Clock*/
    }

    if( pTimeBase->Signal_Clock > 0 )
    {
        pTimeBase->Period = (uint32_t) (pTimeBase->Clock / pTimeBase->Signal_Clock) - 1;    /* Set Period by target Signal_Clock*/ 
    }
}

/*
 * if APBx prescaler is 1, then TIMxCLK = PCLKx, otherwise TIMxCLK = 2x PCLKx
 * Default APB1 Prescaler is 4 (PCLK1 = 168/4 = 42 MHz) (TIMxCLK = 84 MHz)
 * Default APB2 Prescaler is 2 (PCLK2 = 168/2 = 84 MHz) (TIMxCLK = 168 MHz)
 */
uint16_t MA_TIM_CalcPrescaler(MA_TIM_APBx_t APBx, uint32_t DesiredClock)
{
    if (APBx == APB1) 	/* APB1 Clock = SystemCoreClock/4 */
        return (uint16_t) ((SystemCoreClock / 2) / DesiredClock) - 1;
    else if (APBx == APB2) 	/* APB2 Clock = SystemCoreClock/2 */
        return (uint16_t) ((SystemCoreClock) / DesiredClock) - 1;

    return 0;
}

MA_TIM_APBx_t MA_TIM_ObtainAPBx(TIM_TypeDef* TIMx)
{
    if((TIMx == TIM2) || (TIMx == TIM3) || (TIMx == TIM4) || (TIMx == TIM5) || (TIMx == TIM6) || (TIMx == TIM7) || (TIMx == TIM12) || (TIMx == TIM13) || (TIMx == TIM14))
    {
        return APB1;
    }
    else if((TIMx == TIM1) || (TIMx == TIM8) || (TIMx == TIM9) || (TIMx == TIM10) || (TIMx == TIM11))
    {
        return APB2;
    }
    return APB_ERR;
}

