#include "drv_can.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

void CAN_Init(void)
{

    CAN_FilterTypeDef can_filter_db;
    can_filter_db.FilterActivation = ENABLE;
    can_filter_db.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_db.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_db.FilterIdHigh = 0x0000;
    can_filter_db.FilterIdLow = 0x0000;
    can_filter_db.FilterMaskIdHigh = 0x0000;
	
    can_filter_db.FilterMaskIdLow = 0x0000;
    can_filter_db.FilterBank = 0;
    can_filter_db.FilterFIFOAssignment = CAN_RX_FIFO0;
	
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_db);//初始化 CAN1 过滤器
    HAL_CAN_Start(&hcan1);//启动 CAN1
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);//激活CAN1 FIFO0 接收


    can_filter_db.SlaveStartFilterBank = 14;
    can_filter_db.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_db);////初始化 CAN2 过滤器
    HAL_CAN_Start(&hcan2);//启动 CAN2
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);//激活CAN2 FIFO0 接收

}

