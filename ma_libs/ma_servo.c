#include "ma_servo.h"

int SERVO_SetAngle(MA_SERVO_t Servo, uint16_t Angle)
{
    uint32_t pulse = (uint32_t) (Servo.PulseMin + (Servo.PulseRange * Angle/180));
    
    switch(Servo.CHx){
        case CH1:
            Servo.TIMx->CCR1 = pulse;
            break;
        case CH2:
            Servo.TIMx->CCR2 = pulse;
            break;
        case CH3:
            Servo.TIMx->CCR3 = pulse;
            break;
        case CH4:
            Servo.TIMx->CCR4 = pulse;
            break;
        default:
            return 0;
    }
    
    return 1;
}
