#ifndef __BSP_LED_H_
#define __BSP_LED_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "startup_main.h"
	
	
	
	
	
class BSP_LED
{
	public:
		void GPIO_config_init(void);
};

extern BSP_LED bsp_led;





#ifdef __cplusplus
}
#endif

#endif
