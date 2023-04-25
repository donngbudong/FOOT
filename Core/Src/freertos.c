/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "packet.h"
#include "imu_data_decode.h"
#include "bsp_can.h"
#include "bsp_usart.h"
#include "stm32f4xx_it.h"
#include "remote_receive.h"

#include "chassis_task.h"
#include "gimbal_task.h"
#include "shoot_task.h"
#include "vofa_task.h"
#include "visual_receive_task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint32_t dbus_imu_off_line_time;
extern uint32_t imu_off_line_time;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern IWDG_HandleTypeDef hiwdg;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId CHASSISHandle;
osThreadId GIMBALHandle;
osThreadId SHOOTHandle;
osThreadId VISIONHandle;
osThreadId GUSUIHandle;
osThreadId OFF_LINEHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void CHASSIS_TASK(void const * argument);
void GIMBAL_TASK(void const * argument);
void SHOOT_TASK(void const * argument);
void VISION_TASK(void const * argument);
void GUSUI_TASK(void const * argument);
void OFF_LINE_TASK(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of CHASSIS */
  osThreadDef(CHASSIS, CHASSIS_TASK, osPriorityHigh, 0, 256);
  CHASSISHandle = osThreadCreate(osThread(CHASSIS), NULL);

  /* definition and creation of GIMBAL */
  osThreadDef(GIMBAL, GIMBAL_TASK, osPriorityHigh, 0, 256);
  GIMBALHandle = osThreadCreate(osThread(GIMBAL), NULL);

  /* definition and creation of SHOOT */
  osThreadDef(SHOOT, SHOOT_TASK, osPriorityHigh, 0, 256);
  SHOOTHandle = osThreadCreate(osThread(SHOOT), NULL);

  /* definition and creation of VISION */
  osThreadDef(VISION, VISION_TASK, osPriorityRealtime, 0, 256);
  VISIONHandle = osThreadCreate(osThread(VISION), NULL);

  /* definition and creation of GUSUI */
  osThreadDef(GUSUI, GUSUI_TASK, osPriorityRealtime, 0, 256);
  GUSUIHandle = osThreadCreate(osThread(GUSUI), NULL);

  /* definition and creation of OFF_LINE */
  osThreadDef(OFF_LINE, OFF_LINE_TASK, osPriorityRealtime, 0, 128);
  OFF_LINEHandle = osThreadCreate(osThread(OFF_LINE), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(2);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_CHASSIS_TASK */
/**
* @brief Function implementing the CHASSIS thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CHASSIS_TASK */
void CHASSIS_TASK(void const * argument)
{
  /* USER CODE BEGIN CHASSIS_TASK */
  /* Infinite loop */
  for(;;)
  {	
		chassis_ctrl();
		osDelay(2);
  }
  /* USER CODE END CHASSIS_TASK */
}

/* USER CODE BEGIN Header_GIMBAL_TASK */
/**
* @brief Function implementing the GIMBAL thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GIMBAL_TASK */
void GIMBAL_TASK(void const * argument)
{
  /* USER CODE BEGIN GIMBAL_TASK */
  /* Infinite loop */
  for(;;)
  {
		gimbal_ctrl();
		osDelay(2);
  }
  /* USER CODE END GIMBAL_TASK */
}

/* USER CODE BEGIN Header_SHOOT_TASK */
/**
* @brief Function implementing the SHOOT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SHOOT_TASK */
void SHOOT_TASK(void const * argument)
{
  /* USER CODE BEGIN SHOOT_TASK */
  /* Infinite loop */
  for(;;)
  {
		shoot_ctrl();
		osDelay(2);
  }
  /* USER CODE END SHOOT_TASK */
}

/* USER CODE BEGIN Header_VISION_TASK */
/**
* @brief Function implementing the VISION thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_VISION_TASK */
void VISION_TASK(void const * argument)
{
  /* USER CODE BEGIN VISION_TASK */
  /* Infinite loop */
  for(;;)
  {
		visual_send_date();
		osDelay(3);
  }
  /* USER CODE END VISION_TASK */
}

/* USER CODE BEGIN Header_GUSUI_TASK */
/**
* @brief Function implementing the GUSUI thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GUSUI_TASK */
void GUSUI_TASK(void const * argument)
{
  /* USER CODE BEGIN GUSUI_TASK */
//		uint32_t currentTime;	
  /* Infinite loop */
  for(;;)
  {
//		currentTime = xTaskGetTickCount();//当前系统时间
		GUSIUI();
		vTaskSuspend(OFF_LINEHandle);//挂起任务

//		vTaskDelayUntil(&currentTime, 10);//绝对延时	
		osDelay(3);

  }
  /* USER CODE END GUSUI_TASK */
}

/* USER CODE BEGIN Header_OFF_LINE_TASK */
/**
* @brief Function implementing the OFF_LINE thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OFF_LINE_TASK */
void OFF_LINE_TASK(void const * argument)
{
  /* USER CODE BEGIN OFF_LINE_TASK */
  /* Infinite loop */
  for(;;)
  {
//		currentTime = xTaskGetTickCount();//当前系统时间
//		if(HAL_GetTick()-imu_off_line_time > 500)
//		{
//			
//		}
//		{
//			HAL_IWDG_Refresh(&hiwdg);//执行喂狗操作 
//		}
		osDelay(3);
		
  }
  /* USER CODE END OFF_LINE_TASK */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
