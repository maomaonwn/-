#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "./BSP/GTIM.h"



int main(void)
{
	uint16_t ledpwmval = 0;
	uint8_t dir = 1;
	
    HAL_Init();                         /* ��ʼ��HAL�� */
    SystemClock_Config();               /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */

	LED_Init();                         //��ʼ��LED
	gtim_timx_pwm_chy_init(500-1,72-1); //1Mhz�ļ���Ƶ�ʣ�2Khz��PWM           

	
	
	while(1)
	{
		delay_ms(10);
		
		if(dir==1)
		{
			ledpwmval++;
		}
		else if(dir==0)
		{
			ledpwmval--;
		}
		
		/*ledpwmval����300�󣬷����Ϊ�ݼ���ledpwmval����0�󣬷����Ϊ����*/
		if(ledpwmval>300)
		{
			dir=0;
		}
		else if(ledpwmval==0)
		{
			dir=1;
		}
		
		/*�޸ıȽ�ֵ����ռ�ձ�*/
		__HAL_TIM_SET_COMPARE(&g_htim1_pwm,TIM_CHANNEL_2,ledpwmval); 
    }
}
