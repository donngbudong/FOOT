#ifndef __DRIVER_H
#define __DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stdbool.h"


#include "drv_can.h"
#include "drv_usart.h"
#include "imu_data_decode.h"



void Driver_Init(void);

#endif
