#include "./BSP/TRACK.h"
#include "./SYSTEM/delay/delay.h"

void Track_init(void)
{
		GPIO_InitTypeDef gpio_init_struct={0};
		__HAL_RCC_GPIOC_CLK_ENABLE();
		
		gpio_init_struct.Pin = GPIO_PIN_13;
		gpio_init_struct.Mode = GPIO_MODE_INPUT;
		gpio_init_struct.Pull = GPIO_PULLUP;
		
		HAL_GPIO_Init(GPIOC,&gpio_init_struct);
}




uint8_t Track_scan(void){	
	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==0){
		delay_ms(10);
		
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==0){	
			return 1;
		}
	}
	return 0;
}