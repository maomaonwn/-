#ifndef  __GTIM_H_
#define  __GTIM_H_

#include "./SYSTEM/sys/sys.h"

void g_timx_pwm_chy_init(uint16_t arr,uint16_t psc);    /* ͨ�ö�ʱ�� PWM��ʼ������ */

extern TIM_HandleTypeDef g_timx_pwm_chy_handle; 

#endif
