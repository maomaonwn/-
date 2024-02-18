#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "usart.h"



int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    SystemClock_Config();               /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
	LED_INIT();  
	
	uart_init();
	
	
	
	while(1)
	{
		
	}
}






