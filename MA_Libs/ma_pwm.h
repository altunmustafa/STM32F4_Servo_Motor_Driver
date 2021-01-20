#ifndef MA_PWM_H
#define MA_PWM_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	
#include "stm32f4xx.h"

typedef struct{
	TIM_TypeDef* TIM;			/*!< Pointer to timer used */
	uint32_t Channel;
	uint32_t Frequency;		/*!< PWM frequency used */
	uint16_t Prescaler;		/*!< Prescaler used for PWM frequency */
	uint32_t Period;			/*!< Period used, set on initialization for PWM */
}MA_PWM_Conf_t;


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* MA_PWM_H */
