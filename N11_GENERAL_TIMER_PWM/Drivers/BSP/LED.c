#include "LED.h"

void LED_Init(void){
    //使能时钟
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
    //定义并配置GPIO结构体
	GPIO_InitTypeDef GPIO_LED = {0};
	GPIO_LED.Pin = GPIO_PIN_13;
	GPIO_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_LED.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_LED.Pull = GPIO_NOPULL;

	
	//GPIO初始化
	HAL_GPIO_Init(GPIOC,&GPIO_LED);	
}

