/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED3_Pin GPIO_PIN_13
#define LED3_GPIO_Port GPIOC
#define MQ_Pin GPIO_PIN_0
#define MQ_GPIO_Port GPIOA
#define CD_Pin GPIO_PIN_5
#define CD_GPIO_Port GPIOA
#define IN4_Pin GPIO_PIN_7
#define IN4_GPIO_Port GPIOA
#define IN3_Pin GPIO_PIN_0
#define IN3_GPIO_Port GPIOB
#define IN2_Pin GPIO_PIN_1
#define IN2_GPIO_Port GPIOB
#define IN1_Pin GPIO_PIN_10
#define IN1_GPIO_Port GPIOB
#define LED6_Pin GPIO_PIN_11
#define LED6_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_12
#define LED4_GPIO_Port GPIOB
#define BT6_Pin GPIO_PIN_14
#define BT6_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_15
#define LED1_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_8
#define LED5_GPIO_Port GPIOA
#define BT5_Pin GPIO_PIN_11
#define BT5_GPIO_Port GPIOA
#define BT4_Pin GPIO_PIN_12
#define BT4_GPIO_Port GPIOA
#define BT3_Pin GPIO_PIN_15
#define BT3_GPIO_Port GPIOA
#define BT1_Pin GPIO_PIN_4
#define BT1_GPIO_Port GPIOB
#define LED_BUI_Pin GPIO_PIN_5
#define LED_BUI_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_8
#define LED2_GPIO_Port GPIOB
#define BT2_Pin GPIO_PIN_9
#define BT2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
