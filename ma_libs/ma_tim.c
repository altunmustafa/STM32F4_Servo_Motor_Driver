#include "ma_tim.h"

void MA_TIM_TimeBaseInit(MA_TIM_TimeBaseInitStructure_t* MA_TIM_TimeBase)
{
    TIM_DeInit(MA_TIM_TimeBase->TIMx);

    MA_TIM_CompleteParameters(MA_TIM_TimeBase);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    TIM_TimeBaseStructure.TIM_ClockDivision = MA_TIM_TimeBase->ClockDivision;
    TIM_TimeBaseStructure.TIM_CounterMode   = MA_TIM_TimeBase->CounterMode;
    TIM_TimeBaseStructure.TIM_Period        = MA_TIM_TimeBase->Period;
    TIM_TimeBaseStructure.TIM_Prescaler	    = MA_TIM_TimeBase->Prescaler;

    TIM_TimeBaseInit(MA_TIM_TimeBase->TIMx, &TIM_TimeBaseStructure);
}

void MA_TIM_CompleteParameters(MA_TIM_TimeBaseInitStructure_t* MA_TIM_TimeBase)
{
    MA_TIM_TimeBase->APBx = MA_TIM_ObtainAPBx(MA_TIM_TimeBase->TIMx);   /* Set APBx */

    if( MA_TIM_TimeBase->TimerClock > 0 )
    {
        MA_TIM_TimeBase->Prescaler = MA_TIM_CalcPrescaler(MA_TIM_TimeBase->APBx, MA_TIM_TimeBase->TimerClock);     /* Set Prescaler by target Clock*/
    }

    if( MA_TIM_TimeBase->SignalClock > 0 )
    {
        MA_TIM_TimeBase->Period = (uint32_t) (MA_TIM_TimeBase->TimerClock / MA_TIM_TimeBase->SignalClock) - 1;    /* Set Period by target Signal_Clock*/ 
    }
}

/*
 * if APBx prescaler is 1, then TIMxCLK = PCLKx, otherwise TIMxCLK = 2x PCLKx
 * Default APB1 Prescaler is 4 (PCLK1 = 168/4 = 42 MHz) (TIMxCLK = 84 MHz)
 * Default APB2 Prescaler is 2 (PCLK2 = 168/2 = 84 MHz) (TIMxCLK = 168 MHz)
 */
uint16_t MA_TIM_CalcPrescaler(MA_TIM_APBx_t APBx, uint32_t DesiredClock)
{
    if (APBx == APB1) 	/* APB1 Clock = SystemCoreClock/4  => TIMxCLK = SystemCoreClock/2 */
        return (uint16_t) ((SystemCoreClock / 2) / DesiredClock) - 1;
    else if (APBx == APB2) 	/* APB2 Clock = SystemCoreClock/2 => TIMxCLK = SystemCoreClock */
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

void MA_TIM_OCInit(MA_TIM_OCInitStructure_t *MA_TIM_OCInit){
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode      = MA_TIM_OCInit->OCMode;
    TIM_OCInitStructure.TIM_OCPolarity  = MA_TIM_OCInit->OCPolarity;
    TIM_OCInitStructure.TIM_OutputState = MA_TIM_OCInit->OutputState;
    TIM_OCInitStructure.TIM_Pulse       = MA_TIM_OCInit->Pulse;
    
    switch(MA_TIM_OCInit->CHx){
        case CH1:
            TIM_OC1Init(MA_TIM_OCInit->TIMx, &TIM_OCInitStructure);
            break;
        case CH2:
            TIM_OC2Init(MA_TIM_OCInit->TIMx, &TIM_OCInitStructure);
            break;
        case CH3:
            TIM_OC3Init(MA_TIM_OCInit->TIMx, &TIM_OCInitStructure);
            break;
        case CH4:
            TIM_OC4Init(MA_TIM_OCInit->TIMx, &TIM_OCInitStructure);
            break;
        default:
            assert_param(0);
    }
    
}
