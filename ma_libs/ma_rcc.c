#include "ma_rcc.h"

void MA_RCC_EnableClock(GPIO_TypeDef* GPIOx) {
	/* Set bit according to the 1 << portsourcenumber */
	RCC->AHB1ENR |= (1 << MA_GPIO_GetPortSource(GPIOx));
}

void MA_RCC_DisableClock(GPIO_TypeDef* GPIOx) {
	/* Clear bit according to the 1 << portsourcenumber */
	RCC->AHB1ENR &= ~(1 << MA_GPIO_GetPortSource(GPIOx));
}
