#include "./BSP/GTIM.h"

TIM_HandleTypeDef g_timx_pwm_chy_handle;

/**
 *@brief     通用定时器PWM输出初始化函数
 *@note      无
 *@param     arr:自动重装值
 *@param     psc:时钟预分频数
 *@retval    无 
 */
void g_timx_pwm_chy_init(uint16_t arr,uint16_t psc)
{
	TIM_OC_InitTypeDef timx_oc_pwm_chy;
	
	g_timx_pwm_chy_handle.Instance = TIM3;
	g_timx_pwm_chy_handle.Init.Prescaler = psc;                      /*预分频系数*/
	g_timx_pwm_chy_handle.Init.Period = arr;                         /*自动装载值*/
	g_timx_pwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;     /*递增计数模式*/
	HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);                        /* 初始化PWM */
	
	timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                        /* 模式选择PWM1 */
	timx_oc_pwm_chy.Pulse = arr/2;                                   /* 设置比较值,此值用来确定占空比 */
	timx_oc_pwm_chy.OCNPolarity = TIM_OCPOLARITY_LOW;
	HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle,&timx_oc_pwm_chy,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle,TIM_CHANNEL_2);
}

/*定时器输出PWM MSP初始化函数,初始GPIO口*/
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		GPIO_InitTypeDef gpio_init_struct;
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_TIM3_CLK_ENABLE();
		
		gpio_init_struct.Pin = GPIO_PIN_5;
		gpio_init_struct.Mode = GPIO_MODE_AF_PP;
		gpio_init_struct.Pull = GPIO_PULLUP;
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOB,&gpio_init_struct);
		
		__HAL_RCC_AFIO_CLK_ENABLE();
		__HAL_AFIO_REMAP_TIM3_PARTIAL();
	}
}
