#include "stm32f4xx.h"                  // Device header
#include "../ma_libs/ma_gpio.h"
#include "../ma_libs/ma_tim.h"
#include "../ma_libs/ma_delay.h"

void TIM7_IRQHandler(){
    if(TIM_GetITStatus(TIM7, TIM_IT_Update) == SET ){
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    }
}


int main(){
    
    #if 0
    MA_LED_t LED_Green   = {GPIOD, GPIO_Pin_12};
    MA_LED_t LED_Orange  = {GPIOD, GPIO_Pin_13};
    MA_LED_t LED_Red     = {GPIOD, GPIO_Pin_14};
    MA_LED_t LED_Blue    = {GPIOD, GPIO_Pin_15}; 
    #endif

    MA_DELAY_Init();
    
    /* Initialize On-Board LEDs (D12, D13, D14, D15) */
    MA_GPIO_InitOnBoardLeds();
    /*
    for(int i=0; i<10; i++){
        GPIO_ToggleBits(LED_Green.Port, LED_Green.Pin);
        MA_DELAY_ms(1000);
    }*/
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    
    MA_TIM_TimeBaseInitStructure_t MA_TIM_TimeBaseInitStructure;
    MA_TIM_TimeBaseInitStructure.APBx   = APB1;
    MA_TIM_TimeBaseInitStructure.TIMx   = TIM7;
    MA_TIM_TimeBaseInitStructure.TimerClock    = 2000; /* Hz */
    MA_TIM_TimeBaseInitStructure.SignalClock   = 8;    /* Hz */
    MA_TIM_TimeBaseInitStructure.ClockDivision  = 0;
    MA_TIM_TimeBaseInitStructure.CounterMode    = TIM_CounterMode_Up;
    MA_TIM_TimeBaseInit(&MA_TIM_TimeBaseInitStructure);
    
    MA_TIM_Enable(TIM7);
    
    TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);  
    
    NVIC_InitTypeDef NVIC_InitStructure;      
    NVIC_InitStructure.NVIC_IRQChannel                      = TIM7_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0x00;         //farkli türler arasi oncelik
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0x00;         //kendi turunun icindeki oncelik
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
    
    while(1);

    
}
