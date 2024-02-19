/********************************************
 * @file      BTIM.c
 * @brief     ͨ�ö�ʱ�� ��������
 ********************************************/
 
 #include "./BSP/LED.h"
 #include "./BSP/GTIM.h"
 
 
 
 
 
 TIM_HandleTypeDef g_htim1;
 
 
 
 
 
/**
 * @brief       ͨ�ö�ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ͨ�ö�ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ͨ�ö�ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
 void gtim_timx_int_init(uint16_t arr,uint16_t psc)
 {
	 
	 
	 g_htim1.Instance = TIM3;                            
	 g_htim1.Init.Prescaler = psc; 
	 g_htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	 g_htim1.Init.Period = arr;
	 HAL_TIM_Base_Init(&g_htim1);
	 
	 /*ʹ�ܶ�ʱ��X�ж�*/
	 HAL_TIM_Base_Start_IT(&g_htim1);
 }
 
 
 
/**
 * @brief       ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
                �˺����ᱻHAL_TIM_Base_Init()��������
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0);   /* TIM3 ʱ��ʹ�� */    
        HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3); /* ��ռ1�������ȼ�3����2 */
        HAL_NVIC_EnableIRQ(TIM3_IRQn);         /* ����ITM3�ж� */
    }
}



/**
 * @brief       ��ʱ��TIMX�жϷ�����
 * @param       ��
 * @retval      ��
 */
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_htim1); /* ��ʱ���жϹ��������� */
}
/**
 * @brief       ��ʱ�������жϻص�����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
			do{ HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); }while(0);        /* ��תLED */
			HAL_Delay(500);
    }
}
