#include "stm32f4xx.h"                  // Device header
#include "ma_delay.h"
#include "ma_servo.h"
#include "ma_gpio.h"

#define TIM12_FREQ 200000 
#define TIM12_PERIOD 4000 /* TIM_FREQ / TIM_Period = 50 Hz (Servo motor frequency) */



int main()
{
	MA_DELAY_Init();
	
	uint16_t prescaler_Tim12;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);

	MA_GPIO_t D12, D13, D14, D15;
	
	D12.Port	= GPIOD;
	D12.Pin		= GPIO_Pin_12;
	D12.Mode	= GPIO_Mode_OUT;
	D12.OType	= GPIO_OType_PP;
	D12.PuPd 	= GPIO_PuPd_NOPULL;
	D12.Speed 	= GPIO_Speed_100MHz;
	
	D15 = D14 = D13 = D12;
	
	D13.Pin	= GPIO_Pin_13;
	D14.Pin = GPIO_Pin_14;
	D15.Pin = GPIO_Pin_15;
	
	MA_GPIO_MultiInit(4, D12, D13, D14, D15);
	
	MA_GPIO_t B14;
	
	B14.Port	= GPIOB;
	B14.Pin		= GPIO_Pin_14;
	B14.Mode	= GPIO_Mode_AF;
	B14.OType	= GPIO_OType_PP;
	B14.PuPd 	= GPIO_PuPd_UP;
	B14.Speed 	= GPIO_Speed_100MHz;
	B14.AF		= GPIO_AF_TIM12;
	
	MA_GPIO_Init(B14);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	prescaler_Tim12 = (uint16_t)((SystemCoreClock/2)/TIM12_FREQ) - 1;
	TIM_DeInit(TIM12);
	TIM_TimeBaseStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseStructure.TIM_CounterMode	= TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period	= TIM12_PERIOD-1; 
	TIM_TimeBaseStructure.TIM_Prescaler	= prescaler_Tim12;
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode 		= TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity	= TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse 		= 200;
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM12, ENABLE);
	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM12, ENABLE);
	
	MA_PWM_Conf_t pwm1;
	MA_SERVO_t servo1;
	
	pwm1.TIM 	= TIM12;
	pwm1.Frequency 	= 50;
	pwm1.Period 	= 4000;
	pwm1.Prescaler 	= (uint16_t)((SystemCoreClock/2)/TIM12_FREQ) - 1;
	
	servo1.PWM 		= pwm1;
	servo1.PulseMin		= 100;
	servo1.PulseRange	= 350;
	

	for(int i=0; i<=180; i+=5)
	{
		SERVO_SetAngle(servo1, i);
		delay(500);
	}
	
	
	
}

void assert_failed(uint8_t* file, uint32_t line)
{
	while(1);
}
