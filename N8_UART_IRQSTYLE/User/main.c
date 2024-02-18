#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "usart.h"



int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config();               /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
	LED_INIT();  
	
	uart_init();
	
	
	
	while(1)
	{
		
	}
}






