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
	//ʹ��DMA���ڽ���
	SET_BIT(huart2.Instance->CR3, USART_CR3_DMAR);
	//ʹ�ܿ����ж�
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
   //ʧЧDMA
	__HAL_DMA_DISABLE(&hdma_usart2_rx);
	while(hdma_usart2_rx.Instance->CR & DMA_SxCR_EN)
	{
			__HAL_DMA_DISABLE(&hdma_usart2_rx);
	}

	hdma_usart2_rx.Instance->PAR = (uint32_t) & (USART2->DR);
    //�ڴ滺����1
	hdma_usart2_rx.Instance->M0AR = (uint32_t)(rx1_buf);
    //�ڴ滺����2
	hdma_usart2_rx.Instance->M1AR = (uint32_t)(rx2_buf);
	
    //���ݳ���
	hdma_usart2_rx.Instance->NDTR = dma_buf_num;
    //ʹ��˫������
	SET_BIT(hdma_usart2_rx.Instance->CR, DMA_SxCR_DBM);

    //ʹ��DMA
	__HAL_DMA_ENABLE(&hdma_usart2_rx);
		
}


void USART_Init(void)
{
	RC_Init(sbus_rx_buf[0], sbus_rx_buf[1], SBUS_RX_BUF_NUM);//usart2
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);//����ϵͳ
	__HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);//ң����
	__HAL_UART_ENABLE_IT(&huart4,UART_IT_IDLE);//�Ӿ�
	__HAL_UART_ENABLE_IT(&huart5,UART_IT_RXNE);//������
	__HAL_UART_ENABLE_IT(&huart6,UART_IT_RXNE);//vofa	
}