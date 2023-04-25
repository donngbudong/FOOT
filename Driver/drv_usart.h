#ifndef __DRV_UART_H
#define __DRV_UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"



#define SBUS_RX_BUF_NUM 36u
#define RC_FRAME_LENGTH 18u


void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num);
void USART_Init(void);


#endif
