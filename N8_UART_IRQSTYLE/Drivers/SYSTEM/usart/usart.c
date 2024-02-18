#include "usart.h"
#include "./BSP/LED.h"

UART_HandleTypeDef uart1;

uint8_t rx_buffer[1];



/**
 * @brief        UART���ڳ�ʼ������
 * @note         ע�⣺����������ȷ��ʱ��Դ�����򴮿ڲ����ʾͻ������쳣
 */
void uart_init(void)
{
	uart1.Instance      = USART1;                  //���ڻ���ַ��Ӧ�ĺ�
	uart1.Init.BaudRate = 115200;
	uart1.Init.WordLength = UART_WORDLENGTH_8B;    //�ֳ�Ϊ8λ����λ
	uart1.Init.StopBits = UART_STOPBITS_1;         //һ��ֹͣλ
	uart1.Init.Parity = UART_PARITY_NONE;          //����żУ��λ
	uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;    //��Ӳ��������
	uart1.Init.Mode = UART_MODE_TX_RX;             //�շ�ģʽ
	HAL_UART_Init(&uart1);
	
    /*�ú����Ὺ�������ж�:��־λUART_IT_RXNE���������ý��ջ��弰����������������*/	
	HAL_UART_Receive_IT(&uart1,rx_buffer,1);
}



/**
 * @brief       UART�ײ��ʼ������
 * @param       huart: UART�������ָ��
 * @note        �˺����ᱻHAL_UART_Init()����
 *              ���ʱ��ʹ�ܣ��������ã��ж�����
 * @retval      ��
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (huart->Instance == USART1)                            /* ����Ǵ���1�����д���1 MSP��ʼ�� */
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();                             /* ʹ�ܴ���TX_RX��ʱ�� */
        __HAL_RCC_USART1_CLK_ENABLE();                                  /* ʹ�ܴ���ʱ�� */

        gpio_init_struct.Pin = GPIO_PIN_9;               /* ����TX���ź� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* IO�ٶ�����Ϊ���� */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
                
        gpio_init_struct.Pin = GPIO_PIN_10;               /* ����RX�� ģʽ���� */
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;    
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);   /* ����RX�� �������ó�����ģʽ */
        
        HAL_NVIC_EnableIRQ(USART1_IRQn);                      /* ʹ��USART1�ж�ͨ�� */
        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);              /* ��2��������ȼ�:��ռ���ȼ�3�������ȼ�3 */
    }
}



void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&uart1);
	
	/*HAL��Ĵ��ڹ����������Ǹ���������ִ������Ѵ����жϹرա�����������Ҫ�ٴο���*/
	HAL_UART_Receive_IT(&uart1,rx_buffer,1);
}
/**
 * @brief      �������ݽ��ջص����������ݴ�����������С�
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		//���Է�1������
		//���Է�0���ص�
		if(*rx_buffer == 49)  //��1��
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		}
        if(*rx_buffer == 48)  //��0��
        {
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		}
	}
}	

