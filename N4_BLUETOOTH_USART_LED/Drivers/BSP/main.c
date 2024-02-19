#include "main.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"

UART_HandleTypeDef huart1;

void Bluetooth(void) {
  HAL_Init();
  SystemClock_Config();
  USART1_UART_Init();

  while (1) {
    char rxData;

    // 阻塞式接收数据
    if (HAL_UART_Receive(&huart1, (uint8_t *)&rxData, 1, HAL_MAX_DELAY) == HAL_OK) {
      switch (rxData) {
        case '1':
          // 点亮LED
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
          break;
        case '2':
          // 熄灭LED
          HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
          break;
        default:
          break;
      }
    }
  }
}

void USART1_UART_Init(void) {
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600; // 设置蓝牙模块波特率，根据实际情况修改
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&huart1) != HAL_OK) {
    Error_Handler();
  }
}

void Error_Handler(void) {
  while (1) {
    // 错误处理代码
  }
}
