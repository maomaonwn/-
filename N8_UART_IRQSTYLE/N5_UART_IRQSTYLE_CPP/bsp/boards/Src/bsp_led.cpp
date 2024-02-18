#include "bsp_led.h"




BSP_LED bsp_led;



/************************BSP_LED_INIT类书写**********************/
/**
 * @brief   类里GPIO配置兼初始化函数
 * @param   无
 * @retval  无
 */
void BSP_LED::GPIO_config_init(void)
{
	/*时钟使能*/
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
	/*配置GPIO结构体*/
	GPIO_InitTypeDef GPIO_LED = {0};
	GPIO_LED.Pin = GPIO_PIN_13;
	GPIO_LED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_LED.Speed = GPIO_SPEED_FREQ_LOW;
	
	/*GPIO初始化*/
	HAL_GPIO_Init(GPIOC,&GPIO_LED);
}
/************************BSP_LED_INIT类书写**********************/

