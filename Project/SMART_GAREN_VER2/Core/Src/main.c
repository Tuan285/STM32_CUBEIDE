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
#include "STEPPER.h"
#include "stdio.h"
#include "string.h"
#include "i2c-lcd.h"
#include "button.h"
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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
Button_t bt1, bt2, bt3, bt4;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#define STEPPER_MOTOR1   0
void microDelay(uint16_t delay) {
	__HAL_TIM_SET_COUNTER(&htim1, 0);
	while (__HAL_TIM_GET_COUNTER(&htim1) < delay)
		;
}
uint32_t value_adc[3];
uint16_t DAD, DAD2;
uint64_t t_prev, t_prev2;
#define DHT22_PORT GPIOA
#define DHT22_PIN GPIO_PIN_0
uint8_t RH1, RH2, TC1, TC2, SUM, CHECK;
uint32_t pMillis, cMillis;
float tCelsius = 0;

float tFahrenheit = 0;
float RH = 0;

uint8_t DHT22_Start(void) {
	uint8_t Response = 0;
	GPIO_InitTypeDef GPIO_InitStructPrivate = { 0 };
	GPIO_InitStructPrivate.Pin = DHT22_PIN;
	GPIO_InitStructPrivate.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructPrivate.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStructPrivate.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT22_PORT, &GPIO_InitStructPrivate); // set the pin as output
	HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, 0);   // pull the pin low
	microDelay(1300);   // wait for 1300us
	HAL_GPIO_WritePin(DHT22_PORT, DHT22_PIN, 1);   // pull the pin high
	microDelay(30);   // wait for 30us
	GPIO_InitStructPrivate.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructPrivate.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(DHT22_PORT, &GPIO_InitStructPrivate); // set the pin as input
	microDelay(40);
	if (!(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))) {
		microDelay(80);
		if ((HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)))
			Response = 1;
	}
	pMillis = HAL_GetTick();
	cMillis = HAL_GetTick();
	while ((HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)) && pMillis + 2 > cMillis) {
		cMillis = HAL_GetTick();
	}
	return Response;
}
uint8_t DHT22_Read(void) {
	uint8_t a, b;
	for (a = 0; a < 8; a++) {
		pMillis = HAL_GetTick();
		cMillis = HAL_GetTick();
		while (!(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))
				&& pMillis + 2 > cMillis) {  // wait for the pin to go high
			cMillis = HAL_GetTick();
		}
		microDelay(40);   // wait for 40 us
		if (!(HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN)))   // if the pin is low
			b &= ~(1 << (7 - a));
		else
			b |= (1 << (7 - a));
		pMillis = HAL_GetTick();
		cMillis = HAL_GetTick();
		while ((HAL_GPIO_ReadPin(DHT22_PORT, DHT22_PIN))
				&& pMillis + 2 > cMillis) {  // wait for the pin to go low
			cMillis = HAL_GetTick();
		}
	}
	return b;
}
void DHT22_value() {
	if (DHT22_Start()) {
		RH1 = DHT22_Read(); // First 8bits of humidity
		RH2 = DHT22_Read(); // Second 8bits of Relative humidity
		TC1 = DHT22_Read(); // First 8bits of Celsius
		TC2 = DHT22_Read(); // Second 8bits of Celsius
		SUM = DHT22_Read(); // Check sum
		CHECK = RH1 + RH2 + TC1 + TC2;
		if (CHECK == SUM) {
			if (TC1 > 127) // If TC1=10000000, negative temperature
					{
				tCelsius = (float) TC2 / 10 * (-1);
			} else {
				tCelsius = (float) ((TC1 << 8) | TC2) / 10;
			}
			tFahrenheit = tCelsius * 9 / 5 + 32;
			RH = (float) ((RH1 << 8) | RH2) / 10;
		}
	}
}
long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
uint8_t bom, boms, quat, den, rem;
uint8_t bom1 = 0, bom2 = 0, quat1 = 0, den1 = 0;
uint8_t tt = 0, tt1 = 0;
uint8_t tt_rem;
void bt_press_callback(Button_t *button) {
	if (tt == 1) {					// bang tay
		if (button == &bt1) {
			if (bom == 1) {
				bom = 0;
			} else {
				bom = 1;
			}
		}
		if (button == &bt2) {
			if (boms == 1) {
				boms = 0;
			} else {
				boms = 1;
			}
		}
		if (button == &bt3) {
			if (tt_rem == 1) {
				STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CCW);
				tt_rem = 0;
			} else {
				STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CW);
				tt_rem = 1;
			}
		}
	}
	if (button == &bt4) {
		if (tt == 1) {
			tt = 0;
		} else {
			tt = 1;
		}
	}
}
void on_off_led(uint8_t b, uint8_t b2) {
	switch (b) {
	case 1:
		HAL_GPIO_WritePin(BOM_GPIO_Port, BOM_Pin, 1);
		break;
	case 0:
		HAL_GPIO_WritePin(BOM_GPIO_Port, BOM_Pin, 0);
		break;
	default:
		break;
	}
	switch (b2) {
	case 1:
		HAL_GPIO_WritePin(BOM2_GPIO_Port, BOM2_Pin, 1);
		break;
	case 0:
		HAL_GPIO_WritePin(BOM2_GPIO_Port, BOM2_Pin, 0);
		break;
	default:
		break;
	}
}
uint8_t buf1[20], buf2[20], buf3[20], buffer[30];
void show_lcd() {
	sprintf((char*) buf1, "Nhiet Do: %2.1f ", tCelsius);
	sprintf((char*) buf2, "DAD:%d", DAD);
	sprintf((char*) buf3, " DA:%.1f", RH);
	//lcd_clear_display();
	lcd_goto_XY(1, 0);
	lcd_send_string((char*) buf1);
	lcd_send_string("C");
	lcd_goto_XY(2, 0);
	lcd_send_string((char*) buf2);
	lcd_send_string((char*) buf3);
}
uint8_t DataRx[20];
uint8_t flag = 0;
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	flag = 1;
	HAL_UARTEx_ReceiveToIdle_IT(&huart1, DataRx, sizeof(DataRx));
}
void check() {
	if (strcmp((char*) DataRx, "B11\r\n") == 0) {
		bom = 1;
	} else if (strcmp((char*) DataRx, "B10\r\n") == 0) {
		bom = 0;
	} else if (strcmp((char*) DataRx, "B20\r\n") == 0) {
		boms = 0;
	} else if (strcmp((char*) DataRx, "B21\r\n") == 0) {
		boms = 1;
	} else if (strcmp((char*) DataRx, "R0\r\n") == 0) {
		if (tt_rem == 1) {
			STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CCW);
			tt_rem = 0;
		} else {
			STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CW);
			tt_rem = 1;
		}
	} else if (strcmp((char*) DataRx, "R1\r\n") == 0) {
		if (tt_rem == 1) {
			STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CCW);
			tt_rem = 0;
		} else {
			STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CW);
			tt_rem = 1;
		}
	} else if (strcmp((char*) DataRx, "T0\r\n") == 0) {
		tt = 0;
	} else if (strcmp((char*) DataRx, "T1\r\n") == 0) {
		tt = 1;
	}
}
uint8_t cb_mua, check_cbmua;
uint8_t b1, b2, b3, b4;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	STEPPER_TMR_OVF_ISR(htim);
}
uint16_t AD_RES = 0;
uint8_t t_rems;
void auto_rem() {
	cb_mua = HAL_GPIO_ReadPin(MUA_GPIO_Port, MUA_Pin);
	if (HAL_GPIO_ReadPin(MUA_GPIO_Port, MUA_Pin) == 0) {
		t_prev2  = HAL_GetTick();
		if (tt_rem == 0) {
			STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CW);
			tt_rem = 1;
		}
	} else {
		if (tt_rem == 1 && HAL_GetTick() - t_prev2 >= 3000) {
			STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 6500, DIR_CCW);
			tt_rem = 0;
		}
	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
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
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
	MX_TIM1_Init();
	MX_TIM4_Init();
	/* USER CODE BEGIN 2 */
	Button_Init(&bt1, BT1_GPIO_Port, BT1_Pin);
	Button_Init(&bt2, BT2_GPIO_Port, BT2_Pin);
	Button_Init(&bt3, BT3_GPIO_Port, BT3_Pin);
	Button_Init(&bt4, BT4_GPIO_Port, BT4_Pin);

	HAL_UARTEx_ReceiveToIdle_IT(&huart1, DataRx, sizeof(DataRx));
	HAL_ADC_Start_DMA(&hadc1, value_adc, 3);
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_TIM_Base_Start(&htim1);

	lcd_init();
	lcd_goto_XY(1, 0);
	lcd_send_string("XIN CHAO");
	t_prev = HAL_GetTick();
	t_prev2 = HAL_GetTick();
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
	STEPPERS_Init_TMR(&htim4);
	STEPPER_SetSpeed(STEPPER_MOTOR1, 4096 >> 8);
	tt = 1;
	bom = 0;
	boms = 0;
	//STEPPER_Step_NonBlocking(STEPPER_MOTOR1, 2000, DIR_CW);		// 1 vong
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		bt_handle(&bt1);
		bt_handle(&bt2);
		bt_handle(&bt3);
		bt_handle(&bt4);
		b1 = HAL_GPIO_ReadPin(BT1_GPIO_Port, BT1_Pin);
		b2 = HAL_GPIO_ReadPin(BT2_GPIO_Port, BT2_Pin);
		b3 = HAL_GPIO_ReadPin(BT3_GPIO_Port, BT3_Pin);
		b4 = HAL_GPIO_ReadPin(BT4_GPIO_Port, BT4_Pin);
		if (flag == 1) {
			check();
			memset(DataRx, 0, strlen((char*) DataRx));
			flag = 0;
		}
		if (HAL_GetTick() - t_prev >= 500) {
			//HAL_GPIO_TogglePin(DEN_GPIO_Port, DEN_Pin);
			DHT22_value();
			HAL_ADC_Start_DMA(&hadc1, value_adc, 3);
			DAD = map(value_adc[0], 0, 4096, 0, 100);
			DAD2 = map(value_adc[1], 0, 4096, 0, 100);
			if (value_adc[2] >= 2800) {
				HAL_GPIO_WritePin(DEN_GPIO_Port, DEN_Pin, 1);
			} else {
				HAL_GPIO_WritePin(DEN_GPIO_Port, DEN_Pin, 0);
			}
			show_lcd();
			sprintf((char*) buffer, "%.1f/%.1f/%d/%d/%d/%d/%d/%d\r\n", tCelsius,
					RH, DAD, DAD2, bom, boms, tt_rem, tt);
			HAL_UART_Transmit(&huart1, buffer, strlen((char*) buffer), 2000);
			t_prev = HAL_GetTick();
		}
		if (tt == 0) {
			auto_rem();
			if (DAD >= 65) {
				bom = 1;
			}
			if (DAD < 30) {
				bom = 0;
			}
			if (DAD2 >= 60) {
				boms = 1;
			}
			if (DAD2 < 60) {
				boms = 0;
			}
		}
		on_off_led(bom, boms);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
	PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void) {

	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */
	/** Common config
	 */
	hadc1.Instance = ADC1;
	hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 3;
	if (HAL_ADC_Init(&hadc1) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_3;
	sConfig.Rank = ADC_REGULAR_RANK_2;
	sConfig.SamplingTime = ADC_SAMPLETIME_41CYCLES_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/** Configure Regular Channel
	 */
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_REGULAR_RANK_3;
	sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC1_Init 2 */

	/* USER CODE END ADC1_Init 2 */

}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void) {

	/* USER CODE BEGIN TIM1_Init 0 */

	/* USER CODE END TIM1_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM1_Init 1 */

	/* USER CODE END TIM1_Init 1 */
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 72 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 0xffff - 1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM1_Init 2 */

	/* USER CODE END TIM1_Init 2 */

}

/**
 * @brief TIM4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM4_Init(void) {

	/* USER CODE BEGIN TIM4_Init 0 */

	/* USER CODE END TIM4_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 0;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 65535;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void) {

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void) {

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Channel1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, IN4_Pin | IN3_Pin | IN2_Pin | BOM2_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, DEN_Pin | BOM_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : LED_Pin */
	GPIO_InitStruct.Pin = LED_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : DHT22_Pin */
	GPIO_InitStruct.Pin = DHT22_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DHT22_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : MUA_Pin */
	GPIO_InitStruct.Pin = MUA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(MUA_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : IN4_Pin IN3_Pin IN2_Pin BOM2_Pin */
	GPIO_InitStruct.Pin = IN4_Pin | IN3_Pin | IN2_Pin | BOM2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : IN1_Pin */
	GPIO_InitStruct.Pin = IN1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(IN1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : BT2_Pin BT3_Pin BT1_Pin BT4_Pin */
	GPIO_InitStruct.Pin = BT2_Pin | BT3_Pin | BT1_Pin | BT4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pins : DEN_Pin BOM_Pin */
	GPIO_InitStruct.Pin = DEN_Pin | BOM_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
