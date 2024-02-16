#include "BSP_USART.h"


#define DEBUG_USART_BAUDRATE 115200

//引脚定义
 /************************************************************/
#define DEBUG_USART                             USART1
#define DEBUG_USART_CLK_ENABLE()                __USART1_CLK_ENABLE()
 
#define RCC_PERIPHCLK_UARTx                     RCC_PERIPHCLK_USART1
#define RCC_UARTxCLKSOURCE_SYSCLK               RCC_USART1CLKSOURCE_SYSCLK

#define DEBUG_USART_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_RX_GPIO_CLK_ENABLE()        __GPIOA_CLK_ENABLE()
#define DEBUG_USART_RX_PIN                      GPIO_PIN_10
#define DEBUG_USART_RX_AF                       GPIO_AF7_USART1

#define DEBUG_USART_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_TX_GPIO_CLK_ENABLE()        __GPIOA_CLK_ENABLE()
#define DEBUG_USART_TX_PIN                      GPIO_PIN_9
#define DEBUG_USART_TX_AF                       GPIO_AF7_USART1

#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
#define DEBUG_USART_IRQ                         USART1_IRQn
 /************************************************************/
 
 
 
 void USART_Config(void)
 {
	 UART_HandleTypeDef UartHandle;
	
	 UartHandle.Instance        = DEBUG_USART;           //USART1句柄
	 UartHandle.Init.BaudRate   = DEBUG_USART_BAUDRATE;
	 UartHandle.Init.WordLength = UART_WORDLENGTH_8B;    //8位字长
	 UartHandle.Init.StopBits   = UART_PARITY_NONE;      //无奇偶校验
	 UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;   //无硬件流控
	 UartHandle.Init.Mode       = UART_MODE_TX_RX;       //收发模式
	 
	 HAL_UART_Init(&UartHandle);
	 
	 /*使能串口接收断*/
	 __HAL_UART_ENABLE_IT(&UartHandle,UART_IT_RXNE);
	 
 }
