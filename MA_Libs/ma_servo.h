/**
 * @author  Mustafa Altun
 * @website http://altunmustafa.com
 * @link    https://github.com/altunmustafa/stm32f4-bacis-projects
 * @version 0.1
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   Customized Servo Motor Library for STM32F4xx devices
 */	
 
#ifndef MA_SERVO_H
#define MA_SERVO_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	
#include "stm32f4xx.h"
#include "ma_tim.h"

typedef struct{
    TIM_TypeDef*    TIMx;       /*  -TIM1...TIM14 */
    MA_TIM_CHx_t    CHx;        /*  -CH1...CH4 */
    uint32_t        PulseMin;
    uint32_t        PulseRange;
}MA_SERVO_t;

int SERVO_SetAngle(MA_SERVO_t Servo, uint16_t Angle);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* MA_SERVO_H */
