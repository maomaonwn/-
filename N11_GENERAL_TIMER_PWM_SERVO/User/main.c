#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "./BSP/GTIM.h"


int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    SystemClock_Config();               /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */

	g_timx_pwm_chy_init(2000-1,720-1); //20ms�ı�׼PWM�ź�����         

	
	
	while(1)
	{
		/*�޸ıȽ�ֵ����ռ�ձ�*/
		__HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_2,50);
		delay_ms(100);
		
        __HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_2,150);	
		delay_ms(100);		
    }
}

