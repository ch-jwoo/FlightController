/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
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

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for MPU9250_Task */
osThreadId_t MPU9250_TaskHandle;
uint32_t MPU9250_TaskBuffer[ 256 ];
osStaticThreadDef_t MPU9250_TaskControlBlock;
const osThreadAttr_t MPU9250_Task_attributes = {
  .name = "MPU9250_Task",
  .stack_mem = &MPU9250_TaskBuffer[0],
  .stack_size = sizeof(MPU9250_TaskBuffer),
  .cb_mem = &MPU9250_TaskControlBlock,
  .cb_size = sizeof(MPU9250_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for BME280_Task */
osThreadId_t BME280_TaskHandle;
uint32_t BME280_TaskBuffer[ 256 ];
osStaticThreadDef_t BME280_TaskControlBlock;
const osThreadAttr_t BME280_Task_attributes = {
  .name = "BME280_Task",
  .stack_mem = &BME280_TaskBuffer[0],
  .stack_size = sizeof(BME280_TaskBuffer),
  .cb_mem = &BME280_TaskControlBlock,
  .cb_size = sizeof(BME280_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for IST8310_Task */
osThreadId_t IST8310_TaskHandle;
uint32_t IST8310_TaskBuffer[ 256 ];
osStaticThreadDef_t IST8310_TaskControlBlock;
const osThreadAttr_t IST8310_Task_attributes = {
  .name = "IST8310_Task",
  .stack_mem = &IST8310_TaskBuffer[0],
  .stack_size = sizeof(IST8310_TaskBuffer),
  .cb_mem = &IST8310_TaskControlBlock,
  .cb_size = sizeof(IST8310_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for SD_Task */
osThreadId_t SD_TaskHandle;
uint32_t SD_TaskBuffer[ 2048 ];
osStaticThreadDef_t SD_TaskControlBlock;
const osThreadAttr_t SD_Task_attributes = {
  .name = "SD_Task",
  .stack_mem = &SD_TaskBuffer[0],
  .stack_size = sizeof(SD_TaskBuffer),
  .cb_mem = &SD_TaskControlBlock,
  .cb_size = sizeof(SD_TaskControlBlock),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for AHRS_Task */
osThreadId_t AHRS_TaskHandle;
uint32_t AHRS_TaskBuffer[ 256 ];
osStaticThreadDef_t AHRS_TaskControlBlock;
const osThreadAttr_t AHRS_Task_attributes = {
  .name = "AHRS_Task",
  .stack_mem = &AHRS_TaskBuffer[0],
  .stack_size = sizeof(AHRS_TaskBuffer),
  .cb_mem = &AHRS_TaskControlBlock,
  .cb_size = sizeof(AHRS_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for Commander_Task */
osThreadId_t Commander_TaskHandle;
uint32_t Commander_TaskBuffer[ 256 ];
osStaticThreadDef_t Commander_TaskControlBlock;
const osThreadAttr_t Commander_Task_attributes = {
  .name = "Commander_Task",
  .stack_mem = &Commander_TaskBuffer[0],
  .stack_size = sizeof(Commander_TaskBuffer),
  .cb_mem = &Commander_TaskControlBlock,
  .cb_size = sizeof(Commander_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for Debug_Task */
osThreadId_t Debug_TaskHandle;
const osThreadAttr_t Debug_Task_attributes = {
  .name = "Debug_Task",
  .priority = (osPriority_t) osPriorityAboveNormal,
  .stack_size = 512 * 4
};
/* Definitions for Buzzer_Task */
osThreadId_t Buzzer_TaskHandle;
uint32_t Buzzer_TaskBuffer[ 256 ];
osStaticThreadDef_t Buzzer_TaskControlBlock;
const osThreadAttr_t Buzzer_Task_attributes = {
  .name = "Buzzer_Task",
  .stack_mem = &Buzzer_TaskBuffer[0],
  .stack_size = sizeof(Buzzer_TaskBuffer),
  .cb_mem = &Buzzer_TaskControlBlock,
  .cb_size = sizeof(Buzzer_TaskControlBlock),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Health_Task */
osThreadId_t Health_TaskHandle;
uint32_t Health_TaskBuffer[ 256 ];
osStaticThreadDef_t Health_TaskControlBlock;
const osThreadAttr_t Health_Task_attributes = {
  .name = "Health_Task",
  .stack_mem = &Health_TaskBuffer[0],
  .stack_size = sizeof(Health_TaskBuffer),
  .cb_mem = &Health_TaskControlBlock,
  .cb_size = sizeof(Health_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for AC_Task */
osThreadId_t AC_TaskHandle;
uint32_t AC_TaskBuffer[ 256 ];
osStaticThreadDef_t AC_TaskControlBlock;
const osThreadAttr_t AC_Task_attributes = {
  .name = "AC_Task",
  .stack_mem = &AC_TaskBuffer[0],
  .stack_size = sizeof(AC_TaskBuffer),
  .cb_mem = &AC_TaskControlBlock,
  .cb_size = sizeof(AC_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for INS_Task */
osThreadId_t INS_TaskHandle;
const osThreadAttr_t INS_Task_attributes = {
  .name = "INS_Task",
  .priority = (osPriority_t) osPriorityHigh7,
  .stack_size = 2048 * 4
};
/* Definitions for PC_Task */
osThreadId_t PC_TaskHandle;
uint32_t PC_TaskBuffer[ 512 ];
osStaticThreadDef_t PC_TaskControlBlock;
const osThreadAttr_t PC_Task_attributes = {
  .name = "PC_Task",
  .stack_mem = &PC_TaskBuffer[0],
  .stack_size = sizeof(PC_TaskBuffer),
  .cb_mem = &PC_TaskControlBlock,
  .cb_size = sizeof(PC_TaskControlBlock),
  .priority = (osPriority_t) osPriorityRealtime,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void MPU9250_StartTask(void *argument);
extern void BME280_StartTask(void *argument);
extern void IST8310_StartTask(void *argument);
extern void SD_StartTask(void *argument);
extern void AHRS_StartTask(void *argument);
extern void Commander_StartTask(void *argument);
extern void Debug_StartTask(void *argument);
extern void Buzzer_StartTask(void *argument);
extern void Health_StartTask(void *argument);
extern void AC_StartTask(void *argument);
extern void INS_StartTask(void *argument);
extern void PC_StartTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of MPU9250_Task */
  MPU9250_TaskHandle = osThreadNew(MPU9250_StartTask, NULL, &MPU9250_Task_attributes);

  /* creation of BME280_Task */
  BME280_TaskHandle = osThreadNew(BME280_StartTask, NULL, &BME280_Task_attributes);

  /* creation of IST8310_Task */
  IST8310_TaskHandle = osThreadNew(IST8310_StartTask, NULL, &IST8310_Task_attributes);

  /* creation of SD_Task */
  SD_TaskHandle = osThreadNew(SD_StartTask, NULL, &SD_Task_attributes);

  /* creation of AHRS_Task */
  AHRS_TaskHandle = osThreadNew(AHRS_StartTask, NULL, &AHRS_Task_attributes);

  /* creation of Commander_Task */
  Commander_TaskHandle = osThreadNew(Commander_StartTask, NULL, &Commander_Task_attributes);

  /* creation of Debug_Task */
  Debug_TaskHandle = osThreadNew(Debug_StartTask, NULL, &Debug_Task_attributes);

  /* creation of Buzzer_Task */
  Buzzer_TaskHandle = osThreadNew(Buzzer_StartTask, NULL, &Buzzer_Task_attributes);

  /* creation of Health_Task */
  Health_TaskHandle = osThreadNew(Health_StartTask, NULL, &Health_Task_attributes);

  /* creation of AC_Task */
  AC_TaskHandle = osThreadNew(AC_StartTask, NULL, &AC_Task_attributes);

  /* creation of INS_Task */
  INS_TaskHandle = osThreadNew(INS_StartTask, NULL, &INS_Task_attributes);

  /* creation of PC_Task */
  PC_TaskHandle = osThreadNew(PC_StartTask, NULL, &PC_Task_attributes);

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
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
