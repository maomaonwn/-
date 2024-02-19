#include "./BSP/GTIM.h"
#include "./BSP/LED.h"


TIM_HandleTypeDef g_htim1;


/**
 * @brief       ͨ�ö�ʱ��TIMX ��ʱ������ʱ�жϳ�ʼ������ �� ��ʱ���ײ���������
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
void gtim_timx_int_init(uint16_t arr, uint16_t psc)
{
    do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0);                                /* ʹ��TIMxʱ�� */

    g_htim1.Instance = TIM3;                              /* ͨ�ö�ʱ��x */
    g_htim1.Init.Prescaler = psc;                         /* Ԥ��Ƶϵ�� */
    g_htim1.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_htim1.Init.Period = arr;                            /* �Զ�װ��ֵ */
    HAL_TIM_Base_Init(&g_htim1);

    HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3);                /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);                        /* ����ITMx�ж� */

    HAL_TIM_Base_Start_IT(&g_htim1);                      /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
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



/***********************************������ͨ�ö�ʱ��PWM���ʵ�����**********************************************/
TIM_HandleTypeDef g_htim1_pwm;         //��ʱ�����


/**
 * @brief       ͨ�ö�ʱ��TIMX ͨ��Y PWM��� ��ʼ��������ʹ��PWMģʽ1��
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
void gtim_timx_pwm_chy_init(uint16_t arr, uint16_t psc)
{
    TIM_OC_InitTypeDef timx_oc_pwm_chy  = {0};                /* ��ʱ��PWM������� */

    g_htim1_pwm.Instance = TIM3;                              /* ��ʱ��x */
    g_htim1_pwm.Init.Prescaler = psc;                         /* ��ʱ����Ƶ */
    g_htim1_pwm.Init.CounterMode = TIM_COUNTERMODE_UP;        /* ��������ģʽ */
    g_htim1_pwm.Init.Period = arr;                            /* �Զ���װ��ֵ */
    HAL_TIM_PWM_Init(&g_htim1_pwm);                           /* ��ʼ��PWM */

    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;                           /* ģʽѡ��PWM1 */
    timx_oc_pwm_chy.Pulse = arr / 2;                                    /* ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձ� */
                                                                        /* Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50% */
    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_LOW;                    /* ����Ƚϼ���Ϊ�� */
    HAL_TIM_PWM_ConfigChannel(&g_htim1_pwm, &timx_oc_pwm_chy, TIM_CHANNEL_2 ); /* ����TIMxͨ��y */
    HAL_TIM_PWM_Start(&g_htim1_pwm, TIM_CHANNEL_2);       /* ������ӦPWMͨ�� */
}
/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
                �˺����ᱻHAL_TIM_PWM_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3)
	{
		GPIO_InitTypeDef gpio_init_struct;
		do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0);   /* PB��ʱ��ʹ�� */
        do{ __HAL_RCC_TIM3_CLK_ENABLE(); }while(0);  /* TIM3 ʱ��ʹ�� */

		gpio_init_struct.Pin = GPIO_PIN_5;             //ͨ��y��GPIO��
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;       //�����������
		gpio_init_struct.Pull = GPIO_PULLUP;           //����
		gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; //����
		HAL_GPIO_Init(GPIOB, &gpio_init_struct);
	}
}	
