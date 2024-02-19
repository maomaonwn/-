#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED.h"
#include "./BSP/GTIM.h"

/**
 * @brief TIM3ͨ�ö�ʱ���µĶ�ʱ���жϣ����ж���ʹPC13�����
 */


int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    SystemClock_Config();               /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
	
	LED_INIT();
	
	gtim_timx_int_init(5000-1,7200-1);  //10Khz�ļ���Ƶ�ʣ�����5K��Ϊ500ms
	
	
	while(1){
	}
}






