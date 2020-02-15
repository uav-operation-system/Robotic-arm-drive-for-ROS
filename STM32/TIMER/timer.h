#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
void TIM2_3_PWM_Init(u16 arr, u16 psc);
void Rds_Control(int ang,int serial_num);
#define CH1_PWM_VAL TIM2->CCR1
#define CH2_PWM_VAL TIM2->CCR2
#define CH3_PWM_VAL TIM2->CCR3
#define CH4_PWM_VAL TIM2->CCR4
#define CH5_PWM_VAL TIM3->CCR1
#define CH6_PWM_VAL TIM3->CCR2
#endif
