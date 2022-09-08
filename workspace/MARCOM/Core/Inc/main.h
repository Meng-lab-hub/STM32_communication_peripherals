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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GLCD_RW_Pin GPIO_PIN_7
#define GLCD_RW_GPIO_Port GPIOE
#define DB0_Pin GPIO_PIN_8
#define DB0_GPIO_Port GPIOE
#define DB1_Pin GPIO_PIN_9
#define DB1_GPIO_Port GPIOE
#define DB2_Pin GPIO_PIN_10
#define DB2_GPIO_Port GPIOE
#define DB3_Pin GPIO_PIN_11
#define DB3_GPIO_Port GPIOE
#define DB4_Pin GPIO_PIN_12
#define DB4_GPIO_Port GPIOE
#define DB5_Pin GPIO_PIN_13
#define DB5_GPIO_Port GPIOE
#define DB6_Pin GPIO_PIN_14
#define DB6_GPIO_Port GPIOE
#define DB7_Pin GPIO_PIN_15
#define DB7_GPIO_Port GPIOE
#define BL_PWM_Pin GPIO_PIN_8
#define BL_PWM_GPIO_Port GPIOC
#define GLCD_RESET_Pin GPIO_PIN_3
#define GLCD_RESET_GPIO_Port GPIOD
#define GLCD_DI_Pin GPIO_PIN_6
#define GLCD_DI_GPIO_Port GPIOD
#define GLCD_E_Pin GPIO_PIN_7
#define GLCD_E_GPIO_Port GPIOD
#define GLCD_CS1_Pin GPIO_PIN_4
#define GLCD_CS1_GPIO_Port GPIOB
#define GLCD_CS2_Pin GPIO_PIN_5
#define GLCD_CS2_GPIO_Port GPIOB
#define GLCD_EN_Pin GPIO_PIN_7
#define GLCD_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
