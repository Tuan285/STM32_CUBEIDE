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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define C_Pin GPIO_PIN_14
#define C_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOA
#define SS_Pin GPIO_PIN_4
#define SS_GPIO_Port GPIOA
#define LED_RFID_Pin GPIO_PIN_0
#define LED_RFID_GPIO_Port GPIOB
#define AMTHANH_Pin GPIO_PIN_1
#define AMTHANH_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOB
#define H_Pin GPIO_PIN_13
#define H_GPIO_Port GPIOB
#define G_Pin GPIO_PIN_14
#define G_GPIO_Port GPIOB
#define F_Pin GPIO_PIN_15
#define F_GPIO_Port GPIOB
#define E_Pin GPIO_PIN_8
#define E_GPIO_Port GPIOA
#define D_Pin GPIO_PIN_9
#define D_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_10
#define LED4_GPIO_Port GPIOA
#define B_Pin GPIO_PIN_11
#define B_GPIO_Port GPIOA
#define A_Pin GPIO_PIN_12
#define A_GPIO_Port GPIOA
#define Y7_Pin GPIO_PIN_15
#define Y7_GPIO_Port GPIOA
#define Y4_Pin GPIO_PIN_4
#define Y4_GPIO_Port GPIOB
#define Y3_Pin GPIO_PIN_5
#define Y3_GPIO_Port GPIOB
#define Y2_Pin GPIO_PIN_6
#define Y2_GPIO_Port GPIOB
#define Y1_Pin GPIO_PIN_7
#define Y1_GPIO_Port GPIOB
#define Y6_Pin GPIO_PIN_8
#define Y6_GPIO_Port GPIOB
#define Y5_Pin GPIO_PIN_9
#define Y5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
