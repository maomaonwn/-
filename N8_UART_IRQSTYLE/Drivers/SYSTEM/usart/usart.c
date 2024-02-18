#include "usart.h"
#include "./BSP/LED.h"

UART_HandleTypeDef uart1;

uint8_t rx_buffer[1];



/**
 * @brief        UART串口初始化函数
 * @note         注意：必须设置正确的时钟源，否则串口波特率就会设置异常
 */
void uart_init(void)
{
	uart1.Instance      = USART1;                  //等于基地址对应的宏
	uart1.Init.BaudRate = 115200;
	uart1.Init.WordLength = UART_WORDLENGTH_8B;    //字长为8位数据位
	uart1.Init.StopBits = UART_STOPBITS_1;         //一个停止位
	uart1.Init.Parity = UART_PARITY_NONE;          //无奇偶校验位
	uart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;    //无硬件流控制
	uart1.Init.Mode = UART_MODE_TX_RX;             //收发模式
	HAL_UART_Init(&uart1);
	
    /*该函数会开启接收中断:标志位UART_IT_RXNE，并且设置接收缓冲及缓冲接收最大数据量*/	
	HAL_UART_Receive_IT(&uart1,rx_buffer,1);
}



/**
 * @brief       UART底层初始化函数
 * @param       huart: UART句柄类型指针
 * @note        此函数会被HAL_UART_Init()调用
 *              完成时钟使能，引脚配置，中断配置
 * @retval      无
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (huart->Instance == USART1)                            /* 如果是串口1，进行串口1 MSP初始化 */
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();                             /* 使能串口TX_RX脚时钟 */
        __HAL_RCC_USART1_CLK_ENABLE();                                  /* 使能串口时钟 */

        gpio_init_struct.Pin = GPIO_PIN_9;               /* 串口TX引脚号 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
        gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* IO速度设置为高速 */
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);
                
        gpio_init_struct.Pin = GPIO_PIN_10;               /* 串口RX脚 模式设置 */
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;    
        HAL_GPIO_Init(GPIOA, &gpio_init_struct);   /* 串口RX脚 必须设置成输入模式 */
        
        HAL_NVIC_EnableIRQ(USART1_IRQn);                      /* 使能USART1中断通道 */
        HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);              /* 组2，最低优先级:抢占优先级3，子优先级3 */
    }
}



void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&uart1);
	
	/*HAL库的串口公共服务函数是个特例，它执行完后会把串口中断关闭。所以这里需要再次开启*/
	HAL_UART_Receive_IT(&uart1,rx_buffer,1);
}
/**
 * @brief      串口数据接收回调函数，数据处理在这里进行。
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		//电脑发1，开灯
		//电脑发0，关灯
		if(*rx_buffer == 49)  //‘1’
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
		}
        if(*rx_buffer == 48)  //‘0’
        {
            HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
		}
	}
}	

