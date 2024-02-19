#include "./BSP/GTIM.h"
#include "./BSP/LED.h"


TIM_HandleTypeDef g_htim1;


/**
 * @brief       通用定时器TIMX 定时器、定时中断初始化函数 和 定时器底层驱动函数
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为36M, 所以定时器时钟 = 72Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0);                                /* 使能TIMx时钟 */

    g_htim1.Instance = TIM3;                              /* 通用定时器x */
    g_htim1.Init.Prescaler = psc;                         /* 预分频系数 */
    g_htim1.Init.CounterMode = TIM_COUNTERMODE_UP;        /* 递增计数模式 */
    g_htim1.Init.Period = arr;                            /* 自动装载值 */
    HAL_TIM_Base_Init(&g_htim1);

    HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3);                /* 设置中断优先级，抢占优先级1，子优先级3 */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);                        /* 开启ITMx中断 */

    HAL_TIM_Base_Start_IT(&g_htim1);                      /* 使能定时器x和定时器x更新中断 */
}



/**
 * @brief       定时器TIMX中断服务函数
 * @param       无
 * @retval      无
 */
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_htim1); /* 定时器中断公共处理函数 */
}



/***********************************以下是通用定时器PWM输出实验程序**********************************************/
TIM_HandleTypeDef g_htim1_pwm;         //定时器句柄


/**
 * @brief       通用定时器TIMX 通道Y PWM输出 初始化函数（使用PWM模式1）
 * @note
 *              通用定时器的时钟来自APB1,当PPRE1 ≥ 2分频的时候
 *              通用定时器的时钟为APB1时钟的2倍, 而APB1为36M, 所以定时器时钟 = 72Mhz
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值。
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwm_chy  = {0};                /* 定时器PWM输出配置 */

    g_htim1_pwm.Instance = TIM3;                              /* 定时器x */
    g_htim1_pwm.Init.Prescaler = psc;                         /* 定时器分频 */
    g_htim1_pwm.Init.CounterMode = TIM_COUNTERMODE_UP;        /* 递增计数模式 */
    g_htim1_pwm.Init.Period = arr;                            /* 自动重装载值 */
    HAL_TIM_PWM_Init(&g_htim1_pwm);                           /* 初始化PWM */

    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                           /* 模式选择PWM1 */
    timx_oc_pwm_chy.Pulse = arr / 2;                                    /* 设置比较值,此值用来确定占空比 */
                                                                        /* 默认比较值为自动重装载值的一半,即占空比为50% */
    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;                    /* 输出比较极性为低 */
    HAL_TIM_PWM_ConfigChannel(&g_htim1_pwm, &timx_oc_pwm_chy, TIM_CHANNEL_2 ); /* 配置TIMx通道y */
    HAL_TIM_PWM_Start(&g_htim1_pwm, TIM_CHANNEL_2);       /* 开启对应PWM通道 */
}
/**
 * @brief       定时器底层驱动，时钟使能，引脚配置
                此函数会被HAL_TIM_PWM_Init()调用
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		GPIO_InitTypeDef gpio_init_struct;
		do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0);   /* PB口时钟使能 */
        do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0);  /* TIM3 时钟使能 */

		gpio_init_struct.Pin = GPIO_PIN_5;             //通道y的GPIO口
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;       //复用推挽输出
		gpio_init_struct.Pull = GPIO_PULLUP;           //上拉
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; //高速
		HAL_GPIO_Init(GPIOB, &gpio_init_struct);
	}
}	
