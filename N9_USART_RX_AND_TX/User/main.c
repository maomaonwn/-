#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/BSP_USART.h"

UART_HandleTypeDef UartHandle;          //�ٴζ���

void USART_SendString(uint8_t *str);





int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
	
	USART_Config();                     //USART��ʼ��������
	
	USART_SendString((uint8_t *)"Hello,World!");
}





void USART_SendString(uint8_t *str)
{
	unsigned int k = 0;
	do {
		HAL_UART_Transmit(&UartHandle,(uint8_t *)(str+k),1,1000);
		k++;
	}
	while (*(str+k)!='\0');
}



