#include "LED.h"

void LED_Init(void){
    //ʹ��ʱ��
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
    //���岢����GPIO�ṹ��
	GPIO_InitTypeDef GPIO_LED = {0};
	GPIO_LED.Pin = GPIO_PIN_13;
	GPIO_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_LED.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_LED.Pull = GPIO_NOPULL;

	
	//GPIO��ʼ��
	HAL_GPIO_Init(GPIOC,&GPIO_LED);	
}

