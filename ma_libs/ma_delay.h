/**
 * @author  Mustafa Altun
 * @website http://altunmustafa.com
 * @link    https://github.com/altunmustafa/stm32f4-bacis-projects
 * @version 0.1
 * @ide     Keil uVision
 * @license GNU GPL v3
 * @brief   Customized Delay Library for STM32F4xx devices
 */	
 
#ifndef MA_DELAY_H
#define MA_DELAY_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#include "stm32f4xx.h"

#define delay(time_ms) MA_DELAY_ms((time_ms))

void MA_DELAY_Init(void);
void MA_DELAY_ms(volatile uint32_t Time_ms);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* MA_DELAY_H */
