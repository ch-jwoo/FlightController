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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

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
#define WINCH1_Pin GPIO_PIN_2
#define WINCH1_GPIO_Port GPIOE
#define WINCH2_Pin GPIO_PIN_3
#define WINCH2_GPIO_Port GPIOE
#define LIDAR_Pin GPIO_PIN_5
#define LIDAR_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define I2C2_SDA_Pin GPIO_PIN_0
#define I2C2_SDA_GPIO_Port GPIOF
#define I2C2_SCL_Pin GPIO_PIN_1
#define I2C2_SCL_GPIO_Port GPIOF
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define USART2_CTS_Pin GPIO_PIN_0
#define USART2_CTS_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_1
#define BUZZER_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define MOTOR5_Pin GPIO_PIN_6
#define MOTOR5_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define MOTOR7_Pin GPIO_PIN_1
#define MOTOR7_GPIO_Port GPIOB
#define External_LEC_contrl_Pin GPIO_PIN_12
#define External_LEC_contrl_GPIO_Port GPIOF
#define GPIO1_Pin GPIO_PIN_13
#define GPIO1_GPIO_Port GPIOF
#define GPIO2_Pin GPIO_PIN_14
#define GPIO2_GPIO_Port GPIOF
#define GPIO3_Pin GPIO_PIN_15
#define GPIO3_GPIO_Port GPIOF
#define GPIO4_Pin GPIO_PIN_0
#define GPIO4_GPIO_Port GPIOG
#define GPIO5_Pin GPIO_PIN_1
#define GPIO5_GPIO_Port GPIOG
#define UART7_RX_Pin GPIO_PIN_7
#define UART7_RX_GPIO_Port GPIOE
#define UART7_TX_Pin GPIO_PIN_8
#define UART7_TX_GPIO_Port GPIOE
#define SERVO4_Pin GPIO_PIN_9
#define SERVO4_GPIO_Port GPIOE
#define SERVO1_Pin GPIO_PIN_11
#define SERVO1_GPIO_Port GPIOE
#define SERVO2_Pin GPIO_PIN_13
#define SERVO2_GPIO_Port GPIOE
#define SERVO3_Pin GPIO_PIN_14
#define SERVO3_GPIO_Port GPIOE
#define SERVO5_Pin GPIO_PIN_14
#define SERVO5_GPIO_Port GPIOB
#define SERVO6_Pin GPIO_PIN_15
#define SERVO6_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define MOTOR1_Pin GPIO_PIN_12
#define MOTOR1_GPIO_Port GPIOD
#define MOTOR2_Pin GPIO_PIN_13
#define MOTOR2_GPIO_Port GPIOD
#define MOTOR3_Pin GPIO_PIN_14
#define MOTOR3_GPIO_Port GPIOD
#define MOTOR4_Pin GPIO_PIN_15
#define MOTOR4_GPIO_Port GPIOD
#define SD_DETECT_Pin GPIO_PIN_3
#define SD_DETECT_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define MOTOR8_Pin GPIO_PIN_6
#define MOTOR8_GPIO_Port GPIOC
#define MOTOR6_Pin GPIO_PIN_7
#define MOTOR6_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define USART2_RTS_Pin GPIO_PIN_4
#define USART2_RTS_GPIO_Port GPIOD
#define USART2_TX_Pin GPIO_PIN_5
#define USART2_TX_GPIO_Port GPIOD
#define SAFETY_SWITCH_Pin GPIO_PIN_7
#define SAFETY_SWITCH_GPIO_Port GPIOD
#define SPI1_INT_Pin GPIO_PIN_12
#define SPI1_INT_GPIO_Port GPIOG
#define SPI1_RESET_Pin GPIO_PIN_13
#define SPI1_RESET_GPIO_Port GPIOG
#define SPI1_WAKE_Pin GPIO_PIN_14
#define SPI1_WAKE_GPIO_Port GPIOG
#define SPI1_CS_Pin GPIO_PIN_3
#define SPI1_CS_GPIO_Port GPIOB
#define SPI1_MISO_Pin GPIO_PIN_4
#define SPI1_MISO_GPIO_Port GPIOB
#define I2C1_INT_Pin GPIO_PIN_5
#define I2C1_INT_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOB
#define UART8_RX_Pin GPIO_PIN_0
#define UART8_RX_GPIO_Port GPIOE
#define UART8_TX_Pin GPIO_PIN_1
#define UART8_TX_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
