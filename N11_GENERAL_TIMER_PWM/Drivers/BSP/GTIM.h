#ifndef  __GTIM_H_
#define  __GTIM_H_

#include "./SYSTEM/sys/sys.h"

void gtim_timx_int_init(uint16_t arr, uint16_t psc);        /* ͨ�ö�ʱ�� ��ʱ������ʱ�жϳ�ʼ�����ײ����ú��� */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc);    /* ͨ�ö�ʱ�� PWM��ʼ������ */

extern TIM_HandleTypeDef g_htim1_pwm; 

#endif
