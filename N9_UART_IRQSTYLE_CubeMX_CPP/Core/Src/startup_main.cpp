#include "startup_main.h"
#include "bsp_led.h"
#include "usart.h"
#include "bsp_delay.h"
#include <stdio.h>

extern uint8_t rx_buffer[1];
int aaa = 50;

void startup_main(void)
{
  bsp_delay.f1.Init(72);
  bsp_led.GPIO_config_init();
  HAL_UART_Receive_IT(&huart1,rx_buffer,1);/*该函数会开启接收中断:标志位UART_IT_RXNE，并且设置接收缓冲及缓冲接收最大数据量*/
	

#if isRTOS==0    	//如果是裸机开发
	for(;;)  //等同于while(true)
	{
//		
//    while ((USART1->SR & 0X40) == 0);     /* 等待上一个字符发送完成 */
//    USART1->DR = rx_buffer;             /* 将要发送的字符 ch 写入到DR寄存器 */
//		
//	
//    HAL_UART_Transmit(&huart1,rx_buffer,1,5000);
//		
//		
//		
//	while ((USART1->SR & 0X40) == 0);     /* 检测是否有字符过来，如果有就跳出while循环 */
//    rx_buffer = USART1->DR;             /* 将要发送的字符 ch 写入到DR寄存器 */	
//		
//	HAL_UART_Receive(&huart1,rx_buffer,1,5000);
	
	printf("%d\r\n",aaa);
	bsp_delay.f1.ms(1000);
	aaa++;
	}
#endif
}