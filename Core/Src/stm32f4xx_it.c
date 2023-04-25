/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "drv_usart.h"



#include "imu_data_decode.h"
#include "packet.h"
#include "imu_data_decode.h"
#include "referee.h"
#include <string.h>
#include "visual_receive_task.h"
#include "remote_receive.h"
#include "system.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
uint8_t ch;
extern uint8_t sbus_rx_buf[2][SBUS_RX_BUF_NUM];
extern uint8_t  Judge_Buffer[JUDGE_BUFFER_LEN ];
extern uint8_t  Visual_Buffer[VISAUAL_DATE_LEN];

extern IWDG_HandleTypeDef hiwdg;
extern RC_ctrl_t rc_ctrl;

extern uint32_t Imu_time;//遥控器
extern uint32_t Remote_time;//遥控器
extern uint32_t Refer_time;//裁判系统
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart6;
extern TIM_HandleTypeDef htim14;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
		
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart4_rx);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles CAN1 RX0 interrupts.
  */
void CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX0_IRQn 0 */

  /* USER CODE END CAN1_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan1);
  /* USER CODE BEGIN CAN1_RX0_IRQn 1 */

  /* USER CODE END CAN1_RX0_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */
		imu_ctrl();
  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE)!=RESET) 
		{
			__HAL_UART_CLEAR_IDLEFLAG(&huart1);
			HAL_UART_DMAStop(&huart1);
			uint8_t len=128-__HAL_DMA_GET_COUNTER(huart1.hdmarx);
			HAL_UART_Receive_DMA(&huart1,Judge_Buffer,128);
			Judege_read_data(Judge_Buffer);		//读取裁判系统数据
			memset(Judge_Buffer, 0, 128);
			HAL_UART_DMAResume(&huart1);
		}
  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	if(USART2->SR & UART_FLAG_IDLE)
		{
			__HAL_UART_CLEAR_PEFLAG(&huart2);

			static uint16_t this_time_rx_len = 0;

			if ((huart2.hdmarx->Instance->CR & DMA_SxCR_CT) == RESET)
			{
					__HAL_DMA_DISABLE(huart2.hdmarx);
					this_time_rx_len = SBUS_RX_BUF_NUM - __HAL_DMA_GET_COUNTER(huart2.hdmarx);
					__HAL_DMA_SET_COUNTER(huart2.hdmarx, SBUS_RX_BUF_NUM);
					huart2.hdmarx->Instance->CR |= DMA_SxCR_CT;
					__HAL_DMA_ENABLE(huart2.hdmarx);

				if(this_time_rx_len == RC_FRAME_LENGTH)
				{
						sbus_to_rc(sbus_rx_buf[0], &rc_ctrl);
				}
			}
			
			else
			{
					__HAL_DMA_DISABLE(huart2.hdmarx);
					this_time_rx_len = SBUS_RX_BUF_NUM - __HAL_DMA_GET_COUNTER(huart2.hdmarx);
					__HAL_DMA_SET_COUNTER(huart2.hdmarx, SBUS_RX_BUF_NUM);
					huart2.hdmarx->Instance->CR &= ~(DMA_SxCR_CT);
					__HAL_DMA_ENABLE(huart2.hdmarx);
				if(this_time_rx_len == RC_FRAME_LENGTH)
				{
						//处理遥控器数据
					sbus_to_rc(sbus_rx_buf[1], &rc_ctrl);
				}
			}
//		Remote_time = HAL_GetTick()+300;

	 }
  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles TIM8 trigger and commutation interrupts and TIM14 global interrupt.
  */
void TIM8_TRG_COM_TIM14_IRQHandler(void)
{
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 0 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 0 */
  HAL_TIM_IRQHandler(&htim14);
  /* USER CODE BEGIN TIM8_TRG_COM_TIM14_IRQn 1 */

  /* USER CODE END TIM8_TRG_COM_TIM14_IRQn 1 */
}

/**
  * @brief This function handles UART4 global interrupt.
  */
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */

  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */
if(__HAL_UART_GET_FLAG(&huart4,UART_FLAG_IDLE)!=RESET) 
	{
		__HAL_UART_CLEAR_IDLEFLAG(&huart4);
		HAL_UART_DMAStop(&huart4);
		uint8_t len=15-__HAL_DMA_GET_COUNTER(huart4.hdmarx);
		HAL_UART_Receive_DMA(&huart4,Visual_Buffer,100);
		visual_date(Visual_Buffer);								//读取视觉数据
		HAL_UART_DMAResume(&huart4);
	}
	
  /* USER CODE END UART4_IRQn 1 */
}

/**
  * @brief This function handles UART5 global interrupt.
  */
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */

  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */
if(__HAL_UART_GET_FLAG(&huart5,UART_FLAG_RXNE)!=RESET) 
	{	
		HAL_UART_Receive(&huart5,&ch,1,100);
		Packet_Decode(ch);
		__HAL_UART_CLEAR_NEFLAG(&huart5);					/*清除中断标志位*/
//		Imu_time=HAL_GetTick()+500;								/*掉线检测*/
	}
  /* USER CODE END UART5_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream2 global interrupt.
  */
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}

/**
  * @brief This function handles CAN2 RX0 interrupts.
  */
void CAN2_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN2_RX0_IRQn 0 */

  /* USER CODE END CAN2_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan2);
  /* USER CODE BEGIN CAN2_RX0_IRQn 1 */

  /* USER CODE END CAN2_RX0_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream7 global interrupt.
  */
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/**
  * @brief This function handles USART6 global interrupt.
  */
void USART6_IRQHandler(void)
{
  /* USER CODE BEGIN USART6_IRQn 0 */

  /* USER CODE END USART6_IRQn 0 */
  HAL_UART_IRQHandler(&huart6);
  /* USER CODE BEGIN USART6_IRQn 1 */
//if(__HAL_UART_GET_FLAG(&huart6,UART_FLAG_RXNE)!=RESET) 
//		{	
//			HAL_IWDG_Refresh(&hiwdg);//
//			HAL_UART_Receive(&huart6,&ch,1,100);
//			Packet_Decode(ch);
//			__HAL_UART_CLEAR_NEFLAG(&huart6);
//		}
  /* USER CODE END USART6_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
