/**
 * @author  Mustafa Altun
 * @website http://altunmustafa.com
 * @link    https://github.com/altunmustafa/stm32f4-bacis-projects
 * @version 0.1
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   Customized Reset and Clock Control (RCC) Library for STM32F4xx devices
 */	
 
#ifndef MA_RCC_H
#define MA_RCC_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	
#include "stm32f4xx.h"
#include "ma_gpio.h"

void MA_RCC_EnableClock(GPIO_TypeDef* GPIOx);
void MA_RCC_DisableClock(GPIO_TypeDef* GPIOx);


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* MA_RCC_H */
