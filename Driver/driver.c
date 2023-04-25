#include "driver.h"

extern uint8_t sbus_rx_buf[2][SBUS_RX_BUF_NUM];

void Driver_Init(void)
{
	imu_data_decode_init();//Õ”¬›“«
	CAN_Init();//can≥ı ºªØ
	USART_Init();
}

