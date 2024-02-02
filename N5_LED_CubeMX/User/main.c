#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"



int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    SystemClock_Config();               /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
	
	LED_INIT();
	
	while(1){
	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
	  HAL_Delay(700);
	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
	  HAL_Delay(700);
	}
}






