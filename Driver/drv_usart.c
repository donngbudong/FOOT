#include "drv_usart.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;

extern DMA_HandleTypeDef hdma_usart2_rx;

 uint8_t sbus_rx_buf[2][SBUS_RX_BUF_NUM];

void RC_Init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{
	//使能DMA串口接收
	SET_BIT(huart2.Instance->CR3, USART_CR3_DMAR);
	//使能空闲中断
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
   //失效DMA
	__HAL_DMA_DISABLE(&hdma_usart2_rx);
	while(hdma_usart2_rx.Instance->CR & DMA_SxCR_EN)
	{
			__HAL_DMA_DISABLE(&hdma_usart2_rx);
	}

	hdma_usart2_rx.Instance->PAR = (uint32_t) & (USART2->DR);
    //内存缓冲区1
	hdma_usart2_rx.Instance->M0AR = (uint32_t)(rx1_buf);
    //内存缓冲区2
	hdma_usart2_rx.Instance->M1AR = (uint32_t)(rx2_buf);
	
    //数据长度
	hdma_usart2_rx.Instance->NDTR = dma_buf_num;
    //使能双缓冲区
	SET_BIT(hdma_usart2_rx.Instance->CR, DMA_SxCR_DBM);

    //使能DMA
	__HAL_DMA_ENABLE(&hdma_usart2_rx);
		
}


void USART_Init(void)
{
	RC_Init(sbus_rx_buf[0], sbus_rx_buf[1], SBUS_RX_BUF_NUM);//usart2
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//裁判系统
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);//遥控器
	__HAL_UART_ENABLE_IT(&huart4,UART_IT_IDLE);//视觉
	__HAL_UART_ENABLE_IT(&huart5,UART_IT_RXNE);//陀螺仪
	__HAL_UART_ENABLE_IT(&huart6,UART_IT_RXNE);//vofa	
}