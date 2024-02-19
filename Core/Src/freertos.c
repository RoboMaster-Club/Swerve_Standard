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
#include "global_define.h"
#include "tim.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "remote.h"
#include "bsp_can.h"
#include "imu_task.h"
#include "bsp_serial.h"
#include "dji_motor.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
osThreadId imu_TaskHandle;
/* USER CODE END Variables */
osThreadId global_init_tasHandle;
osThreadId can1_txHandle;
osThreadId debug_taskHandle;
osThreadId robot_ctrl_taskHandle;
osThreadId can2_txHandle;
osMessageQId can1_tx_queueHandle;
osMessageQId can2_tx_queueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void Global_Init(void);
/* USER CODE END FunctionPrototypes */

void GlobalInit(void const * argument);
extern void CAN_BSP_CAN1Tx(void const * argument);
void Debug_Task(void const * argument);
void Robot_Ctrl(void const * argument);
extern void CAN_BSP_CAN2Tx(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

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

  /* Create the queue(s) */
  /* definition and creation of can1_tx_queue */
  osMessageQDef(can1_tx_queue, 4, CAN_Tx_Pack_t);
  can1_tx_queueHandle = osMessageCreate(osMessageQ(can1_tx_queue), NULL);

  /* definition and creation of can2_tx_queue */
  osMessageQDef(can2_tx_queue, 4, CAN_Tx_Pack_t);
  can2_tx_queueHandle = osMessageCreate(osMessageQ(can2_tx_queue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of global_init_tas */
  osThreadDef(global_init_tas, GlobalInit, osPriorityNormal, 0, 128);
  global_init_tasHandle = osThreadCreate(osThread(global_init_tas), NULL);

  /* definition and creation of can1_tx */
  osThreadDef(can1_tx, CAN_BSP_CAN1Tx, osPriorityHigh, 0, 128);
  can1_txHandle = osThreadCreate(osThread(can1_tx), NULL);

  /* definition and creation of debug_task */
  osThreadDef(debug_task, Debug_Task, osPriorityIdle, 0, 128);
  debug_taskHandle = osThreadCreate(osThread(debug_task), NULL);

  /* definition and creation of robot_ctrl_task */
  osThreadDef(robot_ctrl_task, Robot_Ctrl, osPriorityHigh, 0, 512);
  robot_ctrl_taskHandle = osThreadCreate(osThread(robot_ctrl_task), NULL);

  /* definition and creation of can2_tx */
  osThreadDef(can2_tx, CAN_BSP_CAN2Tx, osPriorityHigh, 0, 128);
  can2_txHandle = osThreadCreate(osThread(can2_tx), NULL);

  /* USER CODE BEGIN RTOS_THREADS */

  osThreadDef(imu_task, IMU_Task, osPriorityHigh, 0, 256);
  imu_TaskHandle = osThreadCreate(osThread(imu_task), NULL);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_GlobalInit */
/**
 * @brief  Function implementing the global_init_tas thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_GlobalInit */
void GlobalInit(void const * argument)
{
  /* USER CODE BEGIN GlobalInit */
/* Infinite loop */
#ifdef LED_ENABLED
#endif

#ifdef REMOTE_ENABLED
  RemoteInit();
#endif

#ifdef CAN_ENABLED
  CAN_BSP_Init(&hcan1);
  CAN_BSP_Init(&hcan2);
#endif

#ifdef PWM_ENABLED
  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

  HAL_TIM_Base_Start(&htim8);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
#endif
  vTaskDelete(NULL);
  /* USER CODE END GlobalInit */
}

/* USER CODE BEGIN Header_Debug_Task */
/**
 * @brief Function implementing the debug_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Debug_Task */
__weak void Debug_Task(void const * argument)
{
  /* USER CODE BEGIN Debug_Task */
  /* Infinite loop */
  portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  const TickType_t TimeIncrement = pdMS_TO_TICKS(10);
  while (1)
  {
    printf("debug_param=%f\r\n",0.0f);
    vTaskDelayUntil(&xLastWakeTime, TimeIncrement);
  }
  /* USER CODE END Debug_Task */
}

/* USER CODE BEGIN Header_Robot_Ctrl */
/**
* @brief Function implementing the robot_ctrl_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Robot_Ctrl */
__weak void Robot_Ctrl(void const * argument)
{
  /* USER CODE BEGIN Robot_Ctrl */
  
  /* Infinite loop */
  for(;;)
  {
    DJI_Motor_Send(HEAD, 1, 3000, 0, 0, 0);
    osDelay(1);
  }
  /* USER CODE END Robot_Ctrl */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
