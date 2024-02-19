#ifndef  __GTIM_H_
#define  __GTIM_H_

#include "./SYSTEM/sys/sys.h"

void gtim_timx_int_init(uint16_t arr, uint16_t psc);        /* 通用定时器 定时器、定时中断初始化及底层配置函数 */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);    /* 通用定时器 PWM初始化函数 */

extern TIM_HandleTypeDef g_htim1_pwm; 

#endif
