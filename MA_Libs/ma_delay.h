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
