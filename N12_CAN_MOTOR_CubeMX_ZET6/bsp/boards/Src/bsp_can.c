#include "bsp_can.h"
#include "can.h"

extern CAN_HandleTypeDef hcan1;


/**
 *@brief  开启CAN滤波器，使能正常进入CAN_RX中断，从而接收数据
 *@param  无
 *@note   无
 */
void CAN1_Filter_Init(void)
{
	CAN_FilterTypeDef CAN_Filter_st;
	CAN_Filter_st.FilterActivation  = ENABLE;
	CAN_Filter_st.FilterMode    = CAN_FILTERMODE_IDMASK;
	CAN_Filter_st.FilterScale   = CAN_FILTERSCALE_32BIT;
	CAN_Filter_st.FilterIdHigh  = 0x0000;
	CAN_Filter_st.FilterIdLow   = 0x0000;
	CAN_Filter_st.FilterMaskIdHigh  = 0x0000;
	CAN_Filter_st.FilterMaskIdLow   = 0x0000;
	CAN_Filter_st.FilterBank = 0;
	CAN_Filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	
	HAL_CAN_ConfigFilter(&hcan1,&CAN_Filter_st);
}


/**
 *@brief  使能CAN通信和CAN通信中断
 *@param  can句柄
 *@note   无
 */
void CAN_Start(CAN_HandleTypeDef *hcan)
{
	if(HAL_CAN_Start(hcan)!=HAL_OK)
	{
		Error_Handler();
	}
	
	if(HAL_CAN_ActivateNotification(hcan,CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)
	{
		Error_Handler();
	}
}