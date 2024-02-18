#include "bsp_led.h"




BSP_LED bsp_led;



/************************BSP_LED_INIT����д**********************/
/**
 * @brief   ����GPIO���ü��ʼ������
 * @param   ��
 * @retval  ��
 */
void BSP_LED::GPIO_config_init(void)
{
	/*ʱ��ʹ��*/
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	/*����GPIO�ṹ��*/
	GPIO_InitTypeDef GPIO_LED = {0};
	GPIO_LED.Pin = GPIO_PIN_13;
	GPIO_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_LED.Speed = GPIO_SPEED_FREQ_LOW;
	
	/*GPIO��ʼ��*/
	HAL_GPIO_Init(GPIOC,&GPIO_LED);
}
/************************BSP_LED_INIT����д**********************/

