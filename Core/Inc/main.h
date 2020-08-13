/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void cppMain();
void MPU9250_StartTask(void *argument);
void BME280_StartTask(void *argument);
void IST8310_StartTask(void *argument);
void SD_StartTask(void *argument);
void AHRS_StartTask(void *argument);
void Commander_StartTask(void *argument);
void Debug_StartTask(void *argument);
void Buzzer_StartTask(void *argument);
void Health_StartTask(void *argument);
void AC_StartTask(void *argument);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WINCH_CONTROL1_Pin GPIO_PIN_2
#define WINCH_CONTROL1_GPIO_Port GPIOE
#define WINCH_CONTROL2_Pin GPIO_PIN_3
#define WINCH_CONTROL2_GPIO_Port GPIOE
#define LIDAR_Pin GPIO_PIN_5
#define LIDAR_GPIO_Port GPIOE
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOF
#define BAT_CURRENT_Pin GPIO_PIN_2
#define BAT_CURRENT_GPIO_Port GPIOC
#define BAT_VOLTAGE_Pin GPIO_PIN_3
#define BAT_VOLTAGE_GPIO_Port GPIOC
#define TELEM_CTS_Pin GPIO_PIN_0
#define TELEM_CTS_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOA
#define TELEM_RX_Pin GPIO_PIN_3
#define TELEM_RX_GPIO_Port GPIOA
#define M7_Pin GPIO_PIN_6
#define M7_GPIO_Port GPIOA
#define SD_DETECTION_Pin GPIO_PIN_5
#define SD_DETECTION_GPIO_Port GPIOC
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define M5_Pin GPIO_PIN_1
#define M5_GPIO_Port GPIOB
#define EXTERNAL_LED_CONTROL_Pin GPIO_PIN_12
#define EXTERNAL_LED_CONTROL_GPIO_Port GPIOF
#define SBUS_RX_Pin GPIO_PIN_7
#define SBUS_RX_GPIO_Port GPIOE
#define SBUS_TX_Pin GPIO_PIN_8
#define SBUS_TX_GPIO_Port GPIOE
#define S4_Pin GPIO_PIN_9
#define S4_GPIO_Port GPIOE
#define S1_Pin GPIO_PIN_11
#define S1_GPIO_Port GPIOE
#define S2_Pin GPIO_PIN_13
#define S2_GPIO_Port GPIOE
#define S3_Pin GPIO_PIN_14
#define S3_GPIO_Port GPIOE
#define S5_Pin GPIO_PIN_14
#define S5_GPIO_Port GPIOB
#define S6_Pin GPIO_PIN_15
#define S6_GPIO_Port GPIOB
#define STLINK_RX_Pin GPIO_PIN_8
#define STLINK_RX_GPIO_Port GPIOD
#define STLINK_TX_Pin GPIO_PIN_9
#define STLINK_TX_GPIO_Port GPIOD
#define USB_OTG_FS_PWR_EN_Pin GPIO_PIN_10
#define USB_OTG_FS_PWR_EN_GPIO_Port GPIOD
#define M3_Pin GPIO_PIN_12
#define M3_GPIO_Port GPIOD
#define M4_Pin GPIO_PIN_13
#define M4_GPIO_Port GPIOD
#define M2_Pin GPIO_PIN_14
#define M2_GPIO_Port GPIOD
#define M1_Pin GPIO_PIN_15
#define M1_GPIO_Port GPIOD
#define SD_DETECTIONG3_Pin GPIO_PIN_3
#define SD_DETECTIONG3_GPIO_Port GPIOG
#define USB_OTG_FS_OVCR_Pin GPIO_PIN_7
#define USB_OTG_FS_OVCR_GPIO_Port GPIOG
#define M8_Pin GPIO_PIN_6
#define M8_GPIO_Port GPIOC
#define M6_Pin GPIO_PIN_7
#define M6_GPIO_Port GPIOC
#define TELEM_RTS_Pin GPIO_PIN_4
#define TELEM_RTS_GPIO_Port GPIOD
#define TELEM_TX_Pin GPIO_PIN_5
#define TELEM_TX_GPIO_Port GPIOD
#define SAFETY_SWITCH_Pin GPIO_PIN_7
#define SAFETY_SWITCH_GPIO_Port GPIOD
#define MPU9250_INT_Pin GPIO_PIN_5
#define MPU9250_INT_GPIO_Port GPIOB
#define MPU9250_SCL_Pin GPIO_PIN_6
#define MPU9250_SCL_GPIO_Port GPIOB
#define MPU9250_SDA_Pin GPIO_PIN_9
#define MPU9250_SDA_GPIO_Port GPIOB
#define GPS_RX_Pin GPIO_PIN_0
#define GPS_RX_GPIO_Port GPIOE
#define GPS_TX_Pin GPIO_PIN_1
#define GPS_TX_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
