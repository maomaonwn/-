/********************************************
 * @file      BTIM.c
 * @brief     通用定时器 驱动代码
 ********************************************/
 
 #include "./BSP/LED.h"
 #include "./BSP/GTIM.h"
 
 
 
 
 
 TIM_HandleTypeDef g_htim1;
 
 
 
 
 
/**
 * @brief       通用定时器TIMX定时中断初始化函数
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
 void gtim_timx_int_init(uint16_t arr,uint16_t psc)
 {
	 
	 
	 g_htim1.Instance = TIM3;                            
	 g_htim1.Init.Prescaler = psc; 
	 g_htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	 g_htim1.Init.Period = arr;
	 HAL_TIM_Base_Init(&g_htim1);
	 
	 /*使能定时器X中断*/
	 HAL_TIM_Base_Start_IT(&g_htim1);
 }
 
 
 
/**
 * @brief       定时器底层驱动，开启时钟，设置中断优先级
                此函数会被HAL_TIM_Base_Init()函数调用
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0);   /* TIM3 时钟使能 */    
        HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3); /* 抢占1，子优先级3，组2 */
        HAL_NVIC_EnableIRQ(TIM3_IRQn);         /* 开启ITM3中断 */
    }
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
/**
 * @brief       定时器更新中断回调函数
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
			do{ HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); }while(0);        /* 翻转LED */
			HAL_Delay(500);
    }
}
