#include "ma_gpio.h"

/**
* @brief  Initializes the MA_GPIO.Port peripheral according to the specified parameters in the MA_GPIO.
* @param  MA_GPIO: MA_GPIO_t structure that contains the configuration information for the specified GPIO peripheral.
* @retval None
*/
void MA_GPIO_Init(MA_GPIO_t MA_GPIO) 
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin 	= MA_GPIO.Pin;
	GPIO_InitStructure.GPIO_Mode 	= MA_GPIO.Mode;
	GPIO_InitStructure.GPIO_OType 	= MA_GPIO.OType;
	GPIO_InitStructure.GPIO_PuPd 	= MA_GPIO.PuPd;
	GPIO_InitStructure.GPIO_Speed 	= MA_GPIO.Speed;
	
	GPIO_Init(MA_GPIO.Port, &GPIO_InitStructure);
	
	if(MA_GPIO.Mode == GPIO_Mode_AF)
	{
		GPIO_PinAFConfig(MA_GPIO.Port, MA_GPIO_GetPinSource(MA_GPIO.Pin), MA_GPIO.AF);
	}
}

/**
* @brief  Initializes the many peripheral according to the specified parameters in the many MA_GPIO.
* @param  CountPin: Number of pin configurations given to this function
* @param  ...: Many MA_GPIO_t structures that contains the configuration information for the specified GPIO peripheral.
* @retval None
*/
void MA_GPIO_MultiInit(uint8_t CountPin, ...)
{
	va_list Args;
	va_start(Args, CountPin);
	
	for(int i = 0 ; i < CountPin ; i++)
	{
		MA_GPIO_Init(va_arg(Args, MA_GPIO_t));
	}
	va_end(Args);
}

/**
 * @brief  Gets pin source from desired GPIO pin
 * @param  GPIO_Pin: GPIO pin for calculating port source
 * @retval Calculated pin source for GPIO pin
 */
uint16_t MA_GPIO_GetPinSource(uint16_t GPIO_Pin) 
{
	uint16_t PinSource = 0;
	
	while (GPIO_Pin > 1)
	{
		PinSource++;	/* Increase PinSource */
		GPIO_Pin >>= 1;	/* Shift right */
	}
	return PinSource; /* Return source */
}

/**
 * @brief  Gets port source from desired GPIOx PORT
 * @param  GPIOx: GPIO PORT for calculating port source
 * @retval Calculated port source for GPIO
 */
uint16_t MA_GPIO_GetPortSource(GPIO_TypeDef* GPIOx) 
{
	return	((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE));
		/* Offset from GPIOA	/	Difference between 2 GPIO addresses */
}
