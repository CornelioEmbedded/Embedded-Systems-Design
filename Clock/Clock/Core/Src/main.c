/* USER CODE BEGIN Header */
/**
  **************************
  * @file           : main.c
  * @brief          : Main program body
  **************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

//Variables
ADC_HandleTypeDef hadc1;
RTC_HandleTypeDef hrtc;
int D1=0x70;//Y7
int D2=0x60;
int D3=0x50;
int D4=0x40;
int D5=0x30;
int D6=0x20;
int D7=0x10;
int D8=0x00; //Y0

int numero=0;
int numeros[10]={0x0,0x01,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9};
int u,count;

uint16_t adcValue; //Asignacion de variable para el ADC
int sec,dsec,min,dmin,hou,dhou,hora,horas,minutos,segundos,boton;

int i=0x0;
//Voids
void setDisplay(int hora);
void displayNumber(int numero);
void cambioHora(int boton);


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_ADC1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  RTC_TimeTypeDef sTime;
    RTC_TimeTypeDef sDate;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
      {
        /* USER CODE END WHILE */
    	  displayNumber(numero);
    	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))
    	  	  	{
    	  	  	count=1;
    	  	  	HAL_Delay(1000);
    	  	  	cambioHora(boton);
    	  	  	sTime.Hours=horas;
    	  	  	sTime.Minutes=minutos;
    	  	  	sTime.Seconds=segundos;
    	  	  	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    	  	  	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);}
        /* USER CODE BEGIN 3 */
      }
      /* USER CODE END 3 */
    }

    void cambioHora(int boton)
    {
    	while(count==1)
    	{
    	HAL_ADC_Start(&hadc1);
        adcValue=(HAL_ADC_GetValue(&hadc1)/171);
    	horas=adcValue;
    	dhou=horas/10;
    	hou=horas%10;
    	setDisplay (hora);
    	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
    	count=2;
    	HAL_Delay(1000);}
    	}

    	while(count==2)
    	{
    	HAL_ADC_Start(&hadc1);
    	adcValue=(HAL_ADC_GetValue(&hadc1)/68);
    	minutos=adcValue;
    	dmin=minutos/10;
    	min=minutos%10;
    	setDisplay (hora);
    	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
    	count=3;
    	HAL_Delay(1000);}
    	}

    	while(count==3)
    	{
    	HAL_ADC_Start(&hadc1);
    	adcValue=(HAL_ADC_GetValue(&hadc1)/68);
    	segundos=adcValue;
    	dsec=segundos/10;
    	sec=segundos%10;
    	setDisplay (hora);
    	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
    	count=0;
    	HAL_Delay(1000);}
    	}
    }

    void displayNumber(int numero)
    {
    	RTC_TimeTypeDef sTime;
    	RTC_TimeTypeDef sDate;
    	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
    	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);
    	dhou=(sTime.Hours/16);
    	hou=(sTime.Hours%16);
    	dmin=(sTime.Minutes/16);
    	min=(sTime.Minutes%16);
    	dsec=(sTime.Seconds/16);
    	sec=(sTime.Seconds%16);
    	setDisplay (hora);
    }

    void setDisplay(int hora)
    {

    	GPIOD->ODR=numeros[sec]+D8;
    	HAL_Delay(1);
    	GPIOD->ODR=numeros[dsec]+D7;
    	HAL_Delay(1);
    	//GPIOD->ODR=numeros[dig3]+D3;
        //HAL_Delay(1);
    	GPIOD->ODR=numeros[min]+D5;
    	HAL_Delay(1);
    	GPIOD->ODR=numeros[dmin]+D4;
    	HAL_Delay(1);
    	//GPIOD->ODR=numeros[dig6]+D6;
    	//HAL_Delay(1);
    	GPIOD->ODR=numeros[hou]+D2;
    	HAL_Delay(1);
    	GPIOD->ODR=numeros[dhou]+D1;
    	HAL_Delay(1);
    }

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
