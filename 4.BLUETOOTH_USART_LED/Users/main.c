#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/xunji/xunji.h"

void led_init(void);                       

int main(void)
{
    HAL_Init();                              
    sys_stm32_clock_init(RCC_PLL_MUL9);      
    delay_init(72);                          
    led_init();												  
    xunji_init();
	
    while(1)
    { 
			if(xunji_scan())
				{
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
				}
				else
				{	
						HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
				} 
    }
}