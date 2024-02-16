#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/BSP_USART.h"

UART_HandleTypeDef UartHandle;          //再次定义

void USART_SendString(uint8_t *str);





int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */
	
	USART_Config();                     //USART初始化和配置
	
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



