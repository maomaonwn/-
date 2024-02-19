#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "./BSP/GTIM.h"



int main(void)
{
	uint16_t ledpwmval = 0;
	uint8_t dir = 1;
	
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config();               /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */

	LED_Init();                         //初始化LED
	gtim_timx_pwm_chy_init(500-1,72-1); //1Mhz的计数频率，2Khz的PWM           

	
	
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
		
		/*ledpwmval到达300后，方向改为递减。ledpwmval到达0后，方向改为递增*/
		if(ledpwmval>300)
		{
			dir=0;
		}
		else if(ledpwmval==0)
		{
			dir=1;
		}
		
		/*修改比较值控制占空比*/
		__HAL_TIM_SET_COMPARE(&g_htim1_pwm,TIM_CHANNEL_2,ledpwmval); 
    }
}
