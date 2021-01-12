#include "ma_servo.h"

int SERVO_SetAngle(MA_SERVO_t Servo, uint16_t Angle)
{
	Servo.PWM.TIM->CCR1 = (int) (Servo.PulseMin + (Servo.PulseRange * Angle/180));
	GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	return 1;
}