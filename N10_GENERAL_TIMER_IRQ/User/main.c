#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "./BSP/GTIM.h"

/**
 * @brief TIM3通用定时器下的定时器中断：在中断中使PC13跑马灯
 */


int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config();               /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
	
	LED_INIT();
	
	gtim_timx_int_init(5000-1,7200-1);  //10Khz的计数频率，计数5K次为500ms
	
	
	while(1){
	}
}






