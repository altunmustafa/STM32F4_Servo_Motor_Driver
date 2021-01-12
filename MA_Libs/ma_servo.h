#ifndef MA_SERVO_H
#define MA_SERVO_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */
	
#include "stm32f4xx.h"
#include "ma_pwm.h"

typedef struct{
	MA_PWM_Conf_t PWM;		/*!< PWM settings */
	uint32_t PulseMin;
	uint32_t PulseRange;
}MA_SERVO_t;

int SERVO_SetAngle(MA_SERVO_t Servo, uint16_t Angle);


#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* MA_SERVO_H */