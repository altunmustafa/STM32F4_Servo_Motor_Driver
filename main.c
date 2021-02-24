#include "stm32f4xx.h"                  // Device header
#include "ma_delay.h"
#include "ma_servo.h"
#include "ma_gpio.h"
#include "ma_tim.h"

#define LED_G D12 	/* Green LED */
#define LED_O D13	/* Orange LED */
#define LED_R D14	/* Red LED */
#define LED_B D15	/* Blue LED */

#define TIM12_FREQ 200000 
#define TIM12_PERIOD 4000 /* TIM_FREQ / TIM_Period = 50 Hz (Servo motor frequency) */
#define SERVO_MOTOR_FREQ 50


int main()
{
    MA_DELAY_Init();

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);

    /* Initialize GPIO for LEDs */
    MA_GPIO_t D12, D13, D14, D15;
    D12.Port    = GPIOD;
    D12.Pin     = GPIO_Pin_12;
    D12.Mode    = GPIO_Mode_OUT;
    D12.OType   = GPIO_OType_PP;
    D12.PuPd    = GPIO_PuPd_NOPULL;
    D12.Speed   = GPIO_Speed_100MHz;
    
    D15 = D14 = D13 = D12;
    D13.Pin = GPIO_Pin_13;
    D14.Pin = GPIO_Pin_14;
    D15.Pin = GPIO_Pin_15;
    MA_GPIO_MultiInit(4, D12, D13, D14, D15);

    /* Initialize GPIO for PWM Pin */
    MA_GPIO_t B14;
    B14.Port    = GPIOB;
    B14.Pin     = GPIO_Pin_14;
    B14.Mode    = GPIO_Mode_AF;
    B14.OType   = GPIO_OType_PP;
    B14.PuPd    = GPIO_PuPd_UP;
    B14.Speed   = GPIO_Speed_100MHz;
    B14.AF      = GPIO_AF_TIM12;
    MA_GPIO_Init(B14);

    /* Initialize the TIMx for PWM Signal */
    MA_TIM_TimeBaseInitStructure_t MA_TIM_TimeBaseInitStructure;
    MA_TIM_TimeBaseInitStructure.TIMx           = TIM12;
    MA_TIM_TimeBaseInitStructure.ClockDivision  = 0;
    MA_TIM_TimeBaseInitStructure.CounterMode    = TIM_CounterMode_Up;
    MA_TIM_TimeBaseInitStructure.Clock          = TIM12_FREQ;
    MA_TIM_TimeBaseInitStructure.Signal_Clock   = SERVO_MOTOR_FREQ; 
    MA_TIM_TimeBaseInit(&MA_TIM_TimeBaseInitStructure);

    /* Initialize the Channelx of TIMx for PWM Signal*/ 
    MA_TIM_OCInitStructure_t MA_TIM_OCInitStructure;
    MA_TIM_OCInitStructure.TIMx         = TIM12;
    MA_TIM_OCInitStructure.CHx          = CH1;
    MA_TIM_OCInitStructure.OCMode       = TIM_OCMode_PWM1;
    MA_TIM_OCInitStructure.OCPolarity   = TIM_OCPolarity_High;
    MA_TIM_OCInitStructure.OutputState  = TIM_OutputState_Enable;
    //MA_TIM_OCInitStructure.Pulse        = 200;
    MA_TIM_OCInit(&MA_TIM_OCInitStructure);

    MA_TIM_Enable(TIM12);
    MA_TIM_OC1PreloadEnable(TIM12);
    MA_TIM_ARRPreloadEnable(TIM12);

    MA_SERVO_t servo1;

    servo1.TIMx         = TIM12;
    servo1.CHx          = CH1;
    servo1.PulseMin     = 100; /* pulse=100 => 0 degree for SG90, by trial and error method */
    servo1.PulseRange   = 350; /* pulse=450 => 180 degree for SG90, by trial and error method */
	
    for(int angle=0; angle<=-180; angle+=5)
    {
        SERVO_SetAngle(servo1, angle);
        delay(1000);
    }

}

void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}
