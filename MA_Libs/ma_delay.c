#include "ma_delay.h"

volatile uint32_t delay_time;

void MA_DELAY_Init(void)
{
	/* Set SysTick interrupt every 1ms */
	if (SysTick_Config(SystemCoreClock / 1000)) 
	{
		/* Capture error */
		while (1);
	}
}

void SysTick_Handler(void)
{
	if(delay_time !=0)
	{
		delay_time --;
	}
}  


//time: ms cinsinden
void MA_DELAY_ms(volatile uint32_t time_ms)
{
	delay_time = time_ms;
	while(delay_time!=0);
}
