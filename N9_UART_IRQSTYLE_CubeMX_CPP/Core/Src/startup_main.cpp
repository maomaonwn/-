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
  HAL_UART_Receive_IT(&huart1,rx_buffer,1);/*�ú����Ὺ�������ж�:��־λUART_IT_RXNE���������ý��ջ��弰����������������*/
	

#if isRTOS==0    	//������������
	for(;;)  //��ͬ��while(true)
	{
//		
//    while ((USART1->SR & 0X40) == 0);     /* �ȴ���һ���ַ�������� */
//    USART1->DR = rx_buffer;             /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */
//		
//	
//    HAL_UART_Transmit(&huart1,rx_buffer,1,5000);
//		
//		
//		
//	while ((USART1->SR & 0X40) == 0);     /* ����Ƿ����ַ�����������о�����whileѭ�� */
//    rx_buffer = USART1->DR;             /* ��Ҫ���͵��ַ� ch д�뵽DR�Ĵ��� */	
//		
//	HAL_UART_Receive(&huart1,rx_buffer,1,5000);
	
	printf("%d\r\n",aaa);
	bsp_delay.f1.ms(1000);
	aaa++;
	}
#endif
}