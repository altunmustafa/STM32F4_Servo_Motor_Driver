#include "ma_gpio.h"

/**
* @brief  Initializes the MA_GPIO.Port peripheral according to the specified parameters in the MA_GPIO.
* @param  MA_GPIO: MA_GPIO_t structure that contains the configuration information for the specified GPIO peripheral.
* @retval None
*/
void MA_GPIO_Init(MA_GPIO_t MA_GPIO){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin     = MA_GPIO.Pin;
    GPIO_InitStructure.GPIO_Mode    = MA_GPIO.Mode;
    GPIO_InitStructure.GPIO_OType   = MA_GPIO.OType;
    GPIO_InitStructure.GPIO_PuPd    = MA_GPIO.PuPd;
    GPIO_InitStructure.GPIO_Speed   = MA_GPIO.Speed;

    MA_RCC_EnableClock(MA_GPIO.Port);
    GPIO_Init(MA_GPIO.Port, &GPIO_InitStructure);

    if(MA_GPIO.Mode == GPIO_Mode_AF){
        GPIO_PinAFConfig(MA_GPIO.Port, MA_GPIO_GetPinSource(MA_GPIO.Pin), MA_GPIO.AF);
    }
}

/**
* @brief  Initializes the many peripheral according to the specified parameters in the many MA_GPIO.
* @param  CountPin: Number of pin configurations given to this function
* @param  ...: Many MA_GPIO_t structures that contains the configuration information for the specified GPIO peripheral.
* @retval None
*/
void MA_GPIO_MultiInit(uint8_t CountPin, ...){
    va_list Args;
    va_start(Args, CountPin);

    for(int i = 0 ; i < CountPin ; i++){
        MA_GPIO_Init(va_arg(Args, MA_GPIO_t));
    }
    va_end(Args);
}

void MA_GPIO_InitLed(MA_LED_t MA_LED){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin     = MA_LED.Pin;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;

    MA_RCC_EnableClock(MA_LED.Port);
    GPIO_Init(MA_LED.Port, &GPIO_InitStructure);
}

void MA_GPIO_InitOnBoardLeds(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;

    MA_RCC_EnableClock(GPIOD);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}


/**
 * @brief  Gets pin source from desired GPIO pin
 * @param  GPIO_Pin: GPIO pin for calculating port source
 * @retval Calculated pin source for GPIO pin
 */
uint16_t MA_GPIO_GetPinSource(uint16_t GPIO_Pin){
    uint16_t PinSource = 0;

    while (GPIO_Pin > 1){
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
uint16_t MA_GPIO_GetPortSource(GPIO_TypeDef* GPIOx) {
                       /* Offset from GPIOA / Difference range of GPIO addresses */
	return ((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE));
}
