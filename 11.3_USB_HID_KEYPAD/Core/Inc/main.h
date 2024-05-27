/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef huart1;
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
#define BSP_R3_INPUT_Pin GPIO_PIN_13
#define BSP_R3_INPUT_GPIO_Port GPIOB
#define BSP_R3_INPUT_EXTI_IRQn EXTI4_15_IRQn
#define BSP_R4_INPUT_Pin GPIO_PIN_14
#define BSP_R4_INPUT_GPIO_Port GPIOB
#define BSP_R4_INPUT_EXTI_IRQn EXTI4_15_IRQn
#define BSP_C1_OUTPUT_Pin GPIO_PIN_15
#define BSP_C1_OUTPUT_GPIO_Port GPIOA
#define BSP_C2_OUTPUT_Pin GPIO_PIN_3
#define BSP_C2_OUTPUT_GPIO_Port GPIOB
#define BSP_C3_OUTPUT_Pin GPIO_PIN_4
#define BSP_C3_OUTPUT_GPIO_Port GPIOB
#define BSP_C4_OUTPUT_Pin GPIO_PIN_5
#define BSP_C4_OUTPUT_GPIO_Port GPIOB
#define BSP_R1_INPUT_Pin GPIO_PIN_6
#define BSP_R1_INPUT_GPIO_Port GPIOB
#define BSP_R1_INPUT_EXTI_IRQn EXTI4_15_IRQn
#define BSP_R2_INPUT_Pin GPIO_PIN_7
#define BSP_R2_INPUT_GPIO_Port GPIOB
#define BSP_R2_INPUT_EXTI_IRQn EXTI4_15_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
