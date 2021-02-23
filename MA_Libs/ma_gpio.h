#ifndef MA_GPIO_H
#define MA_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	
#include "stm32f4xx.h"
#include <stdarg.h>

typedef struct{
    GPIO_TypeDef*		Port; 	/* GPIOx */
    uint16_t		    Pin;	/* GPIO_Pin_x */
    GPIOMode_TypeDef 	Mode;	/* GPIO_Mode_IN - GPIO_Mode_OUT - GPIO_Mode_AF - GPIO_Mode_AN */
    GPIOOType_TypeDef	OType;	/* GPIO_OType_PP - GPIO_OType_OD */
    GPIOPuPd_TypeDef	PuPd;	/* GPIO_PuPd_NOPULL - GPIO_PuPd_UP - GPIO_PuPd_DOWN */
    GPIOSpeed_TypeDef	Speed;	/* GPIO_Speed_2MHz - GPIO_Speed_25MHz - GPIO_Speed_50MHz - GPIO_Speed_100MHz */
    uint8_t 		    AF;	    /* GPIO_AF_TIMx */
}MA_GPIO_t;

void MA_GPIO_Init(MA_GPIO_t MA_GPIO);
void MA_GPIO_MultiInit(uint8_t CountPin, ...);

uint16_t MA_GPIO_GetPinSource(uint16_t GPIO_Pin);
uint16_t MA_GPIO_GetPortSource(GPIO_TypeDef* GPIOx);


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* MA_GPIO_H */
