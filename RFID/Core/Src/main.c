/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "rc522.h"
#include "stdio.h"
#include "string.h"
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
SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t CardID[5];
uint8_t CardID_s[5];
uint8_t MyID1[5] = { 0x26, 0x35, 0xaf, 0xac, 0xb3 };
uint8_t MyID2[5] = { 0x26, 0xfc, 0x5, 0xad, 0x11 };
uint8_t MyID3[5] = { 0x26, 0x52, 0xe, 0xad, 0x24 };
uint8_t MyID4[5] = { 0x26, 0x36, 0xf, 0xad, 0x11 };
uint8_t MyID5[5] = { 0x26, 0x5, 0x94, 0xac, 0x8 };

uint8_t Status = 0;
uint8_t Status1 = 0;
uint8_t Status2 = 0;
uint8_t Status3 = 0;
uint8_t Status4 = 0;
uint8_t Status5 = 0;

uint32_t t_prev = 0;
uint32_t t_prev2 = 0;
uint32_t t_prev3 = 0;
uint8_t DataRx[20];
uint8_t bufferRx[32];
uint8_t indexx;
uint8_t flag_Rx = 0;
uint8_t num = 0, num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0;
void check_out() {
	if (strcmp((char*) DataRx, "1\r\n") == 0) {
		num1 = 0;
	} else if (strcmp((char*) DataRx, "2\r\n") == 0) {
		num2 = 0;
	} else if (strcmp((char*) DataRx, "3\r\n") == 0) {
		num3 = 0;
	} else if (strcmp((char*) DataRx, "4\r\n") == 0) {
		num4 = 0;
	}
	num--;
	if (num == 0) {
		num = 0;
	}
	t_prev3 = HAL_GetTick();
	Status2 = 1;
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	flag_Rx = 1;

	HAL_UARTEx_ReceiveToIdle_IT(&huart3, DataRx, sizeof(DataRx));
}
uint8_t segmentNumber[10] = { 0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
		0x80, 0x90 };

void NumWrite(uint8_t number) {
	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, ((number >> 0) & 0x01));
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, ((number >> 1) & 0x01));
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, ((number >> 2) & 0x01));
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, ((number >> 3) & 0x01));
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, ((number >> 4) & 0x01));
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, ((number >> 5) & 0x01));
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, ((number >> 6) & 0x01));
}
void servo_in_ON() {
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 750);  // duty cycle is 2ms
}
void servo_in_OFF() {
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 250);  // duty cycle is 1 ms
}
int a = 1;
int b = 1;
int c = 1;
int d = 1;
uint8_t loa5;
uint64_t time;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

	HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, 0);
	HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, 0);
	HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, 0);
	HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, 0);
	HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, 0);
	HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, 0);
	HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, 0);
	//HAL_GPIO_WritePin(H_GPIO_Port, H_Pin, 0);

	HAL_UARTEx_ReceiveToIdle_IT(&huart3, DataRx, sizeof(DataRx));

	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	TM_MFRC522_Init();
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 2);

	HAL_GPIO_WritePin(Y1_GPIO_Port, Y1_Pin, 1);
	HAL_GPIO_WritePin(Y2_GPIO_Port, Y2_Pin, 1);
	HAL_GPIO_WritePin(Y3_GPIO_Port, Y3_Pin, 1);
	HAL_GPIO_WritePin(Y4_GPIO_Port, Y4_Pin, 1);
	HAL_GPIO_WritePin(Y5_GPIO_Port, Y5_Pin, 1);
	HAL_GPIO_WritePin(Y6_GPIO_Port, Y4_Pin, 1);
	HAL_GPIO_WritePin(Y7_GPIO_Port, Y5_Pin, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		if (flag_Rx == 1) {
			check_out();
			memset(DataRx, 0, strlen((char*) DataRx));
			flag_Rx = 0;
		}
		if (HAL_GetTick() - t_prev >= 100) {
			num = num1 + num2 + num3 + num4 + num5;
			if (!TM_MFRC522_Request(PICC_REQIDL, CardID)) {
				if (!TM_MFRC522_Anticoll(CardID)) {
					if (TM_MFRC522_Compare(CardID, MyID1) != MI_OK
							&& TM_MFRC522_Compare(CardID, MyID2) != MI_OK
							&& TM_MFRC522_Compare(CardID, MyID3) != MI_OK
							&& TM_MFRC522_Compare(CardID, MyID4) != MI_OK
							&& TM_MFRC522_Compare(CardID, MyID5) != MI_OK) {
						Status = 1;
						HAL_GPIO_WritePin(Y7_GPIO_Port, Y7_Pin, 0);
					}
					if (num >= 4) {
						Status1 = 1;
						HAL_GPIO_WritePin(Y6_GPIO_Port, Y6_Pin, 0);
					} else {
						if (TM_MFRC522_Compare(CardID, MyID1) == MI_OK) {
							HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
							servo_in_ON();
							num1 = 1;
							Status1 = 1;
							HAL_GPIO_WritePin(Y1_GPIO_Port, Y1_Pin, 0);
						} else if (TM_MFRC522_Compare(CardID, MyID2) == MI_OK) {
							HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1);
							servo_in_ON();
							num2 = 1;
							Status1 = 1;
							HAL_GPIO_WritePin(Y2_GPIO_Port, Y2_Pin, 0);
						} else if (TM_MFRC522_Compare(CardID, MyID3) == MI_OK) {
							HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1);
							servo_in_ON();
							num3 = 1;
							Status1 = 1;
							HAL_GPIO_WritePin(Y3_GPIO_Port, Y3_Pin, 0);
						} else if (TM_MFRC522_Compare(CardID, MyID4) == MI_OK) {
							HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1);
							servo_in_ON();
							num4 = 1;
							Status1 = 1;
							HAL_GPIO_WritePin(Y4_GPIO_Port, Y4_Pin, 0);
						} else if (TM_MFRC522_Compare(CardID, MyID5) == MI_OK) {
							HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1);
							servo_in_ON();
							num5 = 1;
							Status1 = 1;
							HAL_GPIO_WritePin(Y4_GPIO_Port, Y4_Pin, 0);
						}
					}

				}
				t_prev2 = HAL_GetTick();
			}
			Status1 = 1;
			t_prev = HAL_GetTick();
		}
		NumWrite(segmentNumber[num]);
		if (Status2 == 1) {
			HAL_GPIO_WritePin(Y5_GPIO_Port, Y5_Pin, 0);
			if (HAL_GetTick() - t_prev3 >= 100) {
				Status2 = 0;
				HAL_GPIO_WritePin(Y5_GPIO_Port, Y5_Pin, 1);
				t_prev3 = HAL_GetTick();
			}
		}
		if (Status1 == 1) {
			if (HAL_GetTick() - t_prev2 >= 5000) {			// 5000
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0);
				HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0);
				HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0);
				HAL_GPIO_WritePin(Y1_GPIO_Port, Y1_Pin, 1);
				HAL_GPIO_WritePin(Y2_GPIO_Port, Y2_Pin, 1);
				HAL_GPIO_WritePin(Y3_GPIO_Port, Y3_Pin, 1);
				HAL_GPIO_WritePin(Y4_GPIO_Port, Y4_Pin, 1);
				HAL_GPIO_WritePin(Y5_GPIO_Port, Y5_Pin, 1);
				HAL_GPIO_WritePin(Y6_GPIO_Port, Y6_Pin, 1);
				HAL_GPIO_WritePin(Y7_GPIO_Port, Y7_Pin, 1);
				servo_in_OFF();
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
				t_prev2 = HAL_GetTick();

				memset(CardID, 0, strlen((char*) CardID));
				Status1 = 0;
			}
		}

	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 16-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 10000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED_Pin|C_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED1_Pin|LED2_Pin|SS_Pin|E_Pin
                          |D_Pin|LED4_Pin|B_Pin|A_Pin
                          |Y7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_RFID_Pin|LED3_Pin|H_Pin|G_Pin
                          |F_Pin|Y4_Pin|Y3_Pin|Y2_Pin
                          |Y1_Pin|Y6_Pin|Y5_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin C_Pin */
  GPIO_InitStruct.Pin = LED_Pin|C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED1_Pin LED2_Pin SS_Pin E_Pin
                           D_Pin LED4_Pin B_Pin A_Pin
                           Y7_Pin */
  GPIO_InitStruct.Pin = LED1_Pin|LED2_Pin|SS_Pin|E_Pin
                          |D_Pin|LED4_Pin|B_Pin|A_Pin
                          |Y7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RFID_Pin LED3_Pin H_Pin G_Pin
                           F_Pin Y4_Pin Y3_Pin Y2_Pin
                           Y1_Pin Y6_Pin Y5_Pin */
  GPIO_InitStruct.Pin = LED_RFID_Pin|LED3_Pin|H_Pin|G_Pin
                          |F_Pin|Y4_Pin|Y3_Pin|Y2_Pin
                          |Y1_Pin|Y6_Pin|Y5_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : AMTHANH_Pin */
  GPIO_InitStruct.Pin = AMTHANH_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(AMTHANH_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
