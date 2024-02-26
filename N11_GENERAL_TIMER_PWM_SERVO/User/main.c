#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "./BSP/GTIM.h"


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config();               /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */

	g_timx_pwm_chy_init(2000-1,720-1); //20ms的标准PWM信号周期         

	
	
	while(1)
	{
		/*修改比较值控制占空比*/
		__HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_2,50);
		delay_ms(100);
		
        __HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle,TIM_CHANNEL_2,150);	
		delay_ms(100);		
    }
}

